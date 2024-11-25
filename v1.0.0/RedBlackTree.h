/**
*****************************************************************************
*  Copyright (C), 2024, GOSUN CL
*
*  @file    ReaBlackTree.h
*  @brief   红黑树操作库, 前置库为二叉树操作库, 包含了一些红黑树的常用操作
*           1.特有类型: 新增 红黑树结点/红黑树根结点(消除歧义: 不存储数据的结点) 结构体
*           2.功能: 新增 新建红黑树/新建红黑树结点/左旋红黑树结点/右旋红黑树结点/插入红黑树结点/删除红黑树结点/查找红黑树值/释放红黑树
*           3.类型: 新增 颜色 并定义了相关宏
*
*  @author  KafuuChino
*  @date    2024-11-22
*  @version V1.0.0 20241122
*****************************************************************************
*/
#ifndef _REDBLACKTREE_H_
#define _REDBLACKTREE_H_

#include "BinaryTree.h"

#define BLACK 1
#define RED   0

typedef unsigned char Color;

typedef struct RBTreeNode_t{
    int value;
    struct RBTreeNode_t* leftChild;
    struct RBTreeNode_t* rightChild;
    struct RBTreeNode_t* parent;
    Color color;
}*RBNode;

typedef struct RBTreeRoot_t{
    unsigned int size;
    RBNode root;
}*RBTree;

void* getRBTreeChild(void* node, int child);

int getRBTreeValue(void* node);

RBTree createRBTree();

RBNode createRBNode(int value);

Status leftRotationRB(RBTree root, RBNode sign);

Status rightRotationRB(RBTree root, RBNode sign);

Status insertRBNode(RBTree root, int value);

Status deleteRBNode(RBTree root, int value);

RBNode findRBNode(RBTree root, int value);

Status destroyRBTree(RBTree root);

#endif /* END _REDBLACKTREE_H_ */