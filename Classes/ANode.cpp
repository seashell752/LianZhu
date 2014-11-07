//
//  ANode.cpp
//  LianZhu
//
//  Created by Ruils on 14-10-7.
//
//

#include "ANode.h"

 ANode* ANode::create(int x, int y) {
   
     ANode *node = new (std::nothrow) ANode();
     if (node)
     {
         node->x = x;
         node->y = y;
         node->autorelease();
         return node;
     }
     CC_SAFE_DELETE(node);
     return nullptr;

}

void ANode::calF(){
    F = G + H;
}