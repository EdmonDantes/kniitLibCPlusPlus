#include <iostream>
#include "kniitLibrary/data/readerinputstream.h"

using namespace std;
using KNIIT_LIB_NAMESPACE;

int main() {
	ReaderInputStream reader("input.txt");

	cout << reader.readNumber().getDouble() << '\n';
}