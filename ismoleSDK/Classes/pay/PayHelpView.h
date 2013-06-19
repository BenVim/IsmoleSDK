//
//  PayHelpView.h
//  Navigations
//
//  Created by Ben on 5/7/13.
//
//

#ifndef __Navigations__PayHelpView__
#define __Navigations__PayHelpView__


#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class PayHelpView : public cocos2d::CCLayer
,public cocos2d::extension::CCBSelectorResolver
,public cocos2d::extension::CCBMemberVariableAssigner
,public cocos2d::extension::CCNodeLoaderListener
{
public:
    PayHelpView();
    ~PayHelpView();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(PayHelpView, create);
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    void backOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    
    void ZfbOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void SzOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void LtOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void DxOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    
    void initView();
    void onRequestData();
    void onRequestFaild();
    
    
    
private:
    CCControlButton* m_pBackBtn;
    CCControlButton* m_pBtnZfb;
    cocos2d::extension::CCControlButton* m_pBtnSz;
    cocos2d::extension::CCControlButton* m_pBtnLt;
    cocos2d::extension::CCControlButton* m_pBtnDx;
    
    cocos2d::CCLabelTTF* m_pPassThroughNumTxt;
    cocos2d::CCLabelTTF* m_pMcashNumTxt;
    cocos2d::CCLabelTTF* m_pProductNameTxt;
    cocos2d::CCLabelTTF* m_pGameNameTxt;
    
};


class PayHelpViewLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PayHelpViewLoader, loader);
    
protected:
    
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(PayHelpView);
    
};

#endif /* defined(__Navigations__PayHelpView__) */
