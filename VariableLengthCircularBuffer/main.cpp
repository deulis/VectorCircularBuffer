#include <cstdio>
#include "VectorCircularBuffer.h"


void PrintVector(std::vector<unsigned char> vec)
{
    for (unsigned char c : vec)
        printf("%c", c);
    printf("\n");
}

int main()
{
    printf("hello from %s!\n", "VariableLengthCircularBuffer");

    VectorCircularBuffer buff;

    std::vector<unsigned char> vec1 = { '1', '-', 'A', 'B', 'C'};
    std::vector<unsigned char> vec2 = { '2', '-', '1', '2', '3', '4'};
    std::vector<unsigned char> vec3 = { '3', '-', 'F', 'I', 'N', 'A', 'L'};

    std::vector<unsigned char> output;

    buff.put(vec1);
    buff.put(vec2);
    buff.get(&output); PrintVector(output);
    buff.put(vec3);

    while (buff.len() > 0)
    {
        buff.get(&output);
        PrintVector(output);
    }


    return 0;
}