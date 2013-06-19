//
//  Proxy.cpp
//  libs
//
//  Created by  brucex on 12-12-4.
//
//

#include "Proxy.h"
#include "ProxyFilterManager.h"
#include "GameUtils.h"


//#include "ProxyScriptManager.h"

USING_NS_CC;

Proxy::Proxy(Json::Value requestParamData)
: m_nResponseErrorCodeId(0)
, m_bIsResponseSusscced(false)
, m_jvRequestParamData(requestParamData)
, m_sProxyStatus(ProxyStatusDefault)
, m_bCancel(false)
{
    //ProxyScriptManager::sharedScriptManager()->addProxy(this);
    m_pDispatchTable = CCDictionary::create();
    CC_SAFE_RETAIN(m_pDispatchTable);
}

Proxy::~Proxy()
{
    //ProxyScriptManager::sharedScriptManager()->removeProxy(this);
    CC_SAFE_RELEASE(m_pDispatchTable);
}

void Proxy::cancel()
{
    m_bCancel = true;
    sendActionsForProxyEvents(ProxyEventCancel);
}

Json::Value Proxy::getParamValueByName(std::string paramName)
{
    return m_jvRequestParamData[paramName];
}

void Proxy::load()
{
    ProxyFilterManager::sharedFilterManger()->filter(ProxyStatusRequest, this);
    m_sProxyStatus = ProxyStatusRequest;
    if (!this->m_bCancel)
    {
        std::string key = "data";
        std::string value = getRequestParamString();
        m_pRequest = DataRequest::createWithTarget(this, request_selector(Proxy::onDataRequestCompleteHandler));
        CC_SAFE_RETAIN(m_pRequest);
        m_pRequest->addParamInfo(key, value);
        
        std::string secretKey = "d3d259c564a16c64e96d531d4c192cf8";
        std::string valueuId = CCUserDefault::sharedUserDefault()->getStringForKey("uid","0");
        std::string keyuId = "usk";
        m_pRequest->addParamInfo(keyuId, valueuId);
        
        m_pRequest->addParamInfo("v", "");
        std::string result = value + secretKey + valueuId + "";// md5(request['data'] + "密钥" + usk + version)
        
        std::string final = GameUtils::getStringWithMd5(result);
        m_pRequest->addParamInfo("s", final.c_str());
        
        Json::Value v = getRequestMoreParam();
        Json::Value::Members members( v.getMemberNames() );
        
        for (Json::Value::Members::iterator it = members.begin(); it != members.end(); it++)
        {
            const std::string &name = *it;
            m_pRequest->addParamInfo(name, v[name].asString());
        }
        
        ProxyFilterManager::sharedFilterManger()->filter(ProxyStatusWait, this);
        m_sProxyStatus = ProxyStatusWait;
        
        m_pRequest->load("");
    }
    
    beginLoad();
}

void Proxy::firstLoad()
{
    ProxyFilterManager::sharedFilterManger()->filter(ProxyStatusRequest, this);
    m_sProxyStatus = ProxyStatusRequest;
    if (!this->m_bCancel)
    {
        std::string key = "data";
        std::string value = getRequestParamString();
        m_pRequest = DataRequest::createWithTarget(this, request_selector(Proxy::onDataRequestCompleteHandler));
        CC_SAFE_RETAIN(m_pRequest);
        m_pRequest->addParamInfo(key, value);
        std::string secretKey = "d3d259c564a16c64e96d531d4c192cf8";
        std::string version = "";
        m_pRequest->addParamInfo("v", version);
        std::string valueuId = CCUserDefault::sharedUserDefault()->getStringForKey("uid","0");
        std::string result = value + secretKey + valueuId + version;;// md5(request['data'] + "密钥" + usk)
        std::string final = GameUtils::getStringWithMd5(result);
        CCLog(final.c_str());
        m_pRequest->addParamInfo("s", final.c_str());
        
        Json::Value v = getRequestMoreParam();
        Json::Value::Members members( v.getMemberNames());
        
        for (Json::Value::Members::iterator it = members.begin(); it != members.end(); it++)
        {
            const std::string &name = *it;
            m_pRequest->addParamInfo(name, v[name].asString());
        }
        
        ProxyFilterManager::sharedFilterManger()->filter(ProxyStatusWait, this);
        m_sProxyStatus = ProxyStatusWait;
        
        m_pRequest->load("");
    }
    beginLoad();
}

void Proxy::load(std::string url)
{
    ProxyFilterManager::sharedFilterManger()->filter(ProxyStatusRequest, this);
    m_sProxyStatus = ProxyStatusRequest;
    if (!this->m_bCancel)
    {
        std::string key = "data";
        std::string value = getRequestParamString();
        m_pRequest = DataRequest::createWithTarget(this, request_selector(Proxy::onDataRequestCompleteHandler));
        CC_SAFE_RETAIN(m_pRequest);
        m_pRequest->addParamInfo(key, value);

        Json::Value v = getRequestMoreParam();
        Json::Value::Members members( v.getMemberNames());
        
        for (Json::Value::Members::iterator it = members.begin(); it != members.end(); it++)
        {
            const std::string &name = *it;
            m_pRequest->addParamInfo(name, v[name].asString());
        }
        
        ProxyFilterManager::sharedFilterManger()->filter(ProxyStatusWait, this);
        m_sProxyStatus = ProxyStatusWait;
        
        m_pRequest->load(url);
    }
    beginLoad();
}

void Proxy::onDataRequestCompleteHandler(RequestStatus status, std::string data)
{
    if (status == RequestStatusSucceed)
    {
        Json::Value root;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(data, root);
        if (!parsingSuccessful)
        {
            return;
        }
        onResponse(root);
    }
    else
    {
        onError(data);
    }
    m_pRequest->release();
    m_pRequest = NULL;
    
    endLoad();
}

Json::Value Proxy::getResponseValueByName(std::string name)
{
    return m_jvRequestParamData[name];
}

void Proxy::onResponse(Json::Value responseData)
{
    CCLog("Proxy::onResponse");
    m_jvResponseData = responseData;
    
    m_bIsResponseSusscced = false;
    
    if (!responseData["s"].isNull())
    {
        m_bIsResponseSusscced = responseData["s"].asInt() == 0;
    }
    
    m_nResponseErrorCodeId = responseData["s"].asInt();
    
    if (m_bIsResponseSusscced)
    {
        sendActionsForProxyEvents(ProxyEventResponseSucceed);
    }
    else
    {
        sendActionsForProxyEvents(ProxyEventResponseError);
    }
    
    ProxyFilterManager::sharedFilterManger()->filter(ProxyStatusResponse, this);
    
    m_bIsRequestSusscced = true;
    
    sendActionsForProxyEvents(ProxyEventRequestSucceed);
}

void Proxy::onError(std::string data)
{
    m_bIsRequestSusscced = false;
    m_sRequestErrorMessage = data;
    sendActionsForProxyEvents(ProxyEventRequestFail);
    ProxyFilterManager::sharedFilterManger()->filter(ProxyStatusResponse, this);
}

void Proxy::sendActionsForProxyEvents(ProxyEvent proxyEvent)
{
    for (int i = 0; i < kProxyEventTotalNumber; i ++)
    {
        if ((proxyEvent & (1 << i)))
        {
            CCArray *pInvocationList = this->dispatchListforProxyEvent(1 << i);
            CCObject *pObj = NULL;
            CCARRAY_FOREACH(pInvocationList, pObj)
            {
                ProxyInvocation *pInvocation = (ProxyInvocation *)pObj;
                Json::Value data = this->getResponseData();
                if (!data.isNull())
                {
                    //CCLOG(data.asCString());
                    pInvocation->invoke(this);
                }
                else
                {
                    CCLog("sendActionsForProxyEvents data is NULL !!!!!!!");
                }
            }
        }
    }
    //ProxyScriptManager::sharedScriptManager()->dispatcherEvent(this, proxyEvent);
}


void Proxy::addTargetWithActionFromProxyEvents(cocos2d::CCObject *target, SEL_ProxyHandler action, ProxyEvent proxyEvent)
{
    for (int i = 0; i < kProxyEventTotalNumber; i ++)
    {
        if ((proxyEvent & (1 << i)))
        {
            addTargetWithActionFromProxyEvent(target, action, proxyEvent);
        }
    }
}

void Proxy::removeTargetWithActionFromProxyEvents(cocos2d::CCObject *target, SEL_ProxyHandler action, ProxyEvent proxyEvent)
{
    for (int i = 0; i < kProxyEventTotalNumber; i ++)
    {
        if ((proxyEvent & (1 << i)))
        {
            this->removeTargetWithActionFromProxyEvent(target, action, 1 << i);
        }
    }
}

void Proxy::removeTargetWithActionFromProxyEvent(cocos2d::CCObject *target, SEL_ProxyHandler action, ProxyEvent proxyEvent)
{
    CCArray *pEventInvocationList = this->dispatchListforProxyEvent(proxyEvent);
    
    bool bDeleteObjects = true;
    
    if (!target && !action)
    {
        pEventInvocationList->removeAllObjects();
    }
    else
    {
        CCObject *pObj = NULL;
        CCARRAY_FOREACH(pEventInvocationList, pObj)
        {
            ProxyInvocation *pInvocation = (ProxyInvocation *)pObj;
            bool shouldBeRemoved = true;
            if (target)
            {
                shouldBeRemoved = (target == pInvocation->getTarget());
            }
            if (action)
            {
                shouldBeRemoved = (shouldBeRemoved && (action == pInvocation->getAction()));
            }
            
            if (shouldBeRemoved)
            {
                pEventInvocationList->removeObject(pInvocation, bDeleteObjects);
            }
        }
    }
}

void Proxy::addTargetWithActionFromProxyEvent(cocos2d::CCObject *target, SEL_ProxyHandler action, ProxyEvent proxyEvent)
{
    ProxyInvocation *pInvocation = ProxyInvocation::create(target, action, proxyEvent);
    CCArray *eventInvocationList = this->dispatchListforProxyEvent(proxyEvent);
    eventInvocationList->addObject(pInvocation);
}

CCArray *Proxy::dispatchListforProxyEvent(ProxyEvent proxyEvent)
{
    CCArray *pInvocationList = dynamic_cast<CCArray *>(m_pDispatchTable->objectForKey(proxyEvent));
    
    if (pInvocationList == NULL)
    {
        pInvocationList = CCArray::createWithCapacity(1);
        m_pDispatchTable->setObject(pInvocationList, proxyEvent);
    }
    return pInvocationList;
}