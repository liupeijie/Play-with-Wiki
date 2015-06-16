//
//  main.c
//  wiki
//
//  Created by 向日葵会下雨 on H27/06/14.
//  Copyright (c) 平成27年 向日葵会下雨. All rights reserved.
//

/*find most linked page*/
#include <stdio.h>
#include <stdlib.h>
#define SIZE1 4552836      //cat_link.txtの総行数
#define SIZE2 229894       //cats.txtの総行数

#define WORD_LENGTH 1000     //wikipediaの見出し語の長さ
#include <sys/time.h>

double get_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

typedef struct data_t1{
    int page_id;                 //ページのid
    int classified;             //カテゴリのid
}data_type1;

typedef struct data_t2{
    int classified;
    char *name;
}data_type2;

data_type1 table1[SIZE1];     //大きさSIZE1の配列を宣言
data_type2 table2[SIZE2];     //大きさSIZE2の配列を宣言

int num_classified[SIZE2]={0};  //被リンク数を格納する配列を宣言、0で初期化

int n;                      //リンク情報数
int m;                      //ページ情報数


void insert_linkend(int page_id,int classified){ /*table1の最後にデータを追加する*/
    if(n<SIZE1-1){  /*table1に空きがあるなら*/
        table1[n+1].page_id=page_id;
        table1[n+1].classified=classified;
        n++;
    }else{
        printf("テーブルがいっぱいです\n");
        exit(1);
    }
}

void insert_pageend(int classified,char *name){ /*table2の最後にデータを追加する*/

   
        if(m<SIZE2-1){  /*table2に空きがあるなら*/
            table2[m+1].classified=classified;
            table2[m+1].name=name;
            m++;
        }else{
            printf("テーブルがいっぱいです\n");
            exit(1);
        }
    
}

void read_linkfile(char *filename){ /*ファイルからリンク情報を読み込む*/
    FILE *file;
    int id,linked;
    int r;
    
    file=fopen(filename,"r");   //ファイルを読み込み専用で開く
    if(file==NULL){ /*ファイルが見つからなかったら*/
        printf("ファイル%sが見つかりません\n",filename);
        exit(1);    //エラーを出して終了
    }
    while(1){
        r=fscanf(file,"%d\t%d\n",&id,&linked);  //1行リンク情報を読み込む
        if(r==EOF){ /*ファイルの終わりなら*/
            fclose(file);   //ファイルを閉じて
            return; //終了
        }else{  /*データがあったなら*/
            insert_linkend(id,linked);  //それを追加して読み込みを続ける
        }
    }
}

void read_pagefile(char *filename){ /*ファイルからページ情報を読み込む*/
    FILE *file;
    int id;
    char *name;
  //r  char *str1="Category:";
    int r;
    
    file=fopen(filename,"r");   //ファイルを読み込み専用で開く
    if(file==NULL){ /*ファイルが見つからなかったら*/
        printf("ファイル%sが見つかりません\n",filename);
        exit(1);    //エラーを出して終了
    }
    
    while(1){
       
        name=(char *)malloc(WORD_LENGTH);   //見出し語を格納するメモリを確保
        r=fscanf(file,"%d\t%s\n",&id,name); //1行、ページ情報を読み込む
        if(r==EOF){ /*ファイルの終わりなら*/
            fclose(file);   //ファイルを閉じて
            return; //終了
        }else{  /*データがあったなら*/
           // if(strstr(name,str1)!=NULL){
                insert_pageend(id,name);//それを追加して読み込みを続ける
                //i++;
                //printf("%s",name);
          //  }
        }
    }
    
    
}


int main(void){
    double begin = get_time();
    n=-1;    //table1[0]からデータを入れるために-1に初期化
    read_linkfile("/Users/liupeijie/kadai3/category/category/cat_link.txt"); //リンク情報を読み込む
    m=-1;   //table2[0]からデータを入れるために-1に初期化
    read_pagefile("/Users/liupeijie/kadai3/category/category/cats.txt"); //ページ情報を読み込む
    int i;
    for(i=0;i<SIZE1;i++){   /*全てのリンク関係について*/
        
        num_classified[table1[i].classified]+=1;    //カテゴリの中の数を数える
        
    }
   // printf("%d",i);
    int max=0;
    int id = 0;
    for(i=0;i<SIZE2;i++){
        if(max<num_classified[i] ){
            max=num_classified[i];
            id=i;
            printf("%d\n",i);
        }
    }
    
    printf("top is %d:%d\n",id,table2[id].classified);
    double end = get_time();
    printf("time: %.6lf sec\n", end - begin);
}
