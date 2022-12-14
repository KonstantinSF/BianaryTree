#include <iostream>
using namespace std; 
using std::cout; 
using std::cin; 
using std::endl; 
#define tab "\t"
#define delimiter "\n-----------------------------------------------------\n"

class Tree
{
	class Element
	{
		int Data;
		Element* pLeft, * pRight; 
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) : Data(Data), pLeft(pLeft), pRight(pRight) 
		{
			cout << "EConstructor:\t" << endl; 
		}
		~Element()
		{
			cout << "EDestructor:\t" << endl; 
		}
		friend class Tree; 
	}*Root;

public:
	Element* getRoot()const
	{
		return this->Root; 
	}
	Tree() :Root(nullptr)
	{
		cout << "TConstructor:\t" << this << endl; 
	}
	~Tree()
	{
		cout << "TDestructor:\t" << this << endl; 
	}
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr) this->Root = new Element(Data); 
		if (Root == nullptr) return; //условие выхода из рекурсии
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr) Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft); 
		}
		else
		{
			if (Root->pRight == nullptr) Root->pRight = new Element(Data);
			else insert(Data, Root->pRight); 
		}
	}


	void print(Element* Root)const
	{
		if (Root == nullptr)return; 
		print(Root->pLeft); 
		cout << Root->Data << tab; 
		print(Root->pRight); 
	}
};

void main()
{
	setlocale(LC_ALL, "Russia"); 
	int n; 
	cout << "Enter a number of elements\t"; cin >> n; 
	Tree tree; 
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100, tree.getRoot()); 
	}
	tree.print(tree.getRoot()); 
	cout << endl; 
}