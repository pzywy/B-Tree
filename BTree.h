#pragma once
#include "BTreeNode.h"
class BTree
{
    BTreeNode* root; // Pointer to root node
    int t;  // Tree order
public:
    //init tree as empty
    BTree(int _t)
    {
        root = NULL;  t = _t;
    }

    //print
    void print()
    {
        if (root != NULL) root->print();
    }

    //insert a new key in this B-Tree
    void insert(int k)
    {
        //tree is empty
        if (root == NULL)
        {
            // Allocate memory for root
            root = new BTreeNode(t, true);
            root->keys[0] = k;  // Insert key
            root->n = 1;  // Update number of keys in root
        }
        else // If tree is not empty
        {
            // If root is full, then tree grows in height
            if (root->n == 2 * t - 1)
            {
                // Allocate memory for new root
                BTreeNode* s = new BTreeNode(t, false);

                // Make old root as child of new root
                s->children[0] = root;

                // Split the old root and move 1 key to the new root
                s->splitChild(0, root);

                // New root has two children now.  Decide which of the
                // two children is going to have new key
                int i = 0;
                if (s->keys[0] < k)
                    i++;
                s->children[i]->insertToNotFull(k);

                // Change root
                root = s;
            }
            else  // If root is not full, call insertToNotFull for root
                root->insertToNotFull(k);
        }
    }

    //search a key
    BTreeNode* search(int k)
    {
        return (root == NULL) ? NULL : root->search(k);
    }
};

