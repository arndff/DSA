#ifndef BST_HEADER_INCLUDED__
#define BST_HEADER_INCLUDED__

template <class T>
class BST
{
public:
	BST()
		: m_root(nullptr)
		, m_size(0)
	{}

	~BST() { clear(m_root); }

	BST(const BST& rhs)
		: m_root(copy(rhs.m_root))
		, m_size(rhs.m_size)
	{}

	BST& operator=(const BST& rhs)
	{
		if (this != &rhs)
		{
			clear(m_root);
			m_root = copy(rhs.m_root);
			m_size = rhs.m_size;
		}

		return *this;
	}

	//public methods
	void insert(const T& data) { insert(m_root, data); }
	bool find(const T& data) const { return find(m_root, data); }
	void remove(const T& data) { remove(m_root, data); }

	size_t getSize() const { return m_size; }
	size_t getHeight() const { return (size_t)height(m_root); }

	void printInorder() const { print(m_root); std::cout << "\n"; }

private:
	struct Node
	{
		Node(const T& data, Node* left = nullptr, Node* right = nullptr)
			: m_data(data)
			, m_left(left)
			, m_right(right)
		{}

		T m_data;
		Node* m_left;
		Node* m_right;
	} *m_root;

	size_t m_size;

private:
	Node* copy(Node* root)
	{
		return root ? new Node(root->m_data, copy(root->m_left), copy(root->m_right))
			    : root;
	}

	void clear(Node*& root)
	{
		if (root)
		{
			clear(root->m_left);
			clear(root->m_right);
			delete root;
			root = nullptr;
		}
	}

	void insert(Node*& root, const T& data)
	{
		if (!root)
		{
			root = new Node(data);
			++m_size;

			return;
		}

		(data < root->m_data) ? insert(root->m_left, data)
				      : insert(root->m_right, data);
	}

	bool find(const Node* root, const T& data) const
	{
		if (!root) return false;

		if (root->m_data == data)
		{
			return true;
		}

		return (data < root->m_data) ? find(root->m_left, data)
			                     : find(root->m_right, data);
	}

	void remove(Node*& root, const T& data)
	{
		if (!root) return;
		if (root->m_data == data)
		{
			if (root->m_data == data)
			{
				removeHelper(root);
				--m_size;

				return;
			}

			else
			{
				return;
			}
		}

		(data < root->m_data) ? remove(root->m_left, data)
			              : remove(root->m_right, data);
	}

	void removeHelper(Node*& root)
	{
		Node* toDel = root;

		if (!root->m_left)
		{
			root = root->m_right;
		}
		else if (!root->m_right)
		{
			root = root->m_left;
		}
		else
		{
			Node* mR = extractMin(root->m_right);
			mR->m_left = root->m_left;
			mR->m_right = root->m_right;
			root = mR;
		}

		delete toDel;
	}

	Node* extractMin(Node*& root)
	{
		if (root->m_left)
			return extractMin(root->m_left);

		Node* n = root;
		root = root->m_right;
		return n;
	}

	int height(const Node* root) const
	{
		if (!root) return 0;
		return 1 + std::max(height(root->m_left), height(root->m_right));
	}

	void print(const Node* root) const
	{
		if (!root) return;

		print(root->m_left);
		std::cout << root->m_data << " ";
		print(root->m_right);
	}
};

#endif // !_BST_HEADER_INCLUDED_
