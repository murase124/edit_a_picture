// opencv
#pragma warning(push)
#pragma warning ( disable : 4819 )
#include <opencv2/opencv.hpp>
#pragma warning(pop)
#include<stdio.h>
#include <windows.h>
#include <string.h>
#include<math.h>
#include <time.h>

//
#include "putText_Jpn.h"

void a_main(cv::Mat tmp_img);//テスト用
void a_main(cv::Mat tmp_img, char* p_ary_message, cv::Point ary_pos_org, cv::Scalar font_color, double font_scale);//文字描画

//BITMAP a(cv::Mat& img, double fontScale);



void a_main(cv::Mat tmp_img, char* p_ary_message,cv::Point ary_pos_org, cv::Scalar font_color,double font_scale)
{
	int result = -1;


	if (!tmp_img.empty())
	{
		//const char *p_ary_message[] = { "OpenCVで日本語表示", "日本語２", "ﾆﾎﾝｺﾞ3", "ＥＳＣで終了" };
		//cv::Point ary_pos_org_a[4] = { cv::Point(10, 100), cv::Point(0, 150), cv::Point(100, 200), cv::Point(0, 300) };
		cv::Point pos_cv = cv::Point(320, 300);
		//cv::Scalar font_color(255, 255, 255);
		//double font_scale = 10.0f;
		int thickness = 1;

		sc::myCV::putText_Jpn(tmp_img, p_ary_message, ary_pos_org, NULL, font_scale, font_color, thickness);
		
		//cv::imshow("hoge", tmp_img);
		//cv::waitKey(0);

		//cv::imwrite("opencv_nihongo.png", tmp_img);

		result = 0;
	}
}

//テスト用
void a_main(cv::Mat tmp_img)
{
	int result = -1;


	if (!tmp_img.empty())
	{
		const char* p_ary_message[] = { "OpenCVで日本語表示", "日本語２", "ﾆﾎﾝｺﾞ3", "ＥＳＣで終了" };
		cv::Point ary_pos_org_a[4] = { cv::Point(10, 100), cv::Point(0, 150), cv::Point(100, 200), cv::Point(0, 300) };
		cv::Point pos_cv = cv::Point(320, 300);
		cv::Scalar font_color(255, 255, 255);
		double font_scale = 30.0f;
		int thickness = 1;

		cv::Point ary_pos_org;
		ary_pos_org = ary_pos_org_a[0];
		sc::myCV::putText_Jpn(tmp_img, p_ary_message[0], ary_pos_org, NULL, font_scale, font_color, thickness);

		cv::imshow("hoge", tmp_img);
		cv::waitKey(0);

		cv::imwrite("opencv_nihongo.png", tmp_img);

		result = 0;
	}

}
