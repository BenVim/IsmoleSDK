//
//  SingleProxy.h
//  libs
//
//  Created by  brucex on 12-12-5.
//
//

#ifndef __Sangou__SingleProxy__
#define __Sangou__SingleProxy__

#include "Proxy.h"
#include "DataRequest.h"

class SingleProxy : public Proxy
{
public:
    SingleProxy(Json::Value param);
    ~SingleProxy();
    virtual std::string getRequestParamString();
    
    static SingleProxy *create(Json::Value param);
    
    CC_GAME_GET_SET(int, m_nProxyId, ProxyId);
    
protected:
    virtual void beginLoad();
    virtual void endLoad();
    virtual Json::Value getRequestMoreParam();
    
private:
    DataRequest *m_pRequest;
    bool m_bIsLoaded;
    int m_nProxyId;
};

#endif /* defined(__Sangou__SingleProxy__) */
