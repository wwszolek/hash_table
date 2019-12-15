#include "hash.h"

#include <string>

#include "list.h"

int int_from_str(const std::string& key) {
	int val = 0;
	for (int i = 0; i < key.size(); i++) {
		val += key[i];
	}
	return val;
}