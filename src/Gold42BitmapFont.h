//---------------------------------------------------------------------------//
//!
//! \file   Gold42BitmapFont.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The gold 42 bitmap font class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GOLD_42_BITMAP_FONT_H
#define GOLD_42_BITMAP_FONT_H

// Std Lib Includes
#include <memory>

// QtD1 Includes
#include "BitmapFont.h"

namespace QtD1{

//! The Gold 42 bitmap font class
class Gold42BitmapFont : public BitmapFont
{

public:

  //! Get the Gold42BitmapFont instance
  static Gold42BitmapFont* getInstance();

  //! Destructor
  ~Gold42BitmapFont()
  { /* ... */ }

  //! Get the font name
  QString getName() const override;

  //! Return the font size
  int getSize() const override;

private:

  //! Constructor
  Gold42BitmapFont();

  //! The singleton instance
  static std::unique_ptr<Gold42BitmapFont> s_instance;

  //! The widths of each character
  static const QVector<int> s_widths;
};

} // end QtD1 namespace

#endif // end GOLD_42_BITMAP_FONT_H

//---------------------------------------------------------------------------//
// end Gold42BitmapFont.h
//---------------------------------------------------------------------------//
