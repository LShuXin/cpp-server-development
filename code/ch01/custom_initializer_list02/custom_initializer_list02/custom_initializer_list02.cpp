// custom_initializer_list02.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <initializer_list>
#include <vector>

// 简单的模拟 JSON 支持的几种数据类型
enum class jsonType
{
	jsonTypeNull,
	jsonTypeInt,
	jsonTypeLong,
	jsonTypeDouble,
	jsonTypeBool,
	jsonTypeString,
	jsonTypeArray,
	jsonTypeObject
};

struct jsonNode
{
	jsonNode(const char* key, const char* value):
		m_type(jsonType::jsonTypeString),
		m_key(key),
		m_value(value)
	{
		std::cout << "jsonNode constructor1 called." << std::endl;
	}

	jsonNode(const char* key, double value) :
		m_type(jsonType::jsonTypeDouble),
		m_key(key),
		m_value(std::to_string(value))
	{
		std::cout << "jsonNode constructor2 called." << std::endl;
	}

	// 省略其它类型的构造函数

	jsonType        m_type;
	std::string     m_key;
	// 始终使用 string 类型保存值，避免浮点类型因为精度问题而显示不同的结果
	std::string     m_value;

};

class json
{
public:
	static json& array(std::initializer_list<jsonNode> nodes)
	{
		m_json.m_nodes.clear();
		m_json.m_nodes.insert(m_json.m_nodes.end(), nodes.begin(), nodes.end());

		std::cout << "json::array() called." << std::endl;

		return m_json;
	}

	json()
	{
	
	}

	~json()
	{
	
	}

	std::string toString()
	{
		size_t size = m_nodes.size();
		for (size_t i = 0; i < size; ++i)
		{
			// 根据类型组装成一个 JSON 字符串，代码省略
			switch (m_nodes[i].m_type)
			{
			case jsonType::jsonTypeDouble:
				break;

			case jsonType::jsonTypeString:
				break;
			}
		}
	}

private:
	std::vector<jsonNode>     m_nodes;
	static json               m_json;
};


json json::m_json;
int main()
{
	json array_not_object = json::array({ { "currency", "USD"}, { "value", 42.99 } });
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
