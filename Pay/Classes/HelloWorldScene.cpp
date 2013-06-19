#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameCCBLoader.h"
#include "StageScene.h"
#include "QimiPlatform.h"

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
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero);
    this->addChild(pMenu, 1);
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    //LoginView* pPayView = GameCCBLoader::sharedLoader()->createCCBNode<LoginView>("LoginView.ccbi");
    //StageScene::shareStageScene()->m_DialogContainer->addChild(pPayView);
    //pPayView->setPosition(ccp(0, 0));
    QimiPlatform::shareQimiPlatform()->openPayDailog(58, 14, "bb7ed06454fdb77f1bfdc42918f175ba", 10);
}









