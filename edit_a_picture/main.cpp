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
	imgdate** Change_img = (imgdate * *)malloc(sizeof(imgdate*));//�ύX�ۑ��p
};

//�O
//call
void COLOR(imgdate** pimg, int num);
void imgdate_Structure(imgdate** pimg);
void img_display(imgdate** pimg);
void imshow_move(imgdate** pimg);
void back_img(imgdate** pimg);
void next_img(imgdate** pimg);
void img_Save(imgdate** pimg);
void Ruled_line(cv::Mat* aimg);
void Change_next_img(imgdate** Change_img);
void processing_back(imgdate** pimg);
void processing_next(imgdate** pimg);
void specify_move_img(imgdate** pimg, int i);
void size_Change(imgdate** pimg);
void size_Change_multiple(imgdate** pimg);
//edit__multiple
void edit_main(imgdate** pimg);
void edit_main_multiple(imgdate** pimg);
//Other codes
void lowerstring(char* out, const char* in);
void gomi();

int main(void)
{
	/*try
	{*/
		//�摜�@�ǂݍ��݁E�o��
		const char pasr[6] = "read/";//�ǂݍ��݃t�@�C���p�X
		const char pask[6] = "keep/";//�ۑ��t�@�C���p�X
		char pas[100];//�摜�p�X
		WIN32_FIND_DATA ffd;//�摜���

		//�\���̗p
		cv::Mat* aimg = new cv::Mat;//�摜�̌^�쐬
		HANDLE hFind = INVALID_HANDLE_VALUE;//�摜�n���h��
		imgdate** pimg = (imgdate**)malloc(sizeof(imgdate*));//�摜�\����
		*pimg = NULL;

		//���̑�
		int move_mun = 0;//�摜���ړ����閇��
		char command[20];//�R�}���h�ۊ�
		int CoFlg = -1;//�R�}���h�t���b�N
		bool end_flg = false;//�I�����邩
		bool Image_loading_flg = false;//�摜�ǂݍ��߂����H

		//�摜�ǂݍ��ݏ���

		//�s���I�h����
		hFind = FindFirstFile("read/*", &ffd);
		FindNextFile(hFind, &ffd);
		//�摜�ǂݍ���
		printf("�ǂݍ��݉摜\n");

		//�ǂݍ���
		while (FALSE != FindNextFile(hFind, &ffd))
		{
			Image_loading_flg = true;//�摜��ǂݍ��߂���
			imgdate_Structure(pimg);//�摜�\���̍쐬
			strcpy_s(((*pimg)->pas), ffd.cFileName);//�摜���ۊ�
			printf("%s\n", ffd.cFileName);//�摜���\��
			strcpy_s(pas, pasr);//�p�X�A������
			strcat_s(pas, ffd.cFileName);//�p�X�A�Z�b�g

			cv::Mat* aimg = new cv::Mat;//�摜�̌^�쐬
			try//�摜�ǂݍ���
			{
				*aimg = cv::Mat(cv::imread(pas, -1));
				((*pimg)->img) = aimg;
			}
			catch (const std::exception&)//�G���[����
			{
				printf("�摜�ȊO��read�t�@�C���Ɋ܂܂�Ă���\��������܂��B");
				return -1;
			}
			//���H�ۑ���쐬
			Change_next_img(pimg);
		}
		printf("\n");




		//�摜�ҏW
		if (Image_loading_flg)
		{
			//�ҏW���@�I��
			while (CoFlg == -1)
			{
				printf("| 1�����ƕҏW/o | �ꊇ�ҏW/b | ����/e |\n");
				printf("|   one_sheet   |    bulk    |   exit   | \n");

				scanf_s("%s[^\0]", command, 20);
				//���͗]�����
				gomi();
				//��������
				lowerstring(command, command);

				if (strcmp(command, "one_sheet") == 0)	CoFlg = 0;
				if (strcmp(command, "o") == 0)	CoFlg = 0;
				if (strcmp(command, "bulk") == 0)	CoFlg = 1;
				if (strcmp(command, "b") == 0)	CoFlg = 1;
				if (strcmp(command, "exit") == 0)	CoFlg = 2;
				if (strcmp(command, "e") == 0)	CoFlg = 2;
			}

			if (0 == CoFlg)//�ꖇ������
			{
				//�ǂݍ��݃��[�h
				while (true)
				{
					//�摜�\��
					img_display(pimg);

					//�������
					printf("\n\n\n\n");
					printf("�摜�̓ǂݍ��݂��w�� �R�}���h\n");
					printf("| ����/s | �L�����Z��/ca | �t���f�[�^/a | �J���[/co | ���m�N��/mh |\n");
					printf("| save   |   cancel      |     all      |  color    |  monochrome |\n");
					printf("| �摜�O��/ib | �摜����/in | 00�ړ���/mo | �摜�ړ�/im |\n");
					printf("|  img_back   |  img_next   |    move       | imshow_move |\n");

					scanf_s("%s[^\0]", command, 20);
					//���͗]�����
					gomi();
					//��������
					lowerstring(command, command);

					//�ϊ��@switch�Ŏg�p�̂���
					CoFlg = -1;//������
					if (strcmp(command, "save") == 0)	CoFlg = 0;
					if (strcmp(command, "s") == 0)	CoFlg = 0;
					if (strcmp(command, "cancel") == 0)	CoFlg = 1;
					if (strcmp(command, "ca") == 0)	CoFlg = 1;
					if (strcmp(command, "all") == 0)	CoFlg = 2;
					if (strcmp(command, "a") == 0)	CoFlg = 2;
					if (strcmp(command, "color") == 0)	CoFlg = 3;
					if (strcmp(command, "co") == 0)	CoFlg = 3;
					if (strcmp(command, "monochrome") == 0)	CoFlg = 4;
					if (strcmp(command, "mh") == 0)	CoFlg = 4;
					if (strcmp(command, "img_back") == 0)	CoFlg = 5;
					if (strcmp(command, "ib") == 0)	CoFlg = 5;
					if (strcmp(command, "img_next") == 0)	CoFlg = 6;
					if (strcmp(command, "in") == 0)	CoFlg = 6;
					if (strcmp(command, "move") == 0)	CoFlg = 7;
					if (strcmp(command, "mo") == 0)	CoFlg = 7;
					if (strcmp(command, "imshow_move") == 0)	CoFlg = 8;
					if (strcmp(command, "im") == 0)	CoFlg = 8;

					//�摜�ǂݍ��ݎ��
					switch (CoFlg)
					{
					case(0)://s ����
						end_flg = true;
						break;

					case(1)://esc �L�����Z��
						printf("�L�����Z�����܂����B");
						return 0;
						break;

					case(2)://�A���t�@�`�����l��
						COLOR((*pimg)->Change_img, -1);
						break;

					case(3)://�J���|
						COLOR((*pimg)->Change_img, 1);
						break;

					case(4)://�O���[�X�P�[��
						COLOR((*pimg)->Change_img, 0);
						break;

					case(5)://�O�̉摜
						back_img(pimg);
						break;

					case(6)://���̉摜
						next_img(pimg);
						break;

					case(7)://�摜�I��
						try
						{
							printf("�����ړ����܂����H �}�C�i�X���\");
							scanf_s("%d", &move_mun);
							//���͗]�����
							gomi();

							specify_move_img(pimg, move_mun);
						}
						catch (const std::exception&)//�G���[����
						{
							printf("���̓G���[");
						}
						break;
					case(8):
						imshow_move(pimg);
						break;

					default:
						printf("�R�}���h�G���[");
						break;
					}
					//���[�v������
					if (end_flg) break;
				}

				//���Z�b�g
				end_flg = false;
				//�ύX���Z�b�g
				for (int i = 0; i < *((*pimg)->number); i++)
				{
					(*pimg)->img = (*((*pimg)->Change_img))->img;
					next_img(pimg);
				}

				//�T�C�Y�ݒ�
				size_Change(pimg);

				//�ύX���Z�b�g
				/*float colsbox;
				float rowsbox;

				for (int loop = 0; loop < *((*pimg)->number); loop++)
				{
					Change_next_img(pimg);
					*aimg = *((*(*pimg)->Change_img)->img);
					colsbox =  (aimg->cols);
					rowsbox =  (aimg->rows);
					resize(*aimg, *aimg, cv::Size(), 300.0 / aimg->cols, 300.0 / aimg->rows);
					resize(*aimg, *aimg, cv::Size(), 240.0 / aimg->cols, 240.0 / aimg->rows);

					*((*(*pimg)->Change_img)->img) = *aimg;

					next_img(pimg);
				}
				(*pimg) = *((*pimg)->start);*/

				for (int i = 0; i < *((*pimg)->number); i++)
				{
					*((*pimg)->img) = (*((*pimg)->Change_img))->img->clone();
					next_img(pimg);
				}


				//�ҏW
				while (true)
				{
					//�摜�\��
					img_display(pimg);

					//�������
					printf("\n\n\n\n");
					printf("�R�}���h\n");
					printf("| �I��/e | �ۑ�/s | ���Z�b�g/r | �摜�O��/ib | �摜����/in | 00�ړ���/m |\n");
					printf("| eixt   | save   |  reset     |  img_back   |   imt_next  |     move     |\n");
					printf("| �ҏW�O��/eb | �ҏW����/en |  �`��/d | �摜�ړ�/im |\n");
					printf("|   edit_back |   edit_next | drawing | imshow_move |\n");
					scanf_s("%s[^\0]", command, 20);
					//���͗]�����
					gomi();
					//��������
					lowerstring(command, command);

					/*** �R�}���h���t���O�ɕϊ��@�X�C�b�`���p ***/
					//�ϊ��@switch�Ŏg�p�̂���
					CoFlg = -1;//������
					if (strcmp(command, "exit") == 0)	CoFlg = 0;
					if (strcmp(command, "e") == 0)	CoFlg = 0;
					if (strcmp(command, "save") == 0)	CoFlg = 1;
					if (strcmp(command, "s") == 0)	CoFlg = 1;
					if (strcmp(command, "reset") == 0)	CoFlg = 2;
					if (strcmp(command, "r") == 0)	CoFlg = 2;
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
					if (strcmp(command, "drawing") == 0)	CoFlg = 8;
					if (strcmp(command, "d") == 0)	CoFlg = 8;
					if (strcmp(command, "imshow_move") == 0)	CoFlg = 9;
					if (strcmp(command, "im") == 0)	CoFlg = 9;

					//�ҏW
					switch (CoFlg)
					{
					case(0)://esc �I��
						end_flg = true;
						break;
					case(1)://s �ۑ�
						end_flg = true;
						break;

					case(2)://���Z�b�g
						(*(*pimg)->Change_img)->img = (*pimg)->img;
						break;

					case(3)://�O�̉摜
						back_img(pimg);
						break;

					case(4)://���̉摜
						next_img(pimg);
						break;

					case(5)://�摜�I��
						try
						{
							printf("�����ړ����܂����H �}�C�i�X���\");
							scanf_s("%d", &move_mun);

							//���͗]�����
							gomi();

							specify_move_img(pimg, move_mun);
						}
						catch (const std::exception&)//�G���[����
						{
							printf("���̓G���[");
						}

						break;

					case(6)://���H���P�߂��摜

						processing_back(pimg);
						//next_img(pimg);
						break;

					case(7)://���H���P���։摜�@�i�P�߂����ꍇ�j

						processing_next(pimg);
						//next_img(pimg);
						break;

					case (8)://�`��(edit)
						edit_main(pimg);
						break;

					case(9):
						imshow_move(pimg);
						break;

					default:
						printf("�R�}���h�G���[");
						break;
					}

					//���[�v������
					if (end_flg) break;
				}

				//�ۑ�����
				if (1 == CoFlg)
				{
					//�ۑ�����
					img_Save(pimg);
					printf("\n�ۑ�����\n");
					return 1;
				}
				else
				{
					printf("\n�ۑ�����܂���ł���\n");
					return 0;
				}
			}


			/////////////////////////////////////////////////////////////////////////////

			else if (1 == CoFlg)//�ꊇ����
			{

				(*pimg) = *((*pimg)->start);

				//�ǂݍ��݃��[�h
				while (true)
				{
					//�摜�\��
					img_display(pimg);

					//�R�}���h
					printf("\n\n\n\n");
					printf("�摜�̓ǂݍ��݂��w�� �R�}���h\n");
					printf("| ����/s | �L�����Z��/ca | �t���f�[�^/a | �J���[/co | ���m�N��/m | �摜�ړ�/im |\n");
					printf("| save   |   cancel      |     all      |   color   | monochrome | imshow_move |\n");
					scanf_s("%s[^\0]", command, 20);
					//���͗]�����
					gomi();
					//��������
					lowerstring(command, command);

					//�ϊ��@switch�Ŏg�p�̂���
					CoFlg = -1;//������
					if (strcmp(command, "save") == 0)	CoFlg = 0;
					if (strcmp(command, "s") == 0)	CoFlg = 0;
					if (strcmp(command, "cancel") == 0)	CoFlg = 1;
					if (strcmp(command, "ca") == 0)	CoFlg = 1;
					if (strcmp(command, "all") == 0)	CoFlg = 2;
					if (strcmp(command, "a") == 0)	CoFlg = 2;
					if (strcmp(command, "color") == 0)	CoFlg = 3;
					if (strcmp(command, "co") == 0)	CoFlg = 3;
					if (strcmp(command, "monochrome") == 0)	CoFlg = 4;
					if (strcmp(command, "m") == 0)	CoFlg = 4;
					if (strcmp(command, "imshow_move") == 0)	CoFlg = 5;
					if (strcmp(command, "im") == 0)	CoFlg = 5;

					//�摜�ǂݍ��ݎ��
					switch (CoFlg)
					{
					case(0)://s ����
						end_flg = true;
						break;

					case(1)://esc �L�����Z��
						printf("�L�����Z�����܂����B");
						return 0;
						break;

					case(2)://�A���t�@�`�����l��
						for (int i = 0; i < *((*pimg)->number); i++)
						{
							COLOR((*pimg)->Change_img, -1);
							next_img(pimg);
						}
						(*pimg) = *((*pimg)->start);
						break;

					case(3)://�J���|
						for (int i = 0; i < *((*pimg)->number); i++)
						{
							COLOR((*pimg)->Change_img, 1);
							next_img(pimg);
						}
						(*pimg) = *((*pimg)->start);
						break;

					case(4)://�O���[�X�P�[��
						for (int i = 0; i < *((*pimg)->number); i++)
						{
							COLOR((*pimg)->Change_img, 0);
							next_img(pimg);
						}
						(*pimg) = *((*pimg)->start);
						break;

					case(5):
						imshow_move(pimg);
						break;

					default:
						printf("�R�}���h�G���[");
						break;

					}
					//���[�v������
					if (end_flg) break;
				}
				//���Z�b�g
				end_flg = false;

				//�ύX���Z�b�g
				for (int i = 0; i < *((*pimg)->number); i++)
				{
					(*pimg)->img = (*((*pimg)->Change_img))->img;
					next_img(pimg);
				}

				//�T�C�Y�ݒ�
				size_Change_multiple(pimg);

				//�ύX���Z�b�g
				for (int i = 0; i < *((*pimg)->number); i++)
				{
					(*pimg)->img = (*((*pimg)->Change_img))->img;
					next_img(pimg);
				}

				//�ҏW
				while (true)
				{
					//�摜�\��
					img_display(pimg);

					//�R�}���h
					printf("\n\n\n\n");
					printf("�R�}���h\n");
					printf("| �I��/e | �ۑ�/s | ���Z�b�g/r | �ҏW�O��/eb | �ҏW����/en |  �`��/d | �摜�ړ�/im |\n");
					printf("| eixt   | save   |  reset     | edit_back   | edit_next   | drawing | imshow_move |\n");
					scanf_s("%s[^\0]", command, 20);
					//���͗]�����
					gomi();
					//��������
					lowerstring(command, command);

					/*** �R�}���h���t���O�ɕϊ��@�X�C�b�`���p ***/
					//�ϊ��@switch�Ŏg�p�̂���
					CoFlg = -1;//������
					if (strcmp(command, "exit") == 0)	CoFlg = 0;
					if (strcmp(command, "e") == 0)	CoFlg = 0;
					if (strcmp(command, "save") == 0)	CoFlg = 1;
					if (strcmp(command, "s") == 0)	CoFlg = 1;
					if (strcmp(command, "reset") == 0)	CoFlg = 2;
					if (strcmp(command, "r") == 0)	CoFlg = 2;
					if (strcmp(command, "edit_back") == 0)	CoFlg = 3;
					if (strcmp(command, "eb") == 0)	CoFlg = 3;
					if (strcmp(command, "edit_next") == 0)	CoFlg = 4;
					if (strcmp(command, "en") == 0)	CoFlg = 4;
					if (strcmp(command, "drawing") == 0)	CoFlg = 5;
					if (strcmp(command, "d") == 0)	CoFlg = 5;
					if (strcmp(command, "imshow_move") == 0)	CoFlg = 6;
					if (strcmp(command, "im") == 0)	CoFlg = 6;

					switch (CoFlg)
					{
					case(0)://esc �I��
						end_flg = true;
						break;
					case(1)://s �ۑ�
						end_flg = true;
						break;

					case(2)://���Z�b�g
						for (int i = 0; i < *((*pimg)->number); i++)
						{
							(*(*pimg)->Change_img)->img = (*pimg)->img;
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

					case (5)://�`��(edit)
						edit_main_multiple(pimg);
						break;

					case(6):
						imshow_move(pimg);
						break;

					default:
						printf("�R�}���h�G���[");
						break;
					}
					//���[�v������
					if (end_flg) break;

					//�R�}���h�\��

				}
				//�ۑ�����
				if (1 == CoFlg)
				{
					//�ۑ�����
					img_Save(pimg);
					printf("\n�ۑ�����\n");
					return 1;
				}
			}
		}
		else
		{
			printf("\n�摜�Ȃ�\n");
			return -1;
		}
		//�摜�����
		cv::destroyAllWindows();
		printf("\n�ۑ�����܂���ł���\n");
		return 0;
	//}
	//catch (const std::exception&)//�G���[����
	//{
	//	printf("�G���[");
	//	return -10;
	//}
}