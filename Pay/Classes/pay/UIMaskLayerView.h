//
//  UIMaskLayerView.h
//  Pay
//
//  Created by Ben on 6/27/13.
//
//

#ifndef __Pay__UIMaskLayerView__
#define __Pay__UIMaskLayerView__

#include "cocos2d.h"
#include "cocos-ext.h"


USING_NS_CC;
USING_NS_CC_EXT;

class UIMaskLayerView : public cocos2d::CCLayer
{
public:
    UIMaskLayerView();
    ~UIMaskLayerView();
    CREATE_FUNC(UIMaskLayerView);
    bool init();
    
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){return true;};
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){};
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){};
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){};
    
};
#endif /* defined(__Pay__UIMaskLayerView__) */
