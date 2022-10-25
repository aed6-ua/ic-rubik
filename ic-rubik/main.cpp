#include "Cube.h"

int main(int argc, char* argv[]) {

    rubiks::Cube cube;

    if (cube.isSolved())
        printf("Is solved");

    return 0;
}