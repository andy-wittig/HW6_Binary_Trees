#ifndef LINKED_BTREE_NODE
#define LINKED_BTREE_NODE

template<class ItemType>
class LinkedBTreeNode 
{
private:
	ItemType item;
	LinkedBTreeNode<ItemType>* leftChildPtr;
	LinkedBTreeNode<ItemType>* rightChildPtr;
public:
	//Constructors
	LinkedBTreeNode()
	{
		leftChildPtr = nullptr;
		rightChildPtr = nullptr;
	}
	LinkedBTreeNode(const ItemType& newData)
	{
		item = newData;
		leftChildPtr = nullptr;
		rightChildPtr = nullptr;
	}

	LinkedBTreeNode(const ItemType& newData, LinkedBTreeNode<ItemType>* left, LinkedBTreeNode<ItemType>* right)
	{
		item = newData;
		leftChildPtr = left;
		rightChildPtr = right;
	}

	//Setters
	void setItem(const ItemType& newData)
	{
		item = newData;
	}

	void setLeftChildPtr(LinkedBTreeNode<ItemType>* newLeftChildPtr)
	{
		leftChildPtr = newLeftChildPtr;
	}

	void setRightChildPtr(LinkedBTreeNode<ItemType>* newRightChildPtr)
	{
		rightChildPtr = newRightChildPtr;
	}

	//Getters
	ItemType getItem() const
	{
		return item;
	}

	bool isLeaf() const
	{
		return leftChildPtr == nullptr && rightChildPtr == nullptr;
	}

	LinkedBTreeNode<ItemType>* getLeftChildPtr() const
	{
		return leftChildPtr;
	}

	LinkedBTreeNode<ItemType>* getRightChildPtr() const
	{
		return rightChildPtr;
	}
};
#endif
