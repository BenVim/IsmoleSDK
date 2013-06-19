//
//  ProxyFilterManager.h
//  libs
//
//  Created by  brucex on 12-12-5.
//
//

#ifndef __Sangou__ProxyFilterManager__
#define __Sangou__ProxyFilterManager__

#include "cocos2d.h"
#include "ProxyFilter.h"

class ProxyFilterManager : public cocos2d::CCObject
{
public:
    static ProxyFilterManager* sharedFilterManger();
    
    ~ProxyFilterManager();

    ProxyFilterManager();

    void filter(ProxyStatus status, Proxy *pProxy);

    void addFilter(ProxyFilter *pFilter);
    void removeFilter(ProxyFilter *pFilter);

private:

    cocos2d::CCArray *m_pFilterList;
};

#endif /* defined(__Sangou__ProxyFilterManager__) */
