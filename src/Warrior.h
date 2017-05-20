//---------------------------------------------------------------------------//
//!
//! \file   Warrior.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The warrior class declaration
//!
//---------------------------------------------------------------------------//

#ifndef WARRIOR_H
#define WARRIOR_H

// Std Lib Includes
#include <utility>
#include <tuple>

// QtD1 Includes
#include "Character.h"

namespace QtD1{

//! The warrior class
class Warrior : public Character
{
  Q_OBJECT
  Q_IMPORT_ALIAS( "QtD1", 1, 0, "Warrior" )

public:

  //! Constructor
  Warrior( QGraphicsObject* parent = 0 );

  //! Constructor
  Warrior( const QString& name, QGraphicsObject* parent = 0 );

  //! Destructor
  ~Warrior()
  { /* ... */ }

  //! Get the number of image assets used by the object
  int getNumberOfImageAssets() const override;

  //! Get the image asset names used by the object
  void getImageAssetNames( QSet<QString>& image_asset_names ) const override;

  //! Check if an image asset is used
  bool isImageAssetUsed( const QString& image_asset_name ) const override;

  //! Clone the Warrior
  Warrior* clone( QGraphicsObject* parent = 0 ) const override;

private:

  // The map type of assets and the corresponding character states
  typedef QMap<QString,Character::States> AssetStateMap;

  // Initialize asset state map
  static void initializeAssetStateMap();

  // Get the asset state map
  static const AssetStateMap& getAssetStateMap();

  // Initialize warrior stats
  void initializeStats();

  // Get the states associated with the image asset
  const Character::States& getImageAssetStates(
                              const QString& image_asset_name ) const override;

  //! Get the number of sprite sheet frames per direction
  int getSpriteSheetFramesPerDirection( const States& states ) const override;

  // The warrior image asset names
  static AssetStateMap s_asset_state_map;
};

} // end QtD1 namespace

Q_DECLARE_METATYPE( QtD1::Warrior )
Q_DECLARE_METATYPE( QtD1::Warrior* )

#endif // end WARRIOR_H

//---------------------------------------------------------------------------//
// end Warrior.h
//---------------------------------------------------------------------------//
