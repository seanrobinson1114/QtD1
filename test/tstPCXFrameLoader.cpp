//---------------------------------------------------------------------------//
//!
//! \file   tstPCXFrameLoader.cpp
//! \author Alex Robinson
//! \brief  PCX frame loader unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Qt Includes
#include <QtTest/QtTest>
#include <QtPlugin>
#include <QSignalSpy>

// QtD1 Includes
#include "PCXFrameLoader.h"
#include "MPQHandler.h"

// Import custom plugins
Q_IMPORT_PLUGIN(pcx)

//---------------------------------------------------------------------------//
// Test suite.
//---------------------------------------------------------------------------//
class TestPCXFrameLoader : public QObject
{
  Q_OBJECT

private slots:

  void initTestCase()
  {
    // Register the MPQHandler with the file engine system
    QtD1::MPQHandler::getInstance();
  }

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the source can be set
void setSource()
{
  std::unique_ptr<QtD1::FrameLoader> loader( new QtD1::PCXFrameLoader );
  loader->setSource( "/ui_art/logo.pcx" );

  QCOMPARE( loader->getSource(), QString("/ui_art/logo.pcx") );
}
  
//---------------------------------------------------------------------------//
// Check that the transparent color can be set
void setTransparentColor()
{
  QtD1::PCXFrameLoader loader;
  loader.setTransparentColor( QColor( 0, 255, 0 ) );

  QCOMPARE( loader.getTransparentColor(), QColor( 0, 255, 0 ) );
}

//---------------------------------------------------------------------------//
// Check that the number of rows in the image can be set
void setNumberOfRows()
{
  QtD1::PCXFrameLoader loader;
  loader.setNumberOfRows( 15 );

  QCOMPARE( loader.getNumberOfRows(), 15 );
}

//---------------------------------------------------------------------------//
// Check that the number of columns in the image can be set
void setNumberOfCols()
{
  QtD1::PCXFrameLoader loader;
  loader.setNumberOfCols( 15 );

  QCOMPARE( loader.getNumberOfCols(), 15 );
}

//---------------------------------------------------------------------------//
// Check that the frames can be loaded asynchronously
void loadFrames()
{
  std::unique_ptr<QtD1::FrameLoader> loader;
  
  {
    QtD1::PCXFrameLoader* tmp_loader = new QtD1::PCXFrameLoader;
    tmp_loader->setTransparentColor( QColor( 0, 255, 0 ) );
    tmp_loader->setNumberOfRows( 15 );
    tmp_loader->setNumberOfCols( 1 );
    tmp_loader->setSource( "/ui_art/logo.pcx" );

    loader.reset( tmp_loader );
  }

  QSignalSpy frame_loaded_spy( loader.get(), SIGNAL(frameLoaded(const int,QImage)) );
  QSignalSpy source_loaded_spy( loader.get(), SIGNAL(sourceLoaded(QString)) );

  loader->loadFrames();
  loader->waitForLoadToFinish();

  // Check that 15 frames have been loaded in order
  QCOMPARE( frame_loaded_spy.size(), 15 );

  for( int i = 0; i < 15; ++i )
  {
    const QList<QVariant>& signal_args = frame_loaded_spy[i];

    QCOMPARE( signal_args.size(), 2 );
    QCOMPARE( signal_args[0].toInt(), i );

    QImage frame = signal_args[1].value<QImage>();
    QCOMPARE( frame.width(), 550 );
    QCOMPARE( frame.height(), 216 );

    // Check that the transparent pixel has been set
    for( int j = 0; j < frame.height(); ++j )
    {
      const QRgb* pixels = (const QRgb*)frame.scanLine( j );
      
      for( int i = 0; i < frame.width(); ++i )
        QVERIFY( pixels[i] != QColor( 0, 255, 0 ).rgba() );
    }
  }

  // Check that the entire source has been loaded
  QCOMPARE( source_loaded_spy.size(), 1 );
  QCOMPARE( source_loaded_spy[0].size(), 1 );
  QCOMPARE( source_loaded_spy[0][0].toString(), QString("/ui_art/logo.pcx") );
}

//---------------------------------------------------------------------------//
// Check that the frames can be loaded synchronously
void loadFramesSync()
{
  std::unique_ptr<QtD1::FrameLoader> loader;
  
  {
    QtD1::PCXFrameLoader* tmp_loader = new QtD1::PCXFrameLoader;
    tmp_loader->setTransparentColor( QColor( 0, 255, 0 ) );
    tmp_loader->setNumberOfRows( 15 );
    tmp_loader->setNumberOfCols( 1 );
    tmp_loader->setSource( "/ui_art/logo.pcx" );

    loader.reset( tmp_loader );
  }

  QSignalSpy frame_loaded_spy( loader.get(), SIGNAL(frameLoaded(const int,QImage)) );
  QSignalSpy source_loaded_spy( loader.get(), SIGNAL(sourceLoaded(QString)) );

  loader->loadFramesSync();

  // Check that 15 frames have been loaded in order
  QCOMPARE( frame_loaded_spy.size(), 15 );

  for( int i = 0; i < 15; ++i )
  {
    const QList<QVariant>& signal_args = frame_loaded_spy[i];

    QCOMPARE( signal_args.size(), 2 );
    QCOMPARE( signal_args[0].toInt(), i );

    QImage frame = signal_args[1].value<QImage>();
    QCOMPARE( frame.width(), 550 );
    QCOMPARE( frame.height(), 216 );

    // Check that the transparent pixel has been set
    for( int j = 0; j < frame.height(); ++j )
    {
      const QRgb* pixels = (const QRgb*)frame.scanLine( j );
      
      for( int i = 0; i < frame.width(); ++i )
        QVERIFY( pixels[i] != QColor( 0, 255, 0 ).rgba() );
    }
  }

  // Check that the entire source has been loaded
  QCOMPARE( source_loaded_spy.size(), 1 );
  QCOMPARE( source_loaded_spy[0].size(), 1 );
  QCOMPARE( source_loaded_spy[0][0].toString(), QString("/ui_art/logo.pcx") );
}

//---------------------------------------------------------------------------//
// Check that a subset of frames can be loaded asynchronously
void loadFrames_subset()
{
  std::unique_ptr<QtD1::FrameLoader> loader;
  
  {
    QtD1::PCXFrameLoader* tmp_loader = new QtD1::PCXFrameLoader;
    tmp_loader->setTransparentColor( QColor( 0, 255, 0 ) );
    tmp_loader->setNumberOfRows( 15 );
    tmp_loader->setNumberOfCols( 1 );
    tmp_loader->setSource( "/ui_art/logo.pcx" );

    loader.reset( tmp_loader );
  }

  QSignalSpy frame_loaded_spy( loader.get(), SIGNAL(frameLoaded(const int,QImage)) );
  QSignalSpy source_loaded_spy( loader.get(), SIGNAL(sourceLoaded(QString)) );

  QList<int> frames_to_load;
  frames_to_load << 0 << 2 << 4 << 6 << 8 << 10 << 12 << 14;
    
  loader->loadFrames( frames_to_load );
  loader->waitForLoadToFinish();

  // Check that 15 frames have been loaded in order
  QCOMPARE( frame_loaded_spy.size(), frames_to_load.size() );

  for( int i = 0; i < frames_to_load.size(); ++i )
  {
    const QList<QVariant>& signal_args = frame_loaded_spy[i];

    QCOMPARE( signal_args.size(), 2 );
    QCOMPARE( signal_args[0].toInt(), frames_to_load[i] );

    QImage frame = signal_args[1].value<QImage>();
    QCOMPARE( frame.width(), 550 );
    QCOMPARE( frame.height(), 216 );

    // Check that the transparent pixel has been set
    for( int j = 0; j < frame.height(); ++j )
    {
      const QRgb* pixels = (const QRgb*)frame.scanLine( j );
      
      for( int i = 0; i < frame.width(); ++i )
        QVERIFY( pixels[i] != QColor( 0, 255, 0 ).rgba() );
    }
  }

  // Check that the entire source has been loaded
  QCOMPARE( source_loaded_spy.size(), 1 );
  QCOMPARE( source_loaded_spy[0].size(), 1 );
  QCOMPARE( source_loaded_spy[0][0].toString(), QString("/ui_art/logo.pcx") );
}

//---------------------------------------------------------------------------//
// Check that a subset of frames can be loaded synchronously
void loadFramesSync_subset()
{
  std::unique_ptr<QtD1::FrameLoader> loader;
  
  {
    QtD1::PCXFrameLoader* tmp_loader = new QtD1::PCXFrameLoader;
    tmp_loader->setTransparentColor( QColor( 0, 255, 0 ) );
    tmp_loader->setNumberOfRows( 15 );
    tmp_loader->setNumberOfCols( 1 );
    tmp_loader->setSource( "/ui_art/logo.pcx" );

    loader.reset( tmp_loader );
  }

  QSignalSpy frame_loaded_spy( loader.get(), SIGNAL(frameLoaded(const int,QImage)) );
  QSignalSpy source_loaded_spy( loader.get(), SIGNAL(sourceLoaded(QString)) );

  QList<int> frames_to_load;
  frames_to_load << 0 << 2 << 4 << 6 << 8 << 10 << 12 << 14;
    
  loader->loadFramesSync( frames_to_load );

  // Check that 15 frames have been loaded in order
  QCOMPARE( frame_loaded_spy.size(), frames_to_load.size() );

  for( int i = 0; i < frames_to_load.size(); ++i )
  {
    const QList<QVariant>& signal_args = frame_loaded_spy[i];

    QCOMPARE( signal_args.size(), 2 );
    QCOMPARE( signal_args[0].toInt(), frames_to_load[i] );

    QImage frame = signal_args[1].value<QImage>();
    QCOMPARE( frame.width(), 550 );
    QCOMPARE( frame.height(), 216 );

    // Check that the transparent pixel has been set
    for( int j = 0; j < frame.height(); ++j )
    {
      const QRgb* pixels = (const QRgb*)frame.scanLine( j );
      
      for( int i = 0; i < frame.width(); ++i )
        QVERIFY( pixels[i] != QColor( 0, 255, 0 ).rgba() );
    }
  }

  // Check that the entire source has been loaded
  QCOMPARE( source_loaded_spy.size(), 1 );
  QCOMPARE( source_loaded_spy[0].size(), 1 );
  QCOMPARE( source_loaded_spy[0][0].toString(), QString("/ui_art/logo.pcx") );
}

//---------------------------------------------------------------------------//
// End test suite
//---------------------------------------------------------------------------//
};

//---------------------------------------------------------------------------//
// Test Main
//---------------------------------------------------------------------------//
QTEST_MAIN( TestPCXFrameLoader )
#include "tstPCXFrameLoader.moc"

//---------------------------------------------------------------------------//
// end tstPCXFrameLoader.cpp
//---------------------------------------------------------------------------//
