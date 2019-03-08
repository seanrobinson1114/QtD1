//---------------------------------------------------------------------------//
//!
//! \file   PentSpinMenuPushButtonBox.h
//! \author Alex Robinson
//! \brief  The pent spin menu push button box class declaration
//!
//---------------------------------------------------------------------------//

#ifndef PENT_SPIN_MENU_PUSH_BUTTON_BOX_H
#define PENT_SPIN_MENU_PUSH_BUTTON_BOX_H

// Qt Includes
#include <QWidget>

namespace QtD1{

class PentSpinMenuPushButton;

//! The pent spin menu push button box
class PentSpinMenuPushButtonBox : public QWidget
{
  Q_OBJECT

public:

  //! Constructor
  PentSpinMenuPushButtonBox( QWidget* parent );
  
  //! Destructor
  ~PentSpinMenuPushButtonBox()
  { /* ... */ }

  //! Add a button
  void addButton( PentSpinMenuPushButton* button );

public slots:

  //! Move the active button up
  void moveActiveButtonUp();

  //! Move the active button down
  void moveActiveButtonDown();

  //! Click the active button
  void clickActiveButton();

  //! Reset active button (set to first)
  void resetActiveButton();

protected:

  //! Handle show events
  void showEvent( QShowEvent* event ) final override;

  //! Handle hide events
  void hideEvent( QHideEvent* event ) final override;

  //! Remove a button
  void removeButton( PentSpinMenuPushButton* button );

private slots:

  // Handle a menu push button pressed
  void handleMenuPushButtonPressed();

private:

  // Re-center the buttons
  void recenterButtons();

  // The talk button order
  QList<PentSpinMenuPushButton*> d_button_order;

  // The active talk button
  PentSpinMenuPushButton* d_active_button;
};
  
} // end QtD1 namespace

#endif // end PENT_SPIN_MENU_PUSH_BUTTON_BOX_H

//---------------------------------------------------------------------------//
// end PentSpinMenuPushButtonBox.h
//---------------------------------------------------------------------------//
