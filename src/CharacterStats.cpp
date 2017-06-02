//---------------------------------------------------------------------------//
//!
//! \file   CharacterStats.cpp
//! \author Sean Robinson, Alex Robinson
//! \brief  The character stats menu class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <utility>

// Qt Includes
#include <QImageReader>
#include <QShowEvent>

// QtD1 Includes
#include "CharacterStats.h"
#include "Character.h"

namespace QtD1{

// Constructor
CharacterStats::CharacterStats( Character* character, QWidget* parent )
  : QWidget( parent ),
    d_character( character )
{
  // Load the character stats menu image
  QImage background_image( "/data/char.cel+levels/towndata/town.pal" );
  QLabel* character_stats_image = new QLabel( this );
  character_stats_image->setPixmap( QPixmap::fromImage( background_image ) );
  character_stats_image->setFixedSize( background_image.size() );
  this->setFixedSize( character_stats_image->size() );
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end CharacterStats.cpp
//---------------------------------------------------------------------------//
