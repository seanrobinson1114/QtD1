//---------------------------------------------------------------------------//
//!
//! \file   NPCInteractionSubmenu.h
//! \author Alex Robinson
//! \brief  The NPC interaction submenu class declaration
//!
//---------------------------------------------------------------------------//

#ifndef NPC_INTERACTION_SUBMENU_H
#define NPC_INTERACTION_SUBMENU_H

// Std Lib Includes
#include <map>

// Qt Includes
#include <QWidget>
#include <QPushButton>
#include <QVector>

namespace QtD1{

//! The NPC interaction submenu class
class NPCInteractionSubmenu : public QWidget
{
  Q_OBJECT

public:

  //! The submenu type
  enum Type{
    Primary = 0,
    Discussion = 1,
    Trade = 2
  };

  //! Constructor
  NPCInteractionSubmenu( QWidget* parent = 0 );

  //! Destructor
  ~NPCInteractionSubmenu()
  { /* ... */ }

  //! Get the submenu type
  virtual Type getType() const = 0;

  //! Assign a submenu to a named button
  void assignSubmenuToNamedButton( const QString& button_name,
                                   NPCInteractionSubmenu* submenu );

  //! Assign an action to a named button
  void assignActionToNamedButton( const QString& button_name,
                                  QObject* obj,
                                  const char* action );

  //! Assign back submenu
  void assignBackSubmenu( NPCInteractionSubmenu* back_submenu );

signals:

  //! Show the submenu
  void showSubmenu( NPCInteractionSubmenu* submenu );

public slots:

  //! Move the active button up
  virtual void moveActiveButtonUp() = 0;

  //! Move the active button down
  virtual void moveActiveButtonDown() = 0;

  //! Click the active button
  virtual void clickActiveButton() = 0;

  //! Reset active button (set to first)
  virtual void resetActiveButton() = 0;

  //! Click the back button
  void clickBackButton();

protected slots:

  //! Handle named button pushed
  virtual void handleNamedButtonPushed();

  //! Handle back button pushed
  virtual void handleBackButtonPushed();

protected:

  //! Get the submenu frame
  static const QVector<QPixmap>& getFrames( const NPCInteractionSubmenu::Type type );

  //! Set the back button
  void setBackButton( QPushButton* back_button );

  //! Set the named buttons
  void setNamedButtons( const std::map<QString,QPushButton*>& named_buttons );

private:

  // Initialize a submenu frame
  static void initializeSubmenuFrame( NPCInteractionSubmenu::Type type );

  // Initialize the primary submenu frame
  static void initializePrimarySubmenuFrame();

  // Initialize the trade submenu frame
  static void initializeTradeSubmenuFrame();

  // The submenu frames
  static QVector<QVector<QPixmap> > s_frames;

  // The back button
  QPushButton* d_back_button;

  // The named buttons
  std::map<QString,QPushButton*> d_named_buttons;

  // The button connections
  std::map<QPushButton*,NPCInteractionSubmenu*> d_button_connections;

  // The back submenu
  NPCInteractionSubmenu* d_back_submenu;
};
  
} // end QtD1 namespace

#endif // end NPC_INTERACTION_SUBMENU_H

//---------------------------------------------------------------------------//
// end NPCInteractionSubmenu.h
//---------------------------------------------------------------------------//
