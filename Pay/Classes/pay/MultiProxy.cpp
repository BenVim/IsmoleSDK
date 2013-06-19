//
//  MultiProxy.cpp
//  libs
//
//  Created by  brucex on 12-12-5.
//
//

#include "MultiProxy.h"
#include "SingleProxy.h"

USING_NS_CC;

MultiProxy *MultiProxy::create()
{
    MultiProxy *pRet = new MultiProxy();
    if (pRet)
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

MultiProxy *MultiProxy::create(Json::Value param)
{
    MultiProxy *pRet = new MultiProxy(param);
    if (pRet)
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

Json::Value MultiProxy::getRequestMoreParam()
{
    Json::Value v;
    v["m"] = "1";
    return v;
}

MultiProxy *MultiProxy::createWithArray(cocos2d::CCArray *pSingleProxyArr)
{
    MultiProxy *pRet = new MultiProxy(pSingleProxyArr);
    if (pRet)
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

MultiProxy *MultiProxy::createWithArray(Json::Value param, cocos2d::CCArray *pSingleProxyArr)
{
    MultiProxy *pRet = new MultiProxy(param, pSingleProxyArr);
    if (pRet)
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

void MultiProxy::initSubProxyArr(cocos2d::CCArray *pTargetArr)
{
    if (pTargetArr != NULL)
    {
        m_pSubProxyList = CCArray::create();
        CCObject *pObj;
        CCARRAY_FOREACH(pTargetArr, pObj)
        {
            m_pSubProxyList->addObject(pObj);
        }
    }
    else
    {
        m_pSubProxyList = CCArray::create();
    }
    CC_SAFE_RETAIN(m_pSubProxyList);
}

MultiProxy::MultiProxy() : Proxy(Json::Value()), m_bIsLoaded(false)
{
    initSubProxyArr(NULL);
}

MultiProxy::MultiProxy(Json::Value param) : Proxy(param), m_bIsLoaded(false)
{
    initSubProxyArr(NULL);
}

MultiProxy::MultiProxy(CCArray *pSubProxyList) : Proxy(Json::Value()), m_bIsLoaded(false)
{
    initSubProxyArr(pSubProxyList);
}

MultiProxy::MultiProxy(Json::Value param, CCArray *pSubProxyArr) : Proxy(param), m_bIsLoaded(false)
{
    initSubProxyArr(pSubProxyArr);
}

MultiProxy::~MultiProxy()
{
    CC_SAFE_RELEASE(m_pSubProxyList);
}

void MultiProxy::beginLoad()
{
    m_bIsLoaded = true;
    retain();
}

void MultiProxy::endLoad()
{
    if (m_bIsLoaded)
    {
        release();
    }
    m_bIsLoaded = false;
}

std::string MultiProxy::getRequestParamString()
{
    Json::Value root;
    CCObject *pObj = NULL;
    CCARRAY_FOREACH(m_pSubProxyList, pObj)
    {
        Proxy *pProxy = dynamic_cast<Proxy *>(pObj);
        if (pProxy)
        {
            root.append(pProxy->m_jvRequestParamData);
        }
    }
    Json::FastWriter writer;
    return writer.write(root);
}

void MultiProxy::onResponse(Json::Value responseData)
{
    m_jvResponseData = responseData;
    
    /*for (int i = 0; i < responseData.size(); i ++)
    {
        Json::Value jsonItem = responseData[i];
        std::string sMod = jsonItem["mod"].asString();
        std::string sDo = jsonItem["do"].asString();
        int idx = jsonItem["idx"].asInt();
        
        SingleProxy *pProxy = findProxy(sMod, sDo, idx);
        if (pProxy)
        {
            pProxy->onResponse(jsonItem);
        }
    }*/
    CCLog("MultiProxy::onResponse");
    for (int i = 0; i < m_pSubProxyList->count(); i ++)
    {
        SingleProxy *pProxy = (SingleProxy *)m_pSubProxyList->objectAtIndex(i);
        
        std::string sMod = pProxy->getParamValueByName("mod").asString();
        std::string sDo = pProxy->getParamValueByName("do").asString();
        
        Json::Value v = responseData[sMod];
        if (!v.empty())
        {
            Json::Value v2 = v[sDo];
            if (!v2.empty())
            {
                pProxy->onResponse(v2);
            }
        }
    }
    
    m_bIsRequestSusscced = true;
    
    sendActionsForProxyEvents(ProxyEventRequestSucceed);
}

SingleProxy *MultiProxy::findProxy(std::string sMod, std::string sDo)
{
    CCObject *pObj = NULL;
    CCARRAY_FOREACH(m_pSubProxyList, pObj)
    {
        SingleProxy *pProxy = dynamic_cast<SingleProxy *>(pObj);
        if (pProxy)
        {
            std::string sParamMod = pProxy->getParamValueByName("mod").asString();
            std::string sParamDo = pProxy->getParamValueByName("do").asString();
            if (sParamMod == sMod && sParamDo == sDo)
            {
                return pProxy;
            }
        }
    }
    return NULL;
}

CCArray *MultiProxy::getSubProxyList()
{
    return m_pSubProxyList;
}

void MultiProxy::addSubProxy(SingleProxy *pSubProxy)
{
    m_pSubProxyList->addObject(pSubProxy);
}