//
//  Proxy.h
//  libs
//
//  Created by  brucex on 12-12-4.
//
//

#ifndef __Libs__Proxy__
#define __Libs__Proxy__

#include "cocos2d.h"
#include "json.h"
#include "ProxyInvocation.h"
#include "ProxyStatus.h"
#include "DataRequest.h"

#define kProxyEventTotalNumber 5

class MultiProxy;

enum
{
    //请求中断的代理事件
    ProxyEventCancel = 1 << 0,
    //请求成功的代理事件
    ProxyEventRequestSucceed = 1 << 1,
    //请求失败的代理事件
    ProxyEventRequestFail = 1 << 2,
    //响应结果的请求成功事件
    ProxyEventResponseSucceed = 1 << 3,
    //响应结果的请求失败事件
    ProxyEventResponseError = 1 << 4
};

class Proxy : public cocos2d::CCObject
{
    friend class MultiProxy;
public:
    Proxy(Json::Value requestParamData);
    ~Proxy();
    
    virtual void sendActionsForProxyEvents(ProxyEvent proxyEvent);
    
    virtual void addTargetWithActionFromProxyEvents(CCObject *target, SEL_ProxyHandler action, ProxyEvent proxyEvent);
    
    virtual void removeTargetWithActionFromProxyEvents(CCObject *target, SEL_ProxyHandler action, ProxyEvent proxyEvent);
    
    virtual void load();
    
    virtual void firstLoad();
    
    virtual void load(std::string url);
    
    virtual void cancel();
    
    virtual void onResponse(Json::Value responseData);
    
    virtual void onError(std::string data);
    
    virtual std::string getRequestParamString() = 0;
    
    Json::Value getParamValueByName(std::string name);
    
    Json::Value getResponseValueByName(std::string name);
    
public:
    CC_SYNTHESIZE_READONLY(ProxyStatus, m_sProxyStatus, ProxyStatus);
    
    CC_SYNTHESIZE_READONLY(bool, m_bIsResponseSusscced, IsResponseSuccessed);
    
    CC_SYNTHESIZE_READONLY(bool, m_bIsRequestSusscced, IsRequestSuccessed);
    
    CC_SYNTHESIZE_READONLY(std::string, m_sRequestErrorMessage, RequestErrorMessage);
    
    CC_SYNTHESIZE_READONLY(int, m_nResponseErrorCodeId, ResponseErrorCodeId);
    
    CC_SYNTHESIZE_READONLY(bool, m_bCancel, IsCancel);
    
    CC_SYNTHESIZE_READONLY(Json::Value, m_jvResponseData, ResponseData);
    
protected:
    
    cocos2d::CCArray *dispatchListforProxyEvent(ProxyEvent proxyEvent);
    
    virtual void addTargetWithActionFromProxyEvent(CCObject *target, SEL_ProxyHandler action, ProxyEvent proxyEvent);
    
    virtual void removeTargetWithActionFromProxyEvent(CCObject *target, SEL_ProxyHandler action, ProxyEvent proxyEvent);
    
    void onDataRequestCompleteHandler(RequestStatus status, std::string data);
    
protected:
    virtual void beginLoad() = 0;
    virtual void endLoad() = 0;
    
    virtual Json::Value getRequestMoreParam() = 0;
    
private:
    
    template <class T>
    void appendParamItem(std::string key, T value)
    {
        m_jvRequestParamData[key] = value;
    }
    
protected:
    
    cocos2d::CCDictionary *m_pDispatchTable;
    
    Json::Value m_jvRequestParamData;
    
    DataRequest *m_pRequest;
    
};

#endif /* defined(__Sangou__Proxy__) */
