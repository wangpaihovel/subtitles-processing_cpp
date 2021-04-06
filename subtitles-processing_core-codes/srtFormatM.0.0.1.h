
#pragma once

#include <string>

using namespace std;

class srtFormat
{
public:
	string ordinal_num;//ordinal number ���
	string time_data;//ʱ����Ϣ
	string text_info;//text information ������Ϣ

private:
	string integration;//���ϳɵ���Ϣ

private:
	srtFormat&operator+(const srtFormat&r_srt)//��Ϊ�������û�д�����ʱ�¶��󣬶���ֱ��ʹ��ԭ������������������������ױ����ã���˲���Ϊ����
	{
		const char* pcstr = this->text_info.c_str();
		if ('\0' != pcstr[0])//���this��������Ϣʲôû��Ҳû�У��Ǻϲ�ʱ�Ͳ��üӻ��з�
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

};

