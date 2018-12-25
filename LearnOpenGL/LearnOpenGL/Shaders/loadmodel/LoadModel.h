//
//  LoadModel.h
//  LearnOpenGL
//
//  Created by hongxing zhang on 2018/10/3.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

#ifndef LoadModel_h
#define LoadModel_h

#include "../../Glad/glad.h"
#include <GLFW/glfw3.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace LoadModel
{
    void  Draw(GLFWwindow * window);
}

#endif /* LoadModel_h */
