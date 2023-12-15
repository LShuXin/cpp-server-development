��ʵ���� pimpl02 �� C11 �Ľ��棬��Ҫ�Ľ����������¼���

1. CSocketClent ˽�г�Ա����

��

```
private:
    class Impl;
    Impl* m_pImpl;
```
��Ϊ

```
private:
    struct Impl; // �� class Impl;
    std::unique_ptr<Impl> m_pImpl;
```

2. Impl ��������

��

```
class CSocketClient::Impl
{

}
```
��Ϊ

```
struct CSocketClient::Impl

{
}
```


3. CSocketClient �Ĺ��캯��

��

```
CSocketClient::CSocketClient()
{
    m_pImpl = new Impl();
}
```
��Ϊ

```
CSocketClient::CSocketClient()
{
    m_pImpl.reset(new Impl());   
}
```

4. CSocketClient ����������

��

```
CSocketClient::~CSocketClient()
{
    delete m_pImpl;
}
```
��Ϊ

```
CSocketClient::~CSocketClient()
{
    // delete m_pImpl;
}
```

5. Ϊ��ʹ�� std::unique_ptr<T>, ������ <memory>




���������޸ĺ󣬳�Ա�����ĳ�ʼ�������˱仯�����������ж��� m_pImpl ָ�벻��Ҫ��ʹ�� delete