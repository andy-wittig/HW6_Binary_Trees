#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

#include "LinkedBTree.h"
#include "LinkedBSearchTree.h"

//Tree Simulation
ofstream b_tree_file;
void binaryTreeSimulation(LinkedBTree<int>&, LinkedBSearchTree<int>&);

//Interface Functions
void generateRandVect(vector<int>& vect, int rand_range, int vect_height, TreeInterface<int>&);
void addToTree(TreeInterface<int>&);
void removeFromTree(TreeInterface<int>&);
void containedInTree(TreeInterface<int>&);
void rootOfTree(TreeInterface<int>&);
void heightOfTree(TreeInterface<int>&);
void clearTree(TreeInterface<int>&);
void isEmptyTree(TreeInterface<int>&);

//Overloaded Functions
void inorderOfTree(LinkedBTree<int>&);
void preorderOfTree(LinkedBTree<int>&);
void postorderOfTree(LinkedBTree<int>&);
void inorderOfTree(LinkedBSearchTree<int>&);
void preorderOfTree(LinkedBSearchTree<int>&);
void postorderOfTree(LinkedBSearchTree<int>&);

int getSubChoice();

int main()
{
	srand(time(NULL)); //initalize random number seed

	LinkedBTree<int> binary_tree;
	LinkedBSearchTree<int> binary_search_tree;

	int menu_choice;
	do
	{
		cout << "\nBinary Trees Main Menu:" << endl;
		cout << "0. Exit." << endl;
		cout << "1. Generate Simulation File." << endl;
		cout << "2. Binary Tree." << endl;
		cout << "3. Binary Search Tree." << endl;

		cin >> menu_choice;

		{
			switch (menu_choice)
			{
			case 0:
				break;
			case 1:
				binaryTreeSimulation(binary_tree, binary_search_tree);
				break;
			case 2:
				cout << "Binary Tree Menu:" << endl;
				int sub_choice_1;
				do
				{
					sub_choice_1 = getSubChoice();

					switch (sub_choice_1)
					{
					case 0:
						break;
					case 1:
						addToTree(binary_tree);
						break;
					case 2:
						removeFromTree(binary_tree);
						break;
					case 3:
						containedInTree(binary_tree);
						break;
					case 4:
						inorderOfTree(binary_tree);
						break;
					case 5:
						preorderOfTree(binary_tree);
						break;
					case 6:
						postorderOfTree(binary_tree);
						break;
					case 7:
						rootOfTree(binary_tree);
						break;
					case 8:
						heightOfTree(binary_tree);
						break;
					case 9:
						clearTree(binary_tree);
						break;
					case 10:
						isEmptyTree(binary_tree);
						break;
					default:
						cout << endl << "Invalid option!" << endl;
						break;
					}
				} while (sub_choice_1 != 0);
				break;
			case 3:
				cout << "Binary Search Tree Menu:" << endl;
				int sub_choice_2;
				do
				{
					sub_choice_2 = getSubChoice();

					switch (sub_choice_2)
					{
					case 0:
						break;
					case 1:
						addToTree(binary_search_tree);
						break;
					case 2:
						removeFromTree(binary_search_tree);
						break;
					case 3:
						containedInTree(binary_search_tree);
						break;
					case 4:
						inorderOfTree(binary_search_tree);
						break;
					case 5:
						preorderOfTree(binary_search_tree);
						break;
					case 6:
						postorderOfTree(binary_search_tree);
						break;
					case 7:
						rootOfTree(binary_search_tree);
						break;
					case 8:
						heightOfTree(binary_search_tree);
						break;
					case 9:
						clearTree(binary_search_tree);
						break;
					case 10:
						isEmptyTree(binary_search_tree);
						break;
					default:
						cout << endl << "Invalid option!" << endl;
						break;
					}
				} while (sub_choice_2 != 0);
				break;
			default:
				cout << endl << "Invalid option!" << endl;
				break;
			}
		}
	} while (menu_choice != 0);
	return 0;
}

int getSubChoice()
{
	int userChoice;

	cout << "\n0. Back to main menu." << endl;
	cout << "1. Add value to the tree." << endl;
	cout << "2. Remove value from the tree." << endl;
	cout << "3. Check if value is contained in the tree." << endl;
	cout << "4. Inorder of the tree." << endl;
	cout << "5. Preorder of the tree" << endl;
	cout << "6. Post order of the tree." << endl;
	cout << "7. Root of the tree." << endl;
	cout << "8. Height of the tree." << endl;
	cout << "9. Clear the tree." << endl;
	cout << "10. Check if the tree is empty." << endl;

	cin >> userChoice;
	return userChoice;
}

void generateRandVect(vector<int>& vect, int rand_range, int vect_height, TreeInterface<int>& tree)
{
	vect.clear();

	while (vect.size() < vect_height)
	{
		int rand_num = rand() % rand_range + 1;

		if (find(vect.begin(), vect.end(), rand_num) == vect.end()) //ensures all random values are unique
		{
			vect.push_back(rand_num);
		}
	}

	//Add vectors to tree and display
	cout << "Generated numbers:" << endl;
	for (int i = 0; i < vect.size(); i++)
	{
		cout << vect[i] << " ";
		tree.add(vect[i]);
	}
	cout << endl;
}

void file_write(int num) //display helper
{
	b_tree_file << num << " ";
}

void binaryTreeSimulation(LinkedBTree<int>& b_tree, LinkedBSearchTree<int>& b_search_tree)
{
	vector<int> rand_vect_1;
	vector<int> rand_vect_2;
	generateRandVect(rand_vect_1, 200, 100, b_tree);
	generateRandVect(rand_vect_2, 200, 100, b_search_tree);

	cout << "Generated a file for the tree simulation." << endl;

	b_tree_file.open("Binary Tree Simulaion.txt");

	//Binary Tree
	b_tree_file << "Binary Tree:\n";
	b_tree_file << "Using the randomly generated data the height of the tree is: " << b_tree.getHeight() << ".\n";
	b_tree_file << "Inorder of the tree: ";
	b_tree.inorder(file_write);
	b_tree_file << "\n";
	b_tree_file << "Preorder of the tree: ";
	b_tree.preorder(file_write);
	b_tree_file << "\n";
	b_tree_file << "Postorder of the tree: ";
	b_tree.postorder(file_write);
	b_tree.clear();

	//Binary Search Tree
	b_tree_file << "\nBinary Search Tree:\n";
	b_tree_file << "Using the randomly generated data the height of the tree is: " << b_search_tree.getHeight() << ".\n";
	b_tree_file << "Inorder of the tree: ";
	b_search_tree.inorder(file_write);
	b_tree_file << "\n";
	b_tree_file << "Preorder of the tree: ";
	b_search_tree.preorder(file_write);
	b_tree_file << "\n";
	b_tree_file << "Postorder of the tree: ";
	b_search_tree.postorder(file_write);
	b_search_tree.clear();

	b_tree_file.close();
}

void addToTree(TreeInterface<int>& tree)
{
	cout << "What value would you like to add to the tree?:" << endl;
	int input_val;
	cin >> input_val;
	tree.add(input_val);
}

void removeFromTree(TreeInterface<int>& tree)
{
	cout << "What value would you like to remove from the tree?:" << endl;
	int input_val;
	cin >> input_val;
	bool itemFound = tree.remove(input_val);
	if (itemFound) { cout << "Item was removed!" << endl; }
	else { cout << "Item could not be removed since it does not exist!" << endl; }
}

void containedInTree(TreeInterface<int>& tree)
{
	cout << "What value are you searching for?:" << endl;
	int search_val;
	cin >> search_val;
	bool itemFound = tree.contains(search_val);
	if (itemFound) { cout << "Item was found!" << endl; }
	else { cout << "Item was not found!" << endl; }
}

void rootOfTree(TreeInterface<int>& tree)
{
	try
	{
		if (!tree.isEmpty())
		{
			cout << "The root of the tree is: " << tree.getRootData() << endl;
		}
		else { throw exception(); }
	}
	catch (const exception& e)
	{
		cout << "The tree is empty and there is no root!" << endl;
	}
}
void heightOfTree(TreeInterface<int>& tree)
{
	cout << "The height of the tree is: " << tree.getHeight() << endl;
}


void clearTree(TreeInterface<int>& tree)
{
	cout << "Clearing the tree!" << endl;
	tree.clear();
}

void isEmptyTree(TreeInterface<int>& tree)
{
	if (tree.isEmpty()) { cout << "Nofin' left in the tree!" << endl; }
	else { cout << "There is still data in the tree!"; }
}

//Overloaded Functions
void display(int num) //display helper
{
	cout << num << " ";
}

void inorderOfTree(LinkedBTree<int>& tree)
{
	if (!tree.isEmpty())
	{
		cout << "Binary Tree Inorder:" << endl;
		tree.inorder(display);
	}
	else { cout << "Sorry, but since the tree was chopped, there is no order!" << endl; }
}
void preorderOfTree(LinkedBTree<int>& tree)
{
	if (!tree.isEmpty())
	{
		cout << "Binary Tree Preorder:" << endl;
		tree.preorder(display);
	}
	else { cout << "Sorry, but since the tree was chopped, there is no order!" << endl; }
}
void postorderOfTree(LinkedBTree<int>& tree)
{
	if (!tree.isEmpty())
	{
		cout << "Binary Tree Postorder:" << endl;
		tree.postorder(display);
	}
	else { cout << "Sorry, but since the tree was chopped, there is no order!" << endl; }
}

void inorderOfTree(LinkedBSearchTree<int>& tree)
{
	if (!tree.isEmpty())
	{
		cout << "Binary Tree Inorder:" << endl;
		tree.inorder(display);
	}
	else { cout << "Sorry, but since the tree was chopped, there is no order!" << endl; }
}
void preorderOfTree(LinkedBSearchTree<int>& tree)
{
	if (!tree.isEmpty())
	{
		cout << "Binary Tree Preorder:" << endl;
		tree.preorder(display);
	}
	else { cout << "Sorry, but since the tree was chopped, there is no order!" << endl; }
}
void postorderOfTree(LinkedBSearchTree<int>& tree)
{
	if (!tree.isEmpty())
	{
		cout << "Binary Tree Postorder:" << endl;
		tree.postorder(display);
	}
	else { cout << "Sorry, but since the tree was chopped, there is no order!" << endl; }
}

/*
Binary Search Tree (inherits) --> Binary Tree (implements) --> Tree Interface
Height - Longest path from the root to the leaves + 1 (count nodes for height)
Subtree - Node dependent, its left and right branches all the way to the bottom (children).
Leaf - No children, and no sub-trees
The height of the left and right subtree of every node will differ by at most 1.
In order for a tree to be balanced the |height of the left - the height of the right| must be <= 1.
Removing a node will not remove a sub-tree just itself
Time complexity of log(n)
*/