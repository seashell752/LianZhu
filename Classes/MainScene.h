#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

class Main : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of HelloWorldreturning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuNewGameCallback(cocos2d::Ref* pSender);
    void menuContinueCallback(cocos2d::Ref* pSender);
    void menuHowToPlayCallback(cocos2d::Ref* pSender);
    void menuRankCallback(cocos2d::Ref* pSender);
    void menuMoreGameCallback(cocos2d::Ref* pSender);
    void menuRemoveAdCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(Main);
};

#endif // __HELLOWORLD_SCENE_H__
