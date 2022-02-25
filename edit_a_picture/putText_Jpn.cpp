//
#include "putText_Jpn.h"

//
#include <windows.h>
#include <cstring>

// opencv
#pragma warning(push)
#pragma warning ( disable : 4819 )
#include <opencv2/opencv.hpp>
#pragma warning(pop)

//
#include <string>

//
namespace
{
	const char *P_STR_DEF_FONTNAME = "ＭＳ ゴシック";
	const unsigned char THRESH_MOJI = 0x50;
}

//---------------------------------------------------------------
//
// static関数
//
//---------------------------------------------------------------

//
static HBITMAP sttc_CreateBackbuffer(int nWidth, int nHeight)
{
	HBITMAP hBmp;
	LPVOID           lp;
	BITMAPINFO       bmi;
	BITMAPINFOHEADER bmiHeader;

	::ZeroMemory(&bmiHeader, sizeof(BITMAPINFOHEADER));
	bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmiHeader.biWidth = nWidth;
	bmiHeader.biHeight = nHeight;
	bmiHeader.biPlanes = 1;
	bmiHeader.biBitCount = 24;

	bmi.bmiHeader = bmiHeader;

	hBmp = ::CreateDIBSection(NULL, (LPBITMAPINFO)&bmi, DIB_RGB_COLORS, &lp, NULL, 0);
	return hBmp;
}

// 横書き
static int sttc_DrawText_Horizontal(cv::Mat &a_r_img_dst, const BITMAP a_hbmp, int a_pos_x, int a_pos_y, cv::Scalar a_font_color)
{
	int result = 0;
	int attach_width, attach_height, attach_bit, attach_linesize;
	int dst_width, dst_height, dst_linesize;

	attach_width = a_hbmp.bmWidth;
	attach_height = a_hbmp.bmHeight;
	attach_bit = a_hbmp.bmBitsPixel;
	attach_linesize = ((attach_bit / 8) * a_hbmp.bmWidth) & ~3;

	dst_width = a_r_img_dst.cols;
	dst_height = a_r_img_dst.rows;
	dst_linesize = ((a_hbmp.bmBitsPixel / 8) * a_r_img_dst.cols) & ~3;

	unsigned char r08, g08, b08;
	r08 = static_cast<unsigned char>(a_font_color.val[2]);
	g08 = static_cast<unsigned char>(a_font_color.val[1]);
	b08 = static_cast<unsigned char>(a_font_color.val[0]);

	unsigned char *p_attach_img, *p_dst_img;
	int x, y;

	for (y = 0; y < attach_height; y++)
	{
		if (a_pos_y + y >= 0 && a_pos_y + y < dst_height)
		{
			p_dst_img = a_r_img_dst.data + 3 * a_pos_x + (a_pos_y + y) * dst_linesize;
			p_attach_img = static_cast<unsigned char *>(a_hbmp.bmBits) + (attach_height - y - 1) * attach_linesize;
			//			::CopyMemory(p_dst_img, p_attach_img, copy_linesize);
			for (x = 0; x < attach_width; x++)
			{
				if (x + a_pos_x >= dst_width)
				{
					break;
				}
				if (p_attach_img[0] < THRESH_MOJI && p_attach_img[1] < THRESH_MOJI && p_attach_img[2] < THRESH_MOJI)
				{
					p_dst_img[0] = b08;
					p_dst_img[1] = g08;
					p_dst_img[2] = r08;
				}

				p_dst_img += 3;
				p_attach_img += 3;
			}
		}

	}

	return result;
}



//
static void sttc_putTextCore(cv::Mat &a_r_img_dst, const char *a_p_text, cv::Point a_pos_org, const char *a_p_fontname, double a_font_scale, cv::Scalar a_font_color, int a_thickness, int a_lineType)
{
	// 未使用
	UNREFERENCED_PARAMETER(a_lineType);
	UNREFERENCED_PARAMETER(a_thickness);

	//
	//const double FONT_SCALE_COEF = 1.0f;
	HDC hdc_Compatible;
	HBITMAP hbmp, hbmpPrev;
	BITMAP  bm;
	HFONT hFont, hFont_old;
	int width, height, linesize;
	int size_y = 100;
	int str_size;

	str_size = ::lstrlen(a_p_text);

	size_y = static_cast<int>(a_font_scale + 6.0f);
	width = a_r_img_dst.cols;
	height = (size_y * 3) / 2;
	hdc_Compatible = ::CreateCompatibleDC(NULL);
	hbmp = sttc_CreateBackbuffer(width, height);
	hbmpPrev = reinterpret_cast<HBITMAP>(::SelectObject(hdc_Compatible, hbmp));

	::GetObject(hbmp, sizeof(BITMAP), &bm);

	//
	int back_color = 0x99;
	linesize = ((bm.bmBitsPixel / 8) * width) & ~3;
	std::memset(bm.bmBits, back_color, linesize * height);

	hFont = ::CreateFont(
		size_y, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE,
		SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		VARIABLE_PITCH | FF_ROMAN, a_p_fontname
		);
	hFont_old = reinterpret_cast<HFONT>(::SelectObject(hdc_Compatible, hFont));
	//		::SetTextColor(hdc_Compatible, RGB(254, 192, 64));

	// 基準座標
	volatile int v_flag_org_left_bottom = 0;
	int y_org = size_y;
	if (v_flag_org_left_bottom)
	{
		y_org = size_y;	// left bottom
	}
	else
	{
		y_org = size_y / 3;	// @@@ left center(適当なパラメータ、要最適化)
	}

	// 白いウィンドウにグレー背景の黒文字を描画する。
	::TextOutA(hdc_Compatible, 0, y_org, a_p_text, str_size);

	// BGR値が(0x00,0x00,0x00)の画素を、a_font_colorで指定されたBGR値に置き換える。
	sttc_DrawText_Horizontal(a_r_img_dst, bm, a_pos_org.x, a_pos_org.y - size_y, a_font_color);

	::SelectObject(hdc_Compatible, hFont_old);
	::SelectObject(hdc_Compatible, hbmpPrev);
	::DeleteObject(hbmp);
	::DeleteDC(hdc_Compatible);

	return;
}

/////////////////////////////////////////////////////////////////////////////////////
//
// extern関数
//
/////////////////////////////////////////////////////////////////////////////////////

//
void sc::myCV::putText_Jpn(cv::Mat &a_r_img_dst, const char *a_p_text, cv::Point a_pos_org, const char *a_p_fontname, double a_font_scale, cv::Scalar a_font_color, int a_thickness, int a_lineType)
{
	// a_r_img_dstが空ではない
	if (!a_r_img_dst.empty())
	{
		// チャンネル数 = 3、チャンネルごとのビット深度が8(unsigned char)
		if (a_r_img_dst.channels() == 3 && a_r_img_dst.depth() == CV_8U)
		{
			int str_size;

			str_size = ::lstrlen(a_p_text);

			// 入力文字列の長さが0より大きい
			if ( str_size > 0)
			{
				const char *p_current_fontname = P_STR_DEF_FONTNAME;
				if (a_p_fontname)
				{
					p_current_fontname = a_p_fontname;
				}
				sttc_putTextCore(a_r_img_dst, a_p_text, a_pos_org, p_current_fontname, a_font_scale, a_font_color, a_thickness, a_lineType);
			}
		}
	}

	return;
}

