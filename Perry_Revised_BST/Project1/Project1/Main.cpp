#include <iostream>
#include<string>

using namespace std;

template <typename generic_type>
class Node //Node class
{
public:
	Node* parent;//Node pointers & data (parent,left & right)
	Node* left;
	Node* right;
	generic_type data;

	Node()//Node constructor
	{
		parent = nullptr;//nullifying pointers 
		left = nullptr;
		right = nullptr;
		data = NULL;//nullifying data
	}

	Node(generic_type init_D)
	{// passing the class constructor w/ all its data members
		data = init_D;
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	}

	Node(Node*init_P, Node*init_L, Node*init_R, generic_type init_D)
	{
		// initializing data members;
		parent = init_P;
		left = init_L;
		right = init_R;
		data = init_D;
	}
};

template <typename generic_type>
class BST//class for Binary Search Tree
{
public://creating the root & leaf pointers
	Node<generic_type>*root;
	Node<generic_type>*leaf;

	 BST() //binary tree constructor
	{		
		root = nullptr;//nullifying the pointers for the constructor
		leaf = nullptr;
	}

	 BST(BST*init_RT)//initializing root
	 {
		 root = init_RT;
		 leaf = nullptr;
	 }

	BST(BST*init_RT, BST*init_LF)
	{
		root = init_RT;
		leaf = init_LF;
	}

	Node<generic_type>* Insert( generic_type init_D)//insert function that returns a node
	{
		
		if (root == NULL)//if root is null
		{
			Node<generic_type>* current = new Node<generic_type>();//creating a new node
			current->data = init_D;//then new node will take the new data
			current->left = NULL;
			current->right = NULL;
			root = current;//root is now new node
			return current;
		}
		return Insert(root, init_D);//insert function that returns a node
	}
	Node<generic_type>* Insert(Node<generic_type>*node, generic_type init_D)//insert function that returns a node
	{
		if (node != nullptr)
		{
			if (node->data > init_D)//if root's data is more than data youre adding 
			{
				if (node->left != NULL)
				{
					Insert(node->left, init_D);//use recursive function add in node as the next left node 

				}

				else {
					Node<generic_type>* current = new Node<generic_type>();
					current->data = init_D;//then new node will take the new data
					current->left = NULL;
					current->right = NULL;
					node->left = current;
					current->parent = node;

					return current;//return node
				}
			}
			if (node->data < init_D)
				// use recursive function add in node as the next right node
			{
				if (node->right != NULL)
				{
					Insert(node->right, init_D);//use recursive function add in node as the next left node

				}
				else {
					Node<generic_type>* current = new Node<generic_type>();
					current->data = init_D;//then new node will take the new data
					current->left = NULL;
					current->right = NULL;
					node->right = current;
					current->parent = node;
					//node->right = Insert(node->right, init_D);
					return current;//return node
				}
			}
		}
			return nullptr;
		
	}
	Node<generic_type>* Find(Node<generic_type> *root, generic_type init_D)//function that finds nodes based on their data
	{
		if (root== NULL)//if root is NULL print message
		{cout << "\nThis tree is bare!" << endl;}
		
	 	else if(root->data == init_D)//if data equals root data, return root
		{return root;}
		 
	 	else if (init_D > root->data)//if data youre looking for is more than root data
		{
			Find(root->right, init_D);//recurse using find function down right subtree of root
		}
		 else if (init_D < root->data)//if data youre looking for is less than root data
		{
			Find(root->left, init_D);//recurse using find function down left subtree of root
		}
	}

	

	Node<generic_type>* Remove(Node<generic_type> *root, generic_type init_D)//function to delete nodes from tree
	{
		if (root == nullptr)//if root is null, print message
		{
			cout << "\nThis tree is bare!" << endl;
			return 0;
		}
		else if (init_D < root->data) root->left = Remove(root->left, init_D);//looking for node to delete in the correct subtree
		else if (init_D> root->data) root->right = Remove(root->right, init_D);

		else
		{
			Node<generic_type>*temp = new Node<generic_type>(init_D);//crate temporary node using data to be deleted
			temp = Find(root, init_D);//find temp node by data
			
			if (temp->left == nullptr && temp->right == nullptr)//if node has no children
			{
				if (temp->parent->left == temp)//if node is on the left side
				{
					temp->parent->left = nullptr;//node parent left now points to null
					delete temp;// delete temp node
				}
				else{//otherwise temp is on right side
					
					temp->parent->right = nullptr;//so point node's parent right to null
					delete temp;//and delete temp
				}
			}
			else if (temp->left == NULL)// if node only has a right child
			{
				root = root->right;//node is now its right child 
				delete temp;//delete old temp
			}
			else if (temp->right == NULL) //if node only has a left child
			{
				root = root->left;//node is now its left child 
				delete temp;//delete old temp
			}
			
			else if (temp->left != nullptr && temp->right != nullptr)//if node has 2 children
			{
				Node<generic_type>*successor = Max(temp);//return max node on temp's left side as a node (successor)
				temp->data = successor->data;//make temps data same as succcesor's data
				delete successor;//delete the leaf node
			}
		}
		return root;
	}

	

	Node<generic_type>* Max(Node<generic_type>*M) //function that gets largest node on the left side of a tree 
	{
		if (M == nullptr) { cout << "\nThere's no Max" << endl; }//node is null print message
		else if (M->parent->right == NULL) { return M; }//if theres nothing in the right side of parent return parent
		else { return Max(M->parent->right); }//otherwise find the max of parent's right side

		return nullptr;
	}
	void showTree(Node<generic_type>*root)//function that traverses through tree
	{
		 if (root == nullptr)//if node is null print message
		 {
			 cout << "there's nothing here" << endl;
		 }
		 else if (root != nullptr)//otherwise 
		{
			showTree(root->left);//then go down node's left side
			cout << root->data << endl;//start at node
			showTree(root->right);//then go down node's right side
		}
		
	}
};

int main()
{
	int choice;
	BST<int> BST1;


	//creating a do while loop for a menu
	do {

		cout << "\nHere's my Binary Search Tree Application. Please choose a valid option\n" << endl;
		cout << "1. Test default constructor (also ensures default constructor is empty)" << endl;
		cout << "2. Test Insert function with 1 Node" << endl;
		cout << "3. Finding different Nodes" << endl;
		cout << "4. Deleting a Node with only 1 child" << endl;
		cout << "5. Deleting a Node with 2 children" << endl;
		cout << "6. Deleting the root" << endl;
		cout << "7. Quit" << endl;
		cin >> choice;// take user input as variable

		if (choice == 1)
		{
			BST1 = BST<int>();//create empty binary tree
			Node<int>*N1 = new Node<int>(1);//create new node w/ data but dont put it into tree 
			cout << "\nNew Tree called BST1 has been created" << endl;
			cout << "A node has also been created but is not inserted within BST1" << endl;
			BST1.Remove(N1,1);//try removing node from empty tree, you should get a message
		}

		if (choice == 2)
		{
			BST1 = BST<int>();//create tree
			auto N1 = BST1.Insert(1);//insert new node into tree
			cout << "A new node has been created as root of the BST. Lets see its data!" << endl;
			cout << N1->data << endl;
		}
		if (choice == 3)//Finding a specific Node
		{
			BST1 = BST<int>();//create tree
			Node<int>*N1 = NULL;// Three new nodes created
			Node<int>*N2 = NULL;
			Node<int>*N3 = NULL;
			N1 = BST1.Insert(3);//Inserting nodes into tree
			cout << "\nInserting a node containing data of 3" << endl;
			N2 = BST1.Insert(5);
			cout << "\nInserting a node containing data of 5" << endl;
			N3 = BST1.Insert(1);
			cout << "\nInserting a node containing data of 1" << endl;
			N2 = BST1.Find(N1,5);//find node 2 (containing data value 5)
			cout << N2->data << endl;
			
		}
		if (choice == 4)// Show that function can delete nodes w/ 1 child of the tree
		{
			BST<int> BST1;//create tree
			Node<int>*N1 = NULL;// Four new nodes created
			Node<int>*N2 = NULL;
			Node<int>*N3 = NULL;
			Node<int>*N4 = NULL;
			Node<int>*N5 = NULL;
			cout << "Creating a multinode Tree....." << endl;
			N1 = BST1.Insert(3);// Insert node 1 into BST
			N2 = BST1.Insert(5);// Insert node 2 into BST
			N3 = BST1.Insert(1);// Insert node 3 into BST
			N4 = BST1.Insert(2);// Insert node 4 into BST
			N5 = BST1.Insert(4);// Insert node 5 into BST
	
			cout << "Searching for a Node and deleting it...." << endl;
			BST1.Remove(N1, 1);// Delete node 3 (containing value 1 w/ one child)
			cout << "Here's your new BST" << endl;
			cout << N1->data << "\n" << N2->data << "\n"<< N3->data << "\n" << N4->data << "\n" << N5->data << "\n" << endl;
		}
		if (choice == 5)//Deleting node w/ 2 children
		{
			BST<int> BST1;//create tree
			Node<int>*N1 = NULL;// Five new nodes created
			Node<int>*N2 = NULL;
			Node<int>*N3 = NULL;
			Node<int>*N4 = NULL;
			Node<int>*N5 = NULL;
			Node<int>*N6 = NULL;
			N1 = BST1.Insert(3);// Insert node 1 into BST
			N2 = BST1.Insert(5);// Insert node 2 into BST
			N3 = BST1.Insert(1);// Insert node 3 into BST
			N4 = BST1.Insert(2);// Insert node 4 into BST
			N5 = BST1.Insert(4);// Insert node 5 into BST
			N6 = BST1.Insert(6);// Insert node 6 into BST
			BST1.Remove(N1,5);//Remove node containing value 5 w/ 2 children)
			cout<<N1->data<<"\n"<< N2->data << N3->data << "\n" << N4->data << "\n"<< N5->data<< "\n"<< N6->data<<endl;
		}
		if (choice == 6)//removing the root
		{
			BST<int> BST1;//create tree
			Node<int>*N1 = NULL;// Four new nodes created
			Node<int>*N2 = NULL;
			Node<int>*N3 = NULL;
			Node<int>*N4 = NULL;
			N1 = BST1.Insert(3);// Insert nodes into BST
			N2 = BST1.Insert(1);
			N3 = BST1.Insert(2);
			N1 = BST1.Insert(5);
			N4 = BST1.Insert(4);
		
			//BST1.Remove(N1, 3);//Delete root
			cout << N1->data << "\n" << N2->data << N3->data << "\n" << N4->data << endl;
		}
	} while (choice != 7);
	system("pause");
	return 0;
}