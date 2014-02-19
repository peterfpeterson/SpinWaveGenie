#ifndef __Neighbors_H__
#define __Neighbors_H__

#define _USE_MATH_DEFINES
#include <iostream>
#include"Containers/Matrices.h"
#include "Containers/UniquePositions.h"

class Sublattice;
class Cell;

//! Finds neighbors of two sublattices between distances min and max.

class Neighbors
{
public:
    Neighbors();
    //! Finds neighbors of two sublattices between distances min and max.
    //! \param cell pointer to unit cell
    //! \param sl1 pointer to first sublattice
    //! \param sl2 pointer to second sublattice
    //! \param min minimum distance considered (Angstroms)
    //! \param max maximum distance considered (Angstroms)
    void findNeighbors(Cell& cell,std::string& sl1, std::string& sl2, double min, double max);
    double getNumberNeighbors();
    std::complex<double> getGamma(Vector3 K);
    typedef UniquePositions::Iterator Iterator;
    //! \return Returns an iterator pointing to the first element of the neighbor list
    Iterator begin();
    //! \return Returns an iterator pointing to the first element of the neighbor list
    Iterator end();
private:
    UniquePositions neighborList;
    double numberNeighbors;
};
#endif // __Neighbors_H__ 
