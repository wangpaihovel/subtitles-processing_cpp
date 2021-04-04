

#include <iostream>
#include <fstream>

#include "srtFormat.h"
#include "Myload_M.0.1.h"

using namespace std;

int get_srtFormat(ifstream& file_temp, srtFormat&r_srt);//从file_temp中获取一个字幕帧，并保存到r_srt中。
bool out_srtFormat(fstream& file_temp, srtFormat&r_srt, int ordinal_num = 0);//把一个字幕帧r_srt保存到file_temp中，ordinal_num是字幕帧的序号。

const int maxlen = 1000;//maxlen：max length 最大长度
char buffer[maxlen] = { 0 };
Myload loading(buffer, maxlen);//将loading对象与buffer数组绑定

int main()
{
	ifstream fin;
	fstream fout;

	const int maxread = 1000;//一次最大读入的srt文件数

	int ftal = 0; //ftal：total files 文件总数
	srtFormat srt;
	
	try
	{
		for (int i = 1; i <= maxread; ++i)//计算文件个数
		{
			loading.retarda() << i << ".srt";
			fin.open(loading, ios_base::in);
			if (fin.is_open())
				++ftal;
			else
				break;
			fin.close();
		}

		if (!ftal)
			throw "对不起，一个可读取的srt文件都没有";

		for (int fct = 1; fct <= ftal; ++fct)//fct：file count 文件计数
		{
			int fnum = 0;//fnum：frame number 帧数
			int return_value = 0;

			loading.retarda() << fct << ".srt";
			fin.open(loading, ios_base::in);

			loading.retarda() << "处理后的文件" << fct << ".srt";
			fout.open(loading, ios_base::out);

			while (EOF != (return_value = get_srtFormat(fin, srt)))
			{/* 注意，因为get_srtFormat函数中使用的是fin.peek函数，所以这里也应该使用peek函数或直接使用get_srtFormat函数，
			 而不要使用eof函数判断循环终止条件。因为eof函数与peek函数的原理还是有些区别的，
			 如果在上一次到文件尾后，调用了open函数但是失败，此时eof不会判定为文件尾，而peek会 */
			
				switch (return_value)
				{
				case true:
					++fnum;
					cout << "文件" << fct << ".srt：帧数读取到了第" << fnum << "帧\n\n" 
						<< "帧开始###" << srt.show_all() << "****帧结束\n\n";
					break;

				case EOF://此处是为了严谨而设置的，实际上此处永远不会被执行
					break;

				case false:
					loading.retarda() << "获取文件" << fct << ".srt的字幕内容出现错误";
					throw (char*)loading;//使用throw之后，可以不使用break；此处不允许省略 (char*) ，这可能是throw语句的特殊之处

				default:
					loading.retarda() << "获取文件" << fct 
						<< ".srt的函数get_srtFormat()出现了意外的返回值" << return_value;
					throw (char*)loading;//使用throw之后，可以不使用break；此处不允许省略 (char*) ，这可能是throw语句的特殊之处

				}//switch的右括号
				out_srtFormat(fout, srt, fnum);
			}//while的右括号

			fin.clear();
			fin.close();//如果此处没有调用此函数，则下一次的open函数将失效
			fout.clear();
			fout.close();//如果此处没有调用此函数，则下一次的open函数将失效

		}//for的右括号
		cout.clear();
		cout << "注意：如果屏幕最后没有任何理所应当的输出，有可能是因为所读取srt文件的编码均不是ANSI。"<<endl
			<<"      但是，最终输出的文件可能依然是正常的，且输出文件的编码与读取的文件对应相同。";
	}//try的右括号
	catch (char * error_info)
	{
		cout << error_info;
		fin.clear();
		fin.close();
		fout.clear();
		fout.close();
	}

	cout << endl << endl;

	system("pause");
	return 0;
}

int get_srtFormat(ifstream& file_temp, srtFormat&r_srt)
{
	const int temaxlen = 1000;//temaxlen：temporary maximum length 临时最大长度
	char get_temp[temaxlen];

	char next_ch = file_temp.peek();

	if ('\n' == next_ch)
		return false;
	else if (EOF == next_ch)
		return EOF;
	file_temp.getline(get_temp, temaxlen);
	r_srt.ordinal_num = get_temp;//获取序号

	if ('\n' == file_temp.peek())
		return false;
	file_temp.getline(get_temp, temaxlen);
	r_srt.time_data = get_temp;//获取时间轴信息

	if ('\n' == file_temp.peek())
		return false;
	file_temp.getline(get_temp, temaxlen);
	r_srt.text_info = get_temp;//获取第一行文字
	while ('\n' != file_temp.peek() && !file_temp.eof()) //如果第二行还有文字，继续获取
	{
		file_temp.getline(get_temp, temaxlen);
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

		loading.retarda() << ordinal_num;
		r_srt.ordinal_num = loading;
		r_srt.update();
		file_temp << r_srt.integration;
	}

	return true;
}


