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
#include "QuestMenuPushButton.h"
#include "UIArtLoader.h"
#include "BitmapText.h"
#include "MenuPushButton.h"

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
    d_talk_buttons_box( NULL ),
    d_talk_button_order(),
    d_gossip_button( NULL ),
    d_quest_discussion_buttons(),
    d_active_menu_button( NULL ),
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
    d_talk_menu_button = new SmallPentSpinMenuPushButton(
                                                QString("Talk to ") + npc_name,
                                                "QtD1Blue11",
                                                d_primary_menu );
    d_talk_menu_button->setFocusProxy( d_primary_menu );
    d_talk_menu_button->setStyleSheet( QString( "background: transparent" ) );
    d_talk_menu_button->move( (d_primary_menu->width()-d_talk_menu_button->width())/2, 150 );
    d_talk_menu_button->raise();

    // Set this as the active button
    d_active_menu_button = d_talk_menu_button;

    QObject::connect( d_talk_menu_button, SIGNAL(pressed()),
                      this, SLOT(handleMenuPushButtonPressed()) );
    QObject::connect( d_talk_menu_button, SIGNAL(released()),
                      this, SLOT(showTalkMenu()) );
  }
  
  // Create the exit button
  {
    d_exit_button = new MenuPushButton( exit_menu_text,
                                        "QtD1White11",
                                        d_primary_menu );
    d_exit_button->setFocusProxy( d_primary_menu );
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
  d_talk_buttons_box = new QLabel( d_talk_menu );

  // Create the gossip button
  {
    d_gossip_button = new SmallPentSpinMenuPushButton( "Gossip",
                                                       "QtD1Blue11",
                                                       d_talk_buttons_box );
    d_gossip_button->setFocusProxy( d_talk_menu );
    d_gossip_button->setStyleSheet( QString( "background: transparent" ) );
    d_gossip_button->raise();

    // Resize the talk buttons box
    d_talk_buttons_box->resize( d_gossip_button->size() );

    // Add the button to the button order
    d_talk_button_order << d_gossip_button;

    QObject::connect( d_gossip_button, SIGNAL(pressed()),
                      this, SLOT(handleMenuPushButtonPressed()) );
    QObject::connect( d_gossip_button, SIGNAL(released()),
                      this, SIGNAL(gossip()) );
  }

  // Move the talk buttons box
  this->recenterTalkButtonsBox();

  // Create the back button
  {
    d_go_back_button = new MenuPushButton( "Back",
                                           "QtD1White11",
                                           d_talk_menu );
    d_go_back_button->setFocusProxy( d_talk_menu );
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
  auto quest_discussion_buttons_it =
    d_quest_discussion_buttons.find( quest );
  
  if( quest_discussion_buttons_it == d_quest_discussion_buttons.end() )
  {
    QuestMenuPushButton* quest_button =
      new QuestMenuPushButton( quest, "QtD1White11", d_talk_buttons_box );
    quest_button->setStyleSheet( QString( "background: transparent" ) );
    quest_button->move( 0, d_talk_buttons_box->height()+quest_button->height() );
    quest_button->raise();

    QObject::connect( quest_button, SIGNAL(pressed()),
                      this, SLOT(handleMenuPushButtonPressed()) );
    QObject::connect( quest_button, SIGNAL(releasedQuest(const Quest::Type)),
                      this, SIGNAL(discussQuest(const Quest::Type)) );

    d_quest_discussion_buttons[quest] = quest_button;

    // Add the quest button to the talk button order
    d_talk_button_order.back()->setDownButton( quest_button );
    d_talk_button_order.front()->setUpButton( quest_button );
    quest_button->setUpButton( d_talk_button_order.back() );
    quest_button->setDownButton( d_talk_button_order.front() );
    
    d_talk_button_order << quest_button;

    int button_box_height =
      d_talk_buttons_box->height() + 2*quest_button->height();

    int button_box_width = d_talk_buttons_box->width();

    if( quest_button->width() > button_box_width )
      button_box_width = quest_button->width();

    d_talk_buttons_box->resize( QSize(button_box_width, button_box_height) );

    this->recenterTalkButtons();
    this->recenterTalkButtonsBox();
  }
}

// Deactivate a quest
void NPCInteractionMenu::deactivateQuest( const Quest::Type quest )
{
  auto quest_discussion_buttons_it =
    d_quest_discussion_buttons.find( quest );
  
  if( quest_discussion_buttons_it != d_quest_discussion_buttons.end() )
  {
    // Find the order of the button
    auto removed_quest_button_it = d_talk_button_order.begin();

    while( removed_quest_button_it != d_talk_button_order.end() )
    {
      if( *removed_quest_button_it == quest_discussion_buttons_it->second )
        break;

      ++removed_quest_button_it;
    }

    // Loop through all buttons that come after this button and move them up
    if( removed_quest_button_it != d_talk_button_order.end() )
    {
      auto remaining_button_it = removed_quest_button_it;
      ++remaining_button_it;
      
      while( remaining_button_it != d_talk_button_order.end() )
      {
        (*remaining_button_it)->move( (*remaining_button_it)->x(),
                                      (*remaining_button_it)->y() -
                                      2*(*removed_quest_button_it)->height() );

        (*remaining_button_it)->raise();
        
        ++remaining_button_it;
      }

      // Remove the button from the order list
      auto up_button = (*removed_quest_button_it)->getUpButton();
      auto down_button = (*removed_quest_button_it)->getDownButton();

      up_button->setDownButton( down_button );
      down_button->setUpButton( up_button );
      
      d_talk_button_order.erase( removed_quest_button_it );

      // Resize the talk buttons box
      d_talk_buttons_box->resize( QSize(d_talk_buttons_box->width(),
                                        d_talk_buttons_box->height() -
                                        (*removed_quest_button_it)->height()) );
      this->recenterTalkButtonsBox();
    }

    // Destroy the button
    delete quest_discussion_buttons_it->second;

    d_quest_discussion_buttons.erase( quest_discussion_buttons_it );
  }
}

// Re-center the talk buttons box
void NPCInteractionMenu::recenterTalkButtonsBox()
{
  d_talk_buttons_box->move( (d_talk_menu->width()-d_talk_buttons_box->width())/2, (d_talk_menu->height()-d_talk_buttons_box->height())/2 );
  
  d_talk_buttons_box->raise();
}

// Re-center the talk buttons
void NPCInteractionMenu::recenterTalkButtons()
{
  auto talk_button_it = d_talk_button_order.begin();

  while( talk_button_it != d_talk_button_order.end() )
  {
    (*talk_button_it)->move( (d_talk_buttons_box->width()-(*talk_button_it)->width())/2, (*talk_button_it)->y() );
      
    ++talk_button_it;
  }
}

// Show the talk menu
void NPCInteractionMenu::showTalkMenu()
{
  d_primary_menu->hide();
  //d_primary_menu->clearFocus();
  
  d_talk_menu->show();
  d_talk_menu->raise();
  d_talk_menu->setFocus();

  if( d_active_menu_button )
    d_active_menu_button->deactivate();

  d_active_menu_button = d_gossip_button;
  d_active_menu_button->activate();
}

// Show the primary menu
void NPCInteractionMenu::showPrimaryMenu()
{
  d_talk_menu->hide();
  //d_talk_menu->clearFocus();
  
  d_primary_menu->show();
  d_primary_menu->raise();
  d_primary_menu->setFocus();

  if( d_active_menu_button )
    d_active_menu_button->deactivate();
  
  d_active_menu_button = d_talk_menu_button;
  d_active_menu_button->activate();
}

// Handle key press events
void NPCInteractionMenu::keyPressEvent( QKeyEvent* event )
{
  if( event->key() == Qt::Key_Up )
  {
    if( d_active_menu_button )
    {
      d_active_menu_button->deactivate();

      d_active_menu_button = d_active_menu_button->getUpButton();

      d_active_menu_button->activate();
    }
  }
  else if( event->key() == Qt::Key_Down )
  {
    if( d_active_menu_button )
    {
      d_active_menu_button->deactivate();

      d_active_menu_button = d_active_menu_button->getDownButton();

      d_active_menu_button->activate();
    }
  }
  else if( event->key() == Qt::Key_Enter ||
           event->key() == Qt::Key_Return )
  {
    if( d_active_menu_button )
      d_active_menu_button->click();
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

// Handle show events
void NPCInteractionMenu::showEvent( QShowEvent* event )
{
  if( d_active_menu_button )
    d_active_menu_button->activate();

  QWidget::showEvent( event );
}

// Handle hide events
void NPCInteractionMenu::hideEvent( QHideEvent* event )
{
  if( d_active_menu_button )
    d_active_menu_button->deactivate();
  
  QWidget::hideEvent( event );
}

// Handle a menu push button pressed
void NPCInteractionMenu::handleMenuPushButtonPressed()
{
  QObject* raw_sender = QObject::sender();

  SmallPentSpinMenuPushButton* sender =
    dynamic_cast<SmallPentSpinMenuPushButton*>( raw_sender );

  if( sender )
  {
    if( d_active_menu_button )
      d_active_menu_button->deactivate();

    d_active_menu_button = sender;
    d_active_menu_button->activate();
  }
}

} // end QtD1 includes

//---------------------------------------------------------------------------//
// end NPCInteractionMenu.cpp
//---------------------------------------------------------------------------//
