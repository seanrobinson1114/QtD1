//---------------------------------------------------------------------------//
//!
//! \file   Blue11BitmapFont.h
//! \author Alex Robinson
//! \brief  The blue 11 bitmap font class declaration
//!
//---------------------------------------------------------------------------//

#ifndef BLUE_11_BITMAP_FONT_H
#define BLUE_11_BITMAP_FONT_H

// Std Lib Includes
#include <memory>

// QtD1 Includes
#include "11BitmapFont.h"

namespace QtD1{

//! The blue 11 bitmap font class
class Blue11BitmapFont : public _11BitmapFont
{

public:

  //! Get the Blue11BitmapFont instance
  static Blue11BitmapFont* getInstance();

  //! Destructor
  ~Blue11BitmapFont()
  { /* ... */ }

private:

  // Constructor
  Blue11BitmapFont();

  // The singleton instance
  static std::unique_ptr<Blue11BitmapFont> s_instance;
};
  
} // end QtD1 namespace

#endif // end BLUE_11_BITMAP_FONT_H

//---------------------------------------------------------------------------//
// end Blue11BitmapFont.h
//---------------------------------------------------------------------------//
