#include <iostream>
#include "../data/writer_output_stream.h"
#include "../data/reader_input_stream.h"

using namespace std;
using KNIIT_LIB_NAMESPACE;

int main() {
    ReaderInputStream reader("input.txt");
    auto matrix = reader.readMatrix();

    WriterOutputStream writer("out.txt");
    Set<Number> set;
    set.add(85);
    set.add(85.25);
    set.add(25);
    set.add(85);
    writer.writeSet(set);
    writer.writeString("\n\n");
    writer.writeMatrix(matrix);
    writer.writeChar('\n');
    writer.close();

    return 0;
}
