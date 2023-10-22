#include "treemap.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode TreeNode;

struct TreeNode
{
    Pair*     pair;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
};

struct TreeMap
{
    TreeNode* root;
    TreeNode* current;
    int (*lower_than)(void* key1, void* key2);
};

int lower_than_string(void* key1, void* key2)
{
    char* k1=(char*) key1;
    char* k2=(char*) key2;
    
    if(strcmp(k1, k2) < 0)
        return 1;

    return 0;
}

int lower_than_int(void* key1, void* key2)
{
    if (*((int*)key1) < *((int*)key2))
        return 1;

    return 0;
}

int is_equal(TreeMap* tree, void* key1, void* key2)
{
    if (tree->lower_than(key1, key2) == 0 && tree->lower_than(key2, key1) == 0)
        return 1;
    
    return 0;
}

TreeNode* CreateTreeNode(void* key, void* value)
{
    if (key == NULL || value == NULL)
        return NULL;

    TreeNode* temp = (TreeNode *)Malloc(sizeof(TreeNode));

    temp->pair = CreatePair(key, value);
    temp->parent = temp->left = temp->right = NULL;

    return temp;
}

TreeMap* CreateTreeMap(int (*lower_than)(void* key1, void* key2))
{
    TreeMap* temp = Malloc(sizeof(TreeMap));

    temp->root = NULL;
    temp->current = NULL;

    temp->lower_than = lower_than;

    return temp;
}

TreeNode* SearchTreeNode(TreeMap* tree, TreeNode* node, void* key)
{
    if (tree == NULL || key == NULL)
        return NULL;

    if (node == NULL || is_equal(tree, node->pair->key, key))
        return node;

    if (tree->lower_than(node->pair->key, key))
        return SearchTreeNode(tree, node->right, key);

    return SearchTreeNode(tree, node->left, key);
}

void InsertTreeMap(TreeMap* tree, void* key, void* value)
{
    if (SearchTreeMap(tree, key) != NULL || value == NULL)
        return;

    TreeNode* temp = CreateTreeNode(key, value);
    if (temp == NULL)
        return;


    if (tree->root == NULL)
    {
        tree->root = temp;
        tree->current = temp;
        return;
    }

    TreeNode* current = tree->root;
    TreeNode* parent = NULL;

    while (current != NULL)
    {
        parent = current;

        if (tree->lower_than(key, current->pair->key))
            current = current->left;
        else
            current = current->right;
    }

    temp->parent = parent;
    if (tree->lower_than(key, parent->pair->key))
        parent->left = temp;
    else
        parent->right = temp;

    tree->current = temp;
}

TreeNode* Minimum(TreeNode* x)
{
    if(x==NULL)
        return NULL;

    while (x->left != NULL)
        x = x->left;
    
    return x;
}

void RemoveNodeHelper(TreeMap* tree, TreeNode* node, void* val)
{
    if (node->parent->right == NULL || node->parent->left == NULL)
        return;

    if (is_equal(tree, node->parent->right->pair->key, node->pair->key))
        node->parent->right = val;

    else if (is_equal(tree, node->parent->left->pair->key, node->pair->key))
        node->parent->left = val;

}

void RemoveNode(TreeMap *tree, TreeNode *node)
{
    if (tree == NULL || node == NULL)
        return;

    if (SearchTreeMap(tree, node->pair->key) == NULL)
        return;

    // Sin hijos
    if (node->right == NULL && node->left == NULL)
        RemoveNodeHelper(tree, node, NULL);

    // Un hijo
    else if (node->right != NULL && node->left == NULL)
    {
        node->right->parent = node->parent;
        RemoveNodeHelper(tree, node, node->right);
    } 
    else if (node->right == NULL && node->left != NULL)
    {
        node->left->parent = node->parent;
        RemoveNodeHelper(tree, node, node->left);
    }

    // Dos hijos
    else if (node->right != NULL && node->left != NULL)
    {
        TreeNode *min = Minimum(node->right);
        node->pair->key = min->pair->key;
        node->pair->value = min->pair->value;
        RemoveNode(tree, min);
    }
}

void EraseTreeMap(TreeMap* tree, void* key)
{
    if (tree == NULL || tree->root == NULL || key == NULL)
      return;   
    
    if (SearchTreeMap(tree, key) == NULL)
      return;

    RemoveNode(tree, tree->current);
}

Pair* SearchTreeMap(TreeMap* tree, void* key)
{
    if (tree == NULL || key == NULL)
        return NULL;

    TreeNode *result = SearchTreeNode(tree, tree->root, key);
    tree->current = result;

    if (result == NULL)
        return NULL;

    return result->pair;
}

Pair* UpperBound(TreeMap* tree, void* key)
{
    if (tree == NULL || key == NULL)
        return NULL;

    TreeNode* ub = NULL;
    TreeNode* current = tree->root;

    while (current != NULL)
    {
        if (is_equal(tree, current->pair->key, key))
          return current->pair;
        
        else if (tree->lower_than(current->pair->key, key))
          current = current->right;     

        else if (tree->lower_than(current->pair->key, key) != 1)
        {
            ub = current;
            current = current->left;
        }
    }

    if (ub == NULL)
        return NULL;

    return ub->pair;
}

Pair* FirstTreeMap(TreeMap* tree)
{
    if (tree == NULL)
        return NULL;

    TreeNode* current = Minimum(tree->root);

    if (current != NULL)
        return current->pair;


    return NULL;
}

Pair* NextTreeMap(TreeMap* tree)
{
    if (tree == NULL || tree->current == NULL)
        return NULL;

    TreeNode* current = tree->current;

    if (current->right != NULL) 
    {
        tree->current = Minimum(tree->current->right);
        return tree->current->pair;
    }
    else
    {
        while (current->parent != NULL && current == current->parent->right)
        {
            current = current->parent;
        }
        
        tree->current = current->parent;
        if (current->parent != NULL)
        {
            return current->parent->pair;
        }
    }

    return NULL;
}