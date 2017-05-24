//---------------------------------------------------------------------------//
//!
//! \file   LevelSquareFactory.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The level square factory class definition
//!
//---------------------------------------------------------------------------//

// Qt Includes
#include <QDataStream>
#include <QFile>
#include <QBuffer>

// QtD1 Includes
#include "LevelSquareFactory.h"
#include "LevelPillarFactory.h"

#include <iostream>

namespace QtD1{

// Constructor
LevelSquareFactory::LevelSquareFactory( const QString& level_min_file_name,
                                        const QString& level_til_file_name )
  : d_level_min_file_name( level_min_file_name ),
    d_level_til_file_name( level_til_file_name )
{
  if( !level_min_file_name.contains( ".min" ) )
  {
    qFatal( "LevelPillarFactory Error: cannot parse file %s (only .min files "
            "can be parsed)!",
            level_min_file_name.toStdString().c_str() );
  }
  if( !level_til_file_name.contains( ".til" ) )
  {
    qFatal( "LevelPillarFactory Error: cannot parse file %s (only .til files "
            "can be parsed)!",
            level_til_file_name.toStdString().c_str() );
  }
}

// Create the level squares
QList<LevelSquare*> LevelSquareFactory::createLevelSquares() const
{
  // Create the level pillars
  QList<LevelPillar*> level_pillars;

  {
    LevelPillarFactory pillar_factory( d_level_min_file_name );

    level_pillars = pillar_factory.createLevelPillars();
  }

  return this->createLevelSquares( level_pillars );
}

// Create the level squares (advanced)
QList<LevelSquare*> LevelSquareFactory::createLevelSquares(
                                    const QList<LevelPillar*>& level_pillars ) const
{
  // Create a new square list
  QList<LevelSquare*> level_squares;

  // Open the til file
  QFile til_file( d_level_til_file_name );
  til_file.open( QIODevice::ReadOnly );

  // Extract the til file data
  QDataStream stream( &til_file );
  stream.setByteOrder( QDataStream::LittleEndian );

  while( true )
  {
    if( stream.atEnd() )
      break;

    // Read the pillar indices
    quint16 top_index, right_index, left_index, bottom_index;

    stream >> top_index;
    stream >> right_index;
    stream >> left_index;
    stream >> bottom_index;

    // Create a new square
    LevelSquare* level_square = new LevelSquare( level_pillars[top_index],
                                                 level_pillars[right_index],
                                                 level_pillars[left_index],
                                                 level_pillars[bottom_index] );
    level_squares << level_square;
  }

  return level_squares;
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end LevelSquareFactory.cpp
//---------------------------------------------------------------------------//
