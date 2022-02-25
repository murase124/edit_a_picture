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
	imgdate** Change_img = (imgdate * *)malloc(sizeof(imgdate*));//変更保存用
};

//外
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
		//画像　読み込み・出力
		const char pasr[6] = "read/";//読み込みファイルパス
		const char pask[6] = "keep/";//保存ファイルパス
		char pas[100];//画像パス
		WIN32_FIND_DATA ffd;//画像情報

		//構造体用
		cv::Mat* aimg = new cv::Mat;//画像の型作成
		HANDLE hFind = INVALID_HANDLE_VALUE;//画像ハンドル
		imgdate** pimg = (imgdate**)malloc(sizeof(imgdate*));//画像構造体
		*pimg = NULL;

		//その他
		int move_mun = 0;//画像を移動する枚数
		char command[20];//コマンド保管
		int CoFlg = -1;//コマンドフラック
		bool end_flg = false;//終了するか
		bool Image_loading_flg = false;//画像読み込めたか？

		//画像読み込み処理

		//ピリオド処理
		hFind = FindFirstFile("read/*", &ffd);
		FindNextFile(hFind, &ffd);
		//画像読み込み
		printf("読み込み画像\n");

		//読み込み
		while (FALSE != FindNextFile(hFind, &ffd))
		{
			Image_loading_flg = true;//画像を読み込めたか
			imgdate_Structure(pimg);//画像構造体作成
			strcpy_s(((*pimg)->pas), ffd.cFileName);//画像名保管
			printf("%s\n", ffd.cFileName);//画像名表示
			strcpy_s(pas, pasr);//パス、初期化
			strcat_s(pas, ffd.cFileName);//パス、セット

			cv::Mat* aimg = new cv::Mat;//画像の型作成
			try//画像読み込み
			{
				*aimg = cv::Mat(cv::imread(pas, -1));
				((*pimg)->img) = aimg;
			}
			catch (const std::exception&)//エラー処理
			{
				printf("画像以外がreadファイルに含まれている可能性があります。");
				return -1;
			}
			//加工保存先作成
			Change_next_img(pimg);
		}
		printf("\n");




		//画像編集
		if (Image_loading_flg)
		{
			//編集方法選択
			while (CoFlg == -1)
			{
				printf("| 1枚ごと編集/o | 一括編集/b | 閉じる/e |\n");
				printf("|   one_sheet   |    bulk    |   exit   | \n");

				scanf_s("%s[^\0]", command, 20);
				//入力余り消去
				gomi();
				//小文字化
				lowerstring(command, command);

				if (strcmp(command, "one_sheet") == 0)	CoFlg = 0;
				if (strcmp(command, "o") == 0)	CoFlg = 0;
				if (strcmp(command, "bulk") == 0)	CoFlg = 1;
				if (strcmp(command, "b") == 0)	CoFlg = 1;
				if (strcmp(command, "exit") == 0)	CoFlg = 2;
				if (strcmp(command, "e") == 0)	CoFlg = 2;
			}

			if (0 == CoFlg)//一枚ずつ処理
			{
				//読み込みモード
				while (true)
				{
					//画像表示
					img_display(pimg);

					//操作説明
					printf("\n\n\n\n");
					printf("画像の読み込みを指定 コマンド\n");
					printf("| 完了/s | キャンセル/ca | フルデータ/a | カラー/co | モノクロ/mh |\n");
					printf("| save   |   cancel      |     all      |  color    |  monochrome |\n");
					printf("| 画像前へ/ib | 画像次へ/in | 00個移動へ/mo | 画像移動/im |\n");
					printf("|  img_back   |  img_next   |    move       | imshow_move |\n");

					scanf_s("%s[^\0]", command, 20);
					//入力余り消去
					gomi();
					//小文字化
					lowerstring(command, command);

					//変換　switchで使用のため
					CoFlg = -1;//初期化
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

					//画像読み込み種類
					switch (CoFlg)
					{
					case(0)://s 完了
						end_flg = true;
						break;

					case(1)://esc キャンセル
						printf("キャンセルしました。");
						return 0;
						break;

					case(2)://アルファチャンネル
						COLOR((*pimg)->Change_img, -1);
						break;

					case(3)://カラ－
						COLOR((*pimg)->Change_img, 1);
						break;

					case(4)://グレースケール
						COLOR((*pimg)->Change_img, 0);
						break;

					case(5)://前の画像
						back_img(pimg);
						break;

					case(6)://次の画像
						next_img(pimg);
						break;

					case(7)://画像選択
						try
						{
							printf("何枚移動しますか？ マイナスも可能");
							scanf_s("%d", &move_mun);
							//入力余り消去
							gomi();

							specify_move_img(pimg, move_mun);
						}
						catch (const std::exception&)//エラー処理
						{
							printf("入力エラー");
						}
						break;
					case(8):
						imshow_move(pimg);
						break;

					default:
						printf("コマンドエラー");
						break;
					}
					//ループ抜ける
					if (end_flg) break;
				}

				//リセット
				end_flg = false;
				//変更をセット
				for (int i = 0; i < *((*pimg)->number); i++)
				{
					(*pimg)->img = (*((*pimg)->Change_img))->img;
					next_img(pimg);
				}

				//サイズ設定
				size_Change(pimg);

				//変更をセット
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


				//編集
				while (true)
				{
					//画像表示
					img_display(pimg);

					//操作説明
					printf("\n\n\n\n");
					printf("コマンド\n");
					printf("| 終了/e | 保存/s | リセット/r | 画像前へ/ib | 画像次へ/in | 00個移動へ/m |\n");
					printf("| eixt   | save   |  reset     |  img_back   |   imt_next  |     move     |\n");
					printf("| 編集前へ/eb | 編集次へ/en |  描画/d | 画像移動/im |\n");
					printf("|   edit_back |   edit_next | drawing | imshow_move |\n");
					scanf_s("%s[^\0]", command, 20);
					//入力余り消去
					gomi();
					//小文字化
					lowerstring(command, command);

					/*** コマンドをフラグに変換　スイッチ文用 ***/
					//変換　switchで使用のため
					CoFlg = -1;//初期化
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

					//編集
					switch (CoFlg)
					{
					case(0)://esc 終了
						end_flg = true;
						break;
					case(1)://s 保存
						end_flg = true;
						break;

					case(2)://リセット
						(*(*pimg)->Change_img)->img = (*pimg)->img;
						break;

					case(3)://前の画像
						back_img(pimg);
						break;

					case(4)://次の画像
						next_img(pimg);
						break;

					case(5)://画像選択
						try
						{
							printf("何枚移動しますか？ マイナスも可能");
							scanf_s("%d", &move_mun);

							//入力余り消去
							gomi();

							specify_move_img(pimg, move_mun);
						}
						catch (const std::exception&)//エラー処理
						{
							printf("入力エラー");
						}

						break;

					case(6)://加工を１つ戻す画像

						processing_back(pimg);
						//next_img(pimg);
						break;

					case(7)://加工を１つ次へ画像　（１つ戻した場合）

						processing_next(pimg);
						//next_img(pimg);
						break;

					case (8)://描画(edit)
						edit_main(pimg);
						break;

					case(9):
						imshow_move(pimg);
						break;

					default:
						printf("コマンドエラー");
						break;
					}

					//ループ抜ける
					if (end_flg) break;
				}

				//保存判定
				if (1 == CoFlg)
				{
					//保存する
					img_Save(pimg);
					printf("\n保存完了\n");
					return 1;
				}
				else
				{
					printf("\n保存されませんでした\n");
					return 0;
				}
			}


			/////////////////////////////////////////////////////////////////////////////

			else if (1 == CoFlg)//一括処理
			{

				(*pimg) = *((*pimg)->start);

				//読み込みモード
				while (true)
				{
					//画像表示
					img_display(pimg);

					//コマンド
					printf("\n\n\n\n");
					printf("画像の読み込みを指定 コマンド\n");
					printf("| 完了/s | キャンセル/ca | フルデータ/a | カラー/co | モノクロ/m | 画像移動/im |\n");
					printf("| save   |   cancel      |     all      |   color   | monochrome | imshow_move |\n");
					scanf_s("%s[^\0]", command, 20);
					//入力余り消去
					gomi();
					//小文字化
					lowerstring(command, command);

					//変換　switchで使用のため
					CoFlg = -1;//初期化
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

					//画像読み込み種類
					switch (CoFlg)
					{
					case(0)://s 完了
						end_flg = true;
						break;

					case(1)://esc キャンセル
						printf("キャンセルしました。");
						return 0;
						break;

					case(2)://アルファチャンネル
						for (int i = 0; i < *((*pimg)->number); i++)
						{
							COLOR((*pimg)->Change_img, -1);
							next_img(pimg);
						}
						(*pimg) = *((*pimg)->start);
						break;

					case(3)://カラ－
						for (int i = 0; i < *((*pimg)->number); i++)
						{
							COLOR((*pimg)->Change_img, 1);
							next_img(pimg);
						}
						(*pimg) = *((*pimg)->start);
						break;

					case(4)://グレースケール
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
						printf("コマンドエラー");
						break;

					}
					//ループ抜ける
					if (end_flg) break;
				}
				//リセット
				end_flg = false;

				//変更をセット
				for (int i = 0; i < *((*pimg)->number); i++)
				{
					(*pimg)->img = (*((*pimg)->Change_img))->img;
					next_img(pimg);
				}

				//サイズ設定
				size_Change_multiple(pimg);

				//変更をセット
				for (int i = 0; i < *((*pimg)->number); i++)
				{
					(*pimg)->img = (*((*pimg)->Change_img))->img;
					next_img(pimg);
				}

				//編集
				while (true)
				{
					//画像表示
					img_display(pimg);

					//コマンド
					printf("\n\n\n\n");
					printf("コマンド\n");
					printf("| 終了/e | 保存/s | リセット/r | 編集前へ/eb | 編集次へ/en |  描画/d | 画像移動/im |\n");
					printf("| eixt   | save   |  reset     | edit_back   | edit_next   | drawing | imshow_move |\n");
					scanf_s("%s[^\0]", command, 20);
					//入力余り消去
					gomi();
					//小文字化
					lowerstring(command, command);

					/*** コマンドをフラグに変換　スイッチ文用 ***/
					//変換　switchで使用のため
					CoFlg = -1;//初期化
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
					case(0)://esc 終了
						end_flg = true;
						break;
					case(1)://s 保存
						end_flg = true;
						break;

					case(2)://リセット
						for (int i = 0; i < *((*pimg)->number); i++)
						{
							(*(*pimg)->Change_img)->img = (*pimg)->img;
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

					case (5)://描画(edit)
						edit_main_multiple(pimg);
						break;

					case(6):
						imshow_move(pimg);
						break;

					default:
						printf("コマンドエラー");
						break;
					}
					//ループ抜ける
					if (end_flg) break;

					//コマンド表示

				}
				//保存判定
				if (1 == CoFlg)
				{
					//保存する
					img_Save(pimg);
					printf("\n保存完了\n");
					return 1;
				}
			}
		}
		else
		{
			printf("\n画像なし\n");
			return -1;
		}
		//画像を閉じる
		cv::destroyAllWindows();
		printf("\n保存されませんでした\n");
		return 0;
	//}
	//catch (const std::exception&)//エラー処理
	//{
	//	printf("エラー");
	//	return -10;
	//}
}