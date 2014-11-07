#include "GameMainScene.h"
#include "ANode.h"

//5 12 21 32 45
USING_NS_CC;
using namespace std;

Scene* GameMain::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameMain::create();

    // add layer as a child to scene
    scene->addChild(layer);
 
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameMain::init()
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
                                           CC_CALLBACK_1(GameMain::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    //init board array
    for (int i=0; i< LENGTH; i++){
        for (int j=0; j< LENGTH; j++){
            ballArray[i][j] = nullptr;
        }
    }
    //emptyPoints = new Vector<Point*>;
    // add background
    auto bg = Sprite::create("background.png");
    
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	bg->setScale(visibleSize.width / bg->getContentSize().width, visibleSize.height / bg->getContentSize().height);
	this->addChild(bg, 0);
    
    boardBg = Sprite::create("board_bg.png");
	boardBg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    float scale = (visibleSize.width - 10.0f) / boardBg->getContentSize().width;
    
    CCLOG("visibleSize.width  = %f", visibleSize.width );
    CCLOG("boardBg->getContentSize().width = %f", boardBg->getContentSize().width);
    CCLOG("scale = %f", scale);
    
	boardBg->setScale(scale, scale);
	this->addChild(boardBg, 1);
    
    auto scoreSprite = Sprite::create("game_bar.png");
    float scale2 = (visibleSize.width) / scoreSprite->getContentSize().width;
    scoreSprite->setPosition(visibleSize.width / 2, visibleSize.height-scoreSprite->getContentSize().height);
    scoreSprite->setScale(scale2,scale2);
    this->addChild(scoreSprite, 1);
    
    maxScoreLable = LabelTTF::create("100", "Arial", 20);
    maxScoreLable->setColor(Color3B::YELLOW);
    scoreLable = LabelTTF::create("50", "Arial", 20);
    maxScoreLable->setColor(Color3B::YELLOW);
    
    scoreLable->addChild(maxScoreLable);
    scoreSprite->addChild(scoreLable);
    
    // touch
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchAllAtOnce::create();
	//listener->onTouchesEnded = CC_CALLBACK_2(GameMain::onTouchesEnded, this);
	listener->onTouchesBegan = CC_CALLBACK_2(GameMain::onTouchesBegan, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    addBalls();
    
    this->scheduleOnce((SEL_SCHEDULE)&GameMain::shootBalls, 0.5f);
    return true;
}

static Ball* colorToBall(int i) {
    switch (i) {
        case 0: return Ball::create("chess0.png");
        case 1: return Ball::create("chess1.png");
        case 2: return Ball::create("chess2.png");
        case 3: return Ball::create("chess3.png");
        case 4: return Ball::create("chess4.png");
        case 5: return Ball::create("chess5.png");
        case 6: return Ball::create("chess6.png");
        default:
            return Ball::create("chess0.png");
    }
}


void GameMain::findEmpty() {
    emptyPoints.clear();
    for (int i=0; i< LENGTH; i++){
        for (int j=0; j< LENGTH; j++) {
            if(ballArray[i][j] == nullptr) {
                emptyPoints.pushBack(ANode::create(i,j));
            }
        }
    }
}

void GameMain::shootBalls() {
    findEmpty();
    
    if (emptyPoints.size() < NUMBER) {
        CCLOG("GameOVer.");
        return;
    }
    
    auto ball = initballs[0];
    float x = ball->getContentSize().width;
    float y = ball->getContentSize().height;
    
    if (firstBallPos.x == 0 || firstBallPos.y == 0) {
        auto size = boardBg->getContentSize();
        firstBallPos.x = 2.0f*x/3.0f+1;
        firstBallPos.y = size.height - 2.0f*y/3.0f-6.0f;
        
        CCLOG("size.width = %f",size.width);
        CCLOG("size.height = %f",size.height);
    }
    
    //for test
//    for (int i=0; i< LENGTH; i++){
//        for (int j=0; j< LENGTH; j++){
//                auto ballx = colorToBall(CCRANDOM_0_1()*10);
//                ballx->setPosition(Vec2(firstBallPos.x + i*(x-2.5), firstBallPos.y-j*(y-3)));
//                boardBg->addChild(ballx);
//        }
//    }
    

    for (int i=0; i< NUMBER; i++) {
        int random = (int)(CCRANDOM_0_1() * emptyPoints.size());
        auto aNode = emptyPoints.at(random);
        emptyPoints.erase(emptyPoints.begin()+random);
        CCLOG("point.x = %i", aNode->x);
        CCLOG("point.y = %i", aNode->y);

        Vec2 newVec2(firstBallPos.x + aNode->x*(x-2.5f), firstBallPos.y-aNode->y*(y-3.0f));
        auto ball = initballs[i];
        auto actionTo = MoveTo::create(0.5f, newVec2);
        ball -> runAction(actionTo);
        
        ball->xPos = aNode->x;
        ball->yPos = aNode->y;
        ball->x = newVec2.x;
        ball->y = newVec2.y;
        
        ballArray[(int)aNode->x][(int)aNode->y] = ball;
    }
    
    addBalls();
    
    scan();
    
}



void GameMain::addBalls() {
    
    for (int i = 0; i< NUMBER; ++i) {
        int color = (int)(CCRANDOM_0_1() * COLORS);
        CCLOG("ball %i color = %i", i, color);
        
        auto ball = colorToBall(color);
        ball->color = color;
        auto position = boardBg->getContentSize();
        float x = ball->getContentSize().width;
        float y = ball->getContentSize().height;
        float startx = position.width/2 - x;
        ball->setPosition(startx+ i*x,y/2);
        initballs[i] = ball;
        boardBg->addChild(ball);
    }
}

void GameMain::onTouchesEnded(const vector<Touch*>& touches, Event* event)
{
	Touch* touch = touches[0];
	Point location = touch->getLocation();
    
    //CCLOG("onTouchesEnded location.x=%f, location.y=%f",location.x, location.y);

//    Point pointInball = boardBg -> convertToNodeSpace(location);
//    auto ball = Sprite::create("chess0.png");
//    ball->setPosition(pointInball.x, pointInball.y);
//    boardBg->addChild(ball, 2);
}

void GameMain::onTouchesBegan(const vector<Touch*>& touches, Event* event)
{
	Touch* touch = touches[0];
	Point location = touch->getLocation();
    CCLOG("onTouchesBegan location.x=%f, location.y=%f",location.x, location.y);
    if (!boardBg->getBoundingBox().containsPoint(location)) {
          CCLOG("not in boardBG!!!!!!");
        return;
    }
    
    Point pointInboard = boardBg->convertToNodeSpace(location);
    auto tempBall = initballs[0];
    float x = tempBall->getContentSize().width;
    float y = tempBall->getContentSize().height;
    

    int xPos = (int)(((pointInboard.x-firstBallPos.x)/(x-2.5f))+0.5f);
    int yPos = (int)(((firstBallPos.y-pointInboard.y)/(y-3.0f))+0.5f);
    
    CCLOG("xPos=%i",xPos);
    CCLOG("yPos=%i",yPos);
    if (xPos < 0 || xPos > LENGTH -1 || yPos < 0 || yPos > LENGTH - 1) {
        CCLOG("Out of rang!!");
        return;
    }
    
    auto hitBall = ballArray[xPos][yPos];
    //点在某个球上
    if(hitBall != nullptr) {
       // if(sprite->getBoundingBox().containsPoint(pointInboard)) {
            CCLOG("Hit!!!!!!");
            if (choosedBall == hitBall) {
                return;
            }
            if(choosedBall != nullptr){
                choosedBall->stopAllActions();
                choosedBall->runAction(ScaleTo::create(0.2f, 1.0f));
            }
            choosedBall = hitBall;
            auto action = ScaleBy::create(0.5f, 0.6f);
            hitBall ->runAction(RepeatForever::create(Sequence::create(action, action->reverse(), NULL)));
      //  }
        return;
    }
    
    //点在空白的地方，看能否移动。//A*算法
    if (hitBall == nullptr && choosedBall != nullptr) {
        ANode* start = ANode::create(choosedBall->xPos,choosedBall->yPos);
        ANode* end = ANode::create(xPos,yPos);
        
        CCLOG("start:%i,%i",start->x,start->y);
        CCLOG("end:%i,%i",end->x,end->y);
        
        openList.clear();
        closeList.clear();
        
        ANode* aNode = findPath(start,end);
        if (aNode != nullptr) {
            Vector<ANode*> path = Vector<ANode*>();
            while (aNode != nullptr) {
                CCLOG("Path:%i,%i",aNode->x,aNode->y);
                path.pushBack(aNode);
                aNode = aNode->parentNode;
            }
            //auto array = PointArray::create(path.size());
            Vector<FiniteTimeAction*> actions = Vector<FiniteTimeAction*>();
            for (int i=path.size()-1; i>=0; --i) {
                auto n = path.at(i);
                actions.pushBack(MoveTo::create(0.05f, Vec2(firstBallPos.x + n->x*(x-2.5f), firstBallPos.y-n->y*(y-3.0f))));
                //array->addControlPoint(Vec2(firstBallPos.x + n->x*(x-2.5f), firstBallPos.y-n->y*(y-3.0f)));
                
            }
            //auto csb = CardinalSplineBy::create(1, array, 1);
            choosedBall->xPos = end->x;
            choosedBall->yPos = end->y;
            
            ballArray[start->x][start->y] = nullptr;
            ballArray[end->x][end->y] = choosedBall;
            
            choosedBall->stopAllActions();
            choosedBall->runAction(ScaleTo::create(0.2f, 1.0f));

            actions.pushBack(CallFunc::create(CC_CALLBACK_0(GameMain::scanAndShoot,this)));
            choosedBall->runAction(Sequence::create(actions));
            choosedBall = nullptr;
            
            //this->scheduleOnce((SEL_SCHEDULE)&GameMain::scanAndShoot, 0.05f*path.size());
            //this->scheduleOnce((SEL_SCHEDULE)&GameMain::shootBalls, 0.05f*path.size());
        }
      
     
        
    }

}


void GameMain::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
}


ANode* find(Vector<ANode*> &nodes, ANode &aNode) {
    
    for(int i=0;i<nodes.size();i++){
        auto n = nodes.at(i);
        if ((n->x == aNode.x) && (n->y == aNode.y)) {
            return n;
        }
    }
    
    return nullptr;
}

bool exists(Vector<ANode*> &nodes, ANode &aNode) {
    for(int i=0;i<nodes.size();i++){
        auto n = nodes.at(i);
        if ((n->x == aNode.x) && (n->y == aNode.y)) {
            return true;
        }
    }
    return false;
}

bool exists(Vector<ANode*> &nodes, int x, int y) {
    for(int i=0;i<nodes.size();i++){
        auto n = nodes.at(i);
        if ((n->x == x) && (n->y == y)) {
            return true;
        }
    }
    return false;
}

int calcG(ANode* start, ANode* node) {
    int G = GameMain::STEP;
    int parentG = node->parentNode != nullptr ? node->parentNode->G : 0;
    return G + parentG;
}

int calcH(ANode* end, ANode* node) {
    int step = abs(node->x - end->x) + abs(node->y - end->y);
    return step * GameMain::STEP;
}

void foundPoint(ANode* tempStart, ANode* node) {
    int G = calcG(tempStart, node);
    if (G < node->G) {
        node->parentNode = tempStart;
        node->G = G;
        node->calF();
    }
}



void GameMain::notFoundPoint(ANode* tempStart, ANode* end, ANode* node) {
    node->parentNode = tempStart;
    node->G = calcG(tempStart, node);
    node->H = calcH(end, node);
    node->calF();
    openList.pushBack(node);
}

ANode* GameMain::findMinFNodeInOpneList() {
    auto tempNode = openList.at(0);
    for(int i=0;i<openList.size();i++){
        auto n = openList.at(i);
        if (n->F < tempNode->F) {
            tempNode = n;
        }
    }
    return tempNode;
}

void GameMain::findNeighborNodes(ANode* currentNode) {
    neighborList.clear();

    int topX = currentNode->x;
    int topY = currentNode->y - 1;
    if (canReach(topX, topY) && !exists(closeList, topX, topY)) {
        neighborList.pushBack(ANode::create(topX, topY));
    }
    int bottomX = currentNode->x;
    int bottomY = currentNode->y + 1;
    if (canReach(bottomX, bottomY) && !exists(closeList, bottomX, bottomY)) {
        neighborList.pushBack(ANode::create(bottomX, bottomY));
    }
    int leftX = currentNode->x - 1;
    int leftY = currentNode->y;
    if (canReach(leftX, leftY) && !exists(closeList, leftX, leftY)) {
        neighborList.pushBack(ANode::create(leftX, leftY));
    }
    int rightX = currentNode->x + 1;
    int rightY = currentNode->y;
    if (canReach(rightX, rightY) && !exists(closeList, rightX, rightY)) {
        neighborList.pushBack(ANode::create(rightX, rightY));
    }

}

bool GameMain::canReach(int x, int y) {
     if (x >= 0 && x < LENGTH && y >= 0 && y < LENGTH) {
        return ballArray[x][y] == nullptr;
    }
    return false;
}

ANode* GameMain::findPath(ANode* startNode, ANode* endNode) {
    

    openList.pushBack(startNode);
    
    while (openList.size() > 0) {

        ANode* currentNode = findMinFNodeInOpneList();
        openList.eraseObject(currentNode);

        closeList.pushBack(currentNode);
        
        findNeighborNodes(currentNode);
        for(int i=0;i<neighborList.size();i++){
            auto node = neighborList.at(i);
            if (exists(openList, *node)) {
                foundPoint(currentNode, node);
            } else {
                notFoundPoint(currentNode, endNode, node);
            }
        }
        auto n = find(openList, *endNode);
        if (n != nullptr) {
            return n;
        }
    }
    
    return find(openList, *endNode);
}

int GameMain::getColor(int x, int y){
    auto ball = ballArray[x][y];
    if (ball != nullptr) {
        return ball->color;
    }
    return -1;
    
}
void GameMain::scan(){
    scanHorizontal();
    removeBall();
    scanVertical();
    removeBall();
    scanLeftOblique();
    removeBall();
    scanRightOblique();
    removeBall();

 
}
void GameMain::scanAndShoot(){
    scanHorizontal();
    bool b1 = removeBall();
    scanVertical();
    bool b2 = removeBall();
    scanLeftOblique();
    bool b3 = removeBall();
    scanRightOblique();
    bool b4 = removeBall();
    if (!(b1||b2||b3||b4)) {
        shootBalls();
    }
    
}
bool GameMain::removeBall(){
     int N = removedList.size();
     if (N>0) {
        for (int i=0; i<N; i++) {
            auto sprite = removedList.at(i);
            CCLOG("scan sprite.x=%i sprite.y=%i",sprite->xPos,sprite->yPos);
            auto animate = Animate::create(getRemoveAnimation());
            auto action = Sequence::create(animate,
                                           CallFunc::create(CC_CALLBACK_0(GameMain::animationEnd,this)),
                                           nullptr);
            sprite->runAction(action);
            //CCCallFunc::create(this,callfunc_selector(xx::menuSetVisableFalse))；
            //sprite->setVisible(false);
            
        }
        //removedList.clear();
        return true;
    }
    return false;
}
void GameMain::animationEnd(){
    for (int i=0; i<removedList.size(); i++) {
        auto sprite = removedList.at(i);
        sprite->setVisible(false);
    }
    removedList.clear();
}

void GameMain::scanVertical(){
    CCLOG("scanVertical");
    for (int i=0; i< LENGTH; i++){
        for (int j=0; j< LENGTH; j++){
            int color = getColor(i,j);
            if (color != -1) {
                if (j > 0) {
                    if (color == getColor(i,j - 1)) {
                        continue;
                    }
                }
                for (int k=j; k<LENGTH; k++) {
                    if (getColor(i, k) != color) {
                        if ((k-j) > 4) {
                            CCLOG("scanVertical find1!!");
                            for(int m=j;m<k;m++) {
                                removedList.pushBack(ballArray[i][m]);
                                ballArray[i][m]=nullptr;
                            }
                        }
                        break;
                    }
                    if (k==LENGTH-1) {
                        if (k-j >= 4) {
                            CCLOG("scanVertical find2!!");
                            for(int m=j;m<LENGTH;m++) {
                                removedList.pushBack(ballArray[i][m]);
                                ballArray[i][m]=nullptr;
                            }
                        }
                    }
                }
            }
        }
    }
}

void GameMain::scanHorizontal(){
    CCLOG("scanHorizontal");
    for (int i=0; i< LENGTH; i++){
        for (int j=0; j< LENGTH; j++){
            int color = getColor(j,i);
            if (color != -1) {
                if (j > 0) {
                    if (color == getColor(j-1,i)) {
                        continue;
                    }
                }
                for (int k=j; k<LENGTH; k++) {
                    if (getColor(k, i) != color) {
                        if ((k-j) > 4) {
                            CCLOG("scanHorizontal find1!!");
                            for(int m=j;m<k;m++) {
                                removedList.pushBack(ballArray[m][i]);
                                ballArray[m][i]=nullptr;
                            }
                        }
                        break;
                    }
                    if (k==LENGTH-1) {
                        if (k-j >= 4) {
                            CCLOG("scanHorizontal find2!!");
                            for(int m=j;m<LENGTH;m++) {
                                removedList.pushBack(ballArray[m][i]);
                                ballArray[m][i]=nullptr;
                            }
                        }
                    }
                }
            }
        }
    }

}
//从（0，0）左至右，上至下
void GameMain::scanLeftOblique(){
    CCLOG("scanLeftOblique");
    for (int i=0,j=0; i<LENGTH; i++,j=0) {
        for (int n=0; i+n<LENGTH&&j+n<LENGTH; n++) {
            int color = getColor(i+n,j+n);
            if (color != -1) {
                if (i+n > 0 && j+n > 0) {
                    if (color == getColor(i+n-1,j+n-1)) {
                        continue;
                    }
                }
                
                for (int k=0; i+n+k<LENGTH && j+n+k<LENGTH; k++) {
                    if (getColor(i+n+k, j+n+k) != color) {
                        if (k > 4) {
                            CCLOG("scanLeftOblique find1!!");
                            for(int m=0;m<k;m++) {
                                removedList.pushBack(ballArray[i+n+m][j+n+m]);
                                ballArray[i+n+m][j+n+m]=nullptr;
                            }
                        }
                        break;
                    }
                    if (i+n+k==LENGTH-1 || j+n+k==LENGTH-1) {
                        if (k>= 4) {
                            CCLOG("scanLeftOblique find2!!");
                            for(int m=0;m<=k;m++) {
                                removedList.pushBack(ballArray[i+n+m][j+n+m]);
                                ballArray[i+n+m][j+n+m]=nullptr;
                            }
                        }
                    }
                }
                
            }
            
        }
    }
    
    
    
    
    for (int i=0,j=1; j<LENGTH; j++,i=0) {
        for (int n=0; i+n<LENGTH&&j+n<LENGTH; n++) {
            int color = getColor(i+n,j+n);
            if (color != -1) {
                if (i+n > 0 && j+n > 0) {
                    if (color == getColor(i+n-1,j+n-1)) {
                        continue;
                    }
                }
                
                for (int k=0; i+n+k<LENGTH && j+n+k<LENGTH; k++) {
                    if (getColor(i+n+k, j+n+k) != color) {
                        if (k > 4) {
                            CCLOG("scanLeftOblique find3!!");
                            for(int m=0;m<k;m++) {
                                removedList.pushBack(ballArray[i+n+m][j+n+m]);
                                ballArray[i+n+m][j+n+m]=nullptr;
                            }
                        }
                        break;
                    }
                    if (i+n+k==LENGTH-1 || j+n+k==LENGTH-1) {
                        if (k>= 4) {
                            CCLOG("scanLeftOblique find4!!");
                            for(int m=0;m<=k;m++) {
                                removedList.pushBack(ballArray[i+n+m][j+n+m]);
                                ballArray[i+n+m][j+n+m]=nullptr;
                            }
                        }
                    }
                }
                
            }
            
        }
    }

    
    
    
}
//从(8,0) 右至左，上至下
void GameMain::scanRightOblique(){
    
    for (int i=LENGTH-1,j=0; i>=0; i--,j=0) {
        for (int n=0; i-n>=0&&j+n<LENGTH; n++) {
            int color = getColor(i-n,j+n);
            if (color != -1) {
                if (i-n+1 < LENGTH-1 && j-n > 0) {
                    if (color == getColor(i-n+1,j-n-1)) {
                        continue;
                    }
                }
                
                for (int k=0; i-n-k>=0 && j+n+k<LENGTH; k++) {
                    if (getColor(i-n-k, j+n+k) != color) {
                        if (k > 4) {
                            CCLOG("scanRightOblique find1!!");
                            for(int m=0;m<k;m++) {
                                removedList.pushBack(ballArray[i-n-m][j+n+m]);
                                ballArray[i-n-m][j+n+m]=nullptr;
                            }
                        }
                        break;
                    }
                    if (i-n-k==0 || j+n+k==LENGTH-1) {
                        if (k>= 4) {
                            CCLOG("scanRightOblique find2!!");
                            for(int m=0;m<=k;m++) {
                                removedList.pushBack(ballArray[i-n-m][j+n+m]);
                                ballArray[i-n-m][j+n+m]=nullptr;
                            }
                        }
                    }
                }
                
            }
            
        }
    }

    
    
    for (int i=LENGTH-1,j=0; j<LENGTH; j++) {
        for (int n=0; i-n>=0&&j+n<LENGTH; n++) {
            int color = getColor(i-n,j+n);
            if (color != -1) {
                if (i-n+1 < LENGTH-1 && j-n > 0) {
                    if (color == getColor(i-n+1,j-1)) {
                        continue;
                    }
                }
                
                for (int k=0; i-n-k>=0 && j+n+k<LENGTH; k++) {
                    if (getColor(i-n-k, j+n+k) != color) {
                        if (k > 4) {
                            CCLOG("scanRightOblique find3!!");
                            for(int m=0;m<k;m++) {
                                removedList.pushBack(ballArray[i-n-m][j+n+m]);
                                ballArray[i-n-m][j+n+m]=nullptr;
                            }
                        }
                        break;
                    }
                    if (i-n-k==0 || j+n+k==LENGTH-1) {
                        if (k>= 4) {
                            CCLOG("scanRightOblique find4!!");
                            for(int m=0;m<=k;m++) {
                                removedList.pushBack(ballArray[i-n-m][j+n+m]);
                                ballArray[i-n-m][j+n+m]=nullptr;
                            }
                        }
                    }
                }
                
            }
            
        }
    }
    
    
}

Animation* GameMain::getRemoveAnimation() {
    auto  animationCache = AnimationCache::getInstance();
    auto animation = animationCache->getAnimation("removeAnimation");
    if (animation == nullptr) {
        animation = Animation::create();
        for( int i=1;i<=15;i++)
        {
            char szName[10] = {0};
            sprintf(szName, "e%02d.png", i);
            animation->addSpriteFrameWithFile(szName);
        }
        // should last 0.9 seconds. And there are 15 frames.
        animation->setDelayPerUnit(0.9f / 15.0f);
        //animation->setRestoreOriginalFrame(true);
        animationCache->addAnimation(animation, "removeAnimation");
    }
    return animation;
}





