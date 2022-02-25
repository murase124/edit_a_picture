#include<stdio.h>
#include <windows.h>
#include <string.h>
#include<math.h>
#include <time.h>
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
	int* number;
	imgdate** Change_img;//�ύX�ۑ��p
};

//�O
//putText_Jpn_Main
void a_main(cv::Mat tmp_img, char* p_ary_message, cv::Point ary_pos_org, cv::Scalar font_color, double font_scale);
//call
void Change_next_img(imgdate** Change_img);
void  next_img(imgdate** pimg);
//Other codes
void gomi();
void lowerstring(char* out, const char* in);
//edit_others
cv::Scalar colour_select();
cv::Scalar mosaic_colour(int i);

//��
void edit_main(imgdate** pimg);
void Polygon(imgdate** pimg);	//���p�`
void line(imgdate** pimg);		//��
void mosaic(imgdate** pimg);	//���U�C�N
void Rectangle(imgdate** pimg);	//�l�p�`
void Text(imgdate** pimg);//����
//void _putText(cv::Mat& img, const cv::String& text, const cv::Point& org, const char* fontname, double fontScale, cv::Scalar color);
//HFONT SetMyFont(HDC hdc, LPCTSTR face, int h, int angle);


void edit_main(imgdate** pimg)
{

	Change_next_img(pimg);
	char command[20];
	int Coflg = -1;

	//�������
	printf("\nedit_View�@�́@�����́@1�@20\n");
	printf("�R�}���h\n");
	printf("| �L�����Z��/c | ���p�`/p | ����/l | ���U�C�N/m | �l�p�`/r  | ����/t |\n");
	printf("|   cancel     | Polygon  |  line  |   mosaic   | Rectangle |  Text  |\n");
	scanf_s("%s[^\0]", command, 20);
	//���͗]�����
	gomi();
	//��������
	lowerstring(command, command);

	Coflg = -1;
	if (strcmp(command, "cancel") == 0)	Coflg = 0;
	if (strcmp(command, "c") == 0)	Coflg = 0;
	if (strcmp(command, "polygon") == 0)	Coflg = 1;
	if (strcmp(command, "p") == 0)	Coflg = 1;
	if (strcmp(command, "line") == 0)	Coflg = 2;
	if (strcmp(command, "l") == 0)	Coflg = 2;
	if (strcmp(command, "mosaic") == 0)	Coflg = 3;
	if (strcmp(command, "m") == 0)	Coflg = 3;
	if (strcmp(command, "rectangle") == 0)	Coflg = 4;
	if (strcmp(command, "r") == 0)	Coflg = 4;
	if (strcmp(command, "text") == 0)	Coflg = 5;
	if (strcmp(command, "t") == 0)	Coflg = 5;

	try
	{
		switch (Coflg)
		{
		case(0):
			return;
			break;


		case(1):
			try
			{
				Polygon(pimg);
			}
			catch (const std::exception&)//�G���[����
			{
				printf("���̓G���[");
			}
			break;

		case(2):
			try
			{
				line(pimg);
			}
			catch (const std::exception&)//�G���[����
			{
				printf("���̓G���[");
			}
			break;

		case(3):
			try
			{
				mosaic(pimg);
			}
			catch (const std::exception&)//�G���[����
			{
				printf("���̓G���[");
			}
			break;
			
		case(4):
			try
			{
				Rectangle(pimg);
			}
			catch (const std::exception&)//�G���[����
			{
				printf("���̓G���[");
			}
			break;

			
		case(5):
			try
			{
				Text(pimg);
			}
			catch (const std::exception&)//�G���[����
			{
				printf("���̓G���[");
			}
			break;

		default:
			break;
		}
	}
	catch (const std::exception&)//�G���[����
	{
		printf("���̓G���[");
		
	}
}



//���p�`
void Polygon(imgdate** pimg)
{
	cv::Point pt[10]; //�C�ӂ̓_��z��ɓ����
	const cv::Point* ppt[1] = { pt };
	int The_thickness;
	cv::Scalar colour;
	int flg = -1;
	int i = 0;

	//����
	for (i = 0; i < 10; i++)
	{
		int vertical = 0;
		int beside = 0;
		printf("edit_View�ł̉��̍��W | �R�_�ȏ�@10�_�ȉ��@-1�Ŋ����@ \n");
		scanf_s("%d", &beside);
		if (beside == -1) break;
		printf("edit_View�ł̍����̍��W\n");
		scanf_s("%d", &vertical);
		vertical = vertical * (*(*pimg)->Change_img)->img->rows / 500.0;
		beside = beside * (*(*pimg)->Change_img)->img->rows / 500.0;
		pt[i] = cv::Point( beside, vertical);
		gomi();
	}

	//�h��Ԃ�
	printf("���̑�������� | �h��Ԃ�����-1 \n");
	scanf_s("%d", &The_thickness);
	flg = 0;
	if (The_thickness== -1)	flg = 1;
	gomi();
	int npt[] = { i, i };

	//�F
	colour = colour_select();

	//�`��
	if (i > 2 && (flg == 0 || flg == 1))
	{
		// �摜�C�܂�����_�̔z��̔z��C���_���̔z��C�܂�����C�������Ă��邩�H�C�F�C�������C���
		if (flg == 0)
			cv::polylines(*((*(*pimg)->Change_img)->img), ppt, npt, 1, true, colour, The_thickness);

		//�`��@������ (�摜, �_�̔z��, �_�̐�, �F)
		if (flg == 1)
			cv::fillConvexPoly(*((*(*pimg)->Change_img)->img), pt, i, colour);//BGR
	}
	else
	{
		printf("���_������܂���");
	}
}

//��
void line(imgdate** pimg)
{
	cv::Point pt[2]; //�C�ӂ�2�_��z��ɓ����
	int i = 0;
	cv::Scalar colour;
	int The_thickness;

	//����
	for (i = 0; i < 2; i++)
	{
		int vertical = 0;
		int beside = 0;
		printf("edit_View�ł̉��̍��W  %d�� \n", i);
		scanf_s("%d", &beside);
		printf("edit_View�ł̍����̍��W\n");
		scanf_s("%d", &vertical);
		vertical = vertical * (*(*pimg)->Change_img)->img->rows / 500.0;
		beside = beside * (*(*pimg)->Change_img)->img->rows / 500.0;
		pt[i] = cv::Point(beside, vertical);
		gomi();
	}

	//�F
	colour = colour_select();


	//����
	printf("���̑��������  \n");
	scanf_s("%d", &The_thickness);
	gomi();
	if (The_thickness < 0)
	{
		printf("���̓G���[");
	}

	//�`��
	cv::line(*((*(*pimg)->Change_img)->img), pt[0], pt[1], colour, The_thickness);//BGR
}


//���U�C�N
void mosaic(imgdate** pimg)
{
	srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����
	cv::Scalar colour;
	int x_y[2][2];
	cv::Point pt[4]; //�C�ӂ�2�_��z��ɓ����
	int i;
	int j;

	//����
	for (i = 0; i < 2; i++)
	{
		printf("%d�� �l�p�`�̑Ίp��\n", i);
		printf("edit_View�ł̉��̍��W�@ \n");
		scanf_s("%d", &x_y[i][0]);
		printf("edit_View�ł̍����̍��W\n");
		scanf_s("%d", &x_y[i][1]);
		//���͗]�����
		gomi();
		
	}
	//���_���ꂢ��
	if (x_y[0][0] > x_y[1][0])
	{
		int box = x_y[0][0];
		x_y[0][0] = x_y[1][0];
		x_y[1][0] = box;
	}
	if (x_y[0][1] > x_y[1][1])
	{
		int box = x_y[0][1];
		x_y[0][1] = x_y[1][1];
		x_y[1][1] = box;
	}

	//���W�����̃T�C�Y�ɂ���
	x_y[0][0] = x_y[0][0] * (*(*pimg)->Change_img)->img->rows / 500.0;
	x_y[0][1] = x_y[0][1] * (*(*pimg)->Change_img)->img->rows / 500.0;
	x_y[1][0] = x_y[1][0] * (*(*pimg)->Change_img)->img->rows / 500.0;
	x_y[1][1] = x_y[1][1] * (*(*pimg)->Change_img)->img->rows / 500.0;

	//�͈� 1�ȏ�
	int range_box = 1;

	//�I��͈͂�����
	if (x_y[0][1] + range_box > x_y[1][1] || x_y[0][0] + range_box > x_y[1][0])
	{
		printf("�������܂�");
		return;
	}

	//�`��
	for (j = x_y[0][1]; j < x_y[1][1]; j=j + range_box)
	{
		//�͈̓I�[�o�[
		if (j + range_box > x_y[1][1])	j = x_y[1][1] - range_box;
		for (i = x_y[0][0]; i < x_y[1][0]; i=i + range_box)
		{
			//�͈̓I�[�o�[
			if (i + range_box > x_y[1][0])  i = x_y[1][0] - range_box;

			//���@�c
			pt[0] = cv::Point(i, j);
			pt[1] = cv::Point(i + range_box, j);
			pt[2] = cv::Point(i + range_box, j + range_box);
			pt[3] = cv::Point(i, j + range_box);

			//�F
			colour = mosaic_colour(rand());

			//�`��@������ (�摜, �_�̔z��, �_�̐�, �F)
			cv::fillConvexPoly(*((*(*pimg)->Change_img)->img), pt, 4, colour);//BGR
		}
	}
	
}


//�l�p�`
void Rectangle(imgdate** pimg)
{
	srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����
	cv::Scalar colour;
	int x_y[2][2];
	int x_y2[2][2];
	cv::Point pt[4]; //�C�ӂ�2�_��z��ɓ����
	const cv::Point* ppt[1] = { pt };
	int The_thickness;
	int flg;
	int i;
	

	//����
	for (i = 0; i < 2; i++)
	{
		printf("%d�� �l�p�`�̑Ίp��\n", i);
		printf("edit_View�ł̉��̍��W�@ \n");
		scanf_s("%d", &x_y[i][0]);
		printf("edit_View�ł̍����̍��W\n");
		scanf_s("%d", &x_y[i][1]);
		gomi();
	}

	//�͈͑I���@���ꂢ�ɂ���
	if (x_y[0][0] > x_y[1][0])
	{
		int box = x_y[0][0];
		x_y[0][0] = x_y[1][0];
		x_y[1][0] = box;
	}
	if (x_y[0][1] > x_y[1][1])
	{
		int box = x_y[0][1];
		x_y[0][1] = x_y[1][1];
		x_y[1][1] = box;
	}


	//���̈ʒu��ݒ�@�ҏW�p�̃r���[�̈ʒu����@�I���W�i���T�C�Y��
	x_y2[0][0] = x_y[0][0] * (*(*pimg)->Change_img)->img->rows / 500.0;
	x_y2[0][1] = x_y[0][1] * (*(*pimg)->Change_img)->img->rows / 500.0;
	x_y2[1][0] = x_y[1][0] * (*(*pimg)->Change_img)->img->rows / 500.0;
	x_y2[1][1] = x_y[1][1] * (*(*pimg)->Change_img)->img->rows / 500.0;

	//�͈� 1�ȏ�
	int range_box = 1;

	if (x_y2[0][1] + range_box > x_y2[1][1] || x_y2[0][0] + range_box > x_y2[1][0])
	{
		printf("�������܂�");
		return;
	}

	//���@�c
	pt[0] = cv::Point(x_y2[0][0], x_y2[0][1]);
	pt[1] = cv::Point(x_y2[1][0], x_y2[0][1]);
	pt[2] = cv::Point(x_y2[1][0], x_y2[1][1]);
	pt[3] = cv::Point(x_y2[0][0], x_y2[1][1]);


	//�F
	colour = colour_select();

	//�`��@������ (�摜, �_�̔z��, �_�̐�, �F)
	//cv::fillConvexPoly(*((*(*pimg)->Change_img)->img), pt, 4, colour);//BGR

	//�h��Ԃ�
	printf("���̑�������� | �h��Ԃ�����-1 \n");
	scanf_s("%d", &The_thickness);
	flg = 0;
	if (The_thickness == -1)	flg = 1;
	gomi();
	int npt[] = { i, i };

	//�F
	colour = colour_select();

	//�`��
	if (flg == 0 || flg == 1)
	{
		// �摜�C�܂�����_�̔z��̔z��C���_���̔z��C�܂�����C�������Ă��邩�H�C�F�C�������C���
		if (flg == 0)
			cv::polylines(*((*(*pimg)->Change_img)->img), ppt, npt, 1, true, colour, The_thickness);

		//�`��@������ (�摜, �_�̔z��, �_�̐�, �F)
		if (flg == 1)
			cv::fillConvexPoly(*((*(*pimg)->Change_img)->img), pt, i, colour);//BGR
	}
	

}

//����
void Text(imgdate** pimg)
{
	srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����
	cv::Scalar colour;
	int x_y[2];
	int x_y2[2];
	cv::Point pt; //�C�ӂ�2�_��z��ɓ����
	char text[31];
	int The_thickness;

	//����
	printf("�����̍������W\n");
	printf("edit_View�ł̉��̍��W�@ \n");
	scanf_s("%d", &x_y[0]);
	printf("edit_View�ł̍����̍��W\n");
	scanf_s("%d", &x_y[1]);
	gomi();

	//���̈ʒu��ݒ�@�ҏW�p�̃r���[�̈ʒu����@�I���W�i���T�C�Y��
	x_y2[0] = 2 * x_y[0] * (*(*pimg)->Change_img)->img->rows / 500.0;
	x_y2[1] = 2 * x_y[1] * (*(*pimg)->Change_img)->img->rows / 500.0;

	//���@�c
	pt = cv::Point(x_y2[0], x_y2[1]);

	//�F
	colour = colour_select();

	//�����T�C�Y
	printf("�����̑傫�������  \n");
	scanf_s("%d", &The_thickness);
	gomi();
	if (The_thickness < 0)
	{
		printf("���̓G���[");
	}

	//����
	printf("�������ޕ��� �ő�30����\n");
	scanf_s("%s", text,31);
	gomi();

	float colsbox;
	float rowsbox;
	cv::Mat* aimg = new cv::Mat;//�摜�̌^�쐬
	*aimg = *((*(*pimg)->Change_img)->img);

	colsbox = (aimg->cols);
	rowsbox = (aimg->rows);

	//resize �́@�o�O�΍�
	resize(*((*(*pimg)->Change_img)->img), *((*(*pimg)->Change_img)->img), cv::Size(), colsbox * 2 / aimg->cols, colsbox * 2 / aimg->rows);
	
	//�`��
	a_main(*((*(*pimg)->Change_img)->img),text,pt,colour, The_thickness);
	
	//resize �́@�o�O�΍�
	*aimg = *((*(*pimg)->Change_img)->img);
	resize(*((*(*pimg)->Change_img)->img), *((*(*pimg)->Change_img)->img), cv::Size(), colsbox / aimg->cols, colsbox / aimg->rows);
}

