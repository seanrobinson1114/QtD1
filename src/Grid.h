//---------------------------------------------------------------------------//
//!
//! \file   Grid.h
//! \author Sean Robinson, Alex Robinson
//! \brief  Grid class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GRID_H
#define GRID_H

// QtD1 Includes
#include "LevelPillar.h"
#include "GridElement.h"

// Qt Includes
#include <QList>

namespace QtD1{

//! The grid class declaration
class Grid
{

public:

  //! Typedef for the path through the grid
  typedef std::list<QPointF> Path;

  //! Constructor
  Grid( int rows, int columns, QList<LevelPillar*> pillars );

  //! Destructor
  ~Grid()
  { /* ... */ }

  //! Construct path
  Path constructPath( QGraphicsItem* start, QGraphicsItem* end ) const;

private:

  // Grid
  std::vector<GridElement> d_grid;

  // Map of grid points with corresponding pillars from scene
  std::map<QGraphicsItem*, GridElement*> d_grid_pillar_map;
};

} // end QtD1 namespace

#endif // end GRID_H

//---------------------------------------------------------------------------//
// end Grid.h
//---------------------------------------------------------------------------//
