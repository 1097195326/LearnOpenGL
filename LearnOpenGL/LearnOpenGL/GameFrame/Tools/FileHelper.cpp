//
//  FileHelper.cpp
//  LearnOpenGL
//
//  Created by fafa on 2018/5/9.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

#include "FileHelper.h"

string FileHelper::ReadFileToString(std::string _FilePath)
{
    ifstream inputFile;
    stringstream strContent;
    string content;
    
    inputFile.open(_FilePath);
    if (inputFile.fail())
    {
        return "";
    }
    strContent<<inputFile.rdbuf();
    content = strContent.str();
    printf("zhx::FileHelper::ReadFileToString::Filepath::(%s),content::\n%s\n",_FilePath.c_str(),content.c_str());
    
    inputFile.close();
    
    return content;
}
