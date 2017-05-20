//---------------------------------------------------------------------------//
//!
//! \file   CharacterFrontendProxy.cpp
//! \author Alex Robinson
//! \brief  The character frontend proxy class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "CharacterFrontendProxy.h"

namespace QtD1{

// Constructor
CharacterFrontendProxy::CharacterFrontendProxy( QObject* parent )
  : QObject( parent ),
    d_character_backend( NULL )
{ 
  // Set the object name so that we can find it later
  this->setObjectName( this->objectName() );
}

// Connect to the backend
void CharacterFrontendProxy::connectToBackend(
                                             QDeclarativeView* frontend_widget,
                                             Character* character_backend )
{
  // Connect the backend signals to the frontend slots
  QObject* root_object = frontend_widget->rootObject();

  QList<CharacterFrontendProxy*> character_frontends =
    root_object->findChildren<CharacterFrontendProxy*>( CharacterFrontendProxy::objectName() );

  if( character_frontends.size() != 1 )
  {
    qFatal( "Error: QtD1 game frontend %s has been improperly set up! A "
            "qtd1 game frontend can only have one character backend "
            "object",
            frontend_widget->source().toString().toStdString().c_str() );
  }
  else
  {
    CharacterFrontendProxy* character_frontend = character_frontends[0];

    // Cache the character backend
    character_frontend->d_character_backend = character_backend;

    QObject::connect( character_backend, SIGNAL(healthChanged(const int)),
                      character_frontend, SLOT(forwardHealthChangedToFrontend(const int)) );
    QObject::connect( character_backend, SIGNAL(manaChanged(const int)),
                      character_frontend, SLOT(forwardManaChangedToFrontend(const int)) );
    QObject::connect( character_backend, SIGNAL(baseStatsChanged()),
                      character_frontend, SLOT(forwardBaseStatsChangedToFrontend()) );
    QObject::connect( character_backend, SIGNAL(statsChanged()),
                      character_frontend, SLOT(forwardStatsChangedToFrontend()) );
    QObject::connect( character_backend, SIGNAL(levelUp(const int)),
                      character_frontend, SLOT(forwardLevelUpToFrontend(const int)) );
    QObject::connect( character_backend, SIGNAL(death()),
                      character_frontend, SLOT(forwardDeathToFrontend()) );
  }
}
    
// Get the character name
QString CharacterFrontendProxy::getName() const
{
  if( d_character_backend )
    return d_character_backend->getName();
  else
    return QString();
}

// Get the character type
int CharacterFrontendProxy::getType() const
{
  if( d_character_backend )
    return d_character_backend->getType();
  else
    return 0;
}

// Get the character level
int CharacterFrontendProxy::getLevel() const
{
  if( d_character_backend )
    return d_character_backend->getLevel();
  else
    return 0;
}

// Get the character experience
int CharacterFrontendProxy::getExperience() const
{
  if( d_character_backend )
    return d_character_backend->getExperience();
  else
    return 0;
}

// Get the next level character experience
int CharacterFrontendProxy::getNextLevelExperienceThreshold() const
{
  if( d_character_backend )
    return d_character_backend->getNextLevelExperienceThreshold();
  else
    return 0;
}

// Get the amount of gold the character is holding
int CharacterFrontendProxy::getGold() const
{
  if( d_character_backend )
    return d_character_backend->getGold();
  else
    return 0;
}

// Get the base strength
int CharacterFrontendProxy::getBaseStrength() const
{
  if( d_character_backend )
    return d_character_backend->getBaseStrength();
  else
    return 0;
}

// Get the strength
int CharacterFrontendProxy::getStrength() const
{
  if( d_character_backend )
    return d_character_backend->getStrength();
  else
    return 0;
}

// Get the base magic
int CharacterFrontendProxy::getBaseMagic() const
{
  if( d_character_backend )
    return d_character_backend->getBaseMagic();
  else
    return 0;
}

// Get the magic
int CharacterFrontendProxy::getMagic() const
{
  if( d_character_backend )
    return d_character_backend->getMagic();
  else
    return 0;
}

// Get the base dexterity
int CharacterFrontendProxy::getBaseDexterity() const
{
  if( d_character_backend )
    return d_character_backend->getBaseDexterity();
  else
    return 0;
}

// Get the dexterity
int CharacterFrontendProxy::getDexterity() const
{
  if( d_character_backend )
    return d_character_backend->getDexterity();
  else
    return 0;
}

// Get the base vitality
int CharacterFrontendProxy::getBaseVitality() const
{
  if( d_character_backend )
    return d_character_backend->getBaseVitality();
  else
    return 0;
}

// Get the vitality
int CharacterFrontendProxy::getVitality() const
{
  if( d_character_backend )
    return d_character_backend->getVitality();
  else
    return 0;
}

// Get the base health
int CharacterFrontendProxy::getBaseHealth() const
{
  if( d_character_backend )
    return d_character_backend->getBaseHealth();
  else
    return 0;
}

// Get the max health
int CharacterFrontendProxy::getMaxHealth() const
{
  if( d_character_backend )
    return d_character_backend->getMaxHealth();
  else
    return 0;
}

// Get the health
int CharacterFrontendProxy::getHealth() const
{
  if( d_character_backend )
    return d_character_backend->getHealth();
  else
    return 0;
}

// Get the base mana
int CharacterFrontendProxy::getBaseMana() const
{
  if( d_character_backend )
    return d_character_backend->getBaseMana();
  else
    return 0;
}

// Get the max mana
int CharacterFrontendProxy::getMaxMana() const
{
  if( d_character_backend )
    return d_character_backend->getMaxMana();
  else
    return 0;
}

// Get the mana
int CharacterFrontendProxy::getMana() const
{
  if( d_character_backend )
    return d_character_backend->getMana();
  else
    return 0;
}

// Get the magic resistance
qreal CharacterFrontendProxy::getMagicResistance() const
{
  if( d_character_backend )
    return d_character_backend->getMagicResistance();
  else
    return 0.0;
}

// Get the fire resistance
qreal CharacterFrontendProxy::getFireResistance() const
{
  if( d_character_backend )
    return d_character_backend->getFireResistance();
  else
    return 0.0;
}

// Get the lightning resistance
qreal CharacterFrontendProxy::getLightningResistance() const
{
  if( d_character_backend )
    return d_character_backend->getLightningResistance();
  else
    return 0.0;
}

// Get the armor class
int CharacterFrontendProxy::getArmorClass() const
{
  if( d_character_backend )
    return d_character_backend->getArmorClass();
  else
    return 0;
}

// Get the minimum damage
int CharacterFrontendProxy::getMinimumDamage() const
{
  if( d_character_backend )
    return d_character_backend->getMinimumDamage();
  else
    return 0;
}

// Get the maximum damage
int CharacterFrontendProxy::getMaximumDamage() const
{
  if( d_character_backend )
    return d_character_backend->getMaximumDamage();
  else
    return 0;
}

// Get the chance to hit with melee weapon
qreal CharacterFrontendProxy::getChanceToHitWithMeleeWeapon() const
{
  if( d_character_backend )
    return d_character_backend->getChanceToHitWithMeleeWeapon();
  else
    return 0.0;
}

// Increment the base strength
void CharacterFrontendProxy::incrementBaseStrength()
{
  if( d_character_backend )
    d_character_backend->incrementBaseStrength();
  else
  {
    qWarning( "Cannot increment the base strength because the character "
              "backend has not been connected!" );
  }
}

// Increment the base magic
void CharacterFrontendProxy::incrementBaseMagic()
{
  if( d_character_backend )
    d_character_backend->incrementBaseMagic();
  else
  {
    qWarning( "Cannot increment the base magic because the character "
              "backend has not been connected!" );
  }
}

// Increment the base dexterity
void CharacterFrontendProxy::incrementBaseDexterity()
{
  if( d_character_backend )
    d_character_backend->incrementBaseDexterity();
  else
  {
    qWarning( "Cannot increment the base dexterity because the character "
              "backend has not been connected!" );
  }
}

// Increment the base vitality
void CharacterFrontendProxy::incrementBaseVitality()
{
  if( d_character_backend )
    d_character_backend->incrementBaseVitality();
  else
  {
    qWarning( "Cannot increment the base vitality because the character "
              "backend has not been connected!" );
  }
}

// Forward health changed in character backend to frontend
void CharacterFrontendProxy::forwardHealthChangedToFrontend(
                                                     const int current_health )
{
  emit healthChanged( current_health );
}

// Forward mana changed in character backend to frontend
void CharacterFrontendProxy::forwardManaChangedToFrontend(
                                                       const int current_mana )
{
  emit manaChanged( current_mana );
}

// Forward base stats changed in character backend to frontend
void CharacterFrontendProxy::forwardBaseStatsChangedToFrontend()
{
  emit baseStatsChanged();
}

// Forward stats changed in character backend to frontend
void CharacterFrontendProxy::forwardStatsChangedToFrontend()
{
  emit statsChanged();
}

// Forward level up to frontend
void CharacterFrontendProxy::forwardLevelUpToFrontend( const int new_level )
{
  emit levelUp( new_level );
}

// Forward death to frontend
void CharacterFrontendProxy::forwardDeathToFrontend()
{
  emit death();
}

// Get the object name
QString CharacterFrontendProxy::objectName()
{
  return "CharacterFrontendProxy";
}

QML_REGISTER_TYPE( CharacterFrontendProxy );
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end CharacterFrontendProxy.cpp
//---------------------------------------------------------------------------//
