//
//  QimiRegisterView.h
//  Pay
//
//  Created by Ben on 6/25/13.
//
//

#ifndef __Pay__QimiRegisterView__
#define __Pay__QimiRegisterView__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "json.h"

USING_NS_CC;
USING_NS_CC_EXT;

class QimiRegisterView : public cocos2d::CCLayer
{
public:
    QimiRegisterView();
    ~QimiRegisterView();
    CREATE_FUNC(QimiRegisterView);
    bool init();
    
    
    void registerOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void backOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
private:
    
    
    
    cocos2d::extension::CCScale9Sprite* m_pInputUserNameTxtBg;
    cocos2d::extension::CCScale9Sprite* m_pInputUserPassTxtBg;
    cocos2d::extension::CCScale9Sprite* m_pInputUserVerifyPassTxtBg;
    
    cocos2d::extension::CCEditBox* m_pEditUserName;
    cocos2d::extension::CCEditBox* m_pEditUserPass;
    cocos2d::extension::CCEditBox* m_pEditVerifyPass;
    
    bool isSelelcted;
    
    
private:
    void registerSucceed(cocos2d::CCNode *sender, void *data);
};

#endif /* defined(__Pay__QimiRegisterView__) */
