//
//  GameScrollView.h
//  Navigations
//
//  Created by Yao on 13-1-28.
//
//

#ifndef __Navigations__GameScrollView__
#define __Navigations__GameScrollView__

#include "cocos2d.h"
#include "cocos-ext.h"

class GameScrollView : public cocos2d::extension::CCScrollView{
        
public:
    GameScrollView();
    ~GameScrollView();
    
    virtual void onExit();
    
    static GameScrollView* create(cocos2d::CCSize size, cocos2d::CCNode* container = NULL);
    
    virtual void registerWithTouchDispatcher();
};

#endif /* defined(__Navigations__GameScrollView__) */
