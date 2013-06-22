//
//  PrepaidCardOrder.h
//  Pay
//
//  Created by Ben on 5/10/13.
//
//

#ifndef __Pay__PrepaidCardOrder__
#define __Pay__PrepaidCardOrder__

#include <iostream>
#include "cocos2d.h"
#include "Qimi.h"

USING_NS_CC;

class PrepaidCardOrder : public cocos2d::CCObject
{
public:
    PrepaidCardOrder();
    ~PrepaidCardOrder();

    static PrepaidCardOrder* create();
    bool init();
    
    CC_GAME_GET_SET(int, m_version, Version);
    CC_GAME_GET_SET(std::string, m_merId, MerId);
    CC_GAME_GET_SET(int, m_payMoney, PayMoney);
    
    CC_GAME_GET_SET(std::string, m_orderId, OrderId);
    CC_GAME_GET_SET(std::string, m_returnUrl, ReturnUrl);
    CC_GAME_GET_SET(std::string, m_cardInfo, CardInfo);
    CC_GAME_GET_SET(std::string, m_merUserName, MerUserName);
    CC_GAME_GET_SET(std::string, m_merUserMail, MerUserMail);
    CC_GAME_GET_SET(std::string, m_privateField, PrivateField);
    CC_GAME_GET_SET(int, m_verifyType, VerifyType);
    CC_GAME_GET_SET(int, m_cardTypeCombine, CardTypeCombine);
    CC_GAME_GET_SET(std::string, m_md5String, Md5String);

    
private:
    int m_version;//版本号
    std::string m_merId;//商户ID
    int m_payMoney;//支付金额 单位:分
    std::string m_orderId;//订单号
    std::string m_returnUrl; //服务器返回地址..
    std::string m_cardInfo;//充值卡加密信息
    std::string m_merUserName;//支付用户名
    std::string m_merUserMail;//支付用户邮箱
    std::string m_privateField;//商户私有数据
    int m_verifyType;//数据校验方式 固定传1
    int m_cardTypeCombine;//充值卡类型 数字 0:移动;1:联通;2:电信
    std::string m_md5String;//MD5 校验串
};

#endif /* defined(__Pay__PrepaidCardOrder__) */
