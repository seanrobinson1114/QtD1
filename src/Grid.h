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
  Path constructPath( LevelObject* start, LevelObject* end, QPointF end_coord, QPointF start_coord ) const;

  //! Construct path
  Path constructPath( LevelPillar* start, LevelPillar* end, QPointF end_coord, QPointF start_coord) const;

  //! Construct path
  Path constructPath( const GridElement* start, const GridElement* end, QPointF end_coord, QPointF start_coord ) const;

  //! Update Level Objects z value
  void updateLevelObjectZValue( LevelObject* ) const;

protected:

  // Find the grid element that the point lies in
  const GridElement* findGridElement( const QPointF& ) const;

  // Find the grid element that the level objects bounding box lies in
  const GridElement* findGridElement( LevelObject* ) const;

private:

  // Construct the grid
  void constructGrid();

  // Set all corresponding pillars
  void setCorrespondingPillars( QList<LevelPillar*> );

  // Set the path node adjacencies
  void setPathNodeAdjacencies( const Direction adjacency_direction,
                               const Direction opposite_adjacency_direction,
                               PathNode& current_node,
                               std::list<PathNode>& node_list,
                               std::set<const GridElement*>& unique_grid_elements ) const;

  // Construct a path from the current node
  Path constructShortestPath( PathNode& start_node, PathNode& end_node, QPointF end_coord, QPointF start_coord ) const;

  // Construct binary search tree
  void constructBinarySearchTree();

  // Number of rows
  int d_rows;

  // Number of columns
  int d_columns;

  // Number of z value rows
  int d_z_value_rows;

  // Grid
  std::vector<GridElement> d_grid;

  // Map of grid points with corresponding pillars from scene
  std::map<LevelPillar*, GridElement*> d_grid_pillar_map;

  // Points in binary obb tree
  std::vector<double> d_x_grid_points;
  std::vector<double> d_y_grid_points;

  // Binary obb tree
  std::map<int, std::map<int, std::list<const GridElement*>>> d_binary_obb_tree;
};

} // end QtD1 namespace

#endif // end GRID_H

//---------------------------------------------------------------------------//
// end Grid.h
//---------------------------------------------------------------------------//
