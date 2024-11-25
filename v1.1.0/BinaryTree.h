/**
*****************************************************************************
*  Copyright (C), 2024, GOSUN CL
*
*  @file    BinaryTree.h
*  @brief   二叉树支持库, 包含了二叉树的一些通用操作
*           1.功能: 新增 单栈前中后序遍历
*
*  @author  KafuuChino
*  @date    2024-11-23
*  @version V1.1.0 20241123
*****************************************************************************
*/
#ifndef BINARYTREE_H
#define BINARYTREE_H

#define LEFT 0
#define RIGHT 1

typedef int (*getSize)(void*);

typedef void* (*getRoot)(void*);

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

Status preOrderTraverse(void* root, getValue getValueFunc, getChild getChildFunc, int size);

Status inOrderTraverse(void* root, getValue getValueFunc, getChild getChildFunc, int size);

Status postOrderTraverse(void *root, getValue getValueFunc, getChild getChildFunc, int size);

void* findNode(void* root, int value, getValue getValueFunc, getChild getChildFunc);

Status destroyTree(void* root, getChild getChildFunc);

#endif /* END BINARYTREE_H */
