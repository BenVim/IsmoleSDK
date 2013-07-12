//
//  QimiPlatformIOS.h
//  Pay
//
//  Created by Ben on 6/18/13.
//
//

#ifndef __Pay__QimiPlatformIOS__
#define __Pay__QimiPlatformIOS__

#include <iostream>

#include "cocos2d.h"

USING_NS_CC;


class QimiPlatformIOS :public cocos2d::CCObject
{
public:
    static QimiPlatformIOS* create();
    bool init();
    
    void openWeb(std::string url);
    void openAlert(std::string title, std::string msg);
    
    void alipayPay(std::string order, //订单号
                   float price, //支付金额
                   std::string product, //产品名称
                   std::string productDes, //产品描述
                   std::string appScheme, //应用切换的scheme
                   std::string parent, //商家支付宝帐号ID
                   std::string seller, //商家支付宝帐号
                   std::string notifyUrl, //支付成功的回调地址
                   std::string alipayKey); //商家支付宝密钥
    std::string getDeviceId();//获取设备ID
    
private:
    

};



#endif /* defined(__Pay__QimiPlatformIOS__) */
