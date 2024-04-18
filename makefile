binary_tree: main.o 
	g++ main.o -o binary_tree

main.o: main.cpp LinkedBTreeNode.h LinkedBTree.h LinkedBSearchTree.h
	g++ -c main.cpp

clean:
	rm *.o binary_tree