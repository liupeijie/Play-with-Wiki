//
//  main.c
//  yamanotesenngame
//
//  Created by 向日葵会下雨 on H27/06/16.
//  Copyright (c) 平成27年 向日葵会下雨. All rights reserved.
//

//
//  main.c
//  category
//
//  Created by 向日葵会下雨 on H27/06/16.
//  Copyright (c) 平成27年 向日葵会下雨. All rights reserved.
//


/*find most linked page*/
#include <stdio.h>
#include <stdlib.h>
# include <string.h>

#define SIZE1 52973671      //total links.txt
#define SIZE2 1483277       //total pages.txt
#define WORD_LENGTH 1000     //length of wikipedia

typedef struct data_t1{
    int id;                 //id of the page
    int linked;             //id of the linked page
}data_type1;

typedef struct data_t2{
    int id;
    char *word;
}data_type2;

data_type1 table1[SIZE1];     //declare array whose size is SIZE1
data_type2 table2[SIZE2];     //declare array whose size is SIZE2

int num_linked[SIZE2]={0};  //declare array ,inithiarize by 0

int n;                      //number of the links
int m;                      //number of the pages

void insert_linkend(int id,int linked){ /*add the data at the end of table1*/
    if(n<SIZE1-1){  /*table1 has another room*/
        table1[n+1].id=id;
        table1[n+1].linked=linked;
        n++;
    }else{
        printf("table is full\n");
        exit(1);
    }
}

void insert_pageend(int id,char *word){ /*add the data at the end of table2*/
    if(m<SIZE2-1){  /*table2 has another room*/
        table2[m+1].id=id;
        table2[m+1].word=word;
        m++;
    }else{
        printf("table is full\n");
        exit(1);
    }
}

void read_linkfile(char *filename){ /*read links*/
    FILE *file;
    int id,linked;
    int r;
    
    file=fopen(filename,"r");
    if(file==NULL){
        printf("couldn't find %s\n",filename);
        exit(1);
    }
    while(1){
        r=fscanf(file,"%d\t%d\n",&id,&linked);  //read 1 raw
        //printf("%d",r);
        if(r==EOF){
            fclose(file);
            return;
        }else{
            insert_linkend(id,linked);  //add it then repeat
        }
    }
}

void read_pagefile(char *filename){ /*read pages*/
    FILE *file;
    int id;
    char *word;
    int r;
    
    file=fopen(filename,"r");
    if(file==NULL){
        printf("couldn't find%s\n",filename);
        exit(1);
    }
    while(1){
        word=(char *)malloc(WORD_LENGTH);   //save memori
        r=fscanf(file,"%d\t%s\n",&id,word); //read 1 raw
        if(r==EOF){
            fclose(file);
            return;
        }else{
            insert_pageend(id,word);    //add and continue
        }
    }
    
}

int main(void){
    int i;//,j,dumy,k,rank;
    int count=0;
    int a[1000];
    int id[1000];
    
    n=-1;    //inithiarize by -1
    read_linkfile("cat_link.txt"); //read links
    m=-1;   //inithiarize -1
    read_pagefile("cats.txt"); // read pages
    for(i=0;i<SIZE1;i++){   //for all links
        num_linked[table1[i].linked]+=1;    //count linked number
    }
    
    char str1[1000]; /*serch word interested */
    printf("input the word you are interested in.\n");
    scanf("%s",str1);
    
    
    for(i=0;i<SIZE2;i++){ //for all pages
        if(strstr(table2[i].word,str1)!=NULL){/*check if the word is included*/
            printf("id=%d:%s\n",i,table2[i].word);
            a[count]=num_linked[i];
            count+=1;
            id[i]=i;
        }
        else{
            
        }
    }
    /* for(i = 0; i < count; i++){
     for(j = i + 1; j < count; j++){
     if(a[i] > a[j]){
     dumy = a[i];
     a[i] = a[j];
     a[j] = dumy;
     }
     else{
     }
     }
     }
     for(i=0;i<10;i++){
     printf("rank%d\n",i);
     k=id[i];
     rank=i;
     
     printf("ここきた？%s\n",table2[k].word);
     }*/
}