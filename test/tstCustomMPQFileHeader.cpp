//---------------------------------------------------------------------------//
//!
//! \file   tstCustomMPQFileHeader.cpp
//! \author Alex Robinson
//! \brief  The custom mpq file header unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Qt Includes
#include <QtTest/QtTest>

// QtD1 Includes
#include "CustomMPQFileHeader.h"

//---------------------------------------------------------------------------//
// Test suite.
//---------------------------------------------------------------------------//
class TestCustomMPQFileHeader : public QObject
{
  Q_OBJECT

private slots:

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an element can be added to the header
void addElement()
{
  QtD1::CustomMPQFileHeader header;
  QCOMPARE( header.getNumElements(), 0 );
  
  header.addElement( "dummy_path/dummy_file1.cel", 0 );

  QCOMPARE( header.getNumElements(), 1 );
  QCOMPARE( header[0].filename, QString("dummy_path/dummy_file1.cel") );
  QCOMPARE( header[0].start_location, 0ll );

  header.addElement( "dummy_path/dummy_file2.cel", 10 );

  QCOMPARE( header.getNumElements(), 2 );
  QCOMPARE( header[1].filename, QString("dummy_path/dummy_file2.cel") );
  QCOMPARE( header[1].start_location, 10ll );
}

//---------------------------------------------------------------------------//
// Check that a header can be added to a buffer
void addToBuffer()
{
  QtD1::CustomMPQFileHeader header;
  header.addElement( "dummy_path/dummy_file1.cel", 0 );
  header.addElement( "dummy_path/dummy_file2.cel", 10 );

  QByteArray buffer( 20, 0 );

  qint64 data_start_index = header.addToBuffer( buffer );

  QCOMPARE( buffer.size(), 172 );
  QCOMPARE( data_start_index, 152ll );
}

//---------------------------------------------------------------------------//
// Check that a header can be extracted from a buffer
void extractFromBuffer()
{
  QtD1::CustomMPQFileHeader header;
  header.addElement( "dummy_path/dummy_file1.cel", 0 );
  header.addElement( "dummy_path/dummy_file2.cel", 10 );

  QByteArray buffer( 20, 0 );

  header.addToBuffer( buffer );

  // Extract the header from the buffer
  qint64 data_start_index;
  
  QtD1::CustomMPQFileHeader extracted_header =
    QtD1::CustomMPQFileHeader::extractFromBuffer( buffer, data_start_index );

  QCOMPARE( extracted_header.getNumElements(), 2 );
  QCOMPARE( extracted_header[0].filename, QString("dummy_path/dummy_file1.cel") );
  QCOMPARE( extracted_header[0].start_location, 0ll );

  QCOMPARE( extracted_header.getNumElements(), 2 );
  QCOMPARE( extracted_header[1].filename, QString("dummy_path/dummy_file2.cel") );
  QCOMPARE( extracted_header[1].start_location, 10ll );

  // Check that a buffer without a header can be handled
  buffer.clear();
  buffer.fill( 20, 0 );

  extracted_header =
    QtD1::CustomMPQFileHeader::extractFromBuffer( buffer, data_start_index );

  QCOMPARE( extracted_header.getNumElements(), 0 );
  QCOMPARE( data_start_index, 0ll );
}

//---------------------------------------------------------------------------//
// End test suite
//---------------------------------------------------------------------------//
};

//---------------------------------------------------------------------------//
// Test Main
//---------------------------------------------------------------------------//
QTEST_MAIN( TestCustomMPQFileHeader )
#include "tstCustomMPQFileHeader.moc"

//---------------------------------------------------------------------------//
// end tstCustomMPQFileHeader.cpp
//---------------------------------------------------------------------------//
