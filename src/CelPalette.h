//---------------------------------------------------------------------------//
//!
//! \file   CelPalette.h
//! \author Alex Robinson
//! \brief  The cel palette class declaration
//!
//---------------------------------------------------------------------------//

#ifndef CEL_PALETTE_H
#define CEL_PALETTE_H

// Qt Includes
#include <QString>
#include <QVector>
#include <QColor>

namespace QtD1{

//! The palette class
class CelPalette
{

public:

  //! Constructor (file name)
  CelPalette( const QString& file_name );

  //! Constructor (file name and extracted data)
  CelPalette( const QString& file_name,
              const QByteArray& palette_data );

  //! Destructor
  ~CelPalette()
  { /* ... */ }

  //! Get the palette name
  const QString& getName() const;

  //! Get the transparent color key
  int getTransparentColorKey() const;

  //! Get the color corresponding to the key
  const QColor& getColor( const int key ) const;

  //! Get the color corresponding to the key
  const QColor& operator[]( const int key ) const;

  //! Get the rgba corresponding to the key
  const QRgb& getRgba( const int key ) const;

  //! Get a QImage compatible color table
  const QVector<QRgb>& toColorTable() const;

private:

  // Validate the palette file name
  static void validatePaletteFileName( const QString& file_name );

  // Extract the palette from the device
  void extractPalette( QIODevice& device );

  // The palette file name
  QString d_file_name;

  // The palette colors
  QVector<QColor> d_palette_colors;

  // The palette rgbs
  QVector<QRgb> d_palette_rgbs;

  // The transparent color key
  int d_transparent_color_key;
};
  
} // end QtD1 namespace

#endif // end CEL_PALETTE_H

//---------------------------------------------------------------------------//
// end CelPalette.h
//---------------------------------------------------------------------------//
