//---------------------------------------------------------------------------//
//!
//! \file   PathNode.h
//! \author Sean Robinson, Alex Robinson
//! \brief  PathNode class declaration
//!
//---------------------------------------------------------------------------//

#ifndef PATH_NODE_H
#define PATH_NODE_H

// QtD1 Includes
#include "Direction.h"
#include "GridElement.h"

// Std Lib Includes
#include <map>

namespace QtD1{

//! The grid path class declaration
class PathNode
{

public:

  //! Constructor
  PathNode( const GridElement& );

  //! Destructor
  ~PathNode()
  { /* ... */ }

  //! Set the node weight
  void setWeight( int weight );

  //! Get the node weight
  int getWeight() const;

  //! Get the corresponding grid element
  const GridElement* getCorrespondingGridElement() const;

  //! Set an adjascent node
  void setAdjascentNode( const Direction, const PathNode& );

  //! Get an adjascent node
  const PathNode* getLowestWeightAdjascentNode() const;

private:

  // Grid Element associated with node
  const GridElement* d_corresponding_grid_element;

  // Weight of the node
  int d_node_weight;

  // Map of adjascent nodes
  std::map<Direction, const PathNode*> d_adjascent_path_nodes;
};

} // end QtD1 namespace

#endif // end PATH_NODE_H

//---------------------------------------------------------------------------//
// end PathNode.h
//---------------------------------------------------------------------------//
