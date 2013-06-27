//
//  TipView.h
//  Navigations
//
//  Created by Ben on 6/3/13.
//
//

#ifndef __Navigations__TipView__
#define __Navigations__TipView__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class TipView : public cocos2d::CCNode
{
public:
    TipView();
    ~TipView();
    static TipView* create(const char* msg, CCNode* parent, CCPoint pt, float daleyTimer, bool bIsFadeOut);
    bool init(const char* msg, CCNode* parent, CCPoint pt, float daleyTimer, bool bIsFadeOut);

private:
    cocos2d::CCLabelTTF* m_label;
    std::string m_msg;
    CCNode* m_parent;
    CCNode* m_pContainer;
    CCPoint m_pt;
    float m_daleyTimer;
    bool m_bIsFadeOut;
    
private:
    void show();
    
    void onActionEnd();
    
    
};

#endif /* defined(__Navigations__TipView__) */
