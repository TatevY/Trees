#pragma once
#include<stack>

///Self Balancing Binary Search Tree



template<typename T>

class AVL
{
public:

	AVL(Node<T>*node)
		:root{ node } {}
	~AVL() = default;

	

	bool  	find(const T& node)const;
	void    insert(const T& node);
	void	remove(const T& node);


	void	PrintInorder()const;
	void	PrintPreorder()const;
	void	PrintPostorder()const;

	

private:

	struct Node
	{
		Node* left;
		Node* right;
		int height;
		T data;
	};


private:



	static Node*   find(const Node* node, const T& elem);
	Node*   insert(Node*& node, const T& elem);
	Node*	remove(Node*& node, const T& elem);


	void	PrintPreorder(Node* node)const;
	void	PrintInorder(Node* node)const;
	void  	PrintPostorder(Node* node)const;


	Node* newNode(T data);
	void makeEmptyNode(Node* node);


	Node* SingleRightRotate(Node *node);
	Node* SingleLeftRotate(Node *node);
	Node* DoubleRightRotate(Node *node);
	Node* DoubleLeftRotate(Node *node);


	int max(int a, int b);
	Node* findMixn(Node* node);
	


	int getBalace(Node* node);
	int height(Node* node);


private:
	Node * root;
};


template<typename T>
inline bool AVL<T>::find(const T& node) const
{
	if (nullptr == root)
	{
		return false;
	}

	return find(root, node);
}

template<typename T>
inline void AVL<T>::insert(const T& node)
{
	root = insert(node, root);
}

template<typename T>
inline void AVL<T>::remove(const T& node)
{
	root = remove(node, root);
}

template<typename T>
inline void AVL<T>::PrintInorder() const
{
	std::cout << "Inorder : ";

	if (nullptr == root)
	{
		return;
	}

	PrintInorder(root);

	std::cout << std::endl;
}



template<typename T>
inline void AVL<T>::PrintPreorder() const
{
	std::cout << "Preorder : ";

	if (nullptr == root)
	{
		return;
	}

	PrintPreorder(root);

	std::cout << std::endl;
}

template<typename T>
inline void AVL<T>::PrintPostorder() const
{

	std::cout << "Postorder : ";

	if (nullptr == root)
	{
		return;
	}

	PrintPostorder(root);

	std::cout << std::endl;

}



template<typename T>
inline AVL<T>::Node* AVL<T>::find(const Node * node, const T & elem)
{

	if (node == nullptr || node->data == elem)
		return node;

	if (node->data < elem)
		return find(node->right, data);

	return find(root->left, data);
	
}



template<typename T>
inline AVL<T>::Node * AVL<T>::newNode(T data)
{
	Node* node = new Node();
	node->data = data;
	node->left = nullptr;
	node->right = nullptr
	node->height = 1;

	return(node);

}



template<typename T>
inline void AVL<T>::makeEmptyNode(Node* node)
{
	if (node == nullptr)
		return;
	
	makeEmptyNode(node -> left);
	makeEmptyNode(node -> right);
	delete node;

}



//LL case
template<typename T>
inline AVL<T>::Node * AVL<T>::SingleRightRotate(Node * node)
{

	Node* util = node -> left;
	Node* Subtree = util -> right;

	util->right = node;
	node->left = Subtree;

	node->height = max(height(node->left), height(node->right)) + 1;
	util->height = max(height(util->left), height(util->right)) + 1;

	return util;

}


//RR case
template<typename T>
inline AVL<T>::Node * AVL<T>::SingleLeftRotate(Node * node)//z
{

	Node* util = node->right; //y
	Node* Subtree = util->left; //t2

	util->left = node;
	node->right = Subtree;

	node->height = max(height(node->left), height(node->right)) + 1;
	util->height = max(height(util->left), height(util->right)) + 1;

	return util;

}



//RL case
template<typename T>
inline AVL<T>::Node * AVL<T>::DoubleRightRotate(Node * node)
{
	node->left = SingleRightRotate(node->left);
	return SingleLeftRotate(node);

}



//LR case
template<typename T>
inline AVL<T>::Node * AVL<T>::DoubleLeftRotate(Node * node)
{
	node->left = SingleLeftRotate(node->left);
	return SingleRightRotate(node);
}



template<typename T>
inline int AVL<T>::max(int a, int b)
{
	return(a > b) ? a : b;
}

template<typename T>
inline AVL<T>::Node* AVL<T>::findMixn(Node* node)
{
	
	if (node == NULL)
		return NULL;
	else if (node->left == NULL)
		return t;
	else
		return findMin(node->left);

}



template<typename T>
inline int AVL<T>::getBalace(Node * node)
{
	
	if (node == nullptr)
		return 0;

	return height(node->left) - height(node->right);
}



template<typename T>
inline int AVL<T>::height(Node * node)
{
	if (node = nullptr)
		return 0;
	return node->height;
}



template<typename T>
inline AVL<T>::Node * AVL<T>::insert(Node *& node, const T & elem)
{
	
	if (node == nulptr)
		return (newNode(data));

	else if (elem < node->data)
	{
		node->left = insert(node - left, elem);
		if (height(node->left) - height(node->right) == 2)
		{
			if (elem < node->left->data)
				node = SingleRightRotate(node);
			else
				node = DoubleRightRotate(node);
		}

	}


	else if (elem >= node->data)
	{
		node->right = insert(node, elem);
		if (height(node->right) - height(node->left) == 2)
		{
			if (elem >= node->right->data)
				node = SingleLeftRotate(node);
			else
				node = DoubleLeftRotate(node);
		}
	}

	node->height = max(height(node->left), height(node->right)) + 1;
	return node;

}

template<typename T>
inline AVL<T>::Node* AVL<T>::remove(Node *& node, const T & elem)
{
	
	Node* temp;

	if (t == NULL)
		return NULL;

	else if (x < t->data)
		t->left = remove(x, t->left);
	else if (x > t->data)
		t->right = remove(x, t->right);


	else if (t->left && t->right)
	{
		temp = findMin(t->right);
		t->data = temp->data;
		t->right = remove(t->data, t->right);
	}
	

	else
	{
		temp = t;
		if (t->left == NULL)
			t = t->right;
		else if (t->right == NULL)
			t = t->left;
		delete temp;
	}
	if (t == NULL)
		return t;

	t->height = max(height(t->left), height(t->right)) + 1;



	if (height(t->left) - height(t->right) == 2)
	{
		if (height(t->left->left) - height(t->left->right) == 1)
			return singleLeftRotate(t);

		else
			return doubleLeftRotate(t);
	}




	else if (height(t->right) - height(t->left) == 2)
	{
	
		if (height(t->right->right) - height(t->right->left) == 1)
			return singleRightRotate(t);
		
		else
			return doubleRightRotate(t);
	}
	return t;

}

template<typename T>
inline void AVL<T>::PrintPreorder(Node* node) const
{
	std::cout << node->data << " ";

	if (node->left != nullptr)
	{
		pre_order(node->left);
	}

	if (node->right != nullptr)
	{
		pre_order(node->right);
	}
}

template<typename T>
inline void AVL<T>::PrintInorder(Node* node) const
{
	if (node->left != nullptr)
	{
		in_order(node->left);
	}

	std::cout << node->data << " ";

	if (node->right != nullptr)
	{
		in_order(node->right);
	}

}

template<typename T>
inline void AVL<T>::PrintPostorder(Node* node) const
{

	if (node->left != nullptr)
	{
		post_order(node->left);
	}

	if (node->right != nullptr)
	{
		post_order(node->right);
	}

	std::cout << node->data << " ";

}
