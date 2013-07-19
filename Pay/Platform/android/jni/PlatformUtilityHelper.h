//
//  PlatformUtilityHelper.h
//  sanguo123
//
//  Created by brucex on 13-3-31.
//
//

#ifndef __sanguo123__PlatformUtilityHelper__
#define __sanguo123__PlatformUtilityHelper__
#include "cocos2d.h"
extern "C"
{ 
        extern void payJNI(const char * order,const char * product,const char * productDes,const char * appScheme,const char * parent,const char * seller,const char * notifyUrl,const char * alipayKey, int price);
    
        extern void openWebJNI(const char * webUrl, bool isFullScreen);
        extern void openAlertJNI(const char* title, const char* msg);
        extern const char *getDeviceIdJNI();
}



#endif /* defined(__sanguo123__PlatformUtilityHelper__) */
