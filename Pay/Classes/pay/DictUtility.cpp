//
//  DictUtility.cpp
//  SanguoX
//
//  Created by  ismole04 on 12-12-12.
//
//

#include "DictUtility.h"
#include "TypeUtility.h"
USING_NS_CC;


CCPoint DictUtility::pointForKey(const char *pKey, cocos2d::CCDictionary *pDict)
{
    std::string value = stringForKey(pKey, pDict);
    return CCPointFromString(value.c_str());
}

CCSize DictUtility::sizeForKey(const char *pKey, cocos2d::CCDictionary *pDict)
{
    std::string value = stringForKey(pKey, pDict);
    return CCSizeFromString(value.c_str());
}

std::string DictUtility::stringForKey(const char *key, cocos2d::CCDictionary *dict, std::string defaultValue)
{
	if (dict)
	{
		CCString *pString = dynamic_cast<CCString *>(dict->objectForKey(std::string(key)));
		return pString ? pString->getCString() : defaultValue;
	}
	return defaultValue;
}

bool DictUtility::boolForKey(const char *key, cocos2d::CCDictionary *dict, bool defaultValue)
{
    if (dict)
    {
        CCString *pString = (CCString*)dict->objectForKey(std::string(key));
        bool value =  pString ? std::string(pString->getCString()) == "true" : defaultValue;
        return value;
    }
    return defaultValue;
}

int DictUtility::intForKey(const char *key, cocos2d::CCDictionary *dict, int defualtNum)
{
    if (dict)
    {
        CCInteger *pInt = dynamic_cast<CCInteger *>(dict->objectForKey(std::string(key)));
        if (pInt != NULL)
        {
            return pInt->getValue();
        }
        
        CCString *pString = dynamic_cast<CCString *>(dict->objectForKey(std::string(key)));
        std::string str =  pString ? pString->getCString() : TypeUtility::tostr(defualtNum);
        return atoi(str.c_str());
    }
    return defualtNum;
}

float DictUtility::floatForKey(const char *key, cocos2d::CCDictionary *dict, float defaultValue)
{
    if (dict)
    {
        CCString *pString = (CCString*)dict->objectForKey(std::string(key));
        float value =  pString ? atof(pString->getCString()) : defaultValue;
        return value;
    }
    return defaultValue;
}

cocos2d::CCDictionary *DictUtility::jsonToDictionary(Json::Value v)
{
    if (!v.isObject())
    {
        return NULL;
    }
    CCDictionary *pDict = CCDictionary::create();
    
    Json::Value::Members members (v.getMemberNames());
    Json::Value::Members::iterator it = members.begin(), end = members.end();
    
    for (;it != end; it++)
    {
        std::string key = *it;
        Json::Value value = v[key];
        if (value.isString())
        {
            pDict->setObject(CCString::create(value.asString()), key);
        }
        else if (value.isInt())
        {
            pDict->setObject(CCInteger::create(value.asInt()), key);
        }
        else if (value.isArray())
        {
            pDict->setObject(jsonToArray(value), key);
        }
        else if (value.isObject())
        {
            pDict->setObject(jsonToDictionary(value), key);
        }
    }
    
    return pDict;
}

cocos2d::CCArray *DictUtility::jsonToArray(Json::Value v)
{
    if (!v.isArray())
    {
        return NULL;
    }
    
    //CCArray *pArr = CCArray::create();
    return NULL;
}

cocos2d::CCObject *DictUtility::jsonToObject(Json::Value v)
{
    if (v.isInt())
    {
        return CCInteger::create(v.asInt());
    }
    else if (v.isString())
    {
        return CCString::create(v.asString());
    }
    else if (v.isArray())
    {
        return jsonToArray(v);
    }
    else if (v.isObject())
    {
        return jsonToDictionary(v);
    }
    CCLog("json to object is null");
    return NULL;
}