//
//  QimiUserModel.h
//  Pay
//
//  Created by Ben on 6/20/13.
//
//

#ifndef __Pay__QimiUserModel__
#define __Pay__QimiUserModel__

#include "cocos2d.h"
#include "json.h"
#include "Qimi.h"


class QimiUserModel : public cocos2d::CCObject
{
public:
    CREATE_FUNC(QimiUserModel);
    bool init();
    void initData(Json::Value data);
    
    
    CC_GAME_GET_SET(std::string , m_uId, uID);
    CC_GAME_GET_SET(std::string , m_userName, UserName);
    CC_GAME_GET_SET(std::string , m_avatarURL, AvatarURL);
    CC_GAME_GET_SET(int , m_sex, Sex);
    CC_GAME_GET_SET(std::string , m_email, Email);
    
    CC_GAME_GET_SET(int , m_level, Level);
    CC_GAME_GET_SET(int , m_score, Score);
    CC_GAME_GET_SET(int , m_vipLevel, VipLevel);
    CC_GAME_GET_SET(int , m_vipPrivilege, VipPrivilege);
    CC_GAME_GET_SET(int , m_birthday, Birthday);
    CC_GAME_GET_SET(int , m_regdata, Regdata);
    CC_GAME_GET_SET(int , m_experience, Experience);
    CC_GAME_GET_SET(std::string , m_sessionKey, SessionKey);
    
private:
    std::string m_uId;
    std::string m_userName;
    std::string m_avatarURL;
    int m_sex;
    std::string m_email;
    int m_level;
    int m_score;
    
    int m_vipLevel;
    int m_vipPrivilege;
    int m_birthday;
    int m_regdata;
    int m_experience;
    std::string m_sessionKey;
};

#endif /* defined(__Pay__QimiUserModel__) */

