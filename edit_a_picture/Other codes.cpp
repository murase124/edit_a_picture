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


//“à
void gomi();	//“ü—Í—]‚èÁ‹
char lower(char c);	//•¶š‚ğ¬•¶š‚É‚·‚é
void lowerstring(char* out, const char* in);	//•¶š—ñ‚ğ¬•¶š‚É‚·‚é
char* lowerstring_ver2(char* in);	//•¶š—ñ‚ğ¬•¶š‚É‚·‚é  ver2
void upperstring(char* out, const char* in);	//•¶š—ñ‚ğ‘å•¶š‚É‚·‚é
char upper(char c);//•¶š‚ğ‘å•¶š‚É‚·‚é


//“ü—Í—]‚èÁ‹
void gomi()
{
	while (getchar() != '\n');
}

//•¶š‚ğ¬•¶š‚É‚·‚é
char lower(char c)
{
	if ('A' <= c && c <= 'Z')
	{
		c = c + ('a' - 'A');
	}
	return c;
}

//•¶š—ñ‚ğ¬•¶š‚É‚·‚é
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

//•¶š—ñ‚ğ‘å•¶š‚É‚·‚é
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

//•¶š‚ğ‘å•¶š‚É‚·‚é
char upper(char c)
{
	if ('a' <= c && c <= 'z')
	{
		c = c - ('a' - 'A');
	}
	return c;
}

