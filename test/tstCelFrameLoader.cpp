//---------------------------------------------------------------------------//
//!
//! \file   tstCelFrameLoader.cpp
//! \author Alex Robinson
//! \brief  Cel frame loader unit tests
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
#include "CelFrameLoader.h"
#include "MPQHandler.h"

// Import custom plugins
Q_IMPORT_PLUGIN(cel)

//---------------------------------------------------------------------------//
// Test suite.
//---------------------------------------------------------------------------//
class TestCelFrameLoader : public QObject
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
  std::unique_ptr<QtD1::FrameLoader> loader( new QtD1::CelFrameLoader );
  loader->setSource( "/data/PentSpin.cel+levels/towndata/town.pal" );

  QCOMPARE( loader->getSource(),
            QString("/data/PentSpin.cel+levels/towndata/town.pal") );
}

//---------------------------------------------------------------------------//
// Check that the frames can be loaded asynchronously
void loadFrames()
{
  std::unique_ptr<QtD1::FrameLoader> loader;
  
  {
    QtD1::CelFrameLoader* tmp_loader = new QtD1::CelFrameLoader;
    tmp_loader->setSource( "/data/PentSpin.cel+levels/towndata/town.pal" );

    loader.reset( tmp_loader );
  }

  QSignalSpy frame_loaded_spy( loader.get(), SIGNAL(frameLoaded(const int,QImage)) );
  QSignalSpy source_loaded_spy( loader.get(), SIGNAL(sourceLoaded(QString)) );

  loader->loadFrames();
  loader->waitForLoadToFinish();

  // Check that 8 frames have been loaded in order
  QCOMPARE( frame_loaded_spy.size(), 8 );

  for( int i = 0; i < 8; ++i )
  {
    const QList<QVariant>& signal_args = frame_loaded_spy[i];

    QCOMPARE( signal_args.size(), 2 );
    QCOMPARE( signal_args[0].toInt(), i );

    QImage frame = signal_args[1].value<QImage>();
    QCOMPARE( frame.width(), 48 );
    QCOMPARE( frame.height(), 48 );
  }

  // Check that the entire source has been loaded
  QCOMPARE( source_loaded_spy.size(), 1 );
  QCOMPARE( source_loaded_spy[0].size(), 1 );
  QCOMPARE( source_loaded_spy[0][0].toString(),
            QString("/data/PentSpin.cel+levels/towndata/town.pal") );
}

//---------------------------------------------------------------------------//
// Check that the frames can be loaded synchronoulsy
void loadFramesSync()
{
  std::unique_ptr<QtD1::FrameLoader> loader;
  
  {
    QtD1::CelFrameLoader* tmp_loader = new QtD1::CelFrameLoader;
    tmp_loader->setSource( "/data/PentSpin.cel+levels/towndata/town.pal" );

    loader.reset( tmp_loader );
  }

  QSignalSpy frame_loaded_spy( loader.get(), SIGNAL(frameLoaded(const int,QImage)) );
  QSignalSpy source_loaded_spy( loader.get(), SIGNAL(sourceLoaded(QString)) );

  loader->loadFramesSync();

  // Check that 8 frames have been loaded in order
  QCOMPARE( frame_loaded_spy.size(), 8 );

  for( int i = 0; i < 8; ++i )
  {
    const QList<QVariant>& signal_args = frame_loaded_spy[i];

    QCOMPARE( signal_args.size(), 2 );
    QCOMPARE( signal_args[0].toInt(), i );

    QImage frame = signal_args[1].value<QImage>();
    QCOMPARE( frame.width(), 48 );
    QCOMPARE( frame.height(), 48 );
  }

  // Check tha the entire source has been loaded
  QCOMPARE( source_loaded_spy.size(), 1 );
  QCOMPARE( source_loaded_spy[0].size(), 1 );
  QCOMPARE( source_loaded_spy[0][0].toString(),
            QString("/data/PentSpin.cel+levels/towndata/town.pal") );
}

//---------------------------------------------------------------------------//
// Check that a subset of frames can be loaded asynchronously
void loadFrames_subset()
{
  std::unique_ptr<QtD1::FrameLoader> loader;
  
  {
    QtD1::CelFrameLoader* tmp_loader = new QtD1::CelFrameLoader;
    tmp_loader->setSource( "/data/PentSpin.cel+levels/towndata/town.pal" );

    loader.reset( tmp_loader );
  }

  QSignalSpy frame_loaded_spy( loader.get(), SIGNAL(frameLoaded(const int,QImage)) );
  QSignalSpy source_loaded_spy( loader.get(), SIGNAL(sourceLoaded(QString)) );

  QList<int> frames_to_load;
  frames_to_load << 1 << 3 << 5 << 7;
  
  loader->loadFrames( frames_to_load );
  loader->waitForLoadToFinish();

  // Check that 8 frames have been loaded in order
  QCOMPARE( frame_loaded_spy.size(), frames_to_load.size() );

  for( int i = 0; i < frames_to_load.size(); ++i )
  {
    const QList<QVariant>& signal_args = frame_loaded_spy[i];

    QCOMPARE( signal_args.size(), 2 );
    QCOMPARE( signal_args[0].toInt(), frames_to_load[i] );

    QImage frame = signal_args[1].value<QImage>();
    QCOMPARE( frame.width(), 48 );
    QCOMPARE( frame.height(), 48 );
  }

  // Check tha the entire source has been loaded
  QCOMPARE( source_loaded_spy.size(), 1 );
  QCOMPARE( source_loaded_spy[0].size(), 1 );
  QCOMPARE( source_loaded_spy[0][0].toString(),
            QString("/data/PentSpin.cel+levels/towndata/town.pal") );
}

//---------------------------------------------------------------------------//
// Check that a subset of frames can be loaded asynchronously
void loadFramesSync_subset()
{
    std::unique_ptr<QtD1::FrameLoader> loader;
  
  {
    QtD1::CelFrameLoader* tmp_loader = new QtD1::CelFrameLoader;
    tmp_loader->setSource( "/data/PentSpin.cel+levels/towndata/town.pal" );

    loader.reset( tmp_loader );
  }

  QSignalSpy frame_loaded_spy( loader.get(), SIGNAL(frameLoaded(const int,QImage)) );
  QSignalSpy source_loaded_spy( loader.get(), SIGNAL(sourceLoaded(QString)) );

  QList<int> frames_to_load;
  frames_to_load << 1 << 3 << 5 << 7;
  
  loader->loadFramesSync( frames_to_load );

  // Check that 8 frames have been loaded in order
  QCOMPARE( frame_loaded_spy.size(), frames_to_load.size() );

  for( int i = 0; i < frames_to_load.size(); ++i )
  {
    const QList<QVariant>& signal_args = frame_loaded_spy[i];

    QCOMPARE( signal_args.size(), 2 );
    QCOMPARE( signal_args[0].toInt(), frames_to_load[i] );

    QImage frame = signal_args[1].value<QImage>();
    QCOMPARE( frame.width(), 48 );
    QCOMPARE( frame.height(), 48 );
  }

  // Check tha the entire source has been loaded
  QCOMPARE( source_loaded_spy.size(), 1 );
  QCOMPARE( source_loaded_spy[0].size(), 1 );
  QCOMPARE( source_loaded_spy[0][0].toString(),
            QString("/data/PentSpin.cel+levels/towndata/town.pal") );
}

//---------------------------------------------------------------------------//
// End test suite
//---------------------------------------------------------------------------//
};

//---------------------------------------------------------------------------//
// Test Main
//---------------------------------------------------------------------------//
QTEST_MAIN( TestCelFrameLoader )
#include "tstCelFrameLoader.moc"

//---------------------------------------------------------------------------//
// end tstCelFrameLoader.cpp
//---------------------------------------------------------------------------//
