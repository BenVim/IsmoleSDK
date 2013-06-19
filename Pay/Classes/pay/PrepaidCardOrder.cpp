//
//  PrepaidCardOrder.cpp
//  Pay
//
//  Created by Ben on 5/10/13.
//
//

#include "PrepaidCardOrder.h"


PrepaidCardOrder::PrepaidCardOrder()
{
    
}
PrepaidCardOrder::~PrepaidCardOrder()
{
    
}

PrepaidCardOrder* PrepaidCardOrder::create()
{
    PrepaidCardOrder* pRet = new PrepaidCardOrder();
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

bool PrepaidCardOrder::init()
{
    
    return true;
}