//---------------------------------------------------------------------------//
//!
//! \file   CustomMPQFileHeader.h
//! \author Alex Robinson
//! \brief  Custom MPQ file header class
//!
//---------------------------------------------------------------------------//

#ifndef CUSTOM_MPQ_FILE_HEADER_H
#define CUSTOM_MPQ_FILE_HEADER_H

// Qt Includes
#include <QByteArray>
#include <QVector>
#include <QString>

namespace QtD1{

//! The custom mpq file header class
class CustomMPQFileHeader
{

public:

  struct Element
  {
    QString filename;
    qint64 start_location;
  };

  //! Extract header from buffer
  static CustomMPQFileHeader extractFromBuffer( const QByteArray& buffer,
                                                qint64& data_start_index );

  //! Constructor
  CustomMPQFileHeader();

  //! Destructor
  ~CustomMPQFileHeader()
  { /* ... */ }

  //! Add an element to the header
  void addElement( const QString& filename_with_path,
                   const qint64 start_location );

  //! Add header to buffer
  qint64 addToBuffer( QByteArray& buffer_without_header ) const;

  //! Return the number of header elements
  int getNumElements() const;

  //! Return a header element
  const Element& operator[]( int i ) const;

private:

  // Get the header key
  static QString getHeaderKey();

  // The header
  QVector<Element> d_header;
};
  
} // end QtD1 namespace

#endif // end CUSTOM_MPQ_FILE_HEADER_H

//---------------------------------------------------------------------------//
// end CustomMPQFileHeader.h
//---------------------------------------------------------------------------//
