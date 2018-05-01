//---------------------------------------------------------------------------//
//!
//! \file   PathNode.cpp
//! \author Sean Robinson, Alex Robinson
//! \brief  PathNode class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "PathNode.h"

namespace QtD1{

// Constructor
PathNode::PathNode( const GridElement& grid_element )
  : d_corresponding_grid_element( &grid_element ),
    d_node_weight( -1 ),
    d_adjascent_path_nodes()
{ /* ... */ }

// Set the node weight
void PathNode::setWeight( int weight )
{
  d_node_weight = weight;
}

// Get the node weight
int PathNode::getWeight() const
{
  return d_node_weight;
}

// Get the corresponding grid element
const GridElement* PathNode::getCorrespondingGridElement() const
{
  return d_corresponding_grid_element;
}

// Set an adjascent node
void PathNode::setAdjascentNode( const Direction direction, const PathNode& node )
{
  d_adjascent_path_nodes[direction] = &node;
}

// Get an adjascent node
const PathNode* PathNode::getLowestWeightAdjascentNode() const
{
  // Track which adjascent node has the lowest weight and return it
  const PathNode* lw_path_node;

  auto direction_it = d_adjascent_path_nodes.find( North );
  if( direction_it != d_adjascent_path_nodes.end() && direction_it->second->getWeight() < lw_path_node->getWeight() )
    lw_path_node = direction_it->second;

  direction_it = d_adjascent_path_nodes.find( Northwest );
  if( direction_it != d_adjascent_path_nodes.end() && direction_it->second->getWeight() < lw_path_node->getWeight() )
    lw_path_node = direction_it->second;

  direction_it = d_adjascent_path_nodes.find( Northeast );
  if( direction_it != d_adjascent_path_nodes.end() && direction_it->second->getWeight() < lw_path_node->getWeight() )
    lw_path_node = direction_it->second;

  direction_it = d_adjascent_path_nodes.find( West );
  if( direction_it != d_adjascent_path_nodes.end() && direction_it->second->getWeight() < lw_path_node->getWeight() )
    lw_path_node = direction_it->second;

  direction_it = d_adjascent_path_nodes.find( East );
  if( direction_it != d_adjascent_path_nodes.end() && direction_it->second->getWeight() < lw_path_node->getWeight() )
    lw_path_node = direction_it->second;

  direction_it = d_adjascent_path_nodes.find( Southwest );
  if( direction_it != d_adjascent_path_nodes.end() && direction_it->second->getWeight() < lw_path_node->getWeight() )
    lw_path_node = direction_it->second;

  direction_it = d_adjascent_path_nodes.find( Southeast );
  if( direction_it != d_adjascent_path_nodes.end() && direction_it->second->getWeight() < lw_path_node->getWeight() )
    lw_path_node = direction_it->second;

  direction_it = d_adjascent_path_nodes.find( South );
  if( direction_it != d_adjascent_path_nodes.end() && direction_it->second->getWeight() < lw_path_node->getWeight() )
    lw_path_node = direction_it->second;

  return lw_path_node;
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end PathNode.cpp
//---------------------------------------------------------------------------//
