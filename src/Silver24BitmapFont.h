//---------------------------------------------------------------------------//
//!
//! \file   Silver24BitmapFont.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The silver 24 bitmap font class declaration
//!
//---------------------------------------------------------------------------//

#ifndef SILVER_24_BITMAP_FONT_H
#define SILVER_24_BITMAP_FONT_H

// Std Lib Includes
#include <memory>

// QtD1 Includes
#include "BitmapFont.h"

namespace QtD1{

//! The Silver 24 bitmap font class
class Silver24BitmapFont : public BitmapFont
{

public:

  //! Get the Silver24BitmapFont instance
  static Silver24BitmapFont* getInstance();

  //! Destructor
  ~Silver24BitmapFont()
  { /* ... */ }

  //! Get the font name
  QString getName() const override;

  //! Return the font size
  int getSize() const override;

private:

  //! Constructor
  Silver24BitmapFont();

  //! The widths of each character
  static const QVector<int> s_widths;

  //! The singleton instance
  static std::unique_ptr<Silver24BitmapFont> s_instance;
};

} // end QtD1 namespace

#endif // end SILVER_24_BITMAP_FONT_H

//---------------------------------------------------------------------------//
// end Silver24BitmapFont.h
//---------------------------------------------------------------------------//
