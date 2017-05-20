//---------------------------------------------------------------------------//
//!
//! \file   NPC.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The NPC base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef NPC_H
#define NPC_H

namespace QtD1{

//! The NPC base class
class NPC : public Object
{
  Q_OBJECT

public:

  //! Constructor
  NPC();

  //! Destructor
  virtual ~NPC()
  { /* ... */ }
};
  
} // end QtD1 namespace

#endif // end NPC_H

//---------------------------------------------------------------------------//
// end NPC.h
//---------------------------------------------------------------------------//
