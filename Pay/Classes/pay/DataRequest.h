//
//  DataRequest.h
//  Sangou
//
//  Created by  ismole04 on 12-12-5.
//
//

#ifndef __Sangou__DataRequest__
#define __Sangou__DataRequest__

#include "cocos2d.h"

typedef unsigned int RequestStatus;

enum
{
    RequestStatusSucceed = 1 << 0,
    RequestStatusError = 1 << 1
};

typedef void (cocos2d::CCObject::*SEL_RequestHandler)(RequestStatus status, std::string data);

#define request_selector(_SELECTOR) (SEL_RequestHandler)(&_SELECTOR)

class DataRequest : public cocos2d::CCObject
{
public:
    DataRequest(cocos2d::CCObject *target, SEL_RequestHandler action);
    
    void addParamInfo(std::string key, std::string value);
    
    void load(std::string url);
    
    static DataRequest *createWithTarget(cocos2d::CCObject *target, SEL_RequestHandler handler);
    
private:
    cocos2d::CCString * getRequestString();
    void onHttpRequestCompleteHandler(cocos2d::CCNode *pSender, void *pObj);
    
private:
    cocos2d::CCDictionary *m_pRequestDataDict;
    
    cocos2d::CCObject *m_pTarget;
    SEL_RequestHandler m_requestAction;
};

#endif /* defined(__Sangou__DataRequest__) */
