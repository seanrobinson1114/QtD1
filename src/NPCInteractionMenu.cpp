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

namespace QtD1{

// Constructor
NPCInteractionMenu::NPCInteractionMenu( const QString& npc_name,
                                        const QString& interaction_menu_title_text,
                                        const QString& exit_menu_text,
                                        QWidget* parent )
  : QWidget( parent ),
    d_primary_menu( NULL ),
    d_talk_menu( NULL ),
    d_talk_menu_button( NULL ),
    d_gossip_button( NULL ),
    d_quest_discussion_buttons(),
    d_go_back_button( NULL ),
    d_exit_button( NULL )
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

  // Create the talk menu button
  {
    BitmapText talk_menu_button_text;
    talk_menu_button_text.setFontName( "QtD1Blue11" );
    talk_menu_button_text.setContainerWidth( 300 );
    //talk_menu_button_text.setTextWithNoWrap( QString("Talk to ") + npc_name );
    talk_menu_button_text.setTextWithNoWrap( QString("Talk to ") + npc_name );
    talk_menu_button_text.load();

    QIcon talk_menu_button_icon( talk_menu_button_text.getPixmap() );

    d_talk_menu_button = new QPushButton( d_primary_menu );
    d_talk_menu_button->setFocusProxy( d_primary_menu );
    d_talk_menu_button->setStyleSheet( QString( "background: transparent" ) );
    d_talk_menu_button->setIcon( talk_menu_button_icon );
    d_talk_menu_button->setIconSize( talk_menu_button_text.getPixmap().size() );
    d_talk_menu_button->resize( talk_menu_button_text.getPixmap().size() );
    d_talk_menu_button->move( (d_primary_menu->width()-talk_menu_button_text.getPixmap().width())/2, 150 );
    d_talk_menu_button->raise();

    QObject::connect( d_talk_menu_button, SIGNAL(pressed()),
                      this, SLOT(showTalkMenu()) );
  }
  
  // Create the exit button
  {
    BitmapText exit_button_text;
    exit_button_text.setFontName( "QtD1White11" );
    exit_button_text.setContainerWidth( 150 );
    exit_button_text.setTextWithNoWrap( exit_menu_text );
    exit_button_text.load();
    
    QIcon exit_button_icon( exit_button_text.getPixmap() );
    std::cout << "Icon theme: " << exit_button_icon.themeName().toStdString() << std::endl;
    
    d_exit_button = new QPushButton( d_primary_menu );
    d_exit_button->setFocusProxy( d_primary_menu );
    d_exit_button->setStyleSheet( QString( "background: transparent" ) );
    d_exit_button->setIcon( exit_button_icon );
    d_exit_button->setIconSize( exit_button_text.getPixmap().size() );
    d_exit_button->resize( exit_button_text.getPixmap().size() );
    d_exit_button->move( (d_primary_menu->width()-exit_button_text.getPixmap().width())/2, 250 );
    d_exit_button->raise();
    
    QObject::connect( d_exit_button, SIGNAL(pressed()),
                      this, SIGNAL(exit()) );
    d_exit_button->setShortcut( tr( "Esc" ) );
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

  // Create the gossip button
  {
    BitmapText gossip_button_text;
    gossip_button_text.setFontName( "QtD1Blue11" );
    gossip_button_text.setContainerWidth( 150 );
    gossip_button_text.setTextWithNoWrap( "Gossip" );
    gossip_button_text.load();

    QIcon gossip_button_icon( gossip_button_text.getPixmap() );
    
    d_gossip_button = new QPushButton( d_talk_menu );
    d_gossip_button->setFocusProxy( d_talk_menu );
    d_gossip_button->setStyleSheet( QString( "background: transparent" ) );
    d_gossip_button->setIcon( gossip_button_icon );
    d_gossip_button->setIconSize( gossip_button_text.getPixmap().size() );
    d_gossip_button->resize( gossip_button_text.getPixmap().size() );
    d_gossip_button->move( (d_primary_menu->width()-gossip_button_text.getPixmap().width())/2, d_talk_menu->height()/2 );
    d_gossip_button->raise();
    
    QObject::connect( d_gossip_button, SIGNAL(pressed()),
                      this, SIGNAL(gossip()) );
    //d_gossip_button->setShortcut( tr( "Esc" ) );
  }

  // Create the back button
  {
    BitmapText back_button_text;
    back_button_text.setFontName( "QtD1White11" );
    back_button_text.setContainerWidth( 150 );
    back_button_text.setTextWithNoWrap( "Back" );
    back_button_text.load();
    
    QIcon back_button_icon( back_button_text.getPixmap() );
    
    d_go_back_button = new QPushButton( d_talk_menu );
    d_go_back_button->setFocusProxy( d_talk_menu );
    d_go_back_button->setStyleSheet( QString( "background: transparent" ) );
    d_go_back_button->setIcon( back_button_icon );
    d_go_back_button->setIconSize( back_button_text.getPixmap().size() );
    d_go_back_button->resize( back_button_text.getPixmap().size() );
    d_go_back_button->move( (d_primary_menu->width()-back_button_text.getPixmap().width())/2, 280 );
    d_go_back_button->raise();
    
    QObject::connect( d_go_back_button, SIGNAL(pressed()),
                      this, SLOT(showPrimaryMenu()) );
    //d_go_back_button->setShortcut( tr( "Esc" ) );
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

}

// Deactivate a quest
void NPCInteractionMenu::deactivateQuest( const Quest::Type quest )
{

}

// Show the talk menu
void NPCInteractionMenu::showTalkMenu()
{
  d_primary_menu->hide();
  //d_primary_menu->clearFocus();
  
  d_talk_menu->show();
  d_talk_menu->raise();
  d_talk_menu->setFocus();
}

// Show the primary menu
void NPCInteractionMenu::showPrimaryMenu()
{
  d_talk_menu->hide();
  //d_talk_menu->clearFocus();
  
  d_primary_menu->show();
  d_primary_menu->raise();
  d_primary_menu->setFocus();
}

// Handle key press events
void NPCInteractionMenu::keyPressEvent( QKeyEvent* event )
{
  if( event->key() == Qt::Key_Up )
  {
    
  }
  else if( event->key() == Qt::Key_Down )
  {

  }
  else if( event->key() == Qt::Key_Enter )
  {

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
