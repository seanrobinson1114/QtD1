//---------------------------------------------------------------------------//
//!
//! \file   11BitmapFont.h
//! \author Alex Robinson
//! \brief  11 bitmap font base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef _11_BITMAP_FONT_H
#define _11_BITMAP_FONT_H

// Qt Includes
#include <QVector>

// QtD1 Includes
#include "BitmapFont.h"

namespace QtD1{

//! The 11 bitmap font base class
class _11BitmapFont : public BitmapFont
{

public:
  
  //! Destructor
  ~_11BitmapFont()
  { /* ... */ }

  //! Get the font name
  QString getName() const final override;

  //! Return the font size
  int getSize() const final override;

protected:

  //! Constructor
  _11BitmapFont( const QColor& color = Qt::transparent );
  
private:

  //! The widths of each character
  static const QVector<int> s_widths;

  //! The character order
  static const QVector<int> s_order;
};
  
} // end QtD1 namespace

#endif // end _11_BITMAP_FONT_H

//---------------------------------------------------------------------------//
// end 11BitmapFont.h
//---------------------------------------------------------------------------//
