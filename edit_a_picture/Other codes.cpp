#include<stdio.h>
#include <windows.h>
#include <string.h>
#include<opencv2\opencv.hpp>

typedef struct imgdate
{
	imgdate* next;
	imgdate* back;
	imgdate** start;
	imgdate** last;
	cv::Mat* img;
	char pas[100];
	int situation;
};


//��
void gomi();	//���͗]�����
char lower(char c);	//�������������ɂ���
void lowerstring(char* out, const char* in);	//��������������ɂ���
char* lowerstring_ver2(char* in);	//��������������ɂ���  ver2
void upperstring(char* out, const char* in);	//�������啶���ɂ���
char upper(char c);//������啶���ɂ���


//���͗]�����
void gomi()
{
	while (getchar() != '\n');
}

//�������������ɂ���
char lower(char c)
{
	if ('A' <= c && c <= 'Z')
	{
		c = c + ('a' - 'A');
	}
	return c;
}

//��������������ɂ���
void lowerstring(char* out, const char* in)
{
	int i;

	i = 0;
	while (in[i] != '\0')
	{
		out[i] = lower(in[i]);
		i++;
	}
}
//ver2
char* lowerstring_ver2(char* in)
{
	int i;
	char* out = (char*)malloc(sizeof(char) * 20);

	i = 0;
	while (in[i] != '\0')
	{
		out[i] = lower(in[i]);
		i++;
	}
	out[i] = lower(in[i]);
	return out;
}

//�������啶���ɂ���
void upperstring(char* out, const char* in)
{
	int i;

	i = 0;
	while (in[i] != '\0')
	{
		out[i] = upper(in[i]);
		i++;
	}
}

//������啶���ɂ���
char upper(char c)
{
	if ('a' <= c && c <= 'z')
	{
		c = c - ('a' - 'A');
	}
	return c;
}

