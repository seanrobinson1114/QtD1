//---------------------------------------------------------------------------//
//!
//! \file   PrimaryNPCInteractionSubmenu.h
//! \author Alex Robinson
//! \brief  The primary NPC interaction submenu class declaration
//!
//---------------------------------------------------------------------------//

#ifndef PRIMARY_NPC_INTERACTION_SUBMENU_H
#define PRIMARY_NPC_INTERACTION_SUBMENU_H

// QtD1 Includes
#include "NPCInteractionSubmenu.h"

namespace QtD1{

class PentSpinMenuPushButtonBox;

//! The primary NPC interaction submenu 
class PrimaryNPCInteractionSubmenu : public NPCInteractionSubmenu
{
  Q_OBJECT

public:

  //! Constructor
  PrimaryNPCInteractionSubmenu( const QString& title_text,
                                const QString& npc_talk_button_name,
                                const QList<QString>& extra_button_names,
                                const QString& back_button_name,
                                QWidget* parent = 0 );

  //! Destructor
  ~PrimaryNPCInteractionSubmenu()
  { /* ... */ }

  //! Get the submenu type
  Type getType() const final override;

signals:

  //! Exit the menu
  void exit();

public slots:

  //! Move the active button up
  void moveActiveButtonUp() final override;

  //! Move the active button down
  void moveActiveButtonDown() final override;
  
  //! Click the active button
  void clickActiveButton() final override;

  //! Reset active button (set to first)
  void resetActiveButton() final override;

protected slots:

  //! Handle back button pushed
  void handleBackButtonPushed() final override;

private:

  // The button box
  PentSpinMenuPushButtonBox* d_button_box;
};
  
} // end QtD1 namespace

#endif // end PRIMARY_NPC_INTERACTION_SUBMENU_H

//---------------------------------------------------------------------------//
// end PrimaryNPCInteractionSubmenu.h
//---------------------------------------------------------------------------//
