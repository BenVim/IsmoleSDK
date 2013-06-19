//
//  ProxyFilterManager.cpp
//  libs
//
//  Created by  brucex on 12-12-5.
//
//

#include "ProxyFilterManager.h"


USING_NS_CC;

static ProxyFilterManager *s_gProxyFilterManager = NULL;

ProxyFilterManager * ProxyFilterManager::sharedFilterManger()
{
    if (s_gProxyFilterManager == NULL)
    {
        s_gProxyFilterManager = new ProxyFilterManager();
    }
    return s_gProxyFilterManager;
}

ProxyFilterManager::~ProxyFilterManager()
{
    CC_SAFE_RELEASE(m_pFilterList);
}

ProxyFilterManager::ProxyFilterManager()
{
    m_pFilterList = CCArray::create();
    CC_SAFE_RETAIN(m_pFilterList);
}


void ProxyFilterManager::addFilter(ProxyFilter *pFilter)
{
    m_pFilterList->addObject(pFilter);
}

void ProxyFilterManager::removeFilter(ProxyFilter *pFilter)
{
    m_pFilterList->removeObject(pFilter);
}

void ProxyFilterManager::filter(ProxyStatus status, Proxy *pProxy)
{
    CCObject *pObj = NULL;
    CCARRAY_FOREACH(m_pFilterList, pObj)
    {
        ProxyFilter *pFilter = (ProxyFilter *)pObj;
        if (pFilter)
        {
            pFilter->filter(status, pProxy);
        }
    }
}