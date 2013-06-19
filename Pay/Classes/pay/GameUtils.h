//
//  GameUtils.h
//  NavigationTimes
//
//  Created by Ben on 12-12-13.
//
//

#ifndef __NavigationTimes__GameUtils__
#define __NavigationTimes__GameUtils__

#include <iostream>
#include "cocos2d.h"
#include "json.h"
#include "cocos-ext.h"



class ConfirmParamInfo;
class GameUtils
{
public:
    static std::string itos(int i);
    static std::string intToTimeStr(int time);
    static float getRandom(int from, int to);

    static wchar_t * MBCS2Unicode(wchar_t * buff, const char * str);
    static char * Unicode2MBCS(char * buff, const wchar_t * str);
    static int getAttackWithData(int confId, float grow, int toLevel);
    
    static std::string getStringWithMd5(std::string str);
};

#endif /* defined(__NavigationTimes__GameUtils__) */
