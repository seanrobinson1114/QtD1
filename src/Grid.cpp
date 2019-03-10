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
#include <algorithm>

namespace QtD1{

// Constructor
Grid::Grid( int rows, int columns, QList<LevelPillar*> pillars )
  : d_rows( rows ),
    d_columns( columns ),
    d_z_value_rows( rows + columns - 1 ),
    d_grid( rows * columns ),
    d_grid_pillar_map(),
    d_old_highlighted_path()
{
  this->constructGrid();
  this->setCorrespondingPillars( pillars );

  this->constructBinarySearchTree();
}

// Convert start and end to LevelPillars and construct path
auto Grid::constructPath( LevelObject* start, LevelObject* end, QPointF end_coord, QPointF start_coord ) -> Path
{
  const GridElement* start_grid_element = NULL, * end_grid_element = NULL;

  // Check start
  if( start->isPillar() )
  {
    start_grid_element = d_grid_pillar_map.find( dynamic_cast<LevelPillar*>( start ) )->second;
    std::cout << "start is a pillar" << std::endl;
  }

  else 
  {
    start_grid_element = this->findGridElement( start );
    std::cout << "start is not a pillar" << std::endl;
  }

  // Check end
  if( end->isPillar() )
  {
    end_grid_element = d_grid_pillar_map.find( dynamic_cast<LevelPillar*>( end ) )->second;
    std::cout << "end is a pillar" << std::endl;
  }

  else
  {
    end_grid_element = this->findGridElement( end );
    std::cout << "end is not a pillar" << std::endl;
  }

  if( start_grid_element == NULL )
  {
    std::cout << "start grid element is NULL" << std::endl;
  }

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
    return this->constructPath( start_grid_element, end_grid_element, end_coord, start_coord );

}

// Construct path
auto Grid::constructPath( LevelPillar* start, LevelPillar* end, QPointF end_coord, QPointF start_coord ) -> Path
{
  auto pillar_start_it = d_grid_pillar_map.find( start );
  auto pillar_end_it = d_grid_pillar_map.find( end );

  // Check if start and end are both valid
  if( pillar_start_it == d_grid_pillar_map.end() ||
      pillar_end_it == d_grid_pillar_map.end() )
  {
    return Path();
  }

  return this->constructPath( pillar_start_it->second, pillar_end_it->second, end_coord, start_coord );
}

//! Construct path
auto Grid::constructPath( const GridElement* start, const GridElement* end, QPointF end_coord, QPointF start_coord ) -> Path
{
  std::cout << "constructing path with grid elements" << std::endl;
  std::cout << "mouse click coord: " << end_coord.x() << ", " << end_coord.y() << std::endl;

  // List for tracking current nodes being searched
  std::list<PathNode> path_nodes;

  // Set for checking grid element duplicates
  std::set<const GridElement*> unique_grid_elements;

  // Create node from end and add to current list with weight 0
  path_nodes.emplace_back( *end );
  path_nodes.front().setWeight( 0 );
  unique_grid_elements.insert( end );

  auto current_node_it = path_nodes.begin();
  //auto start_node_it = path_nodes.end();
  
  while( current_node_it != path_nodes.end() )
  {
    // Check if start has been reached
    if( &current_node_it->getCorrespondingGridElement() == start )
      break;
    // if( &current_node_it->getCorrespondingGridElement() == start )
    //   start_node_it = current_node_it;

    /*
     * Get the grid elements adjacencies
     * Check for null adjacencies
     * Set their weights and add to current nodes
     */

    // Northwest <--> Southeast
    this->setPathNodeAdjacencies( Northwest,
                                  Southeast,
                                  *current_node_it,
                                  path_nodes,
                                  unique_grid_elements );

    // Southeast <--> Northwest
    this->setPathNodeAdjacencies( Southeast,
                                  Northwest,
                                  *current_node_it,
                                  path_nodes,
                                  unique_grid_elements );

    // Northeast <--> Southwest
    this->setPathNodeAdjacencies( Northeast,
                                  Southwest,
                                  *current_node_it,
                                  path_nodes,
                                  unique_grid_elements );

    // Southwest <--> Northeast
    this->setPathNodeAdjacencies( Southwest,
                                  Northeast,
                                  *current_node_it,
                                  path_nodes,
                                  unique_grid_elements );
    
    // North <--> South
    this->setPathNodeAdjacencies( North,
                                  South,
                                  *current_node_it,
                                  path_nodes,
                                  unique_grid_elements );

    // South <--> North
    this->setPathNodeAdjacencies( South,
                                  North,
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

    ++current_node_it;
  }

  // There is no path between the start and end point
  //if( start_node_it == path_nodes.end() )
  if( current_node_it == path_nodes.end() )
  {
    std::cout << "No path between points" << std::endl;
    return Path();
  }

  // Construct the shortest path between the start and end node
  return this->constructShortestPath( *current_node_it, path_nodes.front(), end_coord, start_coord );
}

// Update Level Objects z value
void Grid::updateLevelObjectZValue( LevelObject* level_object ) const
{
  const GridElement* grid_element = this->findGridElement( level_object );

  if( grid_element ) 
  {
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
}

// Find the grid element that the point lies in
const GridElement* Grid::findGridElement( const QPointF& point ) const
{
  std::vector<double>::const_iterator d_x_grid_points_it =
    std::lower_bound( d_x_grid_points.begin(), d_x_grid_points.end(), point.x() );

  std::vector<double>::const_iterator d_y_grid_points_it =
    std::lower_bound( d_y_grid_points.begin(), d_y_grid_points.end(), point.y() );

  int x_index = d_x_grid_points_it - d_x_grid_points.begin();

  // Index returned from lower_bound is one after
  if( x_index > 0 )
    --x_index;

  int y_index = d_y_grid_points_it - d_y_grid_points.begin();

  // Index returned from lower_bound is one after
  if( y_index > 0 )
    --y_index;

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
  // TODO figure out how to handle non characters

  // Point near feet of character
  QPointF lower_center_point( level_object->boundingRect().left() + level_object->boundingRect().width()/2, level_object->boundingRect().height() - 20 );

  return this->findGridElement( level_object->mapToScene( lower_center_point ) );
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

    /*
     * Loop through grid and find matching values for left, right, and top
     * Top is relative to scene coordinate system
     */
    for( int j = 0; j < d_grid.size(); ++j )
    {
      QRectF grid_element_bb = d_grid[j].getBoundingBox();

      if( grid_element_bb.left() == pillar_bb.left() &&
          grid_element_bb.right() == pillar_bb.right() &&
          grid_element_bb.bottom() == pillar_bb.bottom() )
      {
        d_grid[j].setCorrespondingPillar( pillars[i] );
        d_grid_pillar_map[pillars[i]] = &d_grid[j];

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
auto Grid::constructShortestPath( const PathNode& start_node,
                                  const PathNode& end_node,
                                  const QPointF& end_coord, 
                                  const QPointF& start_coord ) -> Path
{
  std::cout << "finding shortest path" << std::endl;
  
  // List of nodes to be traveresed by an actor
  NodePath shortest_node_path = constructShortestNodePath( start_node, end_node, end_coord, start_coord );
  std::cout << "\n\noriginal path" << std::endl;
  for( auto&& point : shortest_node_path )
  {
    std::cout << "x: " << point.second.x() << ", y: " << point.second.y() << ", direction: " << point.first << std::endl;
  }
  std::cout << std::endl;

  // returned
  Path shortest_path;

  // node path length > 1
  if( shortest_node_path.size() > 1 ) 
  {
    // need first, second grid elements
    NodePath::iterator first, second;
    first = shortest_node_path.begin();
    second = first;
    ++second;

    double intersection_x_start, intersection_y_start, distance_start;
    Direction direction_start;

    // find closest intersection point with first segment
    this->calculateLineIntersection( first->second, second->second, start_coord, intersection_x_start, intersection_y_start, direction_start, distance_start );

    // need last, second last grid elements
    NodePath::reverse_iterator last, second_last;
    last = shortest_node_path.rbegin();
    second_last = last;
    ++second_last;

    double intersection_x_end, intersection_y_end, distance_end;
    Direction direction_end;

    // find closest intersection point with end segment
    this->calculateLineIntersection( second_last->second, last->second, end_coord, intersection_x_end, intersection_y_end, direction_end, distance_end );

    // Check if distance_start is 0
    if( distance_start > 0 )
    {
      Direction old_direction_start = shortest_node_path.front().first;
      shortest_node_path.pop_front();
      shortest_node_path.push_front( std::make_pair( old_direction_start, QPointF( intersection_x_start, intersection_y_start ) ) );
      shortest_node_path.push_front( std::make_pair( direction_start, start_coord ) );
    } 
    
    // Check if distance_end is 0
    if( distance_end > 0 )
    {
      // shortest_node_path.pop_back();
      // shortest_node_path.push_back( std::make_pair( direction_end, QPointF( intersection_x_end, intersection_y_end ) ) );
      // shortest_node_path.push_back( std::make_pair( direction_end, end_coord ) );
    }

    double distance = 0.0;

    NodePath::const_iterator current, next;
    current = shortest_node_path.begin();
    next = current;
    ++next;

    while( next != shortest_node_path.end() )
    {
      std::cout << "STILL LOOPING" << std::endl;
      const double x_diff = next->second.x() -
        current->second.x();

      const double y_diff = next->second.y() -
        current->second.y();

      // Calculate distance
      distance = std::sqrt( x_diff*x_diff + y_diff*y_diff );

      // Calculate the x and y of the unit vector
      const double u_x = x_diff / distance;
      const double u_y = y_diff / distance;

      shortest_path.push_back( std::make_tuple( current->first, distance, u_x, u_y ) );

      std::cout << "Direction: " << current->first << std::endl;
      std::cout << "Distance: " << distance << std::endl;
      std::cout << "Standard Vector x: " << u_x << std::endl;
      std::cout << "Standard Vector y: " << u_y << std::endl;

      ++current;
      ++next;
    }
  }
  else
  {
    // TODO
    // Special case for mini path within same grid element, only 1 node
  }
  
  return shortest_path;
}

// Construct the shortest path of nodes from the current node
auto Grid::constructShortestNodePath( const PathNode& start_node,
                                  const PathNode& end_node,
                                  const QPointF& end_coord, 
                                  const QPointF& start_coord ) -> NodePath
{
  // Unhighlight old path
  for( auto&& old_pillar : d_old_highlighted_path )
  {
    old_pillar->unhighlight();
  }
  // Clear the old highlighted path
  d_old_highlighted_path.clear();

  std::cout << "finding shortest node path" << std::endl;
  // List of nodes to be traveresed by an actor
  NodePath shortest_node_path;
  Direction direction;

  // Start at end for current_nodes( the end is the starting point )
  // Check adjacencies and add the one with the lowest weight to
  // shortest_path
  const PathNode* current_node = &start_node;

  while( true )
  {
    // Save pillars to unhighlight after new path is made and change highlight prop to true with color
    d_old_highlighted_path.push_back( current_node->getCorrespondingGridElement().getCorrespondingLevelPillar() );
    d_old_highlighted_path.back()->highlight( "blue" );

    // Check if end has been reached
    if( current_node == &end_node )
    {
      std::cout << "current node equals end node" << std::endl;
      break;
    }

    else
      std::cout << "current node doesn't equal end node" << std::endl;

    // Get the adjascent node with lowest weight
    const PathNode* next_node =
      current_node->getLowestWeightAdjascentNode( &direction );

    // Get the adjascent node center point
    QPointF next_node_center_point = next_node->getCenterPoint();

    // Add actual start and actual end
    shortest_node_path.push_back( std::make_pair( direction, current_node->getCenterPoint() ) );

    // Move to the next node
    current_node = next_node;
  }

  // Add the last node to shortest path (direction is not used)
  shortest_node_path.push_back( std::make_pair( Direction::North, current_node->getCenterPoint() ) );

  // Return the list of points
  return shortest_node_path;
}

// Calculate intersection for first and last line segments on path
void  Grid::calculateLineIntersection( const QPointF& first_grid_point, 
                                 const QPointF& second_grid_point,
                                 const QPointF& start_coord, 
                                 double& intersection_x, 
                                 double& intersection_y, 
                                 Direction& direction,
                                 double& t ) 
{
  // start_coord is character position and click target position
  std::cout << "start_coord: " << start_coord.x() << ", " << start_coord.y() << std::endl;

  // Check if x1 and x2 are equal(vertical)
  if( first_grid_point.x() == second_grid_point.x() ) 
  {
    intersection_x = first_grid_point.x();
    intersection_y = start_coord.y();

    // Check if start_coord.x < first_grid_point.x
    if( start_coord.x() < first_grid_point.x() )
    {
      direction = East;
      t = first_grid_point.x() - start_coord.x();
    }
    else
    {
      direction = West;
      t = start_coord.x() - first_grid_point.x();
    }  
  }
  else 
  {
    double m_line = ( second_grid_point.y() - first_grid_point.y() ) / ( second_grid_point.x() - first_grid_point.x() );


    std::cout << first_grid_point.x() << ", " << first_grid_point.y() << std::endl;
    std::cout << second_grid_point.x() << ", " << second_grid_point.y() << std::endl;
    std::cout << "m_line: " << m_line << std::endl;

    // calculate intercept
    double b_line = -1 * ( m_line * first_grid_point.x() ) + first_grid_point.y();
    std::cout << "b_line: " << b_line << std::endl;

    // calculate all directions
    t = std::numeric_limits<double>::max();

    double t_north = start_coord.y() - m_line * start_coord.x() - b_line;
    std::cout << "t_north: " << t_north << std::endl;
    if( t_north >= 0 && t_north < t ) 
    {
      t = t_north;
      direction = North;
      intersection_x = start_coord.x();
      intersection_y = start_coord.y() - t;
    }

    double t_northwest = ( start_coord.y() - m_line * start_coord.x() - b_line ) / ( 1 - m_line );
    std::cout << "t_northwest: " << t_northwest << std::endl;
    if( t_northwest >= 0 && t_northwest < t ) 
    {
      t = t_northwest;
      direction = Northwest;
      intersection_x = start_coord.x() - t;
      intersection_y = start_coord.y() - t;
    }

    double t_northeast = ( start_coord.y() - m_line * start_coord.x() - b_line ) / ( 1 + m_line );
    std::cout << "t_northeast: " << t_northeast << std::endl;
    if( t_northeast >= 0 && t_northeast < t )
    {
      t = t_northeast;
      direction = Northeast;
      intersection_x = start_coord.x() + t;
      intersection_y = start_coord.y() - t;
    }

    double t_west = ( m_line * start_coord.x() + b_line - start_coord.y() ) / ( m_line );
    std::cout << "t_west: " << t_west << std::endl;
    if( t_west >= 0 && t_west < t )
    {
      t = t_west;
      direction = West;
      intersection_x = start_coord.x() - t;
      intersection_y = start_coord.y();
    } 

    double t_east = ( start_coord.y() - m_line * start_coord.x() - b_line ) / m_line;
    std::cout << "t_east: " << t_east << std::endl;
    if( t_east >= 0 && t_east < t )
    {
      t = t_east;
      direction = East;
      intersection_x = start_coord.x() + t;
      intersection_y = start_coord.y();
    }

    double t_southwest = ( m_line * start_coord.x() + b_line - start_coord.y() ) / ( 1 + m_line );
    std::cout << "t_southwest: " << t_southwest << std::endl;
    if( t_southwest >= 0 && t_southwest < t )
    {
      t = t_southwest;
      direction = Southwest;
      intersection_x = start_coord.x() - t;
      intersection_y = start_coord.y() + t;
    }

    double t_southeast = ( start_coord.y() - m_line * start_coord.x() - b_line ) / ( m_line - 1 );
    std::cout << "t_southeast: " << t_southeast << std::endl;
    if( t_southeast >= 0 && t_southeast < t )
    {
      t = t_southeast;
      direction = Southeast;
      intersection_x = start_coord.x() + t;
      intersection_y = start_coord.y() + t;
    }

    double t_south = m_line * start_coord.x() + b_line - start_coord.y();
    std::cout << "t_south: " << t_south << std::endl;
    if( t_south >= 0 && t_south < t )
    {
      t = t_south;
      direction = South;
      intersection_x = start_coord.x();
      intersection_y = start_coord.y() + t;
    }
    if( t == std::numeric_limits<double>::max() )
    {
      std::cout << "\n NO VALID T VALUES" << std::endl;
    }
  }

  std::cout << "Line Segment Intersection: Distance(t): " << t << ", Direction: " << direction << std::endl;
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
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Grid.cpp
//---------------------------------------------------------------------------//
