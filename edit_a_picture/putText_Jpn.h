#ifndef _PUT_TEXT_JPN_H_
#define _PUT_TEXT_JPN_H_


// opencv
#pragma warning(push)
#pragma warning ( disable : 4819 )
#include <opencv2/opencv.hpp>
#pragma warning(pop)

namespace sc
{
	namespace myCV
	{
		void putText_Jpn(cv::Mat &a_r_img_dst, const char *a_p_text, cv::Point a_pos_org, const char *a_p_fontname, double a_font_scale, cv::Scalar a_font_color, int a_thickness = 1, int lineType = 8);
	}
}

#endif	// _PUT_TEXT_JPN_H_
