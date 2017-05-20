//---------------------------------------------------------------------------//
//!
//! \file   SpellBook
//! \author Alex Robinson, Sean Robinson
//! \brief  The spell book class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <utility>

// Qt Includes
#include <QImageReader>
#include <QShowEvent>

// QtD1 Includes
#include "SpellBook.h"

namespace QtD1{

// Initialize static member data
const QSize SpellBook::s_tab_size( 76, 29 );
const QSize SpellBook::s_hidden_tab_size( 0, 0 );

// Constructor
SpellBook::SpellBook( QWidget* parent )
  : QWidget( parent ),
    d_spell_pages(),
    d_spellbook_image( NULL ),
    d_tab_1_button( NULL ),
    d_tab_2_button( NULL ),
    d_tab_3_button( NULL ),
    d_tab_4_button( NULL ),
    d_page_1( NULL ),
    d_page_2( NULL ),
    d_page_3( NULL ),
    d_page_4( NULL ),
    d_active_page( NULL )
{
  // Load the spellbook image
  QImage background_image( "/data/spellbk.cel+levels/towndata/town.pal" );
  d_spellbook_image = new QLabel( this );
  d_spellbook_image->setPixmap( QPixmap::fromImage( background_image ) );
  d_spellbook_image->setFixedSize( background_image.size() );
  this->setFixedSize( d_spellbook_image->size() );

  this->loadSpellBookTabs();

  // connect spellbook tab slots to clicked signals and create key shortcuts
  QObject::connect( d_tab_1_button, SIGNAL( pressed() ), this, SLOT( showPage1() ) );
  d_tab_1_button->setShortcut( tr( "1" ) );
  QObject::connect( d_tab_2_button, SIGNAL( pressed() ), this, SLOT( showPage2() ) );
  d_tab_2_button->setShortcut( tr( "2" ) );
  QObject::connect( d_tab_3_button, SIGNAL( pressed() ), this, SLOT( showPage3() ) );
  d_tab_3_button->setShortcut( tr( "3" ) );
  QObject::connect( d_tab_4_button, SIGNAL( pressed() ), this, SLOT( showPage4() ) );
  d_tab_4_button->setShortcut( tr( "4" ) );
}

// Load the spellbook tab buttons
void SpellBook::loadSpellBookTabs()
{
  // Create the tab buttons
  QImageReader tab_button_reader( "/data/spellbkb.cel+levels/towndata/town.pal" );

  this->initializeTabButton( &d_tab_1_button, tab_button_reader.read() );
  tab_button_reader.jumpToNextImage();

  this->initializeTabButton( &d_tab_2_button, tab_button_reader.read() );
  tab_button_reader.jumpToNextImage();

  this->initializeTabButton( &d_tab_3_button, tab_button_reader.read() );
  tab_button_reader.jumpToNextImage();

  this->initializeTabButton( &d_tab_4_button, tab_button_reader.read() );
  tab_button_reader.jumpToNextImage();

  // Move the buttons to the correct locations
  d_tab_1_button->move( 8, 320 );
  d_tab_2_button->move( 84, 320 );
  d_tab_3_button->move( 160, 320 );
  d_tab_4_button->move( 236, 320 );
}

// Initialize tab button
void SpellBook::initializeTabButton( QPushButton** tab_button,
                                     const QImage& image )
{
  QIcon tab_icon( QPixmap::fromImage( image ) );
  
  *tab_button = new QPushButton( this );
  (*tab_button)->setFocusProxy( this );
  (*tab_button)->setStyleSheet( QString( "background: transparent" ) );
  (*tab_button)->setIcon( tab_icon );
  (*tab_button)->setIconSize( s_hidden_tab_size );
  (*tab_button)->resize( s_tab_size );
}

// Load the spells
void SpellBook::initializePages()
{
  // Initialize the spell order and description
  QVector<Spell::Type> spell_order( 28 );
  QVector<QString> spell_descriptions( 28 );
  QVector<std::pair<QPushButton*,QLabel*> > spells( 28 );

  this->initializeSpellOrderAndDescriptions( spell_order, spell_descriptions );

  // Load the spell icons
  QImageReader spell_image_reader( "/data/spelli2.cel+levels/towndata/town.pal" );
  
  // Set all of the spell icons and descriptions
  for( int i = 0; i < spells.size(); ++i )
  {
    spell_image_reader.jumpToImage( spell_order[i] );
    
    this->initializeSpell( &spells[i].first,
                           &spells[i].second,
                           spell_image_reader.read(),
                           spell_descriptions[i] );
  }
  
  // Insert the first 7 spell buttons and labels into page 1
  QVector<int> page_spell_indices{0,1,2,3,4,5,6};
  
  this->initializeSpellBookPage( &d_page_1,
                                 page_spell_indices.data(),
                                 spell_order,
                                 spells );
  // Unlock the character skill
  d_page_1->incrementSpellLevel( this->getClassSkill() );
  
  // Insert the next 7 spell buttons and labels into page 2
  page_spell_indices = {7,8,9,10,11,12,13};
  
  this->initializeSpellBookPage( &d_page_2,
                                 page_spell_indices.data(),
                                 spell_order,
                                 spells );
  
  // Insert the next 7 spell buttons and labels into page 3
  page_spell_indices = {14,15,16,17,18,19,20};
  
  this->initializeSpellBookPage( &d_page_3,
                                 page_spell_indices.data(),
                                 spell_order,
                                 spells );
  
  // Insert the final 7 spell buttons and labels into page 4
  page_spell_indices = {21,22,23,24,25,26,27};
  
  this->initializeSpellBookPage( &d_page_4,
                                 page_spell_indices.data(),
                                 spell_order,
                                 spells );

  // Set page 1 as the active page
  d_active_page = d_page_1;
  d_tab_1_button->setIconSize( s_tab_size );
}

// Initialize the spell order and descriptions
void SpellBook::initializeSpellOrderAndDescriptions(
                                         QVector<Spell::Type>& spell_order,
                                         QVector<QString>& spell_descriptions )
{
  spell_order.resize( 28 );
  spell_descriptions.resize( 28 );

  // The character skill is the first spell
  spell_order[0] = this->getClassSkill();

  switch( this->getClassSkill() )
  {
    case Spell::RepairItem :
    {
      spell_descriptions[0] = "REPAIR ITEM \n"
                              "SPELL LEVEL 0 \n"
                              "MANA: 6  DAMAGE: 1 - 10";
      break;
    }
    case Spell::DisarmTrap :
    {
      spell_descriptions[0] = "DISARM TRAP \n"
                              "SPELL LEVEL 0 \n"
                              "MANA: 6  DAMAGE: 1 - 10";
      break;
    }
    case Spell::RechargeStaff :
    {
      spell_descriptions[0] = "RECHARGE STAFF \n"
                              "SPELL LEVEL 0 \n"
                              "MANA: 6  DAMAGE: 1 - 10";
      break;
    }
    default :
    {
      qFatal( "Invalid character skill" );
      break;
    }
  }

  spell_order[1] = Spell::FireBolt;
  spell_descriptions[1] = "FIREBOLT \n"
                          "SPELL LEVEL 0 \n"
                          "MANA: 6  DAMAGE: 1 - 10";
  
  spell_order[2] = Spell::ChargedBolt;
  spell_descriptions[2] = "CHARGED BOLT \n"
                          "SPELL LEVEL 0 \n"
                          "MANA: 6  DAMAGE: 1 - 10";
  
  spell_order[3] = Spell::HolyBolt;
  spell_descriptions[3] = "HOLY BOLT \n"
                          "SPELL LEVEL 0 \n"
                          "MANA: 6  DAMAGE: 1 - 10";
  
  spell_order[4] = Spell::Heal;
  spell_descriptions[4] = "HEAL \n"
                          "SPELL LEVEL 0 \n"
                          "MANA: 6  DAMAGE: 1 - 10";
  
  spell_order[5] = Spell::HealOther;
  spell_descriptions[5] = "HEAL OTHER \n"
                          "SPELL LEVEL 0 \n"
                          "MANA: 6  DAMAGE: 1 - 10";
  
  spell_order[6] = Spell::Inferno;
  spell_descriptions[6] = "INFERNO \n"
                          "SPELL LEVEL 0 \n"
                          "MANA: 6  DAMAGE: 1 - 10";
  
  spell_order[7] = Spell::Resurrect;
  spell_descriptions[7] = "RESURRECT \n"
                          "SPELL LEVEL 0 \n"
                          "MANA: 6  DAMAGE: 1 - 10";
  
  spell_order[8] = Spell::FireWall;
  spell_descriptions[8] = "FIRE WALL \n"
                          "SPELL LEVEL 0 \n"
                          "MANA: 6  DAMAGE: 1 - 10";
  
  spell_order[9] = Spell::Telekinesis;
  spell_descriptions[9] = "TELEKINESIS \n"
                          "SPELL LEVEL 0 \n"
                          "MANA: 6  DAMAGE: 1 - 10";
  
  spell_order[10] = Spell::Lightning;
  spell_descriptions[10] = "LIGHTNING \n"
                           "SPELL LEVEL 0 \n"
                           "MANA: 6  DAMAGE: 1 - 10";
  
  spell_order[11] = Spell::TownPortal;
  spell_descriptions[11] = "TOWN PORTAL \n"
                           "SPELL LEVEL 0 \n"
                           "MANA: 6  DAMAGE: 1 - 10";
  
  spell_order[12] = Spell::Flash;
  spell_descriptions[12] = "FLASH \n"
                           "SPELL LEVEL 0 \n"
                           "MANA: 6  DAMAGE: 1 - 10";
  
  spell_order[13] = Spell::StoneCurse;
  spell_descriptions[13] = "STONE CURSE \n"
                           "SPELL LEVEL 0 \n"
                           "MANA: 6  DAMAGE: 1 - 10";
  
  spell_order[14] = Spell::Phasing;
  spell_descriptions[14] = "PHASING \n"
                           "SPELL LEVEL 0 \n"
                           "MANA: 6  DAMAGE: 1 - 10";
  
  spell_order[15] = Spell::ManaShield;
  spell_descriptions[15] = "MANA SHIELD \n"
                           "SPELL LEVEL 0 \n"
                           "MANA: 6  DAMAGE: 1 - 10";
  
  spell_order[16] = Spell::Elemental;
  spell_descriptions[16] = "ELEMENTAL \n"
                           "SPELL LEVEL 0 \n"
                           "MANA: 6  DAMAGE: 1 - 10";
  
  spell_order[17] = Spell::FireBall;
  spell_descriptions[17] = "FIREBALL \n"
                           "SPELL LEVEL 0 \n"
                           "MANA: 6  DAMAGE: 1 - 10";
  
  spell_order[18] = Spell::FlameWave;
  spell_descriptions[18] = "FLAME WAVE \n"
                           "SPELL LEVEL 0 \n"
                           "MANA: 6  DAMAGE: 1 - 10";
  
  spell_order[19] = Spell::ChainLightning;
  spell_descriptions[19] = "CHAIN LIGHTNING \n"
                           "SPELL LEVEL 0 \n"
                           "MANA: 6  DAMAGE: 1 - 10";
  
  spell_order[20] = Spell::Guardian;
  spell_descriptions[20] = "GUARDIAN \n"
                           "SPELL LEVEL 0 \n"
                           "MANA: 6  DAMAGE: 1 - 10";
  
  spell_order[21] = Spell::Nova;
  spell_descriptions[21] = "NOVA \n"
                           "SPELL LEVEL 0 \n"
                           "MANA: 6  DAMAGE: 1 - 10";
  
  spell_order[22] = Spell::Golem;
  spell_descriptions[22] = "GOLEM \n"
                           "SPELL LEVEL 0 \n"
                           "MANA: 6  DAMAGE: 1 - 10";
  
  spell_order[23] = Spell::Teleport;
  spell_descriptions[23] = "TELEPORT \n"
                           "SPELL LEVEL 0 \n"
                           "MANA: 6  DAMAGE: 1 - 10";
  
  spell_order[24] = Spell::Apocalypse;
  spell_descriptions[24] = "APOCALYPSE \n"
                           "SPELL LEVEL 0 \n"
                           "MANA: 6  DAMAGE: 1 - 10";
  
  spell_order[25] = Spell::BoneSpirit;
  spell_descriptions[25] = "BONE SPIRIT \n"
                           "SPELL LEVEL 0 \n"
                           "MANA: 6  DAMAGE: 1 - 10";
  
  spell_order[26] = Spell::BloodStar;
  spell_descriptions[26] = "BLOOD STAR \n"
                           "SPELL LEVEL 0 \n"
                           "MANA: 6  DAMAGE: 1 - 10";
  
  spell_order[27] = Spell::Etherealize;
  spell_descriptions[27] = "ETHEREALIZE \n"
                           "SPELL LEVEL 0 \n"
                           "MANA: 6  DAMAGE: 1 - 10";
}

// Initialize a spell
void SpellBook::initializeSpell( QPushButton** spell_button,
                                 QLabel** spell_description,
                                 const QImage& spell_icon_image,
                                 const QString& raw_description )
{
  *spell_button = new QPushButton( this );
  *spell_description = new QLabel( this );
  
  QIcon repair_item_icon( QPixmap::fromImage( spell_icon_image ) );
  (*spell_button)->setIcon( repair_item_icon );
  (*spell_description)->setText( raw_description );
}

// Initialize a spell book page
void SpellBook::initializeSpellBookPage(
                      SpellBookPage** spell_book_page,
                      const int spell_indices[7],
                      const QVector<Spell::Type>& spell_order,
                      const QVector<std::pair<QPushButton*,QLabel*> >& spells )
{
  // Assign the 7 spells of interest to this page
  QVector<Spell::Type> page_spell_order( 7 );
  QVector<std::pair<QPushButton*,QLabel*> > page_spells( 7 );

  for( int i = 0; i < 7; ++i )
  {
    int spell_index = spell_indices[i];

    page_spell_order[i] = spell_order[spell_index];
    page_spells[i] = spells[spell_index];
  }

  // Create the page
  *spell_book_page = new SpellBookPage( page_spells, page_spell_order, this );
  (*spell_book_page)->setFocusProxy( this );

  // Record which spells are managed by this page
  for( int i = 0; i < 7; ++i )
  {
    int spell_index = spell_indices[i];

    d_spell_pages[spell_order[spell_index]] = *spell_book_page;
  }
}

// Increment the spell level
void SpellBook::incrementSpellLevel( const Spell::Type spell )
{
  // Get the page that handles the spell
  if( d_spell_pages.find( spell ) != d_spell_pages.end() )
    d_spell_pages[spell]->incrementSpellLevel( spell );
  else
    qFatal( "Error: attempt to increment unknown spell!" );
}

// Handle tab 1 click
void SpellBook::showPage1()
{
  d_active_page = d_page_1;

  d_tab_1_button->setIconSize( s_tab_size );
  d_tab_2_button->setIconSize( s_hidden_tab_size );
  d_tab_3_button->setIconSize( s_hidden_tab_size );
  d_tab_4_button->setIconSize( s_hidden_tab_size );

  this->showActivePage();
}

// Handle tab 2 click
void SpellBook::showPage2()
{
  d_active_page = d_page_2;

  d_tab_1_button->setIconSize( s_hidden_tab_size );
  d_tab_2_button->setIconSize( s_tab_size );
  d_tab_3_button->setIconSize( s_hidden_tab_size );
  d_tab_4_button->setIconSize( s_hidden_tab_size );

  this->showActivePage();
}

// Handle tab 3 click
void SpellBook::showPage3()
{
  d_active_page = d_page_3;

  d_tab_1_button->setIconSize( s_hidden_tab_size );
  d_tab_2_button->setIconSize( s_hidden_tab_size );
  d_tab_3_button->setIconSize( s_tab_size );
  d_tab_4_button->setIconSize( s_hidden_tab_size );

  this->showActivePage();
}

// handle tab 4 click
void SpellBook::showPage4()
{
  d_active_page = d_page_4;

  d_tab_1_button->setIconSize( s_hidden_tab_size );
  d_tab_2_button->setIconSize( s_hidden_tab_size );
  d_tab_3_button->setIconSize( s_hidden_tab_size );
  d_tab_4_button->setIconSize( s_tab_size );

  this->showActivePage();
}

// Show active page
void SpellBook::showActivePage()
{
  this->hidePages();

  if( d_active_page )
  {
    d_active_page->show();
    d_active_page->raise();
  }

  this->raiseSpellBookTabs();
}

// Raise the spell book tabs
void SpellBook::raiseSpellBookTabs()
{
  d_tab_1_button->raise();
  d_tab_2_button->raise();
  d_tab_3_button->raise();
  d_tab_4_button->raise();
}

// Hide pages
void SpellBook::hidePages()
{
  d_page_1->hide();
  d_page_2->hide();
  d_page_3->hide();
  d_page_4->hide();
}

// Handle show events
void SpellBook::showEvent( QShowEvent* event )
{
  this->showActivePage();

  event->accept();
}

// Handle hide events
void SpellBook::hideEvent( QHideEvent* event )
{
  this->hidePages();

  event->accept();
}

//! Set the active spell
//void setActiveSpell( const std::shared_ptr<Spell>& spell );

//! Get the active spell
//const std::shared_ptr<Spell> getActiveSpell() const;

// void unlockSpellFromScroll( const std::shared_ptr<Spell>& spell );
// void unlockSpellFromStaff( const std::shared_ptr<Spell>& spell );
// void unlockSpellFromTome( const std::shared_ptr<Spell>& spell );
// void unlockSpellFromCharacter( const std::shared_ptr<Spell>& spell );

// void lockSpellFromScrollSpellCast( const std::shared_ptr<Spell>& spell );
// void lockSpellFromStaffDepleted( const std::shared_ptr<Spell>& spell );

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end SpellBook.cpp
//---------------------------------------------------------------------------//
