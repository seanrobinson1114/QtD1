# Set the test file paths
FIND_FILE(TEST_FILE_TXT_PATH "test_file.txt" PATHS ${CMAKE_CURRENT_SOURCE_DIR}/test_files)

# Configure the test config file
CONFIGURE_FILE(qtd1_test_config.h.in ${CMAKE_CURRENT_BINARY_DIR}/qtd1_test_config.h)

# Add the CMAKE_CURRENT_SOURCE_DIR and the CMAKE_CURRENT_BINARY_DIR to the
# include path (the binary is necessary to access moc files)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

# Add the qtd1_core and Qt::QTest library to the link libraries
LINK_LIBRARIES(qtd1_core Qt4::QtTest)

ADD_EXECUTABLE(tstMPQProperties tstMPQProperties.cpp)
SET_TARGET_PROPERTIES(tstMPQProperties PROPERTIES COMPILE_FLAGS "${QTD1_CXX_FLAGS}" RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
ADD_TEST(MPQproperties_test tstMPQProperties -v2)

ADD_EXECUTABLE(tstCustomMPQFileHeader tstCustomMPQFileHeader.cpp)
SET_TARGET_PROPERTIES(tstCustomMPQFileHeader PROPERTIES COMPILE_FLAGS "${QTD1_CXX_FLAGS}" RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
ADD_TEST(CustomMPQFileHeader_test tstCustomMPQFileHeader -v2)

ADD_EXECUTABLE(tstMPQFileEngine tstMPQFileEngine.cpp)
SET_TARGET_PROPERTIES(tstMPQFileEngine PROPERTIES COMPILE_FLAGS "${QTD1_CXX_FLAGS}" RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
ADD_TEST(MPQFileEngine_test tstMPQFileEngine -v2)

ADD_EXECUTABLE(tstMPQHandler tstMPQHandler.cpp)
SET_TARGET_PROPERTIES(tstMPQHandler PROPERTIES COMPILE_FLAGS "${QTD1_CXX_FLAGS}" RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
ADD_TEST(MPQHandler_test tstMPQHandler -v2)

ADD_EXECUTABLE(tstFileInterface tstFileInterface.cpp)
SET_TARGET_PROPERTIES(tstFileInterface PROPERTIES COMPILE_FLAGS "${QTD1_CXX_FLAGS}" RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
ADD_TEST(FileInterface_test tstFileInterface -v2)

ADD_EXECUTABLE(tstCelImageProperties tstCelImageProperties.cpp)
SET_TARGET_PROPERTIES(tstCelImageProperties PROPERTIES COMPILE_FLAGS "${QTD1_CXX_FLAGS}" RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
ADD_TEST(CelImageProperties_test tstCelImageProperties -v2)

ADD_EXECUTABLE(tstCl2ImageProperties tstCl2ImageProperties.cpp)
SET_TARGET_PROPERTIES(tstCl2ImageProperties PROPERTIES COMPILE_FLAGS "${QTD1_CXX_FLAGS}" RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
ADD_TEST(Cl2ImageProperties_test tstCl2ImageProperties -v2)

ADD_EXECUTABLE(tstCelPalette tstCelPalette.cpp)
SET_TARGET_PROPERTIES(tstCelPalette PROPERTIES COMPILE_FLAGS "${QTD1_CXX_FLAGS}" RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
ADD_TEST(CelPalette_test tstCelPalette -v2)

ADD_EXECUTABLE(tstCelImagePixelSetter tstCelImagePixelSetter.cpp)
SET_TARGET_PROPERTIES(tstCelImagePixelSetter PROPERTIES COMPILE_FLAGS "${QTD1_CXX_FLAGS}" RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
ADD_TEST(CelImagePixelSetter_test tstCelImagePixelSetter -v2)

ADD_EXECUTABLE(tstCelDecoder tstCelDecoder.cpp)
SET_TARGET_PROPERTIES(tstCelDecoder PROPERTIES COMPILE_FLAGS "${QTD1_CXX_FLAGS}" RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
ADD_TEST(CelDecoder_test tstCelDecoder -v2)

ADD_EXECUTABLE(tstCelHandler tstCelHandler.cpp)
SET_TARGET_PROPERTIES(tstCelHandler PROPERTIES COMPILE_FLAGS "${QTD1_CXX_FLAGS}" RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
TARGET_LINK_LIBRARIES(tstCelHandler qtd1_cel_plugin)
ADD_TEST(CelHandler_test tstCelHandler -v2)

ADD_EXECUTABLE(tstBitmapFont tstBitmapFont.cpp)
SET_TARGET_PROPERTIES(tstBitmapFont PROPERTIES COMPILE_FLAGS "${QTD1_CXX_FLAGS}" RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
TARGET_LINK_LIBRARIES(tstBitmapFont qtd1_cel_plugin qtd1_pcx_plugin)
ADD_TEST(BitmapFont_test tstBitmapFont -v2)

ADD_EXECUTABLE(tstViewport tstViewport.cpp)
SET_TARGET_PROPERTIES(tstViewport PROPERTIES COMPILE_FLAGS "${QTD1_CXX_FLAGS}" RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
TARGET_LINK_LIBRARIES(tstViewport)
ADD_TEST(Viewport_test tstViewport -v2)

ADD_EXECUTABLE(tstPCXFrameLoader tstPCXFrameLoader.cpp)
SET_TARGET_PROPERTIES(tstPCXFrameLoader PROPERTIES COMPILE_FLAGS "${QTD1_CXX_FLAGS}" RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
TARGET_LINK_LIBRARIES(tstPCXFrameLoader qtd1_pcx_plugin)
ADD_TEST(PCXFrameLoader_test tstPCXFrameLoader -v2)

ADD_EXECUTABLE(tstCelFrameLoader tstCelFrameLoader.cpp)
SET_TARGET_PROPERTIES(tstCelFrameLoader PROPERTIES COMPILE_FLAGS "${QTD1_CXX_FLAGS}" RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
TARGET_LINK_LIBRARIES(tstCelFrameLoader qtd1_cel_plugin)
ADD_TEST(CelFrameLoader_test tstCelFrameLoader -v2)

ADD_EXECUTABLE(tstImageAssetLoader tstImageAssetLoader.cpp)
SET_TARGET_PROPERTIES(tstImageAssetLoader PROPERTIES COMPILE_FLAGS "${QTD1_CXX_FLAGS}" RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
TARGET_LINK_LIBRARIES(tstImageAssetLoader qtd1_pcx_plugin qtd1_cel_plugin)
ADD_TEST(ImageAssetLoader_test tstImageAssetLoader -v2)

ADD_EXECUTABLE(tstMenuSprite tstMenuSprite.cpp)
SET_TARGET_PROPERTIES(tstMenuSprite PROPERTIES COMPILE_FLAGS "${QTD1_CXX_FLAGS}" RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
TARGET_LINK_LIBRARIES(tstMenuSprite qtd1_cel_plugin qtd1_pcx_plugin)
ADD_TEST(MenuSprite_test tstMenuSprite -v2)

ADD_EXECUTABLE(tstGameSprite tstGameSprite.cpp)
SET_TARGET_PROPERTIES(tstGameSprite PROPERTIES COMPILE_FLAGS "${QTD1_CXX_FLAGS}" RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
TARGET_LINK_LIBRARIES(tstGameSprite qtd1_cel_plugin)
ADD_TEST(GameSprite_test tstGameSprite -v2)

ADD_EXECUTABLE(tstTownLevelPillar tstTownLevelPillar.cpp)
SET_TARGET_PROPERTIES(tstTownLevelPillar PROPERTIES COMPILE_FLAGS "${QTD1_CXX_FLAGS}" RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
TARGET_LINK_LIBRARIES(tstTownLevelPillar qtd1_cel_plugin qtd1_pcx_plugin)
ADD_TEST(TownLevelPillar_test tstTownLevelPillar -v2)

ADD_EXECUTABLE(tstLevelPillarFactory tstLevelPillarFactory.cpp)
SET_TARGET_PROPERTIES(tstLevelPillarFactory PROPERTIES COMPILE_FLAGS "${QTD1_CXX_FLAGS}" RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
TARGET_LINK_LIBRARIES(tstLevelPillarFactory qtd1_cel_plugin qtd1_pcx_plugin)
ADD_TEST(LevelPillarFactory_test tstLevelPillarFactory -v2)

ADD_EXECUTABLE(tstLevelSquare tstLevelSquare.cpp)
SET_TARGET_PROPERTIES(tstLevelSquare PROPERTIES COMPILE_FLAGS "${QTD1_CXX_FLAGS}" RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
TARGET_LINK_LIBRARIES(tstLevelSquare qtd1_cel_plugin qtd1_pcx_plugin)
ADD_TEST(LevelSquare_test tstLevelSquare -v2)

ADD_EXECUTABLE(tstLevelSquareFactory tstLevelSquareFactory.cpp)
SET_TARGET_PROPERTIES(tstLevelSquareFactory PROPERTIES COMPILE_FLAGS "${QTD1_CXX_FLAGS}" RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
TARGET_LINK_LIBRARIES(tstLevelSquareFactory qtd1_cel_plugin qtd1_pcx_plugin)
ADD_TEST(LevelSquareFactory_test tstLevelSquareFactory -v2)

ADD_EXECUTABLE(tstLevelSector tstLevelSector.cpp)
SET_TARGET_PROPERTIES(tstLevelSector PROPERTIES COMPILE_FLAGS "${QTD1_CXX_FLAGS}" RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
TARGET_LINK_LIBRARIES(tstLevelSector qtd1_cel_plugin qtd1_pcx_plugin)
ADD_TEST(LevelSector_test tstLevelSector -v2)

ADD_EXECUTABLE(tstLevelSectorFactory tstLevelSectorFactory.cpp)
SET_TARGET_PROPERTIES(tstLevelSectorFactory PROPERTIES COMPILE_FLAGS "${QTD1_CXX_FLAGS}" RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
TARGET_LINK_LIBRARIES(tstLevelSectorFactory qtd1_cel_plugin qtd1_pcx_plugin)
ADD_TEST(LevelSectorFactory_test tstLevelSectorFactory -v2)
