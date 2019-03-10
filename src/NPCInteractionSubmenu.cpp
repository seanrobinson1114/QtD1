//---------------------------------------------------------------------------//
//!
//! \file   NPCInteractionSubmenu.cpp
//! \author Alex Robinson
//! \brief  The NPC interaction submenu class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <memory>

// Qt Includes
#include <QPainter>

// QtD1 Includes
#include "NPCInteractionSubmenu.h"
#include "UIArtLoader.h"

namespace QtD1{

// The submenu frames
QVector<QPixmap> NPCInteractionSubmenu::s_frames;
  
// Constructor
NPCInteractionSubmenu::NPCInteractionSubmenu( QWidget* parent )
  : QWidget( parent ),
    d_back_button( NULL ),
    d_named_buttons(),
    d_button_connections(),
    d_back_submenu( NULL )
{ 
  // Disable focus borders/outlines on push buttons
  this->setStyleSheet( QString( "QPushButton:focus { border: none; outline: none; }" ) );
}

// Get the submenu frame
QPixmap NPCInteractionSubmenu::getFrame( const NPCInteractionSubmenu::Type type )
{
  // Just-in-time initialization of the frame
  NPCInteractionSubmenu::initializeSubmenuFrame( type );

  return s_frames[type];
}

// Initialize a submenu frame
void NPCInteractionSubmenu::initializeSubmenuFrame( NPCInteractionSubmenu::Type type )
{
  if( s_frames.empty() )
    s_frames.resize( 3 );
  
  if( s_frames[type].width() == 0 )
  {
    switch( type )
    {
      case NPCInteractionSubmenu::Type::Primary:
        NPCInteractionSubmenu::initializePrimarySubmenuFrame();
        break;
      case NPCInteractionSubmenu::Type::Discussion:
        NPCInteractionSubmenu::initializePrimarySubmenuFrame();
        break;
      case NPCInteractionSubmenu::Type::Trade:
        NPCInteractionSubmenu::initializeTradeSubmenuFrame();
        break;
      default:
        qFatal( "The npc interaction submenu type is not supported!" );
    }
  }
}

// Initialize the primary submenu frame
void NPCInteractionSubmenu::initializePrimarySubmenuFrame()
{
  // Load the interaction menu image
  std::unique_ptr<UIArtLoader> ui_art_frame_loader( new UIArtLoader );

  ui_art_frame_loader->setSource( "/ui_art/seldiff.pcx" );
  ui_art_frame_loader->setTransparentColor( QColor( "black" ) );
  ui_art_frame_loader->loadFrames();

  QImage interaction_menu_border_image =
    ui_art_frame_loader->getLoadedFrames().front();

  // Crop the border image
  interaction_menu_border_image =
    interaction_menu_border_image.copy( 274, 55, 351, 215 );
  
  // Stretch the border image
  interaction_menu_border_image =
    interaction_menu_border_image.scaled( interaction_menu_border_image.width()*0.85, interaction_menu_border_image.height()*1.5 );

  // Initialize the border pixmap
  QPixmap& border_pixmap = s_frames[NPCInteractionSubmenu::Type::Primary];
  border_pixmap = QPixmap( interaction_menu_border_image.width()-10,
                           interaction_menu_border_image.height()-2 );
  border_pixmap.fill( QColor( 0, 0, 0, 127 ) );

  // Draw the border image on the pixmap
  QPainter painter( &border_pixmap );
  painter.drawImage( QPoint( 0, 0 ),
                     interaction_menu_border_image,
                     QRect( 3, 0, border_pixmap.width(), border_pixmap.height() ) );

  // Copy the pixmap to the discussion pixmap
  s_frames[NPCInteractionSubmenu::Type::Discussion] = border_pixmap;
}

// Initialize the trade submenu frame
void NPCInteractionSubmenu::initializeTradeSubmenuFrame()
{
  s_frames[NPCInteractionSubmenu::Type::Trade];
}

// Assign a submenu to a named button
void NPCInteractionSubmenu::assignSubmenuToNamedButton(
                                               const QString& button_name,
                                               NPCInteractionSubmenu* submenu )
{
  auto button_it = d_named_buttons.find( button_name );

  if( button_it != d_named_buttons.end() )
  {
    d_button_connections[button_it->second] = submenu;

    QObject::connect( button_it->second, SIGNAL(released()),
                      this, SLOT(handleNamedButtonPushed()) );
  }
  else
  {
    qWarning( "NPCInteractionSubmenu Warning: no button with name %s",
              button_name );
  }
}

// Assign back submenu
void NPCInteractionSubmenu::assignBackSubmenu( NPCInteractionSubmenu* back_submenu )
{
  d_back_submenu = back_submenu;
}

// Set the back button
void NPCInteractionSubmenu::setBackButton( QPushButton* back_button )
{
  if( back_button )
  {
    d_back_button = back_button;

    QObject::connect( back_button, SIGNAL(released()),
                      this, SLOT(handleBackButtonPushed()) );
  }
}

// Set the buttons
void NPCInteractionSubmenu::setNamedButtons(
                          const std::map<QString,QPushButton*>& named_buttons )
{
  d_named_buttons = named_buttons;
}

// Click the back button
void NPCInteractionSubmenu::clickBackButton()
{
  d_back_button->click();
}

// Handle named button pushed
void NPCInteractionSubmenu::handleNamedButtonPushed()
{
  // Get the sender button
  QObject* base_sender_button = QObject::sender();

  QPushButton* sender_button =
    dynamic_cast<QPushButton*>( base_sender_button );

  if( sender_button )
  {
    auto button_connection_it = d_button_connections.find( sender_button );

    if( button_connection_it != d_button_connections.end() )
    {
      emit showSubmenu( button_connection_it->second );
    }
  }
}

// Handle back button pushed
void NPCInteractionSubmenu::handleBackButtonPushed()
{
  if( d_back_submenu )
  {
    emit showSubmenu( d_back_submenu );

    this->resetActiveButton();
  }
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end NPCInteractionSubmenu.cpp
//---------------------------------------------------------------------------//
