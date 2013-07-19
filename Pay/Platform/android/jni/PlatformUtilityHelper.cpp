//
//  PlatformUtilityHelper.cpp
//  sanguo123
//
//  Created by brucex on 13-3-31.
//
//

#include "PlatformUtilityHelper.h"
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#include <string>
#include "cocos2d.h"

USING_NS_CC;

#define  CLASS_NAME "com/ismole/pay/Pay"

extern "C"
{
    
     
    
      void payJNI(const char * order,const char * product,const char * productDes,const char * appScheme,const char * parent,const char * seller,const char * notifyUrl,const char * alipayKey,int price)
    {
        JniMethodInfo t;
        
        if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "pay", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V"))
        {
            jstring jorder = t.env->NewStringUTF(order);
            jstring jproduct = t.env->NewStringUTF(product);
            jstring jproductDes = t.env->NewStringUTF(productDes);
            jstring jappScheme = t.env->NewStringUTF(appScheme);
            jstring jparent = t.env->NewStringUTF(parent);
            jstring jseller = t.env->NewStringUTF(seller);
            jstring jnotifyUrl = t.env->NewStringUTF(notifyUrl);
            jstring jalipayKey = t.env->NewStringUTF(alipayKey);
            
            t.env->CallStaticObjectMethod(t.classID, t.methodID, jorder,jproduct,jproductDes,jappScheme,jparent,jseller,jnotifyUrl,jalipayKey,price);
            
            t.env->DeleteLocalRef(t.classID);
            t.env->DeleteLocalRef(jorder);
            t.env->DeleteLocalRef(jproduct);
            t.env->DeleteLocalRef(jproductDes); 
            t.env->DeleteLocalRef(jappScheme);
            t.env->DeleteLocalRef(jparent);
            t.env->DeleteLocalRef(jseller);
            t.env->DeleteLocalRef(jnotifyUrl);
            t.env->DeleteLocalRef(jalipayKey);

        }
    }
    
    void openWebJNI(const char * webUrl, bool isFullScreen)
    {
        JniMethodInfo t;
        
        if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "openWeb", "(Ljava/lang/String;Z)V")) {
            jstring jkey = t.env->NewStringUTF(webUrl);
            t.env->CallStaticVoidMethod(t.classID, t.methodID, jkey, isFullScreen);
            t.env->DeleteLocalRef(jkey);
            t.env->DeleteLocalRef(t.classID);
        }
    }
    
    
    void openAlertJNI(const char* title, const char* msg)
    {
        JniMethodInfo t;
        
        if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "openAlert", "(Ljava/lang/String;Ljava/lang/String;)V")) {
            jstring jtitle = t.env->NewStringUTF(title);
            jstring jmsg = t.env->NewStringUTF(msg);
            t.env->CallStaticVoidMethod(t.classID, t.methodID, jtitle, jmsg);
            t.env->DeleteLocalRef(jtitle);
            t.env->DeleteLocalRef(jmsg);
            t.env->DeleteLocalRef(t.classID);
        }
    }
    
    const char *getDeviceIdJNI()
    {
        JniMethodInfo t;
        
        if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getDeviceId", "()Ljava/lang/String;"))
        {
            jstring result = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
            t.env->DeleteLocalRef(t.classID);
            CCString *ret = new CCString(JniHelper::jstring2string(result).c_str());
            ret->autorelease();
            t.env->DeleteLocalRef(result);
            return ret->m_sString.c_str();
        }
        return 0;
    }
    
    
}









