//
//  StageScene.cpp
//  NavigationTimes
//
//  Created by Ben on 12-12-13.
//
//

#include "StageScene.h"

StageScene* s_shareStageScene;

StageScene* StageScene::shareStageScene()
{
    if (s_shareStageScene==NULL)
    {
        s_shareStageScene = new StageScene();
        s_shareStageScene->retain();
    }
    return s_shareStageScene;
}

bool StageScene::updataStatusView()
{
    bool bRet = false;
    do {
        bRet = true;
    } while (0);
    
    return bRet;
}