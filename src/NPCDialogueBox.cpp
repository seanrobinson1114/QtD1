//---------------------------------------------------------------------------//
//!
//! \file   NPCDialogueBox.h
//! \author Alex Robinson
//! \brief  The NPC dialogue box base class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "NPCDialogueBox.h"
#include "UIArtLoader.h"
#include "BitmapText.h"

namespace QtD1{

// Constructor
NPCDialogueBox::NPCDialogueBox( QWidget* parent )
  : QWidget( parent ),
    d_scroll_animation_timer_id( -1 ),
    d_dialogue_box( NULL ),
    d_dialogue_text( NULL ),
    d_text_scroll_animation()
{
  // Load the interaction menu image
  std::unique_ptr<UIArtLoader> ui_art_frame_loader( new UIArtLoader );

  ui_art_frame_loader->setSource( "/ui_art/seldiff.pcx" );
  ui_art_frame_loader->setTransparentColor( QColor( "black" ) );
  ui_art_frame_loader->loadFrames();

  QImage dialogue_box_border_image =
    ui_art_frame_loader->getLoadedFrames().front();

  // Crop the border image
  dialogue_box_border_image =
    dialogue_box_border_image.copy( 274, 90, 351, 180 );

  // Stretch the border image
  dialogue_box_border_image =
    dialogue_box_border_image.scaled( dialogue_box_border_image.width()*1.70,
                                      dialogue_box_border_image.height()*1.792 );

  // Create the dialogue box background
  QLabel* dialogue_box_background = new QLabel( this );
  dialogue_box_background->setFixedSize( dialogue_box_border_image.width()-23,
                                         dialogue_box_border_image.height()-3 );

  {
    QPixmap background( dialogue_box_background->size() );
    background.fill( QColor( 0, 0, 0, 127 ) );

    dialogue_box_background->setPixmap( background );
  }

  // Create the dialogue border
  QLabel* dialogue_box_border = new QLabel( dialogue_box_background );
  dialogue_box_border->setPixmap( QPixmap::fromImage( dialogue_box_border_image ) );
  dialogue_box_border->setFixedSize( dialogue_box_border_image.size() );
  dialogue_box_border->move( -6, 0 );

  // Create the dialogue text box
  d_dialogue_box = new QLabel( dialogue_box_background );
  d_dialogue_box->setFixedSize( dialogue_box_background->width()-40,
                                dialogue_box_background->height()-30 );
  //d_dialogue_box->setStyleSheet( QString( "border: 1px solid blue" ) );
  d_dialogue_box->move( (dialogue_box_background->width() - d_dialogue_box->width())/2,
                        (dialogue_box_background->height() - d_dialogue_box->height())/2 );

  // Initialize the dialogue text label
  d_dialogue_text = new QLabel( d_dialogue_box );

  // Create the text scroll animation
  d_text_scroll_animation = new QPropertyAnimation( d_dialogue_text, "pos" );
  
  // Forward the property animation signals
  QObject::connect( d_text_scroll_animation, SIGNAL(finished()),
                    this, SIGNAL(dialogueFinished()) );

  // Set this widgets size and location
  this->setFixedSize( dialogue_box_border_image.size() );
  this->move( 115, 125 );
}

// Display dialogue
/*! \details Scroll delay time is in seconds, Scroll duration is in seconds
 */
void NPCDialogueBox::displayDialogue( QPixmap dialogue_text,
                                      const int dialogue_font_size,
                                      const double scroll_delay_time,
                                      const double scroll_duration )
{
  // Reset the dialogue text
  d_dialogue_text->setPixmap( dialogue_text );
  d_dialogue_text->setFixedSize( dialogue_text.size() );
  d_dialogue_text->move( 0, d_dialogue_box->height()-dialogue_font_size );

  // Convert the scroll duration from seconds to ms
  d_scroll_duration = scroll_duration*1000;

  // Start the animation timer
  d_scroll_animation_timer_id = this->startTimer( scroll_delay_time*1000 );
}

// Get the dialogue box width
int NPCDialogueBox::getDialogueBoxWidth() const
{
  return d_dialogue_box->width();
}

// Handle key press events
void NPCDialogueBox::keyPressEvent( QKeyEvent* event )
{ 
  if( event->key() == Qt::Key_Enter ||
      event->key() == Qt::Key_Escape )
  {
    emit dialogueFinished();
  }
}

// Handle mouse click events
void NPCDialogueBox::mouseReleaseEvent( QMouseEvent* event )
{
  emit dialogueFinished();
}

// Handle hide events
void NPCDialogueBox::hideEvent( QHideEvent* event )
{
  if( d_scroll_animation_timer_id != -1 )
  {
    this->killTimer( d_scroll_animation_timer_id );
    d_scroll_animation_timer_id = -1;
  }

  d_text_scroll_animation->stop();

  QWidget::hideEvent( event );
}

// Handle the timer event
void NPCDialogueBox::timerEvent( QTimerEvent* event )
{
  // Kill the timer
  this->killTimer( d_scroll_animation_timer_id );
  d_scroll_animation_timer_id = -1;

  // Set up the property animation
  d_text_scroll_animation->setDuration( d_scroll_duration );
  d_text_scroll_animation->setStartValue( QPoint(d_dialogue_text->x(), d_dialogue_text->y()) );
  d_text_scroll_animation->setEndValue( QPoint(d_dialogue_text->x(), -d_dialogue_text->height()) );

  d_text_scroll_animation->start();
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end NPCDialogueBox.h
//---------------------------------------------------------------------------//
