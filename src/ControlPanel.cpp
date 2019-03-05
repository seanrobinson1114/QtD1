//---------------------------------------------------------------------------//
//!
//! \file   ControlPanel.cpp
//! \author Sean Robinson, Alex Robinson
//! \brief  The control panel class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "ControlPanel.h"
#include "Rogue.h"
#include "Sorcerer.h"
#include "Warrior.h"

// Std Lib Includes
#include <memory>
#include <tuple>

// Qt Includes
#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QPushButton>
#include <QImageReader>

namespace QtD1{

// Initialize static member data
const QSize ControlPanel::s_active_button_size( 71, 19 );
const QSize ControlPanel::s_hidden_button_size( 0, 0 );

//! Constructor
ControlPanel::ControlPanel( QWidget* parent )
  : QWidget( parent ),
    d_char_button( NULL ),
    d_quest_button( NULL ),
    d_menu_button( NULL ),
    d_inv_button( NULL ),
    d_spell_button( NULL ),
    d_hover_display( NULL )
{
  // Load the control panel image
  QImage background_image( "/ctrlpan/panel8.cel+levels/towndata/town.pal" );
  QLabel* control_panel_image = new QLabel( this );
  control_panel_image->setPixmap( QPixmap::fromImage( background_image ) );
  control_panel_image->setFixedSize( background_image.size() );
  this->setFixedSize( control_panel_image->size() );

  this->loadControlPanelButtons();
  this->loadHoverDisplay();
}

// Check status of the char button and emit signal
void ControlPanel::toggleCharacterStats()
{
  if( d_char_button->iconSize() == QSize( 0, 0 ) )
  {
    d_char_button->setIconSize( s_active_button_size );
    d_quest_button->setIconSize( s_hidden_button_size );
    emit showCharacterStats();
    emit hideQuestLog();
    emit hideGameMenu();
  }
  else
  {
    d_char_button->setIconSize( s_hidden_button_size );
    emit hideCharacterStats();
  }
}

// Check the status of quest button and emit signal
void ControlPanel::toggleQuestLog()
{
  if( d_quest_button->iconSize() == QSize( 0, 0 ) )
  {
    d_quest_button->setIconSize( s_active_button_size );
    d_char_button->setIconSize( s_hidden_button_size );
    emit showQuestLog();
    emit hideCharacterStats();
    emit hideGameMenu();
  }
  else
  {
    d_quest_button->setIconSize( s_hidden_button_size );
    emit hideQuestLog();
  }
}

//! Check the status of the menu button and emit signal
void ControlPanel::toggleGameMenu()
{
    d_menu_button->setIconSize( s_active_button_size );
    d_char_button->setIconSize( s_hidden_button_size );
    d_quest_button->setIconSize( s_hidden_button_size );
    d_inv_button->setIconSize( s_hidden_button_size );
    d_spell_button->setIconSize( s_hidden_button_size );
    d_menu_button->setShortcut( tr( "" ) );
    emit showGameMenu();
    emit hideCharacterStats();
    emit hideQuestLog();
    emit hideInventory();
    emit hideSpellBook();
}

//! Hide the activated game menu button
void ControlPanel::hideMenuButton()
{
  d_menu_button->setIconSize( s_hidden_button_size );
  d_menu_button->setShortcut( tr( "Esc" ) );
}

//! Check the status of the inv button and emit signal
void ControlPanel::toggleInventory()
{
  if( d_inv_button->iconSize() == QSize( 0, 0 ) )
  {
    d_inv_button->setIconSize( s_active_button_size );
    d_spell_button->setIconSize( s_hidden_button_size );
    emit showInventory();
    emit hideSpellBook();
    emit hideGameMenu();
  }
  else
  {
    d_inv_button->setIconSize( s_hidden_button_size );
    emit hideInventory();
  }
}

//! Check the status of the spell button and emit signal
void ControlPanel::toggleSpellBook()
{
  if( d_spell_button->iconSize() == QSize( 0, 0 ) )
  {
    d_spell_button->setIconSize( s_active_button_size );
    d_inv_button->setIconSize( s_hidden_button_size );
    emit showSpellBook();
    emit hideInventory();
    emit hideGameMenu();
  }
  else
  {
    d_spell_button->setIconSize( s_hidden_button_size );
    emit hideSpellBook();
  }
}

// Change object description display
void ControlPanel::changeObjectDescriptionDisplay( QString objectDescription )
{
  //std::cout << objectDescription.toUtf8().constData() << std::endl;
  d_hover_display->setText( objectDescription );
}

// Activate the control panel focus shortcuts
void ControlPanel::activateFocusShortcuts()
{
  d_char_button->setShortcut( tr( "c" ) );
  d_quest_button->setShortcut( tr( "q" ) );
  d_menu_button->setShortcut( tr( "Esc" ) );
  d_inv_button->setShortcut( tr( "i" ) );
  d_spell_button->setShortcut( tr( "s" ) );
}

// Deactivate the control panel focus shortcuts
void ControlPanel::deactivateFocusShortcuts()
{
  d_char_button->setShortcut( tr( "" ) );
  d_quest_button->setShortcut( tr( "" ) );
  d_menu_button->setShortcut( tr( "" ) );
  d_inv_button->setShortcut( tr( "" ) );
  d_spell_button->setShortcut( tr( "" ) );
}

void ControlPanel::loadControlPanelButtons()
{
  // Create the tab buttons
  QImageReader panel_button_reader( "/ctrlpan/panel8bu.cel+levels/towndata/town.pal" );

  this->initializeControlPanelButton( &d_char_button, panel_button_reader.read() );
  panel_button_reader.jumpToNextImage();

  this->initializeControlPanelButton( &d_quest_button, panel_button_reader.read() );
  panel_button_reader.jumpToImage( 3 );

  this->initializeControlPanelButton( &d_menu_button, panel_button_reader.read() );
  panel_button_reader.jumpToNextImage();

  this->initializeControlPanelButton( &d_inv_button, panel_button_reader.read() );
  panel_button_reader.jumpToNextImage();

  this->initializeControlPanelButton( &d_spell_button, panel_button_reader.read() );
  panel_button_reader.jumpToNextImage();

  // Connect buttons to signals
  this->connectButtonsToSignals();

  // Move the buttons to the correct locations
  d_char_button->move( 10, 24 );
  d_quest_button->move( 10, 50 );
  d_menu_button->move( 10, 116 );
  d_inv_button->move( 560, 24 );
  d_spell_button->move( 560, 50 );
}

void ControlPanel::loadHoverDisplay()
{
  d_hover_display = new QLabel( this );
  d_hover_display->setFocusProxy( this );
  d_hover_display->resize( 250, 65 );
  d_hover_display->setStyleSheet( QString( "background: transparent; color: white" ) );
  d_hover_display->setAlignment( Qt::AlignCenter );
  d_hover_display->setWordWrap( true );
  d_hover_display->move( 200, 58 );
}

// Initialize tab button
void ControlPanel::initializeControlPanelButton( QPushButton** panel_button,
                                     const QImage& image )
{
  QIcon panel_icon( QPixmap::fromImage( image ) );

  *panel_button = new QPushButton( this );
  (*panel_button)->setFocusProxy( this );
  (*panel_button)->setStyleSheet( QString( "background: transparent" ) );
  (*panel_button)->setIcon( panel_icon );
  (*panel_button)->setIconSize( s_hidden_button_size );
  (*panel_button)->resize( s_active_button_size );
}

// Connect control panel buttons to signals
void ControlPanel::connectButtonsToSignals()
{
  // Connect the buttons clicked signal with our custom signals and add shortcuts
  QObject::connect( d_char_button, SIGNAL( pressed() ), this, SLOT( toggleCharacterStats() ) );
  QObject::connect( d_quest_button, SIGNAL( pressed() ), this, SLOT( toggleQuestLog() ) );
  QObject::connect( d_menu_button, SIGNAL( pressed() ), this, SLOT( toggleGameMenu() ) );
  QObject::connect( d_inv_button, SIGNAL( pressed() ), this, SLOT( toggleInventory() ) );
  QObject::connect( d_spell_button, SIGNAL( pressed() ), this, SLOT( toggleSpellBook() ) );

  this->activateFocusShortcuts();
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end ControlPanel.h
//---------------------------------------------------------------------------//
