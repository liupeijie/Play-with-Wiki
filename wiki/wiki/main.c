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
data_type2 table2[7852561];     //大きさSIZE2の配列を宣言

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

void QSort(int x[ ], int left, int right)
{
    int i, j;
    int pivot;
    
    i = left;                      /* ソートする配列の一番小さい要素の添字 */
    j = right;                     /* ソートする配列の一番大きい要素の添字 */
    
    pivot = x[(left + right) / 2]; /* 基準値を配列の中央付近にとる */
    
    while (1) {                    /* 無限ループ */
        
        while (x[i] < pivot)       /* pivot より大きい値が */
            i++;                   /* 出るまで i を増加させる */
        
        while (pivot < x[j])       /* pivot より小さい値が */
            j--;                   /*  出るまで j を減少させる */
        if (i >= j)                /* i >= j なら */
            break;                 /* 無限ループから抜ける */
        
        int temp;
        
        temp = x[i];
        x[i] = x[j];
        x[j] = temp;               /* x[i] と x[j]を交換 */
        
        i++;                       /* 次のデータ */
        j--;
    }
   
    
    if (left < i - 1)              /* 基準値の左に 2 以上要素があれば */
        QSort(x, left, i - 1);     /* 左の配列を Q ソートする */
    if (j + 1 <  right)            /* 基準値の右に 2 以上要素があれば */
        QSort(x, j + 1, right);    /* 右の配列を Q ソートする */
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
    int j,dumy,k,rank;
    int count=0;
    int a[5000];
    int id[SIZE2];
    for(i=0;i<SIZE2;i++){ //for all pages
        if(num_classified[i]>500){
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
    for(i=0;i<20;i++){
        k=id[i];
        rank=i;
        printf("rank%d ",rank+1);
        printf("%s、数は：%d\n",table2[k].name,a[i]);
    }

  //  }
   
  // printf("top is %d:%s,数：%d\n",id,table2[id].name,num_classified[id]);
    double end = get_time();
    printf("programing running time: %.6lf sec\n", end - begin);
}
