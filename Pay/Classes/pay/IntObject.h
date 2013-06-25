//
//  IntObject.h
//  MusicNinja
//
//  Created by bruce on 12-8-7.
//
//

#ifndef MusicNinja_IntObject_h
#define MusicNinja_IntObject_h

#include "cocos2d.h"
#include "Json.h"

class IntObject : public cocos2d::CCObject
{
public:
    IntObject(int value) : m_nValue(value),m_pObj(NULL)
    { }
    ~IntObject(){ CC_SAFE_RELEASE_NULL(m_pObj); };
    
    operator int()
    {
        return m_nValue;
    }
    
    int getValue()
    {
        return m_nValue;
    }
    
    static IntObject* create(int value)
    {
        IntObject* pRet = new IntObject(value);
        if (pRet && pRet->init(value))
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
    
    bool init(int value)
    {
        return true;
    }

    
    void setObject(CCObject* pObj){ CC_SAFE_RELEASE_NULL(m_pObj); m_pObj = pObj; m_pObj->retain(); };
    CCObject* getObject(){ return m_pObj; };
    
    CC_GAME_GET_SET(bool, m_nValuebool, ValueBool);
    CC_GAME_GET_SET(Json::Value, m_data, Data);
    
    void setValue2(int value){m_nValue2 = value;};
    int getValue2(){return m_nValue2;};
    
    void setValue3(int value){m_nValue3 = value;};
    int getValue3(){return m_nValue3;};
    
    cocos2d::SEL_CallFuncO getCallFuncO(){return m_call;};
    void setCallFuncO(cocos2d::SEL_CallFuncO call){m_call = call;};
    
public:
    int m_nValue;
    int m_nValue2;
    int m_nValue3;
    bool m_nValuebool;
    cocos2d::CCObject* m_pObj;
    cocos2d::SEL_CallFuncO m_call;
    Json::Value m_data;

};

#endif
