//
//  ProxyFilter.cpp
//  SanguoX
//
//  Created by  ismole04 on 12-12-19.
//
//

#include "ProxyFilter.h"

#include "SingleProxy.h"
#include "MultiProxy.h"

bool ProxyFilter::isSingleProxy(Proxy *pProxy)
{
    return (dynamic_cast<SingleProxy *>(pProxy) != NULL);
}

bool ProxyFilter::isMultiProxy(Proxy *pProxy)
{
    return (dynamic_cast<MultiProxy *>(pProxy) != NULL);
}
