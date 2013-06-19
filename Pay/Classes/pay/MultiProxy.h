//
//  MultiProxy.h
//  libs
//
//  Created by  brucex on 12-12-5.
//
//

#ifndef __Sangou__MultiProxy__
#define __Sangou__MultiProxy__

#include "Proxy.h"

class SingleProxy;

class MultiProxy : public Proxy
{
public:
    
    MultiProxy();
    
    MultiProxy(Json::Value param);
    
    ~MultiProxy();
    
    MultiProxy(cocos2d::CCArray *pSubProxyArr);
    
    MultiProxy(Json::Value param, cocos2d::CCArray *pSubProxyArr);
    
    static MultiProxy* create();
    static MultiProxy* create(Json::Value param);
    
    static MultiProxy* createWithArray(cocos2d::CCArray *pSingleProxyArr);
    static MultiProxy* createWithArray(Json::Value param, cocos2d::CCArray *pSingleProxyArr);
    
    void addSubProxy(SingleProxy *pSubProxy);
    
    virtual std::string getRequestParamString();
    
    virtual void onResponse(Json::Value responseData);
    
protected:
    
    CC_PROPERTY_READONLY(cocos2d::CCArray *, m_pSubProxyList, SubProxyList);
    
    virtual void beginLoad();
    virtual void endLoad();
    
    virtual Json::Value getRequestMoreParam();
    
private:
    SingleProxy *findProxy(std::string sMod, std::string sDo);
    void initSubProxyArr(cocos2d::CCArray *pTargetArr);
    bool m_bIsLoaded;
};

#endif /* defined(__Sangou__MultiProxy__) */
