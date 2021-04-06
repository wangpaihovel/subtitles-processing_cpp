
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "srtFormatM.0.0.1.h"

using namespace std;

int get_srtFormat(ifstream& file_temp, srtFormat&r_srt);//从file_temp中获取一个字幕帧，并保存到r_srt中。
bool out_srtFormat(fstream& file_temp, srtFormat dup_srt, int ordinal_num = 0);//把一个字幕帧r_srt保存到file_temp中，ordinal_num是字幕帧的序号。
void secret_operation(srtFormat& r_srt);//如在字幕信息中发现密语，予以特殊处理
bool switch_srt_text(srtFormat&r_srt1, srtFormat&r_srt2);//交换两个字幕帧中，文字字幕的内容，其他不变。

int main()
{
	char mode, screen_output;

	do//mode-模式选择
	{
		cout << "----------------------------------------------------------------------------------------------" << endl;
		cout << "请输入一个数字："
			<< "（输入 1 代表将文件1的字幕显示在上面，输入 2 代表将文件2的字幕显示在上面）" << endl << endl
			<< ">> 请开始输入一个数字:_\b";
		mode = getchar();
		mode -= '0';//用于消除输入字符导致的ASCII与数学数字之间的相对值
		cout << endl;

		if (mode<1 || mode>2)
		{
			static int count = 0;
			++count;
			cout << "您的输入有误，请重新输入。" << endl << endl
				<< "这是您的第 " << count << " 输入错误，" << "已为您重定向。" << endl << endl;
			
			continue;
		}
		else
		{
			while ('\n' != getchar())//即便是正确的输入，也要清除之后的输入流，避免对其它代码的可能影响
				continue;
			break;
		}

	} while (1);

	do//选择是否将过程输出至屏幕
	{
		cout << "----------------------------------------------------------------------------------------------" << endl;
		cout << "请输入一个数字："
			<< "（输入 1 代表希望将过程输出至屏幕，输入 0 代表不希望）" << endl << endl
			<< ">> 请开始输入一个数字:_\b";
		screen_output = getchar();
		screen_output -= '0';//用于消除输入字符导致的ASCII与数学数字之间的相对值
		cout << endl;

		if (screen_output<0 || screen_output>1)
		{
			static int count = 0;
			++count;
			cout << "您的输入有误，请重新输入。" << endl << endl
				<< "这是您的第 " << count << " 输入错误，" << "已为您重定向。" << endl << endl;

			continue;
		}
		else
		{
			while ('\n' != getchar())//即便是正确的输入，也要清除之后的输入流，避免对其它代码的可能影响
				continue;
			break;
		}

	} while (1);
	
	clock_t start_time = clock();//程序开始计时
	cout << endl << endl << "计时器开启" << endl << endl;

	cout <<  "----------------------------------------------------------------------------------------------" << endl << endl;
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
			static int watchdog = 1;
			if (watchdog++ == 10000)
				cout << "注意：某循环已达到10000次。如果你看得到这条提醒，说明程序的某处可能陷入了死循环！！！" << endl << endl;

			int return_value = get_srtFormat(file1, srt1);
			switch (return_value)
			{
			case true:
				count1++;
				if (1 == screen_output)//当程序开始处用户输入 1 时，此处就会产生“将过程输出至屏幕”的效果
				{
					cout << "文件1.srt：帧数读取到了第" << count1 << "帧\n\n";
					cout << "帧开始###" << srt1.show_all() << "****帧结束\n\n";
				}

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
			static int watchdog = 1;
			if (watchdog++ == 3000)
				cout << "注意：某循环已达到10000次。如果你看得到这条提醒，说明程序的某处可能陷入了死循环！！！" << endl << endl;

			int return_value = get_srtFormat(file2, srt2);
			switch (return_value)
			{
			case true:
				count2++;
				if (1 == screen_output)//当程序开始处用户输入 1 时，此处就会产生“将过程输出至屏幕”的效果
				{
					cout << "文件2.srt：帧数读取到了第" << count2 << "帧\n\n";
					cout << "帧开始###" << srt2.show_all() << "****帧结束\n\n";
				}

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
			secret_operation(srt1);
			secret_operation(srt2);

			if (2 == mode)//当程序最开始、用户输入 2 时，此处就会产生“将文件2的字幕显示在上面”的效果
				switch_srt_text(srt1, srt2);

			srt1 += srt2;
			out_srtFormat(file3, srt1, count3);

			if (1 == screen_output)//当程序开始处用户输入 1 时，此处就会产生“将过程输出至屏幕”的效果
			{
				cout << "合并后的文件.srt：帧数读取到了第" << count3 << "帧\n\n";
				cout << "帧开始###" << srt1.show_all() << "****帧结束\n\n";
			}
		}
	}
	catch (char * error_info)
	{
		cout << error_info<<"\n\n";
		goto end_goto;
	}

end_goto:
	file1.close();
	file2.close();
	file3.close();

	double end_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;//计时结束
	cout << endl << endl << "程序总用时： " << end_time << " 秒" << endl << endl;

	cout << "程序即将结束..." << endl << endl;
	system("pause");//防止最后的输出屏幕自动关闭

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

void secret_operation(srtFormat& r_srt)//此函数必须要在字幕信息没有语法错误的情况下才能执行
{
	const char* pcstr = r_srt.text_info.c_str();
	if (('\"' == pcstr[0] || '“' == pcstr[0]))
	{//如果文字帧里外部只有双引号(中英文皆可)，且双引号之间没有实际内容，那么就直接将文字帧置空
		int order = 1;
		while (' ' == pcstr[order])//双引号之间的空格不计入“实际内容”
			++order;
		if (('\"' == pcstr[order] || '”' == pcstr[order]) && '\0' == pcstr[++order])
		{
			r_srt.text_info = "";
			r_srt.update();
		}
	}
}

bool out_srtFormat(fstream& file_temp, srtFormat dup_srt, int ordinal_num)
{
	if (0 == ordinal_num)
		file_temp << dup_srt.show_all();
	else
	{
		if ('\0' == dup_srt.ordinal_num[0])//如果其他部分的代码有bug，此处可防止空白帧的产生
			return false;

		const int max_temp = 1000;
		char temp[max_temp] = {0};
		_itoa_s(ordinal_num, temp, max_temp, 10);//_itoa_s()为itoa()在VS 2013下的版本，是将int转换为char
		dup_srt.ordinal_num = temp;
		dup_srt.update();
		file_temp << dup_srt.show_all();
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

