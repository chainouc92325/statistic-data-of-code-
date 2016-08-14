#define _CRT_SECURE_NO_WARNINGS
#include  <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#define BUF_MAX 512

void getDate(char * date)
{
	//获取系统时间
	int month = 0;
	int day = 0;
	time_t ts;
	struct tm * ptime;

	time(&ts);
	ptime = localtime(&ts); //函数返回给定的统一世界时间
	month = ptime->tm_mon + 1;
	day = ptime->tm_mday;
	sprintf(date, "%02d%02d", month, day);
}

void getFile(char * date, char * filename)
{
	char cmd[100];
	//绝对路经不好用
	sprintf(cmd, "dir /s /b %s >%s", date, filename);  //指定日期
	//printf(cmd);
	system(cmd);
}

//判定源文件中的代码是不是有效代码
int isRealLine(char * buf)
{
	char * ch = buf;
	char * temp, *pSharp;

	while (isblank(*ch))
		ch++;
	if (strlen(buf) > 5)
	{
		//忽略预处理以及注释,开头为#返回零
		if ((pSharp = strstr(buf, "using")) != NULL ||
			(pSharp = strstr(buf, "#def")) != NULL ||
			(pSharp = strstr(buf, "#in")) != NULL ||
			(temp = strstr(buf, "//")) != NULL)
			return 0;
		else
			return 1;
	}
	else //小于三个字符则判定不符合条件
		return 0;
}

void getRes(char * lineBuf, int * res)
{
	int len = 0;  //本文件有效行
	char buf[BUF_MAX];  //缓存文件行
	FILE * pf = NULL;

	pf = fopen(lineBuf, "r");
	assert(pf != NULL);
	while (fgets(buf, BUF_MAX, pf) != NULL)
		if (isRealLine(buf))   //判定是否为有效行
		{
			*res += 1;  //总行数++
			len += 1;
		}
	printf("有效行<%03d>\n", len);
	fclose(pf);
}



char * isIn(char * lineBuf, char ** toFind)
{
	int flag = 0; // 标志，值0表示没有匹配
	char * lineBuf_bck = lineBuf;  //指针备份
	char ** toFind_bck = toFind;
	char * ch;

	while (*toFind_bck != NULL)
	{
		if (strstr(lineBuf, (*toFind_bck)) != NULL)
		{
			flag = 1;  //找到关键字
			break;
		}
		toFind_bck++;
	}
	//if (i == 1 && !isblank(*(ch + 1)))
	if (flag == 0)
		return NULL;   //该行没匹配到关键字
	if ((ch = strchr(lineBuf, '\n')) != NULL)  //去除文件尾 \n
		*ch = '\0';
	while ((lineBuf = strchr(lineBuf, '\\')) != NULL) //转换文件反斜杠
	{
		*lineBuf = '/';
		ch = lineBuf;    //最后一个反斜杠位置
	}
	char cach[100] = { 0 };
	sprintf(cach, "<%s>", ch + 1);  //打印文件名至cach， 用于输出
	fprintf(stdout, "%-30s", cach);
	return lineBuf_bck;
}

void getNum(char * filename, int * res)
{
	char lineBuf[1024]; //缓存.dat文件各行
	char * toFind[] = { ".cpp", ".c", ".h", "hpp", NULL };  //关键词
	FILE * pf = NULL;

	pf = fopen(filename, "r");   //打开.dat文件
	assert(pf != NULL);
	while (fgets(lineBuf, 1024, pf) != NULL)   //扫描读取.dat文件行
	{
		if (isIn(lineBuf, toFind) != NULL)  //判定是否包含关键字, 返回字符串首地址
			getRes(lineBuf, res);           //获得文件名， 统计结果
	}
	fclose(pf);   //关闭.dat文件
}



void deleteFile(void)
{
	remove("./data.dat");
}

void  print(int  res)
{
	printf("-------------------------------------------------\n");
	printf("您今天共写了%d行有效代码。再接再厉！\n", res);
	//printf("您历史共写了%d行有效代码。再接再厉！\n", res);
	printf("-------------------------------------------------\n");
	system("pause");
}
