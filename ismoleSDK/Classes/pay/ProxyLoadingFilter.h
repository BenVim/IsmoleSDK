//
//  ProxyLoadingFilter.h
//  Sangou
//
//  Created by  ismole04 on 12-12-5.
//
//

#ifndef __Sangou__ProxyLoadingFilter__
#define __Sangou__ProxyLoadingFilter__

#include "ProxyFilter.h"
#include "GameCCBLoader.h"

class ProxyLoadingFilter : public ProxyFilter
{
public:
    ProxyLoadingFilter();
    virtual void filter(ProxyStatus status, Proxy *pProxy);
    CREATE_FUNC(ProxyLoadingFilter);
    
private:
    cocos2d::CCLayerColor *m_pLoadingMaskLayer;
    LoadingView* m_pLoadingView;
    int m_nWaitRequestCount;
};

#endif /* defined(__Sangou__ProxyLoadingFilter__) */
