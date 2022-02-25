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

//外
//Other codes
void lowerstring(char* out, const char* in);
void gomi();
//内
 void COLOR_process(char pas1[], cv::Mat* img, int num);					//画像読み込み前処理
 void COLOR(imgdate** pimg, int num);										//画像読み込み
 void imgdate_Structure(imgdate** pimg);									//画像構造体作成
 void img_display(imgdate** pimg);											//画像表示
 void imshow_move(imgdate** pimg);											//imshowを移動
 void next_img(imgdate** pimg);												//次の画像へ
 void back_img(imgdate** pimg);												//前の画像へ
 void img_Save(imgdate** pimg);												//画像保存
 void Ruled_line(cv::Mat* aimg);											//画像に罫線を引く
 void Change_next_img(imgdate** Change_img);								//画像編集履歴の保管場所作成
 void Change_next_img_delete(imgdate** Change_img);							//Change 解放　
 void processing_back(imgdate** pimg);										//加工を前へ
 void processing_next(imgdate** pimg);										//加工を次へ
 void specify_move_img(imgdate** pimg, int i);								//指定枚数　画像移動
 void size_Change(imgdate** pimg);											//サイズ変更
 void size_Change_process(imgdate** pimg, int CoFlg);						//サイズ変更処理
 void size_Change_multiple(imgdate** pimg);									//サイズ変更(一括)
 void size_Change_process_multiple(imgdate** pimg, int CoFlg);				//サイズ変更処理(一括)




 //画像読み込み前処理
void COLOR(imgdate** pimg, int num)
{
	//パスセット
	char pas1[100] = "read/";
	strcat_s(pas1, (*pimg)->pas);
	//例外処理と　変更なし
	if (num == (*pimg)->situation) return;
	if (num != 0)if (num != 1) if (num != -1) return;
	//画像呼び出す
	(*pimg)->situation = num;
	COLOR_process(pas1, (*pimg)->img,num);
}

//画像読み込み
void COLOR_process(char pas1[], cv::Mat* img, int num)
{
	*img = cv::imread(pas1, num);
}

//画像構造体作成
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
		(*pimg)->number = new int(1);;//画像の枚数を１セット
		(*pimg)->Change_img = (imgdate * *)malloc(sizeof(imgdate*));//変更保存用
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
		*((*pimg)->number) = *((*pimg)->number) + 1;//画像の枚数を＋１
		(*pimg)->Change_img = (imgdate * *)malloc(sizeof(imgdate*));//変更保存用
		(*pimg)->parent_img = (imgdate * *)malloc(sizeof(imgdate*));
		*((*pimg)->Change_img) = NULL;
		*((*pimg)->parent_img) = NULL;
	}
	
	return ;
}

//画像表示
void img_display(imgdate** pimg)
{
	

	//縦500 画像作成
	cv::Mat* aimg = new cv::Mat;//画像の型作成
	*aimg = ((*(*pimg)->Change_img)->img)->clone();
	resize(*aimg, *aimg, cv::Size(), 500.0 / aimg->rows, 500.0 / aimg->rows);
	Ruled_line(aimg);//(*(*pimg)->Change_img)->img->rows
	cv::imshow("edit_View", *(aimg));

	//オリジナルサイズ　画像表示
	char name[200];
	strcpy_s(name, "original_view");
	strcpy_s(name, (*pimg)->pas);
	cv::imshow( name, *((*(*pimg)->Change_img)->img));
	cv::waitKey(1);
	
}

//imshowを移動
void imshow_move(imgdate** pimg)
{
	char key;
	printf("エンターで移動終了\n");
	//画像を閉じる
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



//次の画像へ
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
	//画像を閉じる
	cv::destroyAllWindows();
	return ;
}

//前の画像へ
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
	//画像を閉じる
	cv::destroyAllWindows();
	return ;
}

//画像保存
void img_Save(imgdate** pimg)
{
	const char pask[6] = "keep/";//保存ファイルパス
	char pas[100];//画像パス
	cv::Mat* aimg = new cv::Mat;//画像の型作成

	for (int i = 0; i < *((*pimg)->number); i++)
	{
		*aimg = ((*(*pimg)->Change_img)->img)->clone();
		strcpy_s(pas, pask);
		strcat_s(pas, (*pimg)->pas);
		try
		{
			cv::imwrite(pas, *aimg);
		}
		catch (const std::exception&)//エラー処理
		{
			printf("エラー %sが保存されませんでした。", (*pimg)->pas);
		}
		next_img(pimg);
	}
}


//画像に罫線を引く
void Ruled_line(cv::Mat* aimg)
{
	cv::Point ptline[2]; //任意の2点を配列に入れる
	for (int line_num = 1; line_num < 25; line_num++)
	{
		//縦
		ptline[0] = cv::Point(line_num * 20, 0);
		ptline[1] = cv::Point(line_num * 20, 500);
		//描画　引数は (画像, 点の配列, 点の数, 色)
		if (line_num % 5)
		{
			cv::fillConvexPoly(*aimg, ptline, 2, cv::Scalar(200, 0, 0));//BGR
		}
		else
		{
			cv::fillConvexPoly(*aimg, ptline, 2, cv::Scalar(0, 0, 200));//BGR
		}
		//横
		ptline[0] = cv::Point(0, line_num * 20);
		ptline[1] = cv::Point(500, line_num * 20);
		//描画　引数は (画像, 点の配列, 点の数, 色)
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

//画像編集履歴の保管場所作成
void Change_next_img(imgdate** pimg)
{
	imgdate** Change_img = (*pimg)->Change_img;//短くするため

	//next作成　1個目　それ以降か
	if (*((*pimg)->Change_img) != NULL)
	{
		//processing_backを使っていたら
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
		cv::Mat* aimg = new cv::Mat;//画像の型作成
		*aimg = (*(*Change_img)->back->img);
		//(*(*Change_img)->img) = (*aimg).clone();

		/**aimg = (*(*pimg)->img);
		resize(*aimg, *aimg, cv::Size(), 2, 2);
		*((*(*pimg)->Change_img)->img) = *aimg;*/

		resize(*aimg, *aimg, cv::Size(), 2, 2);//アドレスを別にするため
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
		cv::Mat* aimg = new cv::Mat;//画像の型作成
		*aimg = *((*pimg)->img);
		//(*(*Change_img)->img) = (*aimg).clone();
		resize(*aimg, *aimg, cv::Size(), 2, 2);//アドレスを別にするため
		(*(*Change_img)->img) = *aimg;
		*aimg = (*(*Change_img)->img);

		resize(*aimg, *aimg, cv::Size(), 0.5, 0.5);
		(*(*Change_img)->img) = *aimg;

		//resize(*aimg, *aimg, cv::Size(), 2, 2);//アドレスを別にするため
		//resize(*aimg, *aimg, cv::Size(), 0.5, 0.5);
		//(*(*Change_img)->img) = *aimg;
		
		(*Change_img)->parent_img = pimg;
		strcpy_s((*Change_img)->pas, (*pimg)->pas);
	}
	
	//編集履歴が11以上なら　１個消す
	if ((*Change_img)->situation >= 11)
	{
		Change_next_img_delete(Change_img);
	}

	

}

//Change 解放　
void Change_next_img_delete(imgdate** Change_img)
{
	(*((*Change_img)->start)) = (*((*Change_img)->start))->next;
	free((*((*Change_img)->start))->back);
	(*((*Change_img)->start))->back = NULL;

	(*Change_img)->situation = (*Change_img)->situation - 1;
}

//加工を前へ
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
	if (flg) printf("ありません");
}

//加工を次へ
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
	if(flg) printf("ありません");

}

//指定枚数　画像移動
void specify_move_img(imgdate** pimg, int i)
{
	if (i > 0)
	{
		//指定枚数　次の画像
		for (int j = 0; j < i; j++)
			next_img(pimg);
	}
	else if (i < 0)
	{
		//指定枚数　前の画像
		i = i * -1;
		for (int j = 0; j < i; j++)
			back_img(pimg);
	}
}



//サイズ変更
void size_Change(imgdate** pimg)
{
	char command[10];
	int CoFlg = -1;

	//操作説明
	while (true)
	{


		printf("\n\n\n\n");
		printf("コマンド\n");
		printf("| サイズの変更 | Yes/y | No/n |\n");
		scanf_s("%s[^\0]", command, 10);
		//入力余り消去
		gomi();
		//小文字化
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
				printf("| サイズの変更 |\n");
				printf("| 完了/s | 比率_縦/v | 比率_横/b | 指定/s  | 画像前へ/ib | 画像次へ/in | 00個移動へ/m | 編集前へ/eb | 編集次へ/en | 画像移動/im | リセット/r |\n");
				printf("|  save  |  vertical |   beside  | specify |  img_back   |   imt_next  |     move     |  edit_back  |  edit_next  | imshow_move |  reset     |\n");

				scanf_s("%s[^\0]", command, 10);
				//入力余り消去
				gomi();
				//小文字化
				lowerstring(command, command);
				CoFlg = -1;//初期化
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
			printf("入力エラー");
		}
	}
}

//サイズ変更処理
void size_Change_process(imgdate** pimg, int CoFlg)
{
	int i;
	cv::Mat* aimg = new cv::Mat;//画像の型作成
	float size[2];

	switch (CoFlg)
	{
	case(0):
		printf("| 比率_縦  | 縦の長さを入力\n");
		scanf_s("%f", &size[0]);
		//入力余り消去
		gomi();

		Change_next_img(pimg);
		*aimg = (*(*pimg)->img);
		resize(*aimg, *aimg, cv::Size(), size[0] / aimg->rows, size[0] / aimg->rows);
		*((*(*pimg)->Change_img)->img) = *aimg;
		cv::imshow("edit_View", *((*(*pimg)->Change_img)->img));
		break;

	case(1):
		printf("| 比率_横  | 横の長さを入力\n");
		scanf_s("%f", &size[0]);
		//入力余り消去
		gomi();

		Change_next_img(pimg);
		*aimg = (*(*pimg)->img);
		resize(*aimg, *aimg, cv::Size(), size[0] / aimg->cols, size[0] / aimg->cols);
		*((*(*pimg)->Change_img)->img) = *aimg;
		cv::imshow("edit_View", *((*(*pimg)->Change_img)->img));
		break;

	case(2):
		printf("| 指定  | サイズを入力\n");
		printf("| 縦のサイズ |\n");
		scanf_s("%f", &size[0]);
		//入力余り消去
		gomi();
		printf("| 横のサイズ |\n");
		scanf_s("%f", &size[1]);
		//入力余り消去
		gomi();

		Change_next_img(pimg);
		*aimg = (*(*pimg)->img);
		resize(*aimg, *aimg, cv::Size(), size[1] / aimg->cols, size[0] / aimg->rows);
		*((*(*pimg)->Change_img)->img) = *aimg;
		cv::imshow("edit_View", *((*(*pimg)->Change_img)->img));
		break;

	case(3)://前の画像
		back_img(pimg);
		break;

	case(4)://次の画像
		next_img(pimg);
		break;

	case(5)://画像選択
		printf("何枚移動しますか？ マイナスも可能");
		scanf_s("%d", &i);
		gomi();//入力余り消去
		specify_move_img(pimg, i);
		break;

	case(6)://加工を１つ戻す画像

		processing_back(pimg);
		next_img(pimg);
		break;

	case(7)://加工を１つ次へ画像　（１つ戻した場合）

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
		printf("コマンドエラー");
		break;
	}
}

//サイズ変更(一括)
void size_Change_multiple(imgdate** pimg)
{
	char command[10];
	int CoFlg = -1;

	while (true)
	{
		//操作説明
		printf("\n\n\n\n");
		printf("コマンド\n");
		img_display(pimg);
		printf("| サイズの変更 | Yes/y | No/n |\n");
		scanf_s("%s[^\0]", command, 10);
		//入力余り消去
		gomi();
		//小文字化
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
				printf("| サイズの変更 |\n");
				printf("| 完了/s | 比率_縦/v | 比率_横/b | 指定/sp | 編集前へ/eb | 編集次へ/en | 画像移動/im | リセット/r |\n");
				printf("|  save  |  vertical |   beside  | specify |  edit_back  |  edit_next  | imshow_move |  reset     | \n");
				scanf_s("%s[^\0]", command, 10);
				//入力余り消去
				gomi();
				//小文字化
				lowerstring(command, command);
				CoFlg = -1;//初期化
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
					printf("入力エラー");
				}
			}
		}
		if (CoFlg == -1)
		{
			break;
		}
		else
		{
			printf("入力エラー");
		}
	}
}


//サイズ変更処理(一括)
void size_Change_process_multiple(imgdate** pimg, int CoFlg)
{
	cv::Mat* aimg = new cv::Mat;//画像の型作成
	float size[2];

	switch (CoFlg)
	{

	case(0):
		printf("| 比率_縦  | 縦の長さを入力\n");
		scanf_s("%f", &size[0]);
		//入力余り消去
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
		printf("| 比率_横  | 横の長さを入力\n");
		scanf_s("%f", &size[0]);
		//入力余り消去
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
		printf("| 指定  | サイズを入力\n");
		printf("| 縦のサイズ |\n");
		scanf_s("%f", &size[0]);
		//入力余り消去
		gomi();
		printf("| 横のサイズ |\n");
		scanf_s("%f", &size[1]);
		//入力余り消去
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

	case(3)://加工を１つ戻す画像

		for (int i = 0; i < *((*pimg)->number); i++)
		{
			processing_back(pimg);
			next_img(pimg);
		}
		(*pimg) = *((*pimg)->start);
		break;

	case(4)://加工を１つ次へ画像　（１つ戻した場合）

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
		printf("コマンドエラー");
		break;
	}
}