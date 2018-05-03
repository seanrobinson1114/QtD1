//---------------------------------------------------------------------------//
//!
//! \file   Grid.h
//! \author Sean Robinson, Alex Robinson
//! \brief  Grid class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GRID_H
#define GRID_H

// Std Lib Includes
#include <set>

// Qt Includes
#include <QList>

// QtD1 Includes
#include "LevelPillar.h"
#include "GridElement.h"
#include "PathNode.h"

namespace QtD1{

//! The grid class declaration
class Grid
{

public:

  //! Typedef for the path through the grid
  typedef std::list<std::pair<Direction,double> > Path;

  //! Constructor
  Grid( int rows, int columns, QList<LevelPillar*> pillars );

  //! Destructor
  ~Grid()
  { /* ... */ }

  //! Construct path
  Path constructPath( LevelObject* start, LevelObject* end ) const;

  //! Construct path
  Path constructPath( LevelPillar* start, LevelPillar* end ) const;

private:

  // Set the path node adjacencies
  void setPathNodeAdjacencies( const Direction adjacency_direction,
                               const Direction opposite_adjacency_direction,
                               PathNode& current_node,
                               std::list<PathNode>& node_list,
                               std::set<const GridElement*>& unique_grid_elements ) const;

  // Construct a path from the current node
  Path constructShortestPath( PathNode& start_node, PathNode& end_node ) const;

  // Grid
  std::vector<GridElement> d_grid;

  // Map of grid points with corresponding pillars from scene
  std::map<LevelPillar*, GridElement*> d_grid_pillar_map;
};

} // end QtD1 namespace

#endif // end GRID_H

//---------------------------------------------------------------------------//
// end Grid.h
//---------------------------------------------------------------------------//
