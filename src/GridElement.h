//---------------------------------------------------------------------------//
//!
//! \file   GridElement.h
//! \author Sean Robinson, Alex Robinson
//! \brief  GridElement class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GRID_ELEMENT_H
#define GRID_ELEMENT_H

// Qt Includes
#include <QRectF>

// QtD1 Includes
#include "LevelPillar.h"
#include "Direction.h"

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
  const LevelPillar* getCorrespondingLevelPillar() const;

  //! Set the corresponding pillar
  void setCorrespondingPillar( LevelPillar* );

  //! Set an adjascent grid element
  void setAdjascentGridElement( const Direction, const GridElement& );

  //! Get an adjascent grid element
  const GridElement* getAdjascentGridElement( const Direction ) const;

private:

  // Initialize the adjascent grid grid elements
  void initializeAdjascentGridElements();

  // Bounding Box
  QRectF d_bounding_box;

  LevelPillar* d_corresponding_pillar;

  // Map of adjascent grid elements
  std::map<Direction, const GridElement*> d_adjascent_grid_elements;
};

} // end QtD1 namespace

#endif // end GRID_ELEMENT_H

//---------------------------------------------------------------------------//
// end GridElement.h
//---------------------------------------------------------------------------//
