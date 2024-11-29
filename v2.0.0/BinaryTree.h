/**
*****************************************************************************
*  Copyright (C), 2024, GOSUN CL
*
*  @file    BinaryTree.h
*  @brief   二叉树支持库, 包含了二叉树的一些通用操作
*           1.功能 集成左右旋接口函数
*
*  @author  KafuuChino
*  @date    2024-11-24
*  @version V2.0.0 20241124
*****************************************************************************
*/
#ifndef BINARYTREE_H
#define BINARYTREE_H

#define LEFT 0
#define RIGHT 1

typedef int (*getSize)(void*);

typedef void* (*getRoot)(void*);

typedef void* (*getChild)(void*, int);

typedef void* (*getParent)(void*);

typedef int (*getValue)(void*);

typedef enum{
    SUCCESS = 0,
    FAILED = -1
}Status;

typedef void (*setRoot)(void*, void*);

typedef void (*setChild)(void*, void*, int);

typedef void (*setParent)(void*, void*);

typedef struct BinaryTreeNode_t{
    struct BinaryTreeNode_t* leftChild;
    struct BinaryTreeNode_t* rightChild;
    struct BinaryTreeNode_t* parent;
    int value;
}*BiNode;

typedef struct BinaryTreeRoot_t{
    BiNode root;
    int size;
}*BiTree;

Status rotation(void* head, void* node, unsigned int direction, getChild getChildFunc, getParent getParentFunc, setChild setChildFunc, setParent setParentFunc, setRoot setRootFunc);

Status preOrderTraverse(void* root, getValue getValueFunc, getChild getChildFunc, int size);

Status inOrderTraverse(void* root, getValue getValueFunc, getChild getChildFunc, int size);

Status postOrderTraverse(void *root, getValue getValueFunc, getChild getChildFunc, int size);

Status levelOrderTraverse(void *root, getValue getValueFunc, getChild getChildFunc, int size);

void* findNode(void* root, int value, getValue getValueFunc, getChild getChildFunc);

Status destroyTree(void* root, getChild getChildFunc);

#endif /* END BINARYTREE_H */
