//---------------------------------------------------------------------------//
//!
//! \file   Blue11BitmapFont.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The blue 11 bitmap font class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "Blue11BitmapFont.h"

namespace QtD1 {

// Initialize static members
std::unique_ptr<Blue11BitmapFont> Blue11BitmapFont::s_instance;
  
// Constructor
Blue11BitmapFont::Blue11BitmapFont()
  : _11BitmapFont( QColor( 154, 117, 255 ) )
{ /* ... */ }

// Get the Blue11BitmapFont instance
Blue11BitmapFont* Blue11BitmapFont::getInstance()
{
  // Just-in-time initialization
  if( !s_instance )
    s_instance.reset( new Blue11BitmapFont );

  return s_instance.get();
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Blue11BitmapFont.cpp
//---------------------------------------------------------------------------//
