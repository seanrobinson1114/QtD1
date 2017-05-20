//---------------------------------------------------------------------------//
//!
//! \file   CelFrameDecoder.cpp
//! \author Alex Robinson
//! \brief  The cel frame decoder definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "CelFrameDecoder.h"
#include "CelImageProperties.h"
#include "Cl2ImageProperties.h"
#include "CelImagePixelSetter.h"

namespace QtD1{

// Initialize static member data
const QVector<uint8_t>
CelFrameDecoder::s_upper_lower_impl_trans_frame_row_sizes =
    {0, 4, 4, 8, 8, 12, 12, 16, 16, 20, 20, 24, 24, 28, 28, 32, 32, 32, 28, 28,
     24, 24, 20, 20, 16, 16, 12, 12, 8, 8, 4, 4};

const QVector<uint8_t>
CelFrameDecoder::s_upper_impl_trans_frame_row_sizes =
  {4, 4, 8, 8, 12, 12, 16, 16, 20, 20, 24, 24, 28, 28, 32, 32, 32, 32, 32, 32,
   32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32};

// Get the frame decoder
/*! \details The path must be stripped from the file name. The header must
 * be removed from the frame data before passing it to this method.
 */
auto CelFrameDecoder::getDecoder( const QString& file_name,
                                  const int frame_index,
                                  const QByteArray& frame_data )
  -> DecodeFunctor
{
  // Get the appropriate cel frame decoder
  if( CelFrameDecoder::isCelFile( file_name ) )
  {
    // Get the appropriate level frame decoder
    if( CelFrameDecoder::isLevelCelFile( file_name ) )
    {
      return CelFrameDecoder::getLevelCelFrameDecoder( file_name,
                                                       frame_index,
                                                       frame_data );
    }
    // Create a standard cel frame decoder
    else
    {
      return CelFrameDecoder::getStandardCelFrameDecoder( file_name,
                                                          frame_index,
                                                          frame_data );
    }
  }
  // Get the appropriate cl2 frame decoder
  else if( CelFrameDecoder::isCl2File( file_name ) )
  {
    return CelFrameDecoder::getStandardCl2FrameDecoder( file_name,
                                                        frame_index,
                                                        frame_data );
  }
  // Unknown file type
  else
  {
    qFatal( "CelFrameDecoder Error: Cannot determine frame decoder type for "
            "file %s!", file_name.toStdString().c_str() );

    return DecodeFunctor();
  }
}

// Get a standard cl2 frame decoder
auto CelFrameDecoder::getStandardCl2FrameDecoder(
                                       const QString& file_name,
                                       const int frame_index,
                                       const QByteArray& frame_data )
  -> DecodeFunctor
{
  int frame_width =
    Cl2ImageProperties::getInstance()->getFrameWidth( file_name, frame_index );
  int frame_height =
    Cl2ImageProperties::getInstance()->getFrameHeight( file_name, frame_index );

  return std::bind<QImage>( CelFrameDecoder::decodeStandardCl2Frame,
                            std::cref( file_name ),
                            frame_index,
                            std::cref( frame_data ),
                            std::placeholders::_1,
                            frame_width,
                            frame_height );
}

// Get a standard frame decoder
auto CelFrameDecoder::getStandardCelFrameDecoder(
                                       const QString& file_name,
                                       const int frame_index,
                                       const QByteArray& frame_data )
  -> DecodeFunctor
{
  int frame_width =
    CelImageProperties::getInstance()->getFrameWidth( file_name, frame_index );
  int frame_height =
    CelImageProperties::getInstance()->getFrameHeight( file_name, frame_index );

  return std::bind<QImage>( CelFrameDecoder::decodeStandardCelFrame,
                            std::cref( file_name ),
                            frame_index,
                            std::cref( frame_data ),
                            std::placeholders::_1,
                            frame_width,
                            frame_height );
}

// Get the level cel file frame decoder
auto CelFrameDecoder::getLevelCelFrameDecoder(
                                       const QString& file_name,
                                       const int frame_index,
                                       const QByteArray& frame_data )
  -> DecodeFunctor
{
  switch( frame_data.size() )
  {
    // Tile frame with no implicit transparent pixel data
    case 0x400:
    {
      if( CelFrameDecoder::isNoTransTileFrame( file_name, frame_index ) )
      {
        return std::bind<QImage>( CelFrameDecoder::decodeNoTransTileFrame,
                                  std::cref( file_name ),
                                  frame_index,
                                  std::cref( frame_data ),
                                  std::placeholders::_1 );
      }
      break;
    }
    // Tile frame with upper and lower left or upper and lower right implicit
    // transparent pixel data
    case 0x220:
    {
      if( CelFrameDecoder::hasImplicitUpperLeftTransData( frame_data ) )
      {
        return std::bind<QImage>(
                   CelFrameDecoder::decodeImplicitUpperLowerLeftTransTileFrame,
                   std::cref( file_name ),
                   frame_index,
                   std::cref( frame_data ),
                   std::placeholders::_1 );
      }
      else if( CelFrameDecoder::hasImplicitUpperRightTransData( frame_data ) )
      {
        return std::bind<QImage>(
                  CelFrameDecoder::decodeImplicitUpperLowerRightTransTileFrame,
                  std::cref( file_name ),
                  frame_index,
                  std::cref( frame_data ),
                  std::placeholders::_1 );
      }
      break;
    }
    // Tile frame with upper left or upper right implicit transparent pixel
    // data
    case 0x320:
    {
      if( CelFrameDecoder::hasImplicitUpperLeftTransData( frame_data ) )
      {
        return std::bind<QImage>(
                        CelFrameDecoder::decodeImplicitUpperLeftTransTileFrame,
                        std::cref( file_name ),
                        frame_index,
                        std::cref( frame_data ),
                        std::placeholders::_1 );
      }
      else if( CelFrameDecoder::hasImplicitUpperRightTransData( frame_data ) )
      {
        return std::bind<QImage>(
                       CelFrameDecoder::decodeImplicitUpperRightTransTileFrame,
                       std::cref( file_name ),
                       frame_index,
                       std::cref( frame_data ),
                       std::placeholders::_1 );
      }
      break;
    }
  }

  // If we still haven't found an approriate decoder use a standard decoder
  return CelFrameDecoder::getStandardCelFrameDecoder( file_name,
                                                      frame_index,
                                                      frame_data );
}

// Check if the file is a cel file
bool CelFrameDecoder::isCelFile( const QString& file_name )
{
  return file_name.contains( ".cel", Qt::CaseSensitive );
}

// Check if the file is a cl2 file
bool CelFrameDecoder::isCl2File( const QString& file_name )
{
  return file_name.contains( ".cl2", Qt::CaseSensitive );
}

// Check if the cel file is a level cel file
bool CelFrameDecoder::isLevelCelFile( const QString& file_name )
{
  return file_name == "l1.cel" || file_name == "l2.cel" ||
    file_name == "l3.cel" || file_name == "l4.cel" ||
    file_name == "town.cel";
}

// Decode a standard cl2 frame
QImage CelFrameDecoder::decodeStandardCl2Frame( const QString& file_name,
                                                const int frame_index,
                                                const QByteArray& frame_data,
                                                const CelPalette& palette, 
                                                const int frame_width,
                                                const int frame_height )
{
  // Initialize the frame
  CelImagePixelSetter frame( frame_width, frame_height, palette );

  const char* frame_data_it = frame_data.data();
  const char* frame_data_end = frame_data_it + frame_data.size();

  while( frame_data_it != frame_data_end )
  {
    // Get the command
    int8_t command = static_cast<int8_t>(*frame_data_it);

    // Increment the frame data iterator
    ++frame_data_it;

    // Transparency command
    if( command >= 0 )
    {
      for( int8_t j = 0; j < command; ++j )
      {
        *frame.pixel() = palette.getTransparentColorKey();
        frame.gotoNextPixel();
      }
    }
    // Color command
    else
    {
      command *= -1;

      // Regular color command
      if( command <= 65 )
      {
        for( int8_t j = 0; j < command; ++j )
        {
          *frame.pixel() = *frame_data_it;
          
          frame.gotoNextPixel();
          ++frame_data_it;
        }
      }
      // RLE color command
      else
      {
        uint8_t palette_index = *frame_data_it;

        ++frame_data_it;

        for( int8_t j = 0; j < command - 65; ++j )
        {
          *frame.pixel() = palette_index;

          frame.gotoNextPixel();
        }
      }
    }
  }

  // Make sure that the expected number of pixels were created
  if( !frame.allPixelsSet() )
  {
    qFatal( "CelFrameDecoder Error: The number of decoded pixels does not "
            "match the expected frame dimensions!\n"
            "Note: width (%i) x height (%i) != %i in frame %i of %s.",
            frame_width,
            frame_height,
            frame.getNumberOfSetPixels(),
            frame_index,
            file_name.toStdString().c_str() );
  }

  return frame.getImage();
}

// Decode a standard cel frame
QImage CelFrameDecoder::decodeStandardCelFrame( const QString& file_name,
                                                const int frame_index,
                                                const QByteArray& frame_data,
                                                const CelPalette& palette, 
                                                const int frame_width,
                                                const int frame_height )
{
  // Initialize the frame
  CelImagePixelSetter frame( frame_width, frame_height, palette );

  const char* frame_data_it = frame_data.data();
  const char* frame_data_end = frame_data_it + frame_data.size();

  while( frame_data_it != frame_data_end )
  {
    // Get the command
    uint8_t command = static_cast<uint8_t>(*frame_data_it);

    // Increment the frame data iterator
    ++frame_data_it;

    // Execute the color command
    if( command <= 127 )
    {
      for( uint8_t i = 0; i < command; ++i )
      {
        *frame.pixel() = *frame_data_it;

        frame.gotoNextPixel();
        ++frame_data_it;
      }
    }
    // Execute the transparency command
    else
    {
      for( uint8_t i = 0; i < 256-command; ++i )
      {
        *frame.pixel() = palette.getTransparentColorKey();
        frame.gotoNextPixel();
      }
    }
  }

  // Make sure that the expected number of pixels were created
  if( !frame.allPixelsSet() )
  {
    qFatal( "CelFrameDecoder Error: The number of decoded pixels does not "
            "match the expected frame dimensions!\n"
            "Note: width (%i) x height (%i) != %i in frame %i of %s.",
            frame_width,
            frame_height,
            frame.getNumberOfSetPixels(),
            frame_index,
            file_name.toStdString().c_str() );
  }

  return frame.getImage();
}

// Decode a tile cel frame with no transparency
/*! \details These always have dimensions of 32x32.
 */
QImage CelFrameDecoder::decodeNoTransTileFrame( const QString& file_name,
                                                const int frame_index,
                                                const QByteArray& frame_data,
                                                const CelPalette& palette )
{
  // Initialize the frame
  CelImagePixelSetter frame( 32, 32, palette );

  for( int i = 0; i < frame_data.size(); ++i )
  {
    *frame.pixel() = frame_data[i];
    frame.gotoNextPixel();
  }

  // Make sure that the expected number of pixels were created
  if( !frame.allPixelsSet() )
  {
    qFatal( "CelFrameDecoder Error: The number of decoded pixels does not "
            "match the expected frame dimensions!\n"
            "Note: width (32) x height (32) != %i in frame %i of %s.",
            frame.getNumberOfSetPixels(),
            frame_index,
            file_name.toStdString().c_str() );
  }

  return frame.getImage();
}

// Decode a tile cel frame with implicit upper and lower-left transparency
QImage CelFrameDecoder::decodeImplicitUpperLowerLeftTransTileFrame(
                                                 const QString& file_name,
                                                 const int frame_index,
                                                 const QByteArray& frame_data,
                                                 const CelPalette& palette )
{
  return CelFrameDecoder::decodeImplicitUpperLowerTransTileFrame(
                           file_name, frame_index, frame_data, palette, true );
}

// Decode a tile cel frame with implicit upper and lower-right transparency
QImage CelFrameDecoder::decodeImplicitUpperLowerRightTransTileFrame(
                                                 const QString& file_name,
                                                 const int frame_index,
                                                 const QByteArray& frame_data,
                                                 const CelPalette& palette )
{
  return CelFrameDecoder::decodeImplicitUpperLowerTransTileFrame(
                          file_name, frame_index, frame_data, palette, false );
}

// Decode a tile cel frame with implicit upper and lower transparency
QImage CelFrameDecoder::decodeImplicitUpperLowerTransTileFrame(
                                             const QString& file_name,
                                             const int frame_index,
                                             const QByteArray& frame_data,
                                             const CelPalette& palette, 
                                             const bool is_impl_trans_on_left )
{
  // Initialize the frame
  CelImagePixelSetter frame( 32, 32, palette );

  const char* frame_data_it = frame_data.data();

  // Get the row decoder
  TileFrameRowDecodeFunctor row_decoder =
    CelFrameDecoder::getTileFrameRowDecoder( is_impl_trans_on_left );

  for( int row = 0;
       row < s_upper_lower_impl_trans_frame_row_sizes.size();
       ++row )
  {
    bool explicit_trans_values_present = false;
    if( row%2 == 1 )
      explicit_trans_values_present = true;

    row_decoder( frame,
                 palette,
                 frame_data_it,
                 s_upper_lower_impl_trans_frame_row_sizes[row],
                 explicit_trans_values_present );
  }

  // Make sure that the expected number of pixels were created
  if( !frame.allPixelsSet() )
  {
    qFatal( "CelFrameDecoder Error: The number of decoded pixels does not "
            "match the expected frame dimensions!\n"
            "Note: width (32) x height (32) != %i in frame %i of %s.",
            frame.getNumberOfSetPixels(),
            frame_index,
            file_name.toStdString().c_str() );
  }

  return frame.getImage();
}

// Decode a tile cel frame with implicit upper-left transparency
QImage CelFrameDecoder::decodeImplicitUpperLeftTransTileFrame(
                                                 const QString& file_name,
                                                 const int frame_index,
                                                 const QByteArray& frame_data,
                                                 const CelPalette& palette )
{
  return CelFrameDecoder::decodeImplicitUpperTransTileFrame(
                           file_name, frame_index, frame_data, palette, true );
}

// Decode a tile cel frame with implicit upper-right transparency
QImage CelFrameDecoder::decodeImplicitUpperRightTransTileFrame(
                                                 const QString& file_name,
                                                 const int frame_index,
                                                 const QByteArray& frame_data,
                                                 const CelPalette& palette )
{
  return CelFrameDecoder::decodeImplicitUpperTransTileFrame(
                          file_name, frame_index, frame_data, palette, false );
}

// Decode a tile cel frame with implicit upper transparency
QImage CelFrameDecoder::decodeImplicitUpperTransTileFrame(
                                             const QString& file_name,
                                             const int frame_index,
                                             const QByteArray& frame_data,
                                             const CelPalette& palette,
                                             const bool is_impl_trans_on_left )
{
  // Initialize the frame
  CelImagePixelSetter frame( 32, 32, palette );
  
  const char* frame_data_it = frame_data.data();

  // Get the row decoder
  TileFrameRowDecodeFunctor row_decoder =
    CelFrameDecoder::getTileFrameRowDecoder( is_impl_trans_on_left );

  for( int row = 0;
       row < s_upper_impl_trans_frame_row_sizes.size();
       ++row )
  {
    bool explicit_trans_values_present = false;

    if( row <= 14 )
    {
      if( row%2 == 0 )
        explicit_trans_values_present = true;
    }

    row_decoder( frame,
                 palette,
                 frame_data_it,
                 s_upper_impl_trans_frame_row_sizes[row],
                 explicit_trans_values_present );
  }

  // Make sure that the expected number of pixels were created
  if( !frame.allPixelsSet() )
  {
    qFatal( "CelFrameDecoder Error: The number of decoded pixels does not "
            "match the expected frame dimensions!\n"
            "Note: width (32) x height (32) != %i in frame %i of %s.",
            frame.getNumberOfSetPixels(),
            frame_index,
            file_name.toStdString().c_str() );
  }

  return frame.getImage();
}

// Get the row decoder
auto CelFrameDecoder::getTileFrameRowDecoder( const bool is_impl_trans_on_left )
  -> TileFrameRowDecodeFunctor
{
  if( is_impl_trans_on_left )
    return CelFrameDecoder::decodeImplicitLeftTransTileFrameRow;
  else
    return CelFrameDecoder::decodeImplicitRightTransTileFrameRow;
}

// Check if the cel frame is a tile frame with no transparency
// Note: It is assumed that one has already checked that the size of the frame
//       is 0x400.
bool CelFrameDecoder::isNoTransTileFrame( const QString& file_name,
                                          const int frame_index )
{
  if( file_name == "l1.cel" )
  {
    // These are standard frames
    if( frame_index == 148 || frame_index == 159 || frame_index == 181 ||
        frame_index == 186 || frame_index == 188 )
      return false;
    else
      return true;
  }
  else if( file_name == "l2.cel" )
  {
    // These are standard frames
    if( frame_index == 47 || frame_index == 1397 || frame_index == 1399 ||
        frame_index == 1411 )
      return false;
    else
      return true;
  }
  else if( file_name == "l3.cel" )
  {
    return true;
  }
  else if( file_name == "l4.cel" )
  {
    // These are standard frames
    if( frame_index == 336 || frame_index == 639 )
      return false;
    else
      return true;
  }
  else if( file_name == "town.cel" )
  {
    // These are standard frames
    if( frame_index == 2328 || frame_index == 2367 || frame_index == 2593 )
      return false;
    else
      return true;
  }
  else
    return false;
}

// Check if the cel frame is a tile frame with implicit upper-left trans
bool CelFrameDecoder::hasImplicitUpperLeftTransData(
                                                 const QByteArray& frame_data )
{
  static const QVector<int> upper_left_zero_positions =
    {0, 1, 8, 9, 24, 25, 48, 49, 80, 81, 120, 121, 168, 169, 224, 225};

  for( int i : upper_left_zero_positions )
  {
    if( frame_data[i] != 0 )
      return false;
  }

  return true;
}

// Check if the cel frame is a tile frame with implicit upper-right trans
bool CelFrameDecoder::hasImplicitUpperRightTransData(
                                                 const QByteArray& frame_data )
{
  static const QVector<int> upper_right_zero_positions =
    {2, 3, 14, 15, 34, 35, 62, 63, 98, 99, 142, 143, 194, 195, 254, 255};

  for( int i : upper_right_zero_positions )
  {
    if( frame_data[i] != 0 )
      return false;
  }

  return true;
}

// Decode a row of a tile frame with implicit left transparent pixel data
void CelFrameDecoder::decodeImplicitLeftTransTileFrameRow(
                                     CelImagePixelSetter& frame,
                                     const CelPalette& palette,
                                     const char* frame_data_it,
                                     const uint8_t explicit_row_size,
                                     const bool explicit_trans_values_present )
{
  // Calculate the number of each pixel type
  uint8_t num_explicit_trans_pixels = 0;

  if( explicit_trans_values_present )
    num_explicit_trans_pixels = 2;

  uint8_t num_implicit_trans_pixels = 32 - explicit_row_size;

  uint8_t num_explicit_color_pixels =
    explicit_row_size - num_explicit_trans_pixels;

  // Add the implicit transparent pixels
  for( int i = 0; i < num_implicit_trans_pixels; ++i )
  {
    *frame.pixel() = palette.getTransparentColorKey();
    frame.gotoNextPixel();
  }

  // Add the explicit transparent pixels
  for( int i = 0; i < num_explicit_trans_pixels; ++i )
  {
    *frame.pixel() = palette.getTransparentColorKey();

    frame.gotoNextPixel();
    ++frame_data_it;
  }

  // Add the explicit color pixels
  for( int i = 0; i < num_explicit_color_pixels; ++i )
  {
    *frame.pixel() = *frame_data_it;

    frame.gotoNextPixel();
    ++frame_data_it;
  }
}

// Decode a row of a tile frame with implicit right transparent pixel data
void CelFrameDecoder::decodeImplicitRightTransTileFrameRow(
                                     CelImagePixelSetter& frame,
                                     const CelPalette& palette,
                                     const char* frame_data_it,
                                     const uint8_t explicit_row_size,
                                     const bool explicit_trans_values_present )
{
  // Calculate the number of each pixel type
  uint8_t num_explicit_trans_pixels = 0;

  if( explicit_trans_values_present )
    num_explicit_trans_pixels = 2;

  uint8_t num_implicit_trans_pixels = 32 - explicit_row_size;

  uint8_t num_explicit_color_pixels =
    explicit_row_size - num_explicit_trans_pixels;

  // Add the explicit color pixels
  for( int i = 0; i < num_explicit_color_pixels; ++i )
  {
    *frame.pixel() = *frame_data_it;

    frame.gotoNextPixel();
    ++frame_data_it;
  }

  // Add the explicit transparent pixels
  for( int i = 0; i < num_explicit_trans_pixels; ++i )
  {
    *frame.pixel() = palette.getTransparentColorKey();

    frame.gotoNextPixel();
    ++frame_data_it;
  }

  // Add the implicit transparent pixels
  for( int i = 0; i < num_implicit_trans_pixels; ++i )
  {
    *frame.pixel() = palette.getTransparentColorKey();
    frame.gotoNextPixel();
  }
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end CelFrameDecoder.cpp
//---------------------------------------------------------------------------//
