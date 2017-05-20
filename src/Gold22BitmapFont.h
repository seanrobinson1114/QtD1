//---------------------------------------------------------------------------//
//!
//! \file   Gold22BitmapFont.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The gold 22 bitmap font class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GOLD_22_BITMAP_FONT_H
#define GOLD_22_BITMAP_FONT_H

// Std Lib Includes
#include <memory>

// QtD1 Includes
#include "BitmapFont.h"

namespace QtD1{

//! The Gold 22 bitmap font class
class Gold22BitmapFont : public BitmapFont
{

public:

  //! Get the Gold22BitmapFont instance
  static Gold22BitmapFont* getInstance();

  //! Destructor
  ~Gold22BitmapFont()
  { /* ... */ }

  //! Get the font name
  QString getName() const override;

  //! Return the font size
  int getSize() const override;

private:

  //! Constructor
  Gold22BitmapFont();

  //! The singleton instance
  static std::unique_ptr<Gold22BitmapFont> s_instance;

  //! The widths of each character
  static const QVector<int> s_widths;

  //! The character order
  static const QVector<int> s_order;
};

} // end QtD1 namespace

#endif // end GOLD_22_BITMAP_FONT_H

//---------------------------------------------------------------------------//
// end Gold22BitmapFont.h
//---------------------------------------------------------------------------//
