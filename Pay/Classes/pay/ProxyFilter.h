//
//  ProxyFilter.h
//  libs
//
//  Created by  brucex on 12-12-5.
//
//

#ifndef __Sangou__ProxyFilter__
#define __Sangou__ProxyFilter__

#include "cocos2d.h"
#include "ProxyStatus.h"

class Proxy;

class ProxyFilter : public cocos2d::CCObject
{
public:
    virtual void filter(ProxyStatus status, Proxy *pProxy) = 0;
    virtual bool init() { return true; }
    bool equalStatus(ProxyStatus status, ProxyStatus filterStatus)
    {
        return (status & filterStatus);
    }
    bool isMultiProxy(Proxy *pProxy);
    bool isSingleProxy(Proxy *pProxy);
};

#endif /* defined(__Sangou__ProxyFilter__) */
