//
//  ObjCalls.h
//  Navigations
//
//  Created by Ben on 3/22/13.
//
//

#ifndef __Navigations__ObjCalls__
#define __Navigations__ObjCalls__

#include <iostream.h>
#include <sys/socket.h> // Per msqr
#include <sys/sysctl.h>
#include <net/if.h>
#include <net/if_dl.h>

#pragma mark MAC
// Return the local MAC addy
// Courtesy of FreeBSD hackers email list
// Accidentally munged during previous update. Fixed thanks to mlamb.

class ObjCCalls
{
public:
    void OpenURL(const char *url);//建立開啓網頁方法
    int getStringLength(std::string str);//获取字符串长度
    std::string getMacAddress();//获取MAC地址
};

#endif /* defined(__Navigations__ObjCalls__) */
