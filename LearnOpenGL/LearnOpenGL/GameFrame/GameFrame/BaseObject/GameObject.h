//
//  GameObject.hpp
//  LearnOpenGL
//
//  Created by fafa on 2018/5/25.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include "BaseObject.h"

class GameObject : public BaseObject
{
private:
    
    
public:
    GameObject();
    virtual bool G_init() override;
    virtual void G_Enter() override;
    virtual void G_Tick(float delta) override;
    virtual void G_Exit() override;
    virtual void G_Destroy() override;
};

#endif /* GameObject_hpp */
