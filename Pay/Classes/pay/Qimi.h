//
//  Qimi.h
//  Pay
//
//  Created by Ben on 6/22/13.
//
//

#ifndef __Pay__Qimi__
#define __Pay__Qimi__

#define QIMI_ALIAPAY_SID "2088801319828435"
#define QIMI_ALIAPAY_USERNMAE "mobile@ismole.com"

#define QIMI_PRIVATE_KEY "MIICdgIBADANBgkqhkiG9w0BAQEFAASCAmAwggJcAgEAAoGBANktWYPcmg3+npGv4u9Q2m907PtYgzcq1mlBX2Ba/AM2FzWTLtG4OKpWVK+2Ot/cYJDBCquI14fIWlAgdcc3TtfKoyUMzfQdANRhGVLECYfJYFZk1Yyc1lQfnGZqxyNwZlW1LKk6c7vUruG8fBUAckrR37JTs4UKhP9ccBE8EMmfAgMBAAECgYBDHi7R/7VkqdIbuD3sNBKt63bp3tr+i7Cj6t4tCzFjVK4rkocfrU1l5zRY8XqUgKkfU2mWxb3GavbuWHnNzZwBpuv32z2kBkq0UjMhW6YfDt2KzUQocD+EbSDBIlm6/GlQG4BM/IzKgWqqiXHakZWbzCIibIWRto53t4RIZ0CgEQJBAPa2K97VLBNEMPIsHSDrrqOds3ff5yFPBrHjvQ2kvMHhjUMLewF5UO0WVrVA+J5YLiya6UpCtBpswTRqJZmwojsCQQDhWoXEDzAWSpJvNiuQ+Q70NLl9UMfhzshnDtwIvgbY7tjQ+JoGzWHnGcuDcl7ZQ8eI2yMy2QNXr4I1Hh0JBTvtAkAramGMBD2OYmiupV625WLFPkJP7SISdYK7GVWyqfPhtpySWNnbp4q7PjwiB33495Ggnd5CCD0DjXHulGNriW7zAkEAtMvuU8ynlMrBTu4T59yZbb07L9n2cyh2SZB3YaArWDHPy2AYGur95+4fA9dnV0H0vMyrIalP8DKD8V+2hb0oRQJAfooBEw23HOsCXffqEJpzaPzwaartfqPkIkCPtqC12I5mAokx1EwfZZWo+Kue3Il3ONSkvqmCDCcRUB2F2mgpSQ=="

#define QIMI_FORUM "http://bbs.qimi.com/forum.php?mod=forumdisplay&fid=52" //奇米论坛
#define QIMI_API "http://api.qimi.com/api.php"//AIP地址
#define QIMI_ALIAPLY_NOTIFY_URL "http://www.qimi.com/pay/alipaySj/notify_url.php" //支付宝回调地址
#define QIMI_CZ "http://www.qimi.com/ddxy/qimijiesh.html"//奇米充值地址
#define QIMI_FOGET "http://www.qimi.com/index.php?mod=User&do=backPwdNew" //找回密码
#define QIMI_HELP "http://www.qimi.com/ddxy/bangzhu.html" //帮助页面
#define QIMI_FROM_KEY "e7d4b2571e2d1fd80c19a048b18a529e"//登录论坛的KEY

#define CC_GAME_GET_SET(varType, varName, funName)\
public: varType get##funName(void){return varName;};\
public: void set##funName(varType value){varName = value;};

#define CC_GAME_JSON_ADD(data ,varType, varName, key, toValue) \
if (!data[key].isNull() && data[key].varType()) \
{\
varName = data[key].toValue();\
}


#endif /* defined(__Pay__Qimi__) */
