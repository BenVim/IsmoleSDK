//
//  QimiPlatformAndroid.h
//  Pay
//
//  Created by Ben on 6/18/13.
//
//

#ifndef __Pay__QimiPlatformAndroid__
#define __Pay__QimiPlatformAndroid__

#include <iostream>
#include "cocos2d.h"

class QimiPlatformAndroid : public cocos2d::CCObject
{
public:
    CREATE_FUNC(QimiPlatformAndroid);
    bool init();
    void openWeb(std::string webUrl);
    void openAlert(std::string title, std::string msg);
    std::string getDeviceId();//获取设备ID
};


#endif /* defined(__Pay__QimiPlatformAndroid__) */
