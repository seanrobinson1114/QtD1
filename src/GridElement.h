//---------------------------------------------------------------------------//
//!
//! \file   GridElement.h
//! \author Sean Robinson, Alex Robinson
//! \brief  GridElement class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GRID_ELEMENT_H
#define GRID_ELEMENT_H

// Std Lib Includes
#include <set>

// Qt Includes
#include <QRectF>

// QtD1 Includes
#include "LevelPillar.h"
#include "Direction.h"
#include "LevelObject.h"

namespace QtD1{

//! The grid element class declaration
class GridElement
{

public:

  //! Constructor
  GridElement();

  //! Destructor
  ~GridElement()
  { /* ... */ }

  //! Set bounding box
  void setBoundingBox( int x_min, int y_min, int width, int height );

  //! Get the bounding box
  QRectF getBoundingBox() const;

  //! Get the center point of the grid
  QPointF getCenterPoint() const;

  //! Get the corresponding pillar
  LevelPillar* getCorrespondingLevelPillar() const;

  //! Set the corresponding pillar
  void setCorrespondingPillar( LevelPillar* );

  //! Set the z order
  void setZValue( int );

  //! Get the z order
  int getZValue() const;

  //! Set an adjascent grid element
  void setAdjascentGridElement( const Direction, const GridElement& );

  //! Get an adjascent grid element
  const GridElement* getAdjascentGridElement( const Direction ) const;

  //! Check if painter path contains point
  bool containsPoint( const QPointF& ) const;

  //! Add a blocking Level Object 
  void addBlockingObject( const LevelObject* );

  //! Remove a blocking level object
  void removeBlockingObject( const LevelObject* );

  //! Check if this grid element is blocked
  bool constainsBlockingObject() const;

  //! Check for collisions within grid element
  bool checkForCollisions( const LevelObject* ) const;

private:

  // Initialize the adjascent grid grid elements
  void initializeAdjascentGridElements();

  // Bounding Box
  QRectF d_bounding_box;

  // Z order
  int d_z_value;

  // Painter path
  QPainterPath d_shape;

  LevelPillar* d_corresponding_pillar;

  // Map of adjascent grid elements
  std::map<Direction, const GridElement*> d_adjascent_grid_elements;

  // Set of LevelObjects currently on grid element
  std::set<const LevelObject*> d_blocking_level_objects;
};

} // end QtD1 namespace

#endif // end GRID_ELEMENT_H

//---------------------------------------------------------------------------//
// end GridElement.h
//---------------------------------------------------------------------------//
