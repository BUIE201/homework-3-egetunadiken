#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct Node
{
    int i;
    Node* pLeft;
    Node* pRight;

    Node(int iIn) : i(iIn), pLeft(nullptr), pRight(nullptr) {}
};

void InsertToTree(Node*& pRoot, Node* pNew)
{
    if (!pRoot)
    {
        pRoot = pNew;
        return;
    }

    if (pNew->i <= pRoot->i)
        InsertToTree(pRoot->pLeft, pNew);
    else
        InsertToTree(pRoot->pRight, pNew);
}

void DeleteNodeWithTwoChildren(Node*& q, Node*& p)
{
    if (p->pRight)
    {
        DeleteNodeWithTwoChildren(q, p->pRight);
        return;
    }

    p->i = q->i;
    q = p;
    p = p->pLeft;
}

void DeleteNodeFromTree(Node*& pRoot, int i)
{
    if (!pRoot)
        return;

    if (pRoot->i < i)
    {
        DeleteNodeFromTree(pRoot->pRight, i);
        return;
    }

    if (pRoot->i > i)
    {
        DeleteNodeFromTree(pRoot->pLeft, i);
        return;
    }

    Node* q = pRoot;
    if (!q->pRight)
        pRoot = q->pLeft;
    else if (!q->pLeft)
        pRoot = q->pRight;
    else
        DeleteNodeWithTwoChildren(q, q->pLeft);

    delete q;
}


void Checker(Node* pRoot) 
{
    Node* root = pRoot;
    vector <vector<int> > vect;
    vector <int> branch;
    while(root)
    {
        branch.push_back(pRoot->i);
        if(!(pRoot->pLeft || pRoot -> pRight)){vect.push_back(branch); break;}

    }
    cout << "Branch with the largest sum is: ";
}

int main()
{
    int i;

    Node* pRoot = nullptr;
    while (true)
    {
        cin >> i;
        if (i == 99)
            break;

        Node* p = new Node(i);
        InsertToTree(pRoot, p);
    }
    Checker(pRoot);
}
