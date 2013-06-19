//
//  PrepaidCardNextStepView.h
//  PayPro
//
//  Created by Ben on 5/9/13.
//
//

#ifndef __PayPro__PrepaidCardNextStepView__
#define __PayPro__PrepaidCardNextStepView__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SingleProxy.h"
#include "json.h"



USING_NS_CC;
USING_NS_CC_EXT;

class PrepaidCardOrder;

class PrepaidCardNextStepView : public cocos2d::CCLayer
,public cocos2d::extension::CCBSelectorResolver
,public cocos2d::extension::CCBMemberVariableAssigner
,public cocos2d::extension::CCNodeLoaderListener
{
public:
    PrepaidCardNextStepView();
    ~PrepaidCardNextStepView();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(PrepaidCardNextStepView, create);
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    void rechargeOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    
    void selectCard10OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void selectCard20OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void selectCard30OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void selectCard50OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void selectCard100OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void selectCard300OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void selectCard500OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    
    void backOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    
    void initView();
    void initData(int uId, int sId, std::string key, int money, int kind);
    
private:
    CCControlButton* m_pBtnCongzhi;
    CCControlButton* m_pBtnCard10Select;
    CCControlButton* m_pBtnCard20Select;
    CCControlButton* m_pBtnCard30Select;
    CCControlButton* m_pBtnCard50Select;
    CCControlButton* m_pBtnCard100Select;
    CCControlButton* m_pBtnCard300Select;
    CCControlButton* m_pBtnCard500Select;
    CCControlButton* m_pBackBtn;
    
    
    cocos2d::CCLabelTTF* m_pMcashNumTxt;
    cocos2d::CCLabelTTF* m_pMcashNumBackTxt;
    cocos2d::extension::CCScale9Sprite* m_pInputCarNumTxtBg;
    cocos2d::extension::CCScale9Sprite* m_pInputCarPassTxtBg;
    cocos2d::CCNode* m_pCCEditBoxCardNumCCNode;
    cocos2d::CCNode* m_pCCEditBoxCardPassworldCCNode;
    CCEditBox* m_pCardNum;
    CCEditBox* m_pCardPassword;
    int m_kind;
    int m_uId;
    int m_sId;
    std::string m_key;
    int m_money;
    int m_cash;
    int m_denomination;//面额
    CCArray* m_pButtonList;
    
private:
    
    void upDataView(int pay);
    void upSelectState(int index);
    void requestOrder();//请求订单号
    void requestSucssful(cocos2d::CCNode *sender, void *data);//
    void requestFaild(Proxy* pro, ProxyEvent proxyEvent);//

    void reqeuestPay(PrepaidCardOrder* pOrder);
    void requestPaySucssful(cocos2d::CCNode *sender, void *data);//
    void requestPayFaild(Proxy* pro, ProxyEvent proxyEvent);//
    
};


class PrepaidCardNextStepViewLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PrepaidCardNextStepViewLoader, loader);
    
protected:
    
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(PrepaidCardNextStepView);
    
};


#endif /* defined(__PayPro__PrepaidCardNextStepView__) */
