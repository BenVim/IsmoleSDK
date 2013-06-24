//
//  Qimi.h
//  Pay
//
//  Created by Ben on 6/22/13.
//
//

#ifndef __Pay__Qimi__
#define __Pay__Qimi__

#define QIMI_FORUM "http://www.qimi.com/index.php?mod=User&do=backPwd" //奇米论坛
#define QIMI_API "http://api.qimi.com/api.php"//AIP地址


#define CC_GAME_GET_SET(varType, varName, funName)\
public: varType get##funName(void){return varName;};\
public: void set##funName(varType value){varName = value;};

#define CC_GAME_JSON_ADD(data ,varType, varName, key, toValue) \
if (!data[key].isNull() && data[key].varType()) \
{\
varName = data[key].toValue();\
}


#endif /* defined(__Pay__Qimi__) */
