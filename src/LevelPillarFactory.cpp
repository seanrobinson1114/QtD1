//---------------------------------------------------------------------------//
//!
//! \file   LevelPillarFactory.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The level pillar factory class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Qt Includes
#include <QDataStream>
#include <QFile>
#include <QBuffer>
#include <QList>
#include <QVector>

// QtD1 Includes
#include "LevelPillarFactory.h"
#include "TownLevelPillar.h"

namespace QtD1{

// Constructor
LevelPillarFactory::LevelPillarFactory( const QString& level_min_file_name,
                                        const QString& level_sol_file_name )
  : d_level_min_file_name( level_min_file_name ),
    d_level_sol_file_name( level_sol_file_name )
{
  // Check that the min file name is valid
  if( !level_min_file_name.contains( ".min" ) )
  {
    qFatal( "LevelPillarFactory Error: cannot parse file %s (only .min files "
            "can be parsed)!",
            level_min_file_name.toStdString().c_str() );
  }

  // Check that the sol file name is valid
  if( !level_sol_file_name.contains( ".sol" ) )
  {
    qFatal( "LevelPillarFactory Error: cannot parse file %s (only .sol files "
            "can be parsed)!",
            level_sol_file_name.toStdString().c_str() );
  }
}

// Create the level pillars
QList<std::shared_ptr<LevelPillar> >
LevelPillarFactory::createLevelPillars() const
{
  // Get the level pillar properties
  QVector<LevelPillar::Properties> pillar_properties =
    this->getLevelPillarProperties();

  // Open the min file
  QFile min_file( d_level_min_file_name );
  min_file.open( QIODevice::ReadOnly );

  // Extract the min file data
  QDataStream stream( &min_file );
  stream.setByteOrder( QDataStream::LittleEndian );

  // Create a new pillar list
  QList<std::shared_ptr<LevelPillar> > level_pillars;

  const int blocks_per_pillar = this->getLevelPillarNumBlocksFunction()();

  LevelPillarCreationFunction create_pillar =
    this->getLevelPillarCreationFunction();

  // Get the painter path
  QPainterPath path = createPillarPainterPath();

  int pillar_index = 0;

  while( true )
  {
    if( stream.atEnd() )
      break;

    // Read a section of blocks from the file
    QVector<LevelPillar::Block> blocks( blocks_per_pillar );

    for( int i = 0; i < blocks.size(); ++i )
    {
      quint16 raw_data;

      stream >> raw_data;

      // Indexing in the min file starts at 1 (shift left to 0)
      blocks[i].frame_index = (raw_data & 0x0FFF) - 1;

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
    level_pillars << create_pillar( blocks, pillar_properties[pillar_index], path );

    // Increment the pillar index
    ++pillar_index;
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
std::shared_ptr<LevelPillar> LevelPillarFactory::createTownPillar(
                                    const QVector<LevelPillar::Block>& blocks,
                                    const LevelPillar::Properties& properties,
                                    const QPainterPath& clickable_region )
{
  return std::shared_ptr<LevelPillar>( new TownLevelPillar( blocks, properties, clickable_region ) );
}

// Create a pillar heuristic map for clickable area
QPainterPath LevelPillarFactory::createPillarPainterPath() const
{
  QPolygonF clickable_pillar_region;
  clickable_pillar_region << QPointF( 0.0, 16.0 )
                          << QPointF( 16.0, 32.0 )
                          << QPointF( 32.0, 16.0 )
                          << QPointF( 16.0, 0.0 );

  QPainterPath path;
  path.addPolygon( clickable_pillar_region );
  
  return path;
}

// Create a cathedral pillar
std::shared_ptr<LevelPillar> LevelPillarFactory::createCathedralPillar(
                                            const QVector<LevelPillar::Block>&,
                                            const LevelPillar::Properties& )
{
  qFatal( "Cathedral pillar not implemented" );

  return std::shared_ptr<LevelPillar>();
}

// Create a catacomb pillar
std::shared_ptr<LevelPillar> LevelPillarFactory::createCatacombPillar(
                                            const QVector<LevelPillar::Block>&,
                                            const LevelPillar::Properties& )
{
  qFatal( "Catacomb pillar not implemented" );

  return std::shared_ptr<LevelPillar>();
}

// Create a cave pillar
std::shared_ptr<LevelPillar> LevelPillarFactory::createCavePillar(
                                            const QVector<LevelPillar::Block>&,
                                            const LevelPillar::Properties& )
{
  qFatal( "Cave pillar not implemented" );

  return std::shared_ptr<LevelPillar>();
}

// Create a hell pillar
std::shared_ptr<LevelPillar> LevelPillarFactory::createHellPillar(
                                            const QVector<LevelPillar::Block>&,
                                            const LevelPillar::Properties& )
{
  qFatal( "Hell pillar not implemented" );

  return std::shared_ptr<LevelPillar>();
}

// Get the pillar properties
QVector<LevelPillar::Properties> LevelPillarFactory::getLevelPillarProperties() const
{
  // Open the sol file
  QFile sol_file( d_level_sol_file_name );
  sol_file.open( QIODevice::ReadOnly );

  // Extract the sol file data
  QDataStream stream( &sol_file );
  stream.setByteOrder( QDataStream::LittleEndian );

  // Create the properties list
  QVector<LevelPillar::Properties> level_pillar_properties;

  while( true )
  {
    if( stream.atEnd() )
      break;

    quint8 raw_data;

    stream >> raw_data;

    LevelPillar::Properties
      properties{true,false,false,false,false,false,false,false};

    // First bit is passable property, 0 is passable
    if( (raw_data & 0x01) != 0 )
    {
      properties.passable = false;
    }

    if( (raw_data & 0x02) != 0 )
      properties.unknown_1 = true;

    if( (raw_data & 0x04) != 0 )
      properties.block_projectiles = true;

    if( (raw_data & 0x08) != 0 )
      properties.transparent_when_hiding_character = true;

    if( (raw_data & 0x10) != 0 )
      properties.unknown_4 = true;

    if( (raw_data & 0x20) != 0 )
      properties.unknown_5 = true;

    if( (raw_data & 0x40) != 0 )
      properties.unknown_6 = true;

    if( (raw_data & 0x80) != 0 )
      properties.unknown_7 = true;

    level_pillar_properties << properties;
  }

  return level_pillar_properties;
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
    return LevelPillarNumBlocksFunction();
  }
}

// Get the pillar creation function
LevelPillarFactory::LevelPillarCreationFunction LevelPillarFactory::getLevelPillarCreationFunction() const
{
  if( d_level_min_file_name.contains( "town.min" ) )
    return &LevelPillarFactory::createTownPillar;
  // if( d_level_min_file_name.contains( "l1.min" ) )
  //   return &LevelPillarFactory::createCathedralPillar;
  // if( d_level_min_file_name.contains( "l2.min" ) )
  //   return &LevelPillarFactory::createCatacombPillar;
  // if( d_level_min_file_name.contains( "l3.min" ) )
  //   return &LevelPillarFactory::createCavePillar;
  // if( d_level_min_file_name.contains( "l4.min" ) )
  //   return &LevelPillarFactory::createHellPillar;
  else
  {
    qFatal( "LevelPillarFactory Error: Invalid min file %s!",
            d_level_min_file_name.toStdString().c_str() );
    return LevelPillarCreationFunction();
  }
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end LevelPillarFactory.cpp
//---------------------------------------------------------------------------//
