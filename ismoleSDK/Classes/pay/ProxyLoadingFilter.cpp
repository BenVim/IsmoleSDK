//
//  ProxyLoadingFilter.cpp
//  Sangou
//
//  Created by  ismole04 on 12-12-5.
//
//

#include "ProxyLoadingFilter.h"
#include "Proxy.h"
#include "StageScene.h"
#include "GameCCBLoader.h"
//#include "ResourceConfig.h"

USING_NS_CC;

ProxyLoadingFilter::ProxyLoadingFilter()
: m_pLoadingMaskLayer(NULL)
, m_pLoadingView(NULL)
, m_nWaitRequestCount(0)
{
    
}

void ProxyLoadingFilter::filter(ProxyStatus status, Proxy *pProxy)
{
    bool isMask = true;
    if (!pProxy->getParamValueByName("mask").isNull())
    {
        isMask = pProxy->getParamValueByName("mask").asBool();
    }
    
    if (equalStatus(status, ProxyStatusWait) && isMask)
    {
        if (m_nWaitRequestCount == 0)
        {
            CCSize s = CCDirector::sharedDirector()->getWinSize();
            m_pLoadingMaskLayer = CCLayerColor::create(ccc4(0, 0, 0, 0), s.width, s.height);
            
            
            m_pLoadingView = GameCCBLoader::sharedLoader()->createCCBNode<LoadingView>("LoadingView.ccbi");
            m_pLoadingMaskLayer->addChild(m_pLoadingView);
            
            CCScene *pScene;
            pScene = CCDirector::sharedDirector()->getRunningScene();   
            CCNode *pFirstChild = dynamic_cast<CCNode *>(pScene->getChildren()->objectAtIndex(0));
            pFirstChild->addChild(m_pLoadingMaskLayer, 1000000000);
        }
        
        m_nWaitRequestCount++;
    }
    else if (equalStatus(status, ProxyStatusResponse) && isMask)
    {
        if (m_nWaitRequestCount!=0) {
            m_nWaitRequestCount--;
        }
        if (m_pLoadingMaskLayer && m_nWaitRequestCount == 0)
        {
            m_pLoadingView->removeFromParentAndCleanup(true);
            m_pLoadingMaskLayer->removeFromParentAndCleanup(true);
            m_pLoadingMaskLayer = NULL;
            m_pLoadingView = NULL;
        }
    }
}