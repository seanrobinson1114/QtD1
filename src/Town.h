//---------------------------------------------------------------------------//
//!
//! \file   Town.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The town class declaration
//!
//---------------------------------------------------------------------------//

#ifndef TOWN_H
#define TOWN_H

// QtD1 Includes
#include "Level.h"
#include "NPC.h"

namespace QtD1{

//! The town class declaration
class Town : public Level
{
  Q_OBJECT

public:

  //! Constructor
  Town( QObject* parent = 0 );

  //! Destructor
  ~Town()
  { /* ... */ }

  //! Get the type
  Type getType() const override;

  //! Get the number
  int getNumber() const override;

  //! Get the image asset name
  QString getImageAssetName() const override;

  //! Create the level NPCs and actors
  void createNPCsAndActors( QVector<NPC*>& npcs,
                            QVector<Actor*>& special_actors ) final override;

  //! Activate the NPCs and actors
  void activateNPCsAndActors( QWidget* parent ) final override;

  //! Insert the character
  void insertCharacter( Character* character,
                        const QPointF& location,
                        const Direction direction ) override;

  //! Remove the character
  void removeCharacter() override;

private:

  // Create the level sectors
  void createSectors( QList<LevelSector*>& sectors ) override;

  // Farnham
  NPC* d_farnham;

  // Adria
  NPC* d_adria;

  // Odgen
  NPC* d_ogden;

  // Gillian
  NPC* d_gillian;
};
  
} // end QtD1 namespace

#endif // end TOWN_H

//---------------------------------------------------------------------------//
// end Town.h
//---------------------------------------------------------------------------//
