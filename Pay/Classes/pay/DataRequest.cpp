//
//  DataRequest.cpp
//  Sangou
//
//  Created by  ismole04 on 12-12-5.
//
//

#include "DataRequest.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

DataRequest *DataRequest::createWithTarget(cocos2d::CCObject *target, SEL_RequestHandler handler)
{
    DataRequest *pRet = new DataRequest(target, handler);
    if (pRet != NULL)
    {
        pRet->autorelease();
    }
    return pRet;
}

DataRequest::DataRequest(CCObject *target, SEL_RequestHandler handler)
: m_pTarget(target)
, m_requestAction(handler)
, m_pRequestDataDict(CCDictionary::create())
{
}

void DataRequest::addParamInfo(std::string key, std::string value)
{
    CCString *pStr = CCString::create(value);
    m_pRequestDataDict->setObject(pStr, key);
}

CCString * DataRequest::getRequestString()
{
    std::string ret = "";
    CCArray *pArray = m_pRequestDataDict->allKeys();
    for (int i = 0; i < pArray->count(); i ++)
    {
        CCString *pStr = (CCString *)pArray->objectAtIndex(i);
        CCString *pValue = (CCString *)m_pRequestDataDict->objectForKey(pStr->getCString());
        ret.append(pStr->getCString());
        ret.append("=");
        ret.append(pValue->getCString());
        if (i < pArray->count() - 1)
        {
            ret.append("&");
        }
    }
    return CCString::create(ret);
}

void DataRequest::load(std::string url)
{
    if (url[url.size() - 1] != '?')
    {
        url.append("?");
    }
    
    const char *postData = getRequestString()->getCString();
    url.append(postData);
    CCLog("%s", url.c_str());
    CCHttpRequest *pReq = new CCHttpRequest();
    pReq->setUrl(url.c_str());
    pReq->setRequestType(CCHttpRequest::kHttpPost);
    pReq->setResponseCallback(this, callfuncND_selector(DataRequest::onHttpRequestCompleteHandler));
    pReq->setRequestData(postData, strlen(postData));
    std::vector<std::string> headers;
    headers.push_back("Content-Type: application/json; charset=utf-8");
    //pReq->setHeaders(headers);
    CCHttpClient::getInstance()->send(pReq);
    pReq->release();
}

void DataRequest::onHttpRequestCompleteHandler(cocos2d::CCNode *pSender, void *pObj)
{
    CCHttpResponse *pResponse = (CCHttpResponse* )pObj;
    
    if (!pResponse)
    {
        return;
    }
    
    if (pResponse->isSucceed())
    {
        std::string responseData;
        std::vector<char> *buffer = pResponse->getResponseData();
        char buff[24];
        for (unsigned int i = 0; i < buffer->size(); i ++)
        {
            sprintf(buff, "%c", (*buffer)[i]);
            responseData.append(buff);
        }
        //CCLog(responseData.c_str());
        if (m_pTarget && m_requestAction)
        {
            (m_pTarget->*m_requestAction)(RequestStatusSucceed, responseData);
        }
    }
    else
    {
        const char *error = pResponse->getErrorBuffer();
        if (m_pTarget && m_requestAction)
        {
            (m_pTarget->*m_requestAction)(RequestStatusError, error);
        }
    }
}

