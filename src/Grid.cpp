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
  : d_grid( rows * columns )
{
  // Initialize grid, set bounding boxes and adjacencies
  for( int i = 0; i < rows; ++i )
  {
    for( int j = 0; j < columns; ++j )
    {
      int ge_index = j+(i*columns);

      d_grid[ge_index].setBoundingBox( 32*i + 32*j, 32*(columns/2) - 16*(i+1) + 16*j, 64, 32 );

      // Set North adjacent grid element
      if( i != 0 && j != columns - 1 )
      {
        d_grid[ge_index].setAdjascentGridElement( North, d_grid[j+1+(i-1)*columns]);
      }

      // Set the Northwest adjacent grid element
      if( i != 0 )
      {
        d_grid[ge_index].setAdjascentGridElement( Northwest, d_grid[j+(i-1)*columns]);
      }

      // Set the Northeast adjacent grid element
      if( j != columns - 1 )
      {
        d_grid[ge_index].setAdjascentGridElement( Northeast, d_grid[j+1+(i*columns)]);
      }

      // Set the West adjascent grid element
      if( i != 0 && j != 0 )
      {
        d_grid[ge_index].setAdjascentGridElement( West, d_grid[j-1+(i-1)*columns]);
      }

      // Set the East adjascent grid element
      if( i != rows - 1 && j != columns - 1 )
      {
        d_grid[ge_index].setAdjascentGridElement( East, d_grid[j+1+(i+1)*columns]);
      }

      // Set Southwest adjacent grid element
      if( j != 0 ) {
        d_grid[ge_index].setAdjascentGridElement( Southwest, d_grid[j-1+(i*columns)]);
      }

      // Set the Southeast adjascent grid element
      if( i != rows - 1 )
      {
        d_grid[ge_index].setAdjascentGridElement( Southeast, d_grid[j+(i+1)*columns]);
      }

      // Set the South adjacent grid element
      if( i != rows -1 && j != 0 )
      {
        d_grid[ge_index].setAdjascentGridElement( South, d_grid[j-1+(i+1)*columns]);
      }
    }
  }

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
          grid_element_bb.top() == pillar_bb.top() )
      {
        d_grid[j].setCorrespondingPillar( pillars[i] );
        break;
      }
    }
  }
}

// Construct path
std::list<QPointF> Grid::constructPath( QGraphicsItem* start, QGraphicsItem* end ) const
{
  auto pillar_start_it = d_grid_pillar_map.find( start );
  auto pillar_end_it = d_grid_pillar_map.find( end );

  // Check if start and end are both valid
  if( pillar_start_it == d_grid_pillar_map.end() || pillar_end_it == d_grid_pillar_map.end() )
  {
    // return NULL; // TODO
  }

  // Find path
  else
  {
    // List for tracking current nodes being searched
    std::list<PathNode> current_nodes;

    // Set for checking grid element duplicates
    std::set<const GridElement*> unique_grid_elements;

    // Create node from end and add to current list with weigth 0
    current_nodes.emplace( current_nodes.end(), *pillar_end_it->second );
    current_nodes.front().setWeight( 0 );
    auto current_nodes_it = current_nodes.begin();

    while( current_nodes_it != current_nodes.end() )
    {
      // Check if start has been reached
      if( current_nodes_it->getCorrespondingGridElement() == pillar_start_it->second )
        break;

      // Add grid element to set to prevent duplicate nodes
      const GridElement* grid_element = current_nodes_it->getCorrespondingGridElement();
      unique_grid_elements.insert( grid_element );

      /*
       * Get the grid elements adjacencies
       * Check for null adjacencies
       * Set their weights and add to current nodes
       */

       // Top
       const GridElement* north_adj = grid_element->getAdjascentGridElement( North );
       if( north_adj && !unique_grid_elements.count( north_adj ) )
       {
         PathNode node( *north_adj );
         node.setAdjascentNode( South, *current_nodes_it );
         current_nodes.insert( current_nodes.end(), node );
         current_nodes_it->setAdjascentNode( North, node );
         current_nodes.back().setWeight( current_nodes_it->getWeight() + 1 );
         unique_grid_elements.insert( north_adj );
       }

       // Top left
       const GridElement* northwest_adj = grid_element->getAdjascentGridElement( Northwest );
       if( northwest_adj && !unique_grid_elements.count( northwest_adj ) )
       {
         PathNode node( *northwest_adj );
         node.setAdjascentNode( Southeast, *current_nodes_it );
         current_nodes.insert( current_nodes.end(), node );
         current_nodes_it->setAdjascentNode( Northwest, node );
         current_nodes.back().setWeight( current_nodes_it->getWeight() + 1 );
         unique_grid_elements.insert( northwest_adj );
       }

       // Top right
       const GridElement* northeast_adj = grid_element->getAdjascentGridElement( Northeast );
       if( northeast_adj && !unique_grid_elements.count( northeast_adj ) )
       {
         PathNode node( *northeast_adj );
         node.setAdjascentNode( Southwest, *current_nodes_it );
         current_nodes.insert( current_nodes.end(), node );
         current_nodes_it->setAdjascentNode( Northeast, node );
         current_nodes.back().setWeight( current_nodes_it->getWeight() + 1 );
         unique_grid_elements.insert( northeast_adj );
       }

       // Left
       const GridElement* west_adj = grid_element->getAdjascentGridElement( West );
       if( west_adj && !unique_grid_elements.count( west_adj ) )
       {
         PathNode node( *west_adj );
         node.setAdjascentNode( East, *current_nodes_it );
         current_nodes.insert( current_nodes.end(), node );
         current_nodes_it->setAdjascentNode( West, node );
         current_nodes.back().setWeight( current_nodes_it->getWeight() + 1 );
         unique_grid_elements.insert( west_adj );
       }

       // Right
       const GridElement* east_adj = grid_element->getAdjascentGridElement( East );
       if( east_adj && !unique_grid_elements.count( east_adj ) )
       {
         PathNode node( *east_adj );
         node.setAdjascentNode( West, *current_nodes_it );
         current_nodes.insert( current_nodes.end(), node );
         current_nodes_it->setAdjascentNode( East, node );
         current_nodes.back().setWeight( current_nodes_it->getWeight() + 1 );
         unique_grid_elements.insert( east_adj );
       }

       // Bottom left
       const GridElement* southwest_adj = grid_element->getAdjascentGridElement( Southwest );
       if( southwest_adj && !unique_grid_elements.count( southwest_adj ) )
       {
         PathNode node( *southwest_adj );
         node.setAdjascentNode( Northeast, *current_nodes_it );
         current_nodes.insert( current_nodes.end(), node );
         current_nodes_it->setAdjascentNode( Southwest, node );
         current_nodes.back().setWeight( current_nodes_it->getWeight() + 1 );
         unique_grid_elements.insert( southwest_adj );
       }

       // Bottom right
       const GridElement* southeast_adj = grid_element->getAdjascentGridElement( Southeast );
       if( southeast_adj && !unique_grid_elements.count( southeast_adj ) )
       {
         PathNode node( *southeast_adj );
         node.setAdjascentNode( Northwest, *current_nodes_it );
         current_nodes.insert( current_nodes.end(), node );
         current_nodes_it->setAdjascentNode( Southeast, node );
         current_nodes.back().setWeight( current_nodes_it->getWeight() + 1 );
         unique_grid_elements.insert( southeast_adj );
       }

       // Bottom
       const GridElement* south_adj = grid_element->getAdjascentGridElement( South );
       if( south_adj && !unique_grid_elements.count( south_adj ) )
       {
         PathNode node( *south_adj );
         node.setAdjascentNode( North, *current_nodes_it );
         current_nodes.insert( current_nodes.end(), node );
         current_nodes_it->setAdjascentNode( South, node );
         current_nodes.back().setWeight( current_nodes_it->getWeight() + 1 );
         unique_grid_elements.insert( south_adj );
       }

      ++current_nodes_it;
    }

    // List of path nodes that represent the shortest path
    std::list<const PathNode*> shortest_path;
    shortest_path.insert( shortest_path.end(), &( *current_nodes_it ) );
    auto shortest_path_it = shortest_path.begin();

    // List of points to be traveresed by character
    std::list<QPointF> shortest_path_points;

    /*
     * Start at end for current_nodes( the end is the starting point )
     * Check adjacencies and add the one with the lowest weight to shortest_path
     */
    while( shortest_path_it != shortest_path.end() )
    {
      // Check if end has been reached
      if( (*shortest_path_it)->getCorrespondingGridElement() == pillar_end_it->second )
        break;

      // Insert adjascent node with lowest weight
      const PathNode* next_node = current_nodes_it->getLowestWeightAdjascentNode();
      shortest_path.push_back( next_node );

      // Get corresponding grid element, pillar, and set coords
      const GridElement* grid_element = next_node->getCorrespondingGridElement();
      QRectF bounding_box( grid_element->getBoundingBox() );
      QPointF point( bounding_box.left() + bounding_box.width()/2, bounding_box.bottom() + bounding_box.height()/2 );
      shortest_path_points.push_back( point );


      ++shortest_path_it;
    }

    // Return the list of points
    return shortest_path_points;
  }

}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Grid.cpp
//---------------------------------------------------------------------------//
