//---------------------------------------------------------------------------//
//!
//! \file   NPCInteractionMenu.cpp
//! \author Alex Robinson
//! \brief  The NPC interaction menu class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <memory>

// QtD1 Includes
#include "NPCInteractionMenu.h"
#include "UIArtLoader.h"
#include "BitmapText.h"
#include "MenuPushButton.h"
#include "SmallPentSpinMenuPushButton.h"
#include "PentSpinMenuPushButtonBox.h"
#include "QuestPentSpinMenuPushButtonBox.h"

namespace QtD1{

// Constructor
NPCInteractionMenu::NPCInteractionMenu( const QString& npc_name,
                                        const QString& interaction_menu_title_text,
                                        const QString& exit_menu_text,
                                        QWidget* parent )
  : QWidget( parent ),
    d_primary_menu( NULL ),
    d_primary_menu_button_box( NULL ),
    d_exit_button( NULL ),
    d_talk_menu( NULL ),
    d_talk_menu_button_box( NULL ),
    d_go_back_button( NULL )
{
  // Disable focus borders/outlines on push buttons
  this->setStyleSheet( QString( "QPushButton:focus { border: none; outline: none; }" ) );
  
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
  
  // Create the interaction menu background
  QLabel* interaction_menu_background = new QLabel( this );
  interaction_menu_background->setFixedSize( interaction_menu_border_image.size() );
  {
    QPixmap background( interaction_menu_border_image.width()-10,
                        interaction_menu_border_image.height()-2 );
    background.fill( QColor( 0, 0, 0, 127 ) );
    
    interaction_menu_background->setPixmap( background );
    interaction_menu_background->setAlignment( Qt::AlignCenter );
  }
    
  // Create the interaction menu border
  QLabel* interaction_menu_border = new QLabel( interaction_menu_background );
  interaction_menu_border->setPixmap( QPixmap::fromImage( interaction_menu_border_image ) );
  interaction_menu_border->setFixedSize( interaction_menu_border_image.size() );
  interaction_menu_border->move( 3, 0 );

  // Move the interaction menu to the correct location
  this->setFixedSize( interaction_menu_border->size() );
  this->move( 427, 125 );

  // Create the primary menu parent
  d_primary_menu = new QLabel( interaction_menu_background );
  d_primary_menu->setStyleSheet( QString( "background: transparent" ) );
  d_primary_menu->setFixedSize( QSize( interaction_menu_border_image.width()-13, interaction_menu_border_image.height()-7 ) );
  d_primary_menu->move( 7, 3 );
  
  // Create the primary title region
  {
    QLabel* title_region = new QLabel( d_primary_menu );

    BitmapText title_text;
    title_text.setFontName( "QtD1Gold11" );
    title_text.setContainerWidth( 200 );
    title_text.setTextWithNoWrap( interaction_menu_title_text );
    title_text.load();

    title_region->setStyleSheet( QString( "background: transparent" ) );
    title_region->setFixedSize( QSize( d_primary_menu->width(), 50 ) );
    title_region->setAlignment( Qt::AlignCenter );
    title_region->setPixmap( title_text.getPixmap() );
  }

  // Create the prompt region
  {
    QLabel* prompt_region = new QLabel( d_primary_menu );

    BitmapText prompt_text;
    prompt_text.setFontName( "QtD1Gold11" );
    prompt_text.setContainerWidth( 200 );
    prompt_text.setTextWithNoWrap( "Would you like to:" );
    prompt_text.load();

    prompt_region->setStyleSheet( QString( "background: transparent" ) );
    prompt_region->setFixedSize( QSize( interaction_menu_border_image.width()-13, 50 ) );
    prompt_region->setAlignment( Qt::AlignHCenter | Qt::AlignBottom );
    prompt_region->setPixmap( prompt_text.getPixmap() );
    prompt_region->move( 0, 51 );
  }

  // Create the primary menu button box
  d_primary_menu_button_box = new PentSpinMenuPushButtonBox( d_primary_menu );
  d_primary_menu_button_box->setFocusProxy( d_primary_menu );

  // Create the talk menu button
  {
    SmallPentSpinMenuPushButton* talk_menu_button =
      new SmallPentSpinMenuPushButton( QString("Talk to ") + npc_name,
                                       "QtD1Blue11",
                                       d_primary_menu_button_box );
    talk_menu_button->setStyleSheet( QString( "background: transparent" ) );

    // Add the button to the button box
    d_primary_menu_button_box->addButton( talk_menu_button );
    d_primary_menu_button_box->move( (d_primary_menu->width()-d_primary_menu_button_box->width())/2, 150 );

    QObject::connect( talk_menu_button, SIGNAL(released()),
                      this, SLOT(showTalkMenu()) );
  }
  
  // Create the exit button
  {
    d_exit_button = new MenuPushButton( exit_menu_text,
                                        "QtD1White11",
                                        d_primary_menu );
    d_exit_button->setStyleSheet( QString( "background: transparent" ) );
    d_exit_button->move( (d_primary_menu->width()-d_exit_button->width())/2, 250 );
    d_exit_button->raise();

    QObject::connect( d_exit_button, SIGNAL(pressed()),
                      this, SIGNAL(exit()) );
  }

  // Create the talk menu parent
  d_talk_menu = new QLabel( interaction_menu_background );
  d_talk_menu->setStyleSheet( QString( "background: transparent" ) );
  d_talk_menu->setFixedSize( d_primary_menu->size() );
  d_talk_menu->move( d_primary_menu->pos() );
  d_talk_menu->hide();

  // Create the talk menu title region
  {
    QLabel* title_region = new QLabel( d_talk_menu );

    BitmapText title_text;
    title_text.setFontName( "QtD1Gold11" );
    title_text.setContainerWidth( 200 );
    title_text.setTextWithNoWrap( QString("Talk to ") + npc_name );
    title_text.load();

    title_region->setStyleSheet( QString( "background: transparent" ) );
    title_region->setFixedSize( QSize( d_talk_menu->width(), 50 ) );
    title_region->setAlignment( Qt::AlignCenter );
    title_region->setPixmap( title_text.getPixmap() );
  }

  // Create the talk buttons box
  d_talk_menu_button_box = new QuestPentSpinMenuPushButtonBox( d_talk_menu );
  d_talk_menu_button_box->setFocusProxy( d_talk_menu );

  QObject::connect( d_talk_menu_button_box, SIGNAL(questSelected(const Quest::Type)),
                    this, SIGNAL(discussQuest(const Quest::Type)) );

  // Create the gossip button
  {
    SmallPentSpinMenuPushButton* gossip_button =
      new SmallPentSpinMenuPushButton( "Gossip",
                                       "QtD1Blue11",
                                       d_talk_menu_button_box );
    gossip_button->setStyleSheet( QString( "background: transparent" ) );

    // Add the button to the talk menu button box
    d_talk_menu_button_box->addButton( gossip_button );

    QObject::connect( gossip_button, SIGNAL(released()),
                      this, SIGNAL(gossip()) );

    // Move the talk buttons box
    this->recenterTalkMenuButtonBox();
  }

  // Create the back button
  {
    d_go_back_button = new MenuPushButton( "Back",
                                           "QtD1White11",
                                           d_talk_menu );
    d_go_back_button->setStyleSheet( QString( "background: transparent" ) );
    d_go_back_button->move( (d_primary_menu->width()-d_go_back_button->width())/2, 280 );
    d_go_back_button->raise();
    
    QObject::connect( d_go_back_button, SIGNAL(pressed()),
                      this, SLOT(showPrimaryMenu()) );
  }
  
  // // Load the scroll button image
  // QImage scroll_buttons( "/ui_art/sb_arrow.pcx" );
  
  // // Load the scroll bar image
  // QImage scroll_bar( "/ui_art/sb_bg.pcx" );
  
  // // Load the scroll bar thumb image
  // QImage scroll_bar( "/ui_art/sb_thumb.pcx" );
}

// Activate a quest
void NPCInteractionMenu::activateQuest( const Quest::Type quest )
{
  d_talk_menu_button_box->activateQuest( quest );
  this->recenterTalkMenuButtonBox();
}

// Deactivate a quest
void NPCInteractionMenu::deactivateQuest( const Quest::Type quest )
{
  d_talk_menu_button_box->deactivateQuest( quest );

  this->recenterTalkMenuButtonBox();
}

// Re-center the talk buttons box
void NPCInteractionMenu::recenterTalkMenuButtonBox()
{
  d_talk_menu_button_box->move( (d_talk_menu->width()-d_talk_menu_button_box->width())/2, (d_talk_menu->height()-d_talk_menu_button_box->height())/2 );
  
  d_talk_menu_button_box->raise();
}

// Show the talk menu
void NPCInteractionMenu::showTalkMenu()
{
  d_primary_menu->hide();
  d_primary_menu_button_box->resetActiveButton();
  
  d_talk_menu->show();
  d_talk_menu->raise();
}

// Show the primary menu
void NPCInteractionMenu::showPrimaryMenu()
{
  d_talk_menu->hide();
  d_talk_menu_button_box->resetActiveButton();
  
  d_primary_menu->show();
  d_primary_menu->raise();
}

// Handle key press events
void NPCInteractionMenu::keyPressEvent( QKeyEvent* event )
{
  if( event->key() == Qt::Key_Up )
  {
    if( d_primary_menu->isVisible() )
      d_primary_menu_button_box->moveActiveButtonUp();
    else
      d_talk_menu_button_box->moveActiveButtonUp();
  }
  else if( event->key() == Qt::Key_Down )
  {
    if( d_primary_menu->isVisible() )
      d_primary_menu_button_box->moveActiveButtonDown();
    else
      d_talk_menu_button_box->moveActiveButtonDown();
  }
  else if( event->key() == Qt::Key_Enter ||
           event->key() == Qt::Key_Return )
  {
    if( d_primary_menu->isVisible() )
      d_primary_menu_button_box->clickActiveButton();
    else
      d_talk_menu_button_box->clickActiveButton();
  }
  else if( event->key() == Qt::Key_Escape )
  {
    if( d_talk_menu->isVisible() )
      d_go_back_button->click();
    else
      d_exit_button->click();
  }
  else
    QWidget::keyPressEvent( event );
}

} // end QtD1 includes

//---------------------------------------------------------------------------//
// end NPCInteractionMenu.cpp
//---------------------------------------------------------------------------//
