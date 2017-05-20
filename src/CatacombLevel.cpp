//---------------------------------------------------------------------------//
//!
//! \file   CatacombLevel.cpp
//! \author Alex Robinson
//! \brief  The catacomb level class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "CatacombLevel.h"

namespace QtD1{

// Initialize static member data
std::shared_ptr<Music> CatacombLevel::s_catacomb_music;

//! Constructor
CatacombLevel::CatacombLevel( const int number, QObject* parent )
  : Level( parent ),
    d_number( number )
{
  if( !s_catacomb_music )
  {
    s_catacomb_music.reset( new Music );
    s_catacomb_music->setSource( "/music/dlvlb.wav" );
  }

  this->setMusic( s_catacomb_music );
}

// Get the type
Level::Type CatacombLevel::getType() const
{
  return Level::Catacomb;
}

// Get the number
int CatacombLevel::getNumber() const
{
  return d_number;
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end CatacombLevel.cpp
//---------------------------------------------------------------------------//
