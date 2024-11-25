/**
*****************************************************************************
*  Copyright (C), 2024, GOSUN CL
*
*  @file    BinaryTree.h
*  @brief   二叉树支持库, 包含了二叉树的一些通用操作
*           1.特有类型: 新增 状态码/二叉树结点/二叉树根结点(消除歧义: 不存储数据的结点) 结构体
*           2.接口: 新增 二叉树子结点获取/二叉树值获取
*           3.功能: 新增 查找值/释放二叉树
*
*  @author  KafuuChino
*  @date    2024-11-22
*  @version V1.0.0 20241122
*****************************************************************************
*/
#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#define LEFT 0
#define RIGHT 1

typedef void* (*getChild)(void*, int);

typedef int (*getValue)(void*);

typedef enum{
    SUCCESS = 0,
    FAILED = -1
}Status;

typedef struct BinaryTreeNode_t{
    int value;
    struct BinaryTreeNode_t* leftChild;
    struct BinaryTreeNode_t* rightChild;
    struct BinaryTreeNode_t* parent;
}*BiNode;

typedef struct BinaryTreeRoot_t{
    int size;
    BiNode root;
}*BiTree;

void* getBiTreeChild(void* node, int child);

void* findNode(void* root, int value, getValue getValueFunc, getChild getChildFunc);

Status destroyTree(void* root, getChild getChildFunc);

#endif /* END _BINARYTREE_H_ */