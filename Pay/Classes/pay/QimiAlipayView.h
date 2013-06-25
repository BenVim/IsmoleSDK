//
//  QimiAlipayView.h
//  Pay
//
//  Created by Ben on 6/25/13.
//
//

#ifndef __Pay__QimiAlipayView__
#define __Pay__QimiAlipayView__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "json.h"

USING_NS_CC;
USING_NS_CC_EXT;

class QimiAlipayView : public cocos2d::CCLayer
{
public:
    QimiAlipayView();
    ~QimiAlipayView();
    CREATE_FUNC(QimiAlipayView);
    bool init();
    
    void initView();
    void initData(int uId, int sId, std::string key, int money);
    void rechargeOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void backOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
private:
    
    int m_uId;
    int m_sId;
    std::string m_key;
    int m_money;
    int m_cash;
    CCArray* m_pButtonList;
    std::string m_oderId;
    
    CCLabelTTF* m_pMcashNumTxt;
    CCLabelTTF* m_pMcashNumLastTxt;
    
    
    CCEditBox* m_pEditName;
    
    bool isSelelcted;
    
private:
    void upDataView(int pay);
    void upSelectState(int index);
    void onLoadOrderSucssful(cocos2d::CCNode *sender, void *data);
    void loadAlixPay();
};


#endif /* defined(__Pay__QimiAlipayView__) */
