#ifndef HASH_H
#define HASH_H

#include <string>
#include "list.h"

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
	chain_tab(int(*)(const K&), int(*)(int));
	chain_tab(const chain_tab<K,V,N>&);
	~chain_tab();

	void add(const K&,const V&);
	V search(const K&);
	void del(const K&);

	void show();

};

template <class K, class V, int N>
class open_address_tab {
	struct pair {
		K key;
		V value;
	};
private:
	int fill;
	bool* deleted;
	pair* _tab;
	int(*calc)(const K&);
	int(*hash)(int);
	int(*probe)(int, int);

public:
	open_address_tab(int(*)(const K&), int(*)(int), int(*)(int,int));
	open_address_tab(const open_address_tab<K,V,N>&);
	~open_address_tab();


	bool add(const K&, const V&);
	V search(const K&);
	void del(const K&);

	void show();
};

#include "hash.tpp"
#endif