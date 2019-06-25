#pragma once


template<typename T>

class RBTree
{
public:

	RBTree(Node<T>* node)
		:root{ node } {}
	~RBTree() = default;

public:

	bool  	find(const T& node)const;
	void    insert(const T& data);
//	void	remove(const T& node);


	void	PrintInorder()const;
	void	PrintPreorder()const;
	void	PrintPostorder()const;


private:
	enum Color{Red,Black};

private:
	
	struct Node
	{
		T data;
		bool color;
		Node* left, * right, * parent;

		Node(int data)
		{
			this->data = data;
			left = right = parent = nullptrptr;
		}

	};



	static Node* find(const Node* node, const T& elem);
	Node* insert(Node* node, Node* elem);
//	Node* remove(Node*& node, const T& elem);


	void	PrintPreorder(Node* node)const;
	void	PrintInorder(Node* node)const;
	void  	PrintPostorder(Node* node)const;


//	void makeEmptyNode(Node* node);


	Node* RightRotate(Node* &node, Node* &elem);
	Node* LeftRotate(Node* &node, Node*& elem);


	void fixViolation(Node*& root, Node*& node);


private:
	Node* root;

};


////////////////////////////////



template<typename T>
inline bool RBTree<T>::find(const T& node) const
{
	if (nullptr == root)
	{
		return false;
	}

	return find(root, node);
}

template<typename T>
inline void RBTree<T>::insert(const T& data)
{
	Node* node = new Node(data);
	root = insert(root, node);
	fixViolation(root, node);
}

template<typename T>
inline void RBTree<T>::PrintInorder() const
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
inline void RBTree<T>::PrintPreorder() const
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
inline void RBTree<T>::PrintPostorder() const
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
inline RBTree<T>::Node* RBTree<T>::find(const Node* node, const T& elem)
{
	if (node == nullptr || node->data == elem)
		return node;

	if (node->data < elem)
		return find(node->right, data);

	return find(root->left, data);	
}




template<typename T>
inline RBTree<T>::Node* RBTree<T>::insert(Node* node, Node *elem)
{
	if (node == nullptr)
		return elem;

	if (elem->data < node->data)
	{
		node->left = insert(node->left, elem);
		node->left->parent = node;
	}

	else if (elem->data > node->data)
	{
		node->right = insert(node->right, elem);
		node->right->parent = node;
	}

	return node;
}

template<typename T>
inline void RBTree<T>::PrintPreorder(Node* node) const
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
inline void RBTree<T>::PrintInorder(Node* node) const
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
inline void RBTree<T>::PrintPostorder(Node* node) const
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


template<typename T>
inline RBTree<T>::Node* RBTree<T>::RightRotate(Node*& node, Node*& elem)
{
	
	Node* elem_left = elem->left;
	elem->left = elem_left->right;

	if (elem->left != nullptr)
		elem->left->parent = elem;

	elem_left->parent = elem->parent;

	if (elem->parent == nullptr)
		root = elem_left;

	else if (elem == elem->parent->left)
		elem->parent->left = elem_left;

	else
		elem->parent->right = elem_left;

	elem_left->right = elem;
	elem->parent = elem_left;



}

template<typename T>
inline RBTree<T>::Node* RBTree<T>::LeftRotate(Node*& node, Node*& elem)
{
	Node* elem_right = elem->right;
	elem->right = elem_right->left;

	if (elem->right != nullptr)
		elem->right->parent = elem;

	elem_right->parent = elem->parent;

	if (elem->parent == nullptr)
		root = elem_right;

	else if (elem == elem->parent->left)
		elem->parent->left = elem_right;

	else
		elem->parent->right = elem_right;

	elem_right->left = elem;
	elem->parent = elem_right;

}

template<typename T>
inline void RBTree<T>::fixViolation(Node*& root, Node*& node)
{

	Node* node_parent = nullptr;
	Node* node_grand_parent = nullptr;


	while ((node != root) && (node->color != Black)
		&& (node->parent->color == Red))
	{

		node_parent = node->parent;
		node_grand_parent = node->parent->parent;


		
		if (node_parent == node_grand_parent->left)
		{

			Node* node_uncle = node_grand_parent->right;

			if (node_uncle != nullptr && node_uncle->color = Red)
			{
				node_grand_parent->color = Red;
				node_parent->color = Black;
				node_uncle->color = Black;
				node = node_grand_parent;
			}

			else

			{
				if (node == node_parent->right)
				{
					LeftRotate(root, node_parent);
					node = node_parent;
					node_parent = node->parent;
				}


				RightRotate(root, node_grand_parent);
				swap(node_parent->color, node_grand_parent->color);
				node = node_parent;
			}
		}


		else
		{
			Node* node_uncle = node_grand_parent->left;

			if ((node_uncle != nullptr) && (node_uncle->color == Red))
			{
				node_grand_parent->color = Red;
				node_parent->color = Black;
				node_uncle->color = Black;
				node = node_grand_parent;
			}

			else

			{
				if (node == node_parent->right)
				{
					RightRotate(root, node_parent);
					node = node_parent;
					node_parent = node->parent;
				}


				LeftRotate(root, node_grand_parent);
				swap(node_parent->color, node_grand_parent->color);
				node = node_parent;
			}
		}
	}

	root->color = Black;
}
