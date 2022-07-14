#ifndef _TREE
#define _TREE

#include <iostream>
#include <string>

namespace sortTree
{

    struct Tnode
    {
        std::string word;
        int count;
        Tnode *left;
        Tnode *right;
    };

    class tree
    {
    private:
        // Implement.
        Tnode *m_T;
        void forAdd(Tnode *&t, std::string words);
        void forShow(Tnode *t);
        void forSort(Tnode *t);
        void forFree(Tnode *&t);

    public:
        // Interface.
        tree();
        void addNode(std::string words);
        void showTree();
        void sort();
        void free();
    };

}

#endif