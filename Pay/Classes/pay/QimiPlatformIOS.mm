//
//  QimiPlatformIOS.cpp
//  Pay
//
//  Created by Ben on 6/18/13.
//
//

#include "QimiPlatformIOS.h"

#import "WebView.h"
#import "EAGLView.h"
#import "AlixPayOrder.h"
#import "AlixPayResult.h"
#import "AlixPay.h"
#import "DataSigner.h"
#import "RSADataSigner.h"

QimiPlatformIOS* QimiPlatformIOS::create()
{
    QimiPlatformIOS* pRet = new QimiPlatformIOS();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool QimiPlatformIOS::init()
{
    
    return true;
}

void QimiPlatformIOS::openWeb(std::string webUrl)
{
    NSString* url   = [NSString stringWithFormat:@"%s", webUrl.c_str()];
    CGRect webFrame = CGRectMake(0, 0, 320, 480);
    WebView* web    = [[WebView alloc]initWithFrame:webFrame];
    
    [[EAGLView sharedEGLView] addSubview:web];
    [web openWeb:url];
}

void QimiPlatformIOS::openAlert(std::string title, std::string msg)
{
    NSString* stitle    = [NSString stringWithUTF8String:title.c_str()];
    NSString* message   = [NSString stringWithUTF8String:msg.c_str()];
    
                         
    UIAlertView* alert  = [[UIAlertView alloc]initWithTitle:stitle
                                                   message:message
                                                  delegate:nil
                                         cancelButtonTitle:@"确定"
                                         otherButtonTitles:nil, nil];
    [alert show];
}

void QimiPlatformIOS::alipayPay(std::string order,
                                float price,
                                std::string product,
                                std::string productDes,
                                std::string appScheme,
                                std::string parent,
                                std::string seller,
                                std::string notifyUrl,
                                std::string alipayKey)
{
    /*
     *生成订单信息及签名
     */
	//将商品信息赋予AlixPayOrder的成员变量
    NSString* m_parent              = [NSString stringWithUTF8String:parent.c_str()];                   //@"2088801319828435";
    NSString* m_seller              = [NSString stringWithUTF8String:seller.c_str()];                   //@"mobile@ismole.com";
    NSString* m_productName         = [NSString stringWithUTF8String:product.c_str()];                  //产品名称
    NSString* m_productDescription  = [NSString stringWithUTF8String:productDes.c_str()];               //产品描述
    CGFloat m_price                 = price;                                                            //价格
    NSString* m_pOrder              = [NSString stringWithUTF8String:order.c_str()];                    //订单号
    NSString* m_appScheme           = [NSString stringWithUTF8String:appScheme.c_str()];                //游戏Scheme;应用注册scheme
                                                                                                        //在AlixPayDemo-Info.plist定义URL types
                                                                                                        //用于安全支付成功后重新唤起商户应用
	AlixPayOrder *m_order = [[AlixPayOrder alloc] init];
    
    
	m_order.partner = m_parent;
	m_order.seller = m_seller;
	m_order.tradeNO = m_pOrder;                                           //订单ID
    
	m_order.productName = m_productName;                                  //商品标题
	m_order.productDescription = m_productDescription;                    //商品描述
	m_order.amount = [NSString stringWithFormat:@"%.2f",m_price];         //商品价格
	m_order.notifyURL = [NSString stringWithUTF8String:notifyUrl.c_str()];// @"http://www.baidu.com";                         //回调URL
    
    //应用注册scheme,在AlixPayDemo-Info.plist定义URL types,用于安全支付成功后重新唤起商户应用
	//将商品信息拼接成字符串
	NSString *orderSpec = [m_order description];
    id signer = [[RSADataSigner alloc] initWithPrivateKey:[NSString stringWithUTF8String:alipayKey.c_str()]];
    NSString *signedString = [signer signString:orderSpec];
    
	//将签名成功字符串格式化为订单字符串,请严格按照该格式
	NSString *orderString = nil;
	if (signedString != nil) {
		orderString = [NSString stringWithFormat:@"%@&sign=\"%@\"&sign_type=\"%@\"",
                       orderSpec, signedString, @"RSA"];
        
        NSLog(@"orderString =%@", orderString);
        //获取安全支付单例并调用安全支付接口
        AlixPay * alixpay = [AlixPay shared];
        int ret = [alixpay pay:orderString applicationScheme:m_appScheme];
        if (ret == kSPErrorAlipayClientNotInstalled) {
            //NSLog(@"您还没有安装支付宝快捷支付，请先安装。");
            UIAlertView* alert = [[UIAlertView alloc] initWithTitle:@"提示"
                                                            message:@"您还没有安装支付宝快捷支付，请先安装。"
                                                           delegate:nil
                                                  cancelButtonTitle:@"OK"
                                                  otherButtonTitles:nil, nil];
            [alert show];
            [alert release];
        }
        else if (ret == kSPErrorSignError) {
            NSLog(@"签名错误！");
        }
	}
    //CCLog("支付宝 money %d", price);
}

/*
 @"MIICdgIBADANBgkqhkiG9w0BAQEFAASCAmAwggJcAgEAAoGBANktWYPcmg3+npGv4u9Q2m907PtYgzcq1mlBX2Ba/AM2FzWTLtG4OKpWVK+2Ot/cYJDBCquI14fIWlAgdcc3TtfKoyUMzfQdANRhGVLECYfJYFZk1Yyc1lQfnGZqxyNwZlW1LKk6c7vUruG8fBUAckrR37JTs4UKhP9ccBE8EMmfAgMBAAECgYBDHi7R/7VkqdIbuD3sNBKt63bp3tr+i7Cj6t4tCzFjVK4rkocfrU1l5zRY8XqUgKkfU2mWxb3GavbuWHnNzZwBpuv32z2kBkq0UjMhW6YfDt2KzUQocD+EbSDBIlm6/GlQG4BM/IzKgWqqiXHakZWbzCIibIWRto53t4RIZ0CgEQJBAPa2K97VLBNEMPIsHSDrrqOds3ff5yFPBrHjvQ2kvMHhjUMLewF5UO0WVrVA+J5YLiya6UpCtBpswTRqJZmwojsCQQDhWoXEDzAWSpJvNiuQ+Q70NLl9UMfhzshnDtwIvgbY7tjQ+JoGzWHnGcuDcl7ZQ8eI2yMy2QNXr4I1Hh0JBTvtAkAramGMBD2OYmiupV625WLFPkJP7SISdYK7GVWyqfPhtpySWNnbp4q7PjwiB33495Ggnd5CCD0DjXHulGNriW7zAkEAtMvuU8ynlMrBTu4T59yZbb07L9n2cyh2SZB3YaArWDHPy2AYGur95+4fA9dnV0H0vMyrIalP8DKD8V+2hb0oRQJAfooBEw23HOsCXffqEJpzaPzwaartfqPkIkCPtqC12I5mAokx1EwfZZWo+Kue3Il3ONSkvqmCDCcRUB2F2mgpSQ==
 */



