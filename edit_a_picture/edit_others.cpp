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
//call
void Change_next_img(imgdate** Change_img);
void  next_img(imgdate** pimg);
cv::Scalar mosaic_colour(int i);
//Other codes
void gomi();

//内
cv::Scalar colour_select();			//色選択
cv::Scalar mosaic_colour(int i);	//モザイク色取得

//色選択
cv::Scalar colour_select()
{
	char command[20];
	cv::Scalar colour;

	while (true)
	{


		printf("色 | red/r | green/g | blue/bu | black/ba | white/w\n");
		scanf_s("%s", command, 20);
		gomi();

		if (strcmp(command, "red") == 0)	return cv::Scalar(0, 0, 255);
		if (strcmp(command, "r") == 0)	return cv::Scalar(0, 0, 255);
		if (strcmp(command, "green") == 0) return cv::Scalar(0, 255, 0);
		if (strcmp(command, "g") == 0) return cv::Scalar(0, 255, 0);
		if (strcmp(command, "blue") == 0)  return cv::Scalar(255, 0, 0);
		if (strcmp(command, "bu") == 0)  return cv::Scalar(255, 0, 0);
		if (strcmp(command, "black") == 0)  return cv::Scalar(0, 0, 0);
		if (strcmp(command, "ba") == 0)  return cv::Scalar(0, 0, 0);
		if (strcmp(command, "white") == 0)  return cv::Scalar(255, 255, 255);
		if (strcmp(command, "w") == 0)  return cv::Scalar(255, 255, 255);
		printf("入力エラー");
	}
}

//モザイク色取得
cv::Scalar mosaic_colour(int i)
{
	cv::Vec3d  colour = cv::Vec3b(0, 0, 0);
	srand(i); // 現在時刻の情報で初期化
	colour[0] = (rand() % 200);
	colour[1] = colour[0];
	colour[2] = colour[0];

	return colour;
}