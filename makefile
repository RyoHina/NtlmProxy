ntlm_proxy: wei_util.o ntlm_proxy.o arith_base64.o arith_des.o arith_lm_hash.o arith_ntlm_session_v2.o arith_ntlm_v1.o arith_ntlm_v2.o arith_util.o hmac_md5.o httppc_ntlm.o md4.o md5.o arith_nt_hash.o 
wei_util.o:
	gcc -c -g  wei_util.c
ntlm_proxy.o:
	gcc -c -g ntlm_proxy.c
arith_base64.o:
	gcc -c -g arith_base64.c
arith_des.o:
	gcc -c -g arith_des.c
arith_lm_hash:
	gcc -c -g arith_lm_hash.c
arith_ntlm_session_v2.o:
	gcc -c -g arith_ntlm_session_v2.c
arith_nt_hash.o:
	gcc -c -g arith_nt_hash.c
arith_ntlm_v1.o:
	gcc -c -g arith_ntlm_v1.c
arith_ntlm_v2.o:
	gcc -c -g arith_ntlm_v2.c
arith_util.o:
	gcc -c -g arith_util.c
hmac_md5.o:
	gcc -c -g hmac_md5.c
httppc_ntlm.o:
	gcc -c -g httppc_ntlm.c
md4.o:
	gcc -c -g md4.c
md5.o:
	gcc -c -g md5.c
clean:
	rm -f *.o
	rm -f ntlm_proxy
