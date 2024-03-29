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
   * Describe a move using an index.
   */
    string Cube::getMove(MOVE ind) const
    {
        switch (ind)
        {
        case MOVE::L:
            return "L";
        case MOVE::LPRIME:
            return "L'";
        case MOVE::L2:
            return "L2";
        case MOVE::R:
            return "R";
        case MOVE::RPRIME:
            return "R'";
        case MOVE::R2:
            return "R2";
        case MOVE::U:
            return "U";
        case MOVE::UPRIME:
            return "U'";
        case MOVE::U2:
            return "U2";
        case MOVE::D:
            return "D";
        case MOVE::DPRIME:
            return "D'";
        case MOVE::D2:
            return "D2";
        case MOVE::F:
            return "F";
        case MOVE::FPRIME:
            return "F'";
        case MOVE::F2:
            return "F2";
        case MOVE::B:
            return "B";
        case MOVE::BPRIME:
            return "B'";
        case MOVE::B2:
            return "B2";
        default:
            throw RubiksCubeException("Invalid face turn index.");
        }
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
    
    const std::string reset("\033[0m");
    const std::string red("\033[0;31m");
    const std::string blue("\033[0;34m");
    const std::string yellow("\033[0;33m");
    const std::string orange("\033[0;35m");
    const std::string green("\033[0;32m");

    std::ostream& operator<<(std::ostream& os, const Cube::COLOR& color) {
        switch (color)
        {
        case Cube::COLOR::BLUE :
            os << blue << "B" << reset;
            break;
        case Cube::COLOR::WHITE:
            os << "W";
            break;
        case Cube::COLOR::YELLOW:
            os << yellow << "Y" << reset;
            break;
        case Cube::COLOR::ORANGE:
            os << orange << "O" << reset;
            break;
        case Cube::COLOR::RED:
            os << red << "R" << reset;
            break;
        case Cube::COLOR::GREEN:
            os << green << "G" << reset;
            break;
        }
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Cube::MOVE& move) {
        switch (move)
        {
        case Cube::MOVE::L:
            os << "L";
            return os;
        case Cube::MOVE::LPRIME:
            os << "L'";
            return os;
        case Cube::MOVE::L2:
            os << "L2";
            return os;
        case Cube::MOVE::R:
            os << "R";
            return os;
        case Cube::MOVE::RPRIME:
            os << "R'";
            return os;
        case Cube::MOVE::R2:
            os << "R2";
            return os;
        case Cube::MOVE::U:
            os << "U";
            return os;
        case Cube::MOVE::UPRIME:
            os << "U'";
            return os;
        case Cube::MOVE::U2:
            os << "U2";
            return os;
        case Cube::MOVE::D:
            os << "D";
            return os;
        case Cube::MOVE::DPRIME:
            os << "D'";
            return os;
        case Cube::MOVE::D2:
            os << "D2";
            return os;
        case Cube::MOVE::F:
            os << "F";
            return os;
        case Cube::MOVE::FPRIME:
            os << "F'";
            return os;
        case Cube::MOVE::F2:
            os << "F2";
            return os;
        case Cube::MOVE::B:
            os << "B";
            return os;
        case Cube::MOVE::BPRIME:
            os << "B'";
            return os;
        case Cube::MOVE::B2:
            os << "B2";
            return os;
        default:
            throw RubiksCubeException("Invalid face turn index.");
        }
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Cube& cube) {
        array<Cube::COLOR, 3> ulb = cube.getCornerColors(Cube::CORNER::ULB);
        array<Cube::COLOR, 3> urb = cube.getCornerColors(Cube::CORNER::URB);
        array<Cube::COLOR, 3> urf = cube.getCornerColors(Cube::CORNER::URF);
        array<Cube::COLOR, 3> ulf = cube.getCornerColors(Cube::CORNER::ULF);
        array<Cube::COLOR, 3> dlf = cube.getCornerColors(Cube::CORNER::DLF);
        array<Cube::COLOR, 3> dlb = cube.getCornerColors(Cube::CORNER::DLB);
        array<Cube::COLOR, 3> drb = cube.getCornerColors(Cube::CORNER::DRB);
        array<Cube::COLOR, 3> drf = cube.getCornerColors(Cube::CORNER::DRF);
        os << "      | " << ulb[0] << " " << urb[0] << " |" << endl;
        os << "      | " << ulf[0] << " " << urf[0] << " |" << endl;
        os << "       -----" << endl;
        os << "| " << ulb[1] << " " << ulf[1] << " | " << ulf[2] << " " << urf[2] << " | " << urf[1] << " " << urb[1] << " | " << urb[2] << " " << ulb[2] << " |" << endl;
        os << "| " << dlb[1] << " " << dlf[1] << " | " << dlf[2] << " " << drf[2] << " | " << drf[1] << " " << drb[1] << " | " << drb[2] << " " << dlb[2] << " |" << endl;
        os << " ----- ----- ----- -----" << endl;
        os << "      | " << dlf[0] << " " << drf[0] << " |" << endl;
        os << "      | " << dlb[0] << " " << drb[0] << " |" << endl;

        return os;
    }
}