//---------------------------------------------------------------------------//
//!
//! \file   TradeNPCInteractionSubmenu.cpp
//! \author Alex Robinson
//! \brief  The trade NPC interaction submenu class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "TradeNPCInteractionSubmenu.h"
#include "PentSpinMenuPushButton.h"
#include "Character.h"

namespace QtD1{

// Constructor
TradeNPCInteractionSubmenu::TradeNPCInteractionSubmenu(
                                           const QString& primary_title_text,
                                           const QString& secondary_title_text,
                                           const QString& question_text,
                                           const QString& back_button_name,
                                           Character* character,
                                           QWidget* parent )
  : NPCInteractionSubmenu( parent ),
    d_item_scroll_box( NULL ),
    d_item_button_box( NULL ),
    d_item_scroll_bar( NULL ),
    d_item_prompt_box( NULL ),
    d_item_display_box( NULL ),
    d_item_prompt_yes_no_button_box( NULL )
{
  // Create the background
  QPixmap background_pixmap = this->getFrames( this->getType() ).front();

  QLabel* background = new QLabel( this );
  background->setPixmap( background_pixmap );
  background->setFixedSize( background_pixmap.size() );

  // Resize the menu to the size of the background
  this->setFixedSize( background->size() );

  // Create the divider
  QPixmap divider_pixmap = this->getFrames( this->getType() ).back();
  
  QLabel* divider = new QLabel( background );
  divider->setPixmap( divider_pixmap );
  divider->setFixedSize( divider_pixmap.size() );

  // Create the back button
  QPushButton* back_button = new MenuPushButton( back_button_name,
                                                 "QtD1White11",
                                                 background );
  back_button->setStyleSheet( QString( "background: transparent" ) );
  back_button->move( (background->width()-back_button->width())/2,
                     background->height() - 2*back_button->height() );

  // Register the back button
  this->setBackButton( back_button );

  // Move the divider
  divider->move( 0, background->height() - 3*back_button->height() );

  // Move this submenu to the correct global location
  this->move( 115, 125 );
}

// Get the submenu type
auto TradeNPCInteractionSubmenu::getType() const -> Type
{
  return NPCInteractionSubmenu::Type::Trade;
}

// Move the active button up
void TradeNPCInteractionSubmenu::moveActiveButtonUp()
{

}

// Move the active button down
void TradeNPCInteractionSubmenu::moveActiveButtonDown()
{

}
  
// Click the active button
void TradeNPCInteractionSubmenu::clickActiveButton()
{

}

// Reset active button (set to first)
void TradeNPCInteractionSubmenu::resetActiveButton()
{

}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end TradeNPCInteractionSubmenu.cpp
//---------------------------------------------------------------------------//
