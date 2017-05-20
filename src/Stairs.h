//---------------------------------------------------------------------------//
//!
//! \file   Stairs.h
//! \author Alex Robinson, Sean Robinson
//! \brief  Stairs base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef STAIRS_H
#define STAIRS_H

// QtD1 Includes
#include "Level.h"

namespace QtD1{

//! The stairs class
class Stairs : public Object
{
  Q_OBJECT

public:

  //! Constructor
  Stairs();

  //! Destructor
  virtual ~Stairs()
  { /* ... */ }

  //! Get the next level that will be traveled to
  virtual Level::Type getNextLevel() const = 0;

  //! Get the current level
  virtual Level::Type getCurrentLevel() const = 0;

  //! Check if this is a portal
  virtual bool isPortal() const = 0;

  //! Interact with the object
  void interact() override;

signals:

  void stairsEntered( const Level::Type next_level,
                      const bool is_portal );
};
  
} // end QtD1 namespace

#endif // end STAIRS_H

//---------------------------------------------------------------------------//
// end Stairs.h
//---------------------------------------------------------------------------//
