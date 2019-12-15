#ifdef HASH_H

#include <iostream>

template <int M>
int hmod(int x) {
	return x % M;
}

template <int M>
int linear(int x, int i) {
	return (x + i) % M;
}

template <int M, int C1, int C2>
int quadratic(int x, int i) {
	return (x + C1 * i + C2 * i*i) % M;
}

template <class K, class V, int N>
chain_tab<K, V, N>::chain_tab(int(*calc)(const K&), int(*hash)(int))
	: hash(hash), calc(calc) {
	_list = new list<K, V>[N];
}

template <class K, class V, int N>
chain_tab<K, V, N>::chain_tab(const chain_tab<K, V, N>& other) {
	_list = new list<K, V>[N];
	for (int i = 0; i < N; i++)
		_list[i] = other._list[i];

	calc = other.calc;
	hash = other.hash;
}

template <class K, class V, int N>
chain_tab<K, V, N>::~chain_tab() {
	if (_list)
		delete[] _list;
}

template <class K, class V, int N>
void chain_tab<K, V, N>::add(const K& key, const V& value) {
	int i = hash(calc(key));

	_list[i].insertHead(key, value);
}

template <class K, class V, int N>
V chain_tab<K, V, N>::search(const K& key) {
	int i = hash(calc(key));

	auto p = _list[i].search(key);
	if (p == _list[i].end()) {
		return V();
	}
	else {
		return p->value;
	}
}

template <class K, class V, int N>
void chain_tab<K, V, N>::del(const K& key) {
	int i = hash(int_from_str(key));

	_list[i].delVal(key);
}

template <class K, class V, int N>
void chain_tab<K, V, N>::show() {
	for (int i = 0; i < N; i++) {
		std::cout << i << "->";
		_list[i].show();
		std::cout << std::endl;
	}
}


template <class K, class V, int N>
open_address_tab<K, V, N>::open_address_tab(int(*calc)(const K&), int(*hash)(int), int(*probe)(int,int))
	: calc(calc), hash(hash), probe(probe), fill(0){
	_tab = new pair[N];
	deleted = new bool[N];
	for (int i = 0; i < N; i++) {
		deleted[i] = false;
	}
}

template <class K, class V, int N>
open_address_tab<K, V, N>::open_address_tab(const open_address_tab<K, V, N>& other) {
	fill = other.fill;
	_tab = new pair[N];
	deleted = new bool[N];
	for (int i = 0; i < N; i++) {
		_tab[i] = other._tab[i];
		deleted[i] = other.deleted[i];
	}
}

template <class K, class V, int N>
open_address_tab<K, V, N>::~open_address_tab() {
	delete[] deleted;
	delete[] _tab;
}

template <class K, class V, int N>
bool open_address_tab<K, V, N>::add(const K& key, const V& value) {
	int start = hash(calc(key));
	for (int j = 0, i = start; j < N; j++) {
		if (_tab[i].key == key) {
			return false;
		}
		else if (deleted[i] || _tab[i].key != K()) {
			i = probe(start, j);
		}
		else {
			_tab[i].key = key;
			_tab[i].value = value;
			fill++;
			return true;
		}
	}
	if (fill == N)
		std::cout << "NEED REHASHING" << std::endl;
}

template <class K, class V, int N>
V open_address_tab<K, V, N>::search(const K& key) {
	int start = hash(calc(key));
	for (int j = 0, i = start; j < N; j++) {
		if (_tab[i].key == key && !deleted[i]) {
			return _tab[i].value;
		}
		else if (_tab[i].key != K()) {
			i = probe(start, j);
		}
		else {
			return V();
		}
	}
}

template <class K, class V, int N>
void open_address_tab<K, V, N>::del(const K& key) {
	int start = hash(calc(key));
	for (int j = 0, i = start; j < N; j++) {
		if (_tab[i].key == key) {
			deleted[i] = true;
			break;
		}
		else if (deleted[i] || _tab[i].key != K()) {
			i = probe(start, j);
		}
	}
}

template <class K, class V, int N>
void open_address_tab<K, V, N>::show() {
	for (int i = 0; i < N; i++) {
		if (deleted[i]) {
			std::cout << "(DEL) ";
		}
		else {
			if (_tab[i].key == K())
				std::cout << "() ";
			else
				std::cout << "(" << _tab[i].key << ": " << _tab[i].value << ") ";
		}
	}
	std::cout << std::endl;
}

//bool open_address_tab::add(const std::string& key, int value) {
//	int start = hash(int_from_str(key));
//	for (int j = 0, int i = start; j < _size; j++) {
//		if (_keys[i] == k) {
//			return false;
//		}
//		if (_keys[i] == "") {
//			_keys[i] = key;
//			_values[i] = value;
//			return true;
//		}
//		else {
//			i = probe(start, j);
//		}
//	};
//
//	return false;
//}
//
//bool open_address_tab::is_in(const std::string& key) {
//	int start = hash(int_from_str(key));
//	for (int j = 0, int i = start; j < _size; j++) {
//		if (_keys[i] == key) {
//			return true;
//		}
//		if (_keys[i] == "" && !deleted[i]) {
//			return false;
//		}
//		else {
//			i = probe(start, j);
//		}
//	}
//	return false;
//}
//
//void open_address_tab::del(const std::string& key) {
//	int start = hash(int_from_str(key));
//	for (int j = 0, int i = start; j < _size; j++) {
//		if (_keys[i] == key) {
//			_keys[i] = "";
//			deleted[i] = true;
//			break;
//		}
//		if (_keys[i] == "" && !deleted[i]) {
//			break;
//		}
//		else {
//			i = probe(start, j);
//		}
//	}
//}
//
//int open_address_tab::get_value(const std::string& key) {
//	int start = hash(int_from_str(key));
//	for (int j = 0, int i = start; j < _size; j++) {
//		if (_keys[i] == key) {
//			return _values[i];
//		}
//		if (_keys[i] == "" && !deleted[i]) {
//			return -1;
//		}
//		else {
//			i = probe(start, j);
//		}
//	}
//	return -1;
//}
//
//void open_address_tab::show() {
//	for (int i = 0; i < _size; i++) {
//		std::cout << "(" << _keys[i] << "," << _values[i] << ") ";
//	}
//	std::cout << std::endl;
//}

#endif