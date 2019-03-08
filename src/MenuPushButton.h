//---------------------------------------------------------------------------//
//!
//! \file   MenuPushButton.h
//! \author Alex Robinson
//! \brief  The menu push button class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MENU_PUSH_BUTTON_H
#define MENU_PUSH_BUTTON_H

// Qt Includes
#include <QPushButton>

namespace QtD1{

//! The menu push button
class MenuPushButton : public QPushButton
{
  Q_OBJECT

public:

  //! Constructor
  MenuPushButton( const QString& button_text,
                  const QString& bitmap_font_name,
                  QWidget* parent = 0 );

  //! Destructor
  ~MenuPushButton()
  { /* ... */ }
};

} // end QtD1 namespace

#endif // end MENU_PUSH_BUTTON_H

//---------------------------------------------------------------------------//
// end MenuPushButton.h
//---------------------------------------------------------------------------//

