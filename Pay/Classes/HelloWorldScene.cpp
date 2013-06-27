#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "StageScene.h"
#include "QimiPlatform.h"
#include "QimiParamInfo.h"
#include "QimiUserModel.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    CCScene *scene = CCScene::create();
    HelloWorld *layer = HelloWorld::create();

    scene->addChild(layer);
    CCNode* node = CCNode::create();
    layer->addChild(node);
    StageScene::shareStageScene()->m_DialogContainer = node;

    return scene;
}

bool HelloWorld::init()
{
    if ( !CCLayer::init())
    {
        return false;
    }
    
    
    CCControlButton* backBtn = CCControlButton::create(CCScale9Sprite::create("btn_fanhui.png"));
    backBtn->setPreferredSize(CCSizeMake(101, 51));
    this->addChild(backBtn);
    backBtn->setPosition(ccp(163, 400));
    backBtn->addTargetWithActionForControlEvents(this,
                                                 cccontrol_selector(HelloWorld::menuCloseCallback),
                                                 CCControlEventTouchUpInside);
    
    
    
    CCControlButton* backBtn1 = CCControlButton::create(CCScale9Sprite::create("btn_fanhui.png"));
    backBtn1->setPreferredSize(CCSizeMake(101, 51));
    this->addChild(backBtn1);
    backBtn1->setPosition(ccp(300, 100));
    backBtn1->addTargetWithActionForControlEvents(this,
                                                 cccontrol_selector(HelloWorld::login),
                                                 CCControlEventTouchUpInside);
    return true;
}



void HelloWorld::menuCloseCallback(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent)
{
    /*平台调用方式*/
    /* QimiParamInfo::create(int appId, int sId, std::string appKey);
     * appId 应用ID
     * sId 
     * appkey
     */
    QimiParamInfo* paramInfo = QimiParamInfo::create(21, 15, "7a92bba4670d479c5514720c1cf46aab");
    QimiPlatform::shareQimiPlatform()->setParamInfo(paramInfo);
    
    
    CCLog("是否登录 %d", QimiPlatform::shareQimiPlatform()->isLogined());
    if (QimiPlatform::shareQimiPlatform()->isLogined())
    {
        std::string uId = QimiPlatform::shareQimiPlatform()->getQimiUserModel()->getuID();
        QimiPlatform::shareQimiPlatform()->openPayDailog(uId, 15, "7a92bba4670d479c5514720c1cf46aab", 10);
    }
    else
    {
        QimiPlatform::shareQimiPlatform()->QimiLogin();
    }
}

void HelloWorld::login(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent)
{
    CCLog("是否登录 %d", QimiPlatform::shareQimiPlatform()->isLogined());
}








