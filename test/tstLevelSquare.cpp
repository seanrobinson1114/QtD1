// //---------------------------------------------------------------------------//
// //!
// //! \file   tstLevelSquare.cpp
// //! \author Alex Robinson, Sean Robinson
// //! \brief  The level square unit tests
// //!
// //---------------------------------------------------------------------------//
//
// // Std Lib Includes
// #include <iostream>
// #include <memory>
//
// // Qt Includes
// #include <QtTest/QtTest>
// #include <QImageReader>
// #include <QImageWriter>
// #include <QPainter>
// #include <QGraphicsScene>
// #include <QtPlugin>
//
// // QtD1 Includes
// #include "LevelSquare.h"
// #include "LevelSquareFactory.h"
// #include "TownLevelPillar.h"
// #include "MPQHandler.h"
//
// // Import custom plugins
// Q_IMPORT_PLUGIN(cel)
// Q_IMPORT_PLUGIN(pcx)
//
// //---------------------------------------------------------------------------//
// // Test suite.
// //---------------------------------------------------------------------------//
// class TestLevelSquare : public QObject
// {
//   Q_OBJECT
//
// private:
//
//   // The image asset frames
//   QVector<QPixmap> t_image_asset_frames;
//
//   // Create the pillars
//   void createPillars( QtD1::LevelPillar** top_pillar,
//                       QtD1::LevelPillar** right_pillar,
//                       QtD1::LevelPillar** left_pillar,
//                       QtD1::LevelPillar** bottom_pillar )
//   {
//     QVector<QtD1::LevelPillar::Block> pillar_blocks;
//
//     // Create the top pillar
//     {
//       pillar_blocks.resize( 16 );
//
//       pillar_blocks[0].transparent = true;
//       pillar_blocks[1].transparent = true;
//       pillar_blocks[2].transparent = true;
//       pillar_blocks[3].transparent = true;
//       pillar_blocks[4].transparent = true;
//       pillar_blocks[5].transparent = true;
//       pillar_blocks[6].transparent = true;
//       pillar_blocks[7].transparent = true;
//
//       pillar_blocks[8].transparent = false;
//       pillar_blocks[8].frame_index = 256;
//       pillar_blocks[8].type = 1;
//
//       pillar_blocks[9].transparent = false;
//       pillar_blocks[9].frame_index = 257;
//       pillar_blocks[9].type = 1;
//
//       pillar_blocks[10].transparent = false;
//       pillar_blocks[10].frame_index = 258;
//       pillar_blocks[10].type = 1;
//
//       pillar_blocks[11].transparent = false;
//       pillar_blocks[11].frame_index = 259;
//       pillar_blocks[11].type = 1;
//
//       pillar_blocks[12].transparent = false;
//       pillar_blocks[12].frame_index = 260;
//       pillar_blocks[12].type = 1;
//
//       pillar_blocks[13].transparent = false;
//       pillar_blocks[13].frame_index = 261;
//       pillar_blocks[13].type = 1;
//
//       pillar_blocks[14].transparent = false;
//       pillar_blocks[14].frame_index = 262;
//       pillar_blocks[14].type = 1;
//
//       pillar_blocks[15].transparent = false;
//       pillar_blocks[15].frame_index = 263;
//       pillar_blocks[15].type = 1;
//
//       *top_pillar = new QtD1::TownLevelPillar( pillar_blocks, QtD1::LevelPillar::Properties() );
//     }
//
//     // Create the right pillar
//     {
//       pillar_blocks.clear();
//       pillar_blocks.resize( 16 );
//
//       pillar_blocks[0].transparent = true;
//       pillar_blocks[1].transparent = true;
//       pillar_blocks[2].transparent = true;
//       pillar_blocks[3].transparent = true;
//       pillar_blocks[4].transparent = true;
//       pillar_blocks[5].transparent = true;
//       pillar_blocks[6].transparent = true;
//       pillar_blocks[7].transparent = true;
//       pillar_blocks[8].transparent = true;
//
//       pillar_blocks[9].transparent = false;
//       pillar_blocks[9].frame_index = 264;
//       pillar_blocks[9].type = 1;
//
//       pillar_blocks[10].transparent = true;
//
//       pillar_blocks[11].transparent = false;
//       pillar_blocks[11].frame_index = 265;
//       pillar_blocks[11].type = 1;
//
//       pillar_blocks[12].transparent = true;
//
//       pillar_blocks[13].transparent = false;
//       pillar_blocks[13].frame_index = 266;
//       pillar_blocks[13].type = 1;
//
//       pillar_blocks[14].transparent = false;
//       pillar_blocks[14].frame_index = 267;
//       pillar_blocks[14].type = 2;
//
//       pillar_blocks[15].transparent = false;
//       pillar_blocks[15].frame_index = 268;
//       pillar_blocks[15].type = 3;
//
//       *right_pillar = new QtD1::TownLevelPillar( pillar_blocks, QtD1::LevelPillar::Properties() );
//     }
//
//     // Create the left pillar
//     {
//       pillar_blocks.clear();
//       pillar_blocks.resize( 16 );
//
//       pillar_blocks[0].transparent = true;
//       pillar_blocks[1].transparent = true;
//       pillar_blocks[2].transparent = true;
//       pillar_blocks[3].transparent = true;
//       pillar_blocks[4].transparent = true;
//       pillar_blocks[5].transparent = true;
//       pillar_blocks[6].transparent = true;
//       pillar_blocks[7].transparent = true;
//
//       pillar_blocks[8].transparent = false;
//       pillar_blocks[8].frame_index = 269;
//       pillar_blocks[8].type = 1;
//
//       pillar_blocks[9].transparent = true;
//
//       pillar_blocks[10].transparent = false;
//       pillar_blocks[10].frame_index = 270;
//       pillar_blocks[10].type = 1;
//
//       pillar_blocks[11].transparent = true;
//
//       pillar_blocks[12].transparent = false;
//       pillar_blocks[12].frame_index = 271;
//       pillar_blocks[12].type = 1;
//
//       pillar_blocks[13].transparent = true;
//
//       pillar_blocks[14].transparent = false;
//       pillar_blocks[14].frame_index = 272;
//       pillar_blocks[14].type = 2;
//
//       pillar_blocks[15].transparent = false;
//       pillar_blocks[15].frame_index = 273;
//       pillar_blocks[15].type = 3;
//
//       *left_pillar = new QtD1::TownLevelPillar( pillar_blocks, QtD1::LevelPillar::Properties() );
//     }
//
//     // Create the bottom pillar
//     {
//       pillar_blocks.clear();
//       pillar_blocks.resize( 16 );
//
//       pillar_blocks[0].transparent = true;
//       pillar_blocks[1].transparent = true;
//       pillar_blocks[2].transparent = true;
//       pillar_blocks[3].transparent = true;
//       pillar_blocks[4].transparent = true;
//       pillar_blocks[5].transparent = true;
//       pillar_blocks[6].transparent = true;
//       pillar_blocks[7].transparent = true;
//       pillar_blocks[8].transparent = true;
//       pillar_blocks[9].transparent = true;
//       pillar_blocks[10].transparent = true;
//       pillar_blocks[11].transparent = true;
//       pillar_blocks[12].transparent = true;
//       pillar_blocks[13].transparent = true;
//
//       pillar_blocks[14].transparent = false;
//       pillar_blocks[14].frame_index = 274;
//       pillar_blocks[14].type = 2;
//
//       pillar_blocks[15].transparent = false;
//       pillar_blocks[15].frame_index = 275;
//       pillar_blocks[15].type = 3;
//
//       *bottom_pillar = new QtD1::TownLevelPillar( pillar_blocks, QtD1::LevelPillar::Properties() );
//     }
//   }
//
// private slots:
//
//   void initTestCase()
//   {
//     // Register the MPQHandler with the file engine system
//     QtD1::MPQHandler::getInstance();
//
//     // Load the image asset frames
//     QImageReader asset_reader( "/levels/towndata/town.cel+levels/towndata/town.pal" );
//
//     t_image_asset_frames.resize( asset_reader.imageCount() );
//
//     for( int i = 0; i < asset_reader.imageCount(); ++i )
//     {
//       t_image_asset_frames[i].convertFromImage( asset_reader.read() );
//
//       asset_reader.jumpToNextImage();
//     }
//   }
//
// //---------------------------------------------------------------------------//
// // Tests.
// //---------------------------------------------------------------------------//
// // Check that a level square can be constructed
// void constructor()
// {
//   QtD1::LevelPillar* top_pillar, *right_pillar, *left_pillar, *bottom_pillar;
//
//   createPillars( &top_pillar, &right_pillar, &left_pillar, &bottom_pillar );
//
//   QtD1::LevelSquare square( top_pillar,
//                             right_pillar,
//                             left_pillar,
//                             bottom_pillar );
//   QRectF square_rect = square.boundingRect();
//
//   QCOMPARE( square_rect.width(), 128. );
//   QCOMPARE( square_rect.height(), 288. );
// }
//
// //---------------------------------------------------------------------------//
// // Check that the number of image assets can be returned
// void getNumberOfImageAssets()
// {
//   QtD1::LevelPillar* top_pillar, *right_pillar, *left_pillar, *bottom_pillar;
//
//   createPillars( &top_pillar, &right_pillar, &left_pillar, &bottom_pillar );
//
//   QtD1::LevelSquare square( top_pillar,
//                             right_pillar,
//                             left_pillar,
//                             bottom_pillar );
//   QCOMPARE( square.getNumberOfImageAssets(), 1 );
// }
//
// //---------------------------------------------------------------------------//
// // Check that the image assets used by the square can be retrieved
// void getImageAssetNames()
// {
//   QtD1::LevelPillar* top_pillar, *right_pillar, *left_pillar, *bottom_pillar;
//
//   createPillars( &top_pillar, &right_pillar, &left_pillar, &bottom_pillar );
//
//   QtD1::LevelSquare square( top_pillar,
//                             right_pillar,
//                             left_pillar,
//                             bottom_pillar );
//   QSet<QString> image_asset_names;
//
//   square.getImageAssetNames( image_asset_names );
//
//   QCOMPARE( image_asset_names.size(), 1 );
//   QVERIFY( image_asset_names.contains( "/levels/towndata/town.cel+levels/towndata/town.pal" ) );
// }
//
// //---------------------------------------------------------------------------//
// // Check if the image asset is used by the square
// void isImageAssetUsed()
// {
//   QtD1::LevelPillar* top_pillar, *right_pillar, *left_pillar, *bottom_pillar;
//
//   createPillars( &top_pillar, &right_pillar, &left_pillar, &bottom_pillar );
//
//   QtD1::LevelSquare square( top_pillar,
//                             right_pillar,
//                             left_pillar,
//                             bottom_pillar );
//
//   QVERIFY( square.isImageAssetUsed( "/levels/towndata/town.cel+levels/towndata/town.pal" ) );
//   QVERIFY( !square.isImageAssetUsed( "/dummy/dummy.cel" ) );
// }
//
// //---------------------------------------------------------------------------//
// // Check that an image asset can be loaded
// void loadImageAsset()
// {
//   QtD1::LevelPillar* top_pillar, *right_pillar, *left_pillar, *bottom_pillar;
//
//   createPillars( &top_pillar, &right_pillar, &left_pillar, &bottom_pillar );
//
//   QtD1::LevelSquare square( top_pillar,
//                             right_pillar,
//                             left_pillar,
//                             bottom_pillar );
//
//   QVERIFY( !square.imageAssetsLoaded() );
//
//   square.loadImageAsset( "/levels/towndata/town.cel+levels/towndata/town.pal",
//                          t_image_asset_frames );
//
//   QVERIFY( square.imageAssetsLoaded() );
// }
//
// //---------------------------------------------------------------------------//
// // Check that image assets can be dumped
// void dumpImageAssets()
// {
//   QtD1::LevelPillar* top_pillar, *right_pillar, *left_pillar, *bottom_pillar;
//
//   createPillars( &top_pillar, &right_pillar, &left_pillar, &bottom_pillar );
//
//   QtD1::LevelSquare square( top_pillar,
//                             right_pillar,
//                             left_pillar,
//                             bottom_pillar );
//
//   QVERIFY( !square.imageAssetsLoaded() );
//
//   square.loadImageAsset( "/levels/towndata/town.cel+levels/towndata/town.pal",
//                          t_image_asset_frames );
//
//   QVERIFY( square.imageAssetsLoaded() );
//
//   square.dumpImageAssets();
//
//   QVERIFY( !square.imageAssetsLoaded() );
// }
//
// //---------------------------------------------------------------------------//
// // Check that the square can be cloned
// void clone()
// {
//   QtD1::LevelPillar* top_pillar, *right_pillar, *left_pillar, *bottom_pillar;
//
//   createPillars( &top_pillar, &right_pillar, &left_pillar, &bottom_pillar );
//
//   QtD1::LevelSquare* square( new QtD1::LevelSquare( top_pillar,
//                                                     right_pillar,
//                                                     left_pillar,
//                                                     bottom_pillar ) );
//
//   square->loadImageAsset( "/levels/towndata/town.cel+levels/towndata/town.pal",
//                           t_image_asset_frames );
//
//   QtD1::LevelSquare* square_clone = square->clone();
//
//   QCOMPARE( square->boundingRect(), square_clone->boundingRect() );
//   QVERIFY( square != square_clone );
//
//   delete square;
//   delete square_clone;
// }
//
// //---------------------------------------------------------------------------//
// // Check that the square can be painted
// void paint_33()
// {
//   QtD1::LevelPillar* top_pillar, *right_pillar, *left_pillar, *bottom_pillar;
//
//   createPillars( &top_pillar, &right_pillar, &left_pillar, &bottom_pillar );
//
//   QtD1::LevelSquare* square( new QtD1::LevelSquare( top_pillar,
//                                                     right_pillar,
//                                                     left_pillar,
//                                                     bottom_pillar ) );
//
//   square->loadImageAsset( "/levels/towndata/town.cel+levels/towndata/town.pal",
//                           t_image_asset_frames );
//
//   QGraphicsScene square_scene( square->boundingRect() );
//   square_scene.addItem( square );
//
//   QImage square_image( square->boundingRect().size().toSize(),
//                        QImage::Format_ARGB32 );
//   square_image.fill( Qt::transparent );
//
//   QPainter square_painter( &square_image );
//
//   square_scene.render( &square_painter );
//
//   // Save the square image for visual inspection
//   QImageWriter image_writer( "square_033.png" );
//   image_writer.write( square_image );
// }
//
// //---------------------------------------------------------------------------//
// // Check that the square can be painted
// void paint_58()
// {
//   QtD1::LevelSquare* square;
//
//   {
//     QtD1::LevelSquareFactory square_factory( "/levels/towndata/town.min",
//                                              "/levels/towndata/town.sol",
//                                              "/levels/towndata/town.til" );
//
//     QList<std::shared_ptr<QtD1::LevelSquare> > squares =
//       square_factory.createLevelSquares();
//
//     square = squares[58]->clone();
//   }
//
//   square->loadImageAsset( "/levels/towndata/town.cel+levels/towndata/town.pal",
//                           t_image_asset_frames );
//
//   QGraphicsScene square_scene( square->boundingRect() );
//   square_scene.addItem( square );
//
//   QImage square_image( square->boundingRect().size().toSize(),
//                        QImage::Format_ARGB32 );
//   square_image.fill( Qt::transparent );
//
//   QPainter square_painter( &square_image );
//
//   square_scene.render( &square_painter );
//
//   // Save the square image for visual inspection
//   QImageWriter image_writer( "square_058.png" );
//   image_writer.write( square_image );
// }
//
// //---------------------------------------------------------------------------//
// // Check that the square can be painted
// void paint_21()
// {
//   QtD1::LevelSquare* square;
//
//   {
//     QtD1::LevelSquareFactory square_factory( "/levels/towndata/town.min",
//                                              "/levels/towndata/town.sol",
//                                              "/levels/towndata/town.til" );
//
//     QList<std::shared_ptr<QtD1::LevelSquare> > squares =
//       square_factory.createLevelSquares();
//
//     square = squares[21]->clone();
//   }
//
//   square->loadImageAsset( "/levels/towndata/town.cel+levels/towndata/town.pal",
//                           t_image_asset_frames );
//
//   QGraphicsScene square_scene( square->boundingRect() );
//   square_scene.addItem( square );
//
//   QImage square_image( square->boundingRect().size().toSize(),
//                        QImage::Format_ARGB32 );
//   square_image.fill( Qt::transparent );
//
//   QPainter square_painter( &square_image );
//
//   square_scene.render( &square_painter );
//
//   // Save the square image for visual inspection
//   QImageWriter image_writer( "square_021.png" );
//   image_writer.write( square_image );
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
// QTEST_MAIN( TestLevelSquare )
// #include "tstLevelSquare.moc"
//
// //---------------------------------------------------------------------------//
// // end tstLevelSquare.cpp
// //---------------------------------------------------------------------------//
