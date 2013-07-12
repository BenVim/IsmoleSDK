//
//  QimiLoginView.h
//  Pay
//
//  Created by Ben on 6/24/13.
//
//

#ifndef __Pay__QimiLoginView__
#define __Pay__QimiLoginView__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "json.h"

USING_NS_CC;
USING_NS_CC_EXT;

class QimiLoginView : public cocos2d::CCLayer, CCEditBoxDelegate
{
public:
    QimiLoginView();
    ~QimiLoginView();
    CREATE_FUNC(QimiLoginView);
    bool init();
    
    
    void loginOnclick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void registerOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void backOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    
    
    virtual void editBoxEditingDidBegin(CCEditBox *editBox);
    virtual void editBoxEditingDidEnd(CCEditBox *editBox);
    virtual void editBoxTextChanged(CCEditBox *editBox,const std::string &text);
    virtual void editBoxReturn(CCEditBox *editBox);

private:
    
    
    cocos2d::CCSprite* m_pRememberSprite;
    cocos2d::CCSprite* m_pNoRememberSprite;
    
    cocos2d::extension::CCScale9Sprite* m_pInputUserNameTxtBg;
    cocos2d::extension::CCScale9Sprite* m_pInputUserPassTxtBg;
    
    cocos2d::extension::CCEditBox* m_pUserName;
    cocos2d::extension::CCEditBox* m_pPassWorld;
    
    bool isSelelcted;

    
private:
    void onUpdataView();
    void fogetPassWorld(CCObject* obj);
    void remeberPassworld(CCObject* obj);
    void loginSucceed(cocos2d::extension::CCHttpClient *sender, cocos2d::extension::CCHttpResponse *response);
    //void alipayOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void showWin();
};


#endif /* defined(__Pay__QimiLoginView__) */
