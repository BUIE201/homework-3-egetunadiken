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
    int j = 1;
    vector<pair<vector<int>,int> > vec; 

    if(pRoot->pLeft && pRoot->pRight) //if it has two nodes
    {
        j = j+1; //then we have one more branch
        sum = sum + pRoot->i; //increase the sum with the node we're dealing with
        num.push_back(pRoot->i); //get this in the vector
        FindLargestBranch(pRoot->pLeft, sum, num, level+1); //left and right
        FindLargestBranch(pRoot->pRight, sum, num, level+1);
    }
    else if (pRoot->pLeft && !(pRoot->pRight)) // same with above, only one side. (84-95)
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
        num.push_back(pRoot->i);
        j = j-1; //if it has no child nodes, then we're done with that branch so decrease by 1.
        pair<vector<int>,int> PAIR1;
        PAIR1.first = num; //the 
        PAIR1.second = sum;
        vec.push_back(PAIR1);
        if(j == 0){return vec;}
    }
}

void Checker(Node* pRoot) //this checks all the branches and their sums.
{
    int sum = 0;
    int level = 0;
    vector<int> num;
    vector<pair<vector<int>,int> > vec = FindLargestBranch(pRoot, sum, num, level); //here is the main checking function
    for(int i = 0; i<vec.size(); i++)
    {
        if(vec[i].second > sum){sum = vec[i].second; level = i;} //I possibly made a syntax error here but the idea is that every sum is the second pair so they're compared
    }
    cout << "Branch with the largest sum is: ";
    for(int i =0; i< vec[level].first.size(); i++)
    {
        cout << vec[level].first[i] << " "; //the first is the vector of the numbers in branch so they're printed one by one.
    }
    cout << "-> SUM = " << vec[level].second; //second is the sum of numbers in the branch.

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
