//---------------------------------------------------------------------------//
//!
//! \file   White11BitmapFont.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The white 11 bitmap font class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "White11BitmapFont.h"

namespace QtD1 {

// Initialize static members
std::unique_ptr<White11BitmapFont> White11BitmapFont::s_instance;
  
// Constructor
White11BitmapFont::White11BitmapFont()
  : _11BitmapFont()
{ /* ... */ }

// Get the White11BitmapFont instance
White11BitmapFont* White11BitmapFont::getInstance()
{
  // Just-in-time initialization
  if( !s_instance )
    s_instance.reset( new White11BitmapFont );

  return s_instance.get();
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end White11BitmapFont.cpp
//---------------------------------------------------------------------------//
