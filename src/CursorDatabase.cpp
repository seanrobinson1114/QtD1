//---------------------------------------------------------------------------//
//!
//! \file   CursorDatabase.cpp
//! \author Alex Robinson
//! \brief  The cursor database class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// QtD1 Includes
#include "CursorDatabase.h"
#include "MenuSprite.h"

namespace QtD1{

// Initialize static member data
std::unique_ptr<CursorDatabase> CursorDatabase::s_instance;
  
//! Get the singleton instance
CursorDatabase* CursorDatabase::getInstance()
{
  if( !s_instance )
    s_instance.reset( new CursorDatabase( true ) );

  return s_instance.get();
}

// Default Constructor (this is only included for qml registration)
/* \details Never call this constructor directly.
 */
CursorDatabase::CursorDatabase( QObject* parent )
  : QObject( parent )
{ /* ... */ }

// Constructor
CursorDatabase::CursorDatabase( const bool load_cursors )
  : d_ui_cursor(),
    d_game_cursors(),
    d_managed_widget( NULL )
{
  if( load_cursors )
  {
    // Load the ui cursor
    QtD1::MenuSprite cursor_sprite;
    cursor_sprite.setSource( "/ui_art/cursor.pcx" );
    cursor_sprite.setBackgroundColor( "black" );
    cursor_sprite.loadSync();
    
    QPixmap ui_cursor_image = cursor_sprite.getFrame( 0 );
    
    // The cursor hotspot will be the upper-left corner (0,0)
    d_ui_cursor = QCursor( ui_cursor_image, 0, 0 );
    
    // Load the game cursors
    QtD1::MenuSprite game_cursor_sprites;
    game_cursor_sprites.setSource( "/data/inv/objcurs.cel+/levels/towndata/town.pal" );
    game_cursor_sprites.setDisplayedFrameIndices( "all" );
    game_cursor_sprites.loadSync();
    
    QVector<QPixmap> game_cursor_images;
    game_cursor_sprites.getFrames( game_cursor_images );
    
    d_game_cursors.resize( game_cursor_images.size() );
    
    for( int i = 0; i < game_cursor_images.size(); ++i )
    {
      // The first 10 cursors have a hotspot at the upper-left corner (0,0)
      if( i < 10 )
        d_game_cursors[i] = QCursor( game_cursor_images[i], 0, 0 );
      else
        d_game_cursors[i] = QCursor( game_cursor_images[i] );
    }
  }
}

// Get the cursor pixmap
QPixmap CursorDatabase::getCursorPixmap( const GameCursor cursor ) const
{
  return d_game_cursors[cursor].pixmap();
}

// Set the widget that will be managed
void CursorDatabase::setWidgetToManage( QWidget* widget )
{
  d_managed_widget = widget;
}

// Reset the cursor on the managed item
void CursorDatabase::resetCursorOnManagedWidget() const
{
  this->activateUICursor();
}

// Reset the cursor on the managed item
Q_INVOKABLE void CursorDatabase::resetCursor()
{
  CursorDatabase::getInstance()->resetCursorOnManagedWidget();
}

// Activate the UI cursor on the managed item
void CursorDatabase::activateUICursorOnManagedWidget() const
{
  if( d_managed_widget )
    d_managed_widget->setCursor( d_ui_cursor );
}

// Activate the UI cursor on the managed item
Q_INVOKABLE void CursorDatabase::activateUICursor()
{
  CursorDatabase::getInstance()->activateUICursorOnManagedWidget();
}

// Activate the desired game cursor on the managed widget
void CursorDatabase::activateGameCursorOnManagedWidget(
                                                const GameCursor cursor ) const
{
  if( d_managed_widget )
    d_managed_widget->setCursor( d_game_cursors[cursor] );
}

// Activate the desired game cursor on the managed item
Q_INVOKABLE void CursorDatabase::activateGameCursor( const GameCursor cursor )
{
  CursorDatabase::getInstance()->activateGameCursorOnManagedWidget( cursor );
}

QML_REGISTER_TYPE( CursorDatabase );
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end CursorDatabase.cpp
//---------------------------------------------------------------------------//
