
#pragma once

#include <cstring>
#include <cstdlib>
#include <climits>

using namespace std;

class Myload
{
private:
	char* pointer;//����ָ��
	int MAX_LENGTH;//Ŀ������ĳ��ȡ���ֵ������order������ֵ
	int order;//���ָ��
	int judge;//�ж�ֵ�����ڴ���ĳЩ�����������жϵ����ط���ֵ

public:
	Myload(){ pointer = nullptr; }
	Myload(char* target, int max_length = INT_MAX) :pointer(target),MAX_LENGTH(max_length),order(0){ }

	Myload(const Myload& other) = delete;
	~Myload() = default;

	Myload& operator=(const Myload& other) = delete;

	//newtar��new target ��Ŀ��ֵ, pretar��previous target ��ǰ��Ŀ��ֵ
	char* operator=(char* newtar){ this->order = 0; auto pretar = this->pointer; this->pointer = newtar; return pretar; }

	Myload& operator<<(int data)
	{
		if (nullptr == this->pointer)
			return *this;

		const int maxlen = 1000;//maxlen��max length ��󳤶�
		char temp[maxlen] = { 0 };
		_itoa_s(data, temp, 10);//_itoa_s��itoa��vs2013�µİ汾
		return (*this) << temp;	
	}

	Myload& operator<<(const char array[])
	{
		if (nullptr == this->pointer)
			return *this;
		int i, len;
		for (i = 0, len = strlen(array); i < len;)
		if (this->order == this->MAX_LENGTH - 1)
		{//���order����Խ�磬��ĩβ��������Ϊ'\0'
			this->pointer[order] = '\0';
			return *this;
		}
		else if (this->order >= this->MAX_LENGTH)
			throw "Myload��Ŀ������̫С�����������\n";
		else if (this->order < 0)
			throw "Myload������ָ���쳣\n";
		else
			this->pointer[this->order++] = array[i++];
		this->pointer[this->order] = '\0';//������ĩβ��'\0'
		return *this;
	}

	operator char*(){ return this->pointer; }//��ʹ��Myload�������ֱ�ӵ���ָ����ʹ��

	operator int(){ return this->judge; }//��ʹ�ÿ���ֱ�ӽ�Myload������boolֵ�����ж�

	//resetmaxlen��reset max length �������ֵ�� premax��previous max ��ǰ����󳤶�ֵ
	int resetmaxlen(int new_maxlength){ int premax = MAX_LENGTH; MAX_LENGTH = new_maxlength; return premax; }

	//retarda��reset target data ����Ŀ������
	Myload& retarda()
	{
		if (nullptr == this->pointer)
			this->judge = false;
		else
		{
			this->order = 0;
			this->pointer[this->order] = '\0';
			this->judge = true;
		}
		return *this;
	}
};

