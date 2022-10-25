#include "Cube.h"


namespace rubiks
{
    using namespace std;
    /**
     * Initialize the cube with red on the top and white up front.
     */
    Cube::Cube() {
        // Corners.
        for (unsigned i = 0; i < 8; ++i)
        {
            this->corners[i].index = i;
            this->corners[i].orientation = 0;
        }

        // Centers.
        this->centers[0] = COLOR::RED;
        this->centers[1] = COLOR::BLUE;
        this->centers[2] = COLOR::WHITE;
        this->centers[3] = COLOR::GREEN;
        this->centers[4] = COLOR::YELLOW;
        this->centers[5] = COLOR::ORANGE;

    }

    Cube::Cube(const Cube& cube) {
        if (cube.getColor(FACE::UP, 1, 1) != COLOR::RED ||
            cube.getColor(FACE::FRONT, 1, 1) != COLOR::WHITE)
        {
            throw RubiksCubeException(
                "Cube can only be initialized from a model if it's oriented with red on top and white up front.");
        }

        // Corners.
        for (uint8_t i = 0; i < 8; ++i)
        {
            this->corners[i].index = cube.getCornerIndex((Cube::CORNER)i);
            this->corners[i].orientation = cube.getCornerOrientation((Cube::CORNER)i);
        }
        // Centers.
        this->centers[0] = COLOR::RED;
        this->centers[1] = COLOR::BLUE;
        this->centers[2] = COLOR::WHITE;
        this->centers[3] = COLOR::GREEN;
        this->centers[4] = COLOR::YELLOW;
        this->centers[5] = COLOR::ORANGE;
    }

    /**
   * Move using a move index.
   */
    Cube& Cube::move(MOVE ind)
    {
        switch (ind)
        {
        case MOVE::L:
            return this->l();
        case MOVE::LPRIME:
            return this->lPrime();
        case MOVE::L2:
            return this->l2();
        case MOVE::R:
            return this->r();
        case MOVE::RPRIME:
            return this->rPrime();
        case MOVE::R2:
            return this->r2();
        case MOVE::U:
            return this->u();
        case MOVE::UPRIME:
            return this->uPrime();
        case MOVE::U2:
            return this->u2();
        case MOVE::D:
            return this->d();
        case MOVE::DPRIME:
            return this->dPrime();
        case MOVE::D2:
            return this->d2();
        case MOVE::F:
            return this->f();
        case MOVE::FPRIME:
            return this->fPrime();
        case MOVE::F2:
            return this->f2();
        case MOVE::B:
            return this->b();
        case MOVE::BPRIME:
            return this->bPrime();
        case MOVE::B2:
            return this->b2();
        default:
            throw RubiksCubeException("Invalid face turn index.");
        }
    }

    /**
    * Get the corner colors at an index.  Three colors are returns: U or D, L or
    * R, F or B (YXZ).
    */
    array<Cube::COLOR, 3> Cube::getCornerColors(
        Cube::CORNER ind) const
    {
        array<COLOR, 3> colors;

        Cubie corner = this->corners.at((unsigned)ind);

        unsigned i0, i1, i2;

        // Red or orange on top.
        if (corner.orientation == 0)
        {
            i0 = 0;
            i1 = 1;
            i2 = 2;

            // A quarter turn of U or D swaps the two other colors.
            if ((corner.index + (unsigned)ind) % 2 == 1)
                swap(i1, i2);
        }
        else if (corner.orientation == 1)
        {
            i0 = 1;
            i1 = 2;
            i2 = 0;

            if ((corner.index + (unsigned)ind) % 2 == 1)
                swap(i0, i1);
        }
        else // if (corner.orientation == 2)
        {
            i0 = 2;
            i1 = 0;
            i2 = 1;

            if ((corner.index + (unsigned)ind) % 2 == 1)
                swap(i0, i2);
        }

        switch ((CORNER)corner.index)
        {
        case CORNER::ULB:
            colors[i0] = COLOR::RED;
            colors[i1] = COLOR::BLUE;
            colors[i2] = COLOR::YELLOW;
            break;

        case CORNER::URB:
            colors[i0] = COLOR::RED;
            colors[i1] = COLOR::GREEN;
            colors[i2] = COLOR::YELLOW;
            break;

        case CORNER::URF:
            colors[i0] = COLOR::RED;
            colors[i1] = COLOR::GREEN;
            colors[i2] = COLOR::WHITE;
            break;

        case CORNER::ULF:
            colors[i0] = COLOR::RED;
            colors[i1] = COLOR::BLUE;
            colors[i2] = COLOR::WHITE;
            break;

        case CORNER::DLF:
            colors[i0] = COLOR::ORANGE;
            colors[i1] = COLOR::BLUE;
            colors[i2] = COLOR::WHITE;
            break;

        case CORNER::DLB:
            colors[i0] = COLOR::ORANGE;
            colors[i1] = COLOR::BLUE;
            colors[i2] = COLOR::YELLOW;
            break;

        case CORNER::DRB:
            colors[i0] = COLOR::ORANGE;
            colors[i1] = COLOR::GREEN;
            colors[i2] = COLOR::YELLOW;
            break;

        case CORNER::DRF:
            colors[i0] = COLOR::ORANGE;
            colors[i1] = COLOR::GREEN;
            colors[i2] = COLOR::WHITE;
            break;
        }

        return colors;
    }

    /**
   * Get the facet color using a face, row, and column.
   */
    Cube::COLOR Cube::getColor(
        FACE f, unsigned row, unsigned col) const
    {
        if (row == 1 && col == 1)
            return (COLOR)this->centers[(unsigned)f];

        // The colors are arranged Y, X, Z (see getCornerColors).
        if (f == FACE::UP)
        {
            if (row == 0)
            {
                if (col == 0)
                    return this->getCornerColors(CORNER::ULB)[0];
                else
                    return this->getCornerColors(CORNER::URB)[0];
            }
            else
            {
                if (col == 0)
                    return this->getCornerColors(CORNER::ULF)[0];
                else
                    return this->getCornerColors(CORNER::URF)[0];
            }
        }
        else if (f == FACE::LEFT)
        {
            if (row == 0)
            {
                if (col == 0)
                    return this->getCornerColors(CORNER::ULB)[1];
                else
                    return this->getCornerColors(CORNER::ULF)[1];
            }
            else
            {
                if (col == 0)
                    return this->getCornerColors(CORNER::DLB)[1];
                else
                    return this->getCornerColors(CORNER::DLF)[1];
            }
        }
        else if (f == FACE::FRONT)
        {
            if (row == 0)
            {
                if (col == 0)
                    return this->getCornerColors(CORNER::ULF)[2];
                else
                    return this->getCornerColors(CORNER::URF)[2];
            }
            else
            {
                if (col == 0)
                    return this->getCornerColors(CORNER::DLF)[2];
                else
                    return this->getCornerColors(CORNER::DRF)[2];
            }
        }
        else if (f == FACE::RIGHT)
        {
            if (row == 0)
            {
                if (col == 0)
                    return this->getCornerColors(CORNER::URF)[1];
                else
                    return this->getCornerColors(CORNER::URB)[1];
            }
            else
            {
                if (col == 0)
                    return this->getCornerColors(CORNER::DRF)[1];

                else
                    return this->getCornerColors(CORNER::DRB)[1];
            }
        }
        else if (f == FACE::BACK)
        {
            if (row == 0)
            {
                if (col == 0)
                    return this->getCornerColors(CORNER::URB)[2];
                else
                    return this->getCornerColors(CORNER::ULB)[2];
            }
            else
            {
                if (col == 0)
                    return this->getCornerColors(CORNER::DRB)[2];
                else
                    return this->getCornerColors(CORNER::DLB)[2];
            }
        }
        else // if (f == FACE::DOWN)
        {
            if (row == 0)
            {
                if (col == 0)
                    return this->getCornerColors(CORNER::DLF)[0];
                else
                    return this->getCornerColors(CORNER::DRF)[0];
            }
            else
            {
                if (col == 0)
                    return this->getCornerColors(CORNER::DLB)[0];
                else
                    return this->getCornerColors(CORNER::DRB)[0];
            }
        }
    }

    /**
     * Get the cubie index of a corner cubie.
     */
    uint8_t Cube::getCornerIndex(CORNER ind) const
    {
        return this->corners[(unsigned)ind].index;
    }

    /**
     * Get the orientation of a corner cubie.
     */
    uint8_t Cube::getCornerOrientation(CORNER ind) const
    {
        return this->corners[(unsigned)ind].orientation;
    }

    /**
     * Check if the cube is in a solved state.
     */
    bool Cube::isSolved() const
    {
        for (unsigned i = 0; i < this->corners.size(); ++i)
        {
            if (this->corners[i].index != i || this->corners[i].orientation != 0)
                return false;
        }

        return true;
    }

    /**
     * Helper to update the orientation of corners on 90-degree CW twist.
     * @param ind The corner index to update.
     * @param amount The amount to update the orientation by: 1, or 2.
     */
    inline void Cube::updateCornerOrientation(
        CORNER ind, uint8_t amount)
    {
        Cubie& corner = this->corners[(unsigned)ind];

        // For 90-degree twists that change the orientation of corners, half of the
        // corners change orientation by 1 (0->1, 1->2, 2->0) and the other half
        // change by 2 (0->2, 1->0, 2->1 [mod 3]).
        // Orientation 0: Red or orange on top or bottom.
        // Orientation 1: Red or orange is twisted clockwise from its nearest up or
        // down face.
        // Orientation 2: Red or orange is twisted counterclockwise from its
        // nearest up or down face.
        corner.orientation += amount;

        // % 3, but a bit faster.
        if (corner.orientation == 3)
            corner.orientation = 0;
        else if (corner.orientation == 4)
            corner.orientation = 1;
    }


    /**
     * Up.
     */
    Cube& Cube::u()
    {
        Cubie hold = this->corners[(unsigned)CORNER::ULF];
        this->corners[(unsigned)CORNER::ULF] = this->corners[(unsigned)CORNER::URF];
        this->corners[(unsigned)CORNER::URF] = this->corners[(unsigned)CORNER::URB];
        this->corners[(unsigned)CORNER::URB] = this->corners[(unsigned)CORNER::ULB];
        this->corners[(unsigned)CORNER::ULB] = hold;

        return *this;
    }
    /**
     * Up prime.
     */
    Cube& Cube::uPrime()
    {
        Cubie hold = this->corners[(unsigned)CORNER::ULB];
        this->corners[(unsigned)CORNER::ULB] = this->corners[(unsigned)CORNER::URB];
        this->corners[(unsigned)CORNER::URB] = this->corners[(unsigned)CORNER::URF];
        this->corners[(unsigned)CORNER::URF] = this->corners[(unsigned)CORNER::ULF];
        this->corners[(unsigned)CORNER::ULF] = hold;

        return *this;
    }

    /**
     * Up 2.
     */
    Cube& Cube::u2()
    {
        swap(this->corners[(unsigned)CORNER::ULB], this->corners[(unsigned)CORNER::URF]);
        swap(this->corners[(unsigned)CORNER::URB], this->corners[(unsigned)CORNER::ULF]);

        return *this;
    }

    /**
     * Left.
     */
    Cube& Cube::l()
    {
        Cubie hold = this->corners[(unsigned)CORNER::DLB];
        this->corners[(unsigned)CORNER::DLB] = this->corners[(unsigned)CORNER::DLF];
        this->corners[(unsigned)CORNER::DLF] = this->corners[(unsigned)CORNER::ULF];
        this->corners[(unsigned)CORNER::ULF] = this->corners[(unsigned)CORNER::ULB];
        this->corners[(unsigned)CORNER::ULB] = hold;

        this->updateCornerOrientation(CORNER::DLB, 1);
        this->updateCornerOrientation(CORNER::DLF, 2);
        this->updateCornerOrientation(CORNER::ULF, 1);
        this->updateCornerOrientation(CORNER::ULB, 2);

        return *this;
    }

    /**
     * Left prime.
     */
    Cube& Cube::lPrime()
    {
        Cubie hold = this->corners[(unsigned)CORNER::DLB];
        this->corners[(unsigned)CORNER::DLB] = this->corners[(unsigned)CORNER::ULB];
        this->corners[(unsigned)CORNER::ULB] = this->corners[(unsigned)CORNER::ULF];
        this->corners[(unsigned)CORNER::ULF] = this->corners[(unsigned)CORNER::DLF];
        this->corners[(unsigned)CORNER::DLF] = hold;

        this->updateCornerOrientation(CORNER::DLB, 1);
        this->updateCornerOrientation(CORNER::DLF, 2);
        this->updateCornerOrientation(CORNER::ULF, 1);
        this->updateCornerOrientation(CORNER::ULB, 2);

        return *this;
    }

    /**
     * Left 2.
     */
    Cube& Cube::l2()
    {
        swap(this->corners[(unsigned)CORNER::DLB], this->corners[(unsigned)CORNER::ULF]);
        swap(this->corners[(unsigned)CORNER::ULB], this->corners[(unsigned)CORNER::DLF]);

        return *this;
    }

    /**
     * Front.
     */
    Cube& Cube::f()
    {
        Cubie hold = this->corners[(unsigned)CORNER::ULF];
        this->corners[(unsigned)CORNER::ULF] = this->corners[(unsigned)CORNER::DLF];
        this->corners[(unsigned)CORNER::DLF] = this->corners[(unsigned)CORNER::DRF];
        this->corners[(unsigned)CORNER::DRF] = this->corners[(unsigned)CORNER::URF];
        this->corners[(unsigned)CORNER::URF] = hold;

        this->updateCornerOrientation(CORNER::ULF, 2);
        this->updateCornerOrientation(CORNER::URF, 1);
        this->updateCornerOrientation(CORNER::DRF, 2);
        this->updateCornerOrientation(CORNER::DLF, 1);

        return *this;
    }

    /**
     * Front prime.
     */
    Cube& Cube::fPrime()
    {
        Cubie hold = this->corners[(unsigned)CORNER::ULF];
        this->corners[(unsigned)CORNER::ULF] = this->corners[(unsigned)CORNER::URF];
        this->corners[(unsigned)CORNER::URF] = this->corners[(unsigned)CORNER::DRF];
        this->corners[(unsigned)CORNER::DRF] = this->corners[(unsigned)CORNER::DLF];
        this->corners[(unsigned)CORNER::DLF] = hold;

        this->updateCornerOrientation(CORNER::ULF, 2);
        this->updateCornerOrientation(CORNER::URF, 1);
        this->updateCornerOrientation(CORNER::DRF, 2);
        this->updateCornerOrientation(CORNER::DLF, 1);

        return *this;
    }

    /**
     * Front 2.
     */
    Cube& Cube::f2()
    {
        swap(this->corners[(unsigned)CORNER::ULF], this->corners[(unsigned)CORNER::DRF]);
        swap(this->corners[(unsigned)CORNER::URF], this->corners[(unsigned)CORNER::DLF]);

        return *this;
    }

    /**
     * Right.
     */
    Cube& Cube::r()
    {
        Cubie hold = this->corners[(unsigned)CORNER::DRB];
        this->corners[(unsigned)CORNER::DRB] = this->corners[(unsigned)CORNER::URB];
        this->corners[(unsigned)CORNER::URB] = this->corners[(unsigned)CORNER::URF];
        this->corners[(unsigned)CORNER::URF] = this->corners[(unsigned)CORNER::DRF];
        this->corners[(unsigned)CORNER::DRF] = hold;

        this->updateCornerOrientation(CORNER::DRB, 2);
        this->updateCornerOrientation(CORNER::DRF, 1);
        this->updateCornerOrientation(CORNER::URF, 2);
        this->updateCornerOrientation(CORNER::URB, 1);

        return *this;
    }

    /**
     * Right prime.
     */
    Cube& Cube::rPrime()
    {
        Cubie hold = this->corners[(unsigned)CORNER::DRB];
        this->corners[(unsigned)CORNER::DRB] = this->corners[(unsigned)CORNER::DRF];
        this->corners[(unsigned)CORNER::DRF] = this->corners[(unsigned)CORNER::URF];
        this->corners[(unsigned)CORNER::URF] = this->corners[(unsigned)CORNER::URB];
        this->corners[(unsigned)CORNER::URB] = hold;

        this->updateCornerOrientation(CORNER::DRB, 2);
        this->updateCornerOrientation(CORNER::DRF, 1);
        this->updateCornerOrientation(CORNER::URF, 2);
        this->updateCornerOrientation(CORNER::URB, 1);

        return *this;
    }

    /**
     * Right 2.
     */
    Cube& Cube::r2()
    {
        swap(this->corners[(unsigned)CORNER::DRB], this->corners[(unsigned)CORNER::URF]);
        swap(this->corners[(unsigned)CORNER::URB], this->corners[(unsigned)CORNER::DRF]);

        return *this;
    }

    /**
     * Back.
     */
    Cube& Cube::b()
    {
        Cubie hold = this->corners[(unsigned)CORNER::ULB];
        this->corners[(unsigned)CORNER::ULB] = this->corners[(unsigned)CORNER::URB];
        this->corners[(unsigned)CORNER::URB] = this->corners[(unsigned)CORNER::DRB];
        this->corners[(unsigned)CORNER::DRB] = this->corners[(unsigned)CORNER::DLB];
        this->corners[(unsigned)CORNER::DLB] = hold;

        this->updateCornerOrientation(CORNER::ULB, 1);
        this->updateCornerOrientation(CORNER::URB, 2);
        this->updateCornerOrientation(CORNER::DRB, 1);
        this->updateCornerOrientation(CORNER::DLB, 2);

        return *this;
    }

    /**
     * Back prime.
     */
    Cube& Cube::bPrime()
    {
        Cubie hold = this->corners[(unsigned)CORNER::ULB];
        this->corners[(unsigned)CORNER::ULB] = this->corners[(unsigned)CORNER::DLB];
        this->corners[(unsigned)CORNER::DLB] = this->corners[(unsigned)CORNER::DRB];
        this->corners[(unsigned)CORNER::DRB] = this->corners[(unsigned)CORNER::URB];
        this->corners[(unsigned)CORNER::URB] = hold;

        this->updateCornerOrientation(CORNER::ULB, 1);
        this->updateCornerOrientation(CORNER::URB, 2);
        this->updateCornerOrientation(CORNER::DRB, 1);
        this->updateCornerOrientation(CORNER::DLB, 2);

        return *this;
    }

    /**
     * Back 2.
     */
    Cube& Cube::b2()
    {
        swap(this->corners[(unsigned)CORNER::ULB], this->corners[(unsigned)CORNER::DRB]);
        swap(this->corners[(unsigned)CORNER::URB], this->corners[(unsigned)CORNER::DLB]);

        return *this;
    }

    /**
     * Down.
     */
    Cube& Cube::d()
    {
        Cubie hold = this->corners[(unsigned)CORNER::DLB];
        this->corners[(unsigned)CORNER::DLB] = this->corners[(unsigned)CORNER::DRB];
        this->corners[(unsigned)CORNER::DRB] = this->corners[(unsigned)CORNER::DRF];
        this->corners[(unsigned)CORNER::DRF] = this->corners[(unsigned)CORNER::DLF];
        this->corners[(unsigned)CORNER::DLF] = hold;

        return *this;
    }

    /**
     * Down prime.
     */
    Cube& Cube::dPrime()
    {
        Cubie hold = this->corners[(unsigned)CORNER::DLF];
        this->corners[(unsigned)CORNER::DLF] = this->corners[(unsigned)CORNER::DRF];
        this->corners[(unsigned)CORNER::DRF] = this->corners[(unsigned)CORNER::DRB];
        this->corners[(unsigned)CORNER::DRB] = this->corners[(unsigned)CORNER::DLB];
        this->corners[(unsigned)CORNER::DLB] = hold;

        return *this;
    }

    /**
     * Down 2.
     */
    Cube& Cube::d2()
    {
        swap(this->corners[(unsigned)CORNER::DLB], this->corners[(unsigned)CORNER::DRF]);
        swap(this->corners[(unsigned)CORNER::DRB], this->corners[(unsigned)CORNER::DLF]);

        return *this;
    }
}