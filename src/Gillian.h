//---------------------------------------------------------------------------//
//!
//! \file   Gillian.h
//! \author Sean Robinson
//! \brief  The Gillian class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GILLIAN_H
#define GILLIAN_H

// QtD1 Includes
#include "NPC.h"
#include "Sound.h"
#include "Quest.h"

namespace QtD1{

//! The Gillian class
class Gillian : public NPC
{
  Q_OBJECT

public:

  //! Constructor
  Gillian( QGraphicsObject* parent = 0 );

  //! Destructor
  ~Gillian()
  { /* ... */ }

  //! Get the warrior description
  QString getDescriptionText() const final override;

  //! Get the number of image assets used by the object
  int getNumberOfImageAssets() const final override;

  //! Get the image asset names used by the object
  void getImageAssetNames( QSet<QString>& image_asset_names ) const final override;

  //! Check if an image asset is used
  bool isImageAssetUsed( const QString& image_asset_name ) const final override;

  //! Check if the image assets have been loaded
  bool imageAssetsLoaded() const final override;

  //! Load the image asset
  void loadImageAsset( const QString& image_asset_name,
                       const QVector<QPixmap>& image_asset_frames ) final override;

  //! Finalize image asset loading
  void finalizeImageAssetLoading() final override;
  
  //! Dump the image assets
  void dumpImageAssets() final override;

public slots:
  
  //! Play quest dialogue
  void discussQuest( const Quest::Type quest )final override;

  //! Play gossip dialogue
  void gossip() final override;

protected:

  //! Greet the character
  void greet() final override;

  //! Get the movement speed (pixels per game tic)
  qreal getMovementSpeed() const final override;

  //! Check if the NPC has dialogue for the requested quest
  bool hasDialogue( const Quest::Type quest ) const final override;

  //! Load the interaction menu
  NPCInteractionMenu* createInteractionMenu( QWidget* parent, Character* character ) final override;

private:

  // The image asset name
  static QString s_image_asset_name;

  // The direction sprites
  QMap<QString,std::shared_ptr<BasicActor::DirectionGameSpriteMap> >
  d_direction_sprites;

  // Records if the sprites have been loaded
  bool d_sprites_loaded;

  // The greeting
  Sound d_greeting;

  // The quest dialogues
  std::map<Quest::Type,std::vector<DialogueData> > d_quest_dialogues;

  // The gossip dialogues
  std::vector<DialogueData> d_gossip_dialogues;

  // The unused dialogues
  std::vector<DialogueData> d_unused_dialogues;
};
  
} // end QtD1 namespace

#endif // end GILLIAN_H

//---------------------------------------------------------------------------//
// end Gillian.h
//---------------------------------------------------------------------------//
