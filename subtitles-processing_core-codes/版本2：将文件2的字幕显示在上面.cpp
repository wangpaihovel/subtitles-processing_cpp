
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "srtFormat.h"

using namespace std;

int get_srtFormat(ifstream& file_temp, srtFormat&r_srt);//从file_temp中获取一个字幕帧，并保存到r_srt中。
bool out_srtFormat(fstream& file_temp, srtFormat&r_srt, int ordinal_num = 0);//把一个字幕帧r_srt保存到file_temp中，ordinal_num是字幕帧的序号。
bool switch_srt_text(srtFormat&r_srt1, srtFormat&r_srt2);//交换两个字幕帧中，文字字幕的内容，其他不变。

int _tmain()
{
	ifstream file1("1.srt", ios_base::in);
	ifstream file2("2.srt", ios_base::in);
	fstream file3("合并后的文件.srt", ios_base::out);

	srtFormat srt1, srt2;

	int count1, count2;
	count1 = count2 = 0;

	try
	{
		if (!file1.is_open() || !file2.is_open())
			throw "文件1.srt或文件2.srt不存在";

		while (!file1.eof())
		{
			int return_value = get_srtFormat(file1, srt1);
			switch (return_value)
			{
			case true:
				count1++;
				cout << "文件1.srt：帧数读取到了第" << count1 << "帧\n\n";
				cout << "帧开始###" << srt1.show_all() << "****帧结束\n\n";
				break;

			case EOF:
				break;

			case false:
				throw "获取文件1.srt的字幕内容出现错误";
				break;

			default:
				const int max_temp = 1000;
				char temp1[max_temp] = "获取文件1.srt的函数get_srtFormat()出现了意外的返回值";
				char temp2[max_temp] = { 0 };
				_itoa_s(return_value, temp2, max_temp, 10);//_itoa_s()为itoa()在VS 2013下的版本，是将int转换为char
				strcat_s(temp1, temp2);//这是为了具体显示此意外的返回值是何值
				throw temp1 ;
				break;
			}
				
		}
		file1.clear();

		while (!file2.eof())
		{
			int return_value = get_srtFormat(file2, srt2);
			switch (return_value)
			{
			case true:
				count2++;
				cout << "文件2.srt：帧数读取到了第" << count2 << "帧\n\n";
				cout << "帧开始###" << srt2.show_all() << "****帧结束\n\n";
				break;

			case EOF:
				break;

			case false:
				throw "获取文件2.srt的字幕内容出现错误";
				break;

			default:
			{
					   const int max_temp = 1000;
					   char temp1[max_temp] = "获取文件2.srt的函数get_srtFormat()出现了意外的返回值";
					   char temp2[max_temp] = { 0 };
					   _itoa_s(return_value, temp2, max_temp, 10);//_itoa_s()为itoa()在VS 2013下的版本，是将int转换为char
					   strcat_s(temp1, temp2);//这是为了具体显示此意外的返回值是何值
					   throw temp1;
					   break;

			}
			}

		} 
		file2.clear();

		if (count1 != count2)
			throw "两字幕帧数不相等";

		file1.seekg(0);
		file2.seekg(0);

		for (int count3 = 1; count3 <= count1; ++count3)
		{
			get_srtFormat(file1, srt1);
			get_srtFormat(file2, srt2);
			switch_srt_text(srt1, srt2);
			srt1 += srt2;
			out_srtFormat(file3, srt1,count3);

		}
	}
	catch (char * error_info)
	{
		cout << error_info<<"\n\n";
		file1.close();
		file2.close();
		file3.close();
		exit(0);
	}

	file1.close();
	file2.close();
	file3.close();

	return 0;
}

int get_srtFormat(ifstream& file_temp,srtFormat&r_srt)
{
	char get_temp[1000];

	char next_ch = file_temp.peek();

	if ('\n' == next_ch)
		return false;
	else if (EOF == next_ch)
		return EOF;
	file_temp.getline(get_temp, 1000);
	r_srt.ordinal_num = get_temp;//获取序号

	if ('\n' == file_temp.peek())
		return false;
	file_temp.getline(get_temp, 1000);
	r_srt.time_data = get_temp;//获取时间轴信息

	if ('\n' == file_temp.peek())
		return false;
	file_temp.getline(get_temp, 1000);
	r_srt.text_info = get_temp;//获取第一行文字
	while ('\n' != file_temp.peek() && !file_temp.eof()) //如果第二行还有文字，继续获取
	{
		file_temp.getline(get_temp, 1000);
		r_srt.text_info += '\n';
		r_srt.text_info += get_temp;
	}

	if ('\n' == file_temp.get() || file_temp.eof())//整合一帧的信息,file_temp.get()是为了吃掉最后的换行符
		r_srt.update();

	return true;
}

bool out_srtFormat(fstream& file_temp, srtFormat&r_srt, int ordinal_num)
{
	if (0 == ordinal_num)
		file_temp << r_srt.integration;
	else
	{
		if ('\0' == r_srt.ordinal_num[0])//如果其他部分的代码有bug，此处可防止空白帧的产生
			return false;

		const int max_temp = 1000;
		char temp[max_temp] = {0};
		_itoa_s(ordinal_num, temp, max_temp, 10);//_itoa_s()为itoa()在VS 2013下的版本，是将int转换为char
		r_srt.ordinal_num = temp;
		r_srt.update();
		file_temp << r_srt.integration;
	}

	return true;
}

bool switch_srt_text(srtFormat&r_srt1, srtFormat&r_srt2)
{
	string temp_text = r_srt1.text_info;
	r_srt1.text_info = r_srt2.text_info;
	r_srt2.text_info = temp_text;

	return true;
}

