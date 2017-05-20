//---------------------------------------------------------------------------//
//!
//! \file   HellLevel.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The hell level class declaration
//!
//---------------------------------------------------------------------------//

#ifndef HELL_LEVEL_H
#define HELL_LEVEL_H

// QtD1 Includes
#include "Level.h"

namespace QtD1{

//! The hell level class declaration
class HellLevel : public Level
{
  Q_OBJECT

public:

  //! Constructor
  HellLevel( const int number, QObject* parent = 0 );

  //! Destructor
  ~HellLevel()
  { /* ... */ }

  //! Get the type
  Type getType() const override;

  //! Get the number
  int getNumber() const override;

private:

  // The hell music
  static std::shared_ptr<Music> s_hell_music;

  // The hell level number
  int d_number;
};
  
} // end QtD1 namespace

#endif // end HELL_LEVEL_H

//---------------------------------------------------------------------------//
// end HellLevel.h
//---------------------------------------------------------------------------//
