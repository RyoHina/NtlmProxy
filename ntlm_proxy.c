/************************************************/
/*type1:  各字段填写完成后，其中关键在于标志位，用于对话协商，在linux平台下，其主机名
 *        和域名可以为空，将各字段消息填写完毕后，用base64进行加密处理。
 *type2:  在收到消息后，先将消息用base64进行解码，然后提取消息存在在消息2的结构体中，以供
 *        type3使用。
 *type3： 根据消息2结构中的标志位，判断采用那种消息响应方式，然后根据消息2中的挑战码、
 *        目的主机的相关信息，用户名、密码，构建消息3结构体，完善消息结构体中的不同域，然
 *        后通过http数据包发送出去。*/
/*#ifdef WIN32
#include <winsock2.h>
#endif
#ifdef LINUX*/
#include <netdb.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/resource.h>
#include <sys/wait.h>
//#endif
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "arithmetic.h"
#include "httppc_ntlm.h"
#include "ntlm_proxy.h"
#include "wei_util.h"
struct s_wei_http_response{
	char    version[10];
	int     code;
	int     header_num;
	char ** header;
	char *  body;
	bool    is_suppoort_ntlm;
	char *  Connection;
	char *  Authenticate;
};

static char * httppc_proxy_ip = NULL,* httppc_host = NULL,* httppc_domain = NULL, 
            * httppc_user = NULL, * httppc_passwd = NULL;
static UINT httppc_proxy_port;

static int httppc_sock = -1;
static bool is_httppc_connected = false;

/******************************** PART 1 :HTTP util 工具集 *******************************/
PRIVATE char* wei_get_domain_ip(char* ip_str){
	struct hostent *p;
	p = (struct hostent*)gethostbyname(ip_str);
	if(p == NULL)
		return NULL;
	return inet_ntoa(*(struct in_addr*)(*(p->h_addr_list)));
}
/*分析响应行*/
PRIVATE bool wei_http_analyse_response_startline(OUT struct s_wei_http_response * response,IN OUT char * startline){
	char * part[3];
	memset(part,0,sizeof(part));
	wei_util_replace_all(startline,"  "," ");
	/*看是否可以分成三个部分*/
	if(!wei_util_split(startline," ",3,part))
		return false;
	char * ch = strchr(part[0],'/');
	if(ch == NULL)
		return false;
	strcpy(response->version ,ch + 1);

	if(!wei_util_check_allnum(part[1]))
		return false;
	/*响应行的第一个段就是响应码*/
	response->code = atoi(part[1]);
	return true;
}

PRIVATE char * wei_http_analyse_get_value(IN struct s_wei_http_response * response, IN const char * name,IN int index){
	int num = 0,i;
	char * ch,name_1[128],name_2[128];
	if(strlen(name) > 126)
		return NULL;
	sprintf(name_1,"%s:",name);
	sprintf(name_2,"%s :",name);
	for(i = 1; i < response->header_num; i ++){
		/*这个比较的时候忽略大小写*/
		if(wei_util_str_compare(response->header[i],name_1,false,strlen(name_1))){
			if(index <= num){
				ch = response->header[i] + strlen(name_1);
				/*去掉两者之间的空格*/
				while(* ch == ' ')
					ch ++;
				return ch;
			}else{
				num ++;
			}
		}else if(wei_util_str_compare(response->header[i],name_2,false,strlen(name_2))){
			if(index <= num){
				ch = response->header[i] + strlen(name_2);
				while(* ch == ' ')
					ch ++;
				return ch;
			}else{
				num ++;
			}
		}

	}
	return NULL;
}

PRIVATE bool wei_http_parse_reponse(IN char * buf,IN int buf_len,OUT struct  s_wei_http_response * http_response){
	char * level[2]; // split to http header and http body

	memset(http_response, 0 ,sizeof(struct s_wei_http_response));
	
	//分开header ＆ body
	if(!wei_util_split(buf,"\r\n\r\n", 2 ,level)){
		return false;
	}
	http_response->body = level[1];
	/*根据\r\n来判断头部的数目*/
	http_response->header_num = wei_util_get_str_num(level[0],"\r\n") + 1;
	if(http_response->header_num < 2)
		return false;
	http_response->header = (char **) malloc( sizeof(char *) * http_response->header_num );
	memset(http_response->header,0,sizeof(http_response->header));

        /*将头部分成各自独立的部分，其中http_response->header为指向指针的指针*/
	if(!wei_util_split(level[0],"\r\n",http_response->header_num,http_response->header)){
		free(http_response->header);
		return false;
	}
        int i;
	for(i = 0 ; i < http_response->header_num; i++){
		wei_util_str_trim(http_response->header[i]);
		wei_util_replace_all(http_response->header[i],"  "," ");
	}
	//分析消息头
	if(!wei_http_analyse_response_startline(http_response,http_response->header[0]))
		return false;

	switch(http_response->code){
	case 401:
	{       printf("entering case 401\n");
		int index = 0;
		char * value = NULL;
		while((value = wei_http_analyse_get_value(http_response,"WWW-Authenticate",index)) != NULL){
			if(wei_util_str_compare_trim(value,"NTLM",false)){
				http_response->is_suppoort_ntlm = true;
				break;
			}
			index ++;
		}
		
		http_response->Connection = "keep-alive";
		http_response->Authenticate = wei_http_analyse_get_value(http_response,"WWW-Authenticate",0);
		break;
	}
	default:
		break;
	}
	free(http_response->header);
	return true;
}
// End of PART 1 :HTTP util 工具集

/******************************** PART 2: proxy CONNECT 建立 *******************************/

/******************* PART 2.1 HTTP通信的通用函数 ********************/
PRIVATE static struct sockaddr_in httppc_proxyaddr;

/** 创建TCP的连接，返回socket*/
PRIVATE int wei_httppc_create_connect(){
	int sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
		return -1;
	if(connect(sock,(struct sockaddr *)& httppc_proxyaddr,sizeof(struct sockaddr_in)) != 0){
#ifdef WIN32
		closesocket(sock);
#else
		close(sock);
#endif
		return -2;
	}
	return sock;
}

/** 关闭TCP连接 */
PRIVATE void wei_httppc_close_connect(int * sock){
	if(* sock <= 0)
		return;
#ifdef WIN32
		closesocket(* sock);
#else
		close(* sock);
#endif
		* sock = -1;
		printf("--------- close connect ------------------\n");
}

//********* End of PART 2.1 HTTP通信的通用函数

/** 设置HTTP Proxy Client的相关参数*/
bool wei_set_proxy_info(IN char * the_proxy_ip,IN UINT the_proxy_port,IN char * the_host,
							   IN char * the_domain,IN char * the_user, IN char * the_passwd){
	if(the_proxy_ip == NULL && strlen(the_proxy_ip))
		return false;
	if(the_proxy_port <= 0 || the_proxy_port > 65535)
		return false;
	printf("proxy = %s " , the_proxy_ip);
	if(httppc_proxy_ip != NULL)
		free(httppc_proxy_ip);
	httppc_proxy_ip = (char *) malloc(strlen(the_proxy_ip) + 1);

 	char * p = wei_get_domain_ip(the_proxy_ip);
	if( p == NULL)
		return false;
	strcpy(httppc_proxy_ip,p);

	if(httppc_host != NULL)
		free(httppc_host);
	if(the_host == NULL){
		httppc_host = NULL;
	}else{
		httppc_host = (char *) malloc(strlen(the_host));
		strcpy(httppc_host,the_host);
	}

	if(httppc_domain != NULL)
		free(httppc_domain);
	if(the_domain == NULL){
		httppc_domain = NULL;
	}else{
		httppc_domain = (char *) malloc(strlen(the_domain));
		strcpy(httppc_domain,the_domain);
	}

	if(httppc_user != NULL)
		free(httppc_user);
	if(the_user == NULL){
		httppc_user = NULL;
	}else{
		httppc_user = (char *) malloc(strlen(the_user));
		strcpy(httppc_user,the_user);
	}

	if(httppc_passwd != NULL)
		free(httppc_passwd);
	if(the_passwd == NULL){
		httppc_passwd = NULL;
	}else{
		httppc_passwd = (char *) malloc(strlen(the_passwd));
		strcpy(httppc_passwd,the_passwd);
	}

	httppc_proxy_port = the_proxy_port;

	memset(&httppc_proxyaddr,0,sizeof(struct sockaddr_in));
	httppc_proxyaddr.sin_family=AF_INET;
	httppc_proxyaddr.sin_port=htons(httppc_proxy_port);
	httppc_proxyaddr.sin_addr.s_addr = inet_addr(httppc_proxy_ip);//只能用于x.x.x.x的格式

	printf("proxy = %s " , httppc_proxy_ip);
	return true;
}


/** 清除HTTP Proxy Client的相关参数*/
void wei_reset_proxy_info(){
	if(httppc_proxy_ip != NULL)
		free(httppc_proxy_ip);
	httppc_proxy_ip = NULL;

	if(httppc_host != NULL)
		free(httppc_host);
	httppc_host = NULL;

	if(httppc_domain != NULL)
		free(httppc_domain);
	httppc_domain = NULL;

	if(httppc_user != NULL)
		free(httppc_user);
	httppc_user = NULL;

	if(httppc_passwd != NULL)
		free(httppc_passwd);
	httppc_passwd = NULL;

	httppc_proxy_port = 0;
	memset(&httppc_proxyaddr,0,sizeof(struct sockaddr_in));
}


PUBLIC bool wei_is_httppc_connected(){
	return is_httppc_connected;
}

/** main：可以在main中初始化PROXY参数后，调用此连接。我们的例子使用了HTTP CONNECT的方式。*/
int wei_httppc_connect(char * remote_ip ,int remote_port){
	struct sockaddr_in servaddr;
	int result = 0,recv_len = 0;
	char packet_buff[4096];
	struct s_wei_http_response response;

	memset(packet_buff,0,4096);
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(httppc_proxy_port);
	servaddr.sin_addr.s_addr = inet_addr(httppc_proxy_ip);//只能用于x.x.x.x的格式

	if((httppc_sock = wei_httppc_create_connect()) <= 0)
		return httppc_sock;
        
	sprintf(packet_buff,"GET http://%s:%d HTTP/1.1 \r\n" 
	        "User-Agent: My Service Enpoint 1.0\r\n"
	        "Host: %s\r\n"
	        "Connection: Keep-Alive\r\n"
	        "Pragma: no-cache\r\n"
		    "Content-Length: 0\r\n"
	        "\r\n", remote_ip,remote_port,remote_ip);
	printf("发送:\n%s",packet_buff);
	if(send(httppc_sock,packet_buff,strlen(packet_buff),0) <= 0){
		wei_httppc_close_connect(&httppc_sock);
		return -3;
	}

	memset(packet_buff,0,4096);
	if((recv_len = recv(httppc_sock,packet_buff,4096,0)) <= 0){
		wei_httppc_close_connect(&httppc_sock);
		return -4;
	}
	
	printf("recv packet len = %d\n",recv_len);
	write(1,packet_buff,recv_len);

	if(!wei_http_parse_reponse(packet_buff,recv_len,&response)){
		wei_httppc_close_connect(&httppc_sock);
		return -1;
	}
	printf("first message is success!\n");
	switch(response.code){
	case 200:
		return httppc_sock;
	case 401:
		if(!response.is_suppoort_ntlm){
			wei_httppc_close_connect(&httppc_sock);
			return -1;
		}
		if(wei_util_str_compare_trim(response.Connection,"close",false)){
			printf("----------connect close------------\n");
			wei_httppc_close_connect(&httppc_sock);
			//创建信的连接
			if((httppc_sock = wei_httppc_create_connect()) <= 0)
				return httppc_sock;
		}
		//发送 type
		break;
	default:
		wei_httppc_close_connect(&httppc_sock);
		return 0;
	}
	
	// NTLM type1 flow:
	char buf[1024];
	memset(buf,0,1024);
        /*制作消息1*/
	wei_ntlm_make_type1_base64(true,httppc_domain,httppc_host,AUTHOR_NTLM_SESSION,buf);
	sprintf(packet_buff,"GET http://%s:%d HTTP/1.1 \r\n" 
	        "User-Agent: My Service Enpoint 1.0\r\n"
	        "Host: %s:%d\r\n"
	        "Connection: Keep-Alive\r\n"
	        "Pragma: no-cache\r\n"
			"Authorization: NTLM %s\r\n"
			"Content-Length: 0\r\n"
	        "\r\n", remote_ip,remote_port,remote_ip,remote_port,buf);
	printf("发送:\n%s",packet_buff);
	if(send(httppc_sock,packet_buff,strlen(packet_buff),0) <= 0){
		wei_httppc_close_connect(&httppc_sock);
		return -3;
	}

	memset(packet_buff,0,4096);
	if((recv_len = recv(httppc_sock,packet_buff,4096,0)) <= 0){
		wei_httppc_close_connect(&httppc_sock);
		return -4;
	}
	printf("recv packet len = %d\n%s",recv_len,packet_buff);
	if(!wei_http_parse_reponse(packet_buff,recv_len,&response)){
		wei_httppc_close_connect(&httppc_sock);
		return -1;
	}
        
	printf("response.www-auth:%s\n",response.Authenticate+5);
	printf("/****************Decode Message 2**********************/\n");
        //NTLM type2 flow
	T_NTLM_TYPE_2_MSG M_type2;
	if(!wei_ntlm_decode_type2(true,response.Authenticate+5, &M_type2)){
		printf("Analysis failed!\n");
	}else
	/*if(response.code > 299 || response.code < 200){
		printf("ERROR, Do not connect the remote entity, code %d",response.code);
		wei_httppc_close_connect(&httppc_sock);
		return -1;
	}*/
        printf("/***************Analysis Success************************/\n");
	printf("M_type2.protocal:%s\n",M_type2.protocol);
	printf("response.code = %d\n",response.code);
	printf("/******************Make type3 message*******************/\n");
	char buf_2[2048];
	memset(buf_2,0,2048);
	printf("/******************Making type3 message*****************/\n");
	if(!wei_ntlm_make_type3_base64(true,httppc_domain,httppc_host, httppc_user,
			                           httppc_passwd, &M_type2, buf_2)){
		printf("**********make type3 failed!********************\n");
		exit(0);
	}else
		printf("**********make type3 message success!************\n");

	sprintf(packet_buff,"GET http://%s:%d HTTP/1.1 \r\n" 
	        "User-Agent: My Service Enpoint 1.0\r\n"
	        "Host: %s:%d\r\n"
	        "Connection: Keep-Alive\r\n"
	        "Pragma: no-cache\r\n"
			"Authorization: NTLM %s\r\n"
			"Content-Length: 0\r\n"
	        "\r\n", remote_ip,remote_port,remote_ip,remote_port,buf_2);
	printf("发送:\n%s",packet_buff);
	if(send(httppc_sock,packet_buff,strlen(packet_buff),0) <= 0){
		wei_httppc_close_connect(&httppc_sock);
		return -3;
	}

	memset(packet_buff,0,4096);
	if((recv_len = recv(httppc_sock,packet_buff,4096,0)) <= 0){
		wei_httppc_close_connect(&httppc_sock);
		return -4;
	}
	printf("recv packet len = %d\n%s",recv_len,packet_buff);
	if(!wei_http_parse_reponse(packet_buff,recv_len,&response)){
		wei_httppc_close_connect(&httppc_sock);
		return -1;
	}
	printf("****************************************************\n");
        if(response.code==200){
		printf("Now we have success recieve OK http datagram!\n");
	}
	printf("****************************************************\n");
	return httppc_sock;
}
//**** End of PART 2: proxy CONNECT 建立

int main(int argc,char* argv[] ){
	if(argc!=5){
		printf("Useage:./[Program] proxy_ip proxy_port remote_ip remote_port\n");
		return 0;
	}

	char hostname[32];
	char domain[]="intra";
	char username[]="wangyukun";
	char passwd[]="kun123!@";
        int z;
	z=gethostname(hostname,sizeof(hostname));
	if(-1==z){
		fprintf(stderr,"%s:gethostname(2)\n",strerror(errno));
		exit(1);
	}
	printf("host name= '%s'\n",hostname);
	/*z=getdomainname(domain,sizeof(domain));
	if(-1==z){
		fprintf(stderr,"%s:getdomainname(2)\n",strerror(errno));
		exit(1);
	}*/
	printf("domain name= '%s'\n",domain);

	if(!wei_set_proxy_info(argv[1],atoi(argv[2]),NULL,NULL,username,passwd)){
		printf("Log_Message:wei_set_proxy_info failed!\n");
		return 0;
	}
        
	wei_httppc_connect(argv[3],atoi(argv[4]));
	return 0;
}
