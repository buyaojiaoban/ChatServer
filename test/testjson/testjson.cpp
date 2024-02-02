#include "json.hpp"
using json = nlohmann::json;

#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

// json序列化示例一
void func1() // json底层应该是一个无序哈希表
{
    json js;
    js["msg_type"] = 2;
    js["from"] = "boozeban";
    js["to"] = "jyl";
    js["msg"] = "hello, what do you want to do?";

    string sendBuf = js.dump(); // dump输出 把数据数列化 后的赋给sendBuf
    cout << sendBuf.c_str() << endl; // 通过网络传送 string 转 char*
}

// json序列化示例二
void func2()
{
    json js;
    // 添加数组
    js["id"] = {1,2,3,4,5};
    // 添加key-value
    js["name"] = "boozeban";
    // 添加对象
    js["msg"]["boozeban"] = "hello world";
    js["msg"]["jyl"] = "hello china";
    // 上面等同于下面这句一次性添加数组对象
    js["msg"] = {{"jyl","hello"},{"boozeban","hello china"}};
    cout << js << endl;
}

// json序列化示例三
void func3()
{
    json js;
    // 直接序列化一个vector容器
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(5);

    js["list"] = vec;

    // 直接序列化一个map容器
    map<int, string> m;
    m.insert({1, "黄山"});
    m.insert({2, "华山"});
    m.insert({3, "泰山"});

    js["path"] = m;
    string sendBuf = js.dump(); // json数据对象 序列化 json字符串
    cout<<js<<endl;
}

// json反序列化示例一
string func4() 
{
    json js;
    js["msg_type"] = 2;
    js["from"] = "boozeban";
    js["to"] = "jyl";
    js["msg"] = "hello, what do you want to do?";

    string sendBuf = js.dump(); 
    return sendBuf;
}

// json反序列化示例二
string func5()
{
    json js;
    // 添加数组
    js["id"] = {1,2,3,4,5};
    // 添加key-value
    js["name"] = "boozeban";
    // 添加对象
    js["msg"]["boozeban"] = "hello world";
    js["msg"]["jyl"] = "hello china";
    // 上面等同于下面这句一次性添加数组对象
    js["msg"] = {{"jyl","hello"},{"boozeban","hello china"}};
    return js.dump();
}

// json反序列化示例三
string func6()
{
    json js;
    // 直接序列化一个vector容器
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(5);

    js["list"] = vec;

    // 直接序列化一个map容器
    map<int, string> m;
    m.insert({1, "黄山"});
    m.insert({2, "华山"});
    m.insert({3, "泰山"});

    js["path"] = m;
    string sendBuf = js.dump(); // json数据对象 序列化 json字符串
    return sendBuf;
}
int main()
{   
    string recvBuf = func4();
    // 数据的反序列化   json字符串  -》  反序列化  数据对象(看作容器，方便访问)
    json jsbuf = json::parse(recvBuf);
    cout << jsbuf["msg_type"] << endl;
    cout << jsbuf["from"] << endl;
    cout << jsbuf["to"] << endl;
    cout << jsbuf["msg"] << endl;

    string recvBuf2 = func5();
    json jsbuf2 = json::parse(recvBuf2);
    cout << jsbuf2["id"] << endl;
    auto arr = jsbuf2["id"];
    cout << arr[2] << endl;

    auto msgjs = jsbuf2["msg"];
    cout<<msgjs["jyl"]<<endl;



    string recvBuf3 = func6();
    json jsbuf3 = json::parse(recvBuf3);
    vector<int> vec = jsbuf3["list"]; // js对象里面的数组类型，直接放入vector容器当中
    for(int &v : vec)
    {
        cout<<v<<endl;
    }
    cout<<endl;

    map<int, string> mymap = jsbuf3["path"];
    for(auto& p : mymap)
    {
        cout<<p.first<<" "<<p.second<<endl;
    }
    cout<<endl;

    return 0;
}