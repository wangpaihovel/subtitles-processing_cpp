
#pragma once

#include <string>

using namespace std;

class srtFormat
{
public:
	string ordinal_num;//ordinal number 序号
	string time_data;//时间信息
	string text_info;//text information 文字信息

private:
	string integration;//整合成的信息

private:
	srtFormat&operator+(const srtFormat&r_srt)//因为这个函数没有创建临时新对象，而是直接使用原对象来保存结果，这种设计容易被滥用，因此不设为公有
	{
		const char* pcstr = this->text_info.c_str();
		if ('\0' != pcstr[0])//如果this的文字信息什么没有也没有，那合并时就不用加换行符
			this->text_info += '\n';
		this->text_info += r_srt.text_info;
		this->update();
		return *this;
	}

public:
	srtFormat&operator+=(const srtFormat&r_srt)//将第一个文件的字幕显示在上面，而第二个字幕显示在下面
	{
		*this = *this + r_srt;
		return *this;
	}

	srtFormat& update()//更新“综合信息”的内容，一般如果srtFormat如果有任何其他数据的变化，都要更新一次
	{
		this->integration = this->ordinal_num + '\n'
			              + this->time_data + '\n'
			              + this->text_info + '\n' 
						  + '\n';
		return *this;
	}

	string show_all()//展示字幕帧的所有内容，这是对外的公有接口
	{
		return this->integration;
	}

};

