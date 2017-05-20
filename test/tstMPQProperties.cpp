//---------------------------------------------------------------------------//
//!
//! \file   tstMPQProperties.cpp
//! \author Alex Robinson
//! \brief  The MPQProperties unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// Qt Includes
#include <QtTest/QtTest>

// QtD1 Includes
#include "MPQProperties.h"

//---------------------------------------------------------------------------//
// Test suite.
//---------------------------------------------------------------------------//
class TestMPQProperties : public QObject
{
  Q_OBJECT

private slots:

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that MPQProperties can be initialized
void initialize()
{
  try{
    QtD1::MPQProperties properties;
  }
  catch( const std::exception& exception )
  {
    std::ostringstream oss;
    oss << "Could not load the mpq properties: "
        << exception.what();
    
    QFAIL( oss.str().c_str() );
  }
  catch( ... )
  {
    QFAIL( "Could not load the mpq properties: No further details!" );
  }
  
  // The mpq properties were created successfully
  QVERIFY( true );
}

//---------------------------------------------------------------------------//
// Check if a file has properties
void doesFileHaveProperties()
{
  const QtD1::MPQProperties properties;

  QVERIFY( properties.doesFileHaveProperties( "golddrop.cel" ) );
  QVERIFY( properties.doesFileHaveProperties( "p8bulbs.cel" ) );
  QVERIFY( !properties.doesFileHaveProperties( "dummy.dum" ) );
}

//---------------------------------------------------------------------------//
// Check that the file path can be returned
void getFilePath()
{
  const QtD1::MPQProperties properties;

  QCOMPARE( properties.getFilePath( "golddrop.cel" ),
            QString("ctrlpan/golddrop.cel") );
  QCOMPARE( properties.getFilePath( "p8bulbs.cel" ),
            QString("ctrlpan/p8bulbs.cel") );
}

//---------------------------------------------------------------------------//
// Check that the file paths can be returned
void getFilePaths()
{
  const QtD1::MPQProperties properties;

  // Get all file paths
  QStringList file_names = properties.getFilePaths();

  QCOMPARE( file_names.size(), 2874 );

  // Get all cel files
  file_names = properties.getFilePaths( ".*\\.cel" );

  QCOMPARE( file_names.size(), 281 );

  // Get all cl2 files
  file_names = properties.getFilePaths( ".*\\.cl2" );

  QCOMPARE( file_names.size(), 1121 );

  // Get all pal files
  file_names = properties.getFilePaths( ".*\\.pal" );

  QCOMPARE( file_names.size(), 41 );

  // Get all trn files
  file_names = properties.getFilePaths( ".*\\.trn" );
  
  QCOMPARE( file_names.size(), 124 );

  // Get all pcx files
  file_names = properties.getFilePaths( ".*\\.pcx" );
  
  QCOMPARE( file_names.size(), 78 );
  
  // Get all gif files
  file_names = properties.getFilePaths( ".*\\.gif" );
  
  QCOMPARE( file_names.size(), 13 );

  // Get all smk files
  file_names = properties.getFilePaths( ".*\\.smk" );
  
  QCOMPARE( file_names.size(), 10 );

  // Get all wav files
  file_names = properties.getFilePaths( ".*\\.wav" );
  
  QCOMPARE( file_names.size(), 1134 );

  // Get all dun files
  file_names = properties.getFilePaths( ".*\\.dun" );
  
  QCOMPARE( file_names.size(), 48 );

  // Get all amp files
  file_names = properties.getFilePaths( ".*\\.amp" );
  
  QCOMPARE( file_names.size(), 4 );

  // Get all sol files
  file_names = properties.getFilePaths( ".*\\.sol" );
  
  QCOMPARE( file_names.size(), 6 );

  // Get all min files
  file_names = properties.getFilePaths( ".*\\.min" );
  
  QCOMPARE( file_names.size(), 5 );

  // Get all til files
  file_names = properties.getFilePaths( ".*\\.til" );
  
  QCOMPARE( file_names.size(), 5 );

  // Get all bin files
  file_names = properties.getFilePaths( ".*\\.bin" );
  
  QCOMPARE( file_names.size(), 4 );

  // Test dummy regex
  file_names = properties.getFilePaths( "dummy" );
  
  QCOMPARE( file_names.size(), 0 );
}
  
//---------------------------------------------------------------------------//
// End test suite.
//---------------------------------------------------------------------------//
};

//---------------------------------------------------------------------------//
// Test Main
//---------------------------------------------------------------------------//
QTEST_MAIN( TestMPQProperties )
#include "tstMPQProperties.moc"

//---------------------------------------------------------------------------//
// end tstMPQProperties.cpp
//---------------------------------------------------------------------------//
