#include "chatserver.hpp"
#include "json.hpp"
#include "chatservice.hpp"
#include <functional>
#include <string>
#include <iostream>
using namespace std;
using namespace placeholders;
using json = nlohmann::json;
ChatServer::ChatServer(EventLoop *loop,
                       const InetAddress &listenAddr,
                       const string &nameArg)
    : server_(loop, listenAddr, nameArg), loop_(loop)
{
    server_.setConnectionCallback(bind(&ChatServer::onConnection, this, _1));

    server_.setMessageCallback(bind(&ChatServer::onMessage, this, _1, _2, _3));
    server_.setThreadNum(4);
}

ChatServer::~ChatServer()
{
}

void ChatServer::start()
{
    server_.start();
}

void ChatServer::onConnection(const TcpConnectionPtr &conn)
{
    //客户端断开连接
    if(!conn->connected())
    {
        ChatService::instance()->clientCloseException(conn);
        cout << "client shutdown!" << endl;
        conn->shutdown();
    }
}

void ChatServer::onMessage(const TcpConnectionPtr &conn,
                           Buffer *buffer,
                           Timestamp time)
{
    string buf = buffer->retrieveAllAsString();

    if (buf.empty() || buf == "\n" || buf == "\r\n") {
        return;  // 忽略空消息，直接返回
    }
    // //数据收到后反序列化
    // json js = json::parse(buf);
    // //通过js读出来的
    // // 这边的业务和 具体的操作方法隔开了
    // auto msgHandler = ChatService::instance()->getHandler(js["msgid"].get<int>());
    // //回调消息绑定号的事件处理器，来执行相应的业务处理
    // msgHandler(conn, js, time);
    try {
        // 尝试解析JSON数据
        json js = json::parse(buf);

        // JSON 解析成功，执行相关处理逻辑
        int msgid = js["msgid"].get<int>();
        auto msgHandler = ChatService::instance()->getHandler(msgid);
        msgHandler(conn, js, time);
    } catch (const json::parse_error& e) {
        // 捕获JSON解析错误并判断是否是数字
        bool isNumeric = std::all_of(buf.begin(), buf.end(), ::isdigit);

        if (isNumeric) {
            // 如果是数字，直接返回原始数据
            conn->send(buf);
        } else {
            // 否则，返回原始数据给客户端
            conn->send(buf);
        }
    } catch (const std::exception& e) {
        // 捕获其他异常并返回错误信息
        std::cerr << "Exception caught: " << e.what() << std::endl;
        conn->send("Error: " + std::string(e.what()) + "\n");
    }
}
