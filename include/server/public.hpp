#ifndef PUBLIC_H
#define PUBLIC_H

/*
server和client的共用文件
*/
enum EnMsgType
{
    LOGIN_MSG = 1,
    LOGIN_MSG_ACK, // 登录响应消息
    LOGINOUT_MSG, // 注销消息
    REG_MSG,
    REG_MSG_ACK, // 注册响应消息
    ONE_CHAT_MSG, // 聊天消息 6
    ADD_FRIEND_MSG, // 添加好友消息 7

    CREATE_GROUP_MSG, // 创建群组 8
    ADD_GROUP_MSG, // 加入群组 9
    GROUP_CHAT_MSG, // 群聊天 10
    ERROR_MSG,    //用户不存在 11
};


#endif