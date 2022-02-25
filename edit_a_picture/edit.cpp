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
	imgdate** Change_img;//変更保存用
};

//外
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

//内
void edit_main(imgdate** pimg);
void Polygon(imgdate** pimg);	//多角形
void line(imgdate** pimg);		//線
void mosaic(imgdate** pimg);	//モザイク
void Rectangle(imgdate** pimg);	//四角形
void Text(imgdate** pimg);//文字
//void _putText(cv::Mat& img, const cv::String& text, const cv::Point& org, const char* fontname, double fontScale, cv::Scalar color);
//HFONT SetMyFont(HDC hdc, LPCTSTR face, int h, int angle);


void edit_main(imgdate** pimg)
{

	Change_next_img(pimg);
	char command[20];
	int Coflg = -1;

	//操作説明
	printf("\nedit_View　の　線幅は　1個　20\n");
	printf("コマンド\n");
	printf("| キャンセル/c | 多角形/p | 線分/l | モザイク/m | 四角形/r  | 文字/t |\n");
	printf("|   cancel     | Polygon  |  line  |   mosaic   | Rectangle |  Text  |\n");
	scanf_s("%s[^\0]", command, 20);
	//入力余り消去
	gomi();
	//小文字化
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
			catch (const std::exception&)//エラー処理
			{
				printf("入力エラー");
			}
			break;

		case(2):
			try
			{
				line(pimg);
			}
			catch (const std::exception&)//エラー処理
			{
				printf("入力エラー");
			}
			break;

		case(3):
			try
			{
				mosaic(pimg);
			}
			catch (const std::exception&)//エラー処理
			{
				printf("入力エラー");
			}
			break;
			
		case(4):
			try
			{
				Rectangle(pimg);
			}
			catch (const std::exception&)//エラー処理
			{
				printf("入力エラー");
			}
			break;

			
		case(5):
			try
			{
				Text(pimg);
			}
			catch (const std::exception&)//エラー処理
			{
				printf("入力エラー");
			}
			break;

		default:
			break;
		}
	}
	catch (const std::exception&)//エラー処理
	{
		printf("入力エラー");
		
	}
}



//多角形
void Polygon(imgdate** pimg)
{
	cv::Point pt[10]; //任意の点を配列に入れる
	const cv::Point* ppt[1] = { pt };
	int The_thickness;
	cv::Scalar colour;
	int flg = -1;
	int i = 0;

	//入力
	for (i = 0; i < 10; i++)
	{
		int vertical = 0;
		int beside = 0;
		printf("edit_Viewでの横の座標 | ３点以上　10点以下　-1で完了　 \n");
		scanf_s("%d", &beside);
		if (beside == -1) break;
		printf("edit_Viewでの高さの座標\n");
		scanf_s("%d", &vertical);
		vertical = vertical * (*(*pimg)->Change_img)->img->rows / 500.0;
		beside = beside * (*(*pimg)->Change_img)->img->rows / 500.0;
		pt[i] = cv::Point( beside, vertical);
		gomi();
	}

	//塗りつぶす
	printf("線の太さを入力 | 塗りつぶす時は-1 \n");
	scanf_s("%d", &The_thickness);
	flg = 0;
	if (The_thickness== -1)	flg = 1;
	gomi();
	int npt[] = { i, i };

	//色
	colour = colour_select();

	//描画
	if (i > 2 && (flg == 0 || flg == 1))
	{
		// 画像，折れ線頂点の配列の配列，頂点数の配列，折れ線数，線が閉じているか？，色，線太さ，種類
		if (flg == 0)
			cv::polylines(*((*(*pimg)->Change_img)->img), ppt, npt, 1, true, colour, The_thickness);

		//描画　引数は (画像, 点の配列, 点の数, 色)
		if (flg == 1)
			cv::fillConvexPoly(*((*(*pimg)->Change_img)->img), pt, i, colour);//BGR
	}
	else
	{
		printf("頂点が足りません");
	}
}

//線
void line(imgdate** pimg)
{
	cv::Point pt[2]; //任意の2点を配列に入れる
	int i = 0;
	cv::Scalar colour;
	int The_thickness;

	//入力
	for (i = 0; i < 2; i++)
	{
		int vertical = 0;
		int beside = 0;
		printf("edit_Viewでの横の座標  %d個目 \n", i);
		scanf_s("%d", &beside);
		printf("edit_Viewでの高さの座標\n");
		scanf_s("%d", &vertical);
		vertical = vertical * (*(*pimg)->Change_img)->img->rows / 500.0;
		beside = beside * (*(*pimg)->Change_img)->img->rows / 500.0;
		pt[i] = cv::Point(beside, vertical);
		gomi();
	}

	//色
	colour = colour_select();


	//太さ
	printf("線の太さを入力  \n");
	scanf_s("%d", &The_thickness);
	gomi();
	if (The_thickness < 0)
	{
		printf("入力エラー");
	}

	//描画
	cv::line(*((*(*pimg)->Change_img)->img), pt[0], pt[1], colour, The_thickness);//BGR
}


//モザイク
void mosaic(imgdate** pimg)
{
	srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化
	cv::Scalar colour;
	int x_y[2][2];
	cv::Point pt[4]; //任意の2点を配列に入れる
	int i;
	int j;

	//入力
	for (i = 0; i < 2; i++)
	{
		printf("%d個目 四角形の対角線\n", i);
		printf("edit_Viewでの横の座標　 \n");
		scanf_s("%d", &x_y[i][0]);
		printf("edit_Viewでの高さの座標\n");
		scanf_s("%d", &x_y[i][1]);
		//入力余り消去
		gomi();
		
	}
	//頂点きれいに
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

	//座標を元のサイズにする
	x_y[0][0] = x_y[0][0] * (*(*pimg)->Change_img)->img->rows / 500.0;
	x_y[0][1] = x_y[0][1] * (*(*pimg)->Change_img)->img->rows / 500.0;
	x_y[1][0] = x_y[1][0] * (*(*pimg)->Change_img)->img->rows / 500.0;
	x_y[1][1] = x_y[1][1] * (*(*pimg)->Change_img)->img->rows / 500.0;

	//範囲 1以上
	int range_box = 1;

	//選択範囲が狭い
	if (x_y[0][1] + range_box > x_y[1][1] || x_y[0][0] + range_box > x_y[1][0])
	{
		printf("狭すぎます");
		return;
	}

	//描画
	for (j = x_y[0][1]; j < x_y[1][1]; j=j + range_box)
	{
		//範囲オーバー
		if (j + range_box > x_y[1][1])	j = x_y[1][1] - range_box;
		for (i = x_y[0][0]; i < x_y[1][0]; i=i + range_box)
		{
			//範囲オーバー
			if (i + range_box > x_y[1][0])  i = x_y[1][0] - range_box;

			//横　縦
			pt[0] = cv::Point(i, j);
			pt[1] = cv::Point(i + range_box, j);
			pt[2] = cv::Point(i + range_box, j + range_box);
			pt[3] = cv::Point(i, j + range_box);

			//色
			colour = mosaic_colour(rand());

			//描画　引数は (画像, 点の配列, 点の数, 色)
			cv::fillConvexPoly(*((*(*pimg)->Change_img)->img), pt, 4, colour);//BGR
		}
	}
	
}


//四角形
void Rectangle(imgdate** pimg)
{
	srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化
	cv::Scalar colour;
	int x_y[2][2];
	int x_y2[2][2];
	cv::Point pt[4]; //任意の2点を配列に入れる
	const cv::Point* ppt[1] = { pt };
	int The_thickness;
	int flg;
	int i;
	

	//入力
	for (i = 0; i < 2; i++)
	{
		printf("%d個目 四角形の対角線\n", i);
		printf("edit_Viewでの横の座標　 \n");
		scanf_s("%d", &x_y[i][0]);
		printf("edit_Viewでの高さの座標\n");
		scanf_s("%d", &x_y[i][1]);
		gomi();
	}

	//範囲選択　きれいにする
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


	//線の位置を設定　編集用のビューの位置から　オリジナルサイズへ
	x_y2[0][0] = x_y[0][0] * (*(*pimg)->Change_img)->img->rows / 500.0;
	x_y2[0][1] = x_y[0][1] * (*(*pimg)->Change_img)->img->rows / 500.0;
	x_y2[1][0] = x_y[1][0] * (*(*pimg)->Change_img)->img->rows / 500.0;
	x_y2[1][1] = x_y[1][1] * (*(*pimg)->Change_img)->img->rows / 500.0;

	//範囲 1以上
	int range_box = 1;

	if (x_y2[0][1] + range_box > x_y2[1][1] || x_y2[0][0] + range_box > x_y2[1][0])
	{
		printf("狭すぎます");
		return;
	}

	//横　縦
	pt[0] = cv::Point(x_y2[0][0], x_y2[0][1]);
	pt[1] = cv::Point(x_y2[1][0], x_y2[0][1]);
	pt[2] = cv::Point(x_y2[1][0], x_y2[1][1]);
	pt[3] = cv::Point(x_y2[0][0], x_y2[1][1]);


	//色
	colour = colour_select();

	//描画　引数は (画像, 点の配列, 点の数, 色)
	//cv::fillConvexPoly(*((*(*pimg)->Change_img)->img), pt, 4, colour);//BGR

	//塗りつぶす
	printf("線の太さを入力 | 塗りつぶす時は-1 \n");
	scanf_s("%d", &The_thickness);
	flg = 0;
	if (The_thickness == -1)	flg = 1;
	gomi();
	int npt[] = { i, i };

	//色
	colour = colour_select();

	//描画
	if (flg == 0 || flg == 1)
	{
		// 画像，折れ線頂点の配列の配列，頂点数の配列，折れ線数，線が閉じているか？，色，線太さ，種類
		if (flg == 0)
			cv::polylines(*((*(*pimg)->Change_img)->img), ppt, npt, 1, true, colour, The_thickness);

		//描画　引数は (画像, 点の配列, 点の数, 色)
		if (flg == 1)
			cv::fillConvexPoly(*((*(*pimg)->Change_img)->img), pt, i, colour);//BGR
	}
	

}

//文字
void Text(imgdate** pimg)
{
	srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化
	cv::Scalar colour;
	int x_y[2];
	int x_y2[2];
	cv::Point pt; //任意の2点を配列に入れる
	char text[31];
	int The_thickness;

	//入力
	printf("文字の左下座標\n");
	printf("edit_Viewでの横の座標　 \n");
	scanf_s("%d", &x_y[0]);
	printf("edit_Viewでの高さの座標\n");
	scanf_s("%d", &x_y[1]);
	gomi();

	//線の位置を設定　編集用のビューの位置から　オリジナルサイズへ
	x_y2[0] = 2 * x_y[0] * (*(*pimg)->Change_img)->img->rows / 500.0;
	x_y2[1] = 2 * x_y[1] * (*(*pimg)->Change_img)->img->rows / 500.0;

	//横　縦
	pt = cv::Point(x_y2[0], x_y2[1]);

	//色
	colour = colour_select();

	//文字サイズ
	printf("文字の大きさを入力  \n");
	scanf_s("%d", &The_thickness);
	gomi();
	if (The_thickness < 0)
	{
		printf("入力エラー");
	}

	//文字
	printf("書き込む文字 最大30文字\n");
	scanf_s("%s", text,31);
	gomi();

	float colsbox;
	float rowsbox;
	cv::Mat* aimg = new cv::Mat;//画像の型作成
	*aimg = *((*(*pimg)->Change_img)->img);

	colsbox = (aimg->cols);
	rowsbox = (aimg->rows);

	//resize は　バグ対策
	resize(*((*(*pimg)->Change_img)->img), *((*(*pimg)->Change_img)->img), cv::Size(), colsbox * 2 / aimg->cols, colsbox * 2 / aimg->rows);
	
	//描画
	a_main(*((*(*pimg)->Change_img)->img),text,pt,colour, The_thickness);
	
	//resize は　バグ対策
	*aimg = *((*(*pimg)->Change_img)->img);
	resize(*((*(*pimg)->Change_img)->img), *((*(*pimg)->Change_img)->img), cv::Size(), colsbox / aimg->cols, colsbox / aimg->rows);
}

