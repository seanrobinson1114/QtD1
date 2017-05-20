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
#include "BitmapFont.h"

namespace QtD1{

//! The White 11 bitmap font class
class White11BitmapFont : public BitmapFont
{

public:

  //! Get the White11BitmapFont instance
  static White11BitmapFont* getInstance();

  //! Destructor
  ~White11BitmapFont()
  { /* ... */ }

  //! Get the font name
  QString getName() const override;

  //! Return the font size
  int getSize() const override;

private:

  //! Constructor
  White11BitmapFont();

  //! The singleton instance
  static std::unique_ptr<White11BitmapFont> s_instance;

  //! The widths of each character
  static const QVector<int> s_widths;

  //! The character order
  static const QVector<int> s_order;
};

} // end QtD1 namespace

#endif // end WHITE_11_BITMAP_FONT_H

//---------------------------------------------------------------------------//
// end White11BitmapFont.h
//---------------------------------------------------------------------------//
