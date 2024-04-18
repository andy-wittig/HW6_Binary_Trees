#pragma once
#ifndef LINKED_BINARY_SEARCH_TREE
#define LINKED_BINARY_SEARCH_TREE

#include "LinkedBTree.h"

template<class ItemType>
class LinkedBSearchTree : public LinkedBTree<ItemType> {
private:
	LinkedBTreeNode<ItemType>* rootPtr;
public:
	//Constructors
	LinkedBSearchTree() : rootPtr(nullptr) { }

	//Getters
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
		rootPtr = nullptr; //reset tree
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
	~LinkedBSearchTree() { }
protected:
	//Helpers
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
		else if (newNodePtr->getItem() < subTreePtr->getItem())
		{
			LinkedBTreeNode<ItemType>* leftPtr = subTreePtr->getLeftChildPtr();
			subTreePtr->setLeftChildPtr(balancedAdd(leftPtr, newNodePtr));
		}
		else if (newNodePtr->getItem() > subTreePtr->getItem())
		{
			LinkedBTreeNode<ItemType>* rightPtr = subTreePtr->getRightChildPtr();
			subTreePtr->setRightChildPtr(balancedAdd(rightPtr, newNodePtr));
		}
		else //value matches node
		{
			return subTreePtr;
		}

		//AVL balancing
		LinkedBTreeNode<ItemType>* leftPtr = subTreePtr->getLeftChildPtr();
		LinkedBTreeNode<ItemType>* rightPtr = subTreePtr->getRightChildPtr();

		int balance = getHeightHelper(leftPtr) - getHeightHelper(rightPtr);

		if (balance > 1 && newNodePtr->getItem() < leftPtr->getItem()) //LL
		{
			return rightRotate(subTreePtr);
		}
		if (balance < -1 && newNodePtr->getItem() > rightPtr->getItem()) //RR
		{
			return leftRotate(subTreePtr);
		}
		if (balance > 1 && newNodePtr->getItem() > leftPtr->getItem()) //LR
		{
			subTreePtr->setLeftChildPtr(leftRotate(leftPtr));
			return rightRotate(subTreePtr);
		}
		if (balance < -1 && newNodePtr->getItem() < rightPtr->getItem()) //RL
		{
			subTreePtr->setRightChildPtr(rightRotate(rightPtr));
			return leftRotate(subTreePtr);
		}

		return subTreePtr;
	}
	LinkedBTreeNode<ItemType>* leftRotate(LinkedBTreeNode<ItemType>* subTreePtr)
	{
		LinkedBTreeNode<ItemType>* newRootPtr = subTreePtr->getRightChildPtr();
		LinkedBTreeNode<ItemType>* oldRootPtr = newRootPtr->getLeftChildPtr();

		newRootPtr->setLeftChildPtr(subTreePtr);
		subTreePtr->setRightChildPtr(oldRootPtr);

		return newRootPtr;
	}
	LinkedBTreeNode<ItemType>* rightRotate(LinkedBTreeNode<ItemType>* subTreePtr)
	{
		LinkedBTreeNode<ItemType>* newRootPtr = subTreePtr->getLeftChildPtr();
		LinkedBTreeNode<ItemType>* oldRootPtr = newRootPtr->getRightChildPtr();

		newRootPtr->setRightChildPtr(subTreePtr);
		subTreePtr->setLeftChildPtr(oldRootPtr);

		return newRootPtr;
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
				LinkedBTreeNode<ItemType>* parentPtr = subTreePtr;
				LinkedBTreeNode<ItemType>* minPtr = subTreePtr->getRightChildPtr();

				while (minPtr->getLeftChildPtr() != nullptr) //smallest value in left subtree of right branch
				{
					parentPtr = minPtr;
					minPtr = minPtr->getLeftChildPtr(); //advance down left subtree
				}
				subTreePtr->setItem(minPtr->getItem());

				if (parentPtr->getLeftChildPtr() == minPtr) //relink node to parent
				{
					parentPtr->setLeftChildPtr(minPtr->getRightChildPtr());
				}
				else
				{
					parentPtr->setRightChildPtr(minPtr->getRightChildPtr());
				}

				delete minPtr;
				return subTreePtr;
			}
		}
		else //Recursion
		{
			if (target < subTreePtr->getItem())
			{
				subTreePtr->setLeftChildPtr(removeValue(subTreePtr->getLeftChildPtr(), target, isSuccessful));
				return subTreePtr;
			}
			else
			{
				subTreePtr->setRightChildPtr(removeValue(subTreePtr->getRightChildPtr(), target, isSuccessful));
				return subTreePtr;
			}
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

		LinkedBTreeNode<ItemType>* resultPtr = nullptr;
		if (!isSuccessful)
		{
			resultPtr = findNode(subTreePtr->getLeftChildPtr(), target, isSuccessful);
			resultPtr = findNode(subTreePtr->getRightChildPtr(), target, isSuccessful);
		}
		return resultPtr;
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