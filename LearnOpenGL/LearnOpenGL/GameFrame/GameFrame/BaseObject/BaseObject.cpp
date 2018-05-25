//
//  BaseObject.cpp
//  LearnOpenGL
//
//  Created by fafa on 2018/5/25.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

#include "BaseObject.h"


static unsigned int ObjectCount = 0;

BaseObject::BaseObject()
{
    m_ObjectId = ++ObjectCount;
    
}
BaseObject::~BaseObject()
{
    
}
unsigned int BaseObject::GetId()
{
    return m_ObjectId;
}
