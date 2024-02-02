# ChatServer
可以工作在nginx tcp负载均衡环境中的集群聊天服务器和客户端源码  基于muduo实现

### 编译方式

./autobuild.sh

### 项目所需环境

1.json三方库，已经包含在thirdpart文件夹下
2.muduo网络库的安装，注意因为muduo是基于boost开发的，所以需先安装boost库
3.nginx配置tcp负载均衡
4.redis环境安装配置
5.完后可在test文件夹下进行相关测试

### 集群负载均衡

32位linux服务器sockectfd资源默认是1024个，就算调大，也就是2万个左右并发量。如果想提高服务器的并发能力，让更多的用户同时使用；这就是需要**集群或者是分布式部署** ，这里采用的是集群的方法；集群在水平方向上，原来有一台主机，现在扩展多台主机，每一台主机运行的都是独立的ChatServer。
但思考一下qq登录的时候，并没有让我们选择你要登哪个服务器，此时你无法把选择服务器这个决定扔个用户，用户并不知道哪个服务器空闲或者繁忙。所以在服务器集群这个环境当中，我们肯定是需要引入一个设备叫做**负载均衡器(反向代理设备)** ，他的功能就是帮我们统一接收客户端的请求，根据配置的既定的负载算法，来把客户端的这些请求分发到我们的业务服务器ChatServer上。
这个项目上所用的负载均衡器就是**nginx的tcp负载均衡模块** ，这个nginx一般轻松**5~6 万**并发量是没问题的。如果还想提高更大的并发量的话对于这个负载均衡器本身也可以进行集群，在其前端再挂一个**LVS**，LVS是一个偏底层的负载均衡器。LVS的并发容量，很容易就扩展到**10几万**。一台LVS带多台的nginx就可以进行更大的用户并发容量的扩容。
对于负载均衡，有业务层的负载，通过业务分发；还有传输层的负载，通过tcp或者udp来分发；还有网络层的负载，通过ip来分发；还有数据链路层，通过数据帧来进行分发。

聊天服务器是属于长连接的业务，长连接的业务也就是客服端和这个服务器通信以后，链路一直保持着，因为我们聊天不仅是你作为聊天的发起者(把信息推到服务器)，你还要作为聊天的接收者(服务器主动推消息到我们客户端上)！所以客户端的请求以及服务器的响应都是要经过负载均衡器的。当然因为客服端请求时，负载均衡器要转发客户端的请求，要递交给服务器，如此一来服务器就能拿到所要响应的客户端的网络信息，如此就可以通过建立一条ip隧道，直接响应给客户端，不经过负载均衡器，这样的效率是更加优秀的。

负载均衡器能够和后面的服务器保持**心跳机制**，用于检**测服务器故障**。如果网络环境复杂，中间的数据包，在路由器或者交换机上长时间的存留，相当于也就是说这个服务器不能够提供服务了。所以要保持一个心跳。内部实现大概是，负载均衡器发的时候发一个心跳，心跳计数就减一，然后发了一个心跳没有回，经过一秒就给心跳计数器加一个一，比如果加过3的话，就认为这个网络不通，这个服务器不能够正常提供服务了。 负载均衡器就需要检测业务服务器。

<<<<<<< HEAD
负载均衡器还需要能够发现新添加的ChatServer设备，方便扩展服务器数量。不用重启服务器来扩展。**nginx支持平滑加载配置文件启动**，就是可以在不中断服务的情况下，来动态的去识别新添加的服务器信息。
=======
负载均衡器还需要能够发现新添加的ChatServer设备，方便扩展服务器数量。不用重启服务器来扩展。**nginx支持平滑加载配置文件启动**，就是可以在不中断服务的情况下，来动态的去识别新添加的服务器信息。
>>>>>>> 9f8808959530f3d6b7a4a1a686672556f45cb15d
