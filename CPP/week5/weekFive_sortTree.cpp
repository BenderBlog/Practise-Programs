#include <iostream>
#include <string>
using namespace std;

struct Tnode
{
    string word;
    int count;
    Tnode *left;
    Tnode *right;
};

class tree
{
private:
    Tnode *m_T;
    void forShow(Tnode *t);
    void forAdd(Tnode *&t, string words);

public:
    tree();
    void addNode(string words);
    void showTree();
};

tree::tree()
{
    m_T = NULL;
}

void tree::forShow(Tnode *t)
{
    if (t)
    {
        forShow(t->left);
        cout << t->word << " " << t->count << endl;
        forShow(t->right);
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

// Add Node
void tree::addNode(string words)
{
    forAdd(m_T, words);
}

// Show the Tree aka sort with
void tree::showTree()
{
    if (m_T)
    {
        forShow(m_T);
    }
    else
    {
        cout << "Tree is Empty!" << endl;
    }
}

int main()
{
    tree T;
    string words;
    while (cin >> words)
    {
        T.addNode(words);
    }
    T.showTree();
    return 0;
}