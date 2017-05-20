//---------------------------------------------------------------------------//
//!
//! \file   Cl2ImageProperties.h
//! \author Alex Robinson
//! \brief  Cl2 image properties declaration
//!
//---------------------------------------------------------------------------//

#ifndef CL2_IMAGE_PROPERTIES_H
#define CL2_IMAGE_PROPERTIES_H

// Std Lib Includes
#include <memory>

// QtD1 Includes
#include "StandardImageProperties.h"

namespace QtD1{

//! The cl2 image properties class
class Cl2ImageProperties : public StandardImageProperties
{

public:

  //! Get the singleton instance
  static Cl2ImageProperties* getInstance();

  //! Destructor
  ~Cl2ImageProperties()
  { /* ... */ }

  //! Get the property file name
  QString getPropertyFileName() const override;

private:

  // Constructor
  Cl2ImageProperties();

  // The singleton instance
  // Note: A unique ptr is used here for automatic garbage collection.
  static std::unique_ptr<Cl2ImageProperties> s_instance;
};

} // end QtD1 namespace

#endif // end CL2_IMAGE_PROPERTIES_H

//---------------------------------------------------------------------------//
// end Cl2ImageProperties.h
//---------------------------------------------------------------------------//
