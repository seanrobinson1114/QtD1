//---------------------------------------------------------------------------//
//!
//! \file   CustomMPQFileHeader.cpp
//! \author Alex Robinson
//! \brief  Custom MPQ file header class
//!
//---------------------------------------------------------------------------//

// Qt Includes
#include <QByteArray>
#include <QDataStream>

// QtD1 Includes
#include "CustomMPQFileHeader.h"

namespace QtD1{

// Constructor
CustomMPQFileHeader::CustomMPQFileHeader()
  : d_header()
{ /* ... */ }


// Add an element to the header
void CustomMPQFileHeader::addElement( const QString& filename_with_path,
                                      const qint64 start_location )
{
  d_header.push_back( Element{filename_with_path, start_location} );
}

// Add header to buffer
/*! \details The position in the modified buffer where the data starts will
 * be returned.
 */
qint64 CustomMPQFileHeader::addToBuffer(
                                      QByteArray& buffer_without_header ) const
{
  QByteArray serialized_header_data;
  QDataStream header_data_serializer( &serialized_header_data,
                                      QIODevice::WriteOnly );
  header_data_serializer.setByteOrder( QDataStream::LittleEndian );

  // Serialize the number of header elements
  header_data_serializer << this->getHeaderKey() << d_header.size();
  
  // Serialize the header elements
  for( int i = 0; i < d_header.size(); ++i )
  {
    header_data_serializer << d_header[i].filename
                           << d_header[i].start_location;
  }

  buffer_without_header.prepend( serialized_header_data );

  return serialized_header_data.size();
}

// Return the number of header elements
int CustomMPQFileHeader::getNumElements() const
{
  return d_header.size();
}

//! Return a header element
const CustomMPQFileHeader::Element&
CustomMPQFileHeader::operator[]( int i ) const
{
  return d_header[i];
}

// Extract header from buffer
CustomMPQFileHeader CustomMPQFileHeader::extractFromBuffer(
                                                     const QByteArray& buffer,
                                                     qint64& data_start_index )
{
  CustomMPQFileHeader header;
  
  QDataStream header_data_deserializer( buffer );
  header_data_deserializer.setByteOrder( QDataStream::LittleEndian );

  // Check if there is a header present
  QString key;
  header_data_deserializer >> key;

  // Extract the header
  if( key == CustomMPQFileHeader::getHeaderKey() )
  {
    // Get the number of header elements
    int num_header_elements;
    
    header_data_deserializer >> num_header_elements;

    // Extract all of the elements
    for( int i = 0; i < num_header_elements; ++i )
    {
      QString filename;
      qint64 start_location;
      
      header_data_deserializer >> filename >> start_location;
      
      header.addElement( filename, start_location );
    }

    data_start_index = header_data_deserializer.device()->pos();
  }
  // No header present
  else
    data_start_index = 0;

  return header;
}

// Get the header key
QString CustomMPQFileHeader::getHeaderKey()
{
  return "QtD1";
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end CustomMPQFileHeader.cpp
//---------------------------------------------------------------------------//
