#ifndef HASH_H
#define HASH_H

#include <string>
#include "list.h"

int int_from_str(const std::string&);


template <int M> int hmod(int);

template <int M> int linear(int, int);
template <int M, int C1, int C2> int quadratic(int, int);

template <class K, class V, int N>
class chain_tab{
private:
	list <K,V>* _list;
	int(*calc)(const K&);
	int(*hash)(int);
public:
	chain_tab();
	chain_tab(const chain_tab&);
	~chain_tab();


	void add(const K&,const V&);
	V search(const K&);
	void del(const K&);

	void show();

};

//class open_address_tab {
//private:
//	static std::string DEL
//	std::string* _keys;
//	int* _values;
//	int _size;
//	int(*hash)(int);
//	int(*probe)(int, int);
//
//public:
//	open_address_tab(int);
//	open_address_tab(const open_address_tab&);
//	~open_address_tab();
//
//
//	bool add(const std::string&, int);
//	bool is_in(const std::string&);
//	void del(const std::string&);
//	int get_value(const std::string&);
//
//	void show();
//};

#include "hash.tpp"
#endif