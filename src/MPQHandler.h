//---------------------------------------------------------------------------//
//!
//! \file   MPQHandler.h
//! \author Alex Robinson
//! \brief  MPQ handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MPQ_HANDLER_H
#define MPQ_HANDLER_H

// Std Lib Includes
#include <memory>

// Qt Includes
#include <QAbstractFileEngine>
#include <QString>
#include <QStringList>
#include <QByteArray>

// QtD1 Includes
#include "MPQFileEngine.h"

namespace QtD1{

/*! The mpq handler
 * \details When the singleton instance is initialized it will registered
 * with the Qt library (see the QAbstractFileEngineHandler constructor).
 */
class MPQHandler : public QAbstractFileEngineHandler
{

public:

  //! Get the singleton instance
  static MPQHandler* getInstance();
  
  //! Destructor
  ~MPQHandler();

  //! Check if the file (with path) exists in the mpq file
  bool doesFileExist( const QString& file_name_with_path ) const;

  //! Check if the concatenated files (with paths) exist in the mpq file
  bool doFilesExist( const QString& file_names_with_paths ) const;

  //! Open a file (automatic garbage collection = safe)
  std::shared_ptr<MPQFileEngine> createSafeWithCheck(
                              const QString& file_names_with_paths ) const;

  //! Open a file
  MPQFileEngine* createWithCheck(
                              const QString& file_names_with_paths ) const;
  
  //! Open a file
  MPQFileEngine* create( const QString& file_names_with_paths ) const override;

  //! Extract a file
  void extractFile( const QString& file_name_with_path,
                    QByteArray& file_data ) const;
  
private:

  // Extract file names with clean paths
  void extractFileNamesWithCleanPaths(
                                   const QString& file_names_with_paths_string,
                                   QStringList& file_names_with_paths ) const;

  // Check if the file (with mpq path style) exists in the mpq file
  bool doesFileWithMPQPathStyleExist(
                                  const QString& file_names_with_paths ) const;

  // Clean the file path (remove starting '/' and trailing '/' characters)
  static void cleanFilePath( QString& file_name_with_path );

  // Convert the path style to mpq path style
  static void convertPathStyleToMPQPathStyle( QString& file_name_with_path );
  
  // Constructor
  MPQHandler();

  // The singleton instance
  // Note: A unique ptr is used here for automatic garbage collection.
  static std::unique_ptr<MPQHandler> s_instance;

  // The mpq file
  uintptr_t d_mpq_file;
};
  
} // end QtD1 namespace

#endif // end MPQ_HANDLER_H

//---------------------------------------------------------------------------//
// end MPQHandler.h
//---------------------------------------------------------------------------//
