//
//  QimiPlatformAndroid.cpp
//  Pay
//
//  Created by Ben on 6/18/13.
//
//
#define android_javeClass "com/ismole/Navigations/NavigationsTool"

#include "QimiPlatformAndroid.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <jni.h>
#include <android/log.h>

#endif

bool QimiPlatformAndroid::init()
{
    
    return true;
}

void QimiPlatformAndroid::openWeb(std::string webUrl)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, android_javeClass, "openURL", "(Ljava/lang/String;)V")) {
        jstring jkey = t.env->NewStringUTF(webUrl.c_str());
        t.env->CallStaticVoidMethod(t.classID, t.methodID, jkey);
        t.env->DeleteLocalRef(jkey);
        t.env->DeleteLocalRef(t.classID);
    }
    
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
}

void QimiPlatformAndroid::openAlert(std::string title, std::string msg)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    
#endif
}





