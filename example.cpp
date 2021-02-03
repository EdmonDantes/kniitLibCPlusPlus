#include <iostream>
#include <fstream>
#include "src/main/data/reader_input_stream.h"
#include "src/main/data/stream/impl/c_stream/input_c_stream.h"

using KNIIT_LIB_NAMESPACE;

int main() {
    auto fileInputStream = std::ifstream("input.txt");
    auto inputStream = InputCStream(&fileInputStream);
	ReaderInputStream reader(&inputStream);

	std::cout << reader.readNumber().getDouble() << '\n';
	inputStream.close();
	fileInputStream.close();
	return 0;
}