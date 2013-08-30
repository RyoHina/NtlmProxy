/****************************************************************************************਍ ⨀ Ⰰ遧Ŏ⡸蹵䡎吀吀倀 倀刀伀堀夀萀乶吀䰀䴀需핻⵬葎ꭶﶎ湎ꑸ㪋㙧䁒襢쩭葓ꅶ鞋ɻ丰吀䰀䴀퐀൫上Digest算法的 *਍ ⨀ 褀桛❑ౠ䛿⽏⡦偗刀伀堀夀℀豨⶚콎㡾끞へ౒诿艏㕙ᑏ癸扺蒖䥶匀䄀 倀刀伀堀夀Ȁ‰                      ⨀ഀ
 *                                                                                      *਍ ⨀ 숀͓䒀馍ᩥ棿琀琀瀀挀ⴀ　⸀㠀⸀㘀 쩎⁓栀琀琀瀀㨀⼀⼀眀眀眀⸀椀渀渀漀瘀愀琀椀漀渀⸀挀栀⼀樀愀瘀愀⼀渀琀氀洀⸀栀琀洀氀                   ⨀ഀ
 *           http://blog.chinaunix.net/u/31179/showart_464972.html                      *਍ ⨀                                                                                      ⨀ഀ
 * NTML v1:                                                                             *਍ ⨀ 䌀 㴀 㠀ⴀ戀礀琀攀 猀攀爀瘀攀爀 挀栀愀氀氀攀渀最攀Ⰰ 爀愀渀搀漀洀                                                  ⨀ഀ
 * K1 | K2 | K3 = NT-Hash | 5-bytes-0                                                   *਍ ⨀ 刀㄀ 㴀 䐀䔀匀⠀䬀㄀Ⰰ䌀⤀ 簀 䐀䔀匀⠀䬀㈀Ⰰ䌀⤀ 簀 䐀䔀匀⠀䬀㌀Ⰰ䌀⤀                                               ⨀ഀ
 * K1 | K2 | K3 = LM-Hash | 5-bytes-0                                                   *਍ ⨀ 刀㈀ 㴀 䐀䔀匀⠀䬀㄀Ⰰ䌀⤀ 簀 䐀䔀匀⠀䬀㈀Ⰰ䌀⤀ 簀 䐀䔀匀⠀䬀㌀Ⰰ䌀⤀                                               ⨀ഀ
 * response = R1 | R2                                                                   *਍ ⨀                                                                                      ⨀ഀ
਍ ⨀ ᘀ饿ὥᩧ㋿　　㠀琀ㅞ㈀ࠀ⁧                                                                ⨀ഀ
 ****************************************************************************************/਍ഀ
#include "app/MyUtil.h"਍⌀搀攀昀椀渀攀 䰀伀䜀 䌀䴀礀唀琀椀氀㨀㨀猀栀漀眀䰀漀最ഀ
਍⌀椀昀搀攀昀 圀䤀一㌀㈀ഀ
//#include <winsock2.h>਍⌀攀渀搀椀昀ഀ
#ifdef LINUX਍⌀椀渀挀氀甀搀攀 㰀渀攀琀椀渀攀琀⼀椀渀⸀栀㸀ഀ
#endif਍⌀椀渀挀氀甀搀攀 ∀栀琀琀瀀瀀挀开渀琀氀洀⸀栀∀ഀ
਍⌀椀渀挀氀甀搀攀 ∀愀爀椀琀栀洀攀琀椀挀⸀栀∀ഀ
਍⼀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀ 瀀愀爀琀㄀㨀 一吀䰀䴀 需핻⁬⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⨀⼀ഀ
/*਍猀琀愀琀椀挀 瘀漀椀搀 琀攀洀瀀倀爀椀渀琀䰀攀渀⠀甀渀猀椀最渀攀搀 挀栀愀爀 ⨀ 戀甀昀Ⰰ椀渀琀 氀攀渀 ⤀笀ഀ
	LOG(LOG_DEBUG,"========二进制输出 长度：%d",len);਍ऀ椀渀琀 氀椀渀攀 㴀 氀攀渀⼀㠀㬀ഀ
	if(line * 8 != len)਍ऀऀ氀椀渀攀 ⬀⬀㬀ഀ
	for(int i = 0 ; i <line ; i ++){਍ऀऀ䰀伀䜀⠀䰀伀䜀开䐀䔀䈀唀䜀Ⰰ∀─搀   ─　㈀砀 ─　㈀砀 ─　㈀砀 ─　㈀砀 ─　㈀砀 ─　㈀砀 ─　㈀砀 ─　㈀砀∀Ⰰ椀⨀㠀Ⰰഀ
			(unsigned char)buf[8*i],(unsigned char)buf[8*i+1],(unsigned char)buf[8*i+2],਍ऀऀऀ⠀甀渀猀椀最渀攀搀 挀栀愀爀⤀戀甀昀嬀㠀⨀椀⬀㌀崀Ⰰ⠀甀渀猀椀最渀攀搀 挀栀愀爀⤀戀甀昀嬀㠀⨀椀⬀㐀崀Ⰰ⠀甀渀猀椀最渀攀搀 挀栀愀爀⤀戀甀昀嬀㠀⨀椀⬀㔀崀Ⰰഀ
			(unsigned char)buf[8*i+6],(unsigned char)buf[8*i+7]);਍ऀ紀ഀ
}਍⨀⼀ഀ
PRIVATE void wei_ntlm_make_type1(IN bool is_little_endian,IN char * domain,IN char * name,਍ऀऀऀऀऀऀऀऀ 䤀一 椀渀琀 愀甀琀栀漀爀开琀礀瀀攀Ⰰ伀唀吀 吀开一吀䰀䴀开吀夀倀䔀开㄀开䴀匀䜀 ⨀ 椀渀昀漀⤀笀ഀ
	short int domain_len = 0,name_len = 0;਍ऀ甀渀猀椀最渀攀搀 椀渀琀 昀氀愀最猀㬀ഀ
਍ऀ椀昀⠀搀漀洀愀椀渀 ℀㴀 一唀䰀䰀⤀ഀ
		domain_len = strlen(domain);਍ऀ椀昀⠀渀愀洀攀 ℀㴀 一唀䰀䰀⤀ഀ
		name_len = strlen(name);਍ഀ
	if(info == NULL)਍ऀऀ爀攀琀甀爀渀㬀ഀ
	memset(info,0,sizeof(T_NTLM_TYPE_1_MSG));਍ऀ猀琀爀挀瀀礀⠀椀渀昀漀ⴀ㸀瀀爀漀琀漀挀漀氀Ⰰ∀一吀䰀䴀匀匀倀∀⤀㬀ഀ
	info->type = is_little_endian ? 0x01 : htonl(0x01);਍ऀ猀眀椀琀挀栀⠀愀甀琀栀漀爀开琀礀瀀攀⤀笀ഀ
	case AUTHOR_NTLM_2:਍ऀऀ昀氀愀最猀 㴀 　砀　㈀㠀　戀㈀　㔀㬀ഀ
		break;਍ऀ挀愀猀攀 䄀唀吀䠀伀刀开一吀䰀䴀开匀䔀匀匀䤀伀一㨀ഀ
		flags = 0x0288b201;਍ऀऀ戀爀攀愀欀㬀ഀ
	case AUTHOR_NTLM_1:਍ऀ搀攀昀愀甀氀琀㨀ഀ
		flags = 0xb201;਍ऀऀ戀爀攀愀欀㬀ഀ
	}਍ഀ
	if(domain_len == 0)਍ऀऀ昀氀愀最猀 ⴀ㴀 　砀㄀　　　㬀ഀ
	if(name_len == 0)਍ऀऀ昀氀愀最猀 ⴀ㴀 　砀㈀　　　㬀ഀ
	info->flags = is_little_endian ? flags : htonl(flags);਍ഀ
	//info->flags = is_little_endian ? 0xa208b207 : htonl(0xa208b207);਍ऀ椀渀昀漀ⴀ㸀搀漀洀开氀攀渀㄀  㴀 椀猀开氀椀琀琀氀攀开攀渀搀椀愀渀 㼀 搀漀洀愀椀渀开氀攀渀 㨀 栀琀漀渀氀⠀搀漀洀愀椀渀开氀攀渀⤀㬀ഀ
	info->dom_len2  = info->dom_len1;਍ऀ椀渀昀漀ⴀ㸀搀漀洀开漀昀昀   㴀 椀猀开氀椀琀琀氀攀开攀渀搀椀愀渀 㼀 　砀㈀　 ⬀ 渀愀洀攀开氀攀渀 㨀 栀琀漀渀氀⠀⠀猀栀漀爀琀⤀⠀　砀㈀　 ⬀ 渀愀洀攀开氀攀渀⤀⤀㬀ഀ
	info->host_len1 = is_little_endian ? name_len : htons(name_len);਍ऀ椀渀昀漀ⴀ㸀栀漀猀琀开氀攀渀㈀ 㴀 椀渀昀漀ⴀ㸀栀漀猀琀开氀攀渀㄀㬀ഀ
	info->host_off  = is_little_endian ? 0x20 : htonl(0x20);਍ऀ椀渀昀漀ⴀ㸀搀漀洀 㴀 搀漀洀愀椀渀㬀ഀ
	info->host = name;਍紀ഀ
/*਍甀渀猀椀最渀攀搀 挀栀愀爀 琀愀爀最攀琀嬀崀 㴀 笀　砀　㈀Ⰰ　砀　　Ⰰ　砀　挀Ⰰ　砀　　Ⰰ　砀㐀㐀Ⰰ　砀　　Ⰰ　砀㐀昀Ⰰ　砀　　Ⰰഀ
  0x4d,0x00,0x41,0x00,0x49,0x00,0x4e,0x00,਍  　砀　㄀Ⰰ　砀　　Ⰰ　砀　挀Ⰰ　砀　　Ⰰ　砀㔀㌀Ⰰ　砀　　Ⰰ　砀㐀㔀Ⰰ　砀　　Ⰰഀ
  0x52,0x00,0x56,0x00,0x45,0x00,0x52,0x00,਍  　砀　㐀Ⰰ　砀　　Ⰰ　砀㄀㐀Ⰰ　砀　　Ⰰ　砀㘀㐀Ⰰ　砀　　Ⰰ　砀㘀昀Ⰰ　砀　　Ⰰഀ
  0x6d,0x00,0x61,0x00,0x69,0x00,0x6e,0x00,਍  　砀㈀攀Ⰰ　砀　　Ⰰ　砀㘀㌀Ⰰ　砀　　Ⰰ　砀㘀昀Ⰰ　砀　　Ⰰ　砀㘀搀Ⰰ　砀　　Ⰰഀ
  0x03,0x00,0x22,0x00,0x73,0x00,0x65,0x00,਍  　砀㜀㈀Ⰰ　砀　　Ⰰ　砀㜀㘀Ⰰ　砀　　Ⰰ　砀㘀㔀Ⰰ　砀　　Ⰰ　砀㜀㈀Ⰰ　砀　　Ⰰഀ
  0x2e,0x00,0x64,0x00,0x6f,0x00,0x6d,0x00,਍  　砀㘀㄀Ⰰ　砀　　Ⰰ　砀㘀㤀Ⰰ　砀　　Ⰰ　砀㘀攀Ⰰ　砀　　Ⰰ　砀㈀攀Ⰰ　砀　　Ⰰഀ
  0x63,0x00,0x6f,0x00,0x6d,0x00,0x00,0x00,਍  　砀　　Ⰰ　砀　　紀㬀ഀ
unsigned char client_nounce[] = {਍ऀ　砀昀昀Ⰰ　砀昀昀Ⰰ　砀昀昀Ⰰ　砀　　Ⰰ　砀㄀㄀Ⰰ　砀㈀㈀Ⰰ　砀㌀㌀Ⰰ　砀㐀㐀ഀ
};਍⨀⼀ഀ
void wei_ntlm_make_type1_base64(IN bool is_little_endian,IN char * domain,IN char * host_name,਍ऀऀऀऀऀऀऀऀ䤀一 椀渀琀 愀甀琀栀漀爀开琀礀瀀攀Ⰰ伀唀吀 挀栀愀爀 ⨀ 戀甀昀⤀笀ഀ
	int ntlm_len = 0,domain_len = 0 ,host_name_len = 0;਍ऀ挀栀愀爀 ⨀ 渀琀氀洀开戀甀昀昀 㴀 一唀䰀䰀㬀ഀ
	T_NTLM_TYPE_1_MSG info;਍ഀ
	if(domain != NULL)਍ऀऀ 搀漀洀愀椀渀开氀攀渀 㴀 猀琀爀氀攀渀⠀搀漀洀愀椀渀⤀㬀ഀ
	if(host_name != NULL)਍ऀऀ栀漀猀琀开渀愀洀攀开氀攀渀 㴀 猀琀爀氀攀渀⠀栀漀猀琀开渀愀洀攀⤀㬀ഀ
਍ऀ眀攀椀开渀琀氀洀开洀愀欀攀开琀礀瀀攀㄀⠀椀猀开氀椀琀琀氀攀开攀渀搀椀愀渀Ⰰ搀漀洀愀椀渀Ⰰ栀漀猀琀开渀愀洀攀Ⰰ愀甀琀栀漀爀开琀礀瀀攀Ⰰ☀椀渀昀漀⤀㬀ഀ
਍ऀ渀琀氀洀开氀攀渀 㴀 ㌀㈀ ⬀ 搀漀洀愀椀渀开氀攀渀 ⬀ 栀漀猀琀开渀愀洀攀开氀攀渀㬀ഀ
	ntlm_buff = (char *) malloc(ntlm_len + 4);਍ऀ洀攀洀猀攀琀⠀渀琀氀洀开戀甀昀昀Ⰰ　Ⰰ猀椀稀攀漀昀⠀渀琀氀洀开戀甀昀昀⤀⤀㬀ഀ
	memcpy(ntlm_buff,&info,32);਍ऀഀ
	if(host_name_len != 0)਍ऀऀ洀攀洀挀瀀礀⠀渀琀氀洀开戀甀昀昀 ⬀ ㌀㈀Ⰰ椀渀昀漀⸀栀漀猀琀Ⰰ栀漀猀琀开渀愀洀攀开氀攀渀⤀㬀ഀ
਍ऀ椀昀⠀搀漀洀愀椀渀开氀攀渀 ℀㴀 　⤀ഀ
		memcpy(ntlm_buff + 32 + host_name_len,info.dom,domain_len);਍ഀ
	encode_base64(buf,ntlm_buff,ntlm_len);਍ऀ⼀⼀豈罛ꚕ�䲏҈ٙ൴
	free(ntlm_buff);਍ऀ⼀⨀ഀ
	//void lm_hash(IN char * src, OUT char * dst, OUT int * len);਍ऀ甀渀猀椀最渀攀搀 挀栀愀爀 搀猀琀嬀㄀㘀崀Ⰰ爀攀猀瀀漀渀猀攀嬀㐀㠀崀Ⰰ挀栀愀氀氀攀渀最攀嬀㠀崀Ⰰ爀渀嬀㈀㔀㘀崀Ⰰ氀洀嬀㈀㔀㘀崀㬀ഀ
	int rn_len,lm_len;਍ऀ⼀⼀氀洀开栀愀猀栀⠀∀䈀攀攀戀氀攀戀∀Ⰰ⠀挀栀愀爀 ⨀⤀ 欀攀礀Ⰰ一唀䰀䰀⤀㬀ഀ
	lm_hash("Beeblebrox",dst,NULL);਍ऀ琀攀洀瀀倀爀椀渀琀䰀攀渀⠀搀猀琀Ⰰ㄀㘀⤀㬀ഀ
	nt_hash("Beeblebrox",0,dst,NULL);਍ऀ琀攀洀瀀倀爀椀渀琀䰀攀渀⠀搀猀琀Ⰰ㄀㘀⤀㬀ഀ
	//"Beeblebrox"਍ऀ挀栀愀氀氀攀渀最攀嬀　崀 㴀 　砀　㄀㬀ഀ
	challenge[1] = 0x23;਍ऀ挀栀愀氀氀攀渀最攀嬀㈀崀 㴀 　砀㐀㔀㬀ഀ
	challenge[3] = 0x67;਍ऀ挀栀愀氀氀攀渀最攀嬀㐀崀 㴀 　砀㠀㤀㬀ഀ
	challenge[5] = 0xab;਍ऀ挀栀愀氀氀攀渀最攀嬀㘀崀 㴀 　砀挀搀㬀ഀ
	challenge[7] = 0xef;਍ऀ渀琀氀洀瘀㄀开爀攀猀瀀漀渀猀攀⠀∀匀攀挀刀䔀琀　㄀∀Ⰰ 挀栀愀氀氀攀渀最攀Ⰰ 爀攀猀瀀漀渀猀攀Ⰰ一唀䰀䰀⤀㬀ഀ
	tempPrintLen(response,48);਍ऀ渀琀氀洀瘀㈀开爀攀猀瀀漀渀猀攀⠀∀匀攀挀刀䔀琀　㄀∀Ⰰ ∀甀猀攀爀∀Ⰰ∀䐀伀䴀䄀䤀一∀Ⰰ挀栀愀氀氀攀渀最攀Ⰰ 琀愀爀最攀琀Ⰰ㤀㠀Ⰰ挀氀椀攀渀琀开渀漀甀渀挀攀Ⰰഀ
					rn,&rn_len,lm,&lm_len);਍ऀ琀攀洀瀀倀爀椀渀琀䰀攀渀⠀爀渀Ⰰ爀渀开氀攀渀⤀㬀ഀ
	tempPrintLen(lm,lm_len);਍ഀ
	ntlmv2_session_response("SecREt01",challenge,client_nounce,਍                             爀渀Ⰰ☀爀渀开氀攀渀Ⰰ氀洀Ⰰ☀氀洀开氀攀渀⤀㬀ഀ
	tempPrintLen(rn,rn_len);਍ऀ琀攀洀瀀倀爀椀渀琀䰀攀渀⠀氀洀Ⰰ氀洀开氀攀渀⤀㬀⨀⼀ഀ
}਍ഀ
/** 获取type2的结构，并进行校验*/਍戀漀漀氀 眀攀椀开渀琀氀洀开搀攀挀漀搀攀开琀礀瀀攀㈀⠀䤀一 戀漀漀氀 椀猀开氀椀琀琀氀攀开攀渀搀椀愀渀Ⰰ䤀一 挀栀愀爀 ⨀ 椀渀昀漀Ⰰ 伀唀吀 吀开一吀䰀䴀开吀夀倀䔀开㈀开䴀匀䜀 ⨀ 琀礀瀀攀㈀⤀笀ഀ
	unsigned char buf[256];਍ऀ椀渀琀 琀礀瀀攀开氀攀渀㬀ഀ
	memset(buf,0,128);਍ഀ
	decode_base64(info,strlen(info),(char *)buf,&type_len);਍ऀ洀攀洀挀瀀礀⠀琀礀瀀攀㈀Ⰰ戀甀昀Ⰰ㐀㠀⤀㬀ഀ
਍ऀ⼀⼀豈࡛핔❬�䲏삈൧
	//检查0－8字节：਍ऀ椀昀⠀猀琀爀挀洀瀀⠀琀礀瀀攀㈀ⴀ㸀瀀爀漀琀漀挀漀氀Ⰰ∀一吀䰀䴀匀匀倀∀⤀ ℀㴀 　⤀ഀ
		return false;਍ऀ椀昀⠀℀椀猀开氀椀琀琀氀攀开攀渀搀椀愀渀⤀笀ഀ
		type2->target_name_len = htons(type2->target_name_len);਍ऀऀ琀礀瀀攀㈀ⴀ㸀琀愀爀最攀琀开渀愀洀攀开愀氀氀漀挀愀琀椀漀渀 㴀 栀琀漀渀猀⠀琀礀瀀攀㈀ⴀ㸀琀愀爀最攀琀开渀愀洀攀开愀氀氀漀挀愀琀椀漀渀⤀㬀ഀ
		type2->target_name_offset = htonl(type2->target_name_offset);਍ऀऀ琀礀瀀攀㈀ⴀ㸀昀氀愀最猀 㴀 栀琀漀渀氀⠀琀礀瀀攀㈀ⴀ㸀昀氀愀最猀⤀㬀ഀ
		type2->target_info_len = htons(type2->target_info_len);਍ऀऀ琀礀瀀攀㈀ⴀ㸀琀愀爀最攀琀开椀渀昀漀开愀氀氀漀挀琀椀漀渀 㴀 栀琀漀渀猀⠀琀礀瀀攀㈀ⴀ㸀琀愀爀最攀琀开椀渀昀漀开愀氀氀漀挀琀椀漀渀⤀㬀ഀ
		type2->target_info_offset = htons(type2->target_info_offset);਍ऀ紀ഀ
	਍ऀ椀昀⠀⠀琀礀瀀攀㈀ⴀ㸀琀愀爀最攀琀开椀渀昀漀开漀昀昀猀攀琀 ⬀ 琀礀瀀攀㈀ⴀ㸀琀愀爀最攀琀开椀渀昀漀开氀攀渀 㸀 琀礀瀀攀开氀攀渀⤀ 簀簀ഀ
		(type2->target_name_offset + type2->target_name_len > type_len))਍ऀऀ爀攀琀甀爀渀 昀愀氀猀攀㬀ഀ
਍⼀⨀ഀ
	if(type2->target_info_len != 0 && type2->target_info_offset > 0)਍ऀऀ琀礀瀀攀㈀ⴀ㸀琀愀爀最攀琀开椀渀昀漀 㴀 戀甀昀 ⬀ 琀礀瀀攀㈀ⴀ㸀琀愀爀最攀琀开椀渀昀漀开漀昀昀猀攀琀㬀ഀ
	else਍ऀऀ琀礀瀀攀㈀ⴀ㸀琀愀爀最攀琀开椀渀昀漀 㴀 一唀䰀䰀㬀⨀⼀ഀ
	if(type2->target_info_len != 0 && type2->target_info_offset > 0){਍ऀऀ琀礀瀀攀㈀ⴀ㸀琀愀爀最攀琀开椀渀昀漀 㴀 ⠀甀渀猀椀最渀攀搀 挀栀愀爀 ⨀⤀洀愀氀氀漀挀⠀琀礀瀀攀㈀ⴀ㸀琀愀爀最攀琀开椀渀昀漀开氀攀渀⤀㬀ഀ
		memcpy(type2->target_info,buf + type2->target_info_offset,type2->target_info_len);਍ऀ紀攀氀猀攀ഀ
		type2->target_info = NULL;਍ഀ
਍ऀ椀昀⠀琀礀瀀攀㈀ⴀ㸀琀愀爀最攀琀开渀愀洀攀开氀攀渀 ℀㴀 　 ☀☀ 琀礀瀀攀㈀ⴀ㸀琀愀爀最攀琀开渀愀洀攀开漀昀昀猀攀琀 㸀 　⤀ഀ
		type2->target_name = buf + type2->target_name_offset;਍ऀ攀氀猀攀ഀ
		type2->target_name = NULL;਍ऀഀ
	return true;਍紀ഀ
਍ഀ
਍倀刀䤀嘀䄀吀䔀 瘀漀椀搀 挀爀攀愀琀攀开渀漀渀挀攀⠀伀唀吀 甀渀猀椀最渀攀搀 挀栀愀爀 ⨀ 渀漀渀挀攀⤀笀ഀ
#ifdef _LINUX਍ऀ猀爀愀渀搀漀洀⠀琀椀洀攀⠀　⤀⤀㬀ഀ
#else਍ऀ猀爀愀渀搀⠀琀椀洀攀⠀　⤀⤀㬀ഀ
#endif਍ऀ昀漀爀⠀椀渀琀 椀 㴀 　 㬀 椀㰀 㠀 㬀 椀 ⬀⬀⤀笀ഀ
		nonce[i] = rand() * 1.0 /RAND_MAX * 256;਍ऀ紀ഀ
}਍ഀ
bool wei_ntlm_make_type3_base64(IN bool is_little_endian,IN char * domain ,IN char * host, IN char * user, ਍ऀऀऀऀऀऀऀऀ䤀一 挀栀愀爀 ⨀ 瀀愀猀猀眀搀Ⰰ 䤀一 吀开一吀䰀䴀开吀夀倀䔀开㈀开䴀匀䜀 ⨀ 琀礀瀀攀㈀开洀猀最Ⰰ伀唀吀 挀栀愀爀 ⨀ 戀甀昀⤀笀ഀ
	T_NTLM_TYPE_3_MSG msg;਍ऀ甀渀猀椀最渀攀搀 挀栀愀爀 挀氀椀攀渀琀开渀漀渀挀攀嬀㠀崀Ⰰ氀洀开爀攀猀瀀漀渀猀攀嬀㈀㔀㘀崀Ⰰ渀琀氀洀开爀攀猀瀀漀渀猀攀嬀㔀㄀㈀崀㬀ഀ
	int author_type = AUTHOR_NTLM_1,lm_len = 0,ntlm_len = 0,offset = 0,len = 0;਍ऀ甀渀猀椀最渀攀搀 椀渀琀 昀氀愀最猀 㴀 　㬀ഀ
	char * pure_response;਍ഀ
	if((type2_msg->flags & 0x800000) != 0){਍ऀऀ愀甀琀栀漀爀开琀礀瀀攀 㴀 䄀唀吀䠀伀刀开一吀䰀䴀开㈀㬀ഀ
		if((type2_msg->flags & 0x80000) != 0)਍ऀऀऀ愀甀琀栀漀爀开琀礀瀀攀 㴀 䄀唀吀䠀伀刀开一吀䰀䴀开匀䔀匀匀䤀伀一㬀ഀ
	}਍ഀ
	memset(&msg,0,sizeof(T_NTLM_TYPE_3_MSG));਍ऀ猀琀爀挀瀀礀⠀⠀挀栀愀爀 ⨀⤀洀猀最⸀瀀爀漀琀漀挀漀氀Ⰰ∀一吀䰀䴀匀匀倀∀⤀㬀ഀ
	msg.type = is_little_endian ? 0x03 : htonl(0x03);਍ഀ
	switch(author_type){਍ऀ挀愀猀攀 䄀唀吀䠀伀刀开一吀䰀䴀开㈀㨀ഀ
		LOG(LOG_DEBUG,"TYPE NTLM V2");਍ऀऀ挀爀攀愀琀攀开渀漀渀挀攀⠀挀氀椀攀渀琀开渀漀渀挀攀⤀㬀ഀ
		//tempPrintLen(client_nonce,8);਍ऀऀ⼀⼀琀攀洀瀀倀爀椀渀琀䰀攀渀⠀琀礀瀀攀㈀开洀猀最ⴀ㸀琀愀爀最攀琀开椀渀昀漀Ⰰ琀礀瀀攀㈀开洀猀最ⴀ㸀琀愀爀最攀琀开椀渀昀漀开氀攀渀⤀㬀ഀ
		ntlmv2_response(passwd,user,domain,type2_msg->nonce,type2_msg->target_info,਍ऀऀ                琀礀瀀攀㈀开洀猀最ⴀ㸀琀愀爀最攀琀开椀渀昀漀开氀攀渀Ⰰ挀氀椀攀渀琀开渀漀渀挀攀Ⰰഀ
		                ntlm_response,&ntlm_len,lm_response, &lm_len);਍ऀऀ昀氀愀最猀 㴀 　砀　㈀㠀　戀㈀　㔀㬀ഀ
		break;਍ऀ挀愀猀攀 䄀唀吀䠀伀刀开一吀䰀䴀开匀䔀匀匀䤀伀一㨀ഀ
		LOG(LOG_DEBUG,"TYPE NTLM Session V2");਍ऀऀ挀爀攀愀琀攀开渀漀渀挀攀⠀挀氀椀攀渀琀开渀漀渀挀攀⤀㬀ഀ
		ntlmv2_session_response(passwd, type2_msg->nonce,client_nonce,਍ऀऀ                        渀琀氀洀开爀攀猀瀀漀渀猀攀Ⰰ☀渀琀氀洀开氀攀渀Ⰰ氀洀开爀攀猀瀀漀渀猀攀Ⰰ ☀氀洀开氀攀渀⤀㬀ഀ
		flags = 0x0288b201;਍ऀऀ戀爀攀愀欀㬀ഀ
	case AUTHOR_NTLM_1:਍ऀ搀攀昀愀甀氀琀㨀ഀ
		ntlmv1_response(passwd,type2_msg->nonce,ntlm_response,&ntlm_len,lm_response, ਍ऀऀ                ☀氀洀开氀攀渀⤀㬀ഀ
		flags = 0xb201;਍ऀऀ戀爀攀愀欀㬀ഀ
	}਍ഀ
	//domain਍ऀ漀昀昀猀攀琀 㴀 㘀㐀㬀ഀ
	if(domain != NULL && strlen(domain) != 0){਍ऀऀ氀攀渀 㴀 猀琀爀氀攀渀⠀搀漀洀愀椀渀⤀ ⨀㈀㬀ഀ
		msg.domain_len = is_little_endian ? len : htons(len);਍ऀऀ洀猀最⸀搀漀洀愀椀渀开愀氀氀漀挀愀琀椀漀渀 㴀 洀猀最⸀搀漀洀愀椀渀开氀攀渀㬀ഀ
		msg.domain_offset = is_little_endian ? offset : htonl(offset);਍ऀऀ漀昀昀猀攀琀 ⬀㴀 氀攀渀㬀ഀ
		msg.domain = (char *) malloc(len);਍ऀऀ甀渀椀挀漀搀攀⠀搀漀洀愀椀渀Ⰰ猀琀爀氀攀渀⠀搀漀洀愀椀渀⤀Ⰰ洀猀最⸀搀漀洀愀椀渀Ⰰ一唀䰀䰀⤀㬀ഀ
	}else{਍ऀऀ洀猀最⸀搀漀洀愀椀渀开漀昀昀猀攀琀 㴀 椀猀开氀椀琀琀氀攀开攀渀搀椀愀渀 㼀 漀昀昀猀攀琀 㨀 栀琀漀渀氀⠀漀昀昀猀攀琀⤀㬀ഀ
		flags -= 0x1000;਍ऀ紀ഀ
਍ऀ⼀⼀甀猀攀爀ഀ
	if(user != NULL && strlen(user) != 0){਍ऀऀ氀攀渀 㴀 猀琀爀氀攀渀⠀甀猀攀爀⤀ ⨀ ㈀㬀ഀ
		msg.user_len = is_little_endian ? len : htons(len);਍ऀऀ洀猀最⸀甀猀攀爀开愀氀氀漀挀愀琀椀漀渀 㴀 洀猀最⸀甀猀攀爀开氀攀渀㬀ഀ
		msg.user_offset = is_little_endian ? offset : htonl(offset);਍ऀऀ漀昀昀猀攀琀 ⬀㴀 氀攀渀㬀ഀ
		msg.user = (char *) malloc(len);਍ऀऀ甀渀椀挀漀搀攀⠀甀猀攀爀Ⰰ猀琀爀氀攀渀⠀甀猀攀爀⤀Ⰰ洀猀最⸀甀猀攀爀Ⰰ一唀䰀䰀⤀㬀ഀ
	}else{਍ऀऀ洀猀最⸀甀猀攀爀开漀昀昀猀攀琀 㴀 椀猀开氀椀琀琀氀攀开攀渀搀椀愀渀 㼀 漀昀昀猀攀琀 㨀 栀琀漀渀氀⠀漀昀昀猀攀琀⤀㬀ഀ
	}਍ഀ
	//host਍ऀ椀昀⠀栀漀猀琀 ℀㴀 一唀䰀䰀 ☀☀ 猀琀爀氀攀渀⠀栀漀猀琀⤀ ℀㴀 　⤀笀ഀ
		len = strlen(host) * 2;਍ऀऀ洀猀最⸀栀漀猀琀开氀攀渀 㴀 椀猀开氀椀琀琀氀攀开攀渀搀椀愀渀 㼀 氀攀渀 㨀 栀琀漀渀猀⠀氀攀渀⤀㬀ഀ
		msg.host_allocation = msg.host_len;਍ऀऀ洀猀最⸀栀漀猀琀开漀昀昀猀攀琀 㴀 椀猀开氀椀琀琀氀攀开攀渀搀椀愀渀 㼀 漀昀昀猀攀琀 㨀 栀琀漀渀氀⠀漀昀昀猀攀琀⤀㬀ഀ
		offset += len;਍ऀऀ洀猀最⸀栀漀猀琀 㴀 ⠀挀栀愀爀 ⨀ ⤀ 洀愀氀氀漀挀⠀氀攀渀⤀㬀ഀ
		unicode(host,strlen(host),msg.host,NULL);਍ऀ紀攀氀猀攀笀ഀ
		msg.host_offset = is_little_endian ? offset : htonl(offset);਍ऀऀ昀氀愀最猀 ⴀ㴀 　砀㈀　　　㬀ഀ
	}਍ऀഀ
	//lm_response਍ऀ洀猀最⸀氀洀开爀攀猀瀀开氀攀渀 㴀 椀猀开氀椀琀琀氀攀开攀渀搀椀愀渀 㼀 氀洀开氀攀渀 㨀 栀琀漀渀猀⠀氀洀开氀攀渀⤀㬀ഀ
	msg.lm_resp_allocation = msg.lm_resp_len;਍ऀ洀猀最⸀氀洀开爀攀猀瀀开漀昀昀猀攀琀 㴀 椀猀开氀椀琀琀氀攀开攀渀搀椀愀渀 㼀 漀昀昀猀攀琀 㨀 栀琀漀渀氀⠀漀昀昀猀攀琀⤀㬀ഀ
	offset += lm_len;਍ऀ洀猀最⸀氀洀开爀攀猀瀀 㴀 氀洀开爀攀猀瀀漀渀猀攀㬀ഀ
਍ऀ⼀⼀渀琀氀洀开爀攀猀瀀漀渀猀攀ഀ
	msg.nt_resp_len = is_little_endian ? ntlm_len : htons(ntlm_len);਍ऀ洀猀最⸀渀琀开爀攀猀瀀开愀氀氀漀挀愀琀椀漀渀 㴀 洀猀最⸀渀琀开爀攀猀瀀开氀攀渀㬀ഀ
	msg.nt_resp_offset = is_little_endian ? offset : htonl(offset);਍ऀ漀昀昀猀攀琀 ⬀㴀 渀琀氀洀开氀攀渀㬀ഀ
	msg.nt_resp = ntlm_response;਍ഀ
	//others਍ऀ洀猀最⸀昀氀愀最猀 㴀 椀猀开氀椀琀琀氀攀开攀渀搀椀愀渀 㼀 昀氀愀最猀 㨀 栀琀漀渀氀⠀昀氀愀最猀⤀㬀ഀ
	msg.msg_len = is_little_endian ? offset : htonl(offset);਍ऀ氀攀渀 㴀 漀昀昀猀攀琀㬀ഀ
਍ഀ
	pure_response = (char *) malloc(len);਍ऀ洀攀洀挀瀀礀⠀瀀甀爀攀开爀攀猀瀀漀渀猀攀Ⰰ☀洀猀最Ⰰ㘀㐀⤀㬀ഀ
	offset = 64;਍ऀ椀昀⠀洀猀最⸀搀漀洀愀椀渀 ℀㴀 一唀䰀䰀⤀笀ഀ
		memcpy(pure_response + offset , msg.domain, strlen(domain) *2);਍ऀऀ漀昀昀猀攀琀 ⬀㴀 猀琀爀氀攀渀⠀搀漀洀愀椀渀⤀ ⨀㈀㬀ഀ
	}਍ऀ椀昀⠀洀猀最⸀甀猀攀爀 ℀㴀 一唀䰀䰀⤀笀ഀ
		memcpy(pure_response + offset , msg.user, strlen(user) *2);਍ऀऀ漀昀昀猀攀琀 ⬀㴀 猀琀爀氀攀渀⠀甀猀攀爀⤀ ⨀㈀㬀ഀ
	}਍ऀ椀昀⠀洀猀最⸀栀漀猀琀 ℀㴀 一唀䰀䰀⤀笀ഀ
		memcpy(pure_response + offset , msg.host, strlen(host) *2);਍ऀऀ漀昀昀猀攀琀 ⬀㴀 猀琀爀氀攀渀⠀栀漀猀琀⤀ ⨀㈀㬀ഀ
	}਍ऀ洀攀洀挀瀀礀⠀瀀甀爀攀开爀攀猀瀀漀渀猀攀 ⬀ 漀昀昀猀攀琀 Ⰰ 洀猀最⸀氀洀开爀攀猀瀀Ⰰ 氀洀开氀攀渀⤀㬀ഀ
	offset += lm_len;਍ऀ洀攀洀挀瀀礀⠀瀀甀爀攀开爀攀猀瀀漀渀猀攀 ⬀ 漀昀昀猀攀琀 Ⰰ 洀猀最⸀渀琀开爀攀猀瀀Ⰰ 渀琀氀洀开氀攀渀⤀㬀ഀ
਍ऀ攀渀挀漀搀攀开戀愀猀攀㘀㐀⠀戀甀昀Ⰰ瀀甀爀攀开爀攀猀瀀漀渀猀攀Ⰰ氀攀渀⤀㬀ഀ
	free(pure_response);਍ऀ昀爀攀攀⠀洀猀最⸀搀漀洀愀椀渀⤀㬀ഀ
	free(msg.user);਍ऀ昀爀攀攀⠀洀猀最⸀栀漀猀琀⤀㬀ഀ
	return true;਍紀ഀ
// end of part3: NTML 算法਍ഀ�