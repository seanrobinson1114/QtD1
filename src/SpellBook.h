//---------------------------------------------------------------------------//
//!
//! \file   SpellBook
//! \author Alex Robinson, Sean Robinson
//! \brief  The spell book class declaration
//!
//---------------------------------------------------------------------------//

#ifndef SPELL_BOOK_H
#define SPELL_BOOK_H

// QtD1 Includes
#include "Spell.h"
#include "SpellBookPage.h"

// Std Lib Includes
#include <memory>
#include <tuple>

// Qt Includes
#include <QGraphicsObject>
#include <QMap>
#include <QHBoxLayout>
#include <QPushButton>

namespace QtD1{

//! The spell book class
class SpellBook : public QWidget
{
  Q_OBJECT

public:

  //! The spell state enum
  enum SpellState{
    NoSpellEquiped,
    NonElementalSpellEquiped,
    FireSpellEquiped,
    LightningSpellEquiped
  };

  //! Constructor
  SpellBook( QWidget* parent = 0 );

  //! Destructor
  ~SpellBook()
  { /* ... */ }

  //! Set the active spell
  //void setActiveSpell( const std::shared_ptr<Spell>& spell );

  //! Get the active spell
  //const std::shared_ptr<Spell> getActiveSpell() const

  //! Initialize the spell book pages
  void initializePages();

  //! Clone the spell book
  virtual SpellBook* clone( QWidget* parent = 0 ) const = 0;

signals:

  // void spellUnlocked( const std::shared_ptr<Spell>& spell );
  // void spellLocked( const std::shared_ptr<Spell>& spell );
  void spellChanged( const SpellBook::SpellState state );

public slots:

  //! Show page 1
  void showPage1();

  //! Show page 2
  void showPage2();

  //! Show page 3
  void showPage3();

  //! Show page 4
  void showPage4();

  //! Increment the spell level
  void incrementSpellLevel( const Spell::Type spell );

  // void unlockSpellFromScroll( const std::shared_ptr<Spell>& spell );
  // void unlockSpellFromStaff( const std::shared_ptr<Spell>& spell );
  // void unlockSpellFromTome( const std::shared_ptr<Spell>& spell );
  // void unlockSpellFromCharacter( const std::shared_ptr<Spell>& spell );

  // void lockSpellFromScrollSpellCast( const std::shared_ptr<Spell>& spell );
  // void lockSpellFromStaffDepleted( const std::shared_ptr<Spell>& spell );

protected:

  // Get the classes inherint skill
  virtual Spell::Type getClassSkill() = 0;

  //! Handle show events
  void showEvent( QShowEvent* event ) override;

  //! Handle hide events
  void hideEvent( QHideEvent* event ) override;

private:

  //! Load the spellbook tab buttons
  void loadSpellBookTabs();

  // Initialize tab button
  void initializeTabButton( QPushButton** tab_button, const QImage& image );

  // Initialize the spell order and descriptions
  void initializeSpellOrderAndDescriptions(
                                        QVector<Spell::Type>& spell_order,
                                        QVector<QString>& spell_descriptions );

  // Initialize a spell
  void initializeSpell( QPushButton** spell_button,
                        QLabel** spell_description,
                        const QImage& spell_icon_image,
                        const QString& raw_description );

  // Initialize a spell book page
  void initializeSpellBookPage(
                     SpellBookPage** spell_book_page,
                     const int spell_indices[7],
                     const QVector<Spell::Type>& spell_order,
                     const QVector<std::pair<QPushButton*,QLabel*> >& spells );

  // Show active page
  void showActivePage();

  // Raise the spellbook tabs
  void raiseSpellBookTabs();

  // Hide pages
  void hidePages();

  // The spell page tab size
  static const QSize s_tab_size;

  // The hidden spell page tab size
  static const QSize s_hidden_tab_size;

  // Spells and corresponding spell book page
  QMap<Spell::Type, SpellBookPage*> d_spell_pages;

  // The spellbook image
  QLabel* d_spellbook_image;

  // The tab_1 button
  QPushButton* d_tab_1_button;

  // The tab_2 button
  QPushButton* d_tab_2_button;

  // The tab_3 button
  QPushButton* d_tab_3_button;

  // The tab_4 button
  QPushButton* d_tab_4_button;

  // The first spell book page
  SpellBookPage* d_page_1;

  // The second spell book page_1
  SpellBookPage* d_page_2;

  // The third spell book page_2
  SpellBookPage* d_page_3;

  // The fourth spell book page_3
  SpellBookPage* d_page_4;

  // The active spell book page and button
  SpellBookPage* d_active_page;
};

} // end QtD1 namespace

#endif // end SPELL_BOOK_H

//---------------------------------------------------------------------------//
// end SpellBook.h
//---------------------------------------------------------------------------//
