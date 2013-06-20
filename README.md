IsmoleSDK
=========

###接口概述

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
    void openPayDailog(int uId, int sId, std::string key ,int money);
    
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
    
    /*存入游戏的KEY值*/
    void setQimiGameKey(std::string key){m_key = key;};
    /*存入游戏的UId*/
    void setQimiGameUId(int uID){m_uId = uID;};
    /*存入游戏的sId*/
    void setQimiGameSId(int sID){m_sId = sID;};
    /*存入游戏的appId*/
    void setQimiGameAppId(int appId){m_appid = appId;};
    /*退出登录*/
    void loginOut();

    /*检测是否已登录 返回值为false则没有登录*/
    bool isLogined();
    
    
    /*获得游戏的KEY值*/
    std::string getQimiGameKey(){ return m_key;};
    /*获得游戏的UId*/
    int getQimiGameUId(){return m_uId;};
    /*获得游戏的sId*/
    int getQimiGameSId(){return m_sId;};
    /*获得游戏的appId*/
    int getQimiGameAppId(){return m_appid;};
    
    //qimi 登录的用户数据MODEL
    QimiUserModel* getQimiUserModel(){return m_pQimiUserModel;};
    void setQimiUserModel(QimiUserModel* model){m_pQimiUserModel = model;};
    

####QimiSDK初始化

	/*平台调用方式*/
    /* QimiParamInfo::create(int appId, int sId, std::string appKey);
     * appId 应用ID
     * sId 
     * appkey
     */
    QimiParamInfo* paramInfo = QimiParamInfo::create(21, 15, "7a92bba4670d479c5514720c1cf46aab");
    QimiPlatform::shareQimiPlatform()->setParamInfo(paramInfo);

    QimiPlatform初始化方法如上所示， 创建QimiParamInfo对象，QimiParamInfo对象所需要的三个值是平台赋于应用的关键三个参数。appId是平台方对应用的唯一值，sId是该用对应的服务器ID值。appkey是该应用唯一的KEY。APP应用在平台注册后由平台方提供该参数。

    QimiPlatform初始化必须调用setParamInfo()方法。把QimiParamInfo对象的关键参数赋给平台。初始化完成后才可以进行其它的注册、登录、支付等相关操作。

#####QimiSDK注册
	/**平台注册**/
	void QimiRegister();

	/**调用方法**/
	QimiPlatform::shareQimiPlatform()->QimiRegister();
	如上所示便可以打开平台注册页面。注册完成后服务器返回的数据会填充 QimiUserModel对象（QimiUserModel对象是用户数据MODEL，后面有详细描述或参加源代码）。
	返回的数据如下所示：
	{   
   "data": {      
      "user": {         
         "uid": 22,         
         "name": "test22",         
         "avatar": "http://dev.ismole.com/fish/qimi/www/static/images/sysavatar/default_male.png",         
         "sex": 1,         
         "email": "test22@ismole.com",         
         "level": 1,         
         "score": 0,         
         "vip_level": 0,         
         "vip_privilege": 0,         
         "birthday": 19800101,         
         "regdata": 1340781448,         
         "experience": 0
      },      
      "session_key": "ElUe+DqcmYOI9GS+hM7a5f1UqmQsCVpOiYssHcyPfug="
   },   
   "status": 100,   
   "method": "User.reg"
}













