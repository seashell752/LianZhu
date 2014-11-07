//
//  ShortestPathStep.h
//  LianZhu
//
//  Created by Ruils on 14-10-7.
//
//

#ifndef LianZhu_ShortestPathStep_h
#define LianZhu_ShortestPathStep_h
#include "cocos2d.h"
USING_NS_CC;

class ShortestPathStep : public cocos2d::Ref
{
public:
    ShortestPathStep();
    ~ShortestPathStep();
    static ShortestPathStep *createWithPosition(const cocos2d::Point &pos);
    bool initWithPosition(const cocos2d::Point &pos);
    int getFScore() const;
    bool isEqual(const ShortestPathStep *other) const;
    std::string getDescription() const;
    CC_SYNTHESIZE(cocos2d::Point, _position, Position);
    CC_SYNTHESIZE(int, _gScore, GScore);
    CC_SYNTHESIZE(int, _hScore, HScore);
    CC_SYNTHESIZE(ShortestPathStep*, _parent, Parent);
};

#endif
