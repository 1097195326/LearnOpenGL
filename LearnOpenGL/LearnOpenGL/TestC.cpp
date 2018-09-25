//
//  TestC.c
//  LearnOpenGL
//
//  Created by hongxing zhang on 2018/9/25.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

#include "TestC.h"


ReceiveMsg::ReceiveMsg()
{
    MsgCenter::Instance()->RegisterMsgHeader(Msg_Local, 1000, this, &ReceiveMsg::Receive);
    
}
ReceiveMsg::~ReceiveMsg()
{
    MsgCenter::Instance()->RemoveMsgHeader(Msg_Local, 1000, this);
}
void ReceiveMsg::Receive(_msg_ptr _msg)
{
    int content = *(int*)_msg->GetMsgContent();
    printf("zhx : receive msg : %d\n",content);
    
}
SendMsg::SendMsg()
{
    
}
void SendMsg::Send()
{
    int content = 10;
    _msg_ptr msg(new MsgStruct(Msg_Local,1000,&content));
    MsgCenter::Instance()->SendMsg(msg);
    
}
