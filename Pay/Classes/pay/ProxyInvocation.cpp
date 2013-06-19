//
//  ProxyInvocation.cpp
//  libs
//
//  Created by  brucex on 12-12-5.
//
//

#include "ProxyInvocation.h"
#include "json.h"

USING_NS_CC;

ProxyInvocation *ProxyInvocation::create(cocos2d::CCObject *pTarget, SEL_ProxyHandler action, ProxyEvent proxyEvent)
{
    ProxyInvocation *pRet = new ProxyInvocation(pTarget, action, proxyEvent);
    if (pRet != NULL)
    {
        pRet->autorelease();
    }
    return pRet;
}

ProxyInvocation::ProxyInvocation(CCObject *target, SEL_ProxyHandler action, ProxyEvent proxyEvent)
{
    m_target = target;
    m_action = action;
    m_proxyEvent = proxyEvent;
}

void ProxyInvocation::invoke(Proxy *sender)
{
    CCLOG("ProxyInvocation::invoke");
    if (m_target && m_action)
    {
        (m_target->*m_action)(sender, m_proxyEvent);
    }
}

