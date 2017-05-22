//---------------------------------------------------------------------------//
//!
//! \file   LevelPillarFactory.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The level pillar factory class definition
//!
//---------------------------------------------------------------------------//

// Qt Includes
#include <QDataStream>
#include <QFile>
#include <QBuffer>

// QtD1 Includes
#include "LevelPillarFactory.h"
#include "TownLevelPillar.h"

namespace QtD1{

// Constructor
LevelPillarFactory::LevelPillarFactory( const QString& level_min_file_name )
  : d_level_min_file_name( level_min_file_name )
{
  if( !level_min_file_name.contains( ".min" ) )
  {
    qFatal( "LevelPillarFactory Error: cannot parse file %s (only .min files "
            "can be parsed)!",
            level_min_file_name.toStdString().c_str() );
  }
}

// Create the level pillars
QList<LevelPillar*> LevelPillarFactory::createLevelPillars() const
{
  // Create a new pillar list
  QList<LevelPillar*> level_pillars;

  // Open the min file
  QFile min_file( d_level_min_file_name );
  min_file.open( QIODevice::ReadOnly );

  // Extract the min file data
  QDataStream stream( &min_file );
  stream.setByteOrder( QDataStream::LittleEndian );

  LevelPillarFactory::LevelPillarNumBlocksFunction blocks_per_pillar =
    this->getLevelPillarNumBlocksFunction();

  LevelPillarCreationFunction create_pillar =
    this->getLevelPillarCreationFunction();

  while( true )
  {
    if( stream.atEnd() )
      break;

    // Read a section of blocks from the file
    QVector<LevelPillar::Block> blocks( blocks_per_pillar() );

    for( int i = 0; i < blocks.size(); ++i )
    {
      quint16 raw_data;

      stream >> raw_data;

      // Indexing in the min file starts at 1 (shift left to 0)
      blocks[i].frame_index = raw_data & 0x0FFF - 1;

      if( blocks[i].frame_index >= 0 )
      {
        blocks[i].transparent = false;
        blocks[i].type = (raw_data & 0x7000) >> 12;
      }
      else
      {
        blocks[i].transparent = true;
        blocks[i].type = -1;
      }
    }

    // Create the pillar
    level_pillars << create_pillar( blocks );
  }

  return level_pillars;
}

// Get the number of blocks in a town pillar
int LevelPillarFactory::getNumberOfBlocksInTownPillar()
{
  return 16;
}

// Get the number of blocks in a cathedral pillar
int LevelPillarFactory::getNumberOfBlocksInCathedralPillar()
{
  return 10;
}

// Get the number of blocks in a catacomb pillar
int LevelPillarFactory::getNumberOfBlocksInCatacombPillar()
{
  return 10;
}

// Get the number of blocks in a cave pillar
int LevelPillarFactory::getNumberOfBlocksInCavePillar()
{
  return 10;
}

// Get the number of blocks in a hell pillar
int LevelPillarFactory::getNumberOfBlocksInHellPillar()
{
  return 16;
}

// Create a town pillar
LevelPillar* LevelPillarFactory::createTownPillar( const QVector<LevelPillar::Block>& blocks )
{
  return new TownLevelPillar( blocks );
}

// Create a cathedral pillar
LevelPillar* LevelPillarFactory::createCathedralPillar( const QVector<LevelPillar::Block>& )
{
  qFatal( "Cathedral pillar not implemented" );
}

// Create a catacomb pillar
LevelPillar* LevelPillarFactory::createCatacombPillar( const QVector<LevelPillar::Block>& )
{
  qFatal( "Catacomb pillar not implemented" );
}

// Create a cave pillar
LevelPillar* LevelPillarFactory::createCavePillar( const QVector<LevelPillar::Block>& )
{
  qFatal( "Cave pillar not implemented" );
}

// Create a hell pillar
LevelPillar* LevelPillarFactory::createHellPillar( const QVector<LevelPillar::Block>& )
{
  qFatal( "Hell pillar not implemented" );
}

// Get the number of pillar blocks function
LevelPillarFactory::LevelPillarNumBlocksFunction LevelPillarFactory::getLevelPillarNumBlocksFunction() const
{
  if( d_level_min_file_name.contains( "town.min" ) )
    return &LevelPillarFactory::getNumberOfBlocksInTownPillar;
  if( d_level_min_file_name.contains( "l1.min" ) )
    return &LevelPillarFactory::getNumberOfBlocksInCathedralPillar;
  if( d_level_min_file_name.contains( "l2.min" ) )
    return &LevelPillarFactory::getNumberOfBlocksInCatacombPillar;
  if( d_level_min_file_name.contains( "l3.min" ) )
    return &LevelPillarFactory::getNumberOfBlocksInCavePillar;
  if( d_level_min_file_name.contains( "l4.min" ) )
    return &LevelPillarFactory::getNumberOfBlocksInHellPillar;
  else
  {
    qFatal( "LevelPillarFactory Error: Invalid min file %s!",
            d_level_min_file_name.toStdString().c_str() );
  }
}

// Get the pillar creation function
LevelPillarFactory::LevelPillarCreationFunction LevelPillarFactory::getLevelPillarCreationFunction() const
{
  if( d_level_min_file_name.contains( "town.min" ) )
    return &LevelPillarFactory::createTownPillar;
  if( d_level_min_file_name.contains( "l1.min" ) )
    return &LevelPillarFactory::createCathedralPillar;
  if( d_level_min_file_name.contains( "l2.min" ) )
    return &LevelPillarFactory::createCatacombPillar;
  if( d_level_min_file_name.contains( "l3.min" ) )
    return &LevelPillarFactory::createCavePillar;
  if( d_level_min_file_name.contains( "l4.min" ) )
    return &LevelPillarFactory::createHellPillar;
  else
  {
    qFatal( "LevelPillarFactory Error: Invalid min file %s!",
            d_level_min_file_name.toStdString().c_str() );
  }
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end LevelPillarFactory.cpp
//---------------------------------------------------------------------------//
