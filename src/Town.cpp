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
#include "Grid.h"
#include "Farnham.h"
#include "Adria.h"
#include "Ogden.h"
#include "Gillian.h"
#include "Pepin.h"
#include "Deckard.h"

namespace QtD1{

// Constructor
Town::Town( QObject* parent )
  : Level( parent, "/music/dtowne.wav" ),
    d_farnham( NULL ),
    d_adria( NULL ),
    d_ogden( NULL ),
    d_gillian( NULL ),
    d_pepin( NULL ),
    d_deckard( NULL )
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

// Create the level NPCs and actors
void Town::createNPCsAndActors( QVector<NPC*>& npcs, QVector<Actor*>& )
{
  // This memory will be managed by the scene
  d_farnham = new Farnham;
  d_adria = new Adria;
  d_ogden = new Ogden;
  d_gillian = new Gillian;
  d_pepin = new Pepin;
  d_deckard = new Deckard;

  this->addLevelObject( d_farnham, QPointF( 0, 0 ) );
  this->addLevelObject( d_adria, QPointF( 0, 0 ) );
  this->addLevelObject( d_ogden, QPointF( 0, 0 ) );
  this->addLevelObject( d_gillian, QPointF( 0, 0 ) );
  this->addLevelObject( d_pepin, QPointF( 0, 0 ) );
  this->addLevelObject( d_deckard, QPointF( 0, 0 ) );

  npcs << d_farnham;
  npcs << d_adria;
  npcs << d_ogden;
  npcs << d_gillian;
  npcs << d_pepin;
  npcs << d_deckard;
}

// Activate the NPCs and actors
void Town::activateNPCsAndActors( QWidget* parent_widget )
{
  // Activate Farnham and load interactive menu
  d_farnham->setPos( 2600, 2640 );
  d_farnham->activate();
  d_farnham->startStateMachine();
  d_farnham->loadInteractionMenu( parent_widget );

  // Activate Adria and load interactive menu
  d_adria->setPos( 4945, 1760 );
  d_adria->activate();
  d_adria->startStateMachine();
  d_adria->loadInteractionMenu( parent_widget );

  // Activate Ogden and load interactive menu
  d_ogden->setPos( 2790, 2025 );
  d_ogden->activate();
  d_ogden->startStateMachine();
  d_ogden->loadInteractionMenu( parent_widget );

  // Activate Gillian and load interactive menu
  d_gillian->setPos( 2288, 1910 );
  d_gillian->activate();
  d_gillian->startStateMachine();
  d_gillian->loadInteractionMenu( parent_widget );

  // Activate Pepin and load interactive menu
  d_pepin->setPos( 2255, 2305 );
  d_pepin->activate();
  d_pepin->startStateMachine();
  d_pepin->loadInteractionMenu( parent_widget );

  // Activate Deckard and load interactive menu
  d_deckard->setPos( 2740, 2285 );
  d_deckard->activate();
  d_deckard->startStateMachine();
  d_deckard->loadInteractionMenu( parent_widget );
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
  }
  for( int i = 0; i < left_sector->getNumberOfRows() - 1; ++i )
  {
    QList<LevelSquare*> row_squares;
    row_squares = left_sector->getSquaresForRow( i );
    for( int j = 0; j < row_squares.length(); ++j )
    {
      town_pillars.append( row_squares[j]->getPillars() );
    }
  }
  for( int i = 0; i < right_sector->getNumberOfRows() - 1; ++i )
  {
    QList<LevelSquare*> row_squares;
    row_squares = right_sector->getSquaresForRow( i );
    for( int j = 0; j < row_squares.length(); ++j )
    {
      town_pillars.append( row_squares[j]->getPillars() );
    }
  }
  for( int i = 0; i < bottom_sector->getNumberOfRows() - 1; ++i )
  {
    QList<LevelSquare*> row_squares;
    row_squares = bottom_sector->getSquaresForRow( i );
    for( int j = 0; j < row_squares.length(); ++j )
    {
      town_pillars.append( row_squares[j]->getPillars() );
    }
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

  // Remove the sectors from the town
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
    town_pillars[i]->activate();

    if( town_pillars[i]->isInteractive() )
      this->connectInteractiveLevelObjectSignalsToLevelSignals( town_pillars[i] );
  }

  // Initialize the grid used for pathfinding
  this->setGrid( std::make_shared<Grid>( 96, 96, town_pillars ) );
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Town.cpp
//---------------------------------------------------------------------------//
