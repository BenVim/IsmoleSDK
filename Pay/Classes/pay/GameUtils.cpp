//
//  GameUtils.cpp
//  NavigationTimes
//
//  Created by Ben on 12-12-13.
//
//

#include "GameUtils.h"
#include "GameCCBLoader.h"
#include "GameNotify.h"
#include "DictUtility.h"

#include "md5c.h"





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


