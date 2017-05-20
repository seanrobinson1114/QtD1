//---------------------------------------------------------------------------//
//!
//! \file   Sound.h
//! \author Sean Robinson
//! \brief  The sound class declaration
//!
//---------------------------------------------------------------------------//

#ifndef SOUND_H
#define SOUND_H

// Std Lib Includes
#include <memory>

// Qt Includes
#include <QString>

// QtD1 Includes
#include "MixChunkWrapper.h"
#include "QMLRegistrationHelper.h"

namespace QtD1{

//! The sound class
class Sound : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString source READ getSource WRITE setSource)
  Q_IMPORT_ALIAS( "QtD1", 1, 0, "Sound" )

public:

  //! Constructor
  Sound( QObject* parent = 0 );

  //! Destructor
  ~Sound();

  //! Get the sound file source
  QString getSource() const;

  //! Set the sound file source
  void setSource( const QString& source );

  //! Play the sound
  Q_INVOKABLE void playSound();

private:

  // The sound file source
  QString d_source;

  // The sound chunk
  std::unique_ptr<MixChunkWrapper> d_chunk;
};

} // end QtD1 namespace

#endif // end SOUND_H

//---------------------------------------------------------------------------//
// end Sound.h
//---------------------------------------------------------------------------//
