//
//  GameUtils.cpp
//  NavigationTimes
//
//  Created by Ben on 12-12-13.
//
//

#include "GameUtils.h"
#include "GameNotify.h"
#include "DictUtility.h"

#include "md5c.h"
#include "TipView.h"
#include "QimiPlatform.h"

USING_NS_CC;
USING_NS_CC_EXT;

float GameUtils::getRandom(int from, int to) {
    return from + (rand() % (to + 1 - from));
}

std::string GameUtils::itos(int i)
{
    char buff[124];
    sprintf(buff, "%d", i);
    return std::string(buff);
}

std::string GameUtils::intToTimeStr(int time)
{
    char buff[124];
    time_t ti =	(time_t)time;
    struct tm *ptr = gmtime(&ti);
    if (ptr->tm_hour + (ptr->tm_mday-1)*24 < 100) {
        sprintf(buff,"%02d:%02d:%02d",ptr->tm_hour + (ptr->tm_mday-1)*24,ptr->tm_min,ptr->tm_sec);
    }else{
        sprintf(buff,"%d天",ptr->tm_mday-1);
    }
    return std::string(buff);
}


wchar_t * GameUtils::MBCS2Unicode(wchar_t * buff, const char * str)
{
    wchar_t * wp = buff;
    char * p = (char *)str;
    while(*p)
    {
        if(*p & 0x80)
        {
            *wp = *(wchar_t *)p;
            p++;
        }
        else{
            *wp = (wchar_t) *p;
        }
        wp++;
        p++;
    }
    *wp = 0x0000;
    return buff;
}

char * GameUtils::Unicode2MBCS(char * buff, const wchar_t * str)
{
    wchar_t * wp = (wchar_t *)str;
    char * p = buff, * tmp;
    while(*wp){
        tmp = (char *)wp;
        if(*wp & 0xFF00){
            *p = *tmp;
            p++;tmp++;
            *p = *tmp;
            p++;
        }
        else{
            *p = *tmp;
            p++;
        }
        wp++;
    }
    *p = 0x00;
    return buff;
}

std::string GameUtils::getStringWithMd5(std::string str)
{
    unsigned char digest[16];
    MD5_CTX context;
    MD5Init(&context);
    MD5UpdaterString(&context, str.c_str());
    MD5Final(digest, &context);
    
    std::string finalStr;
    char buff[16];
    for (int i = 0; i < 16; i++) {
        sprintf(buff, "%02X",digest[i]);
        finalStr.append(buff);
    }
    return finalStr;
}

Json::Value GameUtils::getResponseData(cocos2d::extension::CCHttpResponse *response)
{
    if (!response)
    {
        //调用弹窗口。输出用户信息获取失败。请检查网络。
        //QimiPlatform::shareQimiPlatform()->openAlertDailog("系统提示", "请检查网络");
        return NULL;
    }
    
    int statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    CCLog("response code: %d", statusCode);
    
    if (!response->isSucceed())
    {
        CCLog("response failed");
        CCLog("error buffer: %s", response->getErrorBuffer());
        //QimiPlatform::shareQimiPlatform()->openAlertDailog("系统提示", "网络异常，请检查网络！");
        return NULL;
    }
    
    std::vector<char> *buffer = response->getResponseData();
    std::string responseData;
    char buff[24];
    printf("Http Test, dump data: ");
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        printf("%c", (*buffer)[i]);
        sprintf(buff, "%c", (*buffer)[i]);
        responseData.append(buff);
    }
    printf("\n");
    
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(responseData, root);
    
    if (!parsingSuccessful)
    {
        return NULL;
    }
    return root;
}

void GameUtils::showNewTip(const char *msg, cocos2d::CCNode *parent, cocos2d::CCPoint pt, float daleyTimer, bool bIsFadeOut)
{
    TipView::create(msg, parent, pt, daleyTimer, bIsFadeOut);
}


