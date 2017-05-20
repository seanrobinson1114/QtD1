//---------------------------------------------------------------------------//
//!
//! \file   Silver30BitmapFont.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The silver 30 bitmap font class declaration
//!
//---------------------------------------------------------------------------//

#ifndef silver_30_BITMAP_FONT_H
#define SILVER_30_BITMAP_FONT_H

// Std Lib Includes
#include <memory>

// QtD1 Includes
#include "BitmapFont.h"

namespace QtD1{

//! The Silver 30 bitmap font class
class Silver30BitmapFont : public BitmapFont
{

public:

  //! Get the Silver30BitmapFont instance
  static Silver30BitmapFont* getInstance();

  //! Destructor
  ~Silver30BitmapFont()
  { /* ... */ }

  //! Get the font name
  QString getName() const override;

  //! Return the font size
  int getSize() const override;

private:

  //! Constructor
  Silver30BitmapFont();

  //! The widths of each character
  static const QVector<int> s_widths;

  //! The singleton instance
  static std::unique_ptr<Silver30BitmapFont> s_instance;
};

} // end QtD1 namespace

#endif // end SILVER_30_BITMAP_FONT_H

//---------------------------------------------------------------------------//
// end Silver30BitmapFont.h
//---------------------------------------------------------------------------//
