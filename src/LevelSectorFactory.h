//---------------------------------------------------------------------------//
//!
//! \file   LevelSquareFactory.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The level sector factory class declaration
//!
//---------------------------------------------------------------------------//

// Qt Includes
#include <QString>
#include <QList>

// QtD1 Includes
#include "LevelSector.h"

namespace QtD1{

//! The level sector factory class
class LevelSectorFactory
{

public:

  //! Constructor
  LevelSectorFactory( const QString& level_min_file_name,
                      const QString& level_sol_file_name,
                      const QString& level_til_file_name,
                      const QString& level_dun_file_name );

  //! Destructor
  ~LevelSectorFactory()
  { /* ... */ }

  //! Create the level sector
  LevelSector* createLevelSector() const;

  //! Create the level sector (advanced)
  static LevelSector* createLevelSector(
                         const QString& level_dun_file_name,
                         const QList<std::shared_ptr<LevelSquare> >& squares );

private:

  // The level min file name
  QString d_level_min_file_name;

  // The level sol file name
  QString d_level_sol_file_name;

  // The level til file name
  QString d_level_til_file_name;

  // The level dun file name
  QString d_level_dun_file_name;
};
  
} // end QtD1

//---------------------------------------------------------------------------//
// end LevelSectorFactory.cpp
//---------------------------------------------------------------------------//
