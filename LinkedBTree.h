#ifndef LINKED_BINARY_TREE
#define LINKED_BINARY_TREE

#include "TreeInterface.h"
#include "LinkedBTreeNode.h"

template<class ItemType>
class LinkedBTree : public TreeInterface<ItemType> {
private:
	LinkedBTreeNode<ItemType>* rootPtr;
public:
	//Constructor
	LinkedBTree() : rootPtr(nullptr) { }

	//Getter Functions
	bool isEmpty() const
	{
		return rootPtr == nullptr;
	}
	
	int getHeight() const
	{
		return getHeightHelper(rootPtr);
	}
	
	int getNumberOfNodes() const
	{
		return getNumberOfNodesHelper(rootPtr);
	}
	
	ItemType getRootData() const
	{
		if (!isEmpty())
		{
			return rootPtr->getItem();
		}
	}

	//Functions
	bool add(const ItemType& newData)
	{
		LinkedBTreeNode<ItemType>* newPtr = new LinkedBTreeNode<ItemType>(newData);
		rootPtr = balancedAdd(rootPtr, newPtr); 
		return true;
	}
	
	bool remove(const ItemType& data)
	{
		bool isSuccesful = false;
		rootPtr = removeValue(rootPtr, data, isSuccesful);
		return isSuccesful;
	}
	
	bool contains(const ItemType& anEntry) const
	{
		bool isSuccesful = false;
		findNode(rootPtr, anEntry, isSuccesful);
		return isSuccesful;
	}
	
	void clear()
	{
		destroyTree(rootPtr);
		rootPtr = nullptr; //resets tree to default status
	}

	//Traversal Functions
	void inorder(void visit(ItemType))
	{
		inorderHelper(rootPtr, visit);
	}
	void preorder(void visit(ItemType))
	{
		preorderHelper(rootPtr, visit);
	}
	void postorder(void visit(ItemType))
	{
		postorderHelper(rootPtr, visit);
	}

	//Destructor
	~LinkedBTree() { }
protected:
	//Helper Functions
	int getHeightHelper(LinkedBTreeNode<ItemType>* subTreePtr) const
	{
		if (subTreePtr == nullptr)
		{
			return 0;
		}
		else
		{
			//recursively adds left and right elements of the entire tree + 1 to include the current node.
			return 1 + max(getHeightHelper(subTreePtr->getLeftChildPtr()), getHeightHelper(subTreePtr->getRightChildPtr()));
		}
	}
	
	int getNumberOfNodesHelper(LinkedBTreeNode<ItemType>* subTreePtr) const
	{
		if (subTreePtr == nullptr)
		{
			return 0;
		}
		else
		{
			return 1 + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr()) + getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
		}
	}
	
	LinkedBTreeNode<ItemType>* balancedAdd(LinkedBTreeNode<ItemType>* subTreePtr, LinkedBTreeNode<ItemType>* newNodePtr)
	{
		if (subTreePtr == nullptr)
		{
			return newNodePtr;
		}
		else
		{
			LinkedBTreeNode<ItemType>* leftPtr = subTreePtr->getLeftChildPtr();
			LinkedBTreeNode<ItemType>* rightPtr = subTreePtr->getRightChildPtr();
			if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr))
			{
				rightPtr = balancedAdd(rightPtr, newNodePtr);
				subTreePtr->setRightChildPtr(rightPtr);
			}
			else
			{
				leftPtr = balancedAdd(leftPtr, newNodePtr);
				subTreePtr->setLeftChildPtr(leftPtr);
			}
			return subTreePtr;
		}
	}
	
	LinkedBTreeNode<ItemType>* removeValue(LinkedBTreeNode<ItemType>* subTreePtr, const ItemType target, bool& isSuccessful)
	{
		if (subTreePtr == nullptr) //value to delete not contained in tree
		{
			isSuccessful = false;
			return nullptr; 
		}
		else if (subTreePtr->getItem() == target) //target has been found to be removed
		{
			isSuccessful = true;

			//Leaf or single child
			if (subTreePtr->getLeftChildPtr() == nullptr) //Child is on the right
			{
				LinkedBTreeNode<ItemType>* ptrToDelete = subTreePtr->getRightChildPtr();
				delete subTreePtr;
				return ptrToDelete;
			}
			else if (subTreePtr->getRightChildPtr() == nullptr) //Child is on left
			{
				LinkedBTreeNode<ItemType>* ptrToDelete = subTreePtr->getLeftChildPtr();
				delete subTreePtr;
				return ptrToDelete;
			}
			else if (subTreePtr->getLeftChildPtr() != nullptr && subTreePtr->getRightChildPtr() != nullptr) //Two children
			{
				LinkedBTreeNode<ItemType>* deepest_entry = deepestNode(rootPtr, nullptr, 1);
				subTreePtr->setItem(deepest_entry->getItem());
				delete deepest_entry;
				return subTreePtr;
			}
		}
		else //Recursion
		{
			subTreePtr->setLeftChildPtr(removeValue(subTreePtr->getLeftChildPtr(), target, isSuccessful));
			if (!isSuccessful)
			{
				subTreePtr->setRightChildPtr(removeValue(subTreePtr->getRightChildPtr(), target, isSuccessful));
			}
			return subTreePtr;
		}
	}
	
	LinkedBTreeNode<ItemType>* deepestNode(LinkedBTreeNode<ItemType>* subTreePtr, LinkedBTreeNode<ItemType>* parentPtr, int currentLevel)
	{
		if (subTreePtr != nullptr)
		{
			if (currentLevel == getHeightHelper(rootPtr)) //reached max height
			{
				if (parentPtr->getLeftChildPtr() == subTreePtr) //unlink deepest node from parent node
				{
					parentPtr->setLeftChildPtr(nullptr);
				} 
				else 
				{ 
					parentPtr->setRightChildPtr(nullptr); 
				}
				return subTreePtr;
			}
			parentPtr = subTreePtr;
			deepestNode(subTreePtr->getLeftChildPtr(), parentPtr, currentLevel++);
			deepestNode(subTreePtr->getRightChildPtr(), parentPtr, currentLevel++);
		}
	}
	
	LinkedBTreeNode<ItemType>* findNode(LinkedBTreeNode<ItemType>* subTreePtr, const ItemType& target, bool& isSuccessful) const
	{
		if (subTreePtr == nullptr) 
		{ 
			isSuccessful = false;
			return nullptr; 
		}
		else if (subTreePtr->getItem() == target)
		{ 
			isSuccessful = true; 
			return subTreePtr;
		}
		else
		{
			LinkedBTreeNode<ItemType>* resultPtr = nullptr;
			resultPtr = findNode(subTreePtr->getLeftChildPtr(), target, isSuccessful);
			if (resultPtr == nullptr) { resultPtr = findNode(subTreePtr->getRightChildPtr(), target, isSuccessful); } //value was not found in left tree so search right
			return resultPtr;
		}
	}
	
	void destroyTree(LinkedBTreeNode<ItemType>* subTreePtr)
	{
		if (subTreePtr == nullptr) { return; } //tree is already cleared
		//annihilate left and right trees!
		destroyTree(subTreePtr->getLeftChildPtr());
		destroyTree(subTreePtr->getRightChildPtr());
		//deallocate current node
		delete subTreePtr;
	}

	//Traversal Helpers
	void preorderHelper(LinkedBTreeNode<ItemType>* subTreePtr, void visit(ItemType))
	{
		if (subTreePtr == nullptr) { return; } //ends traversal of current subtree
		visit(subTreePtr->getItem()); //visit operation
		preorderHelper(subTreePtr->getLeftChildPtr(), visit); //traverse entire left subtree of current node
		preorderHelper(subTreePtr->getRightChildPtr(), visit); //traverse entire right subtree of current node
	}
	void inorderHelper(LinkedBTreeNode<ItemType>* subTreePtr, void visit(ItemType))
	{
		if (!subTreePtr) { return; }
		inorderHelper(subTreePtr->getLeftChildPtr(), visit);
		visit(subTreePtr->getItem());
		inorderHelper(subTreePtr->getRightChildPtr(), visit);
	}
	void postorderHelper(LinkedBTreeNode<ItemType>* subTreePtr, void visit(ItemType))
	{
		if (subTreePtr == nullptr) { return; }
		postorderHelper(subTreePtr->getLeftChildPtr(), visit);
		postorderHelper(subTreePtr->getRightChildPtr(), visit);
		visit(subTreePtr->getItem());
	}
};
#endif