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

vector<pair<vector<int>,int> > FindLargestBranch(Node* pRoot, int sum, vector<int> num, int level)
{
    int i = 1;
    vector<pair<vector<int>,int> > vec; 

    if(pRoot->pLeft && pRoot->pRight)
    {
        i = i+1;
        sum = sum + pRoot->i;
        num.push_back(pRoot->i);
        FindLargestBranch(pRoot->pLeft, sum, num, level+1);
        FindLargestBranch(pRoot->pRight, sum, num, level+1);
    }
    else if (pRoot->pLeft && !(pRoot->pRight))
    {
        num.push_back(pRoot->i);
        sum = sum + pRoot->i;
        FindLargestBranch(pRoot->pLeft, sum, num, level+1);
    }
    else if (pRoot->pRight && !(pRoot->pLeft))
    {
        num.push_back(pRoot->i);
        sum = sum + pRoot->i;
        FindLargestBranch(pRoot->pRight, sum, num, level+1);
    }
    else
    {
        i = i-1;
        pair<vector<int>,int> PAIR1;
        PAIR1.first = num;
        PAIR1.second = sum;
        vec.push_back(PAIR1);
        if(i == 0){return vec;}
    }
}

void Checker(Node* pRoot)
{
    int sum = 0;
    int level = 0;
    vector<int> num;
    vector<pair<vector<int>,int> > vec = FindLargestBranch(pRoot, sum, num, level);
    for(int i = 0; i<vec.size(); i++)
    {
        if(vec[i].second > sum){sum = vec[i].second; level = i;}
    }
    cout << "Branch with the largest sum is: ";
    for(int i =0; i< vec[level].first.size(); i++)
    {
        cout << vec[level].first[i] << " ";
    }
    cout << "-> SUM = " << vec[level].second;

}

void Insert(Node*& pRoot, Node* pNewNode)
{
    if (!pRoot)
        pRoot = pNewNode;
    else
    {
        if (pNewNode->i < pRoot->i)
            Insert(pRoot->pLeft, pNewNode);
        else
            Insert(pRoot->pRight, pNewNode);
    }
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
