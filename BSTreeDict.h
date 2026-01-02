#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"
using namespace std;

template <typename V >
class BSTreeDict : public Dict<V> {
	private:
		BSTree<TableEntry<V>>* tree;

	public:
		BSTreeDict(){
			tree = new BSTree<TableEntry<V>>();
		}
		~BSTreeDict() override {
			delete tree;
		}

		void insert(string key, V value) override {
			tree->insert(TableEntry<V>(key, value));
		}

		V search(string key) override {
			TableEntry<V> found = tree->search(TableEntry<V>(key));
			return found.value;
		}

		V remove(string key) override {
			TableEntry<V> found = tree->search(TableEntry<V>(key));
			tree->remove(TableEntry<V>(key));
			return found.value;
		}

		int entries() override {
			return tree->size();
		}

		V operator[](string key){
			return search(key);
		}

		friend ostream& operator<<(ostream &out, const BSTreeDict<V> & bd){
			out << *(bd.tree);
			return out;
		}
};

#endif
