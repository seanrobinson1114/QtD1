//---------------------------------------------------------------------------//
//!
//! \file   MPQFileEngine.h
//! \author Alex Robinson
//! \brief  MPQ file engine class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MPQ_FILE_ENGINE_H
#define MPQ_FILE_ENGINE_H

// Qt Includes
#include <QAbstractFileEngine>
#include <QStringList>
#include <QByteArray>

namespace QtD1{

//! The MPQ file engine class
class MPQFileEngine : public QAbstractFileEngine
{

public:

  //! Get the file concatenation character
  static char getFileConcatChar();

  //! Constructor
  MPQFileEngine( const QStringList& filenames, const QByteArray& file_data );

  //! Destructor
  ~MPQFileEngine();

  //! Open the file in the desired mode
  bool open( QIODevice::OpenMode open_mode ) override;

  //! Close the file
  bool close() override;
  
  //! Return the size of the file
  qint64 size() const override;

  //! Return the current file position
  qint64 pos() const override;

  //! Set the file position to the give offset (from the beginning of the file)
  bool seek( qint64 offset ) override;

  //! This device is not sequential
  bool isSequential() const override;

  //! This file system is case sensitive
  bool caseSensitive() const override;

  //! Check if the file has a relative path
  bool isRelativePath() const override;

  //! Return the file name in the desired format
  QString fileName( FileName file = DefaultName ) const override;

  //! Set the file name that will be used by the engine
  void setFileName( const QString& file ) override;

  //! Get the file handle used by this engine
  int handle() const override;

  //! Read data from the file
  qint64 read( char* data, qint64 maxlen ) override;

  //! Read a line of data from the file
  qint64 readLine( char* data, qint64 maxlen ) override;

private:

  // The name of the opened file(s)
  QStringList d_file_names;

  // The (possibly concatenated) file data
  QByteArray d_file_data;

  // The position in the file data
  qint64 d_file_data_pos;
};
  
} // end QtD1 namespace

#endif // end MPQ_FILE_ENGINE_H

//---------------------------------------------------------------------------//
// end MPQFileEngine.h
//---------------------------------------------------------------------------//
