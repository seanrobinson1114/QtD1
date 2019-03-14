//---------------------------------------------------------------------------//
//!
//! \file   MenuPushButton.h
//! \author Alex Robinson
//! \brief  The menu push button class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MENU_PUSH_BUTTON_H
#define MENU_PUSH_BUTTON_H

// Std Lib Includes
#include <memory>

// Qt Includes
#include <QPushButton>

// Qtd1 Includes
#include "Sound.h"

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

protected:

  //! Mouse click event
  void mousePressEvent( QMouseEvent* e );

private:
  
  // Initialize s_click_sound (just in time)
  static void initializeClickSound();

  // Sound for clicking menu item
  static std::unique_ptr<Sound> s_click_sound;
};

} // end QtD1 namespace

#endif // end MENU_PUSH_BUTTON_H

//---------------------------------------------------------------------------//
// end MenuPushButton.h
//---------------------------------------------------------------------------//

