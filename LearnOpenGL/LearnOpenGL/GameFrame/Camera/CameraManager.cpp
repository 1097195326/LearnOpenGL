//
//  CameraManager.cpp
//  LearnOpenGL
//
//  Created by fafa on 2018/5/31.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

#include "CameraManager.h"


CameraManager * CameraManager::Get()
{
    static CameraManager m;
    return &m;
}
void CameraManager::SetCamera(Camera *_camera)
{
    m_CurrentCamera = _camera;
}
Camera * CameraManager::GetCamera()
{
    return m_CurrentCamera;
}
