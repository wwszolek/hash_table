#ifndef LIST_H
#define LIST_H

template<class K,class V>
struct node {
	node<K,V>* next;
	K key;
	V value;

};

template<class K,class V>
class list {
	class iterator {
		node<K,V>* p;

	public:
		iterator(node<K,V>*);
		iterator& operator++();
		iterator operator++(int);
		bool operator==(const iterator& other)const;
		bool operator!=(const iterator& other)const;

		node<K,V>*& operator*();
		node<K,V>* operator->();
	};
public:
	iterator begin();
	iterator end();
	
public:
	node<K,V>* _head;
	node<K,V>* _T;

public:
	list();
	~list();
	list(const list<K,V>&);
	list<K,V>& operator=(const list<K,V>&);

	void insertHead(const K&, const V&);
	//void insertSorted(const K&, const V&);
	void delHead();

	void delVal(const K&);

	iterator search(const K&);

	void queue(const K&, const V&);
	V top();

	bool isempty();
	int len();
	
	void replaceAfter(iterator);
	void bubbleSort();

	void show();
};

#include "list.tpp"
#endif