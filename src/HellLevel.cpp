//---------------------------------------------------------------------------//
//!
//! \file   HellLevel.cpp
//! \author Alex Robinson
//! \brief  The hell level class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "HellLevel.h"

namespace QtD1{

// Initialize static member data
std::shared_ptr<Music> HellLevel::s_hell_music;

//! Constructor
HellLevel::HellLevel( const int number, QObject* parent )
  : Level( parent ),
    d_number( number )
{
  if( !s_hell_music )
  {
    s_hell_music.reset( new Music );
    s_hell_music->setSource( "/music/dlvld.wav" );
  }

  this->setMusic( s_hell_music );
}

// Get the type
Level::Type HellLevel::getType() const
{
  return Level::Hell;
}

// Get the number
int HellLevel::getNumber() const
{
  return d_number;
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end HellLevel.cpp
//---------------------------------------------------------------------------//
