#include "tree.hpp"
namespace sortTree
{
    using namespace std;
    // Init formula.
    tree::tree()
    {
        m_T = NULL;
    }

    void tree::forShow(Tnode *t)
    {
        if (t)
        {
            cout << t->word << ": " << t->count << endl;
            // cout << '\t';
            forShow(t->left);
            // cout << '\t';
            forShow(t->right);
        }
    }

    void tree::forSort(Tnode *t)
    {
        if (t)
        {
            forSort(t->left);
            cout << t->word << ": " << t->count << endl;
            forSort(t->right);
        }
    }

    void tree::forAdd(Tnode *&t, string words)
    {
        if (!t)
        {
            t = new Tnode;
            t->word = words;
            t->count = 1;
            t->left = NULL;
            t->right = NULL;
        }
        else if (words == t->word)
        {
            t->count += 1;
        }
        else if (words < t->word)
        {
            forAdd(t->left, words);
        }
        else
        {
            forAdd(t->right, words);
        }
        return;
    }

    void tree::forFree(Tnode *&t)
    {
        if (t)
        {
            forFree(t->left);
            forFree(t->right);
            delete (t);
        }
    }

    // Add Node
    void tree::addNode(string words)
    {
        forAdd(m_T, words);
    }

    // Show the Tree aka sort with
    void tree::showTree()
    {
        cout << endl << "Showing..." << endl;
        if (m_T)
        {
            forShow(m_T);
        }
        else
        {
            cout << "Tree is Empty!" << endl;
        }
    }

    // Show the Tree aka sort with
    void tree::sort()
    {
        cout << endl << "Sorting..." << endl;
        if (m_T)
        {
            forSort(m_T);
        }
        else
        {
            cout << "Tree is Empty!" << endl;
        }
    }
    // Clean the tree before exit.
    void tree::free()
    {
        if (m_T)
        {
            forFree(m_T);
            return;
        }
        else
        {
            return;
        }
    }
}
