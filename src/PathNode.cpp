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

// Get the node bounding box
QRectF PathNode::getBoundingBox() const
{
  return d_corresponding_grid_element->getBoundingBox();
}

// Get the node center point
QPointF PathNode::getCenterPoint() const
{
  return d_corresponding_grid_element->getCenterPoint();
}

// Get the corresponding grid element
const GridElement& PathNode::getCorrespondingGridElement() const
{
  return *d_corresponding_grid_element;
}

// Set an adjascent node
void PathNode::setAdjascentNode( const Direction direction, const PathNode& node )
{
  d_adjascent_path_nodes[direction] = &node;
}

// Get an adjascent node
const PathNode* PathNode::getLowestWeightAdjascentNode( Direction* direction ) const
{
  // Track which adjascent node has the lowest weight and return it
  const PathNode* lw_path_node = NULL;

  auto direction_it = d_adjascent_path_nodes.find( North );

  if( direction_it != d_adjascent_path_nodes.end() )
  {
    this->checkLowestWeightNode( North,
                                 *direction_it->second,
                                 direction,
                                 lw_path_node );
  }

  direction_it = d_adjascent_path_nodes.find( Northwest );

  if( direction_it != d_adjascent_path_nodes.end() )
  {
    this->checkLowestWeightNode( Northwest,
                                 *direction_it->second,
                                 direction,
                                 lw_path_node );
  }

  direction_it = d_adjascent_path_nodes.find( Northeast );

  if( direction_it != d_adjascent_path_nodes.end() )
  {
    this->checkLowestWeightNode( Northeast,
                                 *direction_it->second,
                                 direction,
                                 lw_path_node );
  }

  direction_it = d_adjascent_path_nodes.find( West );

  if( direction_it != d_adjascent_path_nodes.end() )
  {
    this->checkLowestWeightNode( West,
                                 *direction_it->second,
                                 direction,
                                 lw_path_node );
  }

  direction_it = d_adjascent_path_nodes.find( East );

  if( direction_it != d_adjascent_path_nodes.end() )
  {
    this->checkLowestWeightNode( East,
                                 *direction_it->second,
                                 direction,
                                 lw_path_node );
  }

  direction_it = d_adjascent_path_nodes.find( Southwest );

  if( direction_it != d_adjascent_path_nodes.end() )
  {
    this->checkLowestWeightNode( Southwest,
                                 *direction_it->second,
                                 direction,
                                 lw_path_node );
  }

  direction_it = d_adjascent_path_nodes.find( Southeast );

  if( direction_it != d_adjascent_path_nodes.end() )
  {
    this->checkLowestWeightNode( Southeast,
                                 *direction_it->second,
                                 direction,
                                 lw_path_node );
  }

  direction_it = d_adjascent_path_nodes.find( South );

  if( direction_it != d_adjascent_path_nodes.end() )
  {
    this->checkLowestWeightNode( South,
                                 *direction_it->second,
                                 direction,
                                 lw_path_node );
  }

  return lw_path_node;
}

// Check if the node is the lowest weight node
void PathNode::checkLowestWeightNode( const Direction child_node_direction,
                                      const PathNode& child_node,
                                      Direction* lowest_weight_node_direction,
                                      const PathNode*& lowest_weight_node ) const

{
  if( !lowest_weight_node )
  {
    lowest_weight_node = &child_node;

    if( lowest_weight_node_direction )
      *lowest_weight_node_direction = child_node_direction;
  }

  else if( child_node.getWeight() < lowest_weight_node->getWeight() )
  {
    lowest_weight_node = &child_node;

    if( lowest_weight_node_direction )
      *lowest_weight_node_direction = child_node_direction;
  }
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end PathNode.cpp
//---------------------------------------------------------------------------//
