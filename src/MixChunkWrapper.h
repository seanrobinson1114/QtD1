//---------------------------------------------------------------------------//
//!
//! \file  MixChunkWrapper.h
//! \auhor Alex Robinson
//! \brief Mix_Chunk wrapper class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MIX_CHUNK_WRAPPER_H
#define MIX_CHUNK_WRAPPER_H

// SDL Includes
#include <SDL_mixer.h>

// Qt Includes
#include <QString>
#include <QByteArray>
#include <QIODevice>

namespace QtD1{

/*! The Mix_Chunk wrapper class
 * \details This class manages the allocation and deallocation of Mix_Chunk
 * objects. 
 */
class MixChunkWrapper
{

public:

  //! Constructor (from file)
  MixChunkWrapper( const QString& filename );

  //! Constructor (from device)
  MixChunkWrapper( QIODevice& device );

  //! Constructor (from file handle)
  //MixChunkWrapper( SDL_RWops* src, const bool free_src = true );

  //! Constructor (from buffer)
  MixChunkWrapper( const QByteArray& data );

  //! Destructor
  ~MixChunkWrapper();

  //! Get the raw chunk data
  Uint8* getRawData();

  //! Get the raw chunk data
  const Uint8* getRawData() const;

  //! Get the size of the chunk (used with raw data)
  Uint32 getSize() const;

  //! Get the volume of the chunk
  Uint8 getVolume() const;

  //! Set the volume of the chunk
  void setVolume( int volume );

  //! Get the raw chunk pointer
  Mix_Chunk* getRawMixChunkPtr();

  //! Get the raw chunk pointer
  const Mix_Chunk* getRawMixChunkPtr() const;

private:

  // Constructors and assignment operator
  MixChunkWrapper();
  MixChunkWrapper( const MixChunkWrapper& that );
  MixChunkWrapper& operator=( const MixChunkWrapper& that );

  // Load from device
  void loadFromDevice( QIODevice& device );

  // The raw mix chunk
  Mix_Chunk* d_raw_mix_chunk;

  // The raw chunk data (may be empty depending on constructor used)
  QByteArray d_raw_chunk_data;
};

} // end QtD1 namespace

#endif // end MIX_CHUNK_WRAPPER_H

//---------------------------------------------------------------------------//
// end MixChunkWrapper.h
//---------------------------------------------------------------------------//
