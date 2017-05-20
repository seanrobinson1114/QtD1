//---------------------------------------------------------------------------//
//!
//! \file   Gold30BitmapFont.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The gold 30 bitmap font class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GOLD_30_BITMAP_FONT_H
#define GOLD_30_BITMAP_FONT_H

// Std Lib Includes
#include <memory>

// QtD1 Includes
#include "BitmapFont.h"

namespace QtD1{

//! The Gold 30 bitmap font class
class Gold30BitmapFont : public BitmapFont
{

public:

  //! Get the Gold30BitmapFont instance
  static Gold30BitmapFont* getInstance();

  //! Destructor
  ~Gold30BitmapFont()
  { /* ... */ }

  //! Get the font name
  QString getName() const override;

  //! Return the font size
  int getSize() const override;

private:

  //! Constructor
  Gold30BitmapFont();

  //! The widths of each character
  static const QVector<int> s_widths;

  //! The singleton instance
  static std::unique_ptr<Gold30BitmapFont> s_instance;
};

} // end QtD1 namespace

#endif // end GOLD_30_BITMAP_FONT_H

//---------------------------------------------------------------------------//
// end Gold30BitmapFont.h
//---------------------------------------------------------------------------//
