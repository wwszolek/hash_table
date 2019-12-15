#include "list"
#include "hash.h"

#include <string>
#include <fstream>
#include <iostream>

int main() {
	chain_tab<std::string, int, 50> tab;
	std::fstream file("names_id.txt");
	for (int i = 0; i < 100; i++) {
		std::string k;
		std::string v;
		file >> k;
		file >> v;
		tab.add( k, stoi(v));
	}
	file.close();

	tab.show();

	std::string to_del[7] = { "Janusz", "Kamil", "Elzbieta",
		"Zofia", "Jan", "Henryk", "Urszula" };
	for (int i = 0; i < 7; i++) {
		tab.del(to_del[i]);
	}

	tab.show();
	std::cout << tab.search("Janusz") << std::endl;
	std::cout << tab.search("Wojciech") << std::endl;

	system("PAUSE");

	return 0;
}