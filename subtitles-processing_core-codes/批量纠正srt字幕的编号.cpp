

#include <iostream>
#include <fstream>

#include "srtFormat.h"
#include "Myload_M.0.1.h"

using namespace std;

int get_srtFormat(ifstream& file_temp, srtFormat&r_srt);//��file_temp�л�ȡһ����Ļ֡�������浽r_srt�С�
bool out_srtFormat(fstream& file_temp, srtFormat&r_srt, int ordinal_num = 0);//��һ����Ļ֡r_srt���浽file_temp�У�ordinal_num����Ļ֡����š�

const int maxlen = 1000;//maxlen��max length ��󳤶�
char buffer[maxlen] = { 0 };
Myload loading(buffer, maxlen);//��loading������buffer�����

int main()
{
	ifstream fin;
	fstream fout;

	const int maxread = 1000;//һ���������srt�ļ���

	int ftal = 0; //ftal��total files �ļ�����
	srtFormat srt;
	
	try
	{
		for (int i = 1; i <= maxread; ++i)//�����ļ�����
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
			throw "�Բ���һ���ɶ�ȡ��srt�ļ���û��";

		for (int fct = 1; fct <= ftal; ++fct)//fct��file count �ļ�����
		{
			int fnum = 0;//fnum��frame number ֡��
			int return_value = 0;

			loading.retarda() << fct << ".srt";
			fin.open(loading, ios_base::in);

			loading.retarda() << "�������ļ�" << fct << ".srt";
			fout.open(loading, ios_base::out);

			while (EOF != (return_value = get_srtFormat(fin, srt)))
			{/* ע�⣬��Ϊget_srtFormat������ʹ�õ���fin.peek��������������ҲӦ��ʹ��peek������ֱ��ʹ��get_srtFormat������
			 ����Ҫʹ��eof�����ж�ѭ����ֹ��������Ϊeof������peek������ԭ������Щ����ģ�
			 �������һ�ε��ļ�β�󣬵�����open��������ʧ�ܣ���ʱeof�����ж�Ϊ�ļ�β����peek�� */
			
				switch (return_value)
				{
				case true:
					++fnum;
					cout << "�ļ�" << fct << ".srt��֡����ȡ���˵�" << fnum << "֡\n\n" 
						<< "֡��ʼ###" << srt.show_all() << "****֡����\n\n";
					break;

				case EOF://�˴���Ϊ���Ͻ������õģ�ʵ���ϴ˴���Զ���ᱻִ��
					break;

				case false:
					loading.retarda() << "��ȡ�ļ�" << fct << ".srt����Ļ���ݳ��ִ���";
					throw (char*)loading;//ʹ��throw֮�󣬿��Բ�ʹ��break���˴�������ʡ�� (char*) ���������throw��������֮��

				default:
					loading.retarda() << "��ȡ�ļ�" << fct 
						<< ".srt�ĺ���get_srtFormat()����������ķ���ֵ" << return_value;
					throw (char*)loading;//ʹ��throw֮�󣬿��Բ�ʹ��break���˴�������ʡ�� (char*) ���������throw��������֮��

				}//switch��������
				out_srtFormat(fout, srt, fnum);
			}//while��������

			fin.clear();
			fin.close();//����˴�û�е��ô˺���������һ�ε�open������ʧЧ
			fout.clear();
			fout.close();//����˴�û�е��ô˺���������һ�ε�open������ʧЧ

		}//for��������
		cout.clear();
		cout << "ע�⣺�����Ļ���û���κ�����Ӧ����������п�������Ϊ����ȡsrt�ļ��ı��������ANSI��"<<endl
			<<"      ���ǣ�����������ļ�������Ȼ�������ģ�������ļ��ı������ȡ���ļ���Ӧ��ͬ��";
	}//try��������
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
	const int temaxlen = 1000;//temaxlen��temporary maximum length ��ʱ��󳤶�
	char get_temp[temaxlen];

	char next_ch = file_temp.peek();

	if ('\n' == next_ch)
		return false;
	else if (EOF == next_ch)
		return EOF;
	file_temp.getline(get_temp, temaxlen);
	r_srt.ordinal_num = get_temp;//��ȡ���

	if ('\n' == file_temp.peek())
		return false;
	file_temp.getline(get_temp, temaxlen);
	r_srt.time_data = get_temp;//��ȡʱ������Ϣ

	if ('\n' == file_temp.peek())
		return false;
	file_temp.getline(get_temp, temaxlen);
	r_srt.text_info = get_temp;//��ȡ��һ������
	while ('\n' != file_temp.peek() && !file_temp.eof()) //����ڶ��л������֣�������ȡ
	{
		file_temp.getline(get_temp, temaxlen);
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

		loading.retarda() << ordinal_num;
		r_srt.ordinal_num = loading;
		r_srt.update();
		file_temp << r_srt.integration;
	}

	return true;
}


