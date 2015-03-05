typedef struct Key {
	char *_str;
	int _index;
} Key;

typedef struct Set {
	trieNode **_a;
} Set;

typedef struct rootNode {
	Set *_set;
} rootNode;

typedef struct trieNode {
	Key *_key;
	struct trieNode *_next, *_children;
} trieNode;

class PrefixTrie {
	rootNode *_root;
	PrefixTrie();
	~PrefixTrie();
public:
	trieNode *getRoot();
	bool add(const char *str);
	bool remove(const char *str);
	bool isMember(const char *str);
	trieNode *newNode(const char *str);
};
