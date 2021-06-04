#include <stdio.h>
#include <string.h>

#include "base64.h"

/************************************************************************
 * �������ƣ�_encode_string
 * �������ܣ�base64 ����
 * ����˵����
 * ����޸ģ�2021-06-02
 ************************************************************************/
static void _encode_string(unsigned char *aucPlainText,  unsigned char *aucEncodeText, unsigned int uiEncodeLen)
{
    unsigned int index_plainText = 0;
    unsigned int index_encodeText = 0;
    unsigned char index_base64 = 0;
    unsigned char base64_table[64] =
    {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
        'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
        'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
        'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
        'w', 'x', 'y', 'z', '0', '1', '2', '3',
        '4', '5', '6', '7', '8', '9', '+', '/'
    };


    for(;index_encodeText < uiEncodeLen ; index_plainText += 3, index_encodeText += 4)
    {
        //ÿ 3 byte ���в��Ϊ 4 ������(ÿ����Ϊ 6 bit) ,���ڸ�λ��� 0, Ȼ��õ� table ��Ӧ��������
        //�� 1 ����
        index_base64 = (aucPlainText[index_plainText] >> 2) & 0x3F;
        aucEncodeText[index_encodeText] =   base64_table[index_base64];
        //�� 2 ����
        index_base64 = (aucPlainText[index_plainText] & 0x03) << 4 | ((aucPlainText[index_plainText + 1] >> 4) & 0x0F);
        aucEncodeText[index_encodeText + 1] = base64_table[index_base64];
        //�� 3 ����
        index_base64 = ((aucPlainText[index_plainText + 1] & 0x0F) << 2) | ((aucPlainText[index_plainText + 2] >> 6) & 0x03);
        aucEncodeText[index_encodeText + 2] = base64_table[index_base64];
        //�� 4 ����
        index_base64 = aucPlainText[index_plainText + 2] & 0x3F;
        aucEncodeText[index_encodeText + 3] = base64_table[index_base64];
    }
    return ;
}


int base64_encode(unsigned char *sourceText, unsigned char **encodeString)
{
    //��Ҫ��¼���ܻ������ = Ҫ����, ���潫���� A ���µ�;
    unsigned int i;
    unsigned char ucFillCount = 0;
    unsigned int uiSourceLen = 0;
    unsigned int uiEncodeLen = 0;
    unsigned char *aucPlainText = NULL;
    unsigned char *aucEncodeText = NULL;

    //������;
    if(sourceText == NULL)
    {
        return 1;
    }

    //2.��� str �ĳ����Ƿ��� 3 �ı���,���������Ҫ������Ӧ 0x0;
    uiSourceLen = strlen((const char *)sourceText);
    if(uiSourceLen % 3 != 0)
    {
        ucFillCount = 3 - (uiSourceLen % 3);
    }

    //3.������Ҫʹ�õ��м��������Ҫ���ر����ַ���
    aucPlainText = (unsigned char *)malloc((uiSourceLen  + ucFillCount) * sizeof(unsigned char));
    if(aucPlainText == NULL)
    {
        return 2;
    }

    memset(aucPlainText, 0, (uiSourceLen + ucFillCount) * sizeof(unsigned char));
    memcpy(aucPlainText, sourceText, uiSourceLen);
    uiSourceLen = uiSourceLen + ucFillCount;   //source len ��¼Ϊ plainText �ĳ���

    //Base64 �ǽ� 3 ���ֽ�,���Ϊ 4 ���ֽڵĴ���,�˴���ͨ�� ������ 3 ���� 4�� �õ� Encode �����մ�С
    uiEncodeLen = (uiSourceLen / 3) << 2;
    aucEncodeText = (unsigned char *)malloc((uiEncodeLen + 1) * sizeof(unsigned char));
    if(aucEncodeText == NULL)
    {
        free(aucPlainText);
        return 3;
    }
    memset(aucEncodeText, 0, uiEncodeLen + 1);

    //4. Encode
    _encode_string(aucPlainText, aucEncodeText, uiEncodeLen);

    //5. �����Ӧ�� '='
    i = uiEncodeLen - 1;
    while(ucFillCount > 0)
    {
        if(aucEncodeText[i] == 'A')
        {
            aucEncodeText[i] = '=';
        }
        i--;
        ucFillCount--;
    }

    free(aucPlainText);
    *encodeString = aucEncodeText;
    return 0;
}

/************************************************************************
 * �������ƣ�_get_base64_index
 * �������ܣ����� Base64 �����ַ������������ַ���Ӧ��������(������Ϊԭ����)
 * ����˵����
 * ����޸ģ�2021-06-02
 ************************************************************************/
static void _get_base64_index(unsigned char *pEncodeString, unsigned char *pIndex, unsigned int uiEncodeLen)
{
    unsigned int i = 0;
    for(; i < uiEncodeLen; i++)
    {
        if(pEncodeString[i] >= 'A' && pEncodeString[i] <= 'Z')
        {
            pIndex[i] = pEncodeString[i] - 'A';
        }
        else if(pEncodeString[i] >= 'a' && pEncodeString[i] <= 'z')
        {
            pIndex[i] = pEncodeString[i] - 'a' + 26;
        }
        else if(pEncodeString[i] >= '0' && pEncodeString[i] <= '9')
        {
            pIndex[i] = pEncodeString[i] - '0' + 52;
        }
        else if(pEncodeString[i] == '+')
        {
            pIndex[i] = 62;
        }
        else if(pEncodeString[i] == '/')
        {
            pIndex[i] = 63;
        }
        else // '='
        {
            pIndex[i] = 0;
        }
    }
    return ;
}

static void _decode_string(unsigned char *pEncodeIndex, unsigned char *pSourceData, unsigned int uiEncodeLen)
{
    unsigned int index_encode,index_source;

    for(index_encode = index_source = 0; index_encode < uiEncodeLen; index_encode += 4, index_source += 3)
    {
        pSourceData[index_source] = ((pEncodeIndex[index_encode] & 0x3F)  << 2) | ((pEncodeIndex[index_encode+1] >> 4) & 0x03);
        pSourceData[index_source+1] = ((pEncodeIndex[index_encode + 1] & 0x0F) << 4)  | ((pEncodeIndex[index_encode + 2] >> 2) & 0x0F);
        pSourceData[index_source+2] = ((pEncodeIndex[index_encode + 2] & 0x03) << 6) | (pEncodeIndex[index_encode + 3] & 0x3F);
    }
}



int base64_decode(unsigned char *pEncodeString, unsigned char **pPlainString)
{
    unsigned int uiEncodeLen = 0;
    unsigned int uiSourceDataLen = 0;
    unsigned char *pEncodeIndex = NULL;
    unsigned char *pSourceData = NULL;

    //�������
    if(pEncodeString == NULL)
    {
        return 1;
    }

    uiEncodeLen = strlen((const char *)pEncodeString);
    if(uiEncodeLen % 4 != 0)
    {
        return 2;
    }

    //1.��ȡ��Ӧ��ԭʼ����
    pEncodeIndex = (unsigned char *)malloc(uiEncodeLen * sizeof(unsigned char));
    if(pEncodeIndex == NULL)
    {
        return 3;
    }

    _get_base64_index(pEncodeString, pEncodeIndex, uiEncodeLen);

    //2.����
    uiSourceDataLen = (uiEncodeLen >> 2) * 3;
    pSourceData = (unsigned char *)malloc((uiSourceDataLen + 1) * sizeof(unsigned char));
    if(pSourceData == NULL)
    {
        free(pEncodeIndex);
        return 4;
    }
    memset(pSourceData, 0, (uiSourceDataLen + 1) * sizeof(unsigned char));

    _decode_string(pEncodeIndex, pSourceData, uiEncodeLen);

    //�ͷ���ʱ����
    free(pEncodeIndex);

    *pPlainString = pSourceData;
    return 0;
}




