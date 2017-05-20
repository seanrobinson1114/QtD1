//---------------------------------------------------------------------------//
//!
//! \file   qtd1.cpp
//! \author Alex, Sean Robinson
//! \brief  qtd1 main using qml front-end
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Qt Includes
#include <QtGui/QApplication>
#include <QtPlugin>

// QtD1 Includes
#include "MainWindow.h"

// Import custom plugins
Q_IMPORT_PLUGIN(pcx)
Q_IMPORT_PLUGIN(cel)

//! The qtd1 main using a qml front-end
int main( int argc, char** argv )
{
  // Create the app instance
  QApplication app( argc, argv );

  // Create the main window
  QtD1::MainWindow* window = QtD1::MainWindow::getInstance();
  window->loadWidgets();
  window->customShow();

  app.setQuitOnLastWindowClosed(true);
  
  // Load the game ui
  if( argc == 1 )
  {
    window->gotoTitleScreen();
  }

  // Load a tool ui
  else if( argc == 2 )
  {
    QString tool_command( argv[1] );

    // Open the image viewer
    if( tool_command == "--viewer" )
    {
      window->gotoImageViewer();
    }
    // Print a help message
    else if( tool_command == "-h" || tool_command == "--help" )
    {
      std::cout << "Allowed options: \n"
                << " -h,--help    display this help message \n"
                << " --viewer     open the image viewer"
                << std::endl;
      return 0;
    }
    // Unknown command
    else
    {
      std::cerr << "Unknown tool command (" << argv[1] << ")!" << std::endl;
      return 1;
    }
  }

  // Unknown command line options
  else
  {
    std::cerr << "Unknown command line options!" << std::endl;
    return 1;
  }

  // Run the app
  return app.exec();
}

//---------------------------------------------------------------------------//
// end qtd1.cpp
//---------------------------------------------------------------------------//
