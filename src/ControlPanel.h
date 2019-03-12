//---------------------------------------------------------------------------//
//!
//! \file   ControlPanel.h
//! \author Sean Robinson, Alex Robinson
//! \brief  The control panel class declaration
//!
//---------------------------------------------------------------------------//

#ifndef CONTROL_PANEL_H
#define CONTROL_PANEL_H

// QtD1 Includes
#include "Character.h"

// Std Lib Includes
#include <memory>
#include <tuple>

// Qt Includes
#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QPushButton>

namespace QtD1{

//! The spell book class
class ControlPanel : public QWidget
{
  Q_OBJECT

public:

  //! Constructor
  ControlPanel( QWidget* parent = 0 );

  //! Destructor
  ~ControlPanel()
  { /* ... */ }

  //! Set the y position
  void setYPosition( const int y_pos );

signals:

  void showCharacterStats();
  void hideCharacterStats();
  void showQuestLog();
  void hideQuestLog();
  void showGameMenu();
  void hideGameMenu();
  void showInventory();
  void hideInventory();
  void showSpellBook();
  void hideSpellBook();

public slots:

  //! Check status of the char button and emit signal
  void toggleCharacterStats();

  //! Check the status of quest button and emit signal
  void toggleQuestLog();

  //! Check the status of the menu button and emit signal
  void toggleGameMenu();

  //! Hide the game menu button
  void hideMenuButton();

  //! Check the status of the inv button and emit signal
  void toggleInventory();

  //! Check the status of the spell button and emit signal
  void toggleSpellBook();

  //! Change object description display
  void changeObjectDescriptionDisplay( QString objectDescription );

  //! Activate the control panel focus shortcuts
  void activateFocusShortcuts();
  
  //! Deactivate the control panel focus shortcuts
  void deactivateFocusShortcuts();

  //! Update character health
  void updateCharacterHealth( const int health, const int max_health );

  //! Update character mana
  void updateCharacterMana( const int mana, const int max_mana );

private:

  // Load the control panel images
  void loadControlPanelImages( QImage& background,
                               QImage& health_bulb_full,
                               QImage& mana_bulb_full ) const;

  // Initialize the control panel buttons
  void loadControlPanelButtons();

  // Initialize the control panel hover display
  void loadHoverDisplay();

  // Initialize tab button
  void initializeControlPanelButton( QPushButton** panel_button,
                                     const QImage& image );

  // Connect the buttons with signals
  void connectButtonsToSignals();

  // The activated control panel button size
  static const QSize s_active_button_size;

  // The non active control panel button size
  static const QSize s_hidden_button_size;

  // The char button
  QPushButton* d_char_button;

  // The quest button
  QPushButton* d_quest_button;

  // The menu button
  QPushButton* d_menu_button;

  // The inv button
  QPushButton* d_inv_button;

  // The spell button
  QPushButton* d_spell_button;

  // The background
  QLabel* d_background;

  // The hovered object display
  QLabel* d_hover_display;

  // The health bulb region
  QLabel* d_health_bulb_region;
  
  // The health bulb
  QLabel* d_health_bulb;

  // The mana bulb region
  QLabel* d_mana_bulb_region;
  
  // The mana bulb
  QLabel* d_mana_bulb;
};

} // end QtD1 namespace

#endif // end CONTROL_PANEL_H

//---------------------------------------------------------------------------//
// end ControlPanel.h
//---------------------------------------------------------------------------//
