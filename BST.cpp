#include<iostream>
#include<vector>
#define MAX(A,B) (A>B)?A:B
using namespace std;
struct BST
{
	BST* m_LTree;
	BST* m_RTree;
	int m_Data=0;
	int m_level = 0;
	BST(int _Data)
	{
		m_LTree = nullptr;
		m_RTree = nullptr;
		m_Data = _Data;
	}
};
struct Stack
{
	vector<BST*> m_Data;
	void push(BST* _Data)
	{
		m_Data.push_back(_Data);
	}
	BST* pop()
	{
		if (m_Data.size() == 0)
			return nullptr;
		BST* topofstack = m_Data.back();
		m_Data.pop_back();
		return topofstack;
	}
	BST* peek()
	{
		BST* topofstack = m_Data.back();
		return topofstack;
	}
	int SizeofStack()
	{
		return m_Data.size();
	}
};
struct Queue
{
	vector<BST*> m_Data;
	void enqueue(BST* _Data)
	{
		m_Data.push_back(_Data);
	}
	BST* dequeue()
	{
		if (m_Data.size() == 0)
			return nullptr;
		BST* frontofQueue = m_Data.front();
		m_Data.erase(m_Data.begin());
		return frontofQueue;
	}
	BST* peek()
	{
		BST* frontofQueue = m_Data.front();
		return frontofQueue;
	}
	int SizeofQueue()
	{
		return m_Data.size();
	}
};
void AddNodeIterative(BST* Node, int _Data)
{
	BST* curr = Node;
	BST* parent = nullptr;
	while (curr != nullptr)
	{
		parent = curr;
		if (_Data < curr->m_Data)
			curr = curr->m_LTree;
		else
			curr = curr->m_RTree;
	}
	if (_Data < parent->m_Data)
		parent->m_LTree = new BST(_Data);
	else
		parent->m_RTree = new BST(_Data);
}
BST* AddNodeRecursive(BST* Node, int _Data)
{

	if (Node == nullptr)
		return new BST(_Data);
	if (_Data < Node->m_Data)
		Node->m_LTree = AddNodeRecursive(Node->m_LTree, _Data);
	else
		Node->m_RTree = AddNodeRecursive(Node->m_RTree,_Data);

	return Node;
}
void printPostorder(BST* Node)
{
	if (Node == nullptr)
		return;
	printPostorder(Node->m_LTree);
	printPostorder(Node->m_RTree);
	cout << Node->m_Data << " ";
}

void printInorder(BST* Node)
{
	if (Node == nullptr)
		return;
	printInorder(Node->m_LTree);
	cout << Node->m_Data << " ";
	printInorder(Node->m_RTree);
}

void printPreorder(BST* Node)
{
	if (Node==nullptr)
		return;
	cout << Node->m_Data << " ";
	printPreorder(Node->m_LTree);
	printPreorder(Node->m_RTree);
}
int GetHeight(BST* Node)
{
	if (Node == nullptr)
	{
		return 0;
	}
	int LHeight = 1 + GetHeight(Node->m_LTree);
	int RHeight = 1 + GetHeight(Node->m_RTree);
	return MAX(LHeight, RHeight);
}
int kthSmallest(BST* root, int* i, int k)
{
	if (root == nullptr)
		return INT_MAX;
	int left = kthSmallest(root->m_LTree, i, k);
	if (left != INT_MAX)
		return left;
	if (++ * i == k)
		return root->m_Data;
	return kthSmallest(root->m_RTree, i, k);
}
int kthSmallest(BST* root, int k)
{
	int i = 0;
	return kthSmallest(root, &i, k);
}
int kthLargest(BST* root, int* i, int k)
{
	if (root == nullptr)
		return INT_MAX;
	int left = kthLargest(root->m_RTree, i, k);
	if (left != INT_MAX)
		return left;
	if (++ * i == k)
		return root->m_Data;
	return kthLargest(root->m_LTree, i, k);
}
int kthLargest(BST* root, int k)
{
	int i = 0;
	return kthLargest(root, &i, k);
}
void DepthFirstTraversal(BST* Root)
{
	Stack NodeSttack;
	NodeSttack.push(Root);
	cout << "\n";
	BST* Left;
	BST* Right;
	BST* Node;
	while (NodeSttack.SizeofStack() > 0)
	{
		Node = NodeSttack.pop();
		Left = Node->m_LTree;
		Right = Node->m_RTree;
		cout <<"\n"<< Node->m_Data;
		if (Left != nullptr)
			NodeSttack.push(Left);
		if (Right != nullptr)
			NodeSttack.push(Right);
	}
}
void BreadthFirstTraversal(BST* Root)
{
	Queue NodeQueue;
	NodeQueue.enqueue(Root);
	cout << "\n";
	BST* Left;
	BST* Right;
	BST* Node;
	int m_level = 0;
	Root->m_level = m_level;
	while (NodeQueue.SizeofQueue() > 0)
	{
		Node = NodeQueue.dequeue();
		Left = Node->m_LTree;
		Right = Node->m_RTree;
		cout <<"\n"<< Node->m_Data << "	m_level:" << Node->m_level;
		if (Left != nullptr)
		{
			Left->m_level = Node->m_level+1;
			NodeQueue.enqueue(Left);
		}
		if (Right != nullptr)
		{	
			Right->m_level = Node->m_level+1;
			NodeQueue.enqueue(Right);
		}
	}
}
BST* RRotate(BST* root)
{
	BST* Temp = root->m_LTree;
	root->m_LTree = Temp->m_RTree;
	Temp->m_RTree = root;
	return Temp;
}
BST* LRotate(BST* root)
{
	BST* Temp = root->m_RTree;
	root->m_RTree = Temp->m_LTree;
	Temp->m_LTree = root;
	return Temp;
}
int main()
{
	BST* Root = new BST(10);
	AddNodeIterative(Root, 15);
	AddNodeRecursive(Root, 3);
	AddNodeRecursive(Root, 5); 
	AddNodeIterative(Root, 19);
	AddNodeRecursive(Root, 16);
	AddNodeRecursive(Root, 2);
	printPostorder(Root);
	cout << "\n";
	printInorder(Root);
	cout << "\n";
	printPreorder(Root);
	Root=RRotate(Root);
	cout << "\n Rotated Right";
	cout << "\n";
	printInorder(Root);
	cout << "\n Height:" << GetHeight(Root);
	cout << "\n KthLargest: " << kthLargest(Root, 3);
	DepthFirstTraversal(Root);
	BreadthFirstTraversal(Root);
	
}