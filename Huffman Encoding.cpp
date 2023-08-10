#include <iostream>
#include <string>
#include<fstream>
#include<vector>
using namespace std;

//Queue Class
template <typename T>
class Queue
{

public:
	class node
	{
		T  data;
		int  freq;
		node* next;
		node(T d, node* p)
		{
			freq = 1;
			data = d;
			next = p;
		}
		friend class Queue<T>;
	};

	class Queueiterator
	{
	protected:
		node* current;
		friend class Queue<T>;
	public:
		//Default Constructor
		Queueiterator()
		{
			current = nullptr;
		}
		//Parameterized Constructor used in begin and end functions
		Queueiterator(node* p)
		{
			current = p;
		}
		//Dereference operation to provide access of data to user
		T& operator* () const
		{
			return current->data;
		}
		//Move forward Pre-increment
		Queueiterator& operator++ ()
		{
			if (current != nullptr)
				this->current = this->current->next;
			return *this;
		}
		//Move forward Post-increment
		Queueiterator operator++ (int)
		{
			Queueiterator old = *this;
			++(*this);
			return old;
		}
		//If two iterators point to same node
		bool operator== (const Queueiterator& rhs) const { return current == rhs.current; }
		//If two iterators point to different nodes
		bool operator!= (const Queueiterator& rhs) const { return !(*this == rhs); }
	};
	//Iterator returned that points to First Node 
	Queueiterator begin()
	{
		return front;
	}
	//Iterator returned that points to Last Node  
	Queueiterator end()
	{
		return nullptr;
	}

	//Other Functions of Link Queue
	void  printQueue();
	void  Enqueue(T value);
	void Dequeue();
	void Dequeue(pair<int, char>& temp);
	bool isFull();
	bool isEmpty();
	bool search(T element)
	{
		node* curr = front;
		while (curr)
		{
			if (element == curr->data)
			{
				curr->freq=curr->freq+1;
				return true;
			}
			curr = curr->next;
		}
		return false;
	}
	Queue() { front = nullptr; rear = nullptr; }
	~Queue();
private:
	node* front;
	node* rear;
};
template <typename T>
bool Queue<T>::isFull()
{
	return false;
}
template <typename T>
bool Queue<T>::isEmpty()
{
	if (front == nullptr)
		return true;
	else
		return false;
}
//Dequeue from front
template <typename T>
void Queue<T>::Dequeue()
{
	node* curr = front;
	front = front->next;
	delete curr;
}
template <typename T>
void Queue<T>::Dequeue(pair<int,char>& temp)
{
	temp.first = front->freq;
	temp.second = front->data;
	node* curr = front;
	front = front->next;
	delete curr;
}
//Enqueue node at rear
template <typename T>
void Queue<T>::Enqueue(T value)
{
	node* nnode = new node(value, nullptr);
	if (front == NULL)
	{
		front = nnode;
		rear = nnode;
	}
	else
	{
		rear->next = nnode;
		rear = nnode;
	}
}
//Destructor
template <typename T>
Queue<T>::~Queue()
{
	node* temp;
	while (front != nullptr)
	{
		temp = front;
		front = front->next;
		delete temp;
	}

}
//print Queue
template <typename T>
void Queue<T>::printQueue()
{
	node* current;
	current = front;
	while (current != nullptr)
	{
		cout << current->data <<", "<<current->freq<< " -> ";
		current = current->next;
	}
	cout << "NULL" << endl;
}

//Node Class
template <typename T>
class Node
{
public:
	T data;
	Node* right;
	Node* left;

	Node()
	{
		right = left = nullptr;
	}
	Node(T d)
	{
		data = d;
		right = left = nullptr;
	}
	void displayNode(Node<pair<int,char>> *curr)
	{
		if (curr == nullptr)
			return;
		else
		{
			displayNode(curr->left);
			cout << curr->data.first << ", "<<curr->data.second<<" -> ";
			displayNode(curr->right);
		}
	}
	void displayleafNode(Node<pair<int, char>>* curr)
	{
		if (curr->left == nullptr && curr->right == nullptr)
		{
			cout << curr->data.first << ", " << curr->data.second << " -> ";
			return;
		}
		else
		{
			displayleafNode(curr->left);
			displayleafNode(curr->right);
		}
	}
	void insert(Node<pair<int, char>>temp,bool flag)
	{
		Node<pair<int, char>>* curr = new Node<pair<int, char>>;
		curr->data = temp.data;
		curr->left = temp.left;
		curr->right = temp.right;
		if (!flag)
			left = curr;
		else
			right = curr;

	}
};

//Heap resizing function
template<typename L>
void GrowByTen(L*& arr, int& size)
{
	L* temp = arr;
	arr = new L[size + 10];
	for (int i = 0; i < size; i++)
		arr[i] = temp[i];
	delete temp;
	size += 10;
}

//Heap Class
template<typename T>
class Heap {
	T* heap;
	int heapsize;
	int maxsize;

public:
	Heap()
	{
		maxsize = 10;
		heapsize = 1;
		heap = new T[maxsize];
	}
	void Update(T data)
	{
		if (heapsize == maxsize)
			GrowByTen(heap, maxsize);
		int i = heapsize;
		heap[heapsize] = data;
		heapsize++;
		while (i > 1 && heap[i].data.first < heap[i / 2].data.first)
		{
			swap(heap[i], heap[i / 2]);
			i = i / 2;
		}
	}
	void ExtractMin(T& min)
	{
		min = heap[1];
		heap[1] = heap[--heapsize];
		Heapify(1);
	}
	void Heapify(int i)
	{
		int smallest = i;
		if (2 * i < heapsize && heap[smallest].data.first > heap[2 * i].data.first)
			smallest = 2 * i;
		if ((2 * i + 1) < heapsize && heap[smallest].data.first > heap[2 * i + 1].data.first)
			smallest = 2 * i + 1;
		if (i != smallest)
		{
			swap(heap[i], heap[smallest]);
			Heapify(smallest);
		}
	}
	void SwapValue(T value1, T value2)
	{
		int i = 0;
		for (; i < maxsize; i++)
			if (heap[i] == value1)
				break;
		if (i < maxsize)
		{
			heap[i] = value2;
			if (value1 < value2)
				Heapify(i);
			else if (value1 > value2)
				while (i > 1 && heap[i] < heap[i / 2])
				{
					swap(heap[i], heap[i / 2]);
					i = i / 2;
				}
		}
	}
	void DeleteKey(T value)
	{
		Swap(value, heap[1] - 1);
		T valueTemp = NULL;
		ExtractMin(valueTemp);
	}
	bool isEmpty()
	{
		if (heapsize == 1)
		{
			return true;
		}
		else
			return false;
	}
	void DisplayHeap()
	{
		for (int i = 1; i < heapsize; i++)
			cout << heap[i].data.first << ", "<<heap[i].data.second<<endl;
	}
	~Heap()
	{
		delete[] heap;
	}
};

//Function to fill minheap 
Node<pair<int, char>>* fillHeap(Heap <Node<pair<int, char>>>& minheap, Queue<char>& que)
{
	pair<int, char>temp;
	Node <pair<int, char>>* tmp = new Node<pair<int, char>>;
	while (!que.isEmpty())
	{
		que.Dequeue(temp);
		tmp->data = temp;
		minheap.Update(*tmp);
	}
	return tmp;
}

//Function To make huffman Tree and then return root
Node<pair<int, char>>*buildhuffmanTree(Heap<Node<pair<int, char>>>& minheap, Queue<char>& que)
{
	Node<pair<int, char>> *root=fillHeap(minheap,que);
	Node<pair<int, char>> temp1;
	Node<pair<int, char>> temp2;
	Node<pair<int, char>> temp3;
	temp3.data.second = '*';
	while (true)
	{
		minheap.ExtractMin(temp1);
		if (minheap.isEmpty())
		{
			minheap.Update(temp1);
			break;
		}
		minheap.ExtractMin(temp2);
		temp3.data.first = temp1.data.first + temp2.data.first;
		temp3.insert(temp1, 0);
		temp3.insert(temp2, 1);
		minheap.Update(temp3);
	}
	return root;
}

//Function takes data from file and puts in string
void getDatafromFile(string& str)
{
	ifstream obj;
	string name;
	string temp;
	while (true)
	{
		cout << "Enter File name: ";
		getline(cin, name);
		obj.open(name);
		if (obj.is_open())
		{
			int i = 0;
			while (!obj.eof())
			{
				getline(obj,temp);
				str += temp;
				str += '\n';
			}
			obj.close();
			break;
		}
		else
		{
			cout << "File not found\n";
		}
	}
}

//Function Encodes the string using individual codes
void Encode(Node<pair<int, char>>*curr,vector<pair<string,char>> &vec, string str,string tmp="")
{
	if (curr->left == nullptr && curr->right == nullptr)
	{
		pair<string, char> temp;
		temp.second = curr->data.second;
		temp.first = tmp;
		vec.push_back(temp);
		return;
	}
	else
	{
		tmp += "0";
		Encode(curr->left,vec,str,tmp);
		tmp[tmp.length() - 1] = '\0';
		tmp += "1";
		Encode(curr->right,vec,str,tmp);
	}
}

//Function Decodes Using the code and Huffman tree
void Decode(Node<pair<int, char>>* curr,string &data)
{
	string code;
	getDatafromFile(code);
	cout << "Code in File: " << code<<endl;
	data = "";
	Node<pair<int, char >>* temp = curr;
	for (int i = 0; i < code.length()-1; i++)
	{
		if (temp->left == nullptr && temp->right == nullptr)
		{
			data += temp->data.second;
			temp = curr;
			i--;
			continue;
		}
		else
		{
			if (code[i] == '0')
			{
				temp = temp->left;
			}
			else if (code[i] == '1')
			{
				temp = temp->right;
			}
		}
	}
	data += temp->data.second;
	cout << "Decoded text: " << data << endl;
}

//Function Takes input from Either User or File
void inputText(string& str, Queue<char>& que)
{
	int option=0;
	string name;
	ifstream obj;
	while (option != 1 && option != 2)
	{
		cout << "How to do you want to input the text?\n1) Read File\n2) Enter string\n";
		cin >> option;
		cin.ignore();
		switch(option)
		{
			case 1:
				getDatafromFile(str);
				break;
			case 2:
				cout << "Enter String: ";
				getline(cin, str);
				break;
			default:
				cout << "Invalid Option, Enter again\n";
		}
	}
	system("cls");
	cout << "Input text: " << str << endl;
	for (int i = 0; i < str.length(); i++)
	{
		if (!que.search(str[i]))
			que.Enqueue(str[i]);
	}
}

//Function Prints individual codes
void printCodes(vector<pair<string, char>> &vec)
{
	cout << "Individual codes after Encoding: " << endl;
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i].second << " = " << vec[i].first << endl;
	}
}

//Function Encodes the Whole string
void makeCode(string& code, vector<pair<string, char>> &vec,string str, Node<pair<int, char>>* curr)
{
	Encode(curr, vec, str);
	printCodes(vec);
	code = "";
	for (int i = 0; i < str.length(); i++)
	{
		for (int j = 0; j < vec.size(); j++)
		{
			if (str[i] == vec[j].second)
			{
				code += vec[j].first;
			}
		}
	}
	cout << "Encoded text: " << code << endl;
	ofstream obj2;
	obj2.open("output.txt");
	for (int i = 0; i < code.length(); i++)
	{
		if(code[i]=='1'||code[i]=='0')
			obj2 << code[i];
	}
	obj2.close();
	cout << "Code Saved in file 'output.txt'\n";
}

//Function that Either Decodes or saves code
void askDecode(Node<pair<int, char>>* curr, string code, string& data)
{
	int option = 0;
	
	while (option != 1 && option != 2)
	{
		cout << "1)Decode code from file\n2)Exit\n";
		cin >> option;
		cin.ignore();
		switch (option)
		{
		case 1:
			Decode(curr, data);
			break;
		case 2:
			break;
		default:
			cout << "Invalid Option, Enter again\n";
		}
	}
}

int main()
{
	Heap <Node<pair<int,char>>> minheap;
	Queue <char> que;
	string str;
	vector<pair<string, char>> vec;
	string code;
	int option;

	inputText(str, que);	//Takes input puts it in string and que with frequency
	Node<pair<int, char>>* root = buildhuffmanTree(minheap,que);//Makes heap and huffman tree
	minheap.ExtractMin(*root);
	makeCode(code, vec, str, root);//Encodes the text 
	askDecode(root, code, str);//Either Decodes or saves code according to users wish
	system("pause");
	return 0;
}