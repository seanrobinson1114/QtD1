//---------------------------------------------------------------------------//
//!
//! \file   Gold16BitmapFont.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The gold 16 bitmap font class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GOLD_16_BITMAP_FONT_H
#define GOLD_16_BITMAP_FONT_H

// Std Lib Includes
#include <memory>

// QtD1 Includes
#include "BitmapFont.h"

namespace QtD1{

//! The Gold 16 bitmap font class
class Gold16BitmapFont : public BitmapFont
{

public:

  //! Get the Gold16BitmapFont instance
  static Gold16BitmapFont* getInstance();

  //! Destructor
  ~Gold16BitmapFont()
  { /* ... */ }

  //! Get the font name
  QString getName() const override;

  //! Return the font size
  int getSize() const override;

private:

  //! Constructor
  Gold16BitmapFont();

  //! The widths of each character
  static const QVector<int> s_widths;

  //! The singleton instance
  static std::unique_ptr<Gold16BitmapFont> s_instance;
};

} // end QtD1 namespace

#endif // end GOLD_16_BITMAP_FONT_H

//---------------------------------------------------------------------------//
// end Gold16BitmapFont.h
//---------------------------------------------------------------------------//
