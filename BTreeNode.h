#pragma once
#include <iostream>
class BTreeNode
{

public:
    BTreeNode(int _t, bool _leaf)   // Constructor
    {
        t = _t;
        leaf = _leaf;

        keys = new int[2 * t - 1];//2*t-1 == max
        children = new BTreeNode * [2 * t];

        n = 0;//tree is empty so keys=0;
    }

    // print tree in order
    void print()
    {
        int i;
        for (i = 0; i < n; i++)
        {
            // If not leaf go through child before printing key[i] 
            if (leaf == false)
                children[i]->print();
            std::cout << keys[i] << " ";
        }

        // last child
        if (leaf == false)
            children[i]->print();
    }

    // returns NULL if k is not present.
    BTreeNode* search(int searchedValue)
    {
        // Find the key >= searchedValue
        int i = 0;
        while (i < n && keys[i] < searchedValue)
            i++;

        // key == searchedValue return - element found
        if (keys[i] == searchedValue)
            return this;

        // this is leaf so and we didnt find element
        if (leaf == true)
            return NULL;

        // no element here go to next child.
        return children[i]->search(searchedValue);
    }

    //insert if tree not full
    void insertToNotFull(int insertedValue)
    {
        //set i on last element
        int i = n - 1;

        // If this is a leaf
        if (leaf == true)
        {
            //find right location by pushing all greater keys to the right
            while (i >= 0 && keys[i] > insertedValue)
            {
                keys[i + 1] = keys[i];
                i--;
            }

            // we find right location!
            keys[i + 1] = insertedValue;
            n = n + 1;
        }
        else // If this is not leaf
        {
            // Find the right child
            while (i >= 0 && keys[i] > insertedValue)
                i--;

            // is child  full?
            if (children[i + 1]->n == 2 * t - 1)
            {
                // If the child is full, then split it
                splitChild(i + 1, children[i + 1]);

                // find right child
                if (keys[i + 1] < insertedValue)
                    i++;
            }
            children[i + 1]->insertToNotFull(insertedValue);
        }
    }

    // function to split the child y of this node.
    //The Child y must be full when this function is called
    void splitChild(int i, BTreeNode* y)
    {
        // Create a new node which is going to store (t-1) keys
        BTreeNode* newChild = new BTreeNode(y->t, y->leaf);
        newChild->n = t - 1;

        // Copy the last (t-1) keys of y to z
        for (int j = 0; j < t - 1; j++)
            newChild->keys[j] = y->keys[j + t];

        // Copy the last t children of y to z
        if (y->leaf == false)
        {
            for (int j = 0; j < t; j++)
                newChild->children[j] = y->children[j + t];
        }

        // Reduce the number of keys in y
        y->n = t - 1;

        // create space of new child
        for (int j = n; j >= i + 1; j--)
            children[j + 1] = children[j];

        // Link the new child to this node
        children[i + 1] = newChild;

        // Find the location of new key and move all greater keys one space ahead
        for (int j = n - 1; j >= i; j--)
            keys[j + 1] = keys[j];

        // Copy the middle key of y to this node
        keys[i] = y->keys[t - 1];

       //change count of elements
        n = n + 1;
    }

    //for accesing private
    friend class BTree;

private:
    int* keys;  //array of keys
    int t;      // Tree order
    BTreeNode** children; //array of child pointers
    int n;     // current number of keys
    bool leaf; //true if node is leaf
};

