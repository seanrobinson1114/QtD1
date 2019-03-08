//---------------------------------------------------------------------------//
//!
//! \file   LargePentSpinMenuPushButton.h
//! \author Alex Robinson
//! \brief  The large pent spin menu push button class declaration
//!
//---------------------------------------------------------------------------//

#ifndef LARGE_PENT_SPIN_MENU_PUSH_BUTTON_H
#define LARGE_PENT_SPIN_MENU_PUSH_BUTTON_H

// Qt Incudes
#include <QLabel>

// QtD1 Includes
#include "PentSpinMenuPushButton.h"

namespace QtD1{

//! The large pent spin menu push button
class LargePentSpinMenuPushButton : public PentSpinMenuPushButton
{
  Q_OBJECT

public:

  //! Constructor
  LargePentSpinMenuPushButton( const QString& button_text,
                               const QString& bitmap_font_name,
                               QWidget* parent = 0 );

  //! Destructor
  ~LargePentSpinMenuPushButton()
  { /* ... */ }

protected:

  //! Get the pent spin frame
  QPixmap getPentSpinFrame( const int frame_index ) const final override;

  //! Increment pent spin frame index
  void incrementPentSpinFrame( int& frame_index ) const final override;

private:
  
  // Initialize the pent spin frames
  static void initializePentSpinFrames();

  // The large pent spin sprite frames
  static QVector<QPixmap> s_pent_spin_frames;
};
  
} // end QtD1 namespace

#endif // end LARGE_PENT_SPIN_MENU_BUTTON_H

//---------------------------------------------------------------------------//
// end LargePentSpinPushButton.h
//---------------------------------------------------------------------------//
