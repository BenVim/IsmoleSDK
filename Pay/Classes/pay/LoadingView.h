//
//  LoadingView.h
//  Navigations
//
//  Created by Yao on 13-1-24.
//
//

#ifndef __Navigations__LoadingView__
#define __Navigations__LoadingView__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;

class LoadingView :public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener{
public:
    LoadingView();
    ~LoadingView();
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LoadingView, create);
    void initView();
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
private:
    cocos2d::CCNode* m_pLoadingCCNode;
    cocos2d::CCArray* m_pAnimFrmes;
    cocos2d::CCLayer* m_pLoadingCCLayer;
    void showAnim();
};

class LoadingViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LoadingViewLoader, loader);
    
protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LoadingView);
};


#endif /* defined(__Navigations__LoadingView__) */
