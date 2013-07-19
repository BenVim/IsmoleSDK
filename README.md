IsmoleSDK
=========
- QimiSDK接口概述
- QimiSDK初始化
- QimiSDK平台用户注册
- QimiSDK平台用户登录
- QimiSDK调用平台支付接口
- QimiSDK调用应用内论坛接口
- QimiSDK调用系统aleart接口
- QimiSDK获取平台登录用户信息数据

===========

####接口概述

    /**
     * 平台初始化 QimiParamInfo对象里面保存appId, sId, appKey几个平台初始化必需要的参数
     */
    void setParamInfo(QimiParamInfo* pQimiParamInfo);

    /*
     * forumId int类型。论坛版块ID。
     */
    void QimiOpenGameForum(int forumId)

    /* 打开论坛的接口参数说明
     * 该接口可以在游戏中打开web网页
     * webUrl string 类型 网站网址。
     * isfullScene bool 是否显以全屏显示网页。true.全屏，否则不全屏。
     */
    void openGameWeb(std::string webUrl , bool isfullScene);
    
    /* 支付接口参数说明：
     * uId std::string类型 游戏用户的Id;
     * sId int类型 游戏服务器的Id;
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
    QimiParamInfo* paramInfo = QimiParamInfo::create(2, 150, "7a92bba4670dddd479c5514720c1cf46aab");
    QimiPlatform::shareQimiPlatform()->setParamInfo(paramInfo);

    QimiPlatform初始化方法如上所示， 创建QimiParamInfo对象，QimiParamInfo对象所需要的三个值是平台赋于应用的关键三个参数。appId是平台方对应用的唯一值，sId是该用对应的服务器ID值。appkey是该应用唯一的KEY。APP应用在平台注册后由平台方提供该参数。

    QimiPlatform初始化必须调用setParamInfo()方法。把QimiParamInfo对象的关键参数赋给平台。初始化完成后才可以进行其它的注册、登录、支付等相关操作。

#####QimiSDK平台用户注册
	/**平台注册接口**/
	void QimiRegister();

	/**调用方法**/
	QimiPlatform::shareQimiPlatform()->QimiRegister();
	如上所示便可以打开平台注册页面。注册完成后服务器返回的数据会填充 QimiUserModel对象（QimiUserModel对象是用户数据MODEL，后面有详细描述或参加源代码）。

#####QimiSDK平台用户登录
    /**用户登录接口**/
    void QimiLogin();

    /**使用方法**/
    QimiPlatform::shareQimiPlatform()->QimiLogin();
    调用以上方法打开平台登录界面。登录成功数据填充QimiUserModel对象（QimiUserModel对象是用户数据MODEL，后面有详细描述或参加源代码）。

#####QimiSDK调用平台支付接口
	/* 支付接口参数说明：
     * uId std::string 类型 游戏的用户Id;
     * sId int类型 游戏服务器Id;
     * key string类型 游戏的key;
     * money int类型 需要支付的初始费用（单位：元），进入支付系统后，可以再修改;
     */
    void openPayDailog(std::string uId, int sId, std::string key ,int money);

    /**使用方法**/
    QimiPlatform::shareQimiPlatform()->openPayDailog(1, 5, "7a92bba467dd0d479c5514720c1cf46aab", 10);

#####QimiSDK调用应用内论坛接口
	/* 打开论坛的接口参数说明
     * 该接口可以在游戏中打开web网页
     * webUrl string 类型 网站网址。
     */
    void openGameWeb(std::string webUrl);

     /**使用方法**/
    QimiPlatform::shareQimiPlatform()->openGameWeb("http://bbs.qimi.com/forum.php");
    应用内显示论坛。

#####QimiSDK调用系统aleart接
	/* 提示窗口
     * msg std::string 系统提示信息显示内容；
     * title 弹窗标题
     */
    void openAlertDailog(std::string title, std::string msg);

     /**使用方法**/
    QimiPlatform::shareQimiPlatform()->openAlertDailog("系统提示", "这是一个设备系统提示窗口！");
    
#####QimiSDK获取平台登录用户信息数据
	QimiUserModel* getQimiUserModel();

	/**使用方法**/
	QimiPlatform::shareQimiPlatform()->getQimiUserModel();

#####QimiSDK登录接口
	/**
	* userName 用户名
	* pass 密码
	* target 回调注册traget
	* call 回调函数指针 不需要回调target和call设置为NULL
	* 回调函数返回的类型 成功则返回的是CCString类型 value:"1"则为成功 登录失败则返回的错误提示：例如“用户名不正确！”
	*/
	void QimiLogin(std::string userName, std::string pass, cocos2d::CCObject* target, cocos2d::SEL_CallFuncO call);
	














