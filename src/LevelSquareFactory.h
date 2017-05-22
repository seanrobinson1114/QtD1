//---------------------------------------------------------------------------//
//!
//! \file   LevelSquareFactory.h
//! \author Alex Robinson
//! \brief  The level square factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef LEVEL_SQUARE_FACTORY_H
#define LEVEL_SQUARE_FACTORY_H

// Qt Includes
#include <QString>
#include <QList>

// QtD1 Includes
#include "LevelSquare.h"

namespace QtD1{

//! The level square factory class
class LevelSquareFactory
{

public:

  //! Constructor
  LevelSquareFactory( const QString& level_min_file_name,
                      const QString& level_til_file_name );

  //! Destructor
  ~LevelSquareFactory()
  { /* ... */ }

  //! Create the level squares
  QList<LevelSquare*> createLevelSquares() const;

  //! Create the level squares (advanced)
  QList<LevelSquare*> createLevelSquares(
                                   const QList<LevelPillars*>& pillars ) const;

private:

  // The level min file name
  QString d_level_min_file_name;

  // The level til file name
  QString d_level_til_file_name;
};
  
} // end QtD1 namespace

#endif // end LEVEL_SQUARE_FACTORY_H

//---------------------------------------------------------------------------//
// end LevelSquareFactory.h
//---------------------------------------------------------------------------//
