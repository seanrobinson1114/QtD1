//---------------------------------------------------------------------------//
//!
//! \file   SmallPentSpinMenuPushButton.h
//! \author Alex Robinson
//! \brief  The small pent spin menu push button class declaration
//!
//---------------------------------------------------------------------------//

#ifndef SMALL_PENT_SPIN_MENU_PUSH_BUTTON_H
#define SMALL_PENT_SPIN_MENU_PUSH_BUTTON_H

// Qt Incudes
#include <QLabel>

// QtD1 Includes
#include "MenuPushButton.h"

namespace QtD1{

//! The small pent spin menu push button
class SmallPentSpinMenuPushButton : public MenuPushButton
{
  Q_OBJECT

public:

  //! Constructor
  SmallPentSpinMenuPushButton( const QString& button_text,
                               const QString& bitmap_font_name,
                               QWidget* parent = 0 );

  //! Destructor
  ~SmallPentSpinMenuPushButton()
  { /* ... */ }

  //! Activate the button
  void activate();

  //! Deactivate the button
  void deactivate();

  //! Set the "up" (above) button 
  void setUpButton( SmallPentSpinMenuPushButton* up_button );

  //! Get the "up" (above) button
  SmallPentSpinMenuPushButton* getUpButton() const;

  //! Set the "down" (below) button
  void setDownButton( SmallPentSpinMenuPushButton* down_button );

  //! Get the "down" (below) button
  SmallPentSpinMenuPushButton* getDownButton() const;

protected:

  //! Handle hide events
  void hideEvent( QHideEvent* event ) final override;

  //! Handle the timer event
  void timerEvent( QTimerEvent* event ) final override;

private:
  
  // Initialize the pent spin frames
  static void initializePentSpinFrames();

  // Increment pent spin frame
  void incrementPentSpinFrame();

  // The small pent spin sprite frames
  static QVector<QPixmap> s_pent_spin_frames;

  // The timer id
  int d_pent_spin_timer_id;

  // The pent spin frame index
  int d_pent_spin_frame_index;

  // The left pent spin
  QLabel* d_left_pent_spin;

  // The right pent spin
  QLabel* d_right_pent_spin;

  // The "up" (above) button
  SmallPentSpinMenuPushButton* d_up_button;

  // The "down" (below) button
  SmallPentSpinMenuPushButton* d_down_button;
};
  
} // end QtD1 namespace

#endif // end SMALL_PENT_SPIN_MENU_BUTTON_H

//---------------------------------------------------------------------------//
// end SmallPentSpinPushButton.h
//---------------------------------------------------------------------------//
