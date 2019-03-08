//---------------------------------------------------------------------------//
//!
//! \file   PentSpinMenuPushButtonBox.cpp
//! \author Alex Robinson
//! \brief  The pent spin menu push button box class definition
//!
//---------------------------------------------------------------------------//

// Qt Includes
#include <QKeyEvent>

// QtD1 Includes
#include "PentSpinMenuPushButtonBox.h"
#include "PentSpinMenuPushButton.h"

namespace QtD1{

// Constructor
PentSpinMenuPushButtonBox::PentSpinMenuPushButtonBox( QWidget* parent )
  : QWidget( parent ),
    d_button_order(),
    d_active_button( NULL )
{ /* ... */ }

// Add a button
void PentSpinMenuPushButtonBox::addButton( PentSpinMenuPushButton* button )
{
  button->setParent( this );
  button->raise();

  if( d_button_order.empty() )
  {
    this->resize( button->size() );
    button->move( 0, 0 );

    d_active_button = button;
  }
  else
  {
    // Update the button circularly linked list
    d_button_order.back()->setDownButton( button );
    d_button_order.front()->setUpButton( button );

    button->setUpButton( d_button_order.back() );
    button->setDownButton( d_button_order.front() );

    // Reposition the button
    button->move( 0, this->height()+button->height() );

    // Resize the box
    int box_height = this->height() + 2*button->height();
    int box_width = this->width();

    if( button->width() > box_width )
      box_width = button->width();

    this->resize( QSize(box_width, box_height) );

    // Center all buttons in the box
    this->recenterButtons();
  }

  d_button_order << button;

  QObject::connect( button, SIGNAL(pressed()),
                    this, SLOT(handleMenuPushButtonPressed()) );
}

// Remove a button
void PentSpinMenuPushButtonBox::removeButton( PentSpinMenuPushButton* button )
{
  // Find the order of the button
  auto removed_button_it = d_button_order.begin();

  while( removed_button_it != d_button_order.end() )
  {
    if( *removed_button_it == button )
      break;
    
    ++removed_button_it;
  }

  // Loop through all buttons that come after this button and move them up
  if( removed_button_it != d_button_order.end() )
  {
    auto remaining_button_it = removed_button_it;
    ++remaining_button_it;
      
    while( remaining_button_it != d_button_order.end() )
    {
      (*remaining_button_it)->move( (*remaining_button_it)->x(),
                                    (*remaining_button_it)->y() -
                                    2*(*removed_button_it)->height() );
      
      (*remaining_button_it)->raise();
      
      ++remaining_button_it;
    }
    
    // Update the button circularly linked list
    auto up_button = (*removed_button_it)->getUpButton();
    auto down_button = (*removed_button_it)->getDownButton();

    up_button->setDownButton( down_button );
    down_button->setUpButton( up_button );

    // Remove the button from the order list
    d_button_order.erase( removed_button_it );
    
    // Resize the box
    this->resize( QSize(this->width(),
                        this->height() - (*removed_button_it)->height()) );
  }
}

// Move the active button up
void PentSpinMenuPushButtonBox::moveActiveButtonUp()
{
  if( d_active_button )
  {
    if( d_button_order.size() > 1 )
    {
      d_active_button->deactivate();
      
      d_active_button = d_active_button->getUpButton();
      
      d_active_button->activate();
    }
  }
}

// Move the active button down
void PentSpinMenuPushButtonBox::moveActiveButtonDown()
{
  if( d_active_button )
  {
    if( d_button_order.size() > 1 )
    {
      d_active_button->deactivate();
    
      d_active_button = d_active_button->getDownButton();
    
      d_active_button->activate();
    }
  }
}

// Click the active button
void PentSpinMenuPushButtonBox::clickActiveButton()
{
  if( d_active_button )
    d_active_button->click();
}

// Reset active button (set to first)
void PentSpinMenuPushButtonBox::resetActiveButton()
{
  if( !d_button_order.empty() )
    d_active_button = d_button_order.front();
}

// Handle show events
void PentSpinMenuPushButtonBox::showEvent( QShowEvent* event )
{
    if( d_active_button )
    d_active_button->activate();

  QWidget::showEvent( event );
}

// Handle hide events
void PentSpinMenuPushButtonBox::hideEvent( QHideEvent* event )
{
  if( d_active_button )
    d_active_button->deactivate();
  
  QWidget::hideEvent( event );
}

// Handle a menu push button pressed
void PentSpinMenuPushButtonBox::handleMenuPushButtonPressed()
{
  QObject* raw_sender = QObject::sender();

  PentSpinMenuPushButton* sender =
    dynamic_cast<PentSpinMenuPushButton*>( raw_sender );

  if( sender )
  {
    if( d_active_button )
      d_active_button->deactivate();

    d_active_button = sender;
    d_active_button->activate();
  }
}

// Re-center the buttons
void PentSpinMenuPushButtonBox::recenterButtons()
{
  auto button_it = d_button_order.begin();

  while( button_it != d_button_order.end() )
  {
    (*button_it)->move( (this->width()-(*button_it)->width())/2,
                        (*button_it)->y() );
      
    ++button_it;
  }
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end PentSpinMenuPushButtonBox.cpp
//---------------------------------------------------------------------------//
