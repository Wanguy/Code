#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
 
typedef struct bookinfo book;
/****** 图书信息结构体 *******/
struct bookinfo
{
    int id;     /* 登录号 */
    char    name[32];   /* 书名 */
    char    author[12]; /* 作者名 */
    int class_id;   /* 分类号 */
    char    unit[256];  /* 出版单位 */
    int time[3];    /* 出版时间 */
    float   price;      /* 价格 */
 
    struct bookinfo *next;  /* 下个图书的信息 */
};
/*****************************/
 
 
/* 功能：录入图书信息 */
void input(book **head)
{
    book *s, *p;
 
    if(*head == NULL) {/* 如果表头为空，先为它分配内存 */
        *head = (book *)calloc(1, sizeof(book));
        p = *head;
    } else {/* 否则，就说明有内容，直接切换到尾结点 */
        p = *head;
        while(p->next) 
        p = p->next; 
    }
     
    /* 为这个结点分配内存 */
    s = (book *)calloc(1, sizeof(book));
    printf("登录号：");
    scanf("%d", &s->id);
 
    printf("书名：");
    scanf("%s", s->name);
 
    printf("作者名：");
    scanf("%s", s->author);
     
    printf("分类号：");
    scanf("%d", &s->class_id);
     
    printf("出版单位：");
    scanf("%s", s->unit);
     
    printf("出版时间[年 月 日]：");
    scanf("%d %d %d", &s->time[0], &s->time[1], &s->time[2]);
     
    printf("价格：");
    scanf("%f", &s->price);
     
    p->next = s; /* 保存这个结点 */
    p = p->next; /* 切换至下个结点 */
    p->next = NULL;  
         
    printf("已经成功录入！\n");
}
 
 
int output(book *head)
{
    book *p;
    p = head->next; 
    if(head == NULL || head->next == NULL)
    {
        printf("\t\t未记录图书信息！\n");
        return -1;
    }
    system("cls");/* 清空屏幕内容 */
    /* 打印表头 */
    printf(
        "┌───┬──────┬────┬───┬───────┬─────┬───┐\n"
        "│%s│    %s    │ %s │%s│   %s   │ %s │ %s │\n"
        "├───┼──────┼────┼───┼───────┼─────┼───┤\n"
        ,"登录号","书名","作者名","分类号","出版单位","出版时间","价格");
    /* 打印表中间的内容 */
    do {
        printf( "│%6d│%12s│%8s│%6d│%14s│%04d-%02d-%02d│%6.1f│\n", 
                p->id, p->name, p->author, p->class_id, p->unit, 
                p->time[0],p->time[1],p->time[2], p->price
        );
        p = p->next;/* 切换至下个结点 */
    } while(p != NULL);
    /* 打印表尾 */ 
    printf( "└───┴──────┴────┴───┴───────┴─────┴───┘\n");
    return 0;
}
 
 
/* 功能：保存链表中的图书信息数据至文件 */
int save_data(book *head)
{
    book *p;
    FILE *fp;
    /* 以只“写”的方式打开book.data二进制文件 */
    fp = fopen("book.data", "wb");
    /* 如果文件打开失败，就返回-1 */
    if(NULL == fp) {
        return -1;
    }
    p = head->next; 
    do {
        /* 
         * 把这个结点的数据全部写入至文件内
         * 由于next指针不需要写入至文件，因此，数据大小就是：
         * sizeof(book)-sizeof(book*)
         * 总数据大小减去指针的大小 
         */
        fwrite(p, sizeof(book), 1, fp);
        p = p->next;/* 切换至下个结点 */
    } while(p != NULL);
     
    fclose(fp);/* 关闭文件 */
    return 0; 
}
 
 
/* 功能：从文件读取图书信息数据 */
int read_data(book **head)
{
    int n;
    book *s, *p;
    FILE *fp;
    /* 以只“读”的方式打开book.data二进制文件 */
    fp = fopen("book.data", "rb");
    /* 如果文件打开失败，就返回-1 */
    if(NULL == fp) { 
        *head = NULL; 
        return -1;
    } 
     
    *head = (book *)calloc(1, sizeof(book));
    p = *head; 
     
    while(!feof(fp)) { 
        /* 为下个结点分配内存空间 */
        s = (book *)calloc(1, sizeof(book));
        /* 从文件内读取数据保存至结点 */
        n = fread(s, sizeof(book), 1, fp);
        if(n < 1) {
            free(s);
            p->next= NULL;   /* 最后一个结点为NULL */
            break; 
        }
         
        p->next = s; /* 保存下个结点 */
        p = p->next; /* 切换至下个结点 */
        p->next= NULL;   /* 最后一个结点为NULL */
    }
     
    fclose(fp);/* 关闭文件 */
    return 0; 
}
 
/* 功能：删除指定登录号的图书的信息 */
int delete(book *head)
{
    char name[256];
    int choice, id;
    int found = 0;
    book *p, *t;
 
    /* 如果表头为空 */
    if(head == NULL || head->next == NULL) {
        printf("没有记录学生信息！\n");
        return -1;
    }
    printf( 
        "要删除图书信息，请选择删除方式：\n"
        "[1]通过书名来删除\n"
        "[2]通过登录号来删除\n"
        "选择："
    );
    while(1) {
        scanf("%d", &choice);
        if(choice > 0 && choice < 3) {
            break;  
        }
             
        printf("选择错误，请重新选择：");
    }
    /* 接受用户输入的内容 */
    if(choice == 1) {
        printf("请输入书名：");
        scanf("%s", name);
    } else if(choice == 2) {
        printf("请输入登录号：");
        scanf("%d", &id);
    }
     
    p = head;
     
    while(p->next) {
        t = p;
        p = p->next;
        /* 根据用户输入的内容以及选择的方式，来查找匹配数据 */
        if( choice == 1 && strcmp(p->name, name) == 0
        || choice == 2 && p->id == id) {
            found = 1;
            break;
        }
    }
    /* 如果没有找到 */
    if( found != 1 ) {
        printf("没有找到需删除信息的学生！\n");
        return -1;
    }
    /* 打印表头 */
    printf(
        "┌───┬──────┬────┬───┬───────┬─────┬───┐\n"
        "│%s│    %s    │ %s │%s│   %s   │ %s │ %s │\n"
        "├───┼──────┼────┼───┼───────┼─────┼───┤\n"
        ,"登录号","书名","作者名","分类号","出版单位","出版时间","价格");
    /* 打印中间内容 */
    printf( "│%6d│%12s│%8s│%6d│%14s│%04d-%02d-%02d│%6.1f│\n", 
        p->id, p->name, p->author, p->class_id, p->unit, 
        p->time[0],p->time[1],p->time[2], p->price
    );
    /* 打印表尾 */ 
    printf( "└───┴──────┴────┴───┴───────┴─────┴───┘\n");
 
    while(1) {
        printf("真的需要删除？[1:是  2:否]："); 
        scanf("%d", &choice); 
        if(choice == 1) {
            t->next = p->next;
            free(p); /* 释放这个结点占用的内存 */
            printf("已经删除！\n");
            break;
        } else if(choice == 2) {
            printf("任意键继续......");
        } 
    }
    return 0;
}
 
 
/* 功能：查询图书信息 */
int find(book *head)
{
    char author[256], name[256];
    int choice;
    int found = 0;
    book *p, *t;
 
    if(head == NULL || head->next == NULL) {
        printf("没有记录学生信息！\n");
        return -1;
    }
    printf( 
        "要查询图书信息，请选择查询方式：\n"
        "[1]通过书名来查询\n"
        "[2]通过作者名来查询\n"
        "选择："
    );
    while(1) {
        scanf("%d", &choice);
        if(choice > 0 && choice < 3) { 
            break; 
        } 
        printf("选择错误，请重新选择：");
    }
    /* 接受用户输入的内容 */
    if(choice == 1) {
        printf("请输入书名：");
        scanf("%s", name);
    } else if(choice == 2) {
        printf("请输入作者名：");
        scanf("%s", author);
    }
     
    p = head;
    printf("查询结果：\n");
     
    /* 打印表头 */
    printf(
        "┌───┬──────┬────┬───┬───────┬─────┬───┐\n"
        "│%s│    %s    │ %s │%s│   %s   │ %s │ %s │\n"
        "├───┼──────┼────┼───┼───────┼─────┼───┤\n"
        ,"登录号","书名","作者名","分类号","出版单位","出版时间","价格");
         
    while(p->next) {
        t = p;
        p = p->next;
        /* 根据用户输入的内容以及选择的方式，来查找匹配数据 */
        if( choice == 1 && strcmp(p->name, name) == 0
        || choice == 2 && strcmp(p->author, author) == 0) {
            found = 1;
            /* 打印中间内容 */
            printf( 
                "│%6d│%12s│%8s│%6d│%14s│%04d-%02d-%02d│%6.1f│\n", 
                p->id, p->name, p->author, p->class_id, p->unit, 
                p->time[0],p->time[1],p->time[2], p->price
            );
        }
    }
    /* 打印表尾 */ 
    printf( "└───┴──────┴────┴───┴───────┴─────┴───┘\n");
    /* 如果没有找到 */
    if(found != 1) {
        printf("没有找到符合要求的学生信息！\n");
        return -1;
    }
    return 0;
}
 
/* 功能：修改图书信息 */
int modify(book *head)
{
    char name[256];
    int choice, id;
    int found = 0;
    book *p;
 
    if(head == NULL || head->next == NULL) {
        printf("没有记录学生信息！\n");
        return -1;
    }
    printf( 
        "要修改图书信息，请选择修改方式：\n"
        "[1]通过书名来修改\n"
        "[2]通过登录号来修改\n"
        "选择："
    );
    while(1) {
        scanf("%d", &choice);
         
        if(choice > 0 && choice < 3) { 
            break; 
        } 
        printf("选择错误，请重新选择：");
    }
    /* 接受用户输入的内容 */
    if(choice == 1) {
        printf("请输入书名：");
        scanf("%s", name);
    } else if(choice == 2) {
        printf("请输入登录号：");
        scanf("%d", &id);
    }
     
    p = head;
     
    while(p->next) {
        p = p->next;
        /* 根据用户输入的内容以及选择的方式，来查找匹配数据 */
        if( choice == 1 && strcmp(p->name, name) == 0
        || choice == 2 && p->id == id) {
            found = 1;
            break;
        }
    }
     
    if(found != 1) {
        printf("没有找到符合要求的图书信息！\n");
        return -1;
    }
    printf("登录号：");
    scanf("%d", &p->id);
 
    printf("书名：");
    scanf("%s", p->name);
 
    printf("作者名：");
    scanf("%s", p->author);
     
    printf("分类号：");
    scanf("%d", &p->class_id);
     
    printf("出版单位：");
    scanf("%s", p->unit);
     
    printf("出版时间[年 月 日]：");
    scanf("%d %d %d", &p->time[0], &p->time[1], &p->time[2]);
     
    printf("价格：");
    scanf("%f", &p->price);
    printf("已经修改！");
    return 0;
}
 
 
int main(void)
{
    int choice;
    book *head = NULL;
    read_data(&head);/* 读取数据 */
    while(1) {
        system("cls");/* 清空屏幕内容 */
 
        printf(
        "*********************************\n\n"
        "*\t图书信息管理系统\t*\n"
        "*\t\t\t\t*\n"
        "*\t1 --- 录入图书信息\t*\n"
        "*\t2 --- 查询图书信息\t*\n"
        "*\t3 --- 删除图书信息\t*\n"
        "*\t4 --- 修改图书信息\t*\n"
        "*\t5 --- 输出全部图书信息\t*\n"
        "*\t0 --- 退出并保存数据\t*\n"
        "*********************************\n\n"
        "请输入选项<0-5>："
        );
        scanf("%d", &choice); 
        if(choice == 0) {
            break;
        }
        switch(choice) {
        case 1 : input(&head);  getch();break;
        case 2 : find(head);    getch();break;
        case 3 : delete(head);  getch();break;
        case 4 : modify(head);  getch();break;
        case 5 : output(head);  getch();break;
        }
    }
    save_data(head);
    return 0;
}
