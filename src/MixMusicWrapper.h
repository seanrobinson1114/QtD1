//---------------------------------------------------------------------------//
//!
//! \file   MixMusicWrapper.h
//! \author Alex Robinson
//! \brief  Mix_Music wrapper class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MIX_MUSIC_WRAPPER_H
#define MIX_MUSIC_WRAPPER_H

// SDL Includes
#include <SDL_mixer.h>

// Qt Includes
#include <QString>
#include <QByteArray>
#include <QIODevice>

namespace QtD1{

/*! The Mix_Music wrapper
 * \details This class manages the allocation and deallocation of Mix_Music
 * objects.
 */
class MixMusicWrapper
{

public:

  //! Constructor (from file)
  MixMusicWrapper( const QString& filename );

  //! Constructor (from device)
  MixMusicWrapper( QIODevice& device );

  //! Constructor (from buffer)
  MixMusicWrapper( const QByteArray& data );

  //! Destructor
  ~MixMusicWrapper();

  //! Get the raw music pointer
  Mix_Music* getRawMusicPtr();

  //! Get the raw music pointer
  const Mix_Music* getRawMusicPtr() const;
  
private:

  // Constructors and assignment operator
  MixMusicWrapper();
  MixMusicWrapper( const MixMusicWrapper& that );
  MixMusicWrapper& operator=( const MixMusicWrapper& that );

  // Load from device
  void loadFromDevice( QIODevice& device );

  // The raw mix music
  Mix_Music* d_raw_mix_music;

  // The raw music data (may be empty depending on constructor used)
  QByteArray d_raw_music_data;
};
  
} // end QtD1 namespace

#endif // end MIX_MUSIC_WRAPPER_H

//---------------------------------------------------------------------------//
// end MixMusicWrapper.h
//---------------------------------------------------------------------------//
