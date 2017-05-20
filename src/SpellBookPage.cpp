//---------------------------------------------------------------------------//
//!
//! \file   SpellBookPage
//! \author Alex Robinson, Sean Robinson
//! \brief  The spell book page class declaration
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "SpellBookPage.h"

// Std Lib Includes
#include <memory>
#include <tuple>

// Qt Includes
#include <QGraphicsObject>
#include <QMap>
#include <QShowEvent>

namespace QtD1{

//! Constructor
SpellBookPage::SpellBookPage( const QVector<SpellData> raw_spells,
                              const QVector<Spell::Type> spell_order,
                              QWidget* parent )
  : QWidget( parent ),
    d_spells(),
    d_unlocked_spells()
{
  if( raw_spells.size() != 7 || spell_order.size() != 7 )
    qFatal( "SpellBookPages can only store 7 spells" );

  if( parent )
    this->setFixedSize( parent->size() );
  
  this->processSpells( raw_spells, spell_order );
}

//! Load the spells
void SpellBookPage::processSpells( const QVector<SpellData>& raw_spells,
                                   const QVector<Spell::Type>& spell_order )
{
  QPoint button_location( 11, 18 ), label_location( 60, 20 );
  
  for( int i = 0; i < raw_spells.size(); ++i )
  {
    // Add the spell data to the spell data map
    Spell::Type spell = spell_order[i];

    // The stored spell will have a default level of 0 (locked spell)
    d_spells[spell] = std::make_tuple( std::get<0>(raw_spells[i]),
                                       std::get<1>(raw_spells[i]),
                                       0 );

    // Set the focus proxy and size for the spell button
    QPushButton* spell_button = std::get<0>( raw_spells[i] );
    spell_button->setParent( this );
    spell_button->setFocusProxy( this );
    spell_button->resize( 37, 38 );
    spell_button->setIconSize( QSize( 37, 38 ) );

    // Set the position of the spell button
    spell_button->move( button_location );
    
    button_location.ry() += 43;

    // Set the focus proxy and size for the spell label
    QLabel* spell_label = std::get<1>( raw_spells[i] );
    spell_label->setParent( this );
    spell_label->resize( 200, 35 );
    spell_label->setStyleSheet( QString( "background-color: black; color: white; font-family: monospace; font-size: 11px" ) );

    // Set the position of the spell label
    spell_label->move( label_location );

    label_location.ry() += 43;

    // Locked spells must be hidden
    spell_button->hide();
    spell_label->hide();
  }
}

// Increment spell level
void SpellBookPage::incrementSpellLevel( Spell::Type spell )
{
  if( d_spells.find( spell ) != d_spells.end() )
  {
    ExtendedSpellData& spell_data = d_spells[spell];

    int& spell_level = std::get<2>( spell_data );

    ++spell_level;
    
    if( spell_level == 1 )
      this->unlockSpell( spell );

    this->update();
  }
  else
  {
    qFatal( "Error: cannot increment the spell because it is not managed by "
            "this spell book page!" );
  }
}

// Unlock spell
void SpellBookPage::unlockSpell( Spell::Type unlocked_spell )
{
  if( d_spells.find( unlocked_spell ) != d_spells.end() )
  {
    ExtendedSpellData& spell_data = d_spells[unlocked_spell];
  
    d_unlocked_spells.insert( &spell_data );
  }
  else
  {
    qFatal( "Error: cannot unlock the spell because it is not managed by this "
            "spell book page!" );
  }
}

// Handle show events
void SpellBookPage::showEvent( QShowEvent* event )
{
  UnlockedSpells::iterator unlocked_spells_it, unlocked_spells_end;
  unlocked_spells_it = d_unlocked_spells.begin();
  unlocked_spells_end = d_unlocked_spells.end();

  while( unlocked_spells_it != unlocked_spells_end )
  {
    std::get<0>( **unlocked_spells_it )->show();
    std::get<0>( **unlocked_spells_it )->raise();
    
    std::get<1>( **unlocked_spells_it )->show();
    std::get<1>( **unlocked_spells_it )->raise();
        
    ++unlocked_spells_it;
  }

  event->accept();
}

// Handle hide events
void SpellBookPage::hideEvent( QHideEvent* event )
{
  ExtendedSpellDataMap::iterator spell_it, spell_end;
  spell_it = d_spells.begin();
  spell_end = d_spells.end();

  while( spell_it != spell_end )
  {
    std::get<0>( spell_it.value() )->hide();
    std::get<1>( spell_it.value() )->hide();

    ++spell_it;
  }

  event->accept();
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end SpellBookPage.cpp
//---------------------------------------------------------------------------//
