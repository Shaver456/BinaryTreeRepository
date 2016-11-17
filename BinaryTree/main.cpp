//
//  main.cpp
//  BinaryTree
//
//  Created by 庄锦城 on 16/11/17.
//  Copyright (c) 2016年 no. All rights reserved.
//

//空二叉树的定义
//销毁二叉树，清空二叉树的区别
#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1

typedef char TElemType;
typedef int Status;
typedef struct BiTNode{
    TElemType data;
    struct BiTNode *lchild, *rchild;
    
}BiTNode,*BiTree;


Status InitBiTree( BiTree &T){
    T = (BiTree)malloc(sizeof(BiTNode));
    if(!T) exit(OVERFLOW);
    
    T -> lchild = NULL;
    T -> rchild = NULL;
    T -> data = ' ';
    return OK;
}

Status DestoryBiTree(BiTree &T){
    //销毁树，释放空间
    BiTNode *Tmp;
    Tmp = T;
    if(T){//树不空
        if(DestoryBiTree(T -> lchild))
            if(DestoryBiTree(T -> rchild)){
                free(T);
                return OK;
            }
        return ERROR;
    }else return OK;
}

Status CreatTree(BiTree &T){
    //先序构造树
    char ch;
    scanf("%c",&ch);
    
    if(ch == ' '){
        T -> data = ch;
        T -> lchild = NULL;
        T -> rchild = NULL;
    }
    else{
        
        BiTNode *base = (BiTNode *)malloc(sizeof(BiTNode));
        if(!base) exit(OVERFLOW); //函数结束之后这个空间会不会被释放掉？malloc申请的空间是不是要手动释放？
        
        T -> data = ch;
        CreatTree(T -> lchild);
        CreatTree(T -> rchild);
    }
    
    return OK;
}


Status ClearTree(BiTree &T){
    //将树清为空树
    if(T){
        if(ClearTree(T -> lchild))
            if(ClearTree(T -> rchild)){
                T -> data = ' ';
                return OK;
            }
        return ERROR;
    }
    else return OK;
}



Status BiTreeEmpty(BiTree T){
    return  (T -> data == ' ');
}


int BiTreeDepth(BiTree T){
    int LDepth = BiTreeDepth(T -> lchild);
    int RDepth = BiTreeDepth(T -> rchild);
    int CurDepth;
    CurDepth = ((LDepth > RDepth) ? LDepth : RDepth) + 1;
    if(BiTreeEmpty(T)) CurDepth = 0;
    return CurDepth;
}



BiTree Root(BiTree T){
    return T;
}

TElemType Value(BiTree T, BiTNode e){
    return e.data;
}

Status Assign(BiTree T, BiTNode &e, TElemType value){
    e.data = value;
    return OK;
}


BiTNode *Judge(BiTNode e){
    BiTNode *cur = &e;
    if(cur -> lchild == &e || cur -> rchild == &e)
        return cur;
    Judge(*e.lchild);
    Judge(*e.rchild);
    return NULL;
}


BiTNode *Parent(BiTree T, BiTNode e){
    BiTNode *rt = Root(T);
    if(rt == &e) return NULL;
    Judge(*T);
    return  NULL;
}


BiTNode *LeftChild(BiTree T, BiTNode e){
    return e.lchild;
}

BiTNode *RightChild(BiTree T, BiTNode e){
    return e.rchild;
}

BiTNode *leftSibling(BiTree T, BiTNode e){
    BiTNode *par = Parent(T, e);
    BiTNode *lsb = par -> lchild;
    return lsb;
}

BiTNode * RightSibling(BiTree T, BiTNode e){
    BiTNode *parent = Parent(T, e);
    return parent -> rchild;
}

Status InsertChild(BiTree T, BiTNode *p, int LR, BiTree c){
    //根据LR为0或为1，插入c为T中p所指向的结点的左或右子树，p所指向结点的原有左或右子树则成为c的右子树
    BiTNode *Tmp;
    if ( LR == 0){ //插入到左子树
        Tmp = p ->lchild;
        p -> lchild = c;
        c ->rchild = Tmp;
    }
    else{//插入到右子树
        Tmp = p -> rchild;
        p -> rchild = c;
        c -> rchild = Tmp;
    }
    
    return OK;
}

Status DeleteChild(BiTree T, BiTNode *p, int LR){
    if( LR == 0 ) DestoryBiTree( p -> lchild);
    else DestoryBiTree( p -> rchild);
    return OK;
}


Status PreOrderTraverse(BiTree T, Status (*Visit)(TElemType)){
    /*Status PrintElement(TElemType e){
     printf("e\n");
     return OK;
     }
     调用实例：PreOrderTraverse(T, PrintElement);
     */
    
    if(T){
        if(Visit(T -> data))
            if(PreOrderTraverse( T -> lchild, Visit))
                if(PreOrderTraverse( T -> rchild, Visit))
                    return OK;
        return ERROR;
    }
    else return OK;
    
}



Status InOrderTraverse(BiTree T, Status(* Visit)(TElemType e)){
    if (T) {
        if(InOrderTraverse(T -> lchild, Visit))
            if(Visit(T -> data))
                if(InOrderTraverse(T -> rchild, Visit))
                    return OK;
        return ERROR;
    }
    else
        return OK;
}

Status PostOrderTraverse(BiTree T, Status(* Visit)(TElemType e)){
    if(T){
        if(PostOrderTraverse(T -> lchild, Visit))
            if(PostOrderTraverse(T -> rchild, Visit))
                if(Visit(T -> data))
                    return OK;
        return ERROR;
    }
    else return OK;
}



int main(int argc, const char * argv[]) {
    BiTree Ta;
    
    //InitBiTree
    InitBiTree(Ta);
    
    printf("IS THE TREE EMPTY?\n");
    printf("%d",BiTreeEmpty(Ta));//BiTreeEmpty
    
    //CreatTree
    BiTree Tb;
    CreatTree(Tb);//先序构造一棵树
    
    BiTNode TbNode;
    TbNode=*Root(Tb);
    
    
    return 0;
}




