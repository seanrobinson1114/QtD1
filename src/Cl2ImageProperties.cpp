//---------------------------------------------------------------------------//
//!
//! \file   Cl2ImageProperties.cpp
//! \author Alex Robinson
//! \brief  Cl2 image properties definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>

// QtD1 Includes
#include "Cl2ImageProperties.h"
#include "qtd1_config.h"

namespace QtD1{

// Initialize the static members
std::unique_ptr<Cl2ImageProperties> Cl2ImageProperties::s_instance;

// Get the singleton instance
Cl2ImageProperties* Cl2ImageProperties::getInstance()
{
  if( !s_instance )
    s_instance.reset( new Cl2ImageProperties );

  return s_instance.get();
}

// Constructor
Cl2ImageProperties::Cl2ImageProperties()
  : StandardImageProperties( CL2_IMAGE_PROPERTIES_PATH )
{ /* ... */ }

// Get the property file name
QString Cl2ImageProperties::getPropertyFileName() const
{
  return CL2_IMAGE_PROPERTIES_PATH;
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Cl2ImageProperties.cpp
//---------------------------------------------------------------------------//
