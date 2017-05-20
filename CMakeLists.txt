##---------------------------------------------------------------------------##
## Initialize the QtD1 project
##---------------------------------------------------------------------------##
# Define the minimum required version of CMake
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11 FATAL_ERROR)

# Define the project name
PROJECT(QtD1)

# Set the version numbers
SET(QtD1_VERSION 0.1.0)
SET(QtD1_MAJOR_VERSION 0)
SET(QtD1_MAJOR_MINOR_VERSION 0001000)
SET(QtD1_VERSION_STRING "0.1.0 (Dev)")

# Add the custom modules to the module path
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Enforce an out-of-source build
INCLUDE(EnforceOutOfSourceBuild)
ENFORCE_OUT_OF_SOURCE_BUILD()

# Add the CMAKE_BINARY_DIR to the include path to access config files
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})

# Set the runtime output directory (used with shared object libraries)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# Add compiler flags when compiling qtd1 objects
SET(QTD1_CXX_FLAGS "-Wall -pedantic -Wextra -std=c++11")

# Force shared libraries to be built
SET(BUILD_SHARED_LIBS ON)

# Set the install rpath to the lib install path - this should prevent the
# installed targets from reporting undefined .so files (check with ldd tool)
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

##---------------------------------------------------------------------------##
## Command Line Options
##---------------------------------------------------------------------------##
OPTION(QTD1_ENABLE_TESTING "Enable tests" ON)
OPTION(QTD1_ENABLE_DEV_DOCS "Enable developer API documentation" ON)

##---------------------------------------------------------------------------##
## Configure QtD1 Paths
##---------------------------------------------------------------------------##

# Set the diablo.exe and diabdat.mpq (must be in the build directory)
FIND_FILE(DIABLO_EXE_PATH "Diablo.exe" PATHS ${CMAKE_BINARY_DIR})
FIND_FILE(DIABDAT_MPQ_PATH "diabdat.mpq" PATHS ${CMAKE_BINARY_DIR})

# Set the property file paths
FIND_FILE(MPQ_PROPERTIES_PATH "mpq.ini" PATHS ${CMAKE_SOURCE_DIR}/properties)
FIND_FILE(CEL_IMAGE_PROPERTIES_PATH "cel.ini" PATHS ${CMAKE_SOURCE_DIR}/properties)
FIND_FILE(CL2_IMAGE_PROPERTIES_PATH "cl2.ini" PATHS ${CMAKE_SOURCE_DIR}/properties)

# Set the font file paths
FIND_FILE(FREE_MONO_TTF_PATH "FreeMono.ttf" PATHS ${CMAKE_SOURCE_DIR}/fonts)
FIND_FILE(FREE_MONO_BOLD_TTF_PATH "FreeMonoBold.ttf" ${CMAKE_SOURCE_DIR}/fonts)
FIND_FILE(FREE_MONO_OBLIQUE_TTF_PATH "FreeMonoOblique.ttf" ${CMAKE_SOURCE_DIR})
FIND_FILE(FREE_MONO_BOLD_OBLIQUE_TTF_PATH "FreeMonoBoldOblique.ttf" ${CMAKE_SOURCE_DIR}/fonts)

# Set the qml file paths
FIND_FILE(INTRO_SCREEN_QML_PATH "introscreen.qml" PATHS ${CMAKE_SOURCE_DIR}/qml)
FIND_FILE(TITLE_SCREEN_QML_PATH "titlescreen.qml" PATHS ${CMAKE_SOURCE_DIR}/qml)
FIND_FILE(MAIN_MENU_QML_PATH "mainmenu.qml" PATHS ${CMAKE_SOURCE_DIR}/qml)
FIND_FILE(CREDITS_SCREEN_QML_PATH "creditsscreen.qml" PATH ${CMAKE_SOURCE_DIR}/qml)
FIND_FILE(SINGLE_PLAYER_MENU_QML_PATH "singleplayermenu.qml" PATH ${CMAKE_SOURCE_DIR}/qml)
FIND_FILE(GAME_CONTROL_PANEL_QML_PATH "gamecontrolpanel.qml" PATH ${CMAKE_SOURCE_DIR}/qml)
FIND_FILE(CHARACTER_STATS_QML_PATH "characterstats.qml" PATHS ${CMAKE_SOURCE_DIR}/qml)
FIND_FILE(GAME_MENU_QML_PATH "gamemenu.qml" PATHS ${CMAKE_SOURCE_DIR}/qml)
FIND_FILE(GAME_OPTIONS_MENU_QML_PATH "gameoptionsmenu.qml" PATHS ${CMAKE_SOURCE_DIR}/qml)
FIND_FILE(IMAGE_VIEWER_QML_PATH "imageviewer.qml" PATHS ${CMAKE_SOURCE_DIR}/qml)

# Parse the qtd1 configure file so it can be used in source files
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/cmake/qtd1_config.h.in ${CMAKE_BINARY_DIR}/qtd1_config.h)

##---------------------------------------------------------------------------##
## Configure Qt4 support
##---------------------------------------------------------------------------##

# Tell CMake to run moc automatically when needed
SET(CMAKE_AUTOMOC ON)

FIND_PACKAGE(Qt4 4.8 REQUIRED)
LINK_LIBRARIES(Qt4::QtGui Qt4::QtDeclarative)
ADD_DEFINITIONS("-DQT_STATICPLUGIN")

##---------------------------------------------------------------------------##
## Configure SDL2 mixer support
##---------------------------------------------------------------------------##
IF(DEFINED SDL2_MIXER_PREFIX)
  SET(CMAKE_PREFIX_PATH ${SDL2_MIXER_PREFIX} ${CMAKE_PREFIX_PATH})
ENDIF()

FIND_PACKAGE(SDL2_mixer REQUIRED)

INCLUDE_DIRECTORIES(${SDL2MIXER_INCLUDE_DIR})
LINK_LIBRARIES(${SDL2MIXER_LIBRARY})

##---------------------------------------------------------------------------##
## Configure AVCodec support
##---------------------------------------------------------------------------##
#TODO: Write find macro for AVCodec
LINK_LIBRARIES("-lavutil -lavformat -lavcodec -lswscale -lswresample")

##---------------------------------------------------------------------------##
## Set up the directory hierarchy
##---------------------------------------------------------------------------##
IF(QTD1_ENABLE_DEV_DOCS)
  # Enable the make manual target
  ADD_SUBDIRECTORY(doc)
ENDIF()

ADD_SUBDIRECTORY(extern)
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/extern/StormLib/src/")
LINK_LIBRARIES(StormLib)

ADD_SUBDIRECTORY(src)
INCLUDE_DIRECTORIES(src)

IF(QTD1_ENABLE_TESTING)
  # Enable the make test target
  ENABLE_TESTING()

  ADD_SUBDIRECTORY(test)
ENDIF()
