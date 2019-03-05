//---------------------------------------------------------------------------//
//!
//! \file   Gold11BitmapFont.h
//! \author Alex Robinson
//! \brief  The gold 11 bitmap font class definition
//!
//---------------------------------------------------------------------------//

#ifndef GOLD_11_BITMAP_FONT_H
#define GOLD_11_BITMAP_FONT_H

// Std Lib Includes
#include <memory>

// QtD1 Includes
#include "11BitmapFont.h"

namespace QtD1{

//! The gold 11 bitmap font class
class Gold11BitmapFont : public _11BitmapFont
{

public:

  //! Get the gold 11 bitmap font
  static Gold11BitmapFont* getInstance();

  //! Destructor
  ~Gold11BitmapFont()
  { /* ... */ }

private:

  // Constructor
  Gold11BitmapFont();

  // The singleton instance
  static std::unique_ptr<Gold11BitmapFont> s_instance;
};
  
} // end QtD1 namespace

#endif // end GOLD_11_BITMAP_FONT_H

//---------------------------------------------------------------------------//
// end Gold11BitmapFont.h
//---------------------------------------------------------------------------//
