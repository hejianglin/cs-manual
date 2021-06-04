#include <stdio.h>
#include <string.h>

#include "base64.h"

/************************************************************************
 * 函数名称：_encode_string
 * 函数功能：base64 编码
 * 参数说明：
 * 最后修改：2021-06-02
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
        //每 3 byte 进行拆分为 4 个部分(每部分为 6 bit) ,并在高位填充 0, 然后得到 table 对应的索引号
        //第 1 部分
        index_base64 = (aucPlainText[index_plainText] >> 2) & 0x3F;
        aucEncodeText[index_encodeText] =   base64_table[index_base64];
        //第 2 部分
        index_base64 = (aucPlainText[index_plainText] & 0x03) << 4 | ((aucPlainText[index_plainText + 1] >> 4) & 0x0F);
        aucEncodeText[index_encodeText + 1] = base64_table[index_base64];
        //第 3 部分
        index_base64 = ((aucPlainText[index_plainText + 1] & 0x0F) << 2) | ((aucPlainText[index_plainText + 2] >> 6) & 0x03);
        aucEncodeText[index_encodeText + 2] = base64_table[index_base64];
        //第 4 部分
        index_base64 = aucPlainText[index_plainText + 2] & 0x3F;
        aucEncodeText[index_encodeText + 3] = base64_table[index_base64];
    }
    return ;
}


int base64_encode(unsigned char *sourceText, unsigned char **encodeString)
{
    //需要记录可能会产生的 = 要个数, 后面将最后的 A 更新掉;
    unsigned int i;
    unsigned char ucFillCount = 0;
    unsigned int uiSourceLen = 0;
    unsigned int uiEncodeLen = 0;
    unsigned char *aucPlainText = NULL;
    unsigned char *aucEncodeText = NULL;

    //检查参数;
    if(sourceText == NULL)
    {
        return 1;
    }

    //2.检查 str 的长度是否是 3 的倍数,如果不是需要补足相应 0x0;
    uiSourceLen = strlen((const char *)sourceText);
    if(uiSourceLen % 3 != 0)
    {
        ucFillCount = 3 - (uiSourceLen % 3);
    }

    //3.生成需要使用的中间变量及需要返回编码字符串
    aucPlainText = (unsigned char *)malloc((uiSourceLen  + ucFillCount) * sizeof(unsigned char));
    if(aucPlainText == NULL)
    {
        return 2;
    }

    memset(aucPlainText, 0, (uiSourceLen + ucFillCount) * sizeof(unsigned char));
    memcpy(aucPlainText, sourceText, uiSourceLen);
    uiSourceLen = uiSourceLen + ucFillCount;   //source len 记录为 plainText 的长度

    //Base64 是将 3 个字节,拆分为 4 个字节的处理,此处的通过 ‘除以 3 乘以 4’ 得到 Encode 的最终大小
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

    //5. 填充相应的 '='
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
 * 函数名称：_get_base64_index
 * 函数功能：根据 Base64 各个字符解析出各个字符对应的索引号(索引号为原数据)
 * 参数说明：
 * 最后修改：2021-06-02
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

    //参数检查
    if(pEncodeString == NULL)
    {
        return 1;
    }

    uiEncodeLen = strlen((const char *)pEncodeString);
    if(uiEncodeLen % 4 != 0)
    {
        return 2;
    }

    //1.获取对应的原始数据
    pEncodeIndex = (unsigned char *)malloc(uiEncodeLen * sizeof(unsigned char));
    if(pEncodeIndex == NULL)
    {
        return 3;
    }

    _get_base64_index(pEncodeString, pEncodeIndex, uiEncodeLen);

    //2.解码
    uiSourceDataLen = (uiEncodeLen >> 2) * 3;
    pSourceData = (unsigned char *)malloc((uiSourceDataLen + 1) * sizeof(unsigned char));
    if(pSourceData == NULL)
    {
        free(pEncodeIndex);
        return 4;
    }
    memset(pSourceData, 0, (uiSourceDataLen + 1) * sizeof(unsigned char));

    _decode_string(pEncodeIndex, pSourceData, uiEncodeLen);

    //释放临时变量
    free(pEncodeIndex);

    *pPlainString = pSourceData;
    return 0;
}




