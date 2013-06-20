//
//  QimiParamInfo.h
//  Pay
//
//  Created by Ben on 6/20/13.
//
//

#ifndef __Pay__QimiParamInfo__
#define __Pay__QimiParamInfo__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class QimiParamInfo : public cocos2d::CCObject
{
public:
    static QimiParamInfo *create(int appId, int sId, std::string key)
    {
        QimiParamInfo *pRet = new QimiParamInfo();
        if (pRet && pRet->init(appId, sId, key))
        {
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_RELEASE(pRet);
        return NULL;
    }
    
    bool init(int appId, int sId, std::string key)
    {
        m_appId     = appId;
        m_sId       = sId;
        m_appKey    = key;
        
        return true;
    }

    CC_GAME_GET_SET(int, m_appId, AppID);
    CC_GAME_GET_SET(int, m_sId, SID);
    CC_GAME_GET_SET(std::string, m_appKey, AppKey);

private:
    int m_appId;
    int m_sId;
    std::string m_appKey;


};

#endif /* defined(__Pay__QimiParamInfo__) */

/**

 m_key   = "";
 m_uId   = 0;
 m_sId   = 0;
 m_appid = 0;
**/