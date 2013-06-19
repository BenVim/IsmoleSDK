//
//  DictUtility.h
//  SanguoX
//
//  Created by  ismole04 on 12-12-12.
//
//

#ifndef __SanguoX__DictUtility__
#define __SanguoX__DictUtility__

#include "cocos2d.h"
#include "json.h"

class DictUtility
{
public:
    static std::string stringForKey(const char *pKey, cocos2d::CCDictionary *pDict, std::string defaultValue = "");
    static bool boolForKey(const char *pKey, cocos2d::CCDictionary *pDict, bool defaultValue = false);
    static int intForKey(const char *pKey, cocos2d::CCDictionary *pDict, int defaultNum = 0);
    static float floatForKey(const char *pKey, cocos2d::CCDictionary *pDict, float defualtValue = 0);
    static cocos2d::CCPoint pointForKey(const char *pKey, cocos2d::CCDictionary *pDict);
    static cocos2d::CCSize sizeForKey(const char *pKey, cocos2d::CCDictionary *pDict);
    
    static cocos2d::CCDictionary *jsonToDictionary(Json::Value v);
    static cocos2d::CCArray *jsonToArray(Json::Value v);
    static cocos2d::CCObject *jsonToObject(Json::Value v);
};

#endif /* defined(__SanguoX__DictUtility__) */
