#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <getch.h>
typedef struct Txl 
{
	char name[20];	// 姓名 
	char sex;		// 性别
	char tel[12];	// 电话
}Txl;
	int count = 0 ;		// 有效联系人数量
	Txl txl[100];
void anykey_continue(void)
{
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	puts("任意键继续...");
	getch();
}

void show_msg(const char* msg,float sec)
{
	printf("%s",msg);
	fflush(stdout);
	usleep(sec*1000000);
}

void add(void)
{
	if(count >= 100)
	{
		puts("系统正在升级，请等待....");
		return; 
	}

	int i = 0;
	while(txl[i].sex) i++;
	
	printf("请输入姓名 性别 电话:");
	scanf("%s %c %s",txl[i].name,&txl[i].sex,txl[i].tel);
	count++;

	show_msg("添加联系人成功!\n",0.5);
}

void del(void)
{
	char i = 0;
	char key[20] = {};

	printf("请输入要删除的姓名或电话:");
	scanf("%s",key);

	do{
		if(txl[i].sex)
		{
			if(isdigit(key[0]))
			{
				if(0 == strcmp(txl[i].tel,key)) break;
			}
			else
			{
				if(0 == strcmp(txl[i].name,key)) break;
			}
		}
	}while(++i<100);

	if(i < 100)
	{
		printf("删除 %s %s %s 联系人成功!\n",txl[i].name,'w'==txl[i].sex?"女":"男",txl[i].tel);
		txl[i].sex = 0;
		count--;
	}
	else
	{
		printf("没有找到联系人,检查查询条件:%s\n",key);
	}
	
	show_msg("",1.5);
}

void modify(void)
{
	char key[20] = {};
	printf("请输入要修改的联系人姓名:");
	scanf("%s",key);
	for(int i=0; i<100; i++)
	{
		if(txl[i].sex && 0 == strcmp(txl[i].name,key))
		{
			printf("请重新输入联系人的 姓名 性别 电话:");
			scanf("%s %c %s",txl[i].name,&txl[i].sex,txl[i].tel);
			show_msg("修改联系人成功!\n",1.5);
			return;
		}
	}

	show_msg("未找到该联系人!\n",1.5);
}

void find(void)
{
	char key[20] = {};
	printf("请输入要查询的关键字:");
	scanf("%s",key);

	for(int i=0; i<100; i++)
	{
		if(txl[i].sex && (strstr(txl[i].name,key) || strstr(txl[i].tel,key)))
		{
			printf("%s %s %s\n",txl[i].name,'w'==txl[i].sex?"女":"男",txl[i].tel);
		}
	}
	anykey_continue();
}

void list(void)
{
	for(int i=0; i<100; i++)
	{
		if(txl[i].sex)
		{
			printf("%s %s %s\n",txl[i].name,'w'==txl[i].sex?"女":"男",txl[i].tel);
		}
	}

	anykey_continue();
}

char menu(void)
{
	system("clear");
	puts("***欢迎使用指针通讯录***");
	puts("1、添加联系人");
	puts("2、删除联系人");
	puts("3、修改联系人");
	puts("4、查询联系人");
	puts("5、遍历联系人");
	puts("6、退出通讯录");
	puts("-------------------");
	printf("请输入指令:");
	char cmd = getch();
	printf("%c\n",cmd);
	return cmd;
}

int main(int argc,const char* argv[])
{
	for(;;)
	{
		switch(menu())
		{
			case '1': add(); break;
			case '2': del(); break;
			case '3': modify(); break;
			case '4': find(); break;
			case '5': list(); break;
			case '6': return 0;
		}
	}
}

