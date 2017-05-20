//---------------------------------------------------------------------------//
//!
//! \file   Gold45BitmapFont.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The gold 45 bitmap font class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GOLD_45_BITMAP_FONT_H
#define GOLD_45_BITMAP_FONT_H

// Std Lib Includes
#include <memory>

// QtD1 Includes
#include "BitmapFont.h"

namespace QtD1{

//! The Gold 45 bitmap font class
class Gold45BitmapFont : public BitmapFont
{

public:

  //! Get the Gold45BitmapFont instance
  static Gold45BitmapFont* getInstance();

  //! Destructor
  ~Gold45BitmapFont()
  { /* ... */ }

  //! Get the font name
  QString getName() const override;

  //! Return the font size
  int getSize() const override;

private:

  //! Constructor
  Gold45BitmapFont();

  //! The singleton instance
  static std::unique_ptr<Gold45BitmapFont> s_instance;

  //! The widths of each character
  static const QVector<int> s_widths;

  //! The character order
  static const QVector<int> s_order;
};

} // end QtD1 namespace

#endif // end GOLD_45_BITMAP_FONT_H

//---------------------------------------------------------------------------//
// end Gold45BitmapFont.h
//---------------------------------------------------------------------------//
