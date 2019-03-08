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
#include "PentSpinMenuPushButton.h"

namespace QtD1{

//! The small pent spin menu push button
class SmallPentSpinMenuPushButton : public PentSpinMenuPushButton
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

protected:

  //! Get the pent spin frame
  QPixmap getPentSpinFrame( const int frame_index ) const final override;

  //! Increment pent spin frame index
  void incrementPentSpinFrame( int& frame_index ) const final override;

private:
  
  // Initialize the pent spin frames
  static void initializePentSpinFrames();

  // The small pent spin sprite frames
  static QVector<QPixmap> s_pent_spin_frames;
};
  
} // end QtD1 namespace

#endif // end SMALL_PENT_SPIN_MENU_BUTTON_H

//---------------------------------------------------------------------------//
// end SmallPentSpinPushButton.h
//---------------------------------------------------------------------------//
