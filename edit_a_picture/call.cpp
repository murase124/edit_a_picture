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
	int* number;
	imgdate** Change_img;
	imgdate** parent_img;
};

//�O
//Other codes
void lowerstring(char* out, const char* in);
void gomi();
//��
 void COLOR_process(char pas1[], cv::Mat* img, int num);					//�摜�ǂݍ��ݑO����
 void COLOR(imgdate** pimg, int num);										//�摜�ǂݍ���
 void imgdate_Structure(imgdate** pimg);									//�摜�\���̍쐬
 void img_display(imgdate** pimg);											//�摜�\��
 void imshow_move(imgdate** pimg);											//imshow���ړ�
 void next_img(imgdate** pimg);												//���̉摜��
 void back_img(imgdate** pimg);												//�O�̉摜��
 void img_Save(imgdate** pimg);												//�摜�ۑ�
 void Ruled_line(cv::Mat* aimg);											//�摜�Ɍr��������
 void Change_next_img(imgdate** Change_img);								//�摜�ҏW�����̕ۊǏꏊ�쐬
 void Change_next_img_delete(imgdate** Change_img);							//Change ����@
 void processing_back(imgdate** pimg);										//���H��O��
 void processing_next(imgdate** pimg);										//���H������
 void specify_move_img(imgdate** pimg, int i);								//�w�薇���@�摜�ړ�
 void size_Change(imgdate** pimg);											//�T�C�Y�ύX
 void size_Change_process(imgdate** pimg, int CoFlg);						//�T�C�Y�ύX����
 void size_Change_multiple(imgdate** pimg);									//�T�C�Y�ύX(�ꊇ)
 void size_Change_process_multiple(imgdate** pimg, int CoFlg);				//�T�C�Y�ύX����(�ꊇ)




 //�摜�ǂݍ��ݑO����
void COLOR(imgdate** pimg, int num)
{
	//�p�X�Z�b�g
	char pas1[100] = "read/";
	strcat_s(pas1, (*pimg)->pas);
	//��O�����Ɓ@�ύX�Ȃ�
	if (num == (*pimg)->situation) return;
	if (num != 0)if (num != 1) if (num != -1) return;
	//�摜�Ăяo��
	(*pimg)->situation = num;
	COLOR_process(pas1, (*pimg)->img,num);
}

//�摜�ǂݍ���
void COLOR_process(char pas1[], cv::Mat* img, int num)
{
	*img = cv::imread(pas1, num);
}

//�摜�\���̍쐬
void imgdate_Structure(imgdate** pimg)
{
	if (*pimg == NULL)
	{
		(*pimg) = (imgdate*)malloc(sizeof(imgdate));
		(*pimg)->start = (imgdate * *)malloc(sizeof(imgdate*));
		(*pimg)->last = (imgdate * *)malloc(sizeof(imgdate*));
		*((*pimg)->start) = *pimg;
		*((*pimg)->last) = *pimg;
		(*pimg)->next = NULL;
		(*pimg)->back = NULL;
		(*pimg)->situation = -1;
		(*pimg)->number = new int(1);;//�摜�̖������P�Z�b�g
		(*pimg)->Change_img = (imgdate * *)malloc(sizeof(imgdate*));//�ύX�ۑ��p
		(*pimg)->parent_img = (imgdate * *)malloc(sizeof(imgdate*)); 
		*((*pimg)->Change_img) = NULL;
		*((*pimg)->parent_img) = NULL;
	}
	else
	{
		(*pimg)->next = (imgdate*)malloc(sizeof(imgdate));
		(*pimg)->next->next = NULL;
		(*pimg)->next->back = (*pimg);
		(*pimg)->next->start = (*pimg)->start;
		(*pimg)->next->last = (*pimg)->last;
		((*pimg)->next->number) = ((*pimg)->number);
		*pimg = ((*pimg)->next);
		(*pimg)->situation = -1;
		*((*pimg)->last) = *pimg;
		*((*pimg)->number) = *((*pimg)->number) + 1;//�摜�̖������{�P
		(*pimg)->Change_img = (imgdate * *)malloc(sizeof(imgdate*));//�ύX�ۑ��p
		(*pimg)->parent_img = (imgdate * *)malloc(sizeof(imgdate*));
		*((*pimg)->Change_img) = NULL;
		*((*pimg)->parent_img) = NULL;
	}
	
	return ;
}

//�摜�\��
void img_display(imgdate** pimg)
{
	

	//�c500 �摜�쐬
	cv::Mat* aimg = new cv::Mat;//�摜�̌^�쐬
	*aimg = ((*(*pimg)->Change_img)->img)->clone();
	resize(*aimg, *aimg, cv::Size(), 500.0 / aimg->rows, 500.0 / aimg->rows);
	Ruled_line(aimg);//(*(*pimg)->Change_img)->img->rows
	cv::imshow("edit_View", *(aimg));

	//�I���W�i���T�C�Y�@�摜�\��
	char name[200];
	strcpy_s(name, "original_view");
	strcpy_s(name, (*pimg)->pas);
	cv::imshow( name, *((*(*pimg)->Change_img)->img));
	cv::waitKey(1);
	
}

//imshow���ړ�
void imshow_move(imgdate** pimg)
{
	char key;
	printf("�G���^�[�ňړ��I��\n");
	//�摜�����
	cv::destroyAllWindows();
	img_display(pimg);

	
	while (true)
	{
		Sleep(50);
		key = cv::waitKey(0);
		if (key == 13) break;
		key = NULL;
	}
}



//���̉摜��
void  next_img(imgdate** pimg)
{
	if ((*pimg)->next != NULL)
	{
		(*pimg) = (*pimg)->next;
	}
	else
	{
		*pimg = *((*pimg)->start);
	}
	//�摜�����
	cv::destroyAllWindows();
	return ;
}

//�O�̉摜��
void back_img(imgdate** pimg)
{
	if ((*pimg)->back != NULL)
	{
		(*pimg) = (*pimg)->back;
	}
	else
	{
		*pimg = *((*pimg)->last);
	}
	//�摜�����
	cv::destroyAllWindows();
	return ;
}

//�摜�ۑ�
void img_Save(imgdate** pimg)
{
	const char pask[6] = "keep/";//�ۑ��t�@�C���p�X
	char pas[100];//�摜�p�X
	cv::Mat* aimg = new cv::Mat;//�摜�̌^�쐬

	for (int i = 0; i < *((*pimg)->number); i++)
	{
		*aimg = ((*(*pimg)->Change_img)->img)->clone();
		strcpy_s(pas, pask);
		strcat_s(pas, (*pimg)->pas);
		try
		{
			cv::imwrite(pas, *aimg);
		}
		catch (const std::exception&)//�G���[����
		{
			printf("�G���[ %s���ۑ�����܂���ł����B", (*pimg)->pas);
		}
		next_img(pimg);
	}
}


//�摜�Ɍr��������
void Ruled_line(cv::Mat* aimg)
{
	cv::Point ptline[2]; //�C�ӂ�2�_��z��ɓ����
	for (int line_num = 1; line_num < 25; line_num++)
	{
		//�c
		ptline[0] = cv::Point(line_num * 20, 0);
		ptline[1] = cv::Point(line_num * 20, 500);
		//�`��@������ (�摜, �_�̔z��, �_�̐�, �F)
		if (line_num % 5)
		{
			cv::fillConvexPoly(*aimg, ptline, 2, cv::Scalar(200, 0, 0));//BGR
		}
		else
		{
			cv::fillConvexPoly(*aimg, ptline, 2, cv::Scalar(0, 0, 200));//BGR
		}
		//��
		ptline[0] = cv::Point(0, line_num * 20);
		ptline[1] = cv::Point(500, line_num * 20);
		//�`��@������ (�摜, �_�̔z��, �_�̐�, �F)
		if (line_num % 5)
		{
			cv::fillConvexPoly(*aimg, ptline, 2, cv::Scalar(255, 0, 0));//BGR
		}
		else
		{
			cv::fillConvexPoly(*aimg, ptline, 2, cv::Scalar(0, 0, 200));//BGR
		}
	}
}

//�摜�ҏW�����̕ۊǏꏊ�쐬
void Change_next_img(imgdate** pimg)
{
	imgdate** Change_img = (*pimg)->Change_img;//�Z�����邽��

	//next�쐬�@1�ځ@����ȍ~��
	if (*((*pimg)->Change_img) != NULL)
	{
		//processing_back���g���Ă�����
		if ((*Change_img)->next != NULL)
		{
			imgdate* img;
			img = (*Change_img)->next;
			while (img->next != NULL)
			{
				img = img->next;
				free(img->back);
			}
			free(img);
		}


		imgdate_Structure(Change_img);

		(*Change_img)->img = new cv::Mat;
		cv::Mat* aimg = new cv::Mat;//�摜�̌^�쐬
		*aimg = (*(*Change_img)->back->img);
		//(*(*Change_img)->img) = (*aimg).clone();

		/**aimg = (*(*pimg)->img);
		resize(*aimg, *aimg, cv::Size(), 2, 2);
		*((*(*pimg)->Change_img)->img) = *aimg;*/

		resize(*aimg, *aimg, cv::Size(), 2, 2);//�A�h���X��ʂɂ��邽��
		(*(*Change_img)->img) = *aimg;
		*aimg = (*(*Change_img)->img);

		resize(*aimg, *aimg, cv::Size(), 0.5, 0.5);
		(*(*Change_img)->img) = *aimg;

		(*Change_img)->parent_img = (*Change_img)->back->parent_img;
		strcpy_s((*Change_img)->pas, (*Change_img)->back->pas);
	}
	else
	{
		imgdate_Structure(Change_img);

		(*Change_img)->img = new cv::Mat;
		cv::Mat* aimg = new cv::Mat;//�摜�̌^�쐬
		*aimg = *((*pimg)->img);
		//(*(*Change_img)->img) = (*aimg).clone();
		resize(*aimg, *aimg, cv::Size(), 2, 2);//�A�h���X��ʂɂ��邽��
		(*(*Change_img)->img) = *aimg;
		*aimg = (*(*Change_img)->img);

		resize(*aimg, *aimg, cv::Size(), 0.5, 0.5);
		(*(*Change_img)->img) = *aimg;

		//resize(*aimg, *aimg, cv::Size(), 2, 2);//�A�h���X��ʂɂ��邽��
		//resize(*aimg, *aimg, cv::Size(), 0.5, 0.5);
		//(*(*Change_img)->img) = *aimg;
		
		(*Change_img)->parent_img = pimg;
		strcpy_s((*Change_img)->pas, (*pimg)->pas);
	}
	
	//�ҏW������11�ȏ�Ȃ�@�P����
	if ((*Change_img)->situation >= 11)
	{
		Change_next_img_delete(Change_img);
	}

	

}

//Change ����@
void Change_next_img_delete(imgdate** Change_img)
{
	(*((*Change_img)->start)) = (*((*Change_img)->start))->next;
	free((*((*Change_img)->start))->back);
	(*((*Change_img)->start))->back = NULL;

	(*Change_img)->situation = (*Change_img)->situation - 1;
}

//���H��O��
void processing_back(imgdate** pimg)
{
	bool flg = false;
	if (*((*pimg)->Change_img) != NULL)
	{
		if ((*((*pimg)->Change_img))->back != NULL)
		{
			((*((*pimg)->Change_img))) = ((*((*pimg)->Change_img)))->back;
			((*((*pimg)->Change_img)))->situation = (*((*pimg)->Change_img))->situation - 1;
		}
		else
		{
			flg = true;
		}
	}
	if (flg) printf("����܂���");
}

//���H������
void processing_next(imgdate** pimg)
{
	bool flg= false;
	if (((*((*pimg)->Change_img))) != NULL)
	{
		if ((*((*pimg)->Change_img))->next != NULL)
		{
			((*((*pimg)->Change_img))) = ((*((*pimg)->Change_img)))->next;
			((*((*pimg)->Change_img)))->situation = ((*((*pimg)->Change_img)))->situation + 1;
		}
		else
		{
			flg = true;
		}
	}
	if(flg) printf("����܂���");

}

//�w�薇���@�摜�ړ�
void specify_move_img(imgdate** pimg, int i)
{
	if (i > 0)
	{
		//�w�薇���@���̉摜
		for (int j = 0; j < i; j++)
			next_img(pimg);
	}
	else if (i < 0)
	{
		//�w�薇���@�O�̉摜
		i = i * -1;
		for (int j = 0; j < i; j++)
			back_img(pimg);
	}
}



//�T�C�Y�ύX
void size_Change(imgdate** pimg)
{
	char command[10];
	int CoFlg = -1;

	//�������
	while (true)
	{


		printf("\n\n\n\n");
		printf("�R�}���h\n");
		printf("| �T�C�Y�̕ύX | Yes/y | No/n |\n");
		scanf_s("%s[^\0]", command, 10);
		//���͗]�����
		gomi();
		//��������
		lowerstring(command, command);
		CoFlg = 0;
		if (strcmp(command, "yes") == 0) CoFlg = 1;
		if (strcmp(command, "y") == 0) CoFlg = 1;
		if (strcmp(command, "no") == 0) CoFlg = -1;
		if (strcmp(command, "n") == 0) CoFlg = -1;

		if (CoFlg == 1)
		{
			while (true)
			{
				printf("\n\n\n\n");
				img_display(pimg);
				printf("| �T�C�Y�̕ύX |\n");
				printf("| ����/s | �䗦_�c/v | �䗦_��/b | �w��/s  | �摜�O��/ib | �摜����/in | 00�ړ���/m | �ҏW�O��/eb | �ҏW����/en | �摜�ړ�/im | ���Z�b�g/r |\n");
				printf("|  save  |  vertical |   beside  | specify |  img_back   |   imt_next  |     move     |  edit_back  |  edit_next  | imshow_move |  reset     |\n");

				scanf_s("%s[^\0]", command, 10);
				//���͗]�����
				gomi();
				//��������
				lowerstring(command, command);
				CoFlg = -1;//������
				if (strcmp(command, "vertical") == 0)	CoFlg = 0;
				if (strcmp(command, "v") == 0)	CoFlg = 0;
				if (strcmp(command, "beside") == 0)	CoFlg = 1;
				if (strcmp(command, "b") == 0)	CoFlg = 1;
				if (strcmp(command, "specify") == 0)	CoFlg = 2;
				if (strcmp(command, "sp") == 0)	CoFlg = 2;
				if (strcmp(command, "img_back") == 0)	CoFlg = 3;
				if (strcmp(command, "ib") == 0)	CoFlg = 3;
				if (strcmp(command, "imt_next") == 0)	CoFlg = 4;
				if (strcmp(command, "in") == 0)	CoFlg = 4;
				if (strcmp(command, "move") == 0)	CoFlg = 5;
				if (strcmp(command, "m") == 0)	CoFlg = 5;
				if (strcmp(command, "edit_back") == 0)	CoFlg = 6;
				if (strcmp(command, "eb") == 0)	CoFlg = 6;
				if (strcmp(command, "edit_next") == 0)	CoFlg = 7;
				if (strcmp(command, "en") == 0)	CoFlg = 7;
				if (strcmp(command, "imshow_move") == 0)	CoFlg = 8;
				if (strcmp(command, "im") == 0)	CoFlg = 8;
				if (strcmp(command, "reset") == 0)	CoFlg = 9;
				if (strcmp(command, "r") == 0)	CoFlg = 9;
				if (strcmp(command, "save") == 0)	break;
				if (strcmp(command, "s") == 0)	break;

				size_Change_process(pimg, CoFlg);

			}
		}

		if (CoFlg == -1)
		{
			break;
		}
		else
		{
			printf("���̓G���[");
		}
	}
}

//�T�C�Y�ύX����
void size_Change_process(imgdate** pimg, int CoFlg)
{
	int i;
	cv::Mat* aimg = new cv::Mat;//�摜�̌^�쐬
	float size[2];

	switch (CoFlg)
	{
	case(0):
		printf("| �䗦_�c  | �c�̒��������\n");
		scanf_s("%f", &size[0]);
		//���͗]�����
		gomi();

		Change_next_img(pimg);
		*aimg = (*(*pimg)->img);
		resize(*aimg, *aimg, cv::Size(), size[0] / aimg->rows, size[0] / aimg->rows);
		*((*(*pimg)->Change_img)->img) = *aimg;
		cv::imshow("edit_View", *((*(*pimg)->Change_img)->img));
		break;

	case(1):
		printf("| �䗦_��  | ���̒��������\n");
		scanf_s("%f", &size[0]);
		//���͗]�����
		gomi();

		Change_next_img(pimg);
		*aimg = (*(*pimg)->img);
		resize(*aimg, *aimg, cv::Size(), size[0] / aimg->cols, size[0] / aimg->cols);
		*((*(*pimg)->Change_img)->img) = *aimg;
		cv::imshow("edit_View", *((*(*pimg)->Change_img)->img));
		break;

	case(2):
		printf("| �w��  | �T�C�Y�����\n");
		printf("| �c�̃T�C�Y |\n");
		scanf_s("%f", &size[0]);
		//���͗]�����
		gomi();
		printf("| ���̃T�C�Y |\n");
		scanf_s("%f", &size[1]);
		//���͗]�����
		gomi();

		Change_next_img(pimg);
		*aimg = (*(*pimg)->img);
		resize(*aimg, *aimg, cv::Size(), size[1] / aimg->cols, size[0] / aimg->rows);
		*((*(*pimg)->Change_img)->img) = *aimg;
		cv::imshow("edit_View", *((*(*pimg)->Change_img)->img));
		break;

	case(3)://�O�̉摜
		back_img(pimg);
		break;

	case(4)://���̉摜
		next_img(pimg);
		break;

	case(5)://�摜�I��
		printf("�����ړ����܂����H �}�C�i�X���\");
		scanf_s("%d", &i);
		gomi();//���͗]�����
		specify_move_img(pimg, i);
		break;

	case(6)://���H���P�߂��摜

		processing_back(pimg);
		next_img(pimg);
		break;

	case(7)://���H���P���։摜�@�i�P�߂����ꍇ�j

		processing_next(pimg);
		next_img(pimg);
		break;

	case(8):
		imshow_move(pimg);
		break;

	case(9):
			(*(*pimg)->Change_img)->img = (*pimg)->img;
		break;

	default:
		printf("�R�}���h�G���[");
		break;
	}
}

//�T�C�Y�ύX(�ꊇ)
void size_Change_multiple(imgdate** pimg)
{
	char command[10];
	int CoFlg = -1;

	while (true)
	{
		//�������
		printf("\n\n\n\n");
		printf("�R�}���h\n");
		img_display(pimg);
		printf("| �T�C�Y�̕ύX | Yes/y | No/n |\n");
		scanf_s("%s[^\0]", command, 10);
		//���͗]�����
		gomi();
		//��������
		lowerstring(command, command);
		CoFlg = 0;
		if (strcmp(command, "yes") == 0) CoFlg = 1;
		if (strcmp(command, "y") == 0) CoFlg = 1;
		if (strcmp(command, "no") == 0) CoFlg = -1;
		if (strcmp(command, "n") == 0) CoFlg = -1;

		if (CoFlg == 1)
		{
			while (true)
			{

				img_display(pimg);
				printf("\n\n\n\n");
				printf("| �T�C�Y�̕ύX |\n");
				printf("| ����/s | �䗦_�c/v | �䗦_��/b | �w��/sp | �ҏW�O��/eb | �ҏW����/en | �摜�ړ�/im | ���Z�b�g/r |\n");
				printf("|  save  |  vertical |   beside  | specify |  edit_back  |  edit_next  | imshow_move |  reset     | \n");
				scanf_s("%s[^\0]", command, 10);
				//���͗]�����
				gomi();
				//��������
				lowerstring(command, command);
				CoFlg = -1;//������
				if (strcmp(command, "vertical") == 0)	CoFlg = 0;
				if (strcmp(command, "v") == 0)	CoFlg = 0;
				if (strcmp(command, "beside") == 0)	CoFlg = 1;
				if (strcmp(command, "b") == 0)	CoFlg = 1;
				if (strcmp(command, "specify") == 0)	CoFlg = 2;
				if (strcmp(command, "sp") == 0)	CoFlg = 2;
				if (strcmp(command, "edit_back") == 0)	CoFlg = 3;
				if (strcmp(command, "eb") == 0)	CoFlg = 3;
				if (strcmp(command, "edit_next") == 0)	CoFlg = 4;
				if (strcmp(command, "en") == 0)	CoFlg = 4;
				if (strcmp(command, "imshow_move") == 0)	CoFlg = 5;
				if (strcmp(command, "im") == 0)	CoFlg = 5;
				if (strcmp(command, "reset") == 0)	CoFlg = 6;
				if (strcmp(command, "r") == 0)	CoFlg = 6;
				if (strcmp(command, "save") == 0)	break;
				if (strcmp(command, "s") == 0)	break;

				try
				{
					size_Change_process_multiple(pimg, CoFlg);
				}
				catch (const std::exception&)
				{
					printf("���̓G���[");
				}
			}
		}
		if (CoFlg == -1)
		{
			break;
		}
		else
		{
			printf("���̓G���[");
		}
	}
}


//�T�C�Y�ύX����(�ꊇ)
void size_Change_process_multiple(imgdate** pimg, int CoFlg)
{
	cv::Mat* aimg = new cv::Mat;//�摜�̌^�쐬
	float size[2];

	switch (CoFlg)
	{

	case(0):
		printf("| �䗦_�c  | �c�̒��������\n");
		scanf_s("%f", &size[0]);
		//���͗]�����
		gomi();

		for (int loop = 0; loop < *((*pimg)->number); loop++)
		{
			Change_next_img(pimg);
			*aimg = (*(*pimg)->img);
			resize(*aimg, *aimg, cv::Size(), size[0] / aimg->rows, size[0] / aimg->rows);
			*((*(*pimg)->Change_img)->img) = *aimg;
			
			next_img(pimg);
		}
		(*pimg) = *((*pimg)->start);

		break;

	case(1):
		printf("| �䗦_��  | ���̒��������\n");
		scanf_s("%f", &size[0]);
		//���͗]�����
		gomi();

		for (int loop = 0; loop < *((*pimg)->number); loop++)
		{
			Change_next_img(pimg);
			*aimg = (*(*pimg)->img);
			resize(*aimg, *aimg, cv::Size(), size[0] / aimg->cols, size[0] / aimg->cols);
			*((*(*pimg)->Change_img)->img) = *aimg;

			next_img(pimg);
		}
		(*pimg) = *((*pimg)->start);

		break;

	case(2):
		printf("| �w��  | �T�C�Y�����\n");
		printf("| �c�̃T�C�Y |\n");
		scanf_s("%f", &size[0]);
		//���͗]�����
		gomi();
		printf("| ���̃T�C�Y |\n");
		scanf_s("%f", &size[1]);
		//���͗]�����
		gomi();

		

		for (int loop = 0; loop < *((*pimg)->number); loop++)
		{
			Change_next_img(pimg);
			*aimg = (*(*pimg)->img);
			
				resize(*aimg, *aimg, cv::Size(), size[1] / aimg->cols, size[0] / aimg->rows);
			
			*((*(*pimg)->Change_img)->img) = *aimg;

			next_img(pimg);
		}
		(*pimg) = *((*pimg)->start);
		
		break;

	case(3)://���H���P�߂��摜

		for (int i = 0; i < *((*pimg)->number); i++)
		{
			processing_back(pimg);
			next_img(pimg);
		}
		(*pimg) = *((*pimg)->start);
		break;

	case(4)://���H���P���։摜�@�i�P�߂����ꍇ�j

		for (int i = 0; i < *((*pimg)->number); i++)
		{
			processing_next(pimg);
			next_img(pimg);
		}
		(*pimg) = *((*pimg)->start);
		break;

	case(5):
		imshow_move(pimg);
		break;

	case(6):
		for (int i = 0; i < *((*pimg)->number); i++)
		{
			(*(*pimg)->Change_img)->img = (*pimg)->img;
			next_img(pimg);
		}
		(*pimg) = *((*pimg)->start);
		break;

	default:
		printf("�R�}���h�G���[");
		break;
	}
}