//---------------------------------------------------------------------------//
//!
//! \file   CatacombLevel.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The catacomb level class declaration
//!
//---------------------------------------------------------------------------//

#ifndef CATACOMB_LEVEL_H
#define CATACOMB_LEVEL_H

// QtD1 Includes
#include "Level.h"

namespace QtD1{

//! The catacomb level class declaration
class CatacombLevel : public Level
{
  Q_OBJECT

public:

  //! Constructor
  CatacombLevel( const int number, QObject* parent = 0 );

  //! Destructor
  ~CatacombLevel()
  { /* ... */ }

  //! Get the type
  Type getType() const override;

  //! Get the number
  int getNumber() const override;

private:

  // The catacomb music
  static std::shared_ptr<Music> s_catacomb_music;

  // The catacomb level number
  int d_number;
};
  
} // end QtD1 namespace

#endif // end CATACOMB_LEVEL_H

//---------------------------------------------------------------------------//
// end CatacombLevel.h
//---------------------------------------------------------------------------//
