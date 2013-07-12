#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent);

    void login(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent);
    void logined(CCObject* obj);
    void reg(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent);
    void openWebURL(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent);
    void quit(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent);
    void forget(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent);
    void getDivceId(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
