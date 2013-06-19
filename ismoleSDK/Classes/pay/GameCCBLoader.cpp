//
//  GameCCBLoader.cpp
//  SanguoX
//
//  Created by  ismole04 on 12-12-18.
//
//

#include "GameCCBLoader.h"



USING_NS_CC;
USING_NS_CC_EXT;

GameCCBLoader *g_mSharedLoader = NULL;

GameCCBLoader *GameCCBLoader::sharedLoader()
{
    if (g_mSharedLoader == NULL)
    {
        g_mSharedLoader = new GameCCBLoader();
        g_mSharedLoader->init();
    }
    return g_mSharedLoader;
}

GameCCBLoader::GameCCBLoader()
: m_pLibrary(NULL)
{
    
}

GameCCBLoader::~GameCCBLoader()
{
    
}

void GameCCBLoader::init()
{
    m_pLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    CC_SAFE_RETAIN(m_pLibrary);
    
    m_pLibrary->registerCCNodeLoader("PayView", PayViewLoader::loader());
    m_pLibrary->registerCCNodeLoader("GameUIMaskLayer", GameUIMaskLayerLoader::loader());
    m_pLibrary->registerCCNodeLoader("PayZhifubaoView", PayZhifubaoViewLoader::loader());
    m_pLibrary->registerCCNodeLoader("PayHelpView", PayHelpViewLoader::loader());
    m_pLibrary->registerCCNodeLoader("PrepaidCardView", PrepaidCardViewLoader::loader());
    m_pLibrary->registerCCNodeLoader("PrepaidCardNextStepView", PrepaidCardNextStepViewLoader::loader());
    m_pLibrary->registerCCNodeLoader("LoadingView", LoadingViewLoader::loader());
    m_pLibrary->registerCCNodeLoader("GameUIBigMaskLayer", GameUIBigMaskLayerLoader::loader());
    m_pLibrary->registerCCNodeLoader("LoginView", LoginViewLoader::loader());
    m_pLibrary->registerCCNodeLoader("RegisterView", RegisterViewLoader::loader());
    
}









