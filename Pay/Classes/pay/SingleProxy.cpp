//
//  SingleProxy.cpp
//  libs
//
//  Created by  brucex on 12-12-5.
//
//

#include "SingleProxy.h"
#include "ProxyFilterManager.h"
#include "DataRequest.h"

USING_NS_CC;

SingleProxy::~SingleProxy()
{
    
}

Json::Value SingleProxy::getRequestMoreParam()
{
    Json::Value v;
    return v;
}

SingleProxy::SingleProxy(Json::Value param) : Proxy(param), m_bIsLoaded(false), m_nProxyId(0)
{
    
}

SingleProxy *SingleProxy::create(Json::Value param)
{
    SingleProxy *pProxy = new SingleProxy(param);
    if (pProxy != NULL)
    {
        pProxy->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pProxy);
    }
    return pProxy;
}

std::string SingleProxy::getRequestParamString()
{
    Json::FastWriter writer;
    return writer.write(m_jvRequestParamData);
}

void SingleProxy::beginLoad()
{
    m_bIsLoaded = true;
    retain();
}

void SingleProxy::endLoad()
{
    if (m_bIsLoaded)
    {
        release();
    }
    m_bIsLoaded = false;
}
