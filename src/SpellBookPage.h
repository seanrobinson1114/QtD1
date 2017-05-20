//---------------------------------------------------------------------------//
//!
//! \file   SpellBookPage
//! \author Alex Robinson, Sean Robinson
//! \brief  The spell book page class declaration
//!
//---------------------------------------------------------------------------//

#ifndef SPELL_BOOK_PAGE_H
#define SPELL_BOOK_PAGE_H

// QtD1 Includes
#include "Spell.h"

// Std Lib Includes
#include <memory>
#include <tuple>

// Qt Includes
#include <QWidget>
#include <QVector>
#include <QMap>
#include <QSet>
#include <QLabel>
#include <QPushButton>

namespace QtD1{

//! The spell book class
class SpellBookPage : public QWidget
{
  Q_OBJECT

public:

  // The spell data type (int => level)
  typedef std::pair<QPushButton*,QLabel*> SpellData;
  
  //! Constructor
  SpellBookPage( const QVector<SpellData> raw_spells,
                 const QVector<Spell::Type> spell_order,
                 QWidget* parent = 0 );

  //! Destructor
  ~SpellBookPage()
  { /* ... */ }

signals:

  //void spellChanged( const SpellBook::SpellState state );

public slots:

  //! Increment spell level
  void incrementSpellLevel( Spell::Type spell );

protected:

  //! Handle show events
  void showEvent( QShowEvent* event ) override;

  //! Handle hide events
  void hideEvent( QHideEvent* event ) override;

private:

  // process the spells
  void processSpells( const QVector<SpellData>& raw_spells,
                      const QVector<Spell::Type>& spell_order );

  //! Unlock spell
  void unlockSpell( Spell::Type spell );

  // The extended spell data type (int => level)
  typedef std::tuple<QPushButton*,QLabel*,int> ExtendedSpellData;

  // The extended spell data map
  typedef QMap<Spell::Type, ExtendedSpellData> ExtendedSpellDataMap;
  
  ExtendedSpellDataMap d_spells;

  // The unlocked spells
  typedef QSet<ExtendedSpellData*> UnlockedSpells;
  UnlockedSpells d_unlocked_spells;
};

} // end QtD1 namespace

#endif // end SPELL_BOOK_PAGE_H

//---------------------------------------------------------------------------//
// end SpellBookPage.h
//---------------------------------------------------------------------------//
