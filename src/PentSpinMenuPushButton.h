//---------------------------------------------------------------------------//
//!
//! \file   PentSpinMenuPushButton.h
//! \author Alex Robinson
//! \brief  The pent spin menu push button class declaration
//!
//---------------------------------------------------------------------------//

#ifndef PENT_SPIN_MENU_PUSH_BUTTON_H
#define PENT_SPIN_MENU_PUSH_BUTTON_H

// Qt Includes
#include <QLabel>

// QtD1 Includes
#include "MenuPushButton.h"

namespace QtD1{

//! The small pent spin menu push button
class PentSpinMenuPushButton : public MenuPushButton
{
  Q_OBJECT

public:

  //! Destructor
  ~PentSpinMenuPushButton()
  { /* ... */ }

  //! Activate the button
  void activate();

  //! Deactivate the button
  void deactivate();

  //! Set the "up" (above) button 
  void setUpButton( PentSpinMenuPushButton* up_button );

  //! Get the "up" (above) button
  PentSpinMenuPushButton* getUpButton() const;

  //! Set the "down" (below) button
  void setDownButton( PentSpinMenuPushButton* down_button );

  //! Get the "down" (below) button
  PentSpinMenuPushButton* getDownButton() const;

protected:

  //! Constructor
  PentSpinMenuPushButton( const QString& button_text,
                          const QString& bitmap_font_name,
                          const int pent_width,
                          const int pent_height,
                          QWidget* parent = 0 );

  //! Get the pent spin frame
  virtual QPixmap getPentSpinFrame( const int frame_index ) const = 0;

  //! Increment pent spin frame index
  virtual void incrementPentSpinFrame( int& frame_index ) const = 0;

  //! Handle hide events
  void hideEvent( QHideEvent* event ) final override;

  //! Handle the timer event
  void timerEvent( QTimerEvent* event ) final override;

private:

  // The timer id
  int d_pent_spin_timer_id;

  // The pent spin frame index
  int d_pent_spin_frame_index;

  // The left pent spin
  QLabel* d_left_pent_spin;

  // The right pent spin
  QLabel* d_right_pent_spin;

  // The "up" (above) button
  PentSpinMenuPushButton* d_up_button;

  // The "down" (below) button
  PentSpinMenuPushButton* d_down_button;
};
  
} // end QtD1 namespace

#endif // end PENT_SPIN_MENU_PUSH_BUTTON_H

//---------------------------------------------------------------------------//
// end PentSpinMenuPushButton.h
//---------------------------------------------------------------------------//
