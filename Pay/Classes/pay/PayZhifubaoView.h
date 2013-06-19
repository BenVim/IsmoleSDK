//
//  PayZhifubaoView.h
//  Navigations
//
//  Created by Ben on 5/7/13.
//
//

#ifndef __Navigations__PayZhifubaoView__
#define __Navigations__PayZhifubaoView__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SingleProxy.h"
#include "json.h"

USING_NS_CC;
USING_NS_CC_EXT;

class PayZhifubaoView : public cocos2d::CCLayer
,public cocos2d::extension::CCBSelectorResolver
,public cocos2d::extension::CCBMemberVariableAssigner
,public cocos2d::extension::CCNodeLoaderListener
{
public:
    PayZhifubaoView();
    ~PayZhifubaoView();
    
    
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(PayZhifubaoView, create);
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

    void backOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void select10OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void select20OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void select30OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void select50OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void select100OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void select300OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void select500OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void rechargeOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    
    void initView();
    void initData(int uId, int sId, std::string key, int money);
    
private:
    CCControlButton* m_pBackBtn;
    CCControlButton* m_pBtnCongzhi;
    CCControlButton* m_pBtn10Select;
    CCControlButton* m_pBtn20Select;
    CCControlButton* m_pBtn30Select;
    CCControlButton* m_pBtn50Select;
    CCControlButton* m_pBtn100Select;
    CCControlButton* m_pBtn300Select;
    CCControlButton* m_pBtn500Select;
    
    cocos2d::CCLabelTTF* m_pMcashNumTxt;
    cocos2d::CCLabelTTF* m_pMcashNumBackTxt;
    cocos2d::extension::CCScale9Sprite* m_pInputTxtBg;
    cocos2d::CCNode* m_pCCEditBoxCCNode;
    CCEditBox* m_pEditName;
    
    int m_uId;
    int m_sId;
    std::string m_key;
    int m_money;
    int m_cash;
    CCArray* m_pButtonList;
    std::string m_oderId;
    
private:
    void upDataView(int pay);
    void upSelectState(int index);
    void onLoadOrderSucssful(cocos2d::CCNode *sender, void *data);
    void onLoadOrderFided(Proxy* pro, ProxyEvent proxyEvent);
    void loadAlixPay();
};


class PayZhifubaoViewLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PayZhifubaoViewLoader, loader);
    
protected:
    
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(PayZhifubaoView);
    
};

#endif /* defined(__Navigations__PayZhifubaoView__) */
