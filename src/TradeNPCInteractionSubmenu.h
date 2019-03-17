//---------------------------------------------------------------------------//
//!
//! \file   TradeNPCInteractionSubmenu.h
//! \author Alex Robinson
//! \brief  The trade NPC interaction submenu class declaration
//!
//---------------------------------------------------------------------------//

#ifndef TRADE_NPC_INTERACTION_SUBMENU_H
#define TRADE_NPC_INTERACTION_SUBMENU_H

// Qt Includes
#include <QLabel>
#include <QPushButton>

// QtD1 Includes
#include "NPCInteractionSubmenu.h"

namespace QtD1{

class Character;
class PentSpinMenuPushButtonBox;

//! The trade NPC interaction submenu
class TradeNPCInteractionSubmenu : public NPCInteractionSubmenu
{
  Q_OBJECT

public:

  //! Constructor
  TradeNPCInteractionSubmenu( const QString& primary_title_text,
                              const QString& secondary_title_text,
                              const QString& question_text,
                              const QString& back_button_name,
                              Character* character,
                              QWidget* parent = 0 );

  //! Destructor
  ~TradeNPCInteractionSubmenu()
  { /* ... */ }

  //! Get the submenu type
  Type getType() const final override;

public slots:

  //! Move the active button up
  void moveActiveButtonUp() final override;

  //! Move the active button down
  void moveActiveButtonDown() final override;
  
  //! Click the active button
  void clickActiveButton() final override;

  //! Reset active button (set to first)
  void resetActiveButton() final override;

private:

  // The item scroll box
  QLabel* d_item_scroll_box;

  // The item button box
  PentSpinMenuPushButtonBox* d_item_button_box;

  // The scroll bar
  QWidget* d_item_scroll_bar;

  // The item prompt box
  QLabel* d_item_prompt_box;

  // The item display box
  QLabel* d_item_display_box;

  // The item prompt yes/no button box
  PentSpinMenuPushButtonBox* d_item_prompt_yes_no_button_box;
};
  
} // end QtD1 namespace

#endif // end TRADE_NPC_INTERACTION_SUBMENU_H

//---------------------------------------------------------------------------//
// end TradeNPCInteractionSubmenu.h
//---------------------------------------------------------------------------//
