// //---------------------------------------------------------------------------//
// //!
// //! \file   tstLevelSquareFactory.cpp
// //! \author Alex Robinson, Sean Robinson
// //! \brief  The level square factory unit tests
// //!
// //---------------------------------------------------------------------------//
//
// // Std Lib Includes
// #include <iostream>
//
// // Qt Includes
// #include <QtTest/QtTest>
// #include <QImage>
// #include <QtPlugin>
//
// // QtD1 Includes
// #include "LevelSquareFactory.h"
// #include "LevelPillarFactory.h"
// #include "MPQHandler.h"
//
// // Import custom plugins
// Q_IMPORT_PLUGIN(cel)
// Q_IMPORT_PLUGIN(pcx)
//
// //---------------------------------------------------------------------------//
// // Test suite.
// //---------------------------------------------------------------------------//
// class TestLevelSquareFactory : public QObject
// {
//   Q_OBJECT
//
// private slots:
//
//   void initTestCase()
//   {
//     // Register the MPQHandler with the file engine system
//     QtD1::MPQHandler::getInstance();
//   }
//
// //---------------------------------------------------------------------------//
// // Tests.
// //---------------------------------------------------------------------------//
// // Check that the level squares can be constructed
// void createLevelSquares()
// {
//   QtD1::LevelSquareFactory square_factory( "/levels/towndata/town.min",
//                                            "/levels/towndata/town.sol",
//                                            "/levels/towndata/town.til" );
//
//   QList<std::shared_ptr<QtD1::LevelSquare> > squares =
//     square_factory.createLevelSquares();
//
//   QCOMPARE( squares.size(), 342 );
// }
//
// //---------------------------------------------------------------------------//
// // Check that the level squares can be constructed from cached pillars
// void createLevelSquares_cached_pillars()
// {
//   QtD1::LevelPillarFactory pillar_factory( "/levels/towndata/town.min",
//                                            "/levels/towndata/town.sol" );
//
//   QList<std::shared_ptr<QtD1::LevelPillar> > pillars =
//     pillar_factory.createLevelPillars();
//
//   QList<std::shared_ptr<QtD1::LevelSquare> > squares =
//     QtD1::LevelSquareFactory::createLevelSquares( "/levels/towndata/town.til", pillars );
//
//   QCOMPARE( squares.size(), 342 );
// }
//
// //---------------------------------------------------------------------------//
// // End test suite.
// //---------------------------------------------------------------------------//
// };
//
// //---------------------------------------------------------------------------//
// // Test Main
// //---------------------------------------------------------------------------//
// QTEST_MAIN( TestLevelSquareFactory )
// #include "tstLevelSquareFactory.moc"
//
// //---------------------------------------------------------------------------//
// // end tstLevelSquareFactory.cpp
// //---------------------------------------------------------------------------//
