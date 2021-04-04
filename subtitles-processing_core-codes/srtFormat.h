
#pragma once

#include <string>

using namespace std;

class srtFormat
{
private:
	string ordinal_num;//ordinal number 序号
	string time_data;//时间信息
	string text_info;//text information 文字信息
	string integration;//整合成的信息

	srtFormat&operator+(const srtFormat&r_srt)//因为这个函数没有创建临时新对象，而是直接使用原对象来保存结果，这种设计容易被滥用，因此设为私有
	{
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

	friend int get_srtFormat(ifstream& file_temp, srtFormat&r_srt);
	friend bool out_srtFormat(fstream& file_temp, srtFormat&r_srt, int ordinal_num);
	friend bool switch_srt_text(srtFormat&r_srt1, srtFormat&r_srt2);

};

