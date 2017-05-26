//---------------------------------------------------------------------------//
//!
//! \file   CelFrameDecoder.h
//! \author Alex Robinson
//! \brief  The cel frame decoder declaration
//!
//---------------------------------------------------------------------------//

#ifndef CEL_FRAME_DECODER_H
#define CEL_FRAME_DECODER_H

// Std Lib Includes
#include <memory>
#include <functional>

// Qt Includes
#include <QString>
#include <QImage>
#include <QByteArray>

// QtD1 Includes
#include "CelPalette.h"
#include "CelImagePixelSetter.h"

namespace QtD1{

//! The cel frame decoder base class
class CelFrameDecoder
{

public:

  //! The frame decoder functor type
  typedef std::function<QImage(const CelPalette&)> DecodeFunctor;
  
  //! Get the frame decoder
  static DecodeFunctor getDecoder( const QString& file_name,
                                   const int frame_index,
                                   const QByteArray& frame_data );
  
protected:

  //! Decode a standard cl2 frame
  static QImage decodeStandardCl2Frame( const QString& file_name,
                                        const int frame_index,
                                        const QByteArray& frame_data,
                                        const CelPalette& palette,
                                        const int frame_width,
                                        const int frame_height );

  //! Decode a standard cel frame
  static QImage decodeStandardCelFrame( const QString& file_name,
                                        const int frame_index,
                                        const QByteArray& frame_data,
                                        const CelPalette& palette,
                                        const int frame_width,
                                        const int frame_height );

  //! Decode a tile cel frame with no transparency
  static QImage decodeNoTransTileFrame( const QString& file_name,
                                        const int frame_index,
                                        const QByteArray& frame_data,
                                        const CelPalette& palette );

  //! Decode a tile cel frame with implicit upper and lower-left transparency
  static QImage decodeImplicitUpperLowerLeftTransTileFrame(
                                                const QString& file_name,
                                                const int frame_index,
                                                const QByteArray& frame_data,
                                                const CelPalette& palette );

  //! Decode a tile cel frame with implicit upper and lower-right transparency
  static QImage decodeImplicitUpperLowerRightTransTileFrame(
                                                const QString& file_name,
                                                const int frame_index,
                                                const QByteArray& frame_data,
                                                const CelPalette& palette );

  //! Decode a tile cel frame with implicit upper-left transparency
  static QImage decodeImplicitUpperLeftTransTileFrame(
                                                const QString& file_name,
                                                const int frame_index,
                                                const QByteArray& frame_data,
                                                const CelPalette& palette );

  //! Decode a tile cel frame with implicit upper-right transparency
  static QImage decodeImplicitUpperRightTransTileFrame(
                                                const QString& file_name,
                                                const int frame_index,
                                                const QByteArray& frame_data,
                                                const CelPalette& palette );
  
private:

  // Get a standard cl2 frame decoder
  static DecodeFunctor getStandardCl2FrameDecoder(
                                      const QString& file_name,
                                      const int frame_index,
                                      const QByteArray& frame_data );
  
  // Get a standard cel frame decoder
  static DecodeFunctor getStandardCelFrameDecoder(
                                      const QString& file_name,
                                      const int frame_index,
                                      const QByteArray& frame_data );

  // Get the level cel file frame decoder
  static DecodeFunctor getLevelCelFrameDecoder(
                                      const QString& file_name,
                                      const int frame_index,
                                      const QByteArray& frame_data );

  // Check if the file is a cel file
  static bool isCelFile( const QString& file_name );

  // Check if the file is a cl2 file
  static bool isCl2File( const QString& file_name );

  // Check if the cel file is a level cel file
  static bool isLevelCelFile( const QString& file_name );

  // Check if the cel frame is a tile frame with no transparency
  static bool isNoTransTileFrame( const QString& file_name,
                                  const int frame_index );

  // Check if the cel frame is a tile frame with implicit upper-left trans
  static bool hasImplicitUpperLeftTransData(
                                      const QByteArray& frame_data );

  // Check if the cel frame is a tile frame with implicit upper-right trans
  static bool hasImplicitUpperRightTransData( const QByteArray& frame_data );

  // Decode a tile cel frame with implicit upper and lower transparency
  static QImage decodeImplicitUpperLowerTransTileFrame(
                                            const QString& file_name,
                                            const int frame_index,
                                            const QByteArray& frame_data,
                                            const CelPalette& palette, 
                                            const bool is_impl_trans_on_left );

  // Decode a tile cel frame with implicit upper transparency
  static QImage decodeImplicitUpperTransTileFrame(
                                            const QString& file_name,
                                            const int frame_index,
                                            const QByteArray& frame_data,
                                            const CelPalette& palette,
                                            const bool is_impl_trans_on_left );

  // The tile frame row decode functor type
  typedef std::function<void(CelImagePixelSetter&,
                             const CelPalette&,
                             const char**,
                             const uint8_t,
                             const bool)> TileFrameRowDecodeFunctor;

  // Get the row decoder
  static TileFrameRowDecodeFunctor getTileFrameRowDecoder(
                                            const bool is_impl_trans_on_left );

  // Decode a row of a tile frame with implicit left transparent pixel data
  static void decodeImplicitLeftTransTileFrameRow(
                                    CelImagePixelSetter& frame,
                                    const CelPalette& palette,
                                    const char** frame_data_it,
                                    const uint8_t explicit_row_size,
                                    const bool explicit_trans_values_present );

  // Decode a row of a tile frame with implicit right transparent pixel data
  static void decodeImplicitRightTransTileFrameRow(
                                    CelImagePixelSetter& frame,
                                    const CelPalette& palette,
                                    const char** frame_data_it,
                                    const uint8_t explicit_row_size,
                                    const bool explicit_trans_values_present );
  
  // The upper/lower implicit trans tile frame row sizes
  static const QVector<uint8_t> s_upper_lower_impl_trans_frame_row_sizes;

  // The upper implicit trans tile frame decoded row sizes
  static const QVector<uint8_t> s_upper_impl_trans_frame_row_sizes;

  //! Constructor
  CelFrameDecoder();
};
  
} // end QtD1 namespace

#endif // end CEL_FRAME_DECODER_H

//---------------------------------------------------------------------------//
// end CelFrameDecoder.h
//---------------------------------------------------------------------------//
