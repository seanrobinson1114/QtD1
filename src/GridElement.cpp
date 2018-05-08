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
    d_z_value(),
    d_shape(),
    d_corresponding_pillar( NULL ),
    d_adjascent_grid_elements()
{
  this->initializeAdjascentGridElements();
}

// Set bounding box
void GridElement::setBoundingBox( int x_min, int y_min, int width, int height )
{
  d_bounding_box.setRect( x_min, y_min, width, height );

  // set painter member data
  QPolygonF shape_polygon;
  shape_polygon << QPointF( x_min, y_min + height/2 );
  shape_polygon << QPointF( x_min + width/2, y_min );
  shape_polygon << QPointF( x_min + width, y_min + height/2 );
  shape_polygon << QPointF( x_min + width/2, y_min + height );

  // Add polygon to painter path
  d_shape.addPolygon( shape_polygon );
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
                  d_bounding_box.top() + d_bounding_box.height()/2 );
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

  d_corresponding_pillar->setZValue( d_z_value );
}

// Set the corresponding pillar's z order
void GridElement::setZValue( int z_value )
{
  std::cout << "Setting grid element z value===============================================" << std::endl;
  d_z_value = z_value;
}

//! Get the z order
int GridElement::getZValue() const
{
  return d_z_value;
}

// Set an adjascent grid element
void GridElement::setAdjascentGridElement( const Direction direction, const GridElement&  grid_element )
{
  // std::cout << "\n Setting Adjascent Grid Element: " << std::endl;
  // std::cout << "current x and y: " << this->getCenterPoint().x() << " " << this->getCenterPoint().y() << std::endl;
  // std::cout << "adjasc  x and y: " << grid_element.getCenterPoint().x() << " " << grid_element.getCenterPoint().y() << std::endl;
  // if( grid_element.getCenterPoint() == this->getCenterPoint() )
  //   std::cout << "Centers Match!?\n =======================================================================================" << std::endl;
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

//! Check if painter path contains point
bool GridElement::containsPoint( const QPointF& point ) const
{
  // std::cout << "containsPoint point: " << point.x() << " : " << point.y() << std::endl;
  // std::cout << "bounding box values: "
  // << "left: " << d_bounding_box.left()
  // << " right: " << d_bounding_box.right()
  // << " top: "<< d_bounding_box.top()
  // << " bottom: " << d_bounding_box.bottom()
  // << std::endl;

  return d_shape.contains( point );
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
