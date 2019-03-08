//---------------------------------------------------------------------------//
//!
//! \file   MenuPushButton.cpp
//! \author Alex Robinson
//! \brief  The menu push button class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "MenuPushButton.h"
#include "BitmapText.h"

namespace QtD1{

// Constructor
MenuPushButton::MenuPushButton( const QString& raw_button_text,
                                const QString& bitmap_font_name,
                                QWidget* parent )
  : QPushButton( parent )
{
  BitmapText button_text;
  button_text.setFontName( bitmap_font_name );
  button_text.setContainerWidth( 300 );
  button_text.setTextWithNoWrap( raw_button_text );
  button_text.load();

  QIcon button_icon( button_text.getPixmap() );

  this->setIcon( button_icon );
  this->setIconSize( button_text.getPixmap().size() );
  this->resize( button_text.getPixmap().size() );
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end MenuPushButton.cpp
//---------------------------------------------------------------------------//
