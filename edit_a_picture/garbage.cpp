//�S�~��
//
//BITMAP a(cv::Mat& img, double fontScale)
//{
//	int fontSize = (int)(10 * fontScale); // 10�͓K��
//	int width = img.cols;
//	int height = fontSize * 3 / 2; // �����̓t�H���g�T�C�Y��1.5�{
//
//	HDC hdc = ::CreateCompatibleDC(NULL);
//
//	BITMAPINFOHEADER header;
//	::ZeroMemory(&header, sizeof(BITMAPINFOHEADER));
//	header.biSize = sizeof(BITMAPINFOHEADER);
//	header.biWidth = width;
//	header.biHeight = height;
//	header.biPlanes = 1;
//	header.biBitCount = 24;
//	BITMAPINFO bitmapInfo;
//	bitmapInfo.bmiHeader = header;
//	HBITMAP hbmp = ::CreateDIBSection(NULL, (LPBITMAPINFO)&bitmapInfo, DIB_RGB_COLORS, NULL, NULL, 0);
//	::SelectObject(hdc, hbmp);
//
//	BITMAP  bitmap;
//	::GetObject(hbmp, sizeof(BITMAP), &bitmap);
//	return bitmap;
//}
//
//
//void _putText(cv::Mat& img, const cv::String& text, const cv::Point& org, const char* fontname, double fontScale, cv::Scalar color)
//{
//	int fontSize = (int)(10 * fontScale); // 10�͓K��
//	int width = img.cols;
//	int height = fontSize * 3 / 2; // �����̓t�H���g�T�C�Y��1.5�{
//
//	HDC hdc = ::CreateCompatibleDC(NULL);
//
//	BITMAPINFOHEADER header;
//	::ZeroMemory(&header, sizeof(BITMAPINFOHEADER));
//	header.biSize = sizeof(BITMAPINFOHEADER);
//	header.biWidth = width;
//	header.biHeight = height;
//	header.biPlanes = 1;
//	header.biBitCount = 24;
//	BITMAPINFO bitmapInfo;
//	bitmapInfo.bmiHeader = header;
//	HBITMAP hbmp = ::CreateDIBSection(NULL, (LPBITMAPINFO)&bitmapInfo, DIB_RGB_COLORS, NULL, NULL, 0);
//	::SelectObject(hdc, hbmp);
//
//	BITMAP  bitmap;
//	::GetObject(hbmp, sizeof(BITMAP), &bitmap);
//
//	int back_color = 0x99;
//	int memSize = (((bitmap.bmBitsPixel / 8) * width) & ~3) * height;
//	std::memset(bitmap.bmBits, back_color, memSize);
//
//	HFONT hFont = ::CreateFontA(
//		fontSize, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE,
//		SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS,
//		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
//		VARIABLE_PITCH | FF_ROMAN, fontname);
//	::SelectObject(hdc, hFont);
//
//	::TextOutA(hdc, 0, height / 3 * 1, text.c_str(), (int)text.length());
//
//	int posX = org.x;
//	int posY = org.y - fontSize;
//
//	unsigned char* _tmp;
//	unsigned char* _img;
//	for (int y = 0; y < bitmap.bmHeight; y++) {
//		if (posY + y >= 0 && posY + y < img.rows) {
//			_img = img.data + (int)(3 * posX + (posY + y) * (((bitmap.bmBitsPixel / 8) * img.cols) & ~3));
//			_tmp = (unsigned char*)(bitmap.bmBits) + (int)((bitmap.bmHeight - y - 1) * (((bitmap.bmBitsPixel / 8) * bitmap.bmWidth) & ~3));
//			for (int x = 0; x < bitmap.bmWidth; x++) {
//				if (x + posX >= img.cols) {
//					break;
//				}
//				if (_tmp[0] == 0 && _tmp[1] == 0 && _tmp[2] == 0) {
//					_img[0] = (unsigned char)color.val[0];
//					_img[1] = (unsigned char)color.val[1];
//					_img[2] = (unsigned char)color.val[2];
//				}
//				_img += 5;
//				_tmp += 5;
//			}
//		}
//	}
//
//	::DeleteObject(hFont);
//	::DeleteObject(hbmp);
//	::DeleteDC(hdc);
//}
//
//
//HFONT SetMyFont(HDC hdc, LPCTSTR face, int h, int angle)
//{
//	HFONT hFont;
//	hFont = CreateFont(h,    //�t�H���g����
//		0,                    //������
//		angle,                    //�e�L�X�g�̊p�x
//		0,                    //�x�[�X���C���Ƃ����Ƃ̊p�x
//		FW_REGULAR,            //�t�H���g�̏d���i�����j
//		FALSE,                //�C�^���b�N��
//		FALSE,                //�A���_�[���C��
//		FALSE,                //�ł�������
//		SHIFTJIS_CHARSET,    //�����Z�b�g
//		OUT_DEFAULT_PRECIS,    //�o�͐��x
//		CLIP_DEFAULT_PRECIS,//�N���b�s���O���x
//		PROOF_QUALITY,        //�o�͕i��
//		FIXED_PITCH | FF_MODERN,//�s�b�`�ƃt�@�~���[
//		face);    //���̖�
//	return hFont;
//
//
//	/*HFONT hFont = ::CreateFontA(
//		fontSize,
//		0,
//		0,
//		0,
//		FW_DONTCARE,
//		FALSE,
//		FALSE,
//		FALSE,
//		SHIFTJIS_CHARSET,
//		OUT_DEFAULT_PRECIS,
//		CLIP_DEFAULT_PRECIS,
//		DEFAULT_QUALITY,
//		VARIABLE_PITCH | FF_ROMAN,
//		fontname);
//	::SelectObject(hdc, hFont);*/
//}