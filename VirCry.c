//代码：likuo
#include<stdio.h>				//头文件
#include<string.h>
#include<stdlib.h>
#include<math.h>

/*
转换成大写
*/
void changeUp(char* plainText)
{
	int i;
	for (i = 0; i < strlen(plainText); i++)
	{
		if (plainText[i] >= 'a'&&plainText[i] <= 'z')
		{
			plainText[i] -= 32;				//转换大写
		}
	}
}

/*
传入明文和密钥，进行加密
*/
void encryption(char *plainText, char *pkey)
{
	int i;
	int ptLen;				//明文长度
	int kLen;				//密钥长度
	char pt;				//单个明文
	char cryptoText[500];	//密文数组
	char aff;
	FILE *fp;				//文件指针
	ptLen = strlen(plainText);
	kLen = strlen(pkey);
	printf("要加密的明文为：(密钥是：%s)\n\n", pkey);
	for (i = 0; i < ptLen; i++)
	{
		pt = plainText[i] +(pkey[i%kLen]-65)-65;
		if (pt > 25)
		{
			pt -= 26;
		}
		pt += 65;
		printf("%c", pt);
		cryptoText[i] = pt;
	}
	cryptoText[ptLen] = '\0';				//字符结束符
	printf("是否导出密文？（Y|N）");
	scanf("%c", &aff);
	if (aff == 'Y' || aff == 'y')
	{
		getchar();
		fp = fopen("F:\\Crypto\\message.txt", "w+");
		fprintf(fp, "%s\n", cryptoText);				//密文写入文件
		printf("导出成功！文本名为 message.txt\n");
		fclose(fp);
	}
	else
	{
		exit(0);
	}
}

/*
主函数
*/
void main()
{
	char  plainText[500];				//明文数组
	char  pkey[50];						//密钥
	int choose;
	FILE *fp0;
	printf("1.选择输入要加密的文本\n2.选择从文件中导入\n请选择：（1或2）");
	scanf("%d", &choose);
	while (choose != 1 && choose != 2)
	{
		printf("输入错误！请重新正确输入：\n");
		scanf("%d", &choose);
	}
	getchar();
	if (choose == 1)
	{
		gets(plainText);
	}
	else if (choose == 2)
	{
		printf("这个文件名字必须是text.txt,请确认！\n");
		getch();
		fp0 = fopen("F:\\Crypto\\text.txt", "r+");
		if (fp0 == 0)
		{
			printf("导入错误！\n");
			getch();
			exit(0);
		}
		fscanf(fp0, "%s", plainText);
		fclose(fp0);
	}
	changeUp(plainText);
	printf("要加密的密文是：\n%s\n请输入密钥：", plainText);
	scanf("%s", pkey);
	getchar();
	changeUp(pkey);
	encryption(plainText, pkey);
	getch();
}
