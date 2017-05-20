//---------------------------------------------------------------------------//
//!
//! \file   CelHandler.h
//! \author Alex Robinson, Sean Robinson
//! \brief  Cel handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef CEL_HANDLER_H
#define CEL_HANDLER_H

// Qt Includes
#include <QImageIOPlugin>
#include <QVector>

namespace QtD1{

//! The Cel handler
class CelHandler : public QImageIOHandler
{

public:

  //! Constructor
  CelHandler();

  //! Check if the handler can read from the assigned device
  bool canRead() const override;

  //! Read from the device and load the image
  bool read( QImage* image ) override;

  //! Write the image
  bool write( const QImage& image ) override;

  //! Get the number of images in the device
  int imageCount() const override;

  //! Get the number of times that the animation should loop
  int loopCount() const override;

  //! Get the number of milliseconds to wait before reading next image
  int nextImageDelay() const override;

  //! Jump to the desired image
  bool jumpToImage( int image_number ) override;

  //! Jump to the next image
  bool jumpToNextImage() override;

  //! Load the image frames from the device
  void loadImageFrames();

  //! Check if the handler can read from the device
  static bool canRead( QIODevice* device );

private:

  // The image frames
  QVector<QImage> d_image_frames;

  // The current frame
  int d_frame_index;
};

//! The Cel plugin class
class CelPlugin : public QImageIOPlugin
{

  Q_OBJECT

public:

  //! Return the capabilities of the plugin
  Capabilities capabilities( QIODevice* device, const QByteArray& format ) const override;

  //! Return the list of image keys this plugin supports
  QStringList keys() const override;

  //! Create a handler for the cel image data
  QImageIOHandler* create( QIODevice* device, const QByteArray& format = QByteArray() ) const override;
};
  
} // end QtD1 namespace

#endif // end CEL_HANDLER_H

//---------------------------------------------------------------------------//
// end CelHandler.h
//---------------------------------------------------------------------------//
