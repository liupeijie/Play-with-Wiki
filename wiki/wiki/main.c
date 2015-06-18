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
#define SIZE3 7852561       //カテゴリID大きさ

#define WORD_LENGTH 5000     //wikipediaの見出し語の長さ
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
data_type2 table2[SIZE3];     //大きさSIZE2の配列を宣言

int num_classified[SIZE3]={0};  //被リンク数を格納する配列を宣言、0で初期化

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
            table2[classified].classified=classified;
            table2[classified].name=name;
}

void read_linkfile(char *filename){ /*ファイルからリンク情報を読み込む*/
    FILE *file;
    int page_id,classified;
    int r;
    
    file=fopen(filename,"r");   //ファイルを読み込み専用で開く
    if(file==NULL){ /*ファイルが見つからなかったら*/
        printf("ファイル%sが見つかりません\n",filename);
        exit(1);    //エラーを出して終了
    }
    while(1){
        r=fscanf(file,"%d\t%d\n",&page_id,&classified);  //1行リンク情報を読み込む
        if(r==EOF){ /*ファイルの終わりなら*/
            fclose(file);   //ファイルを閉じて
            return; //終了
        }else{  /*データがあったなら*/
            insert_linkend(page_id,classified);  //それを追加して読み込みを続ける
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
    for(i=1;i<SIZE1+1;i++){   /*全てのリンク関係について*/
        
        num_classified[table1[i].classified]+=1;    //カテゴリの中の数を数える
        
    }
    int j,dumy,k,rank;
    int count=0;
    int a[5000];
    int id[SIZE2];
    printf("ページ数が5000以上のカテゴリ：\n");
    for(i=0;i<SIZE3;i++){ //for all pages
        if(num_classified[i]>5000){
            a[count]=num_classified[i];
            id[count]=i;
            count+=1;
            printf("%s:%d\n",table2[i].name,num_classified[i]);

       }
    }
    for(i = 0; i < count; i++){
        for(j = i + 1; j < count; j++){
            if(a[i] < a[j]){
                dumy = a[i];
                a[i] = a[j];
                a[j] = dumy;
                dumy = id[i];
                id[i] = id[j];
                id[j] = dumy;
               
            }
        }
    }
     printf("ページ数が多い順のカテゴリランキング：\n");
    for(i=0;i<20;i++){
        k=id[i];
        rank=i;
        printf("rank%d ",rank+1);
        printf("%s  %d pages\n",table2[k].name,a[i]);
    }

    double end = get_time();
    printf("programing running time: %.6lf sec\n", end - begin);
}
