//
//  RegisterView.h
//  Pay
//
//  Created by Ben on 5/13/13.
//
//

#ifndef __Pay__RegisterView__
#define __Pay__RegisterView__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SingleProxy.h"
#include "json.h"

USING_NS_CC_EXT;

class RegisterView :public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener{
public:
    RegisterView();
    ~RegisterView();
    
    
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(RegisterView, create);
    void initView();
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    void registerOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void onBack(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
private:
    
    cocos2d::extension::CCControlButton* m_pBackBtn;
    cocos2d::extension::CCControlButton* m_pRegisterBtn;

    cocos2d::CCNode* m_pCCEditBoxUserCCNode;
    cocos2d::CCNode* m_pCCEditBoxPassCCNode;//CCEditBoxPassCCNode:
    cocos2d::CCNode* m_pCCEditBoxVerifyPassCCNode;
    
    cocos2d::extension::CCScale9Sprite* m_pInputUserNameTxtBg;
    cocos2d::extension::CCScale9Sprite* m_pInputUserPassTxtBg;
    cocos2d::extension::CCScale9Sprite* m_pInputUserVerifyPassTxtBg;
    
    cocos2d::extension::CCEditBox* m_pEditUserName;
    cocos2d::extension::CCEditBox* m_pEditUserPass;
    cocos2d::extension::CCEditBox* m_pEditVerifyPass;
    
private:
    
    void registerSucceed(cocos2d::CCNode *sender, void *data);

    
};

class RegisterViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(RegisterViewLoader, loader);
    
protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(RegisterView);
};


#endif /* defined(__Pay__RegisterView__) */
