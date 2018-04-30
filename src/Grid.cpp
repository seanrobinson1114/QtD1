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
void Grid::constructPath( QGraphicsItem* start, QGraphicsItem* end )
{
  // TODO implement path finding algorithm
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Grid.cpp
//---------------------------------------------------------------------------//
