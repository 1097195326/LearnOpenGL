//
//  IObjectInterface.h
//  LearnOpenGL
//
//  Created by fafa on 2018/5/25.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

#ifndef IObjectInterface_h
#define IObjectInterface_h

class IObjectInterface {
public:
    virtual bool G_init() = 0;
    virtual void G_Enter() = 0;
    virtual void G_Tick(float delta) = 0;
    virtual void G_Exit() = 0;
    virtual void G_Destroy() = 0;
    
};

#endif /* IObjectInterface_h */
