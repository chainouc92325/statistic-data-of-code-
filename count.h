#ifndef COUNT_H
#define COUNT_H


#ifdef __cplusplus
extern "C" {
#endif


	//生成dir文件
	void getFile(char * date, char * filename);
	//获取系统时间，或指定时间，存于date数组
	void getDate(char * date);
	void getNum(char * filename, int * res);
	char * isIn(char * lineBuf, char ** toFind);
	void getRes(char * path, int * res);
	int isRealLine(char * buf);
	void deleteFile(void);
	void  print(int  res);


#ifdef __cplusplus
}
#endif


#endif
