//
//  Node.h
//  LianZhu
//
//  Created by Ruils on 14-10-7.
//
//

#ifndef LianZhu_ANode_h
#define LianZhu_ANode_h
#include "cocos2d.h"
USING_NS_CC;

class ANode : public cocos2d::Ref
{
public:
static ANode* create(int x, int y);
//数组下标
int x;
int y;

//for A*
int F;
int G;
int H;
void calF(); //F=G+H;
ANode* parentNode = nullptr;
    
};
#endif
