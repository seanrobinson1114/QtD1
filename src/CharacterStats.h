//---------------------------------------------------------------------------//
//!
//! \file   CharacterStats.h
//! \author Sean Robinson, Alex Robinson
//! \brief  The character stats menu class declaration
//!
//---------------------------------------------------------------------------//

#ifndef CHARACTER_STATS_H
#define CHARACTER_STATS_H

// Std Lib Includes
#include <memory>
#include <tuple>

// Qt Includes
#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QPushButton>

namespace QtD1{

//! The spell book class
class CharacterStats : public QWidget
{
  Q_OBJECT

public:

  //! Constructor
  CharacterStats( QWidget* parent = 0 );

  //! Destructor
  ~CharacterStats()
  { /* ... */ }

signals:

public slots:

private:

};

} // end QtD1 namespace

#endif // end CHARACTER_STATS_H

//---------------------------------------------------------------------------//
// end CharacterStats.h
//---------------------------------------------------------------------------//
