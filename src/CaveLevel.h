//---------------------------------------------------------------------------//
//!
//! \file   CaveLevel.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The cave level class declaration
//!
//---------------------------------------------------------------------------//

#ifndef CAVE_LEVEL_H
#define CAVE_LEVEL_H

// QtD1 Includes
#include "Level.h"

namespace QtD1{

//! The cave level class declaration
class CaveLevel : public Level
{
  Q_OBJECT

public:

  //! Constructor
  CaveLevel( const int number, QObject* parent = 0 );

  //! Destructor
  ~CaveLevel()
  { /* ... */ }

  //! Get the type
  Type getType() const override;

  //! Get the number
  int getNumber() const override;

private:

  // The cave music
  static std::shared_ptr<Music> s_cave_music;

  // The cave level number
  int d_number;
};
  
} // end QtD1 namespace

#endif // end CAVE_LEVEL_H

//---------------------------------------------------------------------------//
// end CaveLevel.h
//---------------------------------------------------------------------------//
