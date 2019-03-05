//---------------------------------------------------------------------------//
//!
//! \file   UIArtLoader.h
//! \author Alex Robinson
//! \brief  The ui art loader class declaration
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "PCXFrameLoader.h"

namespace QtD1{

//! Helper class for loading ui art
class UIArtLoader : public QObject
{
  Q_OBJECT
  
public:

  //! Constructor
  UIArtLoader();

  //! Destructor
  ~UIArtLoader()
  { /* ... */ }

  //! Set the source
  void setSource( const QString& source );

  //! Set the color that will be made transparent
  void setTransparentColor( const QColor& transparent_color );

  //! Set the number of rows
  void setNumberOfRows( const int num_rows );

  //! Load the ui art
  void loadFrames();

  //! Get the loaded frames
  QList<QImage>& getLoadedFrames();

private slots:

  //! Handle frame loaded
  void handleFrameLoaded( const int, QImage frame );

private:

  //! The PCX frame loader
  PCXFrameLoader d_frame_loader;

  //! The loaded frames
  QList<QImage> d_loaded_frames;
};

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end UIArtLoader.h
//---------------------------------------------------------------------------//
