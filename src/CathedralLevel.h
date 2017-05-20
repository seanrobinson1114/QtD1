//---------------------------------------------------------------------------//
//!
//! \file   CathedralLevel.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The cathedral level class declaration
//!
//---------------------------------------------------------------------------//

#ifndef CATHEDRAL_LEVEL_H
#define CATHEDRAL_LEVEL_H

// QtD1 Includes
#include "Level.h"

namespace QtD1{

//! The cathedral level class declaration
class CathedralLevel : public Level
{
  Q_OBJECT

public:

  //! Constructor
  CathedralLevel( const int number, QObject* parent = 0 );

  //! Destructor
  ~CathedralLevel()
  { /* ... */ }

  //! Get the type
  Type getType() const override;

  //! Get the number
  int getNumber() const override;

private:

  // The cathedral music
  static std::shared_ptr<Music> s_cathedral_music;

  // The cathedral level number
  int d_number;
};
  
} // end QtD1 namespace

#endif // end CATHEDRAL_LEVEL_H

//---------------------------------------------------------------------------//
// end CathedralLevel.h
//---------------------------------------------------------------------------//
