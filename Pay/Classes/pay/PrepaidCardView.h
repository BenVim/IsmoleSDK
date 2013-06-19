//
//  PrepaidCardView.h
//  Navigations
//
//  Created by Ben on 5/7/13.
//
//

#ifndef __Navigations__PrepaidCardView__
#define __Navigations__PrepaidCardView__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
//CCScrollView的显示内容的高度
#define SCROLLVIEW_HEIGHT 580


class PrepaidCardView : public cocos2d::CCLayer
,public cocos2d::extension::CCBSelectorResolver
,public cocos2d::extension::CCBMemberVariableAssigner
,public cocos2d::extension::CCNodeLoaderListener
{
public:
    PrepaidCardView();
    ~PrepaidCardView();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(PrepaidCardView, create);
    
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
    void nextOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    
    void initView();
    void initData(int uId, int sId, std::string key, int money, int kind);
    
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
    int m_kind;
    
    CCScrollView* m_pHelpScrollView;
    //CCScrollView的y轴起点
    float mScrollViewY;
    
    CCArray* m_pButtonList;
    
private:
    
    void upDataView(int pay);
    void upSelectState(int index);
};


class PrepaidCardViewLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PrepaidCardViewLoader, loader);
    
protected:
    
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(PrepaidCardView);
    
};

#endif /* defined(__Navigations__PrepaidCardView__) */
