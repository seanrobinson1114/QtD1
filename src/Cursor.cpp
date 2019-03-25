//---------------------------------------------------------------------------//
//!
//! \file   Cursor.cpp
//! \author Alex Robinson
//! \brief  The cursor database class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// QtD1 Includes
#include "Cursor.h"
#include "MenuSprite.h"
#include "GrabbableInteractiveLevelObject.h"

namespace QtD1{

// Initialize static member data
std::unique_ptr<Cursor> Cursor::s_instance;
  
//! Get the singleton instance
Cursor* Cursor::getInstance()
{
  if( !s_instance )
    s_instance.reset( new Cursor( true ) );

  return s_instance.get();
}

// Default Constructor (this is only included for qml registration)
/* \details Never call this constructor directly.
 */
Cursor::Cursor( QObject* parent )
  : QObject( parent )
{ /* ... */ }

// Constructor
Cursor::Cursor( const bool load_cursors )
  : d_ui_cursor(),
    d_game_cursors(),
    d_managed_widget( NULL ),
    d_owned_object( NULL )
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

// Destructor
Cursor::~Cursor()
{
  if( d_owned_object )
  {
    if( !d_owned_object->scene() )
      delete d_owned_object;
  }
}

// Get the cursor pixmap
QPixmap Cursor::getCursorPixmap( const GameCursor cursor ) const
{
  return d_game_cursors[cursor].pixmap();
}

// Set the widget that will be managed
void Cursor::setWidgetToManage( QWidget* widget )
{
  d_managed_widget = widget;
}

// Reset the cursor on the managed item
void Cursor::resetCursorOnManagedWidget() const
{
  this->activateUICursor();
}

// Reset the cursor on the managed item
Q_INVOKABLE void Cursor::resetCursor()
{
  Cursor::getInstance()->resetCursorOnManagedWidget();
}

// Activate the UI cursor on the managed item
void Cursor::activateUICursorOnManagedWidget() const
{
  if( d_managed_widget )
    d_managed_widget->setCursor( d_ui_cursor );
}

// Activate the UI cursor on the managed item
Q_INVOKABLE void Cursor::activateUICursor()
{
  Cursor::getInstance()->activateUICursorOnManagedWidget();
}

// Activate the desired game cursor on the managed widget
void Cursor::activateGameCursorOnManagedWidget(
                                                const GameCursor cursor ) const
{
  if( d_managed_widget )
    d_managed_widget->setCursor( d_game_cursors[cursor] );
}

// Activate the desired game cursor on the managed item
Q_INVOKABLE void Cursor::activateGameCursor( const GameCursor cursor )
{
  Cursor::getInstance()->activateGameCursorOnManagedWidget( cursor );
}

// Activate the last game cursor on the managed widget
void Cursor::activateLastGameCursorOnManagedWidget()
{
  
}

// Check if a grabbable interactive level object is owned
bool Cursor::ownsObject() const
{
  return d_owned_object;
}

// Take ownership of the grabbable interactive level object
void Cursor::takeOwnershipOfObject( GrabbableInteractiveLevelObject* object )
{
  if( d_owned_object )
  {
    qWarning( "The cursor already owns and object - it will now be destroyed" );
    delete d_owned_object;
  }
  
  d_owned_object = object;

  // Pull the item from the scene
  if( d_owned_object->scene() )
    d_owned_object->scene()->removeItem( d_owned_object );

  // Pull the item from it parent item
  d_owned_object->setParent( NULL );

  this->activateGameCursorOnManagedWidget( d_owned_object->getClickCursor() );
}

// Release the grabbable interactive level object
GrabbableInteractiveLevelObject* Cursor::releaseObject()
{
  GrabbableInteractiveLevelObject* owned_object = d_owned_object;

  d_owned_object = NULL;

  this->activateUICursor();
  
  return owned_object;
}

QML_REGISTER_TYPE( Cursor );
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Cursor.cpp
//---------------------------------------------------------------------------//
