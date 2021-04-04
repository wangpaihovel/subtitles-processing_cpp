
#pragma once

#include <cstring>
#include <cstdlib>
#include <climits>

using namespace std;

class Myload
{
private:
	char* pointer;//数组指针
	int MAX_LENGTH;//目标数组的长度。此值决定了order的上限值
	int order;//序号指针
	int judge;//判断值。用于储存某些方法、用作判断的隐藏返回值

public:
	Myload(){ pointer = nullptr; }
	Myload(char* target, int max_length = INT_MAX) :pointer(target),MAX_LENGTH(max_length),order(0){ }

	Myload(const Myload& other) = delete;
	~Myload() = default;

	Myload& operator=(const Myload& other) = delete;

	//newtar：new target 新目标值, pretar：previous target 以前的目标值
	char* operator=(char* newtar){ this->order = 0; auto pretar = this->pointer; this->pointer = newtar; return pretar; }

	Myload& operator<<(int data)
	{
		if (nullptr == this->pointer)
			return *this;

		const int maxlen = 1000;//maxlen：max length 最大长度
		char temp[maxlen] = { 0 };
		_itoa_s(data, temp, 10);//_itoa_s是itoa在vs2013下的版本
		return (*this) << temp;	
	}

	Myload& operator<<(const char array[])
	{
		if (nullptr == this->pointer)
			return *this;
		int i, len;
		for (i = 0, len = strlen(array); i < len;)
		if (this->order == this->MAX_LENGTH - 1)
		{//如果order即将越界，将末尾的数据设为'\0'
			this->pointer[order] = '\0';
			return *this;
		}
		else if (this->order >= this->MAX_LENGTH)
			throw "Myload的目标数组太小，数据已溢出\n";
		else if (this->order < 0)
			throw "Myload的数据指针异常\n";
		else
			this->pointer[this->order++] = array[i++];
		this->pointer[this->order] = '\0';//在数组末尾加'\0'
		return *this;
	}

	operator char*(){ return this->pointer; }//这使得Myload对象可以直接当绑定指针来使用

	operator int(){ return this->judge; }//这使得可以直接将Myload对象当做bool值用于判断

	//resetmaxlen：reset max length 重置最大值， premax：previous max 以前的最大长度值
	int resetmaxlen(int new_maxlength){ int premax = MAX_LENGTH; MAX_LENGTH = new_maxlength; return premax; }

	//retarda：reset target data 重置目标数据
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

