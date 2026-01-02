#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"
using namespace std;

template <typename T>
class BSTree {
	private:
		int nelem;
		BSNode<T>* root;

		BSNode<T>* search(BSNode<T>* n, T e) const {
			if(n == nullptr){
				throw runtime_error("Element not found!!!");
			}else if(n->elem < e){
				return search(n->right, e);
			}else if(n->elem > e){
				return search(n->left, e);
			}else{
				return n;
			}
		}

		BSNode<T>* insert(BSNode<T>* n, T e) {
			if(n == nullptr){
				nelem++;
				return new BSNode<T>(e);
			}else if(n->elem == e){
				throw runtime_error("Duplicated Element");
			}else if(n->elem < e){
				n->right = insert(n->right, e);
			}else{
				n->left = insert(n->left, e);
			}
			return n;
		}

		void print_inorden(ostream& out, BSNode<T>* n) const {
			if(n == nullptr) return;
			print_inorden(out, n->left);
			out << n->elem << " ";
			print_inorden(out, n->right);
		}

		T max(BSNode<T>* n) const {
			if(n == nullptr){
				throw runtime_error("Element not found!!!");
			}
			if(n->right != nullptr){
				return max(n->right);
			}
			return n->elem;
		}

		BSNode<T>* remove_max(BSNode<T>* n){
			if(n == nullptr){
				return nullptr;
			}

			if(n->right == nullptr){
				BSNode<T>* left_sub = n->left;
				delete n;
				nelem--;
				return left_sub;
			}else{
				n->right = remove_max(n->right);
				return n;
			}
		}

		BSNode<T>* remove(BSNode<T>* n, T e){
			if(n == nullptr){
				throw runtime_error("Element not found!!!");
			}else if(n->elem < e){
				n->right = remove(n->right, e);
			}else if(n->elem > e){
				n->left = remove(n->left, e);
			}else{
				if(n->left != nullptr && n->right != nullptr){
				T m = max(n->left);
				n->elem = m;
				n->left = remove_max(n->left);
				}else{
					BSNode<T>* child = (n->left != nullptr) ? n->left : n->right;
					delete n;
					nelem--;
					return child;
				}
			}
			return n;
		}

		void delete_cascade(BSNode<T>* n){
			if(n == nullptr){
				return;
			}
			delete_cascade(n->left);
			delete_cascade(n->right);
			delete n;
		}

	public:
		BSTree() : nelem(0), root(nullptr) {}

		int size() const {
			return nelem;
		}

		T search(T e) const {
			BSNode<T>* found = search(root, e);
			return found->elem;
		}

		T operator[](T e) const {
			return seach(e);
		}

		void insert(T e) {
			root = insert(root, e);
		}

		void remove(T e) {
			root = remove(root, e);
		}

		~BSTree() {
			delete_cascade(root);
			root = nullptr;
			nelem = 0;
		}

		friend ostream& operator<<(ostream &out, const BSTree<T>& bst){
			bst.print_inorden(out, bst.root);
			return out;
		}
};

#endif
