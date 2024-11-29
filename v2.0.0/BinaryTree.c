#include <stdio.h>
#include <stdlib.h>

#include "BinaryTree.h"

/* 此文件为BinaryTree.h的实现, 也是其余二叉树的支持库 */

/* 此处的root参数均为Node类根结点, head为各二叉树变体的头结点 */

/* 内嵌汇编计算log2(x), 搬运自CSDN算法介绍 */
static unsigned int LOG2(unsigned int x){
    unsigned int ret;
    __asm__ __volatile__ ("bsrl %1, %%eax":"=a"(ret):"m"(x));
    return ret;
}

/* 二叉树获取树根 */
static void* getBiTreeRoot(void* root){
    return (void*)(((BiTree)root) -> root);
}

/* 二叉树获取树大小 */
static int getBiTreeSize(void *root){
    return ((BiTree)root) -> size;
}

/* 二叉树获取子结点 */
static void* getBiTreeChild(void* node, int child){
    return (child == RIGHT) ? (void*)(((BiNode)node) -> rightChild) : (void*)(((BiNode)node) -> leftChild);
}

/* 二叉树获取值 */
static int getBiTreeValue(void *node){
    return ((BiNode)node) -> value;;
}

/* 二叉树获取父结点 */
static void* getBiTreeParent(void* node){
    return (void*)(((BiNode)node) -> parent);
}

/* 重设二叉树子结点 */
static void setBiTreeChild(void* node, void* value, int child){
    if (child == LEFT){
        ((BiNode)node) -> leftChild = ((BiNode)value);
    }else{
        ((BiNode)node) -> rightChild = ((BiNode)value);
    }
}

/* 重设二叉树父结点 */
static void setBiTreeParent(void* node, void* value){
    ((BiNode)node) -> parent = ((BiNode)value);
}

/* 重设二叉树根结点 */
static void setBiTreeRoot(void* root, void* value){
    ((BiTree)root) -> root = ((BiNode)value);
}

/* 二叉树旋转 */
Status rotation(void* head, void* sign, unsigned int direction, getChild getChildFunc, getParent getParentFunc, setChild setChildFunc, setParent setParentFunc, setRoot setRootFunc){
    if((head == NULL) || (sign == NULL)){
        return FAILED;
    }
    void* signChild = getChildFunc(sign, !direction);
    setChildFunc(sign, getChildFunc(signChild, direction), !direction);
    if (getChildFunc(signChild, direction) != NULL){
        setParentFunc(getChildFunc(signChild, direction), sign);
    }
    if (getParentFunc(sign) == NULL){
        setRootFunc(head, signChild);
    }else{
        if (getChildFunc(getParentFunc(sign), direction) == sign){
            setChildFunc(getParentFunc(sign), signChild, direction);
        }else{
            setChildFunc(getParentFunc(sign), signChild, !direction);
        }
    }
    setParentFunc(signChild, getParentFunc(sign));
    setChildFunc(signChild, sign, direction);
    setParentFunc(sign, signChild);
    return SUCCESS;
}

/* 二叉树前序遍历 */
Status preOrderTraverse(void* root, getValue getValueFunc, getChild getChildFunc, int size){
    if (root == NULL){
        return FAILED;
    }
    void* stack[size];
    int top = -1;

    stack[++top] = root;
    void* node;

    while (top != -1){
        node = stack[top--];
        printf("%d ", getValueFunc(node));

        if (getChildFunc(node, RIGHT)){
            stack[++top] = getChildFunc(node, RIGHT);
        }
        if (getChildFunc(node, LEFT)){
            stack[++top] = getChildFunc(node, LEFT);
        }
    }
    printf("\n");
    return SUCCESS;
}

/* 二叉树中序遍历 */
Status inOrderTraverse(void *root, getValue getValueFunc, getChild getChildFunc, int size){
    if (root == NULL){
        return FAILED;
    }
    void* stack[size];
    int top = -1;

    stack[++top] = root;
    void* node = getChildFunc(root, LEFT);

    while (top != -1 || node){
        if (node){
            stack[++top] = node;
            node = getChildFunc(node, LEFT);
        }else{
            node = stack[top--];
            printf("%d ", getValueFunc(node));
            node = getChildFunc(node, RIGHT);
        }
    }
    printf("\n");
    return SUCCESS;
}

/* 二叉树后序遍历 */
Status postOrderTraverse(void *root, getValue getValueFunc, getChild getChildFunc, int size){
    if (root == NULL){
        return FAILED;
    }
    void* stack[size];
    int top = -1;
    /* 记录先前访问节点 */
    void* prev = NULL;
    /* 记录当前访问节点 */
    void* current;
    current = root;

    while (top != -1 || current){
        if (current){
            stack[++top] = current;
            current = getChildFunc(current, LEFT);
        }else{
            current = stack[top];
            if (getChildFunc(current, RIGHT) == NULL || getChildFunc(current, RIGHT) == prev){
                current = stack[top--];
                printf("%d ", getValueFunc(current));
                prev = current;
                current = NULL;
            }else{
                current = getChildFunc(current, RIGHT);
            }
        }
    }

    printf("\n");
    return SUCCESS;
}

/* 二叉树层序遍历 */
Status levelOrderTraverse(void *root, getValue getValueFunc, getChild getChildFunc, int size)
{
    if (root == NULL){
        return FAILED;
    }
    /* 仅开辟理论最大需求内存 */
    void* stack_1[1 << LOG2(size)];
    void* stack_2[1 << LOG2(size)];
    
    int top_1 = -1;
    int top_2 = -1;

    stack_1[++top_1] = root;
    printf("%d ", getValueFunc(root));

    while (top_1 != -1){
        while (top_1 != -1){
            if (getChildFunc(stack_1[top_1], RIGHT)){
                stack_2[++top_2] = getChildFunc(stack_1[top_1], RIGHT);
            }
            if (getChildFunc(stack_1[top_1], LEFT)){
                stack_2[++top_2] = getChildFunc(stack_1[top_1], LEFT);
            }
            top_1--;
        }
        while (top_2 != -1){
            printf("%d ", getValueFunc(stack_2[top_2]));
            stack_1[++top_1] = stack_2[top_2--];
        }
    }

    printf("\n");
    return SUCCESS;
}

/* 二叉树查找值 */
void* findNode(void *root, int value, getValue getValueFunc, getChild getChildFunc)
{
    if(root == NULL){
        return NULL;
    }
    void* current = root;
    while (current){
        if (value < getValueFunc(current)){
            current = getChildFunc(current, LEFT);
        }else if (value > getValueFunc(current)){
            current = getChildFunc(current, RIGHT);
        }else{
            break;
        }
    }
    return current;
}

/* 销毁二叉树 */
Status destroyTree(void *root, getChild getChildFunc)
{
    if (root == NULL){
        return FAILED;
    }
    destroyTree(getChildFunc(root, LEFT), getChildFunc);
    destroyTree(getChildFunc(root, RIGHT), getChildFunc);
    free(root);

    return SUCCESS;
}

