//---------------------------------------------------------------------------//
//!
//! \file   GridElement.cpp
//! \author Sean Robinson, Alex Robinson
//! \brief  GridElement class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "GridElement.h"

namespace QtD1{

// Constructor
GridElement::GridElement()
  : d_bounding_box(),
    d_corresponding_pillar( NULL ),
    d_adjascent_grid_elements()
{
  this->initializeAdjascentGridElements();
}

// Set bounding box
void GridElement::setBoundingBox( int x_min, int y_min, int width, int height )
{
  d_bounding_box.setRect( x_min, y_min, width, height );
}

// Get the bounding box
QRectF GridElement::getBoundingBox() const
{
  return d_bounding_box;
}

// Get the center point of the grid
QPointF GridElement::getCenterPoint() const
{
  return QPointF( d_bounding_box.left() + d_bounding_box.width()/2,
                  d_bounding_box.right() + d_bounding_box.height()/2 );
}

// Get the corresponding pillar
const LevelPillar* GridElement::getCorrespondingLevelPillar() const
{
  return d_corresponding_pillar;
}

// Set the corresponding pillar
void GridElement::setCorrespondingPillar( LevelPillar* pillar )
{
  d_corresponding_pillar = pillar;
}

// Set an adjascent grid element
void GridElement::setAdjascentGridElement( const Direction direction, const GridElement&  grid_element )
{
  d_adjascent_grid_elements[direction] = &grid_element;
}

// Get an adjascent grid element
const GridElement* GridElement::getAdjascentGridElement( const Direction direction ) const
{
  auto direction_it = d_adjascent_grid_elements.find( direction );

  if( direction_it != d_adjascent_grid_elements.end() )
    return direction_it->second;

  else
    return NULL;
}

// Initialize adjascent grid elements
void GridElement::initializeAdjascentGridElements()
{
  d_adjascent_grid_elements[North] = NULL;
  d_adjascent_grid_elements[Northeast] = NULL;
  d_adjascent_grid_elements[Northwest] = NULL;
  d_adjascent_grid_elements[East] = NULL;
  d_adjascent_grid_elements[West] = NULL;
  d_adjascent_grid_elements[Southeast] = NULL;
  d_adjascent_grid_elements[Southwest] = NULL;
  d_adjascent_grid_elements[South] = NULL;
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end GridElement.cpp
//---------------------------------------------------------------------------//
