//an item in the list
struct URLRecordListNode {
	int _value;
	URLRecordListNode * _next;
};

class URLRecordList {
public:
	//Head of list
	URLRecordListNode * _head;
	URLRecordListNode *newNode(int val);
	void link(URLRecordListNode *node);
	void unlink(URLRecordListNode *node);
	void insertSorted(int val);
	void init(int val);
	bool isEmpty();
	int compare(int a, int b);
	void append (int val);
	void prepend (int val);  
	int lookup(int val);
	int remove(int val);
	void print();
	URLRecordList();
	~URLRecordList();
};


