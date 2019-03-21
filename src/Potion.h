//---------------------------------------------------------------------------//
//!
//! \file   Potion.h
//! \author Alex Robinson
//! \brief  The potion class declaration
//!
//---------------------------------------------------------------------------//

#ifndef POTION_H
#define POTION_H

// QtD1 Includes
#include "ConsumableInteractiveLevelObject.h"
#include "Sound.h"

namespace QtD1{

//! The potion class
class Potion : public ConsumableInteractiveLevelObject
{
  Q_OBJECT

public:

  //! Constructor
  Potion( QGraphicsObject* parent = 0 );

  //! Destructor
  ~Potion()
  { /* ... */ }

protected:

  //! Copy constructor
  Potion( const Potion& other );

  //! Play the flipping sound
  void playFlippingSound() final override;

private:

  // The potion flip sound
  std::unique_ptr<Sound> s_flip_sound;
};
  
} // end QtD1 namespace

#endif // end POTION_H

//---------------------------------------------------------------------------//
// end Potion.h
//---------------------------------------------------------------------------//
