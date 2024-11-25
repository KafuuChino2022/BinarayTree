/**
***************************************************************************************
*  Copyright (C), 2024, GOSUN CL
*
*  @file    RedBlackTree.h
*  @brief   红黑树操作库, 前置库为二叉树操作库, 包含了一些红黑树的常用操作
*           1.功能: 新增 前中后序遍历
*           2.错误处理: 修改 创建结点时错误返回逻辑:显式返回FAILED状态码以便调用者自行处理
*
*  @author  KafuuChino
*  @date    2024-11-23
*  @version V1.1.0 20241123
***************************************************************************************
*/
#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include "BinaryTree.h"

#define BLACK 1
#define RED   0

typedef unsigned char Color;

typedef struct RBTreeNode_t{
    int value;
    struct RBTreeNode_t* leftChild;
    struct RBTreeNode_t* rightChild;
    struct RBTreeNode_t* parent;
    Color color: 1;
}*RBNode;

typedef struct RBTreeRoot_t{
    unsigned int size;
    RBNode root;
}*RBTree;

RBTree createRBTree();

/**
***************************************************
*  @brief I suggest you not to use these functions. 
*/
RBNode createRBNode(int value);

Status leftRotationRB(RBTree root, RBNode sign);

Status rightRotationRB(RBTree root, RBNode sign);
/**************************************************/

Status insertRBNode(RBTree root, int value);

Status deleteRBNode(RBTree root, int value);

RBNode findRBNode(RBTree root, int value);

Status preOrderTraverseRB(RBTree root);

Status inOrderTraverseRB(RBTree root);

Status postOrderTraverseRB(RBTree root);

Status destroyRBTree(RBTree root);

#endif /* END REDBLACKTREE_H */