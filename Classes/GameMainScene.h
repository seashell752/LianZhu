#ifndef __GameMain_SCENE_H__
#define __GameMain_SCENE_H__

#include "cocos2d.h"
#include "Ball.h"
#include "ANode.h"


USING_NS_CC;
class GameMain : public cocos2d::Layer
{
public:
    static const int LENGTH = 9;
    static const int NUMBER = 3;
    static const int COLORS = 7;
    static const int STEP = 10;
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameMain);
    
private:
    void addBalls();
    void shootBalls();
    Sprite* boardBg;
    //Vector<Sprite*> shootballs = Vector<Sprite*>(NUMBER);
    Ball* initballs[NUMBER];
    Ball* ballArray[LENGTH][LENGTH];
    Ball* choosedBall = nullptr;
    Vec2 firstBallPos = Vec2(0, 0);
    Vector<ANode*> emptyPoints = Vector<ANode*>();
    void findEmpty();
    //float posToDistance(int x);

    
    Vector<ANode*> openList = Vector<ANode*>();
    Vector<ANode*> closeList = Vector<ANode*>();
    
    Vector<ANode*> neighborList = Vector<ANode*>();

    bool canReach(int x, int y);
    ANode* findPath(ANode* startNode, ANode* endNode);
    ANode* findMinFNodeInOpneList();
    void findNeighborNodes(ANode* currentNode);
    void notFoundPoint(ANode* tempStart, ANode* end, ANode* node);
    
    Vector<Ball*> removedList = Vector<Ball*>();
    void scan();
    void scanAndShoot();
    void scanHorizontal();
    void scanVertical();
    void scanLeftOblique();
    void scanRightOblique();
    int getColor(int x, int y);
    bool removeBall();

    Animation* getRemoveAnimation();
    void animationEnd();
    LabelTTF* maxScoreLable;
    LabelTTF* scoreLable;
    int maxSocre = 0;
    int score = 0;
    
    
};

#endif // __HELLOWORLD_SCENE_H__
