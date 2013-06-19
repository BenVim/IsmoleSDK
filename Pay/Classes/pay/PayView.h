//
//  PayView.h
//  Navigations
//
//  Created by Ben on 5/6/13.
//
//

#ifndef __Navigations__PayView__
#define __Navigations__PayView__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SingleProxy.h"
#include "json.h"

USING_NS_CC;
USING_NS_CC_EXT;

class PayView : public cocos2d::CCLayer
,public cocos2d::extension::CCBSelectorResolver
,public cocos2d::extension::CCBMemberVariableAssigner
,public cocos2d::extension::CCNodeLoaderListener
{
public:
    PayView();
    ~PayView();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(PayView, create);
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    void backOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    
    void alipayOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void SzOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void LtOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void DxOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    
    void initView(int uId, int sId, std::string key, int money);
    void onRequestData();
    
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
    
    cocos2d::CCLabelTTF* m_pProductNameLastTxt;
    cocos2d::CCLabelTTF* m_pMcashNumLastTxt;
    
    int m_uId;
    int m_sId;
    std::string m_key;
    int m_money;
    int m_cash;
    std::string m_gameInfo;
    
    
private:
    void onLoadRequestSucssful(cocos2d::CCNode *sender, void *data);
    void onUpdataView();
    void openPrepaidCard(int kind);
};


class PayViewLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PayViewLoader, loader);
    
protected:
    
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(PayView);
    
};

#endif /* defined(__Navigations__PayView__) */
