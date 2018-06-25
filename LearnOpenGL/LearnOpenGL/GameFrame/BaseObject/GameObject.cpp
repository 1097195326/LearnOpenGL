//
//  GameObject.cpp
//  LearnOpenGL
//
//  Created by fafa on 2018/5/25.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

#include "GameObject.h"
#include "ObjectManager.h"


GameObject::GameObject()
{
    
    ObjectManager::Get()->Register(GetId(), this);
}
bool GameObject::G_init()
{
    
    G_Enter();
    return true;
}
void GameObject::G_Enter()
{
    
}
void GameObject::G_Tick(float delta)
{
    
}
void GameObject::G_Exit()
{
    
}
void GameObject::G_Destroy()
{
    ObjectManager::Get()->RemoveValueByKey(GetId());
    
    delete this;
}
