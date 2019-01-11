//
//  Model.hpp
//  LearnOpenGL
//
//  Created by vv on 2019/1/11.
//  Copyright © 2019年 hongxing zhang. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include "Mesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../../ImageTool/stb_image.h"



class Model
{
public:
    Model(string const & path,bool gamma = false);
    void Draw(ShaderProgram shader);
    
    void Init();
private:
    vector<Texture> textures_loaded;
    vector<Mesh*> meshes;
   
    string directory;
    bool gammaCorrection;
    
    void LoadModel(string const & path);
    void ProcessNode(aiNode * node, const aiScene * scene);
    Mesh * ProcessMesh(aiMesh * mesh, const aiScene * scene);
    vector<Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
    TexId TextureFromFile(const char *path, const string &directory, bool gamma = false);
    
};

#endif /* Model_hpp */
