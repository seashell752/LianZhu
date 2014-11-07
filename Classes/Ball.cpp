//
//  Ball.cpp
//  LianZhu
//
//  Created by Ruils on 14-10-7.
//
//

#include "Ball.h"
USING_NS_CC;
Ball* Ball::create(const std::string& filename) {
    
    Ball *sprite = new (std::nothrow) Ball();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}
