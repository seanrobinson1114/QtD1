//---------------------------------------------------------------------------//
//!
//! \file   NPCDialogueBox.h
//! \author Alex Robinson
//! \brief  The NPC dialogue box base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef NPC_DIALOGUE_BOX_H
#define NPC_DIALOGUE_BOX_H

// Std Lib Includes
#include <memory>

// Qt Includes
#include <QWidget>
#include <QLabel>
#include <QPropertyAnimation>

namespace QtD1{

//! The NPC dialogue box class
class NPCDialogueBox : public QWidget
{
  Q_OBJECT

public:

  //! Constructor
  NPCDialogueBox( QWidget* parent = 0 );

  //! Destructor
  ~NPCDialogueBox()
  { /* ... */ }

  //! Get the dialogue box width
  int getDialogueBoxWidth() const;

  //! Display dialogue
  void displayDialogue( QPixmap dialogue_text,
                        const int dialogue_font_size,
                        const double scroll_delay_time,
                        const double scroll_duration );

signals:

  //! The dialogue has finished
  void dialogueFinished();

protected:

  //! Handle key press events
  void keyPressEvent( QKeyEvent* event ) final override;

  //! Handle mouse click events
  void mouseReleaseEvent( QMouseEvent* event ) final override;

  //! Handle show events
  //void showEvent( QShowEvent* event ) final override;

  //! Handle hide events
  void hideEvent( QHideEvent* event ) final override;

  //! Handle the timer event
  void timerEvent( QTimerEvent* event ) final override;

private:

  // The scroll animation timer
  int d_scroll_animation_timer_id;

  // The scroll duration (ms)
  int d_scroll_duration;

  // The dialogue box
  QLabel* d_dialogue_box;
  
  // The dialogue text
  QLabel* d_dialogue_text;

  // The property animation
  QPropertyAnimation* d_text_scroll_animation;
};
  
} // end QtD1 namespace

#endif // end NPC_DIALOGUE_BOX

//---------------------------------------------------------------------------//
// end NPCDialogueBox.h
//---------------------------------------------------------------------------//
