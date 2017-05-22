//---------------------------------------------------------------------------//
//!
//! \file   Town.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The town class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "Town.h"
#include "LevelSquareFactory.h"
#include "LevelSectorFactory.h"

namespace QtD1{

//! Constructor
Town::Town( QObject* parent )
  : Level( parent, "/music/dtowne.wav" )
{ /* ... */ }

// Get the type
Level::Type Town::getType() const
{
  return Level::Town;
}

// Get the number
int Town::getNumber() const
{
  return -1;
}

// Get the image asset name
QString Town::getImageAssetName() const
{
  return "/levels/towndata/town.cel+levels/towndata/town.pal";
}

// Insert the character
void Town::insertCharacter( Character* character,
                            const QPointF& location,
                            const Direction direction )
{
  Level::insertCharacter( character, location, direction );

  character->enterTown();
}

// Remove the character
void Town::removeCharacter()
{
  this->getCharacter()->exitTown();
  
  Level::removeCharacter();
}

// Create the level sectors
void Town::createSectors( QList<LevelSector*>& sectors )
{
  QString level_min_file_name( "/levels/towndata/town.min" );
  QString level_sol_file_name( "/levels/towndata/town.sol" );
  QString level_til_file_name( "/levels/towndata/town.til" );

  QList<LevelSquare*> level_squares;

  {
    LevelSquareFactory level_square_factory( level_min_file_name,
                                             level_til_file_name );

    level_squares = level_square_factory.createLevelSquares();
  }
  
  // Create the top sector first
  LevelSector* top_sector =
    this->createSector( level_min_file_name,
                        level_til_file_name,
                        "/levels/towndata/sector4s.dun",
                        level_squares );

  // Create the left sector
  LevelSector* left_sector =
    this->createSector( level_min_file_name,
                        level_til_file_name,
                        "/levels/towndata/sector3s.dun",
                        level_squares );

  // Create the right sector
  LevelSector* right_sector =
    this->createSector( level_min_file_name,
                        level_til_file_name,
                        "/levels/towndata/sector2s.dun",
                        level_squares );

  // Create the bottom sector
  LevelSector* bottom_sector =
    this->createSector( level_min_file_name,
                        level_til_file_name,
                        "/levels/towndata/sector1s.dun",
                        level_squares );

  // Resize the town bounding rect
  this->setSceneRect( 0, 0,
                      left_sector->width()+right_sector->width(),
                      top_sector->height()+bottom_sector->height() );

  // Reposition the sectors
  top_sector->setPos( top_sector->width()/2, 0 );
  left_sector->setPos( 0, left_sector->height()/2 );
  right_sector->setPos( right_sector->width(), right_sector->height()/2 );
  bottom_sector->setPos( bottom_sector->width()/2, bottom_sector->height() );

  // Add the sectors to the town
  this->addItem( top_sector );
  this->addItem( left_sector );
  this->addItem( right_sector );
  this->addItem( bottom_sector );

  // Add the sectors to the list
  sectors.clear();

  sectors << top_sector << left_sector << right_sector << bottom_sector;
}

// Create a sector
LevelSector* Town::createSector( const QString& level_min_file_name,
                                 const QString& level_til_file_name,
                                 const QString& level_dun_file_name,
                                 const QList<LevelSquare*> level_squares )
{
  LevelSectorFactory sector_factory( level_min_file_name,
                                     level_til_file_name,
                                     level_dun_file_name );

  return sector_factory.createLevelSector( level_squares );
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Town.cpp
//---------------------------------------------------------------------------//
