//---------------------------------------------------------------------------//
//!
//! \file   MPQProperties.h
//! \author Arob
//! \brief  MPQ properties declaration
//!
//---------------------------------------------------------------------------//

#ifndef MPQ_PROPERTIES_H
#define MPQ_PROPERTIES_H

// Qt Includes
#include <QString>
#include <QStringList>
#include <QSettings>

namespace QtD1{

//! The mpq properties class
class MPQProperties
{

public:

  // Constructor
  MPQProperties();
  
  //! Destructor
  ~MPQProperties()
  { /* ... */ }

  //! Check if the file has properties (MPQ file path)
  bool doesFileHaveProperties( const QString& file_name ) const;

  //! Get the file path (including file name) in the MPQ file
  QString getFilePath( const QString& file_name ) const;

  //! Get all of the file paths (including file names)
  QStringList getFilePaths( const QRegExp& regex ) const;

  //! Get all of the file paths (including file names)
  QStringList getFilePaths( const QString& regex = ".*" ) const;

private:

  // The settings file
  QSettings d_properties_file;
};

// Get all of the file paths (including file names)
inline QStringList MPQProperties::getFilePaths( const QString& regex ) const
{
  return this->getFilePaths( QRegExp( regex ) );
}
  
} // end QtD1 namespace

#endif // end MPQ_PROPERTIES_H

//---------------------------------------------------------------------------//
// end MPQProperties.h
//---------------------------------------------------------------------------//
