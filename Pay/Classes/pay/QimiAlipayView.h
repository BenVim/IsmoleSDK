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
    void initData(std::string uId, int sId, std::string key, int money, std::string appScheme, std::string productName);
    void rechargeOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void selected(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void backOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void qimiHelp(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    
private:
    
    int         m_money;
    int         m_cash;
    int         m_sId;
    bool        isSelelcted;
    std::string m_uId;
    std::string m_key;
    std::string m_oderId;
    std::string m_appScheme;
    std::string m_productName;
    
    CCArray*    m_pButtonList;
    CCLabelTTF* m_pMcashNumTxt;
    CCLabelTTF* m_pMcashNumLastTxt;
    CCEditBox*  m_pEditName;
    
private:
    void upDataView(int pay);
    void upSelectState(CCControlButton* btn);
    void onLoadOrderSucssful(cocos2d::extension::CCHttpClient *sender, cocos2d::extension::CCHttpResponse *response);
    void loadAlixPay();
    
};


#endif /* defined(__Pay__QimiAlipayView__) */
