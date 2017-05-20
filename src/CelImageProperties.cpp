//---------------------------------------------------------------------------//
//!
//! \file   CelImageProperties.cpp
//! \author Alex, Sean Robinson
//! \brief  Image properties definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>
#include <iostream>

// QtD1 Includes
#include "CelImageProperties.h"
#include "qtd1_config.h"

namespace QtD1{

// Initialize the static members
std::unique_ptr<CelImageProperties> CelImageProperties::s_instance;

// Get the singleton instance
CelImageProperties* CelImageProperties::getInstance()
{
  // Just-in-time initialization
  if( !s_instance )
    s_instance.reset( new CelImageProperties );

  return s_instance.get();
}

// Constructor
CelImageProperties::CelImageProperties()
  : StandardImageProperties( CEL_IMAGE_PROPERTIES_PATH )
{ /* ... */ }

// Get the property file name
QString CelImageProperties::getPropertyFileName() const
{
  return CEL_IMAGE_PROPERTIES_PATH;
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end CelImageProperties.cpp
//---------------------------------------------------------------------------//
