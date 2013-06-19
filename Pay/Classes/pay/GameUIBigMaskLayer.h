//
//  GameUIBigMaskLayer.h
//  Navigations
//
//  Created by Yao on 13-1-24.
//
//

#ifndef __Navigations__GameUIBigMaskLayer__
#define __Navigations__GameUIBigMaskLayer__

#include "GameUIMaskLayer.h"

class GameUIBigMaskLayer : public GameUIMaskLayer
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(GameUIBigMaskLayer, create);
    
    GameUIBigMaskLayer();
    ~GameUIBigMaskLayer();
    
    virtual void onEnter();
};


class GameUIBigMaskLayerLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GameUIBigMaskLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GameUIBigMaskLayer);
    
};


#endif /* defined(__Navigations__GameUIBigMaskLayer__) */
