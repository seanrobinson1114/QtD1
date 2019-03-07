//---------------------------------------------------------------------------//
//!
//! \file   QuestManager.cpp
//! \author Alex Robinson
//! \brief  The quest manager class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "QuestManager.h"

namespace QtD1{

// Initialize static member data
std::unique_ptr<QuestManager> QuestManager::s_instance;

// Get the quest manager instance
QuestManager& QuestManager::getInstance()
{
  // Initialize the quest manager just-in-time
  if( !s_instance )
    s_instance.reset( new QuestManager );

  return *s_instance;
}

// Constructor
QuestManager::QuestManager()
  : d_possible_quests(),
    d_active_quests(),
    d_finished_quests()
{
  // Randomly select the available quests
  d_possible_quests << Quest::Type::KingLeoricsCurse
                    << Quest::Type::PoisonWater
                    << Quest::Type::TheButcher
                    << Quest::Type::OgdensSign
                    << Quest::Type::GharbadTheWeak
                    << Quest::Type::TheMagicRock
                    << Quest::Type::ArmorOfValor
                    << Quest::Type::HallsOfTheBlind
                    << Quest::Type::ZharTheMad
                    << Quest::Type::TheBlackMushroom
                    << Quest::Type::TheAnvilOfFury
                    << Quest::Type::TheWarlordOfBlood
                    << Quest::Type::Lachdanan
                    << Quest::Type::TheChamberOfBone
                    << Quest::Type::ArchbishopLazarus
                    << Quest::Type::Diablo;
}

// Get the possible quests
const QSet<Quest::Type>& QuestManager::getPossibleQuests() const
{
  return d_possible_quests;
}

// Get the active quests
const QList<Quest::Type>& QuestManager::getActiveQuests() const
{
  return d_active_quests;
}

// Get the finished quests
const QList<Quest::Type>& QuestManager::getFinishedQuests() const
{
  return d_finished_quests;
}

// Activate a quest
void QuestManager::activateQuest( const Quest::Type quest )
{
  if( d_possible_quests.contains( quest ) &&
      !d_active_quests.contains( quest ) )
  {
    d_active_quests << quest;

    emit questActivated( quest );
  }
}

// Finish a quest
void QuestManager::finishQuest( const Quest::Type quest )
{
  if( d_active_quests.contains( quest ) )
  {
    d_active_quests.removeAll( quest );
    d_finished_quests << quest;

    emit questFinished( quest );
  }
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end QuestManager.cpp
//---------------------------------------------------------------------------//
