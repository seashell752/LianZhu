#include "MainScene.h"
#include "GameMainScene.h"

USING_NS_CC;

Scene* Main::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Main::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Main::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(Main::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto closeMenu = Menu::create(closeItem, NULL);
    closeMenu->setPosition(Vec2::ZERO);
    this->addChild(closeMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("海底连珠", "Arial", 70);
    //auto label = Label::createWithSystemFont("海底连珠", "海底连珠2", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add background
    auto bg = Sprite::create("background.png");

	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	bg->setScale(visibleSize.width / bg->getContentSize().width, visibleSize.height / bg->getContentSize().height);
	this->addChild(bg, 0);
    
    CCLOG("visibleSize.width = %f",visibleSize.width);
    CCLOG("visibleSize.height = %f",visibleSize.height);
    CCLOG("origin.x = %f",origin.x);
    CCLOG("origin.y = %f",origin.y);

    MenuItemFont::setFontSize(60);
    //MenuItemFont::setFontName(const std::string &name)
    auto menu1 = MenuItemFont::create("新游戏", CC_CALLBACK_1(Main::menuNewGameCallback, this));
    auto menu2 = MenuItemFont::create("继续", CC_CALLBACK_1(Main::menuContinueCallback, this));
    auto menu3 = MenuItemFont::create("如何玩", CC_CALLBACK_1(Main::menuHowToPlayCallback, this));
    auto menu4 = MenuItemFont::create("排行榜", CC_CALLBACK_1(Main::menuRankCallback, this));
    auto menu5 = MenuItemFont::create("更多游戏", CC_CALLBACK_1(Main::menuMoreGameCallback, this));
    auto menu6 = MenuItemFont::create("去掉广告", CC_CALLBACK_1(Main::menuRemoveAdCallback, this));
    
    auto s = Director::getInstance()->getWinSize();
    auto mainMenu = Menu::create(menu1, menu2, menu3, menu4, menu5, menu6, nullptr);
    mainMenu->alignItemsVertically();
    mainMenu->setPosition(Vec2(s.width/2, s.height/2));
    addChild(mainMenu);
    //mainMenu->setScale(1);
    //mainMenu->runAction(ScaleTo::create(1,1));

    return true;
}

void Main::menuNewGameCallback(Ref* pSender){
    
    //Director::getInstance()->replaceScene(GameMain::createScene());
    //auto transition = TransitionZoomFlipY::create(1.0f,GameMain::createScene());
    auto transition = TransitionFade::create(0.2f,GameMain::createScene());
    //auto transition = TransitionProgressInOut::create(0.5f,GameMain::createScene());
    Director::getInstance()->pushScene(transition);
    
}
void Main::menuContinueCallback(Ref *pSender){

}
void Main::menuHowToPlayCallback(Ref *pSender){
    
}
void Main::menuRankCallback(Ref *pSender){
    
}
void Main::menuMoreGameCallback(Ref *pSender){
    
}
void Main::menuRemoveAdCallback(Ref *pSender){
    
}


void Main::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
