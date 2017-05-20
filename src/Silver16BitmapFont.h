//---------------------------------------------------------------------------//
//!
//! \file   Silver16BitmapFont.h
//! \author Alex Robinson
//! \brief  The silver 16 bitmap font class declaration
//!
//---------------------------------------------------------------------------//

#ifndef SILVER_16_BITMAP_FONT_H
#define SILVER_16_BITMAP_FONT_H

// Std Lib Includes
#include <memory>

// QtD1 Includes
#include "BitmapFont.h"

namespace QtD1{

//! The Silver 16 bitmap font class
class Silver16BitmapFont : public BitmapFont
{

public:

  //! Get the Silver16BitmapFont instance
  static Silver16BitmapFont* getInstance();

  //! Destructor
  ~Silver16BitmapFont()
  { /* ... */ }

  //! Get the font name
  QString getName() const override;

  //! Return the font size
  int getSize() const override;

private:

  //! Constructor
  Silver16BitmapFont();

  //! The widths of each character
  static const QVector<int> s_widths;

  //! The singleton instance
  static std::unique_ptr<Silver16BitmapFont> s_instance;
};

} // end QtD1 namespace

#endif // end SILVER_16_BITMAP_FONT_H

//---------------------------------------------------------------------------//
// end Silver16BitmapFont.h
//---------------------------------------------------------------------------//
