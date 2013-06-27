#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "StageScene.h"
#include "QimiPlatform.h"
#include "QimiParamInfo.h"
#include "QimiUserModel.h"

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
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero);
    this->addChild(pMenu, 1);
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    /*平台调用方式*/
    /* QimiParamInfo::create(int appId, int sId, std::string appKey);
     * appId 应用ID
     * sId 
     * appkey
     */
    QimiParamInfo* paramInfo = QimiParamInfo::create(21, 15, "7a92bba4670d479c5514720c1cf46aab");
    QimiPlatform::shareQimiPlatform()->setParamInfo(paramInfo);
    
    //QimiPlatform::shareQimiPlatform()->QimiRegister();
    QimiUserModel* userModel =QimiPlatform::shareQimiPlatform()->getQimiUserModel();
    
    CCLog("是否登录 %d", QimiPlatform::shareQimiPlatform()->isLogined());
    if (userModel!=NULL && userModel->getuID() != "0")
    {
        QimiPlatform::shareQimiPlatform()->openPayDailog(userModel->getuID(), 15, "7a92bba4670d479c5514720c1cf46aab", 10);
    }
    else
    {
        QimiPlatform::shareQimiPlatform()->QimiLogin();
    }
    
    //QimiPlatform::shareQimiPlatform()->QimiLogin();
}









