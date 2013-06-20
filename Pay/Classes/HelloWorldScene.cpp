#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameCCBLoader.h"
#include "StageScene.h"
#include "QimiPlatform.h"
#include "QimiParamInfo.h"

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
    QimiPlatform::shareQimiPlatform()->QimiRegister();
}









