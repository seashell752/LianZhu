//
//  Ball.h
//  LianZhu
//
//  Created by Ruils on 14-10-7.
//
//

#ifndef LianZhu_Ball_h
#define LianZhu_Ball_h
#include "cocos2d.h"
USING_NS_CC;

class Ball: public cocos2d::Sprite
{
public :
    static Ball* create(const std::string& filename);
    //数组下标
    int xPos;
    int yPos;
    //坐标值
    float x;
    float y;
    //颜色
    int color;
    //Vec2 firstBallPos = Vec2(0, 0);
};
#endif
