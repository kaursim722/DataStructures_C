#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "BSP.h"
#include "Wall.h"
#include "List.h"


// Create a BSP tree 
BSPTree* BSP_Create(ListPtr data, void* (*GetSubtreeRoot)(ListPtr data), ListPtr (*GetSubtrees)(void* parent, ListPtr remaining), int (*DataCompare)(void* data1, void* data2), void (*DataPrinter)(void* data), void (*FreeData)(void *data)){
    BSPTree* create_BSP = (BSPTree*) malloc(sizeof(BSPTree));                           // malloc BSPTree 
    create_BSP -> GetSubtreeRoot = GetSubtreeRoot;
    create_BSP -> GetSubtrees = GetSubtrees;
    create_BSP -> DataCompare = DataCompare;
    create_BSP -> DataPrinter = DataPrinter;
    create_BSP -> FreeData = FreeData;
    create_BSP -> root = BuildSubtree(create_BSP, data, create_BSP -> root);            // set root equal to BuildSubtree
    return create_BSP;
}

TreeNode* TreeNode_Create(void* data){
	//printf("inside treenodeCreate\n");
    TreeNode* temp_node = (TreeNode*)malloc(sizeof(TreeNode));                          // malloc a TreeNode
    temp_node -> left = NULL;
    temp_node -> right = NULL;
    temp_node -> parent = NULL;
    temp_node -> data = data;                                                           // set data equal to data
    return temp_node;
}

TreeNode* BuildSubtree(BSPTree* tree, ListPtr remaining, TreeNode* parent){
	//printf("inside buildsubtree\n");
    segment* create_seg = tree -> GetSubtreeRoot(remaining);                            // create a segment using remaining List
    if(create_seg == NULL) {
        return NULL;
    }
    TreeNode* create_node = TreeNode_Create(create_seg);                                // create a treenode and set its parent equal to equal
    create_node -> parent = parent;
	if(list_length(remaining) < 1) {                                                    // if the length of the remaining list is less than 1, return create node
        return create_node;
    }           
    else {
        create_node -> left = BuildSubtree(tree, tree -> GetSubtrees(create_seg, remaining), create_node);          // else set left and right of create_node to BuildSubtree
        create_node -> right = BuildSubtree(tree, remaining, create_node);
        return create_node;
    }
}

void BSP_print(BSPTree* tree){                                                             // Print BSP by printing list
	ListPtr printingList = BSP_GetTraversal(tree);                                      
    list_print(printingList);
}	

ListPtr BSP_GetTraversal(BSPTree* tree){                                                                    // GetTraversal by creating list and traversing 
	ListPtr traversal_list = list_create(tree -> DataCompare, tree -> DataPrinter, tree -> FreeData);
    PreOrderTraverse(traversal_list, tree -> root);
    return traversal_list;
}

void PreOrderTraverse(ListPtr list, TreeNode* node){
	//printf("inside PreorderTraverse\n");
	if(node != NULL) {                                                                      // if node != NULL then append data in list and traverse node left and right
        list_append(list, node -> data);
        PreOrderTraverse(list, node -> left);
        PreOrderTraverse(list, node -> right);
    }
    else {
        return NULL;
    }
}

void DestroyTree(BSPTree* tree, bool freeData) {
    free(tree);
}