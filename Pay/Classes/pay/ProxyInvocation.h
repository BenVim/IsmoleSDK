//
//  ProxyInvocation.h
//  libs
//
//  Created by  brucex on 12-12-5.
//
//

#ifndef __Sangou__ProxyInvocation__
#define __Sangou__ProxyInvocation__

#include "cocos2d.h"


typedef unsigned int ProxyEvent;

class Proxy;

typedef void (cocos2d::CCObject::*SEL_ProxyHandler)(Proxy *, ProxyEvent);

#define proxy_selector(_SELECTOR) (SEL_ProxyHandler)(&_SELECTOR)

class ProxyInvocation : public cocos2d::CCObject
{
    CC_SYNTHESIZE_READONLY(SEL_ProxyHandler, m_action, Action);
    CC_SYNTHESIZE_READONLY(CCObject *, m_target, Target);
    CC_SYNTHESIZE_READONLY(ProxyEvent, m_proxyEvent, ProxyEvent);
    
public:
    static ProxyInvocation *create(cocos2d::CCObject *pTarget, SEL_ProxyHandler action, ProxyEvent proxyEvent);
    ProxyInvocation(cocos2d::CCObject *target, SEL_ProxyHandler action, ProxyEvent proxyEvent);
    
    void invoke(Proxy *sender);
};

#endif /* defined(__Sangou__ProxyInvocation__) */
