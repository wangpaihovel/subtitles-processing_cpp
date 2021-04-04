
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "srtFormat.h"

using namespace std;

int get_srtFormat(ifstream& file_temp, srtFormat&r_srt);//��file_temp�л�ȡһ����Ļ֡�������浽r_srt�С�
bool out_srtFormat(fstream& file_temp, srtFormat&r_srt, int ordinal_num = 0);//��һ����Ļ֡r_srt���浽file_temp�У�ordinal_num����Ļ֡����š�
bool switch_srt_text(srtFormat&r_srt1, srtFormat&r_srt2);//����������Ļ֡�У�������Ļ�����ݣ��������䡣

int _tmain()
{
	ifstream file1("1.srt", ios_base::in);
	ifstream file2("2.srt", ios_base::in);
	fstream file3("�ϲ�����ļ�.srt", ios_base::out);

	srtFormat srt1, srt2;

	int count1, count2;
	count1 = count2 = 0;

	try
	{
		if (!file1.is_open() || !file2.is_open())
			throw "�ļ�1.srt���ļ�2.srt������";

		while (!file1.eof())
		{
			int return_value = get_srtFormat(file1, srt1);
			switch (return_value)
			{
			case true:
				count1++;
				cout << "�ļ�1.srt��֡����ȡ���˵�" << count1 << "֡\n\n";
				cout << "֡��ʼ###" << srt1.show_all() << "****֡����\n\n";
				break;

			case EOF:
				break;

			case false:
				throw "��ȡ�ļ�1.srt����Ļ���ݳ��ִ���";
				break;

			default:
				const int max_temp = 1000;
				char temp1[max_temp] = "��ȡ�ļ�1.srt�ĺ���get_srtFormat()����������ķ���ֵ";
				char temp2[max_temp] = { 0 };
				_itoa_s(return_value, temp2, max_temp, 10);//_itoa_s()Ϊitoa()��VS 2013�µİ汾���ǽ�intת��Ϊchar
				strcat_s(temp1, temp2);//����Ϊ�˾�����ʾ������ķ���ֵ�Ǻ�ֵ
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
				cout << "�ļ�2.srt��֡����ȡ���˵�" << count2 << "֡\n\n";
				cout << "֡��ʼ###" << srt2.show_all() << "****֡����\n\n";
				break;

			case EOF:
				break;

			case false:
				throw "��ȡ�ļ�2.srt����Ļ���ݳ��ִ���";
				break;

			default:
			{
					   const int max_temp = 1000;
					   char temp1[max_temp] = "��ȡ�ļ�2.srt�ĺ���get_srtFormat()����������ķ���ֵ";
					   char temp2[max_temp] = { 0 };
					   _itoa_s(return_value, temp2, max_temp, 10);//_itoa_s()Ϊitoa()��VS 2013�µİ汾���ǽ�intת��Ϊchar
					   strcat_s(temp1, temp2);//����Ϊ�˾�����ʾ������ķ���ֵ�Ǻ�ֵ
					   throw temp1;
					   break;

			}
			}

		} 
		file2.clear();

		if (count1 != count2)
			throw "����Ļ֡�������";

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
	r_srt.ordinal_num = get_temp;//��ȡ���

	if ('\n' == file_temp.peek())
		return false;
	file_temp.getline(get_temp, 1000);
	r_srt.time_data = get_temp;//��ȡʱ������Ϣ

	if ('\n' == file_temp.peek())
		return false;
	file_temp.getline(get_temp, 1000);
	r_srt.text_info = get_temp;//��ȡ��һ������
	while ('\n' != file_temp.peek() && !file_temp.eof()) //����ڶ��л������֣�������ȡ
	{
		file_temp.getline(get_temp, 1000);
		r_srt.text_info += '\n';
		r_srt.text_info += get_temp;
	}

	if ('\n' == file_temp.get() || file_temp.eof())//����һ֡����Ϣ,file_temp.get()��Ϊ�˳Ե����Ļ��з�
		r_srt.update();

	return true;
}

bool out_srtFormat(fstream& file_temp, srtFormat&r_srt, int ordinal_num)
{
	if (0 == ordinal_num)
		file_temp << r_srt.integration;
	else
	{
		if ('\0' == r_srt.ordinal_num[0])//����������ֵĴ�����bug���˴��ɷ�ֹ�հ�֡�Ĳ���
			return false;

		const int max_temp = 1000;
		char temp[max_temp] = {0};
		_itoa_s(ordinal_num, temp, max_temp, 10);//_itoa_s()Ϊitoa()��VS 2013�µİ汾���ǽ�intת��Ϊchar
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

