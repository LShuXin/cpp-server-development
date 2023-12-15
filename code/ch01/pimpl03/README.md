本实例是 pimpl02 的 C11 改进版，主要改进内容有如下几点

1. CSocketClent 私有成员变量

从

```
private:
    class Impl;
    Impl* m_pImpl;
```
改为

```
private:
    struct Impl; // 或 class Impl;
    std::unique_ptr<Impl> m_pImpl;
```

2. Impl 的类声明

从

```
class CSocketClient::Impl
{

}
```
改为

```
struct CSocketClient::Impl

{
}
```


3. CSocketClient 的构造函数

从

```
CSocketClient::CSocketClient()
{
    m_pImpl = new Impl();
}
```
改为

```
CSocketClient::CSocketClient()
{
    m_pImpl.reset(new Impl());   
}
```

4. CSocketClient 的析构函数

从

```
CSocketClient::~CSocketClient()
{
    delete m_pImpl;
}
```
改为

```
CSocketClient::~CSocketClient()
{
    // delete m_pImpl;
}
```

5. 为了使用 std::unique_ptr<T>, 引入了 <memory>




经过上述修改后，成员变量的初始化发生了变化，析构函数中对于 m_pImpl 指针不需要再使用 delete