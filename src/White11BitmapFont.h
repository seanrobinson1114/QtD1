//---------------------------------------------------------------------------//
//!
//! \file   White11BitmapFont.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The white 11 bitmap font class declaration
//!
//---------------------------------------------------------------------------//

#ifndef WHITE_11_BITMAP_FONT_H
#define WHITE_11_BITMAP_FONT_H

// Std Lib Includes
#include <memory>

// QtD1 Includes
#include "11BitmapFont.h"

namespace QtD1{

//! The white 11 bitmap font class
class White11BitmapFont : public _11BitmapFont
{

public:

  //! Get the White11BitmapFont instance
  static White11BitmapFont* getInstance();

  //! Destructor
  ~White11BitmapFont()
  { /* ... */ }

private:

  // Constructor
  White11BitmapFont();

  // The singleton instance
  static std::unique_ptr<White11BitmapFont> s_instance;
};

} // end QtD1 namespace

#endif // end WHITE_11_BITMAP_FONT_H

//---------------------------------------------------------------------------//
// end White11BitmapFont.h
//---------------------------------------------------------------------------//
