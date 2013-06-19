//
//  GameCCBLoader.h
//  SanguoX
//
//  Created by  ismole04 on 12-12-18.
//
//

#ifndef __Navigations__GameCCBLoader__
#define __Navigations__GameCCBLoader__

#include "cocos2d.h"
#include "cocos-ext.h"


#include "PayView.h"
#include "PayZhifubaoView.h"
#include "PayHelpView.h"
#include "PrepaidCardView.h"
#include "PrepaidCardNextStepView.h"
#include "GameUIMaskLayer.h"
#include "LoadingView.h"
#include "GameUIBigMaskLayer.h"
#include "LoginView.h"
#include "RegisterView.h"



class GameCCBLoader
{
public:
    static GameCCBLoader* sharedLoader();
    
    GameCCBLoader();
    ~GameCCBLoader();
    
    void init();
    template <class T>
    T *createCCBNode(std::string ccbiFileName)
    {
        cocos2d::extension::CCBReader *pReader = new cocos2d::extension::CCBReader(GameCCBLoader::sharedLoader()->getLibrary());
        T *pResult = (T*)pReader->readNodeGraphFromFile(ccbiFileName.c_str());
        pReader->release();
        return pResult;
    }
    
    cocos2d::extension::CCNodeLoaderLibrary *getLibrary()
    {
        return m_pLibrary;
    }
    
private:
    cocos2d::extension::CCNodeLoaderLibrary *m_pLibrary;
};

#endif /* defined(__SanguoX__GameCCBLoader__) */
