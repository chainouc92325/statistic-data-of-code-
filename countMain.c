#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "count.h"
#define TIME_SIZE 10  //时间数组的大小

int main()
{
	char date[TIME_SIZE];   //时间缓存数组
	char * filename = "data.dat";  //文件名
	int res = 0;  //行数

	//设置控制台格式
	system("mode con cols=50 lines=30  & title 代码统计工具 ");
	//获取日期, 格式如：1201
	getDate(date);
	//扫描目录，存入filename文件
	getFile(date, filename);
	//读取.dat文件，获得行数res
	getNum(filename, &res);

	//休眠
	Sleep(500);
	//删除缓存文件
	deleteFile();
	//显示结果
	print(res);
	return EXIT_SUCCESS;
}
