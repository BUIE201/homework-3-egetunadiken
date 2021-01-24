#include <iostream>
#include <vector>
#include <math.h>
#include <map>

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

void BranchCreator(Node* pRoot, vector<int> branch, vector<vector<int> >& vect)
{
    branch.push_back(pRoot->i);//adding this to the branch
    
    if(!(pRoot->pLeft) && !(pRoot -> pRight)){vect.push_back(branch);} //if they're both empty, this is done.
    else if (pRoot->pLeft && !(pRoot->pRight)){BranchCreator(pRoot->pLeft, branch, vect);} //if only there's a left branch
    else if (pRoot->pRight && !(pRoot->pLeft)){BranchCreator(pRoot->pRight, branch, vect);} //if there's only a right branch
    else {BranchCreator(pRoot->pLeft, branch, vect); BranchCreator(pRoot->pRight, branch, vect);} //if there are two branches to either side.
}


void Checker(Node* pRoot) 
{
    vector<vector<int> > vect;
    vector <int> branch;

    BranchCreator(pRoot, branch, vect); //this creates all of the branches and stores them in vect as seperate branches.

    int sum = 0;// this will give out the sum
    int b = -1; //this will determine which branch in vect is the greatest branch
    for (int i = 0 ; i < vect.size() ; i++)
    {
        int insum = 0; //this is for comparison purposes.
        for (int j = 0 ; j < vect[i].size() ; j++)
        {
            insum += vect[i][j]; 
        }
        if (insum > sum){sum = insum; b=i;} //checked if bigger than previous sum, if so, replaced.
    }

    cout << "Branch with the largest sum is: ";
    
    for (int j = 0 ; j < vect[b].size() ; j++)
    {
        cout << vect[b][j] << " ";
    }
    cout << "-> SUM = " << sum;
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
