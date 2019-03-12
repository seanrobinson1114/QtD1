//---------------------------------------------------------------------------//
//!
//! \file   ControlPanel.cpp
//! \author Sean Robinson, Alex Robinson
//! \brief  The control panel class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <memory>
#include <tuple>

// Qt Includes
#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QPushButton>
#include <QImageReader>
#include <QPainter>

// QtD1 Includes
#include "ControlPanel.h"
#include "Rogue.h"
#include "Sorcerer.h"
#include "Warrior.h"

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
    d_background( NULL ),
    d_hover_display( NULL ),
    d_health_bulb_region( NULL ),
    d_health_bulb( NULL ),
    d_mana_bulb_region( NULL ),
    d_mana_bulb( NULL )
{
  // Load the control panel images
  QImage background_image, health_bulb_full_image, mana_bulb_full_image;
  this->loadControlPanelImages( background_image,
                                health_bulb_full_image,
                                mana_bulb_full_image );

  // Create the background
  d_background = new QLabel( this );
  d_background->setPixmap( QPixmap::fromImage( background_image ) );
  d_background->setFixedSize( background_image.size() );
  this->setFixedSize( d_background->size() );

  // Create the full health bulb
  d_health_bulb_region = new QLabel( d_background );
  d_health_bulb_region->setStyleSheet( QString( "background: transparent" ) );
  d_health_bulb_region->setFixedSize( health_bulb_full_image.size() );
  d_health_bulb_region->move( 97, 0 );
  //d_health_bulb_region->hide();

  // QLabel* test_region_1 = new QLabel( d_background );
  // test_region_1->setStyleSheet( QString( "background: blue" ) );
  // test_region_1->setFixedSize( 84, 88 );
  // test_region_1->move( 97, 0 );

  {
    QPixmap health_bulb_full_pixmap =
      QPixmap::fromImage( health_bulb_full_image );
  
    d_health_bulb = new QLabel( d_health_bulb_region );
    d_health_bulb->setPixmap( health_bulb_full_pixmap );
  }

  // Create the full mana bulb
  d_mana_bulb_region = new QLabel( d_background );
  d_mana_bulb_region->setStyleSheet( QString( "background: transparent" ) );
  d_mana_bulb_region->setFixedSize( mana_bulb_full_image.size() );
  d_mana_bulb_region->move( d_background->width()-177, 0 );
  //d_mana_bulb_region->hide();

  // QLabel* test_region_2 = new QLabel( d_background );
  // test_region_2->setStyleSheet( QString( "background: blue" ) );
  // test_region_2->setFixedSize( 81, 88 );
  // test_region_2->move( d_background->width()-177, 0 );
  
  {
    QPixmap mana_bulb_full_pixmap =
      QPixmap::fromImage( mana_bulb_full_image );
  
    d_mana_bulb = new QLabel( d_mana_bulb_region );
    d_mana_bulb->setPixmap( mana_bulb_full_pixmap );
  }
  
  // Disable focus borders/outlines on push buttons
  this->setStyleSheet( QString( "QPushButton:focus { border: none; outline: none; }" ) );

  this->loadControlPanelButtons();
  this->loadHoverDisplay();
}

// Load the control panel images
void ControlPanel::loadControlPanelImages( QImage& background,
                                           QImage& health_bulb_full,
                                           QImage& mana_bulb_full ) const
{
  // Load the control panel image
  QImage background_image( "/ctrlpan/panel8.cel+levels/towndata/town.pal" );

  // Copy the full bulbs
  health_bulb_full = background_image.copy( 97, 0, 84, 88 );
  mana_bulb_full = background_image.copy( background_image.width()-177, 0, 81, 88 );

  // Load the empty bulbs
  QImageReader raw_bulb_images( "/ctrlpan/p8bulbs.cel+levels/towndata/town.pal" );

  QImage health_bulb_empty = raw_bulb_images.read().copy( 1, 0, 84, 88 );

  raw_bulb_images.jumpToNextImage();

  QImage mana_bulb_empty = raw_bulb_images.read().copy( 0, 0, 81, 88 );

  // Draw the background image and the empty bulbs on the background
  background = QImage( background_image.size(), QImage::Format_ARGB32 );
  background.fill( Qt::transparent );
  
  QPainter painter( &background );
  painter.drawImage( QPoint( 0, 16 ),
                     background_image,
                     QRect( 0, 16, background_image.width(), background_image.height()-16 ) );
  painter.drawImage( QPoint( 97, 0 ),
                     health_bulb_empty,
                     health_bulb_empty.rect() );
  painter.drawImage( QPoint( background_image.width()-177, 0 ),
                     mana_bulb_empty,
                     mana_bulb_empty.rect() );
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

// Update character health
void ControlPanel::updateCharacterHealth( const int health, const int max_health )
{
  double health_fraction = (double)health/max_health;
  int health_bulb_y_pos = d_health_bulb->height()*(1-health_fraction);
  
  d_health_bulb_region->show();
  d_health_bulb->move( 0, -health_bulb_y_pos );
  d_health_bulb_region->move( d_health_bulb_region->x(), health_bulb_y_pos );
}

// Update character mana
void ControlPanel::updateCharacterMana( const int mana, const int max_mana )
{
  double mana_fraction = (double)mana/max_mana;
  int mana_bulb_y_pos = d_mana_bulb->height()*(1-mana_fraction);

  d_mana_bulb_region->show();
  d_mana_bulb->move( 0, -mana_bulb_y_pos );
  d_mana_bulb_region->move( d_mana_bulb_region->x(), mana_bulb_y_pos );
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
  (*panel_button)->setAutoDefault( false );
  (*panel_button)->setStyleSheet( "background: transparent" );
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
