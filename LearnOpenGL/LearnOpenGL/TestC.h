//
//  TestC.h
//  LearnOpenGL
//
//  Created by hongxing zhang on 2018/9/25.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

#pragma once

#include "GameFrame/Msg/MsgCenter.hpp"

class ReceiveMsg
{
public:
    ReceiveMsg();
    ~ReceiveMsg();
    void  Receive(_msg_ptr _msg);
    
};
class SendMsg
{
public:
    
    SendMsg();
    void  Send();
};
