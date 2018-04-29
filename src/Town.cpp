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

  QList<std::shared_ptr<LevelSquare> > level_squares;
  QList<LevelPillar*> level_pillars;

  {
    LevelSquareFactory level_square_factory( level_min_file_name,
                                             level_sol_file_name,
                                             level_til_file_name );

    level_squares = level_square_factory.createLevelSquares();
  }

  // Create the top sector first
  LevelSector* top_sector =
    LevelSectorFactory::createLevelSector( "/levels/towndata/sector4s.dun",
                                           level_squares );

  // Create the left sector
  LevelSector* left_sector =
    LevelSectorFactory::createLevelSector( "/levels/towndata/sector3s.dun",
                                           level_squares );

  // Create the right sector
  LevelSector* right_sector =
    LevelSectorFactory::createLevelSector( "/levels/towndata/sector2s.dun",
                                           level_squares );

  // Create the bottom sector
  LevelSector* bottom_sector =
    LevelSectorFactory::createLevelSector( "/levels/towndata/sector1s.dun",
                                           level_squares );

  // Take pillars from all sectors and set in correct order
  QList<LevelPillar*> town_pillars;
  for( int i = 0; i < top_sector->getNumberOfRows() - 1; ++i )
  {
    QList<LevelSquare*> row_squares;
    row_squares = top_sector->getSquaresForRow( i );
    for( int j = 0; j < row_squares.length(); ++j )
    {
      town_pillars.append( row_squares[j]->getPillars() );
    }
    // std::cout << "number of pillars in top sector: " << town_pillars.length() << std::endl;
  }
  for( int i = 0; i < left_sector->getNumberOfRows() - 1; ++i )
  {
    QList<LevelSquare*> row_squares;
    row_squares = left_sector->getSquaresForRow( i );
    for( int j = 0; j < row_squares.length(); ++j )
    {
      town_pillars.append( row_squares[j]->getPillars() );
    }
    // std::cout << "number of pillars in left sector: " << town_pillars.length() << std::endl;
  }
  for( int i = 0; i < right_sector->getNumberOfRows() - 1; ++i )
  {
    QList<LevelSquare*> row_squares;
    row_squares = right_sector->getSquaresForRow( i );
    for( int j = 0; j < row_squares.length(); ++j )
    {
      town_pillars.append( row_squares[j]->getPillars() );
    }
    // std::cout << "number of pillars in top sector: " << town_pillars.length() << std::endl;
  }
  for( int i = 0; i < bottom_sector->getNumberOfRows() - 1; ++i )
  {
    QList<LevelSquare*> row_squares;
    row_squares = bottom_sector->getSquaresForRow( i );
    for( int j = 0; j < row_squares.length(); ++j )
    {
      town_pillars.append( row_squares[j]->getPillars() );
    }
    // std::cout << "number of pillars in top sector: " << town_pillars.length() << std::endl;
  }

  // Resize the town bounding rect
  int town_width = left_sector->boundingRect().width()+
    right_sector->boundingRect().width();
  int town_height = top_sector->boundingRect().height()+
    bottom_sector->boundingRect().height();

  this->setSceneRect( 0, 0, town_width, town_height );

  // Add the sectors to the town
  this->addItem( top_sector );
  this->addItem( left_sector );
  this->addItem( right_sector );
  this->addItem( bottom_sector );

  // Reposition the sectors
  top_sector->setPos( (town_width - top_sector->boundingRect().width())/2, 0 );
  left_sector->setPos( 64,
                       top_sector->boundingRect().height() -
                       left_sector->boundingRect().height()/2 - 112 );
  right_sector->setPos( town_width/2 - 64,
                        top_sector->boundingRect().height() -
                        right_sector->boundingRect().height()/2 - 48 );
  bottom_sector->setPos( (town_width - bottom_sector->boundingRect().width())/2,
                         top_sector->boundingRect().height() - 224 );

  // Add the sectors to the list
  sectors.clear();

  sectors << top_sector << left_sector << right_sector << bottom_sector;

  // Remove the sectors to the town
  this->removeItem( top_sector );
  this->removeItem( left_sector );
  this->removeItem( right_sector );
  this->removeItem( bottom_sector );

  // Set parent and add pillars to the town
  for( int i = 0; i < town_pillars.length(); ++i )
  {
    town_pillars[i]->setPos( town_pillars[i]->mapToScene( QPoint( 0, 0 ) ) );
    town_pillars[i]->setParent( NULL );
    this->addItem( town_pillars[i] );
    std::cout << "z value of added pillar: " << town_pillars[i]->zValue() << std::endl;

  }
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Town.cpp
//---------------------------------------------------------------------------//
