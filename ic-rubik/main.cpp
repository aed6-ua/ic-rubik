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


bool prune(rubiks::Cube::MOVE move, rubiks::Cube::MOVE lastMove) {
    typedef rubiks::Cube::MOVE M;

    // Two twists of the same face.
    if ((move == M::L || move == M::LPRIME || move == M::L2) &&
        (lastMove == M::L || lastMove == M::LPRIME || lastMove == M::L2))
        return true;

    if ((move == M::R || move == M::RPRIME || move == M::R2) &&
        (lastMove == M::R || lastMove == M::RPRIME || lastMove == M::R2))
        return true;

    if ((move == M::U || move == M::UPRIME || move == M::U2) &&
        (lastMove == M::U || lastMove == M::UPRIME || lastMove == M::U2))
        return true;

    if ((move == M::D || move == M::DPRIME || move == M::D2) &&
        (lastMove == M::D || lastMove == M::DPRIME || lastMove == M::D2))
        return true;

    if ((move == M::F || move == M::FPRIME || move == M::F2) &&
        (lastMove == M::F || lastMove == M::FPRIME || lastMove == M::F2))
        return true;

    if ((move == M::B || move == M::BPRIME || move == M::B2) &&
        (lastMove == M::B || lastMove == M::BPRIME || lastMove == M::B2))
        return true;

    // Commutative moves.
    if ((move == M::F || move == M::FPRIME || move == M::F2) &&
        (lastMove == M::B || lastMove == M::BPRIME || lastMove == M::B2))
        return true;

    if ((move == M::L || move == M::LPRIME || move == M::L2) &&
        (lastMove == M::R || lastMove == M::RPRIME || lastMove == M::R2))
        return true;

    if ((move == M::U || move == M::UPRIME || move == M::U2) &&
        (lastMove == M::D || lastMove == M::DPRIME || lastMove == M::D2))
        return true;

    return false;
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
            if (exploring.moves.size() > 0) {
                //some pruning
                // If the last move is the same as this move, no reason to attempt it.
                // e.g. L L is the same as L2.  L2 L2 is a 360 degree twist.
                // Two moves that can be accomplished in one.  For instance, L2 L is the
                // same as L'.  L2 L' is the same as L.  Commutative.
                // In other words, if two moves on the same side occur successively (the
                // start with the same letter), prune.
                char actual = exploring.cube.getMove(moves[i]).at(0);
                char last = exploring.cube.getMove(exploring.moves.back()).at(0);
                if (actual == last) continue;
                // Commutative moves.  For example, F B is the same as B F.
                if (actual == 'F' && last == 'B') continue;
                if (actual == 'L' && last == 'R') continue;
                if (actual == 'U' && last == 'D') continue;

                if (prune(moves[i], exploring.moves.back())) continue;
            }

            Node hijo(exploring);
            hijo.move(moves[i]);
            q.push(hijo);
        }
    }
}



int main(int argc, char* argv[]) {

    rubiks::Cube cube;
    cube.u();
    cube.r();
    cube.lPrime();
    cube.f();
    cube.r();
    cube.l();
    std::cout << cube << std::endl;
    
    if (bfs(cube))
        printf("Is solved");
    else
        printf("Not solved");
    return 0;
}