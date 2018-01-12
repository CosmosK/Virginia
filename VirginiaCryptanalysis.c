//代码:likuo
#include<stdio.h>				//头文件
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define _CRT_NONSTDC_NO_WARNINGS 
/*
把字母转换成大写
*/
void changeUp(char* cipherText)
{
	int i;
	for (i = 0; i < strlen(cipherText); i++)
	{
		if (cipherText[i] >= 'a'&&cipherText[i] <= 'z')
		{
			cipherText[i] -= 32;
		}
	}
}

/*
快速排序Quick Sort
*/
void qksort(int* zh, int zhn)
{
	int i;
	int j;
	int min;				//用来记录假最小值
	int temp;
	for (i = 0; i < zhn - 1; i++)
	{
		min = i;
		for (j = i + 1; j < zhn; j++)
		{
			if (zh[j] < zh[min])
			{
				min = j;
			}
		}
		temp = zh[i];
		zh[i] = zh[min];
		zh[min] = temp;
	}
}

/*
1、密文 2、连续字母 3、出现的个数 4、位置 5、相对位置 6、位置的因子 7、因子的个数
*/
int doulet(char cipherText[], char adChar[][2], int chaCon[], int pos[][10], int relPos[][10], int divisor[][80], int divCon[380])
{
	char p;				//p、q用来记录密文中相连续的字符
	char q;
	char x;				//连续字母的个数
	int i;				//用来循环密文，记录连续字符
	int j;				//用来查找密文中与连续字符相同的
	int k;				//用来循环相同字符个数
	int ctLen = strlen(cipherText);	//密文的长度
	int t;
	int count = 0;		//密文中存在连续字符的个数，初始为0
	int max;
	int min;
	int temp;
	int s;
	//循环密文
	for (i = 0; i < ctLen - 1; i++)
	{
		//记录两个连续的字符
		p = cipherText[i];				
		q = cipherText[i + 1];
		//设相同连续字符个数初始值为0
		x = 0;
		for (j = 0; j < ctLen - 1; j++)
		{
			//如果找到字符相同匹配，则x加一
			if (cipherText[j] == p&&cipherText[j + 1] == q)
			{
				x++;
			}
		}
		//如果x连续字符出现个数大于1，则进行保存到数组位置中
		if (x > 1)
		{
			//将出现次数大于一的连续字符记录保存
			adChar[count][0] = p;
			adChar[count][1] = q;
			chaCon[count] = x;
			//连续字符数出现的+1
			count++;				
		}
	}
	for (i = 0; i < count - 1; i++)
	{
		for (j = i + 1; j < count; j++)
		{
			//循环检查连续字符有没有重复的
			if (adChar[i][0] == adChar[j][0] && adChar[i][1] == adChar[j][1])
			{
				//如果重复，则删除当前重复
				for (k = j; k < count - 1; k++)
				{
					adChar[k][0] = adChar[k + 1][0];
					adChar[k][1] = adChar[k + 1][1];
					chaCon[k] = chaCon[k + 1];
				}
				//密文中连续的字符数出现的-1
				count--;
			}
		}
	}
	//找出出现重合最多的连续字符串
	for (i = 0; i < count - 1; i++)
	{
		//用来记录假最大值下标
		max = i + 1;				
		for (j = i + 1; j < count; j++)
		{
			if (chaCon[j] > chaCon[max])
			{
				//记录最大值下标
				max = j;
			}
		}
		//如果第一个不是最多，则把最多的放到第一个
		if (chaCon[i] < chaCon[max])
		{
			//换个数
			temp = chaCon[i];
			chaCon[i] = chaCon[max];
			chaCon[max] = temp;
			//换第一个字符
			temp = adChar[i][0];
			adChar[i][0] = adChar[max][0];
			adChar[max][0] = temp;
			//换第二个字符
			temp = adChar[i][1];
			adChar[i][1] = adChar[max][1];
			adChar[max][1] = temp;
		}
	}
	//每个连续字符在密文里的位置
	for (i = 0; i < count; i++)
	{
		t = 0;
		for (j = 0; j < ctLen; j++)
		{
			if (cipherText[j] == adChar[i][0] && cipherText[j + 1] == adChar[i][1])
			{
				pos[i][t++] = j;
			}
		}
	}
	//计算每相邻连续字符的相对距离
	for (i = 0; i < count; i++)
	{
		for (j = 0; j < chaCon[i] - 1; j++)
		{
			relPos[i][j] = pos[i][j + 1] - pos[i][j];
		}
	}
	//求每个重复字符的因子
	for (i = 0; i < count; i++)
	{
		t = 0;
		//每个连续的字符的个数
		for (j = 0; j < chaCon[i] - 1; j++)
		{
			for (k = 2; k <= (relPos[i][j] < 50 ? relPos[i][j] : 50); k++)
			{
				//计算因子
				if (relPos[i][j] % k == 0)
				{
					divisor[i][t++] = k;
				}
			}
		}
		//每一个字符因子的个数
		divCon[i] = t;
	}
	//判断因子是否相同
	//循环所有连续字符
	for (s = 0; s < count; s++)
	{
		//每个连续字符出现的个数
		for (i = 0; i < divCon[s] - 1; i++)
		{
			for (j = i + 1; j < divCon[s]; j++)
			{
				//因子数判断是否重复
				if (divisor[s][i] == divisor[s][j])
				{
					//如果重复重次开始，往前覆盖
					for (k = j; k < divCon[s] - 1; k++)
					{
						divisor[s][k] = divisor[s][k + 1];
					}
					//因子减1
					divCon[s]--;
				}
			}

		}
		//排序
		for (i = 0; i < divCon[s] - 1; i++)
		{
			min = i + 1;
			for (j = i + 1; j < divCon[s]; j++)
			{
				if (divisor[s][i] > divisor[s][min])
				{
					temp = divisor[s][i];
					divisor[s][i] = divisor[s][min];
					divisor[s][min] = temp;
				}
			}
		}
	}
		if (count > 20)
		{
			count = 20;
		}
		return count;
	
}
/*
c传入所有相对距离因子数排序后n所有因子的个数
整理出因子出现最多的
*/
int zhengl(int* a, int *b, int *c, int n)
{
	//初始因子出现个数为1，如有重复加1
	int x = 1;
	int i, j;
	int max;
	int temp;
	//循环先把每个因子copy
	for (i = 0; i < n; i++)
	{
		a[i] = c[i];
	}
	//找出排序中重复的进行统计
	for (i = 1; i < n;)
	{
		//排序中如果出现相邻相等则进行删减
		if (a[i] == a[i - 1])
		{
			//开始从出现相等的位置开始往前覆盖
			for (j = i; j < n - 1; j++)
			{
				a[j] = a[j + 1];
			}
			//出现的所有的因子数减一
			n--;
			//当前元素出现次数加1
			x++;
		}
		else
		{
			//把当前因子出现个数记录为X
			b[i - 1] = x;
			//进行下一检验
			i++;
			//x恢复初始值
			x = 1;
		}
	}
	//最后一个为n-1
	b[n - 1] = x;
	//循环统计之后去掉重复的因子
	for (i = 0; i < n - 1; i++)
	{
		//定义一个假最大值下标
		max = i + 1;
		//进行因子出现的次数进行排序
		for (j = i + 1; j < n; j++)
		{
			if (b[j] > b[max])
			{
				max = j;
			}
		}
		//找出次数最多的因子进行交换
		if (b[i] < b[max])
		{
			temp = b[i];
			b[i] = b[max];
			b[max] = temp;
			temp = a[i];
			a[i] = a[max];
			a[max] = temp;
		}
	}
	//所有因子中出现次数最多的个数（最可能的密钥长度）
	n = n > 18 ? 18 : n;
	return n;
}

//重合指数计算
//传入分的子串
double ic(char *p)
{
	int i, j, len;
	//a代表着26个字母数组
	double a[27] = { 0.0 };
	//IC重合指数
	double IC = 0.0;
	//保存子串的长度
	len = strlen(p);				
	//每个子串里的字符都有26种可能
	for (j = 1; j <= 26; j++)
	{
		for (i = 0; i < len; i++)
		{
			//相对距离从0-25，基于A:65
			//j每移动一下，计算子串里26个字母出现的频率
			if (p[i] == 65 + j - 1)
			{
				a[j]++;
			}
		}
	}
	for (i = 1; i <= 26; i++)
	{
		//计算每个字母出现的概率,利用无偏估计值IC'来近似IC
		a[i] = (a[i] * (a[i] - 1)) / (len*(len - 1));
		if (a[i] > 1e-8)
		{
			//重合指数IC
			IC += a[i];
		}
	}
	return IC;
}


//计算平均重合指数IC
double icAvg(char* m, int n)
{
	int i;
	int p[50] = { 0 };
	char ch[50][500];
	double xic[50], icSum = 0.0;
	for (i = 0; i < strlen(m); i++)
	{
		//根据密钥长度，把密文分组成子串
		ch[i%n][p[i%n]] = m[i];
		//p代表每一个子串里的位置
		p[i%n]++;
	}
	//给每个子串加结束标识符
	for (i = 0; i < n; i++)
	{
		ch[i][p[i]] = '\0';
		p[i]++;
	}
	//计算每一个子串的重合指数
	for (i = 0; i < n; i++)
	{
		xic[i] = ic(ch[i]);
	}
	//求每组重合指数IC的和
	for (i = 0; i < n; i++)
	{
		icSum += xic[i];
	}
	//返回每组平均重合指数IC
	return icSum / n;
}

//根据密钥长度和密文计算接近密钥
void circa(char* m, int key, char *keyw)
{
	//第一个分布中26个英文字母固定的概率
	double plet[27] = { 0.082,0.015,0.028,0.043,0.127,0.022,0.02,0.061,0.07,0.002,
		0.008,0.04,0.024,0.067,0.075,0.019,0.001,0.06,0.063,0.091,
		0.028,0.01,0.023,0.001,0.02,0.001 };
	int i, j, k, letmax[50];
	//pml每个字母的频率，ic拟重合指数，icmax记录最大拟重合指数
	double pml[27] = { 0.0 }, ic[27] = { 0.0 }, icmax[50];
	//每个子串的长度
	int p[50] = { 0 };
	//来保存密文的数组
	char ch[50][500];
	//来记录移位变换后的字母
	char change[500];
	//密文分组子串
	for (i = 0; i < strlen(m); i++)
	{
		ch[i%key][p[i%key]] = m[i];
		p[i%key]++;
	}
	//每个子串添加结束标识符
	for (i = 0; i < key; i++)
	{
		ch[i][p[i]] = '\0';
	}
	printf("\n");
	//循环分组，通过计算拟重合指数找出密钥
	for (i = 0; i < key; i++)
	{
		for (j = 0; j < 26; j++)
		{
			for (k = 0; k < 26; k++)
			{
				pml[k] = 0;
			}
				ic[j] = 0.0;
				//循环每个子串k，每个字母都有26种移动可能j
				for (k = 0; k < p[i]; k++)
				{
					//保存子串移动过之后对应的字母
					change[k] = ch[i][k] - j;
					if (change[k] < 65)
					{
						change[k] += 26;
					}
				}
				//移动后产生后的每个字母的频率
				for (k = 0; k < p[i]; k++)
				{
					pml[change[k] - 65]++;
				}
				//拟重合指数：每个字母在第二个分布中发生的概率*那在第一个分布中固有的频率
				for (k = 0; k < 26; k++)
				{
					ic[j] += (pml[k] / p[i])*plet[k];
				}
			
		}
		//记录每组中拟重合指数最大的下标值
		letmax[i] = 0;
		//每个初始值为第一个，一个假最大值
		icmax[i] = ic[0];
		//拟重合测试法，找出每个子串中26个字母的拟重合测试法的最大值
		for (j = 0; j < 26; j++)
		{
			//找出最大拟重合指数，总把最大的放到最前面
			if (fabs(icmax[i] - 0.065)>fabs(ic[j] - 0.065))
			{
				icmax[i] = ic[j];
				//记录下标值
				letmax[i] = j;
			}
		}
		//输出每组1、拟重合指数最大的相对移动数2、拟重合指数最大的字母3、最大拟重合指数
		printf("%d\t%c\t%f\n", letmax[i], letmax[i] + 'A', icmax[i]);
	}
	//保存密钥
	for (i = 0; i < key; i++)
	{
		keyw[i] = letmax[i] + 65;
	}
	keyw[key] = 0;
}


//已知密钥解密
void sol(char *m, char *keyw)
{
	//密文长度密钥长度
	int i, cpLen, kLen;
	char cp;
	//记录用户的选择
	char aff;
	//记录解密后的明文
	char plainText[500];
	//定义文件指针
	FILE *fp0;
	//记录密文长度
	cpLen = strlen(m);
	//记录密钥长度
	kLen = strlen(keyw);
	printf("明文如下:(密钥为： %s)\n\n", keyw);
	for (i = 0; i < cpLen; i++)
	{
		//循环解密
		cp = m[i] - (keyw[i%kLen] - 65);
		if (cp < 65)
		{
			cp += 26;
		}
		cp += 32;
		printf("%c", cp);
		//保存到明文数组中
		plainText[i] = cp;
	}
	//明文数组字符结束符
	plainText[cpLen] = '\0';
	//给出交互
	printf("\n\n\n导出文件?(Y|N)");
	scanf("%c", &aff);
	if (aff == 'Y' || aff == 'y')
	{
		getchar();
		//打开文件夹
		fp0 = fopen("F:\\Crypto\\text.txt", "w+");
		//将明文写入
		fprintf(fp0, "%s\n", plainText);
		printf("导出成功! 这个文件的名字text.txt\n");
		//关闭指针与文件的关联
		fclose(fp0);
	}
	else
	{
		//退出
		exit(0);
	}
}

void main()
{
	//密文数组
	char cirptoText[500];
	int i, n, j, num[380];
	char dl[380][2];
	int  c[380][10], d[380][10], e[380][80], f[380];
	int zh[1000], zhn = 0;
	int yz[1000], yzs[1000], gs;
	double xic[20], xdic[20];
	int key = 0;
	char keyw[50], yon;
	//记录用户的选择
	int choose;
	//定义文件指针
	FILE *fp1;
	//输出交互
	printf("1.手动输入密文 \n 2.从文件中导入\n 请选择:");
	scanf("%d", &choose);
	while (choose != 1 && choose != 2)
	{
		printf("选择错误!\n");
		scanf("%d", &choose);
	}
	getchar();
	if (choose == 1)
	{
		//记录用户输入保存到m数组中
		gets(cirptoText);
	}
	if (choose == 2)
	{
		printf("这个文件的名字必须是message.txt,请确认!\n");
		getchar();
		//打开写入密文的文件夹
		fp1 = fopen("F:\\Crypto\\message.txt", "r+");
		if (fp1 == 0)
		{
			printf("文件导入错误!\n");
			getch();
			exit(0);
		}
		//把密文写入文件中
		fscanf(fp1, "%s", cirptoText);
		//关闭文件夹与指针的关联
		fclose(fp1);
	}
	//把密文转换成大写
	changeUp(cirptoText);
	//输出转换后的密文
	printf("密文内容:\n%s\n\n第一步搜索密钥的长度 ，请选择？(Y|N)", cirptoText);
	scanf("%c", &yon);
	if (yon == 'y' || yon == 'Y')
	{
		getchar();
	}
	else
	{
		exit(0);
	}
	//输出连续字符的存在个数
	n = doulet(cirptoText, dl, num, c, d, e, f);
	for (i = 0; i < n; i++)
	{
		//输出连续字符、出现个数
		printf("%c%c  %d  ", dl[i][0], dl[i][1], num[i]);
		for (j = 0; j < num[i] - 1; j++)
		{
			//输出相对距离
			printf("%d,", d[i][j]);
		}
		//为格式布局
		if (num[i] > 3)
		{
			printf("\t");
		}
		else if (num[i] > 1)
		{
			printf("\t\t");
		}
		else
		{
			printf("\t\t\t");
		}
		for (j = 0; j < f[i]; j++)
		{
			//输出相对距离因子数
			printf("%d,", e[i][j]);
		}
		printf("\n");
	}
	//找出每个连续的字符
	for (i = 0; i < n; i++)
	{
		//每个字符所产生的相对距离因子个数
		for (j = 0; j < f[i]; j++)
		{
			//保存所有相对距离因子数
			zh[zhn++] = e[i][j];
		}
	}
	//对所有相对距离因子数进行排序
	qksort(zh, zhn);
	printf("\n密钥适合的长度:\n");
	//找出相对距离因子出现最多的
	gs = zhengl(yz, yzs, zh, zhn);
	//输出出现次数排序（即可能的密钥长度）
	for (i = 0; i < gs; i++)
	{
		printf("%-3d ", yz[i]);
	}
	printf("\n");
	printf("\n");
	//循环所有的出现，输出连续字符，出现个数，拟重合指数，对0.065的误差
	for (i = 0; i < gs; i++)
	{
		xic[i] = icAvg(cirptoText, yz[i]);
		xdic[i] = fabs(xic[i] - 0.065) * 100;
	}
	//找出误差小于0.01的
	for (j = 0; j < gs; j++)
	{
		if (xdic[j] < 1.0)
		{
			key = yz[j];
			break;
		}
	}
	//如果密钥为0
	if (key == 0)
	{
		printf("没有密钥长度!请重新选择密文!\n");
	}
	else {
		//输出所有拟重合误差小于0.01的
		for (i = 0; i < gs; i++)
		{
			if (xdic[i] < 1.0)
			{
				//输出因子数(可能的密钥长度），出现次数，拟重合指数，误差
				printf("%-5d%-5d  %lf\t%.2lf%%\n", yz[i], yzs[i], xic[i], xdic[i]);
				//找出误差小于0.01里出现最多的因子数
				if (yz[i] < key)
				{
					key = yz[i];
				}
			}
		}
		printf("推荐密钥长度 %d ,继续?第二步(Y|N)", key);
		scanf("%c", &yon);
		if (yon == 'y' || yon == 'Y')
		{
			getchar();
		}
		else
		{
			printf("输入密钥的长度:");
			scanf("%d", &key);
			getchar();
		}
		//找出密钥长度，根据拟重合接具体密钥
		circa(cirptoText, key, keyw);
		//输出具体密钥
		printf("%s\n", keyw);
		printf("推荐密钥%s 继续?（Y|N）", keyw);
		scanf("%c", &yon);
		if (yon == 'y' || yon == 'Y')
		{
			getchar();
		}
		else
		{
			printf("输入密钥:");
			scanf("%s", &keyw);
			getchar();
		}
			changeUp(keyw);
			//已知密钥解密
			sol(cirptoText, keyw);
		
		getch();
	}
}
