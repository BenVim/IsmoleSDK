//
//  RequestLoadingView.h
//  Pay
//
//  Created by Ben on 6/27/13.
//
//

#ifndef __Pay__RequestLoadingView__
#define __Pay__RequestLoadingView__

#include "cocos2d.h"
#include "cocos-ext.h"


USING_NS_CC;
USING_NS_CC_EXT;

class RequestLoadingView : public cocos2d::CCLayer
{
public:
    RequestLoadingView();
    ~RequestLoadingView();
    CREATE_FUNC(RequestLoadingView);
    bool init();
    
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){return true;};
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){};
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){};
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){};
    
    cocos2d::CCArray* m_pAnimFrmes;
    
};

#endif /* defined(__Pay__RequestLoadingView__) */
