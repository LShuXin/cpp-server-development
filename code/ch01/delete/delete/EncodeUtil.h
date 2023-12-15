#include <iostream>


#pragma once
class EncodeUtil
{
public:
	static std::wstring AnsiiToUnicode(const std::string& srrAnsii);
	static std::string UnicodeToAnsii(const std::wstring& strUnicode);
	static std::string AnsiiToUtf8(const std::string& strAnsii);
	static std::string Utf8ToAnsii(const std::string& strUtf8);
	static std::string UnicodeToUtf8(const std::string& strUnicode);
	static std::wstring Utf8ToUnicode(const std::string& strUtf8);

private:
	EncodeUtil() = delete;
	~EncodeUtil() = delete;

	EncodeUtil(const EncodeUtil& rhs) = delete;
	EncodeUtil& operator=(const EncodeUtil& rhs) = delete;
};

