#ifndef ___BASE64_H
#define ___BASE64_H

#ifdef __cplusplus
extern "C"{
#endif

//����֪ʶ�ο�: https://bbs.pediy.com/thread-253433.htm

#include <stdlib.h>
#include <string.h>


int base64_encode(unsigned char *pPlainString, unsigned char **pEncodeString);
int base64_decode(unsigned char *pEncodeString, unsigned char **pPlainString);

#ifdef __cplusplus
}
#endif

#endif // ___BASE64_H
