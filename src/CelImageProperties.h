//---------------------------------------------------------------------------//
//!
//! \file   CelImageProperties.h
//! \author Alex Robinson
//! \brief  Cel image properties declaration
//!
//---------------------------------------------------------------------------//

#ifndef CEL_IMAGE_PROPERTIES_H
#define CEL_IMAGE_PROPERTIES_H

// Std Lib Includes
#include <memory>

// QtD1 Includes
#include "StandardImageProperties.h"

namespace QtD1{

//! The cel image properties class
class CelImageProperties : public StandardImageProperties
{

public:

  //! Get the singleton instance
  static CelImageProperties* getInstance();

  //! Destructor
  ~CelImageProperties()
  { /* ... */ }

  //! Get the property file name
  QString getPropertyFileName() const override;

private:

  // Constructor
  CelImageProperties();

  // The singleton instance
  // Note: A unique ptr is used here for automatic garbage collection.
  static std::unique_ptr<CelImageProperties> s_instance;
};

} // end QtD1 namespace

#endif // end CEL_IMAGE_PROPERTIES_H

//---------------------------------------------------------------------------//
// end CelImageProperties.h
//---------------------------------------------------------------------------//
