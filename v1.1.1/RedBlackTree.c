#include <stdlib.h>

#include "RedBlackTree.h"

/* 此文件为RBTree.h的实现 */

/* 红黑树获取树根 */
static void* getRBTreeRoot(void* root){
    return (root) ? (void*)(((RBTree)root) -> root) : NULL;
}

/* 红黑树获取树大小 */
static int getRBTreeSize(void *root){
    return (root) ? ((RBTree)root) -> size : 0;
}

/* 红黑树获取子结点 */
static void* getRBTreeChild(void* node, int child){
    return child ? (void*)(((RBNode)node) -> rightChild) : (void*)(((RBNode)node) -> leftChild);
}

/* 红黑树获取值 */
static int getRBTreeValue(void *node){
    return ((RBNode)node) -> value;;
}

/* 创建红黑树根 */
RBTree createRBTree()
{
    RBTree newRoot = (RBTree)malloc(sizeof(struct RBTreeRoot_t));
    if (newRoot == NULL){
        return NULL;
    }
    newRoot -> size = 0;
    newRoot -> root = NULL;
    return newRoot;
}

/* 创建红黑树结点, 默认为红色结点 */
RBNode createRBNode(int value)
{
    RBNode newNode = (RBNode)malloc(sizeof(struct RBTreeNode_t));
    if (newNode == NULL){
        return NULL;
    }
    newNode -> value = value;
    newNode -> color = RED;
    newNode -> leftChild = NULL;
    newNode -> rightChild = NULL;
    newNode -> parent = NULL;
    return newNode;
}

/* 对sign左旋 */
Status leftRotationRB(RBTree root, RBNode sign)
{
    if((root == NULL) || (sign == NULL)){
        return FAILED;
    }
    RBNode signRight = sign -> rightChild;
    sign -> rightChild = signRight -> leftChild;
    if (signRight -> leftChild != NULL){
        (signRight -> leftChild) -> parent = sign;
    }
    if (sign -> parent == NULL){
        root -> root = signRight;
    }else{
        if ((sign -> parent) -> leftChild == sign){
            (sign -> parent) -> leftChild = signRight;
        }else{
            (sign -> parent) -> rightChild = signRight;
        }
    }
    signRight -> parent = sign -> parent;
    signRight -> leftChild = sign;
    sign -> parent = signRight;
    return SUCCESS;
}

/* 对sign右旋 */
Status rightRotationRB(RBTree root, RBNode sign)
{
    if((root == NULL) || (sign == NULL)){
        return FAILED;
    }
    RBNode signLeft = sign -> leftChild;
    sign -> leftChild = signLeft -> rightChild;
    if (signLeft -> rightChild != NULL){
        (signLeft -> rightChild) -> parent = sign;
    }
    if (sign -> parent == NULL){
        root -> root = signLeft;
    }else{
        if ((sign -> parent) -> leftChild == sign){
            (sign -> parent) -> leftChild = signLeft;
        }else{
            (sign -> parent) -> rightChild = signLeft;
        }
    }
    signLeft -> parent = sign -> parent;
    signLeft -> rightChild = sign;
    sign -> parent = signLeft;
    return SUCCESS;
}

/* 静态函数, 红黑树插入修复 */
static Status insertRBNodeFixUp(RBTree root, RBNode node){
    if ((root == NULL) || (node == NULL)){
        return FAILED;
    }
    while ((node != (root -> root)) && (((node -> parent) -> color) == RED)){
        RBNode parent = node -> parent;
        RBNode grandParent = parent -> parent;

        if (parent == grandParent -> leftChild){
            RBNode uncle = grandParent -> rightChild;
            if (uncle && (uncle -> color == RED)){
                /* uncle is red */
                parent -> color = BLACK;
                uncle -> color = BLACK;
                grandParent -> color = RED;
                node = grandParent;
            }else{
                if (node == parent -> rightChild){
                    /* node is right child */
                    leftRotationRB(root, parent);
                    node = parent;
                    parent = node -> parent;
                }
                /* after rotationRB, reset parent with BLACK, grandparent with RED, then right rotate */
                parent -> color = BLACK;
                grandParent -> color = RED;
                rightRotationRB(root, grandParent);
            }
        }else{
            RBNode uncle = grandParent -> leftChild;
            if (uncle && (uncle -> color == RED)){
                /* uncle is red */
                parent -> color = BLACK;
                uncle -> color = BLACK;
                grandParent -> color = RED;
                node = grandParent;
            }else{
                if (node == parent -> leftChild){
                    /* node is right child */
                    rightRotationRB(root, parent);
                    node = parent;
                    parent = node -> parent;
                }
                /* after rotationRB, reset parent with BLACK, grandparent with RED, then left rotate */
                parent -> color = BLACK;
                grandParent -> color = RED;
                leftRotationRB(root, grandParent);
            }
        }
    }
    (root -> root) -> color = BLACK;
    return SUCCESS;
}

/* 插入结点 */
Status insertRBNode(RBTree root, int value)
{
    if (root == NULL){
        return FAILED;
    }
    RBNode newNode = createRBNode(value);
    if (newNode == NULL){
        return FAILED;
    }
    if (root -> root == NULL){
        /* case1: the tree is empty */
        newNode -> color = BLACK;
        root -> root = newNode;
    }else{
        /* case2: find the place to insert */
        RBNode current = root -> root;
        RBNode parent = NULL;
        while (current){
            parent = current;
            if (value < current -> value){
                current = current -> leftChild;
            }else if (value > current -> value){
                current = current -> rightChild;
            }else{
                free(newNode);
                return FAILED;
            }
        }
        newNode -> parent = parent;
        if (value < parent -> value){
            parent -> leftChild = newNode;
        }else{
            parent -> rightChild = newNode;
        }

        insertRBNodeFixUp(root, newNode);
    }

    root -> size++;
    return SUCCESS;
}

static Status deleteRBNodeFixUp(RBTree root, RBNode child, RBNode parent){
    /* 兄弟结点 */
    RBNode anotherchild;

    while ((child == NULL || child -> color == BLACK) && root -> root != child){
        /* 若子结点为父结点的左节点 */
        if (parent -> leftChild == child){
            anotherchild = parent -> rightChild;

            if (anotherchild -> color == RED){
                /* 兄弟结点为红色, 将父结点左旋, 父兄交换颜色, 重定向兄弟结点, 这步操作一定会使兄弟节点为黑色 */
                anotherchild -> color = BLACK;
                parent -> color = RED;
                leftRotationRB(root, parent);
                anotherchild = parent -> rightChild;
            }
            /* 此时兄弟结点必定为黑 */
            if ((anotherchild -> leftChild == NULL || (anotherchild -> leftChild) -> color == BLACK) && (anotherchild -> rightChild == NULL || (anotherchild -> rightChild) -> color == BLACK)){
                /* 若兄弟结点子结点皆为黑色 */
                anotherchild -> color = RED;
                child = parent;
                parent = child -> parent;
            }else{
                if (anotherchild -> rightChild == NULL || (anotherchild -> rightChild) -> color == BLACK){
                    /* 若兄弟结点左节点为红, 右节点为黑 */
                    (anotherchild -> leftChild) -> color = BLACK;
                    anotherchild -> color = RED;
                    rightRotationRB(root, anotherchild);
                    anotherchild = parent -> rightChild;
                }
                /* 若兄弟结点右节点为红 */
                anotherchild -> color = parent -> color;
                parent -> color = BLACK;
                (anotherchild -> rightChild) -> color = BLACK;
                leftRotationRB(root, parent);
                break;
            }
        }else{
            anotherchild = parent -> leftChild;

            if (anotherchild -> color == RED){
                /* 兄弟结点为红色, 将父结点右旋, 父兄交换颜色, 重定向兄弟结点, 这步操作一定会使兄弟节点为黑色 */
                anotherchild -> color = BLACK;
                parent -> color = RED;
                rightRotationRB(root, parent);
                anotherchild = parent -> leftChild;
            }
            /* 此时兄弟结点必定为黑 */
            if ((anotherchild -> leftChild == NULL || (anotherchild -> leftChild) -> color == BLACK) && (anotherchild -> rightChild == NULL || (anotherchild -> rightChild) -> color == BLACK)){
                /* 若兄弟结点子结点皆为黑色 */
                anotherchild -> color = RED;
                child = parent;
                parent = child -> parent;
            }else{
                if (anotherchild -> leftChild == NULL || (anotherchild -> leftChild) -> color == BLACK){
                    /* 若兄弟结点左节点为黑, 右节点为红 */
                    (anotherchild -> rightChild) -> color = BLACK;
                    anotherchild -> color = RED;
                    leftRotationRB(root, anotherchild);
                    anotherchild = parent -> leftChild;
                }
                /* 若兄弟结点右节点为黑 */
                anotherchild -> color = parent -> color;
                parent -> color = BLACK;
                (anotherchild -> leftChild) -> color = BLACK;
                rightRotationRB(root, parent);
                break;
            }
        }
    }

    if (root -> root){
        (root -> root) -> color = BLACK;
    }

    return SUCCESS;
}

/* 删除结点 */
Status deleteRBNode(RBTree root, int value){
    if(root == NULL){
        return FAILED;
    }
    /* 找到需要删除的结点 */
    RBNode target = findRBNode(root, value);
    if (target == NULL){
        return FAILED;
    }

    /* 待删除结点的孩子, 父亲与颜色, 方便进行修正 */
    RBNode child = NULL, parent = NULL;
    Color color;

    /* 该结点有两个孩子, 用前驱结点取代目标结点, 目标结点移出红黑树 */
    if ((target -> leftChild) && (target -> rightChild)){
        /* 寻找前驱结点 */
        RBNode prev = target -> leftChild;
        while(prev -> rightChild){
            prev = prev -> rightChild;
        }
        /* 更新父节点中的孩子信息 */
        if (target -> parent){
            /* 若删除结点不为头结点 */
            if ((target -> parent) -> leftChild == target){
                (target -> parent) -> leftChild = prev;
            }else{
                (target -> parent) -> rightChild = prev;
            }
        }else{
            /* 若删除结点为头结点 */
            root -> root = prev;
        }
        /* 前驱结点信息, child为leftChild */
        child = prev -> leftChild;
        parent = prev -> parent;
        color = prev -> color;
        /* 若删除结点为前驱结点的父结点 */
        if (parent == target){
            parent = prev;
        }else{
            /* 若前驱结点有左孩子, 将左孩子连接到前驱结点的上一个结点 */
            if (child){
                child -> parent = parent;
            }
            parent -> rightChild = child;
            prev -> leftChild = target -> leftChild;
            (target -> leftChild) -> parent = prev;
        }

        /* 将前驱结点的信息更新为目标结点原信息, 完成对目标结点的取代 */
        prev -> parent = target -> parent;
        prev -> color = target -> color;
        prev -> rightChild = target -> rightChild;
        (target -> rightChild) -> parent = prev;
    }else{
        if (target -> leftChild){
            child = target -> leftChild;
        }else{
            child = target -> rightChild;
        }
        parent = target -> parent;
        color = target -> color;

        if (child){
            child -> parent = parent;
        }

        /* 目标节点非根节点, 将父节点的孩子重定向 */
        if (parent){
            if (parent -> leftChild == target){
                parent -> leftChild = child;
            }else{
                parent -> rightChild = child;
            }
        }else{
            root -> root = child;
        }
    }

    /* 进行调整并释放待删除结点 */
    if (color == BLACK){
        deleteRBNodeFixUp(root, child, parent);
    }
    free(target);
    root -> size--;
    return SUCCESS;
}

/* 查找数据 */
RBNode findRBNode(RBTree root, int value){
    if((root == NULL) || (root -> root == NULL)){
        return NULL;
    }
    return (RBNode)findNode(root -> root, value, getRBTreeValue, getRBTreeChild);
}

/* 前序遍历红黑树 */
Status preOrderTraverseRB(RBTree root){
    if (root == NULL){
        return FAILED;
    }
    return preOrderTraverse(root -> root, getRBTreeValue, getRBTreeChild, root -> size);
}

/* 中序遍历红黑树 */
Status inOrderTraverseRB(RBTree root){
    if (root == NULL){
        return FAILED;
    }
    return inOrderTraverse(root -> root, getRBTreeValue, getRBTreeChild, root -> size);
}

/* 后序遍历红黑树 */
Status postOrderTraverseRB(RBTree root)
{
    if (root == NULL){
        return FAILED;
    }
    return postOrderTraverse(root -> root, getRBTreeValue, getRBTreeChild, root -> size);
}

/* 层序遍历红黑树 */
Status levelOrderTraverseRB(RBTree root){
    if (root == NULL){
        return FAILED;
    }
    return levelOrderTraverse(root -> root, getRBTreeValue, getRBTreeChild, root -> size);
}

/* 释放红黑树 */
Status destroyRBTree(RBTree root)
{
    if(root == NULL){
        return FAILED;
    }
    destroyTree(root -> root, getRBTreeChild);
    free(root);

    return SUCCESS;
}