//
//  StageScene.h
//  NavigationTimes
//
//  Created by Ben on 12-12-13.
//
//

#ifndef __NavigationTimes__StageScene__
#define __NavigationTimes__StageScene__

#include "cocos2d.h"

class StageScene : public cocos2d::CCNode
{
public:
    static StageScene* shareStageScene();
    cocos2d::CCNode* m_StageScene;
    cocos2d::CCNode* m_TopWinContainer;
    cocos2d::CCNode* m_SuperTopContainer;
    cocos2d::CCNode* m_DialogContainer;
    cocos2d::CCNode* m_pShippingDialogContainer;
    cocos2d::CCNode* m_GuidContainer;
    cocos2d::CCNode* m_pLayer;
    
    bool updataStatusView();
    CC_GAME_GET_SET(int, m_BoatID, BoatID);
    CC_GAME_GET_SET(int, m_BoatPos, BoatPos);
private:
    int m_BoatID;
    int m_BoatPos;
};

#endif /* defined(__NavigationTimes__StageScene__) */
