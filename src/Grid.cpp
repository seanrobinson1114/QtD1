//---------------------------------------------------------------------------//
//!
//! \file   Grid.cpp
//! \author Sean Robinson, Alex Robinson
//! \brief  Grid class definition
//
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "Grid.h"
#include "Direction.h"
#include "PathNode.h"

// Std Lib Includes
#include <list>
#include <set>

namespace QtD1{

// Constructor
Grid::Grid( int rows, int columns, QList<LevelPillar*> pillars )
  : d_rows( rows ),
    d_columns( columns ),
    d_z_value_rows( rows + columns - 1 ),
    d_grid( rows * columns ),
    d_grid_pillar_map()
{
  this->constructGrid();
  this->setCorrespondingPillars( pillars );

  this->constructBinarySearchTree();
}

// Convert start and end to LevelPillars and construct path
auto Grid::constructPath( LevelObject* start, LevelObject* end ) const -> Path
{
  const GridElement* start_grid_element = NULL, * end_grid_element = NULL;

  // Check start
  if( start->isPillar() )
    start_grid_element = d_grid_pillar_map.find( dynamic_cast<LevelPillar*>( start ) )->second;

  else
    start_grid_element = this->findGridElement( start );


  // Check end
  if( end->isPillar() )
    end_grid_element = d_grid_pillar_map.find( dynamic_cast<LevelPillar*>( end ) )->second;

  else
    end_grid_element = this->findGridElement( end );


  if( end_grid_element == NULL )
  {
    std::cout << "end grid element is NULL" << std::endl;
    return Path();
  }

  if( start_grid_element == NULL )
  {
    std::cout << "start grid element is NULL" << std::endl;
    return Path();
  }

  // Construct path
  else
    return this->constructPath( start_grid_element, end_grid_element );

}

// Construct path
auto Grid::constructPath( LevelPillar* start, LevelPillar* end ) const -> Path
{
  auto pillar_start_it = d_grid_pillar_map.find( start );
  auto pillar_end_it = d_grid_pillar_map.find( end );

  // Check if start and end are both valid
  if( pillar_start_it == d_grid_pillar_map.end() ||
      pillar_end_it == d_grid_pillar_map.end() )
  {
    return Path();
  }

  return this->constructPath( pillar_start_it->second, pillar_end_it->second );
}

//! Construct path
auto Grid::constructPath( const GridElement* start, const GridElement* end ) const -> Path
{
  // List for tracking current nodes being searched
  std::list<PathNode> path_nodes;

  // Set for checking grid element duplicates
  std::set<const GridElement*> unique_grid_elements;

  // Create node from end and add to current list with weigth 0
  path_nodes.emplace_back( *end );
  path_nodes.front().setWeight( 0 );
  unique_grid_elements.insert( end );

  auto current_node_it = path_nodes.begin();

  while( current_node_it != path_nodes.end() )
  {
    // Check if start has been reached
    if( &current_node_it->getCorrespondingGridElement() == start )
      break;

    /*
     * Get the grid elements adjacencies
     * Check for null adjacencies
     * Set their weights and add to current nodes
     */

     // North <--> South
    this->setPathNodeAdjacencies( North,
                                  South,
                                  *current_node_it,
                                  path_nodes,
                                  unique_grid_elements );

     // Northwest <--> Southeast
    this->setPathNodeAdjacencies( Northwest,
                                  Southeast,
                                  *current_node_it,
                                  path_nodes,
                                  unique_grid_elements );

     // Northeast <--> Southwest
    this->setPathNodeAdjacencies( Northeast,
                                  Southwest,
                                  *current_node_it,
                                  path_nodes,
                                  unique_grid_elements );

     // West <--> East
    this->setPathNodeAdjacencies( West,
                                  East,
                                  *current_node_it,
                                  path_nodes,
                                  unique_grid_elements );

     // East <--> West
    this->setPathNodeAdjacencies( East,
                                  West,
                                  *current_node_it,
                                  path_nodes,
                                  unique_grid_elements );

     // Southwest <--> Northeast
    this->setPathNodeAdjacencies( Southwest,
                                  Northeast,
                                  *current_node_it,
                                  path_nodes,
                                  unique_grid_elements );

     // Southeast <--> Northwest
    this->setPathNodeAdjacencies( Southeast,
                                  Northwest,
                                  *current_node_it,
                                  path_nodes,
                                  unique_grid_elements );

     // South <--> North
    this->setPathNodeAdjacencies( South,
                                  North,
                                  *current_node_it,
                                  path_nodes,
                                  unique_grid_elements );

    ++current_node_it;
  }

  // There is no path between the start and end point
  if( current_node_it == path_nodes.end() )
    return Path();

  // Construct the shortest path between the start and end node
  return this->constructShortestPath( *current_node_it, path_nodes.front() );
}

// Update Level Objects z value
void Grid::updateLevelObjectZValue( LevelObject* level_object ) const
{
  const GridElement* grid_element = this->findGridElement( level_object );

  // Check if the bounding box of level object is above bottom of grid element
  if( grid_element->getBoundingBox().bottom() <= level_object->boundingRect().bottom() )
  {
    level_object->setZValue( grid_element->getZValue() - 1 );
  }
  else
  {
    level_object->setZValue( grid_element->getZValue() );
  }
}

// Find the grid element that the point lies in
const GridElement* Grid::findGridElement( const QPointF& point ) const
{
  // std::cout << "grid element X: " << point.x() << std::endl;
  // std::cout << "grid element Y: " << point.y() << std::endl;

  std::vector<double>::const_iterator d_x_grid_points_it =
    std::lower_bound( d_x_grid_points.begin(), d_x_grid_points.end(), point.x() );

  std::vector<double>::const_iterator d_y_grid_points_it =
    std::lower_bound( d_y_grid_points.begin(), d_y_grid_points.end(), point.y() );

  int x_index = d_x_grid_points_it - d_x_grid_points.begin();

  // Index returned is one after
  if( x_index > 0 )
    --x_index;

  int y_index = d_y_grid_points_it - d_y_grid_points.begin();

  // Index returned is one after
  if( y_index > 0 )
    --y_index;

  // std::cout << "std::distance x index: " << x_index << std::endl;
  // std::cout << "x lower bound: " << d_x_grid_points[x_index] << std::endl;

  // std::cout << "std::distance y index: " << y_index << std::endl;
  // std::cout << "y lower bound: " << d_y_grid_points[y_index] << std::endl;

  auto x_index_map_it = d_binary_obb_tree.find( x_index );
  if( x_index_map_it != d_binary_obb_tree.end() )
  {
    auto y_index_map_it = x_index_map_it->second.find( y_index );
    if( y_index_map_it != x_index_map_it->second.end() )
    {
      const std::list<const GridElement*>& possible_grids_elements = y_index_map_it->second;
      for( auto grid_element : possible_grids_elements )
      {
        if( grid_element->containsPoint( point ) )
          return grid_element;
      }

      return NULL;
    }
    else
      return NULL;
  }
  else
    return NULL;
}

// Find the grid element that the level objects bounding box lies in
const GridElement* Grid::findGridElement( LevelObject* level_object ) const
{
  QPointF lower_left_point( level_object->boundingRect().left(), level_object->boundingRect().height() );
  return this->findGridElement( level_object->mapToScene( lower_left_point ) );
}

// Construct the grid
void Grid::constructGrid()
{
  // Initialize grid, set bounding boxes and adjacencies
  for( int i = 0; i < d_rows; ++i )
  {
    for( int j = 0; j < d_columns; ++j )
    {
      int ge_index = j+(i*d_columns);

      d_grid[ge_index].setBoundingBox( 32*i + 32*j, (32*(d_columns/2) - 16*(j+1) + 16*i) + 224, 64, 32 );
      d_grid[ge_index].setZValue( d_columns - (j+1) + i );
      std::cout << "row: " << i << std::endl;
      std::cout << "grid element z value: " << d_grid[ge_index].getZValue() << "\n" << std::endl;

      // std::cout << "ge_index: " << ge_index << std::endl;
      // std::cout << "Grid Element center: " << "x y: " << d_grid[ge_index].getCenterPoint().x() << " " << d_grid[ge_index].getCenterPoint().y() << std::endl;
      // Set North adjacent grid element
      if( i != 0 && j != d_columns - 1 )
      {
        d_grid[ge_index].setAdjascentGridElement( North, d_grid[j+1+(i-1)*d_columns] );
      }

      // Set the Northwest adjacent grid element
      if( i != 0 )
      {
        d_grid[ge_index].setAdjascentGridElement( Northwest, d_grid[j+(i-1)*d_columns] );
      }

      // Set the Northeast adjacent grid element
      if( j != d_columns - 1 )
      {
        d_grid[ge_index].setAdjascentGridElement( Northeast, d_grid[j+1+(i*d_columns)] );
      }

      // Set the West adjascent grid element
      if( i != 0 && j != 0 )
      {
        d_grid[ge_index].setAdjascentGridElement( West, d_grid[j-1+(i-1)*d_columns] );
      }

      // Set the East adjascent grid element
      if( i != d_rows - 1 && j != d_columns - 1 )
      {
        d_grid[ge_index].setAdjascentGridElement( East, d_grid[j+1+(i+1)*d_columns] );
      }

      // Set Southwest adjacent grid element
      if( j != 0 ) {
        d_grid[ge_index].setAdjascentGridElement( Southwest, d_grid[j-1+(i*d_columns)] );
      }

      // Set the Southeast adjascent grid element
      if( i != d_rows - 1 )
      {
        d_grid[ge_index].setAdjascentGridElement( Southeast, d_grid[j+(i+1)*d_columns] );
      }

      // Set the South adjacent grid element
      if( i != d_rows - 1 && j != 0 )
      {
        d_grid[ge_index].setAdjascentGridElement( South, d_grid[j-1+(i+1)*d_columns] );
      }
    }
  }
}

// Set all corresponding pillars
void Grid::setCorrespondingPillars( QList<LevelPillar*> pillars )
{
  int success = 0;
  int fail = 0;
  std::cout << "number of pillars: " << pillars.size() << std::endl;

  // Loop through pillars and find corresponding grid element
  for( int i = 0; i < pillars.size(); ++i )
  {
    QRectF pillar_bb = pillars[i]->mapRectToScene( pillars[i]->boundingRect() );

    // std::cout << "pillar bounding box: " << std::endl;
    // std::cout << "left: " << pillar_bb.left() << std::endl;
    // std::cout << "right: " << pillar_bb.right() << std::endl;
    // std::cout << "top: " << pillar_bb.top() << std::endl;
    // std::cout << "bottom: " << pillar_bb.bottom() << std::endl;

    /*
     * Loop through grid and find matching values for left, right, and top
     * Top is relative to scene coordinate system
     */
    for( int j = 0; j < d_grid.size(); ++j )
    {
      QRectF grid_element_bb = d_grid[j].getBoundingBox();

      // std::cout << std::endl;
      // std::cout << "grid element bounding box: " << std::endl;
      // std::cout << "left: " << grid_element_bb.left() << std::endl;
      // std::cout << "right: " << grid_element_bb.right() << std::endl;
      // std::cout << "top: " << grid_element_bb.top() << std::endl;
      // std::cout << "bottom: " << grid_element_bb.bottom() << std::endl;
      // std::cout << "grid element index: " << j << std::endl;
      // std::cout << std::endl;

      if( grid_element_bb.left() == pillar_bb.left() &&
          grid_element_bb.right() == pillar_bb.right() &&
          grid_element_bb.bottom() == pillar_bb.bottom() )
      {
        d_grid[j].setCorrespondingPillar( pillars[i] );
        d_grid_pillar_map[pillars[i]] = &d_grid[j];
        std::cout << "grid z value: " << d_grid[j].getZValue() << std::endl;
        std::cout << "pillar z value: " << d_grid[j].getCorrespondingLevelPillar()->zValue() << "\n" << std::endl;

        ++success;

        break;
      }

      if( j == d_grid.size() -1 )
        ++fail;
    }
  }
  std::cout << "number of matches: " << success << std::endl;
  std::cout << "number of failures: " << fail << std::endl;
}

// Set the path node adjacencies
void Grid::setPathNodeAdjacencies(
                     const Direction adjacency_direction,
                     const Direction opposite_adjacency_direction,
                     PathNode& current_node,
                     std::list<PathNode>& node_list,
                     std::set<const GridElement*>& unique_grid_elements ) const
{
  const GridElement* grid_element_adj =
    current_node.getCorrespondingGridElement().getAdjascentGridElement( adjacency_direction );

  // Make sure that there is a grid element in the desired direction and that
  // this grid element has not been used yet
  if( grid_element_adj && !unique_grid_elements.count( grid_element_adj ) )
  {
    // Check if pillar exists
    if( grid_element_adj->getCorrespondingLevelPillar() )
    {
      // Check if passable
      if( grid_element_adj->getCorrespondingLevelPillar()->isPassable() )
      {
        node_list.emplace_back( *grid_element_adj );
        node_list.back().setAdjascentNode( opposite_adjacency_direction,
                                               current_node );
        node_list.back().setWeight( current_node.getWeight() + 1 );

        current_node.setAdjascentNode( adjacency_direction, node_list.back() );
        unique_grid_elements.insert( &node_list.back().getCorrespondingGridElement() );
      }
    }
  }
}

// Construct a path from the current node
auto Grid::constructShortestPath( PathNode& start_node,
                                  PathNode& end_node ) const -> Path
{
  std::cout << "finding shortest path" << std::endl;
  // List of points to be traveresed by an actor
  Path shortest_path;

  // Start at end for current_nodes( the end is the starting point )
  // Check adjacencies and add the one with the lowest weight to
  // shortest_path
  const PathNode* current_node = &start_node;
  QPointF current_node_center_point = current_node->getCenterPoint();

  while( true )
  {
    // Check if end has been reached
    if( current_node == &end_node )
    {
      std::cout << "current node equals end node" << std::endl;
      break;
    }

    else
      std::cout << "current node doesn't equal end node" << std::endl;

    Direction direction;

    // Get the adjascent node with lowest weight
    std::cout << "current node center: " << current_node->getCenterPoint().x() << " " << current_node->getCenterPoint().y() << std::endl;

    const PathNode* next_node =
      current_node->getLowestWeightAdjascentNode( &direction );

    // Get the adjascent node center point
    QPointF next_node_center_point = next_node->getCenterPoint();

    // Calculate the distance between the two node center points
    double distance = 0.0;

    {
      const double x_diff = current_node_center_point.x() -
        next_node_center_point.x();

      std::cout << "x 1: " << current_node_center_point.x() << std::endl;
      std::cout << "x 2: " << next_node_center_point.x() << std::endl;

      const double y_diff = current_node_center_point.y() -
        next_node_center_point.y();

      std::cout << "y 1: " << current_node_center_point.y() << std::endl;
      std::cout << "y 2: " << next_node_center_point.y() << std::endl;

      // std::cout << "\n x difference: " << x_diff;
      // std::cout << " y difference: " << y_diff << "\n" << std::endl;

      distance = std::sqrt( x_diff*x_diff + y_diff*y_diff );
    }

    shortest_path.push_back( std::make_pair( direction, distance ) );

    // Move to the next node
    current_node = next_node;
    current_node_center_point = next_node_center_point;
  }

  // Return the list of points
  return shortest_path;
}

// Construct binary search tree
void Grid::constructBinarySearchTree()
{
  // Set x points
  d_x_grid_points.resize( d_columns*2 + 1 );
  for( int i = 0; i <= d_columns*2; ++i )
  {
    d_x_grid_points[i] = i*32;
  }

  // Set y points
  d_y_grid_points.resize( d_rows*2 + 1 );
  for( int i = 0; i <= d_rows*2; ++i )
  {
    d_y_grid_points[i] = i*16 + 224; // generalize this offset
  }

  // Get grid elements that overlay each mesh point
  for( int i = 0; i < d_rows; ++i )
  {
    int y_index_second = d_y_grid_points.size()/2 + i;
    int y_index_first = y_index_second - 1;

    int x_index_first = i;
    int x_index_second = x_index_first + 1;

    for( int j = 0; j < d_columns; ++j )
    {
      if( j > 0 )
      {
        --y_index_first;
        --y_index_second;
        ++x_index_first;
        ++x_index_second;
      }

      d_binary_obb_tree[x_index_first][y_index_first].push_back( &d_grid[j + i*d_columns] );
      d_binary_obb_tree[x_index_first][y_index_second].push_back( &d_grid[j + i*d_columns] );
      d_binary_obb_tree[x_index_second][y_index_first].push_back( &d_grid[j + i*d_columns] );
      d_binary_obb_tree[x_index_second][y_index_second].push_back( &d_grid[j + i*d_columns] );
    }
  }
  for( int i = 0; i < d_x_grid_points.size(); ++i )
  {
    // std::cout << "x index[" << i << "]: " << std::endl;
    for( auto y_element : d_binary_obb_tree[i] )
    {
      // std::cout << "  y_index: " << y_element.first << "(" << d_y_grid_points[y_element.first] << "-" << d_y_grid_points[y_element.first+1] << ")" << std::endl;
      for( auto y_grid_element : y_element.second )
      {
        // std::cout << "    bottom: " << y_grid_element->getBoundingBox().bottom() << std::endl
        //           << "    top: " << y_grid_element->getBoundingBox().top()
        // << std::endl;

      }
    }
    // std::cout << std::endl;
  }
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Grid.cpp
//---------------------------------------------------------------------------//
