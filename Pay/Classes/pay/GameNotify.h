//
//  GameNotify.h
//  MusicNinja
//
//  Created by bruce on 12-8-8.
//
//

#ifndef MusicNinja_GameNotify_h
#define MusicNinja_GameNotify_h

//#define NOTIFY_KILL_ENEMY_INFO "killEnemyInfo"
#define NOTIFY_GAME_RESTART "GAME_RESTART" //游戏重新启动
#define NOTIFY_FIHTING_UPDATE_HERO "upDateHero" //更新英雄列表数据
#define NOTIFY_FIHTING_PLAYSKILL_START_EFFECT "start_effect" //播放技能效果
#define NOTIFY_FIHTING_PLAYSKILL_END_EFFECT "end_effect" //技能效果播放完成
#define NOTIFY_FIHTING_UPDATE_HERO_STATE "updateHeroState" //
#define NOTIFY_FIHTING_UPHERO_ACTION_END "updateheroActionEnd" //英雄列表动画出现完成。

#define NOTIFY_GAME_INIT_FINISH "gameInitfinish" //game初始化完成
#define NOTIFY_GAME_UPDATE_USER_INFO "updataUserInfo" //更新用户信息
#define NOTIFY_GAME_UPDATA_SAILOR_LSIT "upadateSailorList" //更新列表

#define NOTIFY_GAME_CHANGE_SAILOR "changeSailor" //替换水手消息
#define NOTIFY_GAME_FREE_SAILOR "freeSailor" //替换水手消息
#define NOTIFY_GAME_UPDATE_ROLE "updateRole" //更改船信息。

#define NOTIFY_GAME_UPDATE_HOME "updateHome" //更改主页
#define NOTIFY_GAME_UPDATE_ARMS "updateArms" //更改弹药显示；

#define NOTIFY_GAME_REMOVE_SUPER_TOP "removeSuperTop" //从SuperTop中移除界面

#define NOTIFY_GAME_TOOL_POTHOUSE "toolPothouse" //工具栏中点击酒馆

//切换场景事件

#define NOTIFY_GAME_CHANGE_SCENE "changeScene"

#define NOTIFY_GAME_REFRESH_ALL_LEVEL "refreshAllLevel"//重置当前港口所有关卡

#define NOTIFY_GAME_REFRESH_DOCK_VIEW "refreshDockView"//刷新当前船坞界面--主要是为了刷新叹号

#define GAME_HOME_SCENE 1
#define GAME_SHIP_SCENE 2
#define GAME_DRUNKERY_SCENE 3
#define GAME_BATTLE_SCENE 4
#define GAME_COURT_SCENE 5
#define GAME_OTHER_SCENE 6
#define GAME_SHIPPING_SCENE 7
#define GAME_MARKET_SCENE 8
#define GAME_MARKET_BUY_SCENE 9
#define GAME_SHIP_SIDE_SCENE 10


#define NOTIFY_ACTION_PAUSE "actionPause"
#define NOTIFY_ACTION_RESUME "actionResume"

#define NOTIFY_KILL_ENEMY_INFO "killEnemyInfo"
#define NOTIFY_KILL_BOSS_INFO   "killBossInfo"
#define NOTIFY_TIMEOUT_INFO "timeOutInfo"
#define NOTIFY_DISTANCE_INFO "distanceInfo"
#define NOTIFY_FINISH_LEVEL "finishLevel"
#define NOTIFY_BEGIN_DRAME_END    "beginDramaEnd" //开始关后剧情
#define NOTIFY_BEGIN_FINISH_LEVEL "beginFinishLevel"
#define NOTIFY_GAME_OVER "gameOver"
#define NOTIFY_ENEMY_ENEMYDOWN "enemyDown"//
#define NOTIFY_ENEMY_CLEARSTATUS "enemyCLEARSTATUS"
#define NOTIFY_ROLE_DEATH "roleDeath"
#define NOTIFY_ADDED_TO_SCENE "addToScene"
#define NOTIFY_GET_OBJECT "getObject"
#define NOTIFY_BEGIN_SCENE "beginScene"
#define NOTIFY_END_SCENE "endScene"

#define NOTIFY_GUID_DRAG_END "NOTIFY_GUID_DRAG_END"
#define NOTIFY_GUID_SAILOR_UPLEVE "NOTIFY_GUID_SAILOR_UPLEVE"
#define NOTIFY_GUID_SAILOR_NAVIGATE "NOTIFY_GUID_SAILOR_NAVIGATE"
#define NOTIFY_GUID_MOVE_ACTION_END "NOTIFY_GUID_MOVE_ACTION_END"

#define NOTIFY_STORY_PLAY_END "NOTIFY_STORY_PLAY_END"
#define NOTIFY_GUID_POST "NOTIFY_GUID_POST" //新手引导完成某一事情，发送的POST消息
#define NOTIFY_GUID_POST2 "NOTIFY_GUID_POST2" //新手引导完成某一事情，发送的POST消息
#define NOTIFY_GUID_BOAT_UPLEVEL_END "NOTIFY_GUID_BOAT_UPLEVEL_END" //船只升级到某一定的级别后的表现

#define NOTIFY_GUID_SHOW_TAVERN "NOTIFY_GUID_SHOW_TAVERN" //显示酒錧提示信息的事件。参数bool
#define NOTIFY_GUID_SHOW_AWARD "NOTIFY_GUID_SHOW_AWARD" //奖品领取的事件。
#define NOTIFY_GUID_SHOW_HOME "NOTIFY_GUID_SHOW_HOME" //主页中的可建造船只的事件。

#include "cocos2d.h"

//notifyKey : NOTIFY_KILL_ENEMY_INFO
class NotifyKillEnemyModeInfo : public cocos2d::CCObject
{
public:
    NotifyKillEnemyModeInfo(int killEnemy, int totalEnemy) : killEnemy(killEnemy), totalEnemy(totalEnemy) { }
    int killEnemy;
    int totalEnemy;
};

class NotifyKillBossModeInfo : public cocos2d::CCObject
{
public:
    NotifyKillBossModeInfo(int killBoss, int totalBoss) : killBoss(killBoss), totalBoss(totalBoss) { }
    int killBoss;
    int totalBoss;
};

class NotifyGetObjectInfo : public cocos2d::CCObject
{
public:
    NotifyGetObjectInfo(std::string objectName, cocos2d::CCObject *target, cocos2d::SEL_CallFuncO callFuncO) : m_sObjectName(objectName), target(target), callFunc(callFuncO) { }
    
    std::string getObjectName()
    {
        return m_sObjectName;
    }
    
    void call(cocos2d::CCObject *pObj)
    {
        if (target && callFunc && pObj)
        {
            (target->*callFunc)(pObj);
        }
    }
    
private:
    std::string m_sObjectName;
    cocos2d::CCObject *target;
    cocos2d::SEL_CallFuncO callFunc;
};

//notifyKey : NOTIFY_BEGIN_SCENE && NOTIFY_END_SCENE
class NotifyGameSceneInfo : public cocos2d::CCObject
{
public:
    NotifyGameSceneInfo(std::string sceneName) : sceneName(sceneName) { }
    std::string sceneName;
};

//notifyKey : NOTIFY_TIMEOUT_INFO
class NotifyTimeoutModeInfo : public cocos2d::CCObject
{
public:
    NotifyTimeoutModeInfo(int leftRoundCount) : leftRoundCount(leftRoundCount) { }
    int leftRoundCount;
};

//notifyKey : NOTIFY_DISTANCE_INFO
class NotifyDistanceModeInfo : public cocos2d::CCObject
{
public:
    NotifyDistanceModeInfo(int curDistance, int totalDistance) : currentDistance(curDistance), totalDistance(totalDistance) { }
    int currentDistance;
    int totalDistance;
};

typedef void (cocos2d::CCObject::*SEL_NotifyFunc)(std::string type, cocos2d::CCObject*);
#define notifyFunc_selector(_SELECTOR) (SEL_NotifyFunc)(&_SELECTOR)

class NotifyItem : public cocos2d::CCObject
{
public:
    NotifyItem(std::string type, cocos2d::CCObject *pObj, cocos2d::SEL_CallFuncO callFunc) : stype(type), pObj(pObj), pCallFun(callFunc), m_bIsAllNotify(false)
    { }
    
    NotifyItem(cocos2d::CCObject *pObj, SEL_NotifyFunc callFunc) : pObj(pObj), pNotifyCallFunc(callFunc), m_bIsAllNotify(true)
    { }
    
    void call(cocos2d::CCObject *pParam)
    {
        (pObj->*pCallFun)(pParam);
    }
    
    void call(std::string type, cocos2d::CCObject *pData)
    {
        (pObj->*pNotifyCallFunc)(type, pData);
    }
    
    bool isAllNotify()
    {
        return m_bIsAllNotify;
    }
    
    cocos2d::CCObject *target()
    {
        return pObj;
    }
    
    cocos2d::SEL_CallFuncO callFunc()
    {
        return pCallFun;
    }
    
    SEL_NotifyFunc notifyFunc()
    {
        return pNotifyCallFunc;
    }
    
    std::string type()
    {
        return stype;
    }
    
private:
    cocos2d::CCObject *pObj;
    cocos2d::SEL_CallFuncO pCallFun;
    SEL_NotifyFunc pNotifyCallFunc;
    bool m_bIsAllNotify;
    std::string stype;
};

class GameNotify
{
public:
    static GameNotify *sharedNotify();
    
    //更新杀怪模式的信息
    void notifyKillEnemyModeInfo(int killEnemy, int totalEnemy);
    //更新倒计时模式的信息
    void notifyTimeoutModeInfo(int leftRoundCount);
    //更新距离模式的信息
    void notifyDistanceModeInfo(int curDistance, int totalDistance);
    bool notifyGetObject(std::string objectName, cocos2d::CCObject *pTarget, cocos2d::SEL_CallFuncO callFuncO);
    //完成关卡
    bool notifyFinishLevel();
    
    //初始化当前场景
    void notifyBeginScene(std::string sceneName);
    //删除当前场景
    void notifyEndScene(std::string sceneName);
    void notifyAddToScene(std::string sceneName);
    
    //注册消息
    void registerNotify(std::string type, cocos2d::CCObject *pObj, cocos2d::SEL_CallFuncO callFunc);
    //注册消息，该方法一般用于在一个类中有多个消息注册的情况
    void registerNotify(cocos2d::CCObject *pObj, SEL_NotifyFunc callFunc);
    //移除指定信息的消息
    void removeNotify(std::string type, cocos2d::CCObject *pObj, cocos2d::SEL_CallFuncO callFunc);
    //移除一个对象注册的所有消息
    void removeNotify(cocos2d::CCObject *pObj);
    void removeAllNotify();//移除所有消息
    //发送一个消息
    bool postNotify(std::string type, cocos2d::CCObject *pParam);
    //发送一个消息，无附加数据
    bool postNotify(std::string type);
    
    void notifyKillBossModeInfo(int killBoss, int totalBoss);
    
private:
    void init();
    
private:
    bool m_bLocked;
    //cocos2d::CCMutableArray<NotifyItem *> *m_pNotifyItems;
    cocos2d::CCArray* m_pNotifyItems;
    //cocos2d::CCMutableArray<NotifyItem *> *m_pForceAdds;
    cocos2d::CCArray* m_pForceAdds;
};

#endif
