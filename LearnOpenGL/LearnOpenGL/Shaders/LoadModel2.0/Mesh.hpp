//
//  Mesh.hpp
//  LearnOpenGL
//
//  Created by vv on 2019/1/10.
//  Copyright © 2019年 hongxing zhang. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include "../../glm/glm.hpp"
#include "../../Glad/glad.h"

#include "../../GameFrame/Render/ShaderProgram.h"


#include <vector>
#include <string>

using namespace std;

struct Vertex
{
    //position
    glm::vec3 Position;
    //normal
    glm::vec3 Normal;
    //texCoords
    glm::vec2 TexCoords;
    //tangent
    glm::vec3 Tangent;
    //bitangent
    glm::vec3 Bitangent;
    
    Vertex(glm::vec3 _Position,glm::vec2 _TexCoords):Position(_Position),TexCoords(_TexCoords)
    {
        
    }
};
struct Texture
{
    unsigned int id;
    string type;
    string path;
    ~Texture()
    {
        glDeleteTextures(1,&id);
    }
};

class Mesh
{
public:
    
    Mesh(vector<Vertex> & _vertices,vector<Texture> &_textures,vector<unsigned int> & indices);
    void Draw(ShaderProgram shader);
    
private:
    vector<Vertex> vertices;
    vector<Texture> textures;
    vector<unsigned int> indices;
    unsigned int VAO,VBO,EBO;
    
    void SetUpMesh();
};

#endif /* Mesh_hpp */
