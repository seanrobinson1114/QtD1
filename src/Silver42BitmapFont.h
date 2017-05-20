//---------------------------------------------------------------------------//
//!
//! \file   Silver42BitmapFont.h
//! \author Alex Robinson
//! \brief  The silver 42 bitmap font class declaration
//!
//---------------------------------------------------------------------------//

#ifndef SILVER_42_BITMAP_FONT_H
#define SILVER_42_BITMAP_FONT_H

// Std Lib Includes
#include <memory>

// QtD1 Includes
#include "BitmapFont.h"

namespace QtD1{

//! The Silver 42 bitmap font class
class Silver42BitmapFont : public BitmapFont
{

public:

  //! Get the Silver42BitmapFont instance
  static Silver42BitmapFont* getInstance();

  //! Destructor
  ~Silver42BitmapFont()
  { /* ... */ }

  //! Get the font name
  QString getName() const override;

  //! Return the font size
  int getSize() const override;

private:

  //! Constructor
  Silver42BitmapFont();

  //! The singleton instance
  static std::unique_ptr<Silver42BitmapFont> s_instance;

  //! The widths of each character
  static const QVector<int> s_widths;
};
  
} // end QtD1 namespace

#endif // end SILVER_42_BITMAP_FONT_H

//---------------------------------------------------------------------------//
// end Silver42BitmapFont.h
//---------------------------------------------------------------------------//
