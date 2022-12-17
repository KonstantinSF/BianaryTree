#include <iostream>
using namespace std; 
using std::cout; 
using std::cin; 
using std::endl; 
#define tab "\t"
#define delimiter "\n-----------------------------------------------------\n"

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft, * pRight; 
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) : Data(Data), pLeft(pLeft), pRight(pRight) 
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << endl;
#endif // DEBUG

		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << endl;
#endif // DEBUG

		}
		bool isLeaf() const
		{
			return pLeft == pRight; 
		}
		friend class Tree; 
		friend class UniqueTree; 
	}*Root;
public:

	Element* getRoot()const
	{
		return Root; 
	}
	Tree() :Root(nullptr)
	{
#ifdef DEBUG
		cout << "TConstructor:\t" << this << endl;
#endif // DEBUG

	}
	Tree (const std::initializer_list<int>&il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
			insert(*it, Root); 
	}
	~Tree()
	{
		clear(Root); 
		#ifdef DEBUG
		cout << "TDestructor:\t" << this << endl;
#endif // DEBUG
	}
	void insert(int Data)
	{
		return insert(Data, Root);
	}
	void clear()
	{
		clear(Root); 
		Root = nullptr; 
	}
	void erase(int Data)
	{
		erase(Data, Root); 
	}
	int minValue()const
	{
		return minValue(Root); 
	}
	int maxValue()const
	{
		return maxValue(Root); 
	}
	int Count()const
	{
		return Count(Root); 
	}
	int Sum()const
	{
		return Sum(Root); 
	}
	double Avg()const
	{
		return(double)Sum(Root) / Count(Root);
	}
	int Depth()const
	{
		return Depth(Root); 
	}
	void print()const
	{
		print(Root); 
		cout << endl; 
	}
private:
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
	
	int minValue(Element* Root)const
	{
		/*if (Root->pLeft == nullptr)return Root->Data; 
		else return minValue(Root->pLeft); */
		return Root->pLeft ? minValue(Root->pLeft): Root->Data; 
	}
	int maxValue(Element* Root)const
	{
		/*if (Root->pRight == nullptr)return Root->Data; 
		else return maxValue(Root->pRight); */
		return Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight); 

	}
	int Count(Element* Root)const
	{
		/*if (Root == nullptr)return 0;
		else return count(Root->pLeft) + count(Root->pRight) + 1;*/
		return !Root ?0 : Count(Root->pLeft) + Count(Root->pRight) + 1; 
	}
	int Sum(Element* Root) const
	{
		return !Root ? 0 : Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data; 
	}
	int Depth(Element* Root)const
	{
		if (Root == nullptr)return 0;
		/*if (Depth(Root->pLeft) < Depth(Root->pRight))return Depth(Root->pRight) + 1;
		else return Depth(Root->pLeft) + 1;*/
		int left_depth = Depth(Root->pLeft) + 1;
		int right_depth = Depth(Root->pRight) + 1;
		return left_depth > right_depth ? left_depth : right_depth;
		/*return !Root ? 0 :
			Depth(Root->pLeft) > Depth(Root->pRight) ?
			Depth(Root->pLeft) + 1 :
			Depth(Root->pRight) + 1;*/
	}
	void erase(int Data, Element* Root)
	{
		if (Root == nullptr)return; 
		erase(Data, Root->pLeft); 
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->isLeaf())
			{
				delete Root; Root = nullptr; 
			}
			else
			{
				if (Count(Root->pLeft) > Count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft); 
					erase(maxValue(Root->pLeft), Root->pLeft); 
				}
				else
				{
					Root->Data = minValue(Root->pRight); 
					erase(minValue(Root->pRight), Root->pRight); 
				}
			}
		}
	}
	void clear(Element* Root)
	{
		if (Root == nullptr)return; //условие выхода из рекурсии
		clear(Root->pLeft); 
		clear(Root->pRight); 
		delete Root; 
	}

	void print(Element* Root)const
	{
		if (Root == nullptr)return; 
		print(Root->pLeft); 
		cout << Root->Data << tab; 
		print(Root->pRight); 
	}
};
class UniqueTree :public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr) this->Root = new Element(Data);
		if (Root == nullptr) return; //условие выхода из рекурсии
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr) Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data>Root->Data)
		{
			if (Root->pRight == nullptr) Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		return insert(Data, Root);
	}
}; 
//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "Russia"); 
#ifdef BASE_CHECK
	int n;
	cout << "Enter a number of elements\t"; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	//tree.clear(); 
	cout << endl;
	cout << "Minimal significance: " << tree.minValue() << endl;
	cout << "Max significance: " << tree.maxValue() << endl;
	cout << "Num of elements in the Tree: " << tree.Count() << endl;
	cout << "Sum of elements in the Tree: " << tree.Sum() << endl;
	cout << "Avarage of elements in the Tree: " << tree.Avg() << endl;
	cout << "Depth of the Tree: " << tree.Depth() << endl;

	UniqueTree unique_tree;
	for (int i = 0; i < n; i++)
	{
		unique_tree.insert(rand() % 100);
	}
	unique_tree.print();
	//unique_tree.clear(); 
	cout << "Minimal significance: " << unique_tree.minValue() << endl;
	cout << "Max significance: " << unique_tree.maxValue() << endl;
	cout << "Num of elements in the Tree: " << unique_tree.Count() << endl;
	cout << "Sum of elements in the Tree: " << unique_tree.Sum() << endl;
	cout << "Avarage of elements in the Tree: " << unique_tree.Avg() << endl;
	cout << "Depth of the Tree: " << unique_tree.Depth() << endl;
#endif // BASE_CHECK
	Tree my_tree = { 50, 25, 75, 16,32, 58,85, 48, 49, 64, 91 }; 
	my_tree.print(); 
	cout << "Minimal significance: " <<		       my_tree.minValue() << endl;
	cout << "Max significance: " <<			       my_tree.maxValue() << endl;
	cout << "Num of elements in the Tree: " <<     my_tree.Count() << endl;
	cout << "Sum of elements in the Tree: " <<     my_tree.Sum() << endl;
	cout << "Avarage of elements in the Tree: " << my_tree.Avg() << endl;
	cout << "Depth of the Tree: " <<			   my_tree.Depth() << endl;
	int value; 
	cout << "Enter the significance of erasible element: "; cin >> value; 
	my_tree.erase(value); 
	my_tree.print(); 
}