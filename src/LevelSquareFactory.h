//---------------------------------------------------------------------------//
//!
//! \file   LevelSquareFactory.h
//! \author Alex Robinson
//! \brief  The level square factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef LEVEL_SQUARE_FACTORY_H
#define LEVEL_SQUARE_FACTORY_H

// Std Lib Includes
#include <memory>

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
                      const QString& level_sol_file_name,
                      const QString& level_til_file_name );

  //! Destructor
  ~LevelSquareFactory()
  { /* ... */ }

  //! Create the level squares
  QList<std::shared_ptr<LevelSquare> > createLevelSquares() const;

  //! Create the level squares (advanced)
  static QList<std::shared_ptr<LevelSquare> > createLevelSquares(
                   const QString& level_til_file_name,
                   const QList<std::shared_ptr<LevelPillar> >& level_pillars );

private:

  // The level min file name
  QString d_level_min_file_name;

  // The level sol file name
  QString d_level_sol_file_name;

  // The level til file name
  QString d_level_til_file_name;
};

} // end QtD1 namespace

#endif // end LEVEL_SQUARE_FACTORY_H

//---------------------------------------------------------------------------//
// end LevelSquareFactory.h
//---------------------------------------------------------------------------//
