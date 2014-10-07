//an item in the list
struct ListNode {
	int _value;
	ListNode * _next;
};

class List {
public:
	//Head of list
	ListNode * _head;
	ListNode *newNode(int val);
	void link(ListNode *node);
	void unlink(ListNode *node);
	void insertSorted(int val);
	void init(int val);
	bool isEmpty();
	int compare(int a, int b);
	void append (int val);
	void prepend (int val);  
	int lookup(int val);
	int remove(int val);
	void print();
	List();
	~List();
};


