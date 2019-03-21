//---------------------------------------------------------------------------//
//!
//! \file   LevelObject.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The level object base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef LEVEL_OBJECT_H
#define LEVEL_OBJECT_H

// Std Lib Includes
#include <memory>

// Qt Includes
#include <QGraphicsObject>
#include <QSet>
#include <QMap>
#include <QVector>

// QtD1 Includes
#include "QMLRegistrationHelper.h"

namespace QtD1{

class Level;

//! The level object base class
class LevelObject: public QGraphicsObject
{
  Q_OBJECT
  Q_IMPORT_ALIAS( "QtD1", 1, 0, "LevelObject" )

public:

  //! Constructor
  LevelObject( QGraphicsObject* parent = 0 );

  //! Destructor
  virtual ~LevelObject()
  { /* ... */ }

  //! Check if object is interactive
  virtual bool isInteractive() const;

  //! Check if the object is grabbable
  virtual bool isGrabbable() const;

  //! Check if the object can be attacked
  virtual bool canBeAttacked() const = 0;

  //! Check if it is a pillar
  virtual bool isPillar() const;

  //! Check if it is a character
  virtual bool isCharacter() const;

protected slots:

  //! Handle being targeted by another object
  virtual void handleBeingTargeted( LevelObject* targeter );

protected:

  //! Notify object that it has been targeted
  void notifyTarget( LevelObject* target );

  //! Get the number of image assets used by the object
  virtual int getNumberOfImageAssets() const = 0;

  //! Get the image asset names used by the object
  virtual void getImageAssetNames( QSet<QString>& image_asset_names ) const = 0;

  //! Check if the image asset is used by the object
  virtual bool isImageAssetUsed( const QString& image_asset_name ) const = 0;

  //! Check if the image assets have been loaded
  virtual bool imageAssetsLoaded() const = 0;

  //! Get ready for image asset loading
  virtual void getReadyForImageAssetLoading()
  { /* ... */ }

  //! Load the raw image asset
  virtual void loadRawImageAsset( const QString& image_asset_name,
                                  const QVector<QImage>& image_asset_frames );

  //! Load the image asset
  virtual void loadImageAsset( const QString& image_asset_name,
                               const QVector<QPixmap>& image_asset_frames ) = 0;

  //! Load the raw image assets
  virtual void loadRawImageAssets(
                          const QMap<QString,QVector<QImage> >& image_assets );

  //! Load the image assets
  virtual void loadImageAssets(
                         const QMap<QString,QVector<QPixmap> >& image_assets );

  //! Finalize image asset loading
  virtual void finalizeImageAssetLoading()
  { /* ... */ }

  //! Dump the image assets
  virtual void dumpImageAssets() = 0;

private:

  // Declare the Level class a friend
  friend class Level;
};

} // end QtD1 namespace

Q_DECLARE_METATYPE( QtD1::LevelObject* )

#endif // end LEVEL_OBJECT_H

//---------------------------------------------------------------------------//
// end LevelObject.h
//---------------------------------------------------------------------------//
