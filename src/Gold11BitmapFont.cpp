//---------------------------------------------------------------------------//
//!
//! \file   Gold11BitmapFont.cpp
//! \author Alex Robinson
//! \brief  The gold 11 bitmap font class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "Gold11BitmapFont.h"

namespace QtD1{

// Initialize static members
std::unique_ptr<Gold11BitmapFont> Gold11BitmapFont::s_instance;
  
// Constructor
Gold11BitmapFont::Gold11BitmapFont()
  : _11BitmapFont( QColor( 255, 230, 145 ) )
{ /* ... */ }

// Get the Gold11BitmapFont instance
Gold11BitmapFont* Gold11BitmapFont::getInstance()
{
  // Just-in-time initialization
  if( !s_instance )
    s_instance.reset( new Gold11BitmapFont );

  return s_instance.get();
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Gold11BitmapFont.cpp
//---------------------------------------------------------------------------//
