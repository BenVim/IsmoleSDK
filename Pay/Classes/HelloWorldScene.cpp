#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "StageScene.h"
#include "QimiPlatform.h"
#include "QimiParamInfo.h"
#include "QimiUserModel.h"
#include "Qimi.h"

USING_NS_CC;
USING_NS_CC_EXT;

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
    //CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCNode* container = CCNode::create();
    this->addChild(container);
    container->setPosition(ccp(0, 80));
    
    QimiParamInfo* paramInfo = QimiParamInfo::create(21, 15, "7a92bba4670d479c5514720c1cf46aab", "pay");
    QimiPlatform::shareQimiPlatform()->setParamInfo(paramInfo);
    
    CCControlButton* backBtn = CCControlButton::create(CCLabelTTF::create("QIMI登录窗口", "Helvetica", 20), CCScale9Sprite::create("buttonblue.png"));
    backBtn->setPreferredSize(CCSizeMake(200, 50));
    container->addChild(backBtn);
    backBtn->setPosition(ccp(240, 520));
    backBtn->addTargetWithActionForControlEvents(this,
                                                 cccontrol_selector(HelloWorld::menuCloseCallback),
                                                 CCControlEventTouchUpInside);
    

    CCControlButton* backBtn3 = CCControlButton::create(CCLabelTTF::create("QIMI注册窗口", "Helvetica", 20), CCScale9Sprite::create("buttonblue.png"));
    backBtn3->setPreferredSize(CCSizeMake(200, 50));
    container->addChild(backBtn3);
    backBtn3->setPosition(ccp(240, 450));
    backBtn3->addTargetWithActionForControlEvents(this,
                                                  cccontrol_selector(HelloWorld::reg),
                                                  CCControlEventTouchUpInside);
    
    CCControlButton* backBtn2 = CCControlButton::create(CCLabelTTF::create("QIMI直接登录窗口", "Helvetica", 20), CCScale9Sprite::create("buttonblue.png"));
    backBtn2->setPreferredSize(CCSizeMake(200, 50));
    container->addChild(backBtn2);
    backBtn2->setPosition(ccp(240, 380));
    backBtn2->addTargetWithActionForControlEvents(this,
                                                  cccontrol_selector(HelloWorld::login),
                                                  CCControlEventTouchUpInside);
    
    
    CCControlButton* backBtn7 = CCControlButton::create(CCLabelTTF::create("QIMI充值中心", "Helvetica", 20), CCScale9Sprite::create("buttonblue.png"));
    backBtn7->setPreferredSize(CCSizeMake(200, 50));
    container->addChild(backBtn7);
    backBtn7->setPosition(ccp(240, 310));
    backBtn7->addTargetWithActionForControlEvents(this,
                                                  cccontrol_selector(HelloWorld::menuCloseCallback),
                                                  CCControlEventTouchUpInside);

    
    
    
    CCControlButton* backBtn4 = CCControlButton::create(CCLabelTTF::create("QIMI论坛", "Helvetica", 20), CCScale9Sprite::create("buttonblue.png"));
    backBtn4->setPreferredSize(CCSizeMake(200, 50));
    container->addChild(backBtn4);
    backBtn4->setPosition(ccp(240, 240));
    backBtn4->addTargetWithActionForControlEvents(this,
                                                  cccontrol_selector(HelloWorld::openWebURL),
                                                  CCControlEventTouchUpInside);
    
    CCControlButton* backBtn5 = CCControlButton::create(CCLabelTTF::create("忘记密码", "Helvetica", 20), CCScale9Sprite::create("buttonblue.png"));
    backBtn5->setPreferredSize(CCSizeMake(200, 50));
    container->addChild(backBtn5);
    backBtn5->setPosition(ccp(240, 160));
    backBtn5->addTargetWithActionForControlEvents(this,
                                                  cccontrol_selector(HelloWorld::forget),
                                                  CCControlEventTouchUpInside);
    
    
    CCControlButton* backBtn6 = CCControlButton::create(CCLabelTTF::create("退出QIMI", "Helvetica", 20), CCScale9Sprite::create("buttonblue.png"));
    backBtn6->setPreferredSize(CCSizeMake(200, 50));
    container->addChild(backBtn6);
    backBtn6->setPosition(ccp(240, 90));
    backBtn6->addTargetWithActionForControlEvents(this,
                                                  cccontrol_selector(HelloWorld::quit),
                                                  CCControlEventTouchUpInside);
    
    CCControlButton* backBtn9 = CCControlButton::create(CCLabelTTF::create("获取设备ID", "Helvetica", 20), CCScale9Sprite::create("buttonblue.png"));
    backBtn9->setPreferredSize(CCSizeMake(200, 50));
    container->addChild(backBtn9);
    backBtn9->setPosition(ccp(240, 20));
    backBtn9->addTargetWithActionForControlEvents(this,
                                                  cccontrol_selector(HelloWorld::getDivceId),
                                                  CCControlEventTouchUpInside);
    
    return true;
}

void HelloWorld::reg(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent)
{
    QimiPlatform::shareQimiPlatform()->QimiRegister();
}

//登录接口
void HelloWorld::menuCloseCallback(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent)
{
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

//直接登录测试帐号
void HelloWorld::login(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent)
{
    CCLog("是否登录 %d", QimiPlatform::shareQimiPlatform()->isLogined());
    QimiPlatform::shareQimiPlatform()->QimiLogin(std::string("ddxytest@ismole.com"), std::string("111111"), this, callfuncO_selector(HelloWorld::logined));
}


void HelloWorld::logined(CCObject* obj)
{
    CCString* pObj = dynamic_cast<CCString*>(obj);
    if (!strcmp(pObj->getCString() ,"1"))
    {
        CCLog("+成功+");
    }
    else
    {
        CCLog("+失败+");
    }
}

void HelloWorld::openWebURL(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent)
{
    QimiPlatform::shareQimiPlatform()->QimiOpenGameForum(52);
}

void HelloWorld::quit(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent)
{
    QimiPlatform::shareQimiPlatform()->loginOut();
}

void HelloWorld::forget(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent)
{
    QimiPlatform::shareQimiPlatform()->openGameWeb(QIMI_FOGET);
}

void HelloWorld::getDivceId(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent)
{
    std::string mDeviceId = QimiPlatform::shareQimiPlatform()->getDeviceId();
    mDeviceId = mDeviceId.append("【设备ID】");
    CCLabelTTF* label = CCLabelTTF::create(mDeviceId.c_str(), "Helvetica", 20);
    this->addChild(label);
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    label->setPosition(ccp(s.width/2, 650));
    
}





