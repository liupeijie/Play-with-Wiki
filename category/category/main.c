// Don't forget to add the '-lm' option to link math.h.
// $ gcc pagerank.c -lm
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINK_MAX 4552836 // links.txtの総行数
#define PAGE_MAX 229894  // pages.txtの総行数

typedef struct link_t {
    int src_id; // リンク元のページのid
    int dst_id; // リンク先のページのid
} link_t;

typedef struct page_t {
    int id;          // ページのid
    char* word;      // ページの見出し語
    int linking_num; // このページから出ているリンク数
    int linked_num;  // このページへ入ってくるリンク数
    double pagerank; // ページランク
} page_t;

link_t links[LINK_MAX]; // 大きさLINK_MAXの配列を宣言
page_t pages[PAGE_MAX]; // 大きさPAGE_MAXの配列を宣言

int link_num = 0; // リンク情報はlinks[link_num]まで
int page_num = 0; // ページ情報はpages[page_num]まで

void category_nums()
{
    int id;
    for (id = 0; id < page_num; id++) {
        printf("%d\n", pages[id].linked_num);
    }
    
}

void insert_link(int src_id, int dst_id) { // linksの最後にデータを追加する
    if (link_num < LINK_MAX) { // linksに空きがあるなら
        links[link_num].src_id = src_id;
        links[link_num].dst_id = dst_id;
        link_num++;
    } else {
        printf("テーブルがいっぱいです。ごめんなさい。\n");
        exit(1);
    }
}

void insert_page(int id, char* word) { // pagesの最後にデータを追加する
    if (page_num < PAGE_MAX) { // pagesに空きがあるなら
        pages[page_num].id = id;
        pages[page_num].word = word;
        pages[page_num].linking_num = 0;
        pages[page_num].linked_num = 0;
        pages[page_num].pagerank = 0;
        page_num++;
    } else {
        printf("テーブルがいっぱいです。ごめんなさい。\n");
        exit(1);
    }
}

void read_linkfile(char *filename) { // ファイルからリンク情報を読み込む
    FILE* file = fopen(filename, "r");  // ファイルを読み込み専用で開く
    if (file == NULL) { // ファイルが見つからなかったら
        printf("がんばってはみましたが、ファイル%sは見つかりませんでした\n", filename);
        exit(1); // エラーを出して終了
    }
    
    while (1) {
        int src_id, dst_id;
        int ret = fscanf(file, "%d\t%d\n", &src_id, &dst_id); // 1行リンク情報を読み込む
        if (ret == EOF) { // ファイルの終わりなら
            fclose(file); // ファイルを閉じて
            return; // 終了
        } else { // データがあったなら
            insert_link(src_id, dst_id); // それを追加して読み込みを続ける
        }
    }
}

void read_pagefile(char *filename) { // ファイルからページ情報を読み込む
    FILE* file = fopen(filename, "r"); // ファイルを読み込み専用で開く
    if (file == NULL) { // ファイルが見つからなかったら
        printf("がんばってはみましたが、ファイル%sは見つかりませんでした\n", filename);
        exit(1); // エラーを出して終了
    }
    
    while (1) {
        int id;
        char buffer[1024];
        int ret = fscanf(file, "%d\t%1023s\n", &id, buffer); // 1行、ページ情報を読み込む
        if (ret == EOF) { // ファイルの終わりなら
            fclose(file); // ファイルを閉じて
            return; // 終了
        } else { // データがあったなら
            int length = strlen(buffer);
            if (length == 1023) {
                printf("なんか見出し語が長すぎ\n");
                exit(1);
            }
            char* word = (char*)malloc(length + 1); // 見出し語を格納するメモリを確保
            strcpy(word, buffer);
            insert_page(id, word); // それを追加して読み込みを続ける
        }
    }
}

int main(void) {
    read_linkfile("cat_link.txt"); // リンク情報を読み込む
    read_pagefile("cats.txt"); // ページ情報を読み込む
    
    category_nums();
    return 0;
}
