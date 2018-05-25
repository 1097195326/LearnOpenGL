//
//  BaseObject.hpp
//  LearnOpenGL
//
//  Created by fafa on 2018/5/25.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

#ifndef BaseObject_hpp
#define BaseObject_hpp

#include "IObjectInterface.h"


class BaseObject : public IObjectInterface
{
private:
    unsigned int    m_ObjectId;
public:
                    BaseObject();
    virtual         ~BaseObject();
    
    unsigned int    GetId();
};

#endif /* BaseObject_hpp */
