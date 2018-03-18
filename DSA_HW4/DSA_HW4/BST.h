#ifndef _BST_HEADER_INCLUDED_
#define _BST_HEADER_INCLUDED_

//a BST which supports duplicate keys

#include "Vector.h"
#include "String.h"

#include <iostream>
#include <algorithm>

template <class KeyType, class DataType>
class BST
{
public:
	//big four
	BST() 
		: m_root(nullptr)
		, m_size(0) 
		, m_pairsCnt(0)
	{}

	~BST() { clear(m_root); }
	
	BST(const BST& rhs)
		: m_root(copy(rhs.m_root))
		, m_size(rhs.m_size) 
		, m_pairsCnt(rhs.m_pairsCnt)
	{}

	BST& operator=(const BST& rhs)
	{
		if (this != &rhs)
		{
			clear(m_root);
			m_root = copy(rhs.m_root);
			m_size = rhs.m_size;
			m_pairsCnt = rhs.m_pairsCnt;
		}

		return *this;
	}

	//public methods
	void insert(const KeyType& key, const DataType& data) { insert(m_root, key, data); }
	bool find(const KeyType& key, const DataType& data) const { return find(m_root, key, data); }
	bool remove(const KeyType& key, const DataType& data) { return remove(m_root, key, data); }
	size_t removeAll(const KeyType& key) 
	{ 
		size_t cnt = 0;
		removeAll(m_root, key, cnt);
		
		return cnt; //how many entries have been removed
	}
	
	//a function which balance the tree by weight:
	//there's already a constructed BST; convert it to sorted vector
	//change each node's left and right pointers to nullptr
	//then pass this vector to another method which do the balacing trick
	void balance()
	{
		Vector<Node*> sortedKeys;
		treeToSortedArray(m_root, sortedKeys);
		
		manipulateArray(sortedKeys);

		int left = 0;
		Node* newRoot = nullptr;
		
		sortedArrayToBST(newRoot, sortedKeys, left, (int)m_size - 1);
		
		m_root = newRoot;
	}

	size_t getSize() const { return m_size; }
	size_t getHeight() const { return (size_t)height(m_root); }

	bool isBalanced() const { return balanced(m_root); }
	bool isPerfectlyBalanced() const { return perfectBalanced(m_root); }

	void printInorder() const { print(m_root); std::cout << "\n"; }

private:
	struct Node
	{
		Node(const KeyType& key, Node* left = nullptr, Node* right = nullptr)
			: m_key(key)
			, m_left(left)
			, m_right(right)
		{}

		//this ctor has been used in BST's copy function
		Node(const KeyType& key, const Vector<DataType>& data, Node* left = nullptr, Node* right = nullptr)
			: m_key(key)
			, m_data(data)
			, m_left(left)
			, m_right(right)
		{}

		KeyType m_key;
		Vector<DataType> m_data; //this way the bst supports entries with duplicate keys
		Node* m_left;
		Node* m_right;
	} *m_root;

	size_t m_size; //unique keys count
	size_t m_pairsCnt; //all pairs count

private:
	Node* copy(Node* root)
	{
		return root ? new Node(root->m_key, rhs->m_data, copy(root->m_left), copy(root->m_right))
			    : root;
	}

	void clear(Node*& root)
	{
		if (root)
		{
			clear(root->m_left);
			clear(root->m_right);
			delete root;
		}
	}

	void insert(Node*& root, const KeyType& key, const DataType& data)
	{
		if (!root)
		{
			root = new Node(key);
			root->m_data.push_back(data);
			
			++m_size;
			++m_pairsCnt;
			
			return;
		}

		//if the tree has already contained this key
		//just push back the new data
		if (root->m_key == key)
		{
			root->m_data.push_back(data);
			++m_pairsCnt;

			return;
		}

		(key < root->m_key) ? insert(root->m_left, key, data)
				    : insert(root->m_right, key, data);
	}

	bool find(const Node* root, const KeyType& key, const DataType& data) const
	{
		if (!root) return false;

		if (root->m_key == key)
		{
			return (root->m_data.contains(data)) ? true 
				                             : false;
		}

		return (key < root->m_key) ? find(root->m_left, key, data)
			                   : find(root->m_right, key, data);
	}

	bool remove(Node*& root, const KeyType& key, const DataType& data)
	{
		if (!root) return false;
		if (root->m_key == key)
		{
			//cover the case where the tree contains duplicate keys
			if (root->m_data.getSize() > 1)
			{
				for (size_t i = 0; i < root->m_data.getSize(); ++i)
				{
					if (root->m_data[i] == data)
					{
						root->m_data.remove(i);
						--m_pairsCnt;
						return true;
					}
				}

				return false;
			}
			
			//if the curr node's vector contains only one data
			else if (root->m_data[0] == data)
			{
				removeHelper(root);
				--m_size;
				--m_pairsCnt;
				
				return true;
			}

			else
			{
				return false;
			}
		}

		return (key < root->m_key) ? remove(root->m_left, key, data)
		                  	   : remove(root->m_right, key, data);
	}

	void removeAll(Node*& root, const KeyType& key, size_t& cnt)
	{
		if (!root) return;

		if (root->m_key == key)
		{
			cnt = root->m_data.getSize();
			removeHelper(root);
			--m_size;
			m_pairsCnt -= cnt;
		}
		else
		{
			(key < root->m_key) ? removeAll(root->m_left, key, cnt)
				            : removeAll(root->m_right, key, cnt);
		}
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

	void treeToSortedArray(Node* root, Vector<Node*>& sortedKeys)
	{
		if(root->m_left) treeToSortedArray(root->m_left, sortedKeys);

		sortedKeys.push_back(root);

		if (root->m_right) treeToSortedArray(root->m_right, sortedKeys);
	}

	void manipulateArray(Vector<Node*>& sortedKeys)
	{
		for (size_t i = 0; i < sortedKeys.getSize(); ++i)
		{
			sortedKeys.getAt(i)->m_left = sortedKeys.getAt(i)->m_right = nullptr;
		}
	}

	void sortedArrayToBST(Node*& root, const Vector<Node*>& sortedKeys, int left, int right)
	{
		if (sortedKeys.getSize() == 0)
			return;

		if (left > right)
			return;

		int mid = left + (right - left) / 2; //avoiding a potential overflow problem
		
		root = sortedKeys.getAt(mid);
		
		sortedArrayToBST(root->m_left, sortedKeys, left, mid - 1);
		sortedArrayToBST(root->m_right, sortedKeys, mid + 1, right);
	}

	int height(const Node* root) const
	{
		if (!root) return 0;
		return 1 + std::max(height(root->m_left), height(root->m_right));
	}

	bool balanced(const Node* root) const
	{
		if (!root) return true;
		return abs(height(root->m_left) - height(root->m_right)) < 2 &&
			   balanced(root->m_left) && balanced(root->m_right);
	}


	bool perfectBalanced(const Node* root) const
	{
		if (!root) return true;
		return labs(weight(root->m_left) - weight(root->m_right)) < 2 &&
			   perfectBalanced(root->m_left) && perfectBalanced(root->m_right);
	}

	size_t weight(const Node* root) const
	{
		if (!root) return 0;
		return 1 + weight(root->m_left) + weight(root->m_right);
	}


	void print(const Node* root) const
	{
		if (root)
		{
			print(root->m_left);
			
			//(key, data), (key, data), ...
			for (size_t i = 0; i < root->m_data.getSize(); ++i)
			{
				std::cout << "(" << root->m_key << ", " << root->m_data[i] << ") ";
			}
			
			print(root->m_right);
		}
	}
};

#endif // !_BST_HEADER_INCLUDED_
