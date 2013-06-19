//
//  TypeUtility.h
//  SanguoX
//
//  Created by  ismole04 on 12-12-12.
//
//

#ifndef __SanguoX__TypeUtility__
#define __SanguoX__TypeUtility__

#include "cocos2d.h"

class TypeUtility
{
public:
    template <class T>
    static std::string tostr(T value)
    {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }
    
    template <class T>
    static const char* tocstr(T value)
    {
        std::stringstream ss;
        ss << value;
        std::string str = ss.str();
        cocos2d::CCString *pStr = cocos2d::CCString::create(str);
        return pStr->getCString();
    }
    
    static void replace(std::string& strBig, const std::string & strsrc, const std::string &strdst)
    
    {
        std::string::size_type pos = 0;
        
        while( (pos = strBig.find(strsrc, pos)) != std::string::npos)
        {
            strBig.replace(pos, strsrc.length(), strdst);
            pos += strdst.length();
        }
    }
    
    static void split(const std::string& s, char c, std::vector<std::string>& v);
    
    static cocos2d::CCArray *convertToCCArray(std::vector<std::string> vec);
    static std::vector<std::string> convertToStringVector(cocos2d::CCArray *pArray);

};
#endif /* defined(__SanguoX__TypeUtility__) */
