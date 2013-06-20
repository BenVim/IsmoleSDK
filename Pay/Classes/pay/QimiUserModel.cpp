//
//  QimiUserModel.cpp
//  Pay
//
//  Created by Ben on 6/20/13.
//
//

#include "QimiUserModel.h"

bool QimiUserModel::init()
{
    return true;
}

void QimiUserModel::initData(Json::Value data)
{
    if (!data.isNull())
    {
        CC_GAME_JSON_ADD(data, isString, m_sessionKey, "session_key", asString);
        
        Json::Value UserData = data["user"];
        if (!UserData.isNull())
        {
            CC_GAME_JSON_ADD(UserData, isInt, m_uId, "uid", isInt);
            CC_GAME_JSON_ADD(UserData, isString, m_userName, "name", asString);
            CC_GAME_JSON_ADD(UserData, isString, m_avatarURL, "avatar", asString);
            CC_GAME_JSON_ADD(UserData, isInt, m_sex, "sex", asInt);
            CC_GAME_JSON_ADD(UserData, isString, m_email, "email", asString);
            CC_GAME_JSON_ADD(UserData, isString, m_sessionKey, "session_key", asString);
            CC_GAME_JSON_ADD(UserData, isInt, m_level, "level", asInt);
            CC_GAME_JSON_ADD(UserData, isInt, m_score, "score", asInt);
            CC_GAME_JSON_ADD(UserData, isInt, m_vipLevel, "vip_level", asInt);
            CC_GAME_JSON_ADD(UserData, isInt, m_vipPrivilege, "vip_privilege", asInt);
            CC_GAME_JSON_ADD(UserData, isInt, m_birthday, "birthday", asInt);
            CC_GAME_JSON_ADD(UserData, isInt, m_regdata, "regdata", asInt);
            CC_GAME_JSON_ADD(UserData, isInt, m_experience, "experience", asInt);
        }
    }
}




/**
 {
 "data": {
 "user": {
    "uid": 22,
    "name": "test22",
    "avatar": "http://dev.ismole.com/fish/qimi/www/static/images/sysavatar/default_male.png",
    "sex": 1,
    "email": "test22@ismole.com",
    "level": 1,
    "score": 0,
    "vip_level": 0,
    "vip_privilege": 0,
 
    "birthday": 19800101,
    "regdata": 1340781448,
    "experience": 0
 },
 "session_key": "ElUe+DqcmYOI9GS+hM7a5f1UqmQsCVpOiYssHcyPfug="
 },
 "status": 100,
 "method": "User.reg"
 }
 **/