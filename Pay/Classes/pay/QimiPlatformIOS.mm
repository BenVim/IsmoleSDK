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
    NSString* url = [NSString stringWithFormat:@"%s", webUrl.c_str()];
    CGRect webFrame = CGRectMake(0, 0, 320, 480);
    WebView* web = [[WebView alloc]initWithFrame:webFrame];
    [[EAGLView sharedEGLView] addSubview:web];
    [web openWeb:url];
}

void QimiPlatformIOS::openAlert(std::string title, std::string msg)
{
    NSString* stitle   = [NSString stringWithFormat:@"%s", title.c_str()];
    [stitle cStringUsingEncoding:NSUTF8StringEncoding];
    NSString* message = [NSString stringWithFormat:@"%s", msg.c_str()];
    UIAlertView* alert = [[UIAlertView alloc]initWithTitle:stitle
                                                   message:message
                                                  delegate:nil
                                         cancelButtonTitle:@"确定"
                                         otherButtonTitles:nil, nil];
    [alert show];
}

