//---------------------------------------------------------------------------//
//!
//! \file   Town.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The town class declaration
//!
//---------------------------------------------------------------------------//

#ifndef TOWN_H
#define TOWN_H

// QtD1 Includes
#include "Level.h"

namespace QtD1{

//! The town class declaration
class Town : public Level
{
  Q_OBJECT

public:

  //! Constructor
  Town( QObject* parent = 0 );

  //! Destructor
  ~Town()
  { /* ... */ }

  //! Get the type
  Type getType() const override;

  //! Get the number
  int getNumber() const override;

  //! Insert the character
  void insertCharacter( Character* character,
                        const QPointF& location,
                        const Direction direction ) override;

  //! Remove the character
  void removeCharacter() override;
};
  
} // end QtD1 namespace

#endif // end TOWN_H

//---------------------------------------------------------------------------//
// end Town.h
//---------------------------------------------------------------------------//
