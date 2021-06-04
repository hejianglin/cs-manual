#include "base64.h"

#include <time.h>
#include <stdio.h>

#define DATA_MAX_LENTH 600


int main(int argc, char *argv[])
{
    srand(time(NULL));

    int ret = 0;
    unsigned char *pData = (unsigned char *)malloc(DATA_MAX_LENTH + 1);
    memset(pData, 0, (DATA_MAX_LENTH + 1));

    unsigned char *pEncodeData = NULL;
    unsigned char *pPlainData = NULL;


    for(int i =1; i < DATA_MAX_LENTH; i++)
    {
        for(int j = 0; j < i; j++)
        {
            pData[j] = rand() % 94 + 32; //ascii 随机获取字符组成字符创
        }


        ret = base64_encode(pData,&pEncodeData);
        if(ret != 0)
        {
            printf("index = %d, encode error!\r\n", i);
            printf("============================\n");
            break;
        }

        //printf("encodeData = %s\n", pEncodeData);

        ret = base64_decode(pEncodeData, &pPlainData);
        if(ret != 0)
        {
            printf("index = %d, decode error!\n",i);
            printf("============================\n");
            free(pEncodeData);
            break;
        }

        //printf("decode string = %s\n", pPlainData);
        //printf("source stirng = %s\n", pData);

        if(memcmp((const char *)pData,(const char *)pPlainData,strlen((const char *)pData)) == 0)
        {
            printf("index = %d, success!\r\n", i);
            printf("============================\n\n");
        }
        else
        {
            printf("index = %d, compare fail!\r\n", i);
            printf("============================\n\n");

            free(pEncodeData);
            free(pPlainData);
            break;
        }
        if(pEncodeData != NULL)
        {
            free(pEncodeData);
            pEncodeData = NULL;
        }

        if(pPlainData != NULL)
        {
            free(pPlainData);
            pPlainData = NULL;
        }
    }

    free(pData);
    return 0;
}
