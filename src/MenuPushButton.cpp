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

// Qt Includes
#include <QMouseEvent>

namespace QtD1{

std::unique_ptr<Sound> MenuPushButton::s_click_sound;

// Constructor
MenuPushButton::MenuPushButton( const QString& raw_button_text,
                                const QString& bitmap_font_name,
                                QWidget* parent )
  : QPushButton( parent )
{
  this->initializeClickSound();

  BitmapText button_text;
  button_text.setFontName( bitmap_font_name );
  button_text.setContainerWidth( 300 );
  button_text.setTextWithNoWrap( raw_button_text );
  button_text.load();

  QIcon button_icon( button_text.getPixmap() );

  this->setIcon( button_icon );
  this->setIconSize( button_text.getPixmap().size() );
  this->resize( button_text.getPixmap().size() );
  this->setFocusProxy( parent );
}

// Mouse click event
void MenuPushButton::mousePressEvent( QMouseEvent* e )
{
  s_click_sound->playSound();
  QPushButton::mousePressEvent( e );
}

// Initialize click sound
void MenuPushButton::initializeClickSound()
{
  if( !s_click_sound )
  {
    s_click_sound.reset( new Sound );
    s_click_sound->setSource( "/sfx/items/titlslct.wav" );
  }
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end MenuPushButton.cpp
//---------------------------------------------------------------------------//
