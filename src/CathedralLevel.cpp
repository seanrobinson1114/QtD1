//---------------------------------------------------------------------------//
//!
//! \file   CathedralLevel.cpp
//! \author Alex Robinson
//! \brief  The cathedral level class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "CathedralLevel.h"

namespace QtD1{

// Initialize static member data
std::shared_ptr<Music> CathedralLevel::s_cathedral_music;

//! Constructor
CathedralLevel::CathedralLevel( const int number, QObject* parent )
  : Level( parent ),
    d_number( number )
{
  if( !s_cathedral_music )
  {
    s_cathedral_music.reset( new Music );
    s_cathedral_music->setSource( "/music/dlvla.wav" );
  }

  this->setMusic( s_cathedral_music );
}

// Get the type
Level::Type CathedralLevel::getType() const
{
  return Level::Cathedral;
}

// Get the number
int CathedralLevel::getNumber() const
{
  return d_number;
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end CathedralLevel.cpp
//---------------------------------------------------------------------------//
