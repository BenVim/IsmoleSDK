//
//  ProxyStatus.h
//  libs
//
//  Created by  brucex on 12-12-5.
//
//

#ifndef Sangou_ProxyStatus_h
#define Sangou_ProxyStatus_h

enum
{
    //处于默认阶段的代理状态
    ProxyStatusDefault = 1 << 0,
    //处于请求阶段的代理状态
    ProxyStatusRequest = 1 << 1,
    //处于请求中的代理状态
    ProxyStatusWait = 1 << 2,
    //处于响应后的代理状态
    ProxyStatusResponse = 1 << 3
};

typedef unsigned int ProxyStatus;

#endif
