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
chain_tab<K, V, N>::chain_tab(): hash(&hmod<N>), calc(&int_from_str) {
	_list = new list<K, V>[N];
	for (int i = 0; i < N; i++)
		_list[i] = list<K, V>();
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


//open_address_tab::open_address_tab(int size) :
//	_size(size), hash(&hmod<13>), probe(&linear<13>) {
//	_keys = new std::string[_size];
//	_values = new int[_size];
//	deleted = new bool[_size];
//	for (int i = 0; i < _size; i++) {
//		_values[i] = -1;
//		deleted[i] = false;
//	}
//}
//
//open_address_tab::open_address_tab(const open_address_tab& other) {
//	_size = other._size;
//	hash = other.hash;
//	probe = other.probe;
//	_keys = new std::string[_size];
//	_values = new int[_size];
//	deleted = new bool[_size];
//	for (int i = 0; i < _size; i++) {
//		_keys[i] = other._keys[i];
//		_values[i] = other._values[i];
//		deleted[i] = other.deleted[i];
//	}
//}
//
//open_address_tab::~open_address_tab() {
//	if (_keys) {
//		delete[] _keys;
//		delete[] _values;
//		delete[] deleted;
//	}
//}
//
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