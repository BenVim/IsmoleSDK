//
//  QimiPlatform.h
//  Pay
//
//  Created by Ben on 6/18/13.
//
//

#ifndef __Pay__QimiPlatform__
#define __Pay__QimiPlatform__


#include "cocos2d.h"

class QimiPlatformIOS;
class QimiPlatformAndroid;

class QimiPlatform : public cocos2d::CCObject
{
public:
    static QimiPlatform* shareQimiPlatform();
    bool initialize();
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
    
    
private:
    QimiPlatformIOS*     m_pQimiPlatformIOS;
    QimiPlatformAndroid* m_pQimiPlatformAndroid;
    
    
    
};

#endif /* defined(__Pay__QimiPlatform__) */
