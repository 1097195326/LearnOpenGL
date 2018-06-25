//
//  ObjectManager.hpp
//  LearnOpenGL
//
//  Created by fafa on 2018/5/25.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

//#ifndef ObjectManager_hpp
//#define ObjectManager_hpp

#include <map>

using namespace std;


template <typename Key,typename Value>
class TemplateManager
{
private:
    map<Key,Value> m_Map;
    
public:
    static TemplateManager *    Get()
    {
        static TemplateManager _m_;
        return &_m_;
    }
    
    void Register(Key _key, Value _value)
    {
        if (m_Map[_key])
        {
            printf("TemplateManager::Register->register to manager key is exist\n");
        }else{
//            m_Map[_key] = _value;
            m_Map.insert(make_pair(_key, _value));
        }
    }
    Value GetValueById(Key _key)
    {
        if (m_Map[_key])
        {
            return m_Map[_key];
        }
    }
    void RemoveValueByKey(Key _key)
    {
        m_Map.erase(_key);
    }
    
};

//#endif /* ObjectManager_hpp */
