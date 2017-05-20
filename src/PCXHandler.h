//---------------------------------------------------------------------------//
//!
//! \file   PCXHandler.h
//! \author Alex Robinson
//! \brief  PCX handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef PCX_HANDLER_H
#define PCX_HANDLER_H

// Qt Includes
#include <QImageIOPlugin>

namespace QtD1{

//! The PCX handler
class PCXHandler : public QImageIOHandler
{

public:

  //! Constructor
  PCXHandler();

  //! Check if the handler can read from the assigned device
  bool canRead() const override;

  //! Read from the device and load the image
  bool read( QImage* image ) override;

  //! Write the image
  bool write( const QImage& image ) override;

  //! Check if the handler can read from the device
  static bool canRead(QIODevice *device);
};

//! The PCX plugin class
class PCXPlugin : public QImageIOPlugin
{

  Q_OBJECT
  
public:

  //! Return the capabilities of the plugin
  Capabilities capabilities(QIODevice *device, const QByteArray &format) const override;

  //! Return the list of image keys this plugin supports
  QStringList keys() const override;

  //! Create a handler for the pcx image data
  QImageIOHandler *create(QIODevice *device, const QByteArray &format = QByteArray()) const override;
};
  
} // end QtD1 namespace

#endif // end PCX_HANDLER_H

//---------------------------------------------------------------------------//
// end PCXHandler.h
//---------------------------------------------------------------------------//
