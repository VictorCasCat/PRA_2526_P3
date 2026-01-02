#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"
#include "../PRA_2526_P1/ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {
	private:
		int n;
		int max;

		ListLinked<TableEntry<V>>** table;

		int h(std::string key){
			int sum = 0;
			for(int i = 0; i< (int)key.size(); i++){
				sum += int(key.at(i));
			}
			return sum % max;
		}
		int find_in_bucket(int bucket, const std::string &key){
			TableEntry<V> target(key);
			for(int i = 0; i < table[bucket]->size(); i++){
				if(table[bucket]->get(i) == target){
					return i;
				}
			}
			return -1;
		}

	public:
		HashTable(int size) : n(0), max(size){
			if(size <= 0){
				throw std::invalid_argument("Tamaño de la tabla no valido!!");
			}
			table = new ListLinked<TableEntry<V>>*[max];

			for(int i = 0; i < max; i++){
				table[i] = new ListLinked<TableEntry<V>>();
			}
		}

		~HashTable() override{
			for (int i = 0; i < max; i++){
				delete table[i];
			}
			delete[] table;
		}

		void insert(std::string key, V value) override{
			int bucket = h(key);

			if(find_in_bucket(bucket, key) != -1){
				throw std::runtime_error("La key ya existe!!!");
			}

			table[bucket]->prepend(TableEntry<V>(key, value));
			n++;
		}

		V search(std::string key) override{
			int bucket = h(key);
			int pos = find_in_bucket(bucket, key);

			if(pos == -1){
				throw std::runtime_error("Key No encontrada!!");
			}
			return table[bucket]->get(pos).value;
		}

		V remove (std::string key) override{
			int bucket = h(key);
			int pos = find_in_bucket(bucket, key);

			if(pos == -1){
				throw std::runtime_error("Key no encontrada!!!");
			}

			TableEntry<V> removed = table[bucket]->remove(pos);
			n--;
			return removed.value;
		}

		int entries() override{
			return n;
		}

		int capacity(){
			return max;
		}

		V operator[](std::string key){
			return search(key);
		}

		friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &ht){
			out << "HashTable [entries: " << ht.n << ", capacity: " << ht.max << "]" << std::endl;
			out << "===================== " << std::endl;

			for(int i = 0; i < ht.max; i++){
				out << "Cubeta: " << i << std::endl;
				out << *(ht.table[i]) << std::endl;
			}

			out << "====================" << std::endl;

			return out;
		}
};

#endif
