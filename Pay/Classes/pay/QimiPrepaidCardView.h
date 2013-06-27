//
//  QimiPrepaidCardView.h
//  Pay
//
//  Created by Ben on 6/25/13.
//
//

#ifndef __Pay__QimiPrepaidCardView__
#define __Pay__QimiPrepaidCardView__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "json.h"

USING_NS_CC;
USING_NS_CC_EXT;

class QimiPrepaidCardView : public cocos2d::CCLayer
{
public:
    QimiPrepaidCardView();
    ~QimiPrepaidCardView();
    CREATE_FUNC(QimiPrepaidCardView);
    bool init();
    
    void initView();
    void initData(std::string uId, int sId, std::string key, int money, int kind);
    
    void selected(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void backOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void nextOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    
    
private:
    
    std::string m_uId;
    int m_sId;
    std::string m_key;
    int m_money;
    int m_cash;
    int m_kind;
    
    CCArray* m_pButtonList;
    CCLabelTTF* m_pMcashNumTxt;
    CCLabelTTF* m_pMcashNumLastTxt;
    
    cocos2d::extension::CCScale9Sprite* m_pInputTxtBg;
    cocos2d::CCNode* m_pCCEditBoxCCNode;
    CCEditBox* m_pEditName;
    
private:
    void upDataView(int pay);
    void upSelectState(int index);
};


#endif /* defined(__Pay__QimiPrepaidCardView__) */
