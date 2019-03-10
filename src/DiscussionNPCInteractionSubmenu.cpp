//---------------------------------------------------------------------------//
//!
//! \file   DiscussionNPCInteractionSubmenu.h
//! \author Alex Robinson
//! \brief  The discussion NPC interaction submenu class definition
//!
//---------------------------------------------------------------------------//

// Qt Includes
#include <QLabel>

// QtD1 Inclues
#include "DiscussionNPCInteractionSubmenu.h"
#include "QuestPentSpinMenuPushButtonBox.h"
#include "SmallPentSpinMenuPushButton.h"
#include "BitmapText.h"

namespace QtD1{

// Constructor
DiscussionNPCInteractionSubmenu::DiscussionNPCInteractionSubmenu(
                                               const QString& raw_title_text,
                                               const QString& back_button_name,
                                               QWidget* parent )
  : NPCInteractionSubmenu( parent )
{
  // Create the background
  QPixmap background_pixmap = this->getFrame( this->getType() );

  QLabel* background = new QLabel( this );
  background->setPixmap( background_pixmap );
  background->setFixedSize( background_pixmap.size() );

  // Resize the menu to the size of the background
  this->setFixedSize( background_pixmap.size() );

  // Create the title region
  {
    QLabel* title_region = new QLabel( background );

    BitmapText title_text;
    title_text.setFontName( "QtD1Gold11" );
    title_text.setContainerWidth( 300 );
    title_text.setTextWithNoWrap( raw_title_text );
    title_text.load();

    title_region->setStyleSheet( QString( "background: transparent" ) );
    title_region->setFixedSize( QSize( background->width(), 50 ) );
    title_region->setAlignment( Qt::AlignCenter );
    title_region->setPixmap( title_text.getPixmap() );
  }

  // Create discussion menu button box
  d_button_box = new QuestPentSpinMenuPushButtonBox( background );

  QObject::connect( d_button_box, SIGNAL(questSelected(const Quest::Type)),
                    this, SIGNAL(questSelected(const Quest::Type)) );

  // Create the gossip button
  {
    SmallPentSpinMenuPushButton* gossip_button =
      new SmallPentSpinMenuPushButton( "Gossip", "QtD1Blue11", d_button_box );
    
    gossip_button->setStyleSheet( QString( "background: transparent" ) );

    // Add the button to the talk menu button box
    d_button_box->addButton( gossip_button );

    QObject::connect( gossip_button, SIGNAL(released()),
                      this, SIGNAL(gossipSelected()) );

    // Move the talk buttons box
    this->recenterButtonBox();
  }

  // Note: no named buttons to register - button push signals will be forwarded
  //       through this class's signals

  // Create the back button
  QPushButton* back_button =
    new MenuPushButton( "Back", "QtD1White11", background );

  back_button->setStyleSheet( QString( "background: transparent" ) );
  back_button->move( (background->width()-back_button->width())/2,
                     background->height()-2*back_button->height() );

  // Register the back button
  this->setBackButton( back_button );

  // Move this submenu to the correct global location
  this->move( 427, 125 );
}

// Get the submenu type
auto DiscussionNPCInteractionSubmenu::getType() const -> Type
{
  return NPCInteractionSubmenu::Type::Discussion;
}

// Activate a quest
void DiscussionNPCInteractionSubmenu::activateQuest( const Quest::Type quest )
{
  d_button_box->activateQuest( quest );
  this->recenterButtonBox();
}

// Deactivate a quest
void DiscussionNPCInteractionSubmenu::deactivateQuest( const Quest::Type quest )
{
  d_button_box->deactivateQuest( quest );
  this->recenterButtonBox();
}

// Move the active button up
void DiscussionNPCInteractionSubmenu::moveActiveButtonUp()
{
  d_button_box->moveActiveButtonUp();
}

// Move the active button down
void DiscussionNPCInteractionSubmenu::moveActiveButtonDown()
{
  d_button_box->moveActiveButtonDown();
}
  
// Click the active button
void DiscussionNPCInteractionSubmenu::clickActiveButton()
{
  d_button_box->clickActiveButton();
}

// Reset active button (set to first)
void DiscussionNPCInteractionSubmenu::resetActiveButton()
{
  d_button_box->resetActiveButton();
}

// Recenter the button box
void DiscussionNPCInteractionSubmenu::recenterButtonBox()
{
  d_button_box->move( (this->width()-d_button_box->width())/2,
                      (this->height()-d_button_box->height())/2 );
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end DiscussionNPCInteractionSubmenu.h
//---------------------------------------------------------------------------//
