#include "Cube.h"
#include <queue>
#include <string>
#include <iostream>


bool bfs(rubiks::Cube &cube) {
    rubiks::Cube::MOVE moves[] = {
            rubiks::Cube::MOVE::L, rubiks::Cube::MOVE::LPRIME, rubiks::Cube::MOVE::L2,
            rubiks::Cube::MOVE::R, rubiks::Cube::MOVE::RPRIME, rubiks::Cube::MOVE::R2,
            rubiks::Cube::MOVE::U, rubiks::Cube::MOVE::UPRIME, rubiks::Cube::MOVE::U2,
            rubiks::Cube::MOVE::D, rubiks::Cube::MOVE::DPRIME, rubiks::Cube::MOVE::D2,
            rubiks::Cube::MOVE::F, rubiks::Cube::MOVE::FPRIME, rubiks::Cube::MOVE::F2,
            rubiks::Cube::MOVE::B, rubiks::Cube::MOVE::BPRIME, rubiks::Cube::MOVE::B2
    };
    std::queue<rubiks::Cube> q;
    q.push(cube);
    int contador = 0;
    while (!q.empty())
    {
        rubiks::Cube exploring = q.front();
        q.pop();
        if (exploring.isSolved()) {
            std::cout << exploring << std::endl;
            return true;
            
        }
        contador++;

        printf("%d", contador);
        for (int i=0; i < 18; i++)
        {
            rubiks::Cube hijo(exploring);
            hijo.move(moves[i]);
            q.push(hijo);
        }
    }
}



int main(int argc, char* argv[]) {

    rubiks::Cube cube;
    cube.u();
    std::cout << cube << std::endl;
    
    if (bfs(cube))
        printf("Is solved");
    else
        printf("Not solved");
    return 0;
}