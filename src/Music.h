//---------------------------------------------------------------------------//
//!
//! \file   Music.h
//! \author Alex Robinson
//! \brief  The music class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MUSIC_H
#define MUSIC_H

// Std Lib Includes
#include <memory>

// Qt Includes
#include <QString>

// QtD1 Includes
#include "MixMusicWrapper.h"
#include "QMLRegistrationHelper.h"

namespace QtD1{

//! The music class
class Music : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString source READ getSource WRITE setSource)
  Q_IMPORT_ALIAS( "QtD1", 1, 0, "Music" )

public:

  //! Constructor
  Music( QObject* parent = 0 );

  //! Destructor
  ~Music()
  { /* ... */ }

  //! Get the music file source
  QString getSource() const;

  //! Set the music file source
  void setSource( const QString& source );

  //! Play the music
  Q_INVOKABLE void playMusic();

  //! Pause the music
  Q_INVOKABLE void pauseMusic();

  //! Stop the music
  Q_INVOKABLE void stopMusic();

private:

  // The music file source
  QString d_source;

  // The music
  std::unique_ptr<MixMusicWrapper> d_music;
};
  
} // end QtD1 namespace

#endif // end MUSIC_H

//---------------------------------------------------------------------------//
// end Music.h
//---------------------------------------------------------------------------//
