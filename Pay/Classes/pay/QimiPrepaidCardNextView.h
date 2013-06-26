//
//  QimiPrepaidCardNextView.h
//  Pay
//
//  Created by Ben on 6/25/13.
//
//

#ifndef __Pay__QimiPrepaidCardNextView__
#define __Pay__QimiPrepaidCardNextView__


#include "cocos2d.h"
#include "cocos-ext.h"
#include "json.h"
#include "PrepaidCardOrder.h"

USING_NS_CC;
USING_NS_CC_EXT;

class QimiPrepaidCardNextView : public cocos2d::CCLayer
{
public:
    QimiPrepaidCardNextView();
    ~QimiPrepaidCardNextView();
    CREATE_FUNC(QimiPrepaidCardNextView);
    bool init();
    
    void initView();
    void initData(int uId, int sId, std::string key, int money, int kind);
    
    void selected(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void backOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void nextOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    
private:
    
    int m_kind;
    int m_uId;
    int m_sId;
    std::string m_key;
    int m_money;
    int m_cash;
    int m_denomination;//面额
    
    CCArray* m_pButtonList;
    CCLabelTTF* m_pMcashNumTxt;
    CCLabelTTF* m_pMcashNumLastTxt;

    cocos2d::extension::CCScale9Sprite* m_pInputCarNumTxtBg;
    cocos2d::extension::CCScale9Sprite* m_pInputCarPassTxtBg;
    cocos2d::CCNode* m_pCCEditBoxCardNumCCNode;
    cocos2d::CCNode* m_pCCEditBoxCardPassworldCCNode;
    CCEditBox* m_pCardNum;
    CCEditBox* m_pCardPassword;
    
private:
    void upDataView(int pay);
    void upSelectState(int index);
    void requestOrder();//请求订单号
    void requestSucssful(cocos2d::CCNode *sender, void *data);//
    
    void reqeuestPay(PrepaidCardOrder* pOrder);
    void requestPaySucssful(cocos2d::CCNode *sender, void *data);//
};


#endif /* defined(__Pay__QimiPrepaidCardNextView__) */
