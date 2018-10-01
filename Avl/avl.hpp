//© Copyright 2018 Marcos Oliveira
/*Essa implementação tem como base o algoritmo
do geeksforgeeks para AVLS,no entando programado
com orientação à objeto e com template adicionado*/
#include <bits/stdc++.h>
enum class order{preorder,inorder,posorder};

template<class T>
struct node{
	T val;
	int rank;
	node<T> * right;
	node<T> * left;
};

template<class T>
class avl{
private:
	node<T> * root;

	node<T> * new_node(T value);

	node<T> * insert_real(node<T> * no,T value);
	node<T> * remove_real(node<T> * no,T value);
	node<T> * remove_min(node<T> * no);

	node<T> * right_rotate(node<T> * no);
	node<T> * left_rotate(node<T> * no);

	void preOrder(node<T> * no);
	void inOrder(node<T> * no);
	void posOrder(node<T> * no);

	bool search_real(node<T> * no, T value);

	bool empty_real(node<T> * no);

	int get_height(node<T> * no);
	int get_balance(node<T> * no);
public:

	avl();
	avl(T value);
	~avl();

	void show(order o);
	void insert(T value);
	bool search(T value);
	void remove(T value);
	bool empty(void);
};

template<class T>
avl<T>::avl(){

	this->root = nullptr;
}
template<class T>
avl<T>::avl(T value){

	this->root = new_node(value);
}

template<class T>
avl<T>::~avl(){
	while(!this->empty()){
		this->root=remove_real(this->root,this->root->val);
	}
}

template<class T>
bool avl<T>::empty_real(node<T> * no){
	if(no == nullptr){
		return true;
	}else{
		return false;
	}
}

template<class T>
bool avl<T>::empty(void){

	return empty_real(this->root);
}

template<class T>
void avl<T>::preOrder(node<T> * no){
	if(no == nullptr){
		return;
	}else{ 
       	std::cout << no->val <<" "; 
        preOrder(no->left); 
        preOrder(no->right); 
    } 
}

template<class T>
void avl<T>::inOrder(node<T> * no){
	if(no == nullptr){
		return;
	}else{ 
        preOrder(no->left); 
       	std::cout << no->val << " "; 
        preOrder(no->right); 
    } 
}

template<class T>
void avl<T>::posOrder(node<T> * no){
	if(no == nullptr){
		return;
	}else{ 
        preOrder(no->left); 
        preOrder(no->right); 
       	std::cout << no->val << " "; 
    } 
}

template<class T>
int avl<T>::get_height(node<T> * no){
	if(no == nullptr){
		return 0;
	}else{
		return no->rank;
	}
}

template<class T>
int avl<T>::get_balance(node<T> * no){
	if(no == nullptr){
		return 0;
	}else{
		return (get_height(no->left) - get_height(no->right));
	}
}

template<class T>
node<T> * avl<T>::left_rotate(node<T> *no){
	node<T> * no_dir = no->right;
	node<T> * no_sub_es = no_dir->left;

	no_dir->left = no;
	no->right = no_sub_es;

	no->rank = std::max(get_height(no->left),get_height(no->right))+1;
	no_dir->rank = std::max(get_height(no_dir->left),get_height(no_dir->right))+1;

	return no_dir;
}

template<class T>
node<T> * avl<T>::right_rotate(node<T> * no){
	node<T> * no_es = no->left;
	node<T> * no_sub_dir = no_es->right;

	no_es->right = no;
	no->left = no_sub_dir;

	no->rank = std::max(get_height(no->left),get_height(no->right))+1;
	no_es->rank = std::max(get_height(no_es->left),get_height(no_es->right))+1;

	return no_es;
}

template<class T>
node<T> * avl<T>::insert_real(node<T> * no,T value){
	if(no == nullptr){
		return new_node(value);
	}else if(value < no->val){
		no->left = insert_real(no->left,value);
	}else if(value > no->val){
		no->right = insert_real(no->right,value);
	}else{
		return no;
	}

	no->rank = std::max(get_height(no->left),get_height(no->right))+1;

	int bf = get_balance(no);

	if (bf > 1 && value < no->left->val){
        return right_rotate(no); 		
	} 

    if (bf < -1 && value > no->right->val){
        return left_rotate(no);     	
    } 

    if (bf > 1 && value > no->left->val){ 
        no->left =  left_rotate(no->left); 
        return right_rotate(no); 
    } 
  
    if (bf < -1 && value < no->right->val){ 
        no->right = right_rotate(no->right); 
        return left_rotate(no); 
    } 
  
    return no; 
}

template<class T>
node<T> * avl<T>::remove_min(node<T> * no){
	node<T> * cur = no;

	while(cur->left != nullptr){
		cur = cur->left;
	}

	return cur;
}

template<class T>
node<T> * avl<T>::remove_real(node<T> * no,T value){

	if(no == nullptr){
		return no;
	}else if(value < no->val){
		no->left = remove_real(no->left,value);
	}else if(value > no->val){
		no->right = remove_real(no->right,value);
	}else{
		if(no->left == nullptr && no->right == nullptr){
			node<T> * temp = no;
			no = nullptr;

			delete temp;
		}else if(no->left == nullptr){
			node<T> * temp = no->right;

			*no = *temp;

			delete temp;
		}else if(no->right == nullptr){
			node<T> * temp = no->left;

			*no = *temp;

			delete temp;
		}else{
			node<T> * temp = remove_min(no->right);

			no->val = temp->val;

			no->right = remove_real(no->right,temp->val);
		}
	}


	if(no == nullptr){
		return no;
	}

	no->rank = std::max(get_height(no->left),get_height(no->right))+1;

	int bf = get_balance(no);

	if (bf > 1 && get_balance(no->left) >= 0){
        return right_rotate(no); 		
	} 

    if (bf > 1 && get_balance(no->left) < 0){ 
        no->left = left_rotate(no->left); 
        return right_rotate(no); 
    } 
  
    if (bf < -1 && get_balance(no->right) <= 0){
        return left_rotate(no);     	
    } 

    if (bf < -1 && get_balance(no->right) > 0){ 
        no->right = right_rotate(no->right); 
        return left_rotate(no); 
    } 
  
    return no; 
}

template<class T>
bool avl<T>::search_real(node<T> * no , T value){
	if(no == nullptr){
		return false;
	}else if(no->val == value){
		return true;
	}else if(no->val < value){
		return search_real(no->right,value);
	}else{
		return search_real(no->left,value);	
	}
}

template<class T>
bool avl<T>::search(T value){

	return search_real(this->root,value);
}

template<class T>
void avl<T>::insert(T value){

	this->root = insert_real(this->root,value);
}

template<class T>
node<T> * avl<T>::new_node(T value){
	node<T> * n = new node<T>;
	n->val = value;
	n->rank = 1;
	n->left = nullptr;
	n->right = nullptr;

	return n;
}

template<class T>
void avl<T>::show(order o){
	if(o == order::preorder){
		this->preOrder(this->root);
		std::cout << std::endl;
	}else if(o == order::inorder){
		this->inOrder(this->root);
		std::cout << std::endl;
	}else if(o == order::posorder){
		this->posOrder(this->root);
		std::cout << std::endl;
	}
}

template<class T>
void avl<T>::remove(T value){

	this->root = remove_real(this->root,value);
}
