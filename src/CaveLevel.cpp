//---------------------------------------------------------------------------//
//!
//! \file   CaveLevel.cpp
//! \author Alex Robinson
//! \brief  The cave level class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "CaveLevel.h"

namespace QtD1{

// Initialize static member data
std::shared_ptr<Music> CaveLevel::s_cave_music;

//! Constructor
CaveLevel::CaveLevel( const int number, QObject* parent )
  : Level( parent ),
    d_number( number )
{
  if( !s_cave_music )
  {
    s_cave_music.reset( new Music );
    s_cave_music->setSource( "/music/dlvlc.wav" );
  }

  this->setMusic( s_cave_music );
}

// Get the type
Level::Type CaveLevel::getType() const
{
  return Level::Cave;
}

// Get the number
int CaveLevel::getNumber() const
{
  return d_number;
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end CaveLevel.cpp
//---------------------------------------------------------------------------//
