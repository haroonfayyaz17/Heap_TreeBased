#include <iostream>
#include <queue>
#include <stack>
using namespace std;
class Heap
{
	struct Node
	{
		int data;
		Node *left;
		Node *right;
		Node *parent;
	};
public:
	stack<Node*>s1;
	Node *root, *last;
	Heap() :root(NULL), last(NULL){}
	int getData(Node* p)
	{
		if (p == NULL)
			return 9999999999;
		else
			return p->data;
	}
	void insert(int N)
	{
		Node *p = new Node;
		p->data = N;
		p->left = p->right = p->parent = NULL;
		s1 = CompleteTree(p, N);
		last = p;
		percolate_Up(p, N);
	}
	stack<Node*> CompleteTree(Node *p, int N)
	{
		stack<Node*>s1;
		if (root == NULL)
		{
			root = p;
			s1.push(p);
		}
		else
		{
			queue<Node*> obj;
			obj.push(root);
			bool done = false;
			while (!obj.empty() && !done)
			{
				Node *element = obj.front();
				obj.pop();
				if (element->left == NULL)
				{
					element->left = p;
					p->parent = element;
					done = true;
				}
				else if (element->right == NULL)
				{
					element->right = p;
					p->parent = element;
					done = true;
				}
				else
				{
					obj.push(element->left);
					obj.push(element->right);
				}
				if (!done || element == root)
					s1.push(element);
			}
		}
		return s1;
	}
	void percolate_Up(Node *p, int N)
	{
		while (p->parent != NULL&&p->parent->data>N)
		{
			p->data = p->parent->data;
			p = p->parent;
		}
		p->data = N;
	}
	void percolate_Down(Node *p, int N)
	{
		while (p != NULL && (N>getData(p->left) || N>getData(p->right)))
		{
			if (getData(p->left) < getData(p->right))
			{
				p->data = getData(p->left);
				p = p->left;
			}
			else
			{
				p->data = getData(p->right);
				p = p->right;
			}
		}
		if (p != NULL)
			p->data = N;
	}
	int delete_Min()
	{
		Node *temp = NULL;
		int N;
		if (root == NULL)
			return N = -99999999;
		else
		{
			N = root->data;
			if (root->left == NULL)
				root = NULL;
			else
			{
				root->data = last->data;
				temp = last;
				if (last->parent->right == last)
				{
					last->parent->right = NULL;
					last = last->parent->left;
				}
				else
				{
					last->parent->left = NULL;
					if (s1.empty())
						last = last->parent;
					else
					{
						last = s1.top()->right;
						s1.pop();
					}
				}
				percolate_Down(root, root->data);
			}
			delete temp;
		}
		return N;
	}
	void decrease_Key(Node *ptr, int data, int factor)
	{
		if (ptr == NULL)
			return;
		else if (ptr->data == data)
			percolate_Up(ptr, data - factor);
		else
		{
			decrease_Key(ptr->left, data, factor);
			decrease_Key(ptr->right, data, factor);
		}
	}
	void increase_Key(Node *ptr, int data, int factor)
	{
		if (ptr == NULL)
			return;
		else if (ptr->data == data)
			percolate_Down(ptr, data + factor);
		else
		{
			increase_Key(ptr->left, data, factor);
			increase_Key(ptr->right, data, factor);
		}
	}
	int DeleteAtX(Node *ptr, int data)
	{
		if (ptr == NULL)
			return -9999999;
		decrease_Key(ptr, data, data - root->data + 10);
		return delete_Min();
	}
	void LevelOrderTraversal()
	{
		queue<Node*> obj;
		if (root == NULL)
			return;
		else
		{
			obj.push(root);
			while (!obj.empty())
			{
				Node *element = obj.front();
				obj.pop();
				if (element->left != NULL)
					obj.push(element->left);
				if (element->right != NULL)
					obj.push(element->right);
				cout << element->data << " ";
			}
		}
		cout << endl;
	}
};
int main()
{
	int num;
	Heap h;
	cout << "Enter 7 elements you want to insert in heap: ";
	for (int i = 0; i <7; i++)
	{
		cin >> num;
		h.insert(num);
	}
	cout << "Elements in heap are: \n";
	h.LevelOrderTraversal();
	cout << "Enter num do you want to delete from heap: ";
	cin >> num;
	cout << h.DeleteAtX(h.root, num) << endl;
	cout << "Elements in heap are: \n";
	h.LevelOrderTraversal();
	cout << "Enter 3 elements you want to insert in heap: ";
	for (int i = 0; i <3; i++)
	{
		cin >> num;
		h.insert(num);
	}
	cout << "Elements in heap are: \n";
	h.LevelOrderTraversal();
	cout << "Elements after heap sort: \n";
	while (h.root)
	{
		cout << h.delete_Min() << " ";
	}
	cout << endl;
	system("pause");
}