#include <stdlib.h>

#include "BinaryTree.h"

/* 此文件为BinaryTree.h的实现, 也是其余二叉树的支持库 */

/* 二叉树获取子结点 */
void *getBiTreeChild(void* node, int child){
    return child ? (void*)(((BiNode)node) -> rightChild) : (void*)(((BiNode)node) -> leftChild);
}

/* 二叉树获取值 */
int getBiTreeValue(void* node){
    return ((BiNode)node) -> value;
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
