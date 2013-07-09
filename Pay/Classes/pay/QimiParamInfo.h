//
//  QimiParamInfo.h
//  Pay
//
//  Created by Ben on 6/20/13.
//
//

#ifndef __Pay__QimiParamInfo__
#define __Pay__QimiParamInfo__

#include "Qimi.h"
#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class QimiParamInfo : public cocos2d::CCObject
{
public:
    static QimiParamInfo *create(int appId, int sId, std::string key, std::string appScheme)
    {
        QimiParamInfo *pRet = new QimiParamInfo();
        if (pRet && pRet->init(appId, sId, key, appScheme))
        {
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_RELEASE(pRet);
        return NULL;
    }
    
    bool init(int appId, int sId, std::string key, std::string appScheme)
    {
        m_appId     = appId;
        m_sId       = sId;
        m_appKey    = key;
        m_appScheme = appScheme;
        return true;
    }

    CC_GAME_GET_SET(int, m_appId, AppID);
    CC_GAME_GET_SET(int, m_sId, SID);
    CC_GAME_GET_SET(std::string, m_appKey, AppKey);
    CC_GAME_GET_SET(std::string, m_appScheme, AppScheme);

private:
    int m_appId;
    int m_sId;
    std::string m_appKey;
    std::string m_appScheme;


};

#endif /* defined(__Pay__QimiParamInfo__) */

/**

 m_key   = "";
 m_uId   = 0;
 m_sId   = 0;
 m_appid = 0;
**/