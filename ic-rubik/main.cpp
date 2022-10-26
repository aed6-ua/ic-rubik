#include "Cube.h"
#include <queue>
#include <string>
#include <iostream>
#include <vector>


class Node
{
public:
    Node();
    Node(const rubiks::Cube& c, const std::vector<rubiks::Cube::MOVE> moves) {
        this->cube = c;
        this->moves = moves;
    }
    void move(rubiks::Cube::MOVE move) {
        this->cube.move(move);
        this->moves.push_back(move);
    }
    ~Node();
    rubiks::Cube cube;
    std::vector<rubiks::Cube::MOVE> moves;

};

Node::Node()
{
}

Node::~Node()
{
}


bool bfs(rubiks::Cube &cube) {
    rubiks::Cube::MOVE moves[] = {
            rubiks::Cube::MOVE::L, rubiks::Cube::MOVE::LPRIME, rubiks::Cube::MOVE::L2,
            rubiks::Cube::MOVE::R, rubiks::Cube::MOVE::RPRIME, rubiks::Cube::MOVE::R2,
            rubiks::Cube::MOVE::U, rubiks::Cube::MOVE::UPRIME, rubiks::Cube::MOVE::U2,
            rubiks::Cube::MOVE::D, rubiks::Cube::MOVE::DPRIME, rubiks::Cube::MOVE::D2,
            rubiks::Cube::MOVE::F, rubiks::Cube::MOVE::FPRIME, rubiks::Cube::MOVE::F2,
            rubiks::Cube::MOVE::B, rubiks::Cube::MOVE::BPRIME, rubiks::Cube::MOVE::B2
    };
    std::queue<Node> q;
    std::vector<rubiks::Cube::MOVE> m;
    Node root = Node(cube, m);
    q.push(root);
    while (!q.empty())
    {
        Node exploring = q.front();
        q.pop();
        if (exploring.cube.isSolved()) {
            std::cout << "\n\nSolved after " << exploring.moves.size() << " moves" << std::endl;
            std::cout << "Moves :" << std::endl;
            for (auto& m : exploring.moves) {
                std::cout << m << " ";
            }
            std::cout << "\n" << exploring.cube << std::endl;
            return true;
            
        }
        for (int i=0; i < 18; i++)
        {
            Node hijo(exploring);
            hijo.move(moves[i]);
            q.push(hijo);
        }
    }
}



int main(int argc, char* argv[]) {

    rubiks::Cube cube;
    cube.u2();
    cube.b();
    cube.fPrime();
    std::cout << cube << std::endl;
    
    if (bfs(cube))
        printf("Is solved");
    else
        printf("Not solved");
    return 0;
}