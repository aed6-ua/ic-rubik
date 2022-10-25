#pragma once
#ifndef _BUSYBIN_RUBIKS_CUBE_INDEX_MODEL_H_
#define _BUSYBIN_RUBIKS_CUBE_INDEX_MODEL_H_

#include <cstdint>
#include <string>
#include <array>
#include "RubiksCubeException.h"
using std::array;
#include <algorithm>
using std::swap;

namespace rubiks
{

    class Cube {
    public:

        struct Cubie
        {
            // 0 - 7 for corners.
            uint8_t index;
            // 0 - 2 for corners.
            uint8_t orientation;
        };
        enum class FACE : uint8_t { UP, LEFT, FRONT, RIGHT, BACK, DOWN };
        enum class COLOR : uint8_t { WHITE, GREEN, RED, BLUE, ORANGE, YELLOW };
        enum class CORNER : uint8_t { ULB, URB, URF, ULF, DLF, DLB, DRB, DRF };
        enum class MOVE : uint8_t
        {
            L, LPRIME, L2,
            R, RPRIME, R2,
            U, UPRIME, U2,
            D, DPRIME, D2,
            F, FPRIME, F2,
            B, BPRIME, B2
        };

    private:
        array<Cubie, 8>  corners;
        array<COLOR, 6>  centers;

        inline void updateCornerOrientation(Cube::CORNER ind, uint8_t amount);

    public:
        //string getMove(MOVE ind) const; 

        Cube();
        Cube(const Cube& a);

        Cube& move(MOVE ind);

        array<COLOR, 3> getCornerColors(CORNER ind) const;
        COLOR getColor(FACE face, unsigned row, unsigned col) const;

        // Indexing methods.
        uint8_t getCornerIndex(CORNER ind) const;
        uint8_t getCornerOrientation(CORNER ind) const;

        bool isSolved() const;

        ~Cube() {};
        //Cube& 	operator=(const Cube& a);
        //bool	operator==(const Cube& a);

        // Face moves.
        Cube& u();
        Cube& uPrime();
        Cube& u2();

        Cube& l();
        Cube& lPrime();
        Cube& l2();

        Cube& f();
        Cube& fPrime();
        Cube& f2();

        Cube& r();
        Cube& rPrime();
        Cube& r2();

        Cube& b();
        Cube& bPrime();
        Cube& b2();

        Cube& d();
        Cube& dPrime();
        Cube& d2();
    };
}
#endif