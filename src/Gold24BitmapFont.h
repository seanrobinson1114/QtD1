//---------------------------------------------------------------------------//
//!
//! \file   Gold24BitmapFont.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The gold 24 bitmap font class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GOLD_24_BITMAP_FONT_H
#define GOLD_24_BITMAP_FONT_H

// Std Lib Includes
#include <memory>

// QtD1 Includes
#include "BitmapFont.h"

namespace QtD1{

//! The Gold 24 bitmap font class
class Gold24BitmapFont : public BitmapFont
{

public:

  //! Get the Gold24BitmapFont instance
  static Gold24BitmapFont* getInstance();

  //! Destructor
  ~Gold24BitmapFont()
  { /* ... */ }

  //! Get the font name
  QString getName() const override;

  //! Return the font size
  int getSize() const override;

private:

  //! Constructor
  Gold24BitmapFont();

  //! The widths of each character
  static const QVector<int> s_widths;

  //! The singleton instance
  static std::unique_ptr<Gold24BitmapFont> s_instance;
};

} // end QtD1 namespace

#endif // end GOLD_24_BITMAP_FONT_H

//---------------------------------------------------------------------------//
// end Gold24BitmapFont.h
//---------------------------------------------------------------------------//
