//
//  QimiAlipayDailog.h
//  Pay
//
//  Created by Ben on 7/5/13.
//
//

#ifndef __Pay__QimiAlipayDailog__
#define __Pay__QimiAlipayDailog__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "json.h"

USING_NS_CC;
USING_NS_CC_EXT;

class QimiAlipayDailog : public cocos2d::CCLayer
{
public:
    QimiAlipayDailog();
    ~QimiAlipayDailog();
    CREATE_FUNC(QimiAlipayDailog);
    bool init();
    void initView();
private:
    CCControlButton* m_pQimiSussfulBtn;
    CCControlButton* m_pQimiFaildBtn;
    
private:
    void paySucssfuly(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void backOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    
    
};

#endif /* defined(__Pay__QimiAlipayDailog__) */
