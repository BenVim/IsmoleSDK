//
//  TypeUtility.cpp
//  SanguoX
//
//  Created by  ismole04 on 12-12-12.
//
//

#include "TypeUtility.h"
#include <sstream>

USING_NS_CC;

void TypeUtility::split(const std::string &s, char c, std::vector<std::string> &v)
{
    std::string::size_type i = 0;
    std::string::size_type j = s.find(c);
    if (j == std::string::npos)
    {
        v.push_back(s);
    }
    while(j != std::string::npos)//没到字符串结束
    {
        v.push_back(s.substr(i,j - i));
        i = ++j;
        j = s.find(c, j);
        if(j == std::string::npos)
        {
            v.push_back(s.substr(i, s.length()));
        }
    }
}

cocos2d::CCArray *TypeUtility::convertToCCArray(std::vector<std::string> vec)
{
    CCArray *pRet = CCArray::create();
    for(std::vector<std::string>::iterator it = vec.begin(); it != vec.end(); it ++)
    {
        pRet->addObject(CCString::create(*it));
    }
    return pRet;
}

std::vector<std::string> TypeUtility::convertToStringVector(cocos2d::CCArray *pArray)
{
    std::vector<std::string> vec;
    if (pArray != NULL)
    {
        CCObject *pObj = NULL;
        CCARRAY_FOREACH(pArray, pObj)
        {
            CCString *pStr = dynamic_cast<CCString *>(pObj);
            if (pStr != NULL)
            {
                vec.push_back(pStr->getCString());
            }
        }
    }
    return vec;
}