#ifdef LIST_H

#include <iostream>

template<class K,class V>
using iterator = typename list<K,V>::iterator;

template <class K, class V>
list<K,V>::iterator::iterator(node<K,V>* p) :p(p) {}

template <class K, class V>
typename list<K,V>::iterator& list<K,V>::iterator::operator++() {
	p = p->next;
	return *this;
}

template <class K, class V>
typename list<K,V>::iterator list<K,V>::iterator::operator++(int) {
	iterator tmp = *this;
	++*this;
	return tmp;
}

template <class K, class V>
bool list<K,V>::iterator::operator==(const iterator& other)const {
	return p == other.p;
}

template <class K, class V>
bool list<K,V>::iterator::operator!=(const iterator& other)const {
	return p != other.p;
}

template <class K, class V>
node<K,V>*& list<K,V>::iterator::operator*() {
	return p;
}

template <class K, class V>
node<K,V>* list<K,V>::iterator::operator->() {
	return p;
}

template <class K, class V>
typename list<K,V>::iterator list<K,V>::begin() {
	return list<K,V>::iterator(_head);
}

template <class K, class V>
typename list<K,V>::iterator list<K,V>::end() {
	return list<K,V>::iterator(NULL);
}

template <class K, class V>
list<K,V>::list(): _head(NULL), _T(NULL){}

template <class K, class V>
list<K,V>::~list() {
	while (_head)
		delHead();
}

template <class K, class V>
list<K,V>::list(const list<K,V>& other): list(){
	node<K,V>* p = other._head;
	while (p) {
		this->queue(p->key, p->value);
		p = p->next;
	}
}

template <class K, class V>
list<K,V>& list<K,V>::operator=(const list<K,V>& other) {
	node<K,V>* p = other._head;
	while (p) {
		this->queue(p->key,p->value);
		p = p->next;
	}

	return *this;
}

template <class K, class V>
void list<K,V>::insertHead(const K& key, const V& value) {
	node<K, V>* p = new node<K, V>;
	p->key = key;
	p->value = value;
	p->next = _head;
	if (!_head)
		_T = p;
	_head = p;
}

//template <class K, class V>
//void list<K,V>::insertSorted(const K& key, const V& value) {
//	node<K,V>* p = new node<K,V>;
//	p->key = key;
//	p->value = value;
//
//	insertHead(key, value);
//	node<K,V>*k = _head;
//	
//	while (k != _T) {
//		if (k->next != T || k->next->key > p->key) {
//			p->next = k->next;
//			k->next = p;
//			break;
//		}
//		k = k->next;
//	}
//
//	delHead();
//}

template <class K, class V>
void list<K,V>::delHead() {
	if (_head) {
		node<K,V>*p = _head;
		_head = _head->next;
		delete p;

		if (!_head)
			_T = NULL;
	}
}


template <class K, class V>
void list<K,V>::delVal(const K& key) {
	if (_head) {
		insertHead(_head->key, _head->value);
		node<K,V>*p = _head;
		while (p->next) {
			if (p->next->key == key) {
				auto k = p->next;
				p->next = k->next;
				delete k;

				if (!_head)
					_T = NULL;
				break;
			}
			else {
				p = p->next;
			}
		}
	}
}

template <class K, class V>
typename list<K,V>::iterator list<K,V>::search(const K& key) {
	auto it = begin();
	while (it != end()) {
		if (it->key == key)
			return it;
		it++;
	}
	return it;
}

template <class K, class V>
void list<K,V>::show() {
	auto it = begin();
	while (it != end()) {
		std::cout << "(" << it->key << ": " << it->value << ")->";
		it++;
	}
	std::cout << "||";
}

template <class K, class V>
void list<K,V>::queue(const K& key, const V& value) {
	node<K, V>* p = new node<K, V>;
	p->key = key;
	p->value = value;
	p->next = NULL;
	_T->next = p;
	_T = p;
}

template <class K, class V>
V list<K,V>::top() {
	if (_head) {
		return _head->value;
	}
	else return V();
}

template <class K, class V>
bool list<K,V>::isempty() {
	return _head == NULL;
}

template <class K, class V>
int list<K,V>::len() {
	int length = 0;
	auto it = begin();
	while (it != end()) {
		it++;
		length++;
	}
	return length;
}

template <class K, class V>
void list<K,V>::replaceAfter(iterator p) {
	if (p!=end()&&p->next&&p->next->next) {
		auto*k = p->next;
		p->next = k->next;
		k->next = p->next->next;
		p->next->next = k;
	}
}

template <class K, class V>
void list<K,V>::bubbleSort(){
	if (!isempty()) {
		bool Done = false;
		insertHead(_head->key, _head->value);
		while (!Done) {
			Done = true;
			auto *p = _head;
			while (p&&p->next&&p->next->next) {
				if (p->next->key > p->next->next->key) {
					replaceAfter(p);
					Done = false;
				}
				p = p->next;
			}
		}
		delHead();
	}
}


#endif