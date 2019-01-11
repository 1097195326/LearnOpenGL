//
//  Mesh.cpp
//  LearnOpenGL
//
//  Created by vv on 2019/1/10.
//  Copyright © 2019年 hongxing zhang. All rights reserved.
//

#include "Mesh.hpp"



TexId Mesh::TextureFromFile(string filename)
{
    TexId texId(new TextureId());
    
    glGenTextures(1, &texId->Id);
    
    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;
        
        glBindTexture(GL_TEXTURE_2D, texId->Id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << std::endl;
        stbi_image_free(data);
    }
    return texId;
}
Mesh::Mesh()
{
    
}
Mesh::Mesh(vector<Vertex> & _vertices,vector<Texture> &_textures,vector<unsigned int> & _indices)
{
    vertices.insert(vertices.end(), _vertices.begin(),_vertices.end());
    textures.insert(textures.end(), _textures.begin(),_textures.end());
    indices.insert(indices.end(), _indices.begin(),_indices.end());
    
    SetUpMesh();
}
void Mesh::InitTexture(string filename)
{
    m_texture.type = "texture_diffuse";
    m_texture.id = TextureFromFile(filename);
    textures.insert(textures.end(), m_texture);
}
void Mesh::SetUpMesh()
{
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
void Mesh::Draw(ShaderProgram shader)
{   
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    
    for (int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        
        string number;
        string name = textures[i].type;
        if (name == "texture_diffuse")
        {
            number = std::to_string(diffuseNr++);
        }else if(name == "texture_specular")
        {
            number = std::to_string(specularNr++);
        }else if(name == "texture_normal")
        {
            number = std::to_string(normalNr++);
        }else if(name == "texture_height")
        {
            number = std::to_string(heightNr++);
        }
        shader.SetUniform1f((name+number).c_str(), i);
        
        glBindTexture(GL_TEXTURE_2D, textures[i].id->Id);
    }
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,(GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    
}
