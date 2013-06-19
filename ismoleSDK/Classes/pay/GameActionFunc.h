//
//  GameActionFunc.h
//  CocosDragonJS
//
//  Created by brucex on 13-1-28.
//
//

#ifndef CocosDragonJS_GameActionFunc_h
#define CocosDragonJS_GameActionFunc_h

typedef void (cocos2d::CCObject::*SEL_ActionFunc)(std::string actionType, cocos2d::CCObject *pData);

#define actionfunc_selector(_SELECTOR) (SEL_ActionFunc)(&_SELECTOR)


#endif
