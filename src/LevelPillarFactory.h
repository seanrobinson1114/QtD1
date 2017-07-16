//---------------------------------------------------------------------------//
//!
//! \file   LevelPillarFactory.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The level pillar factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef LEVEL_PILLAR_FACTORY_H
#define LEVEL_PILLAR_FACTORY_H

// Std Lib Includes
#include <functional>
#include <memory>

// Qt Includes
#include <QString>
#include <QList>

// QtD1 Includes
#include "LevelPillar.h"

namespace QtD1{

//! The level pillar factory class
class LevelPillarFactory
{

public:

  //! Constructor
  LevelPillarFactory( const QString& level_min_file_name,
                      const QString& level_sol_file_name );

  //! Destructor
  ~LevelPillarFactory()
  { /* ... */ }

  //! Create the level pillars
  QList<std::shared_ptr<LevelPillar> > createLevelPillars() const;

private:

  // The level pillar number of blocks function typedef
  typedef std::function<int()> LevelPillarNumBlocksFunction;

  // The level pillar creation function typedef
  typedef std::function<std::shared_ptr<LevelPillar>(const QVector<LevelPillar::Block>&)>
  LevelPillarCreationFunction;

  // Get the number of blocks in a town pillar
  static int getNumberOfBlocksInTownPillar();

  // Get the number of blocks in a cathedral pillar
  static int getNumberOfBlocksInCathedralPillar();

  // Get the number of blocks in a catacomb pillar
  static int getNumberOfBlocksInCatacombPillar();

  // Get the number of blocks in a cave pillar
  static int getNumberOfBlocksInCavePillar();

  // Get the number of blocks in a hell pillar
  static int getNumberOfBlocksInHellPillar();

  // Create a town pillar
  static std::shared_ptr<LevelPillar> createTownPillar( const QVector<LevelPillar::Block>& blocks );

  // Create a cathedral pillar
  static std::shared_ptr<LevelPillar> createCathedralPillar( const QVector<LevelPillar::Block>&  blocks );

  // Create a catacomb pillar
  static std::shared_ptr<LevelPillar> createCatacombPillar( const QVector<LevelPillar::Block>& blocks );

  // Create a cave pillar
  static std::shared_ptr<LevelPillar> createCavePillar( const QVector<LevelPillar::Block>& blocks );

  // Create a hell pillar
  static std::shared_ptr<LevelPillar> createHellPillar( const QVector<LevelPillar::Block>& blocks );

  // Get the number of pillar blocks function
  LevelPillarNumBlocksFunction getLevelPillarNumBlocksFunction() const;

  // Get the pillar creation function
  LevelPillarCreationFunction getLevelPillarCreationFunction() const;

  // The level min file name
  QString d_level_min_file_name;

  // The level sol file name
  QString d_level_sol_file_name;
};

} // end QtD1 namespace

#endif // end LEVEL_PILLAR_FACTORY_H

//---------------------------------------------------------------------------//
// end LevelPillarFactory.h
//---------------------------------------------------------------------------//
