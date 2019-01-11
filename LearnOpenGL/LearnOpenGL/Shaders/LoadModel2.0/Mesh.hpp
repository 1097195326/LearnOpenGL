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
#include "../../ImageTool/stb_image.h"

#include <vector>
#include <string>
#include <memory>


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
    
    Vertex()
    {
        
    }
    Vertex(glm::vec3 _Position,glm::vec2 _TexCoords):Position(_Position),TexCoords(_TexCoords)
    {
        
    }
};
struct TextureId
{
    unsigned int Id;
    ~TextureId()
    {
        glDeleteTextures(1,&Id);
    }
};
typedef shared_ptr<TextureId> TexId;

struct Texture
{
    TexId id;
    string type;
    string path;
    Texture()
    {
        id = TexId(new TextureId());
    }
    
};

class Mesh
{
public:
    static TexId TextureFromFile(string filename);
    
    Mesh();
    Mesh(vector<Vertex> & _vertices,vector<Texture> &_textures,vector<unsigned int> & indices);
    void Draw(ShaderProgram shader);
    
    void InitTexture(string filename);
    
    vector<Vertex> vertices;
    vector<Texture> textures;
    vector<unsigned int> indices;
    Texture m_texture;
    
private:
    
    unsigned int VAO,VBO,EBO;
    
    void SetUpMesh();
    
    
};

#endif /* Mesh_hpp */
