
#pragma once

#include <string>

using namespace std;

class srtFormat
{
private:
	string ordinal_num;//ordinal number ���
	string time_data;//ʱ����Ϣ
	string text_info;//text information ������Ϣ
	string integration;//���ϳɵ���Ϣ

	srtFormat&operator+(const srtFormat&r_srt)//��Ϊ�������û�д�����ʱ�¶��󣬶���ֱ��ʹ��ԭ������������������������ױ����ã������Ϊ˽��
	{
		this->text_info += '\n';
		this->text_info += r_srt.text_info;
		this->update();
		return *this;
	}

public:

	srtFormat&operator+=(const srtFormat&r_srt)//����һ���ļ�����Ļ��ʾ�����棬���ڶ�����Ļ��ʾ������
	{
		*this = *this + r_srt;
		return *this;
	}

	srtFormat& update()//���¡��ۺ���Ϣ�������ݣ�һ�����srtFormat������κ��������ݵı仯����Ҫ����һ��
	{
		this->integration = this->ordinal_num + '\n'
			              + this->time_data + '\n'
			              + this->text_info + '\n' 
						  + '\n';
		return *this;
	}

	string show_all()//չʾ��Ļ֡���������ݣ����Ƕ���Ĺ��нӿ�
	{
		return this->integration;

	}

	friend int get_srtFormat(ifstream& file_temp, srtFormat&r_srt);
	friend bool out_srtFormat(fstream& file_temp, srtFormat&r_srt, int ordinal_num);
	friend bool switch_srt_text(srtFormat&r_srt1, srtFormat&r_srt2);

};

