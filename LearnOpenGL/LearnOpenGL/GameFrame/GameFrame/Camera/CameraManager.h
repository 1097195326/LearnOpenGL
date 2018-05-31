//
//  CameraManager.hpp
//  LearnOpenGL
//
//  Created by fafa on 2018/5/31.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

#ifndef CameraManager_hpp
#define CameraManager_hpp

#include "Camera.h"
#include "BaseObject.h"

class CameraManager{
private:
    Camera *        m_CurrentCamera;
    
    
public:
    static CameraManager * Get();
    
    void            SetCamera(Camera * _camera);
    Camera *        GetCamera();
};

#endif /* CameraManager_hpp */
