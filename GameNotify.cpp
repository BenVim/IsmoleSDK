//
//  GameNotify.cpp
//  MusicNinja
//
//  Created by bruce on 12-8-8.
//
//

#include "cocos2d.h"
#include "GameNotify.h"

USING_NS_CC;

static GameNotify *s_gGameNotify = NULL;

GameNotify *GameNotify::sharedNotify()
{
    if (s_gGameNotify == NULL)
    {
        s_gGameNotify = new GameNotify();
        s_gGameNotify->init();
    }
    return s_gGameNotify;
}

void GameNotify::init()
{
    m_pNotifyItems = CCArray::create();
    m_pNotifyItems->retain();
    m_pForceAdds = CCArray::create();
    m_pForceAdds->retain();
    m_bLocked = false;
}

bool GameNotify::postNotify(std::string type, cocos2d::CCObject *pParam)
{
    bool result = false;
    m_bLocked = true;
    
    if (m_pForceAdds->count() > 0)
    {
        while(m_pForceAdds->count())
        {
            NotifyItem *pItem = dynamic_cast<NotifyItem*>(m_pForceAdds->objectAtIndex(0));
            m_pNotifyItems->addObject(pItem);
            m_pForceAdds->removeObject(pItem);
        }
    }
    
    for (int i = 0; i < m_pNotifyItems->count(); i ++)
    {
        NotifyItem *pItem =  dynamic_cast<NotifyItem*> (m_pNotifyItems->objectAtIndex(i));
        if (!pItem->isAllNotify() && pItem->type() == type)
        {
            pItem->call(pParam);
            result = true;
        }
        else if (pItem->isAllNotify())
        {
            pItem->call(type, pParam);
            result = true;
        }
    }
    
    m_bLocked = false;
    return result;
}

void GameNotify::registerNotify(cocos2d::CCObject *pObj, SEL_NotifyFunc callFunc)
{
    NotifyItem *pItem = new NotifyItem(pObj, callFunc);
    if (m_bLocked)
    {
        m_pForceAdds->addObject(pItem);
    }
    else
    {
        m_pNotifyItems->addObject(pItem);
    }
    pItem->release();
}

bool GameNotify::postNotify(std::string type)
{
    return postNotify(type, NULL);
}

void GameNotify::registerNotify(std::string type, cocos2d::CCObject *pObj, cocos2d::SEL_CallFuncO callFunc)
{
    NotifyItem *pItem = new NotifyItem(type, pObj, callFunc);
    if (m_bLocked)
    {
        m_pForceAdds->addObject(pItem);
    }
    else
    {
        m_pNotifyItems->addObject(pItem);
    }
    pItem->release();
}

void GameNotify::removeNotify(cocos2d::CCObject *pObj)
{
    for (int i = m_pNotifyItems->count() - 1; i >= 0 ; i --)
    {
        NotifyItem *pItem =dynamic_cast<NotifyItem*>( m_pNotifyItems->objectAtIndex(i));
        if (pItem->target() == pObj)
        {
            m_pNotifyItems->removeObjectAtIndex(i);
        }
    }
}

void GameNotify::removeAllNotify()
{
    for (int i = m_pNotifyItems->count() - 1; i >= 0 ; i --)
    {
        NotifyItem *pItem =dynamic_cast<NotifyItem*>( m_pNotifyItems->objectAtIndex(i));
        if (pItem!=NULL)
        {
            m_pNotifyItems->removeObjectAtIndex(i);
        }
    }
}

void GameNotify::removeNotify(std::string type, cocos2d::CCObject *pObj, cocos2d::SEL_CallFuncO callFunc)
{
    for (int i = 0; i < m_pNotifyItems->count(); i ++)
    {
        NotifyItem *pItem =dynamic_cast<NotifyItem*> (m_pNotifyItems->objectAtIndex(i));
        if (pItem->type() == type && pItem->target() == pObj && pItem->callFunc() == callFunc)
        {
            m_pNotifyItems->removeObjectAtIndex(i);
            break;
        }
    }
}

void GameNotify::notifyDistanceModeInfo(int curDistance, int totalDistance)
{
    NotifyDistanceModeInfo *pModeInfo = new NotifyDistanceModeInfo(curDistance, totalDistance);
    postNotify(NOTIFY_DISTANCE_INFO, pModeInfo);
    pModeInfo->release();
}

void GameNotify::notifyKillBossModeInfo(int killBoss, int totalBoss)
{
    NotifyKillBossModeInfo *pModeInfo = new NotifyKillBossModeInfo(killBoss, totalBoss);
    postNotify(NOTIFY_KILL_BOSS_INFO, pModeInfo);
    pModeInfo->release();
}

void GameNotify::notifyKillEnemyModeInfo(int killEnemy, int totalEnemy)
{
    NotifyKillEnemyModeInfo *pModeInfo = new NotifyKillEnemyModeInfo(killEnemy, totalEnemy);
    postNotify(NOTIFY_KILL_ENEMY_INFO, pModeInfo);
    pModeInfo->release();
}

void GameNotify::notifyTimeoutModeInfo(int iLeftRoundCount)
{
    NotifyTimeoutModeInfo *pTimeoutInfo = new NotifyTimeoutModeInfo(iLeftRoundCount);
    postNotify(NOTIFY_TIMEOUT_INFO, pTimeoutInfo);
    pTimeoutInfo->release();
}

bool GameNotify::notifyFinishLevel()
{
    return postNotify(NOTIFY_FINISH_LEVEL, NULL);
}

void GameNotify::notifyAddToScene(std::string sceneName)
{
    NotifyGameSceneInfo *pInfo = new NotifyGameSceneInfo(sceneName);
    postNotify(NOTIFY_ADDED_TO_SCENE, pInfo);
    pInfo->release();
}

bool GameNotify::notifyGetObject(std::string objectName, cocos2d::CCObject *pTarget, cocos2d::SEL_CallFuncO callFuncO)
{
    NotifyGetObjectInfo *pInfo = new NotifyGetObjectInfo(objectName, pTarget, callFuncO);
    bool result = postNotify(NOTIFY_GET_OBJECT, pInfo);
    pInfo->release();
    return result;
}

void GameNotify::notifyBeginScene(std::string sceneName)
{
    NotifyGameSceneInfo *pInfo = new NotifyGameSceneInfo(sceneName);
    postNotify(NOTIFY_BEGIN_SCENE, pInfo);
    pInfo->release();
}

void GameNotify::notifyEndScene(std::string sceneName)
{
    NotifyGameSceneInfo *pInfo = new NotifyGameSceneInfo(sceneName);
    postNotify(NOTIFY_END_SCENE, pInfo);
    pInfo->release();
}