# ChatServer

**可以工作在nginx tcp负载均衡环境中的集群聊天服务器和客户端源码 基于muduo库实现**

## 项目介绍:

  本项目是在Linux环境下开发，**使用CMake编译构建的基于muduo网络库开发的集群聊天服务器，通过muduo的TcpServer和TCpClient类设计服务端、客户端，使用 muduo 注册消息事件到来的回调函数，并根据得到的MSGID定位到不同的功能处理函数中，主要实现用户注册、用户登录、添加好友、添加群组、群组聊天以及保持离线消息等功能，用户数据存放于MySQL数据库中进行增删改查。

### 技术栈：

1、Json序列化和反序列化

2、muduo网络库开发

3、nginx源码编译安装和环境部署

4、nginx的tcp负载均衡器配置

5、redis缓存服务器编程实践

6、基于发布-订阅的服务器中间件redis消息队列编程实践

7、MySQL数据库编程CMake构建编译环境



### 编译方式: 

```shell
cd build
rm -rf * 
cmake .. 
make
cd .. 
cd 
bin/ ./ChatServer 127.0.0.1 6000   //启动服务 
```

或者

直接使用脚本一键编译，生成可执行文件在bin目录下