#include "stdio.h"
#define KEYMAXLEN 50
main()
{
FILE *fp;	//明文文件句柄
FILE *fp2;  //存放预处理后的文件句柄
FILE *fp3;  //密文文件句柄


char ch,ch2;
char key[KEYMAXLEN];	//store key
int keylen;		//key size 	
int keycode[KEYMAXLEN];	//encoding chars in key
int j,readpointer;
int flag=1;
printf("This is an encryption algorithm called 'Vigenere cipher.'\n");
printf("This program is written by 'xifang@aliyun.com'.\n\n");
printf("The encryption key, plain text and cipher text are in the charset of '[a...z]'.\n");
printf("* Input: encryption key,and plain text file 'plain.txt'.\n");
printf("* Output: cipher text file 'cipher.txt'.\n\n");

if((fp=fopen("plain.txt","r"))==NULL)			//明文文件plain.txt
              {
                  printf("Cannot open file!\n");
                  exit();
              }
else 
{
	printf("========The plain text is showed below================\n");
	while((ch=fgetc(fp))!=EOF) putchar(ch);
	putchar('\n');
	printf("========The end of plain text=========================\n\n");
}
fclose(fp);

//输入合法的秘钥-----------------------
	while(flag)
	{
		printf("Please input key:");
		gets(key);
		keylen=strlen(key); 
		if(keylen>KEYMAXLEN) //check the size of key whether exceed limitation or not.
		{
			printf("The keysize should not be more than %d, please input again!\n",KEYMAXLEN);
			continue;
		}
		for(j=0;j<keylen;j++){				//encoding chars in key
			if(key[j]>=97&&key[j]<=122)		//input [a...z] chars as encryption key!
				keycode[j]=key[j]-97;
			else{
				flag=0;
				break;
			}
		}
		if(!flag){
			printf("Please input char in set [a...z]\n");
			flag=1;
		}
		else 
			flag=0;
	}
//--------------the end of input key	

	if((fp=fopen("plain.txt","r"))==NULL)			//明文文件plain.txt
              {
                  printf("Cannot open file!\n");
                  exit();
              }
	if((fp2=fopen("plain2.txt","w"))==NULL){		//预处理后存放的中间文件plain2.txt
		printf("can't create file!\n");
		exit();
	}

	if((fp3=fopen("cipher.txt","w"))==NULL){		//存放密文文件cipher.txt
		printf("can't create file!\n");
		exit();
	}
	
    while((ch=fgetc(fp))!=EOF){    //用fgetc()函数，从文件句柄fp中读字符到变量ch中，并判断是否到文件结束
		if(ch>=97&&ch<=122)
			fputc(ch,fp2);		//用fputc()函数，写字符ch到文件句柄fp2中
		else if(ch>=65&&ch<=90)
			fputc(ch+32,fp2);   //转换成大写后，写字符ch到文件句柄fp2中
		continue;
	}
	fclose(fp2);
	fclose(fp);
	//预处理结束

	if((fp2=fopen("plain2.txt","r"))==NULL){		//从预处理后存放的中间文件plain2.txt中读字符进行维吉尼亚加密
		printf("can't open file!\n");
		exit();
	}

printf("\n=========Encryption is completed! the cipher text file is showed below========\n");
	readpointer=0;  //指向秘钥中的字符的指针
	ch=fgetc(fp2);  //从文件plain2.txt读字符到ch中
	while(ch!=EOF){
		if(readpointer<keylen){
			ch2=(ch-97+keycode[readpointer]) % 26;   //维吉尼亚加密运算的结果，在0...25之间的编码
			fputc((char)ch2+97,fp3);	//加密的结果再转换成字符, +97，并强制转换成字符写到cipher.txt文件中
			printf("%c", ch2+97);
			readpointer++;       //秘钥字符指针后移
			ch=fgetc(fp2);		//继续读文件，文件指针后移
		}
		else
			readpointer=0;    //指向秘钥中的字符的指针，回到开头
	}
	fclose(fp2);
	fclose(fp3);
	putchar('\n');
	printf("==========================The end of cipher text=============================\n\n");
}
