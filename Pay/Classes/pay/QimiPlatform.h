//
//  QimiPlatform.h
//  Pay
//
//  Created by Ben on 6/18/13.
//
//

#ifndef __Pay__QimiPlatform__
#define __Pay__QimiPlatform__

#define RegCallBack "RegCallBack"
#define LoginCallBack "LoginCallBack"
#define QimiPayCallBack "QimiPayCallBack"

#include "cocos2d.h"
#include "cocos-ext.h"
#include "json.h"
#include "Qimi.h"

USING_NS_CC;
USING_NS_CC_EXT;

class QimiPlatformIOS;
class QimiPlatformAndroid;
class QimiUserModel;
class QimiParamInfo;

class QimiPlatform : public cocos2d::CCObject
{
public:
    
    
    
    static QimiPlatform* shareQimiPlatform();
    bool initialize();
    
    /**
     * 平台初始化 QimiParamInfo对象里面保存appId, sId, appKey几个平台初始化必需要的参数
     */
    void setParamInfo(QimiParamInfo* pQimiParamInfo);
    /* 打开论坛的接口参数说明
     * 该接口可以在游戏中打开web网页
     * webUrl string 类型 网站网址。
     */
    void openGameWeb(std::string webUrl);
    
    /* 支付接口参数说明：
     * uId int类型 游戏的uId;
     * sId int类型 游戏的sId;
     * key string类型 游戏的key;
     * money int类型 需要支付的初始费用，进入支付系统后，可以再修改;
     */
    void openPayDailog(std::string uId, int sId, std::string key ,int money);
    
    /* 提示窗口
     * msg std::string 系统提示信息显示内容；
     * title 弹窗标题
     */
    void openAlertDailog(std::string title, std::string msg);
    
    /*
     * 获取用户id,uId;
     */
    int getUserId();
    
    /**
     * 登录和注册奇米平台
     */
    void QimiRegister();
    void QimiLogin();
    
    /*打开奇米论坛方法*/
    void QimiOpenGameForum(int fid);
    
    /**
     注册和登录接口
     回调参数是CCString .登录和注册成功回调为字符串“1”，失败则返回的是服务器错误信息字符串型。
     */
    void QimiLogin(std::string userName, std::string pass, cocos2d::CCObject* target, cocos2d::SEL_CallFuncO call);
    void QimiRegister(std::string userName, std::string userPass, cocos2d::CCObject *target, cocos2d::SEL_CallFuncO call);
    /*存入游戏的KEY值*/
    void setQimiGameKey(std::string key){m_key = key;};
    /*存入游戏的UId*/
    void setQimiGameUId(std::string uID){m_uId = uID;};
    /*存入游戏的sId*/
    void setQimiGameSId(int sID){m_sId = sID;};
    /*存入游戏的appId*/
    void setQimiGameAppId(int appId){m_appid = appId;};
    /*退出登录*/
    void loginOut();
    /*检测是否已登录*/
    bool isLogined();
    
    /*获得游戏的KEY值*/
    std::string getQimiGameKey(){ return m_key;};
    /*获得游戏的UId*/
    std::string getQimiGameUId(){return m_uId;};
    /*获得游戏的sId*/
    int getQimiGameSId(){return m_sId;};
    /*获得游戏的appId*/
    int getQimiGameAppId(){return m_appid;};
    
    //qimi
    QimiUserModel* getQimiUserModel(){return m_pQimiUserModel;};
    
    void setQimiUserModel(QimiUserModel* model){m_pQimiUserModel = model;};
    
    //回调函数 1.支付回调 2.登录回调 3.注册回调
    
    void registerPayCallBack(cocos2d::CCObject* target, cocos2d::SEL_CallFuncO call);
    void registerLoginCallBack(cocos2d::CCObject* target, cocos2d::SEL_CallFuncO call);
    void registerRegCallBack(cocos2d::CCObject* target, cocos2d::SEL_CallFuncO call);
    
    void callPayBack(cocos2d::CCObject* obj);
    void callLoginBack(cocos2d::CCObject* obj);
    void callRegBack(cocos2d::CCObject* obj);
    
    void callLoginAPIBack(cocos2d::CCObject* obj);//调用登录接口的回调
    void callRegAPIBack(cocos2d::CCObject* obj);//调用注册接口回调
    CC_GAME_GET_SET(std::string, m_appScheme, AppScheme);
    
private:
    QimiPlatformIOS*     m_pQimiPlatformIOS;
    QimiPlatformAndroid* m_pQimiPlatformAndroid;
    QimiUserModel*       m_pQimiUserModel;
    std::string          m_key; //游戏的KEY值
    std::string          m_uId; //uid
    std::string          m_appScheme;//游戏scheme
    int                  m_sId; //用户ID
    int                  m_appid; //游戏的APPID
    
    cocos2d::CCObject* m_LoginTarget;
    cocos2d::SEL_CallFuncO m_LoginCall;
    
    cocos2d::CCObject* m_RegTarget;
    cocos2d::SEL_CallFuncO m_RegCall;
    
    cocos2d::CCObject* m_PayTarget;
    cocos2d::SEL_CallFuncO m_payCall;
    
    cocos2d::CCObject* m_LoginAPITarget;
    cocos2d::SEL_CallFuncO m_LoginAPICall;
    
    cocos2d::CCObject *m_regAPITarget;
    cocos2d::SEL_CallFuncO m_regAPICall;
    
private:
    bool isCheckAppId();//检查是否获得APP ID
    bool isCheckAppKey();//检查是否已获得APP KEY
    
    void qimiUserLogin(std::string username, std::string pass);
    void loginSucceed(cocos2d::extension::CCHttpClient *sender, cocos2d::extension::CCHttpResponse *response);
    
    void qimiRegister(std::string userName, std::string usePass);
    void registerSucceed(cocos2d::extension::CCHttpClient *sender, cocos2d::extension::CCHttpResponse *response);
};

#endif /* defined(__Pay__QimiPlatform__) */
