//
//  QimiPlatformIOS.h
//  Pay
//
//  Created by Ben on 6/18/13.
//
//

#ifndef __Pay__QimiPlatformIOS__
#define __Pay__QimiPlatformIOS__

#include <iostream>

#include "cocos2d.h"

USING_NS_CC;


class QimiPlatformIOS :public cocos2d::CCObject
{
public:
    static QimiPlatformIOS* create();
    bool init();
    
    void openWeb(std::string url);
    void openAlert(std::string title, std::string msg);
private:
    

};



#endif /* defined(__Pay__QimiPlatformIOS__) */
