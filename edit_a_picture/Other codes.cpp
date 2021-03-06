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


//内
void gomi();	//入力余り消去
char lower(char c);	//文字を小文字にする
void lowerstring(char* out, const char* in);	//文字列を小文字にする
char* lowerstring_ver2(char* in);	//文字列を小文字にする  ver2
void upperstring(char* out, const char* in);	//文字列を大文字にする
char upper(char c);//文字を大文字にする


//入力余り消去
void gomi()
{
	while (getchar() != '\n');
}

//文字を小文字にする
char lower(char c)
{
	if ('A' <= c && c <= 'Z')
	{
		c = c + ('a' - 'A');
	}
	return c;
}

//文字列を小文字にする
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

//文字列を大文字にする
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

//文字を大文字にする
char upper(char c)
{
	if ('a' <= c && c <= 'z')
	{
		c = c - ('a' - 'A');
	}
	return c;
}

