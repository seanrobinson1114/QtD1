//---------------------------------------------------------------------------//
//!
//! \file   LevelSectorFactory.cpp
//! \author Alex Robinson
//! \brief  The level sector factory class definition
//!
//---------------------------------------------------------------------------//

// Qt Includes
#include <QDataStream>
#include <QFile>
#include <QBuffer>

// QtD1 Includes
#include "LevelSectorFactory.h"
#include "LevelSquareFactory.h"

namespace QtD1{

// Constructor
LevelSectorFactory::LevelSectorFactory( const QString& level_min_file_name,
                                        const QString& level_til_file_name,
                                        const QString& level_dun_file_name )
  : d_level_min_file_name( level_min_file_name ),
    d_level_til_file_name( level_til_file_name ),
    d_level_dun_file_name( level_dun_file_name )
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
  if( !level_dun_file_name.contains( ".dun" ) )
  {
    qFatal( "LevelPillarFactory Error: cannot parse file %s (only .dun files "
            "can be parsed)!",
            level_dun_file_name.toStdString().c_str() );
  }
}

// Create the level sector
LevelSector* LevelSectorFactory::createLevelSector() const
{
  // Create the level squares
  QList<LevelSquare*> level_squares;

  {
    LevelSquareFactory square_factory( d_level_min_file_name,
                                       d_level_til_file_name );

    level_squares = square_factory.createLevelSquares();
  }

  return this->createLevelSector( level_squares );
}

// Create the level sector (advanced)
LevelSector* LevelSectorFactory::createLevelSector(
                                     const QList<LevelSquare*>& squares ) const
{
  // Initialize the square rows and columns
  QVector<QVector<LevelSquare*> > ordered_squares( squares.size() );

  for( int j = 0; j < squares.size(); ++j )
    ordered_squares[j].resize( squares[j]->boundingRect().width() );

  // Open the dun file
  QFile dun_file( d_level_dun_file_name );
  dun_file.open( QIODevice::ReadOnly );

  // Extract the dun file data
  QDataStream stream( &dun_file );
  stream.setByteOrder( QDataStream::LittleEndian );

  // Get the number of rows and columns
  quint16 num_rows, num_cols;

  stream >> num_rows;
  stream >> num_cols;

  for( int j = 0; j < num_rows; ++j )
  {
    for( int i = 0; i < num_cols; ++i )
    {
      // Make sure that the stream is still valid
      if( stream.atEnd() )
      {
        qFatal( "LevelSectorFactory Error: Unexpected end of dun file %s "
                "(row=%i,col=%i)!",
                d_level_dun_file_name.toStdString().c_str(), j, i );
      }

      // Get the square index
      quint16 square_index;

      stream >> square_index;

      ordered_squares[j][i] = squares[square_index];
    }
  }

  // Todo: parse the additional info in the dun file...

  return new LevelSector( ordered_squares );
}

} // end QtD1

//---------------------------------------------------------------------------//
// end LevelSectorFactory.cpp
//---------------------------------------------------------------------------//
