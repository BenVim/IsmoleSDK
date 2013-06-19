//
//  PayZhifubaoView.cpp
//  Navigations
//
//  Created by Ben on 5/7/13.
//
//

#include "PayZhifubaoView.h"
#include "GameCCBLoader.h"
#include "StageScene.h"
#include "stdio.h"

#include "ProxyFilterManager.h"
#include "ProxyLoadingFilter.h"
#include "Proxy.h"
#include "GameUtils.h"

#import "AlixPayOrder.h"
#import "AlixPayResult.h"
#import "AlixPay.h"
#import "DataSigner.h"
#import "EAGLView.h"
#import "RSADataSigner.h"
#import "WebView.h"


PayZhifubaoView::PayZhifubaoView():
m_pBackBtn(NULL),
m_pBtnCongzhi(NULL),
m_pMcashNumTxt(NULL),
m_pMcashNumBackTxt(NULL),
m_pCCEditBoxCCNode(NULL),
m_pInputTxtBg(NULL),
m_pBtn10Select(NULL),
m_pBtn20Select(NULL),
m_pBtn30Select(NULL),
m_pBtn50Select(NULL),
m_pBtn100Select(NULL),
m_pBtn300Select(NULL),
m_pBtn500Select(NULL)
{
    
}

PayZhifubaoView::~PayZhifubaoView()
{
    CC_SAFE_RELEASE(m_pBackBtn);
    CC_SAFE_RELEASE(m_pBtnCongzhi);
    CC_SAFE_RELEASE(m_pMcashNumTxt);
    CC_SAFE_RELEASE(m_pMcashNumBackTxt);
    CC_SAFE_RELEASE(m_pCCEditBoxCCNode);
    CC_SAFE_RELEASE(m_pInputTxtBg);
    CC_SAFE_RELEASE(m_pBtn10Select);
    CC_SAFE_RELEASE(m_pBtn20Select);
    CC_SAFE_RELEASE(m_pBtn30Select);
    CC_SAFE_RELEASE(m_pBtn50Select);
    CC_SAFE_RELEASE(m_pBtn100Select);
    CC_SAFE_RELEASE(m_pBtn300Select);
    CC_SAFE_RELEASE(m_pBtn500Select);
    CC_SAFE_RELEASE(m_pButtonList);
}

cocos2d::SEL_MenuHandler PayZhifubaoView::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    return NULL;
}

cocos2d::extension::SEL_CCControlHandler PayZhifubaoView::onResolveCCBCCControlSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "backOnClickHandler:", PayZhifubaoView::backOnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "10SelectOnClickHandler:", PayZhifubaoView::select10OnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "20SelectOnClickHandler:", PayZhifubaoView::select20OnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "30SelectOnClickHandler:", PayZhifubaoView::select30OnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "50SelectOnClickHandler:", PayZhifubaoView::select50OnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "100SelectOnClickHandler:", PayZhifubaoView::select100OnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "300SelectOnClickHandler:", PayZhifubaoView::select300OnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "500SelectOnClickHandler:", PayZhifubaoView::select500OnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "rechargeOnClickHandler:", PayZhifubaoView::rechargeOnClick);
    return NULL;
}

bool PayZhifubaoView::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BackBtn:", cocos2d::extension::CCControlButton*, m_pBackBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BtnCongzhi:", cocos2d::extension::CCControlButton*, m_pBtnCongzhi);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "McashNumTxt:", cocos2d::CCLabelTTF*, m_pMcashNumTxt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "McashNumLastTxt:", cocos2d::CCLabelTTF*, m_pMcashNumBackTxt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "CCEditBoxCCNode:", cocos2d::CCNode*, m_pCCEditBoxCCNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "InputBgSprte:", cocos2d::extension::CCScale9Sprite*, m_pInputTxtBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Btn10Select:", CCControlButton*, m_pBtn10Select);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Btn20Select:",CCControlButton*, m_pBtn20Select);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Btn30Select:",CCControlButton*, m_pBtn30Select);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Btn50Select:",CCControlButton*, m_pBtn50Select);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Btn100Select:",CCControlButton*, m_pBtn100Select);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Btn300Select:",CCControlButton*, m_pBtn300Select);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Btn500Select:",CCControlButton*, m_pBtn500Select);
    
    return true;
}

void PayZhifubaoView::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    m_pBackBtn->setDefaultTouchPriority(-130);
    m_pBtnCongzhi->setDefaultTouchPriority(-130);
    m_pBtn10Select->setDefaultTouchPriority(-130);
    m_pBtn20Select->setDefaultTouchPriority(-130);
    m_pBtn30Select->setDefaultTouchPriority(-130);
    m_pBtn50Select->setDefaultTouchPriority(-130);
    m_pBtn100Select->setDefaultTouchPriority(-130);
    m_pBtn300Select->setDefaultTouchPriority(-130);
    m_pBtn500Select->setDefaultTouchPriority(-130);
    
    m_pButtonList = CCArray::create();
    m_pButtonList->retain();
    
    m_pButtonList->addObject(m_pBtn10Select);
    m_pButtonList->addObject(m_pBtn20Select);
    m_pButtonList->addObject(m_pBtn30Select);
    m_pButtonList->addObject(m_pBtn50Select);
    m_pButtonList->addObject(m_pBtn100Select);
    m_pButtonList->addObject(m_pBtn300Select);
    m_pButtonList->addObject(m_pBtn500Select);
    initView();
}

void PayZhifubaoView::initView()
{
    CCSize editBoxSize = CCSizeMake(200, 45);
    m_pInputTxtBg->removeFromParentAndCleanup(false);
    m_pEditName = CCEditBox::create(editBoxSize, m_pInputTxtBg);
    m_pEditName->setPosition(m_pCCEditBoxCCNode->getPosition());
    m_pEditName->setFontColor(ccc3(255, 0, 0));
    m_pEditName->setMaxLength(20);
    m_pEditName->setReturnType(kKeyboardReturnTypeDone);
    m_pEditName->setTouchPriority(-130);
    m_pEditName->setText("10");
    addChild(m_pEditName);
}

void PayZhifubaoView::initData(int uId, int sId, std::string key, int money)
{
    m_uId = uId;
    m_sId = sId;
    m_key = key;
    m_money = money;
    upDataView(money);
}


void PayZhifubaoView::select10OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    upDataView(10);
    upSelectState(0);
}
void PayZhifubaoView::select20OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    upDataView(20);
    upSelectState(1);
}
void PayZhifubaoView::select30OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    upDataView(30);
    upSelectState(2);
}
void PayZhifubaoView::select50OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    upDataView(50);
    upSelectState(3);
}
void PayZhifubaoView::select100OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    upDataView(100);
    upSelectState(4);
}
void PayZhifubaoView::select300OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    upDataView(300);
    upSelectState(5);
}
void PayZhifubaoView::select500OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    upDataView(500);
    upSelectState(6);
}

void PayZhifubaoView::upDataView(int pay)
{
    m_money = pay;
    m_pEditName->setText(CCString::createWithFormat("%d", pay)->getCString());
    m_pMcashNumTxt->setString(CCString::createWithFormat("%d", pay*10)->getCString());
    float posX = m_pMcashNumTxt->getPosition().x + m_pMcashNumTxt->getContentSize().width;
    float posY = m_pMcashNumTxt->getPosition().y;
    
    m_pMcashNumBackTxt->setPosition(ccp(posX, posY));
    
}

void PayZhifubaoView::upSelectState(int index)
{
    for (int i =0; i < m_pButtonList->count(); i++) {
        CCControlButton* btn = dynamic_cast<CCControlButton* >(m_pButtonList->objectAtIndex(i));
        if (index == i)
        {
            btn->setEnabled(false);
        }
        else
        {
            btn->setEnabled(true);
        }
    }
}


void PayZhifubaoView::onLoadOrderFided(Proxy* pro, ProxyEvent proxyEvent)
{
    Json::Value data = pro->getResponseData();
    if (!data.isNull())
    {
        std::string str = data["data"].asString();
        CCLog("..%s", str.c_str());
    }
}

void PayZhifubaoView::rechargeOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    m_money = atoi(m_pEditName->getText());
    CCHttpRequest* request = new CCHttpRequest();
    request->setUrl("http://www.qimi.com/platform/addOrder.php");
    request->setRequestType(CCHttpRequest::kHttpPost);
    request->setResponseCallback(this, callfuncND_selector(PayZhifubaoView::onLoadOrderSucssful));
    
    std::string sign = "e7d4b2571e2d1fd80c19a048b18a529e";//游戏参数传入的e7d4b2571e2d1fd80c19a048b18a529e
    std::string msign = GameUtils::getStringWithMd5(CCString::createWithFormat("%d%d%s",m_uId, m_sId, sign.c_str())->getCString());
    CCString* postDataStr = CCString::createWithFormat("uId=%d&sId=%d&sign=%s&money=%d&orderType=alipay&type=0", m_uId, m_sId, msign.c_str(), m_money);
    CCLog("addOrder string ===%s", postDataStr->getCString());
    const char* postData =postDataStr->getCString();// "visitor=cocos2d&TestSuite=Extensions Test/NetworkTest";
    request->setRequestData(postData, strlen(postData));
    
    request->setTag("POST test1");
    CCHttpClient::getInstance()->send(request);
    request->release();
    
}

void PayZhifubaoView::onLoadOrderSucssful(cocos2d::CCNode *sender, void *data)
{
    CCHttpResponse *response = (CCHttpResponse*)data;
    if (!response)
    {
        return;
    }
    
    // You can get original request type from: response->request->reqType
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        CCLog("%s completed", response->getHttpRequest()->getTag());
    }
    
    int statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    CCLog("response code: %d", statusCode);
    
    if (!response->isSucceed())
    {
        CCLog("response failed");
        CCLog("error buffer: %s", response->getErrorBuffer());
        return;
    }
    std::vector<char> *buffer = response->getResponseData();
    std::string responseData;
    char buff[24];
    printf("Http Test, dump data: ");
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        printf("%c", (*buffer)[i]);
        sprintf(buff, "%c", (*buffer)[i]);
        responseData.append(buff);
    }
    printf("\n");
    
    
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(responseData, root);
    if (!parsingSuccessful)
    {
        return;
    }
    m_oderId ="";
    if (!root.isNull())
    {
        m_oderId= root["data"].asString();
    }
    
    
    
    /*

    NSURL *url =[NSURL URLWithString:@"http://www.baidu.com"];
    NSURLRequest *request =[NSURLRequest requestWithURL:url];
    
    CGRect webFrame = CGRectMake(0, 0, 320, 480);
    UIWebView *webView = [[UIWebView alloc] initWithFrame:webFrame];
    [webView setBackgroundColor:[UIColor whiteColor]];//设置北京为白色
    webView.scalesPageToFit = YES;//适应屏幕大小
    [webView loadRequest:request];
    [[EAGLView sharedEGLView] addSubview:webView];
    
    UIToolbar *toolBar = [[[UIToolbar alloc] initWithFrame:CGRectMake(0.0f, 440.0f, 320.0f, 40.0f) ] autorelease];
    [[EAGLView sharedEGLView] addSubview:toolBar];
    
    //创建barbuttonitem
    UIBarButtonItem *item1 = [[[UIBarButtonItem alloc] initWithTitle:@"收藏" style:UIBarButtonItemStyleBordered target:self action:@selector(test:)] autorelease];
*/
   // loadAlixPay();
}

void PayZhifubaoView::loadAlixPay()
{
    /*
     *生成订单信息及签名
     *由于demo的局限性，本demo中的公私钥存放在AlixPayDemo-Info.plist中,外部商户可以存放在服务端或本地其他地方。
     */
	//将商品信息赋予AlixPayOrder的成员变量
	AlixPayOrder *order = [[AlixPayOrder alloc] init];
    
    NSString* m_parent = @"2088801319828435";//@"2088002207101335";//
    NSString* m_seller = @"mobile@ismole.com";//@"smoilbig@126.com";//
    
    NSString* m_productName = @"productName";
    NSString* m_productDescription = @"this is product Description!";
    CGFloat m_price = m_money;
	order.partner = m_parent;
	order.seller = m_seller;
	order.tradeNO = @"1111100000";//[NSString stringWithFormat:@"%s", m_oderId.c_str()];//订单ID（由商家自行制定）
    
	order.productName = m_productName;//商品标题
	order.productDescription = m_productDescription; //商品描述
	order.amount = [NSString stringWithFormat:@"%.2f",m_price]; //商品价格
	order.notifyURL =  @"http://www.baidu.com"; //回调URL
    
	//应用注册scheme,在AlixPayDemo-Info.plist定义URL types,用于安全支付成功后重新唤起商户应用
	NSString *appScheme = @"Pay";
	//将商品信息拼接成字符串
	NSString *orderSpec = [order description];//NSLog(@"orderSpec = %@",orderSpec);
	
	//获取私钥并将商户信息签名,外部商户可以根据情况存放私钥和签名,只需要遵循RSA签名规范,并将签名字符串base64编码和UrlEncode
    //id signer = [[RSADataSigner alloc] initWithPrivateKey:[[NSBundle mainBundle] objectForInfoDictionaryKey:@"RSA private key"]];
    id signer = [[RSADataSigner alloc] initWithPrivateKey:@"MIICdgIBADANBgkqhkiG9w0BAQEFAASCAmAwggJcAgEAAoGBANktWYPcmg3+npGv4u9Q2m907PtYgzcq1mlBX2Ba/AM2FzWTLtG4OKpWVK+2Ot/cYJDBCquI14fIWlAgdcc3TtfKoyUMzfQdANRhGVLECYfJYFZk1Yyc1lQfnGZqxyNwZlW1LKk6c7vUruG8fBUAckrR37JTs4UKhP9ccBE8EMmfAgMBAAECgYBDHi7R/7VkqdIbuD3sNBKt63bp3tr+i7Cj6t4tCzFjVK4rkocfrU1l5zRY8XqUgKkfU2mWxb3GavbuWHnNzZwBpuv32z2kBkq0UjMhW6YfDt2KzUQocD+EbSDBIlm6/GlQG4BM/IzKgWqqiXHakZWbzCIibIWRto53t4RIZ0CgEQJBAPa2K97VLBNEMPIsHSDrrqOds3ff5yFPBrHjvQ2kvMHhjUMLewF5UO0WVrVA+J5YLiya6UpCtBpswTRqJZmwojsCQQDhWoXEDzAWSpJvNiuQ+Q70NLl9UMfhzshnDtwIvgbY7tjQ+JoGzWHnGcuDcl7ZQ8eI2yMy2QNXr4I1Hh0JBTvtAkAramGMBD2OYmiupV625WLFPkJP7SISdYK7GVWyqfPhtpySWNnbp4q7PjwiB33495Ggnd5CCD0DjXHulGNriW7zAkEAtMvuU8ynlMrBTu4T59yZbb07L9n2cyh2SZB3YaArWDHPy2AYGur95+4fA9dnV0H0vMyrIalP8DKD8V+2hb0oRQJAfooBEw23HOsCXffqEJpzaPzwaartfqPkIkCPtqC12I5mAokx1EwfZZWo+Kue3Il3ONSkvqmCDCcRUB2F2mgpSQ=="
                 ];
    NSString *signedString = [signer signString:orderSpec];
    
	//将签名成功字符串格式化为订单字符串,请严格按照该格式
	NSString *orderString = nil;
	if (signedString != nil) {
		orderString = [NSString stringWithFormat:@"%@&sign=\"%@\"&sign_type=\"%@\"",
                       orderSpec, signedString, @"RSA"];
        
        NSLog(@"orderString =%@", orderString);
        //获取安全支付单例并调用安全支付接口
        AlixPay * alixpay = [AlixPay shared];
        int ret = [alixpay pay:orderString applicationScheme:appScheme]; 
        if (ret == kSPErrorAlipayClientNotInstalled) {
            NSLog(@"您还没有安装支付宝快捷支付，请先安装。");
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
    CCLog("支付宝 money %d", m_money);
}

void PayZhifubaoView::backOnClick(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent)
{
    PayView* pPayView = GameCCBLoader::sharedLoader()->createCCBNode<PayView>("PayView.ccbi");
    StageScene::shareStageScene()->m_DialogContainer->addChild(pPayView);
    pPayView->setPosition(ccp(0, 0));
    pPayView->initView(m_uId, m_sId, m_key, m_money);
    this->removeFromParentAndCleanup(true);
}