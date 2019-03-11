//---------------------------------------------------------------------------//
//!
//! \file   PrimaryNPCInteractionSubmenu.cpp
//! \author Alex Robinson
//! \brief  The primary NPC interaction submenu class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "PrimaryNPCInteractionSubmenu.h"
#include "PentSpinMenuPushButtonBox.h"
#include "SmallPentSpinMenuPushButton.h"
#include "BitmapText.h"

namespace QtD1{

// Constructor
PrimaryNPCInteractionSubmenu::PrimaryNPCInteractionSubmenu(
                                      const QString& raw_title_text,
                                      const QString& npc_talk_button_name,
                                      const QList<QString>& extra_button_names,
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
  this->setFixedSize( background->size() );

  // Create the title region
  {
    QLabel* title_region = new QLabel( background );
    
    title_region->setStyleSheet( QString( "background: transparent" ) );
    title_region->setFixedSize( QSize( background->width(), 55 ) );
    
    if( raw_title_text.contains( '\n' ) )
      this->createAdvancedTitleRegion( raw_title_text, title_region );
    else
      this->createBasicTitleRegion( raw_title_text, title_region );
  }

  // Create the prompt region
  {
    QLabel* prompt_region = new QLabel( background );

    BitmapText prompt_text;
    prompt_text.setFontName( "QtD1Gold11" );
    prompt_text.setContainerWidth( 200 );
    prompt_text.setTextWithNoWrap( "Would you like to:" );
    prompt_text.load();

    prompt_region->setStyleSheet( QString( "background: transparent" ) );
    prompt_region->setFixedSize( QSize( background->width(), 50 ) );
    prompt_region->setAlignment( Qt::AlignHCenter | Qt::AlignBottom );
    prompt_region->setPixmap( prompt_text.getPixmap() );
    prompt_region->move( 0, 51 );
  }

  // Create the primary menu button box
  d_button_box = new PentSpinMenuPushButtonBox( background );

  std::map<QString,QPushButton*> named_buttons;

  // Create the talk menu button
  {
    SmallPentSpinMenuPushButton* talk_menu_button =
      new SmallPentSpinMenuPushButton( npc_talk_button_name,
                                       "QtD1Blue11",
                                       background );
    talk_menu_button->setStyleSheet( QString( "background: transparent" ) );

    // Add the button to the button box
    d_button_box->addButton( talk_menu_button );

    // Map the button name to the button
    named_buttons[npc_talk_button_name] = talk_menu_button;
  }

  // Create the extra buttons
  {
    for( auto&& button_name : extra_button_names )
    {
      SmallPentSpinMenuPushButton* extra_menu_button =
        new SmallPentSpinMenuPushButton( button_name,
                                         "QtD1White11",
                                         background );
      extra_menu_button->setStyleSheet( QString( "background: transparent" ) );

      // Add the button to the button box
      d_button_box->addButton( extra_menu_button );

      // Map the button name to the button
      named_buttons[button_name] = extra_menu_button;
    }
  }

  // Register the named buttons
  this->setNamedButtons( named_buttons );

  // Center the button box
  d_button_box->move( (background->width()-d_button_box->width())/2,
                      (background->height()-d_button_box->height())/2 );

  this->setFocusProxy( d_button_box );

  // Create the exit button
  QPushButton* exit_button = new MenuPushButton( back_button_name,
                                                 "QtD1White11",
                                                 background );
  exit_button->setStyleSheet( QString( "background: transparent" ) );
  exit_button->move( (background->width()-exit_button->width())/2,
                     background->height() - 2*exit_button->height() );

  // Register the back button
  this->setBackButton( exit_button );

  // Move this submenu to the correct global location
  this->move( 427, 125 );
}

// Get the submenu type
auto PrimaryNPCInteractionSubmenu::getType() const -> Type
{
  return NPCInteractionSubmenu::Type::Primary;
}

// Move the active button up
void PrimaryNPCInteractionSubmenu::moveActiveButtonUp()
{
  d_button_box->moveActiveButtonUp();
}

// Move the active button down
void PrimaryNPCInteractionSubmenu::moveActiveButtonDown()
{
  d_button_box->moveActiveButtonDown();
}
  
// Click the active button
void PrimaryNPCInteractionSubmenu::clickActiveButton()
{
  d_button_box->clickActiveButton();
}

// Reset active button (set to first)
void PrimaryNPCInteractionSubmenu::resetActiveButton()
{
  d_button_box->resetActiveButton();
}

// Handle back button pushed
void PrimaryNPCInteractionSubmenu::handleBackButtonPushed()
{
  emit exit();

  d_button_box->resetActiveButton();
}

// Create a basic title region
void PrimaryNPCInteractionSubmenu::createBasicTitleRegion(
                                                 const QString& raw_title_text,
                                                 QLabel* title_region ) const
{
  BitmapText title_text;
  title_text.setFontName( "QtD1Gold11" );
  title_text.setContainerWidth( 200 );
  title_text.setTextWithNoWrap( raw_title_text );
  title_text.load();
  
  title_region->setAlignment( Qt::AlignCenter );
  title_region->setPixmap( title_text.getPixmap() );
}

  // Create an advanced title region
void PrimaryNPCInteractionSubmenu::createAdvancedTitleRegion(
                                                 const QString& raw_title_text,
                                                 QLabel* title_region ) const
{
  QStringList raw_title_text_lines = raw_title_text.split( '\n' );

  // Render each line of text separately
  QList<QPixmap> title_text_lines;
  int width = 0;
  int height = 0;

  for( auto&& raw_text : raw_title_text_lines )
  {
    std::cout << "title line: " << raw_text.toStdString() << std::endl;
    BitmapText title_text;
    title_text.setFontName( "QtD1Gold11" );
    title_text.setContainerWidth( 200 );
    title_text.setTextWithNoWrap( raw_text );
    title_text.load();

    if( title_text.getPixmap().width() > width )
      width = title_text.getPixmap().width();

    height += 2*title_text.getPixmap().height();

    title_text_lines << title_text.getPixmap();
  }

  height -= title_text_lines.back().height();

  // Create a title text region that will manage each text line
  QLabel* title_text_region = new QLabel( title_region );
  title_text_region->setStyleSheet( QString( "background: transparent" ) );
  title_text_region->setFixedSize( QSize( width, height ) );

  // Center each line in the title text region
  int current_height = 0;
  
  for( auto&& title_text_line_pixmap : title_text_lines )
  {
    QLabel* title_text_line = new QLabel( title_text_region );
    title_text_line->setStyleSheet( QString( "background: transparent" ) );
    title_text_line->setFixedSize( title_text_line_pixmap.size() );
    title_text_line->setPixmap( title_text_line_pixmap );
    
    title_text_line->move( (title_text_region->width()-title_text_line->width())/2,
                           current_height );

    current_height += 2*title_text_line->height();
  }

  // Center the title text region
  title_text_region->move( (title_region->width()-title_text_region->width())/2,
                           (title_region->height()-title_text_region->height())/2 );
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end PrimaryNPCInteractionSubmenu.cpp
//---------------------------------------------------------------------------//
