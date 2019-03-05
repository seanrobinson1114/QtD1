//---------------------------------------------------------------------------//
//!
//! \file   Farnham.cpp
//! \author Alex Robinson
//! \brief  The Farnham class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "Farnham.h"

namespace QtD1{

// Initialize static member data
QString Farnham::s_image_asset_name = "/towners/drunk/twndrunk.cel+levels/towndata/town.pal";

// Constructor
Farnham::Farnham( QGraphicsObject* parent )
  : NPC( parent, false ),
    d_direction_sprites(),
    d_sprites_loaded( false ),
    d_greeting(),
    d_quest_dialogues(),
    d_gossip_dialogues( 11 ),
    d_unused_dialogues( 8 )
{
  std::cout << "Loading Farnham dialogues..." << std::flush;
  // Load the greeting
  d_greeting.setSource( "/sfx/towners/drunk27.wav" );

  // Load the quest dialogues
  d_quest_dialogues.emplace( Quest::Type::TheButcher, 2 );
  d_quest_dialogues[Quest::Type::TheButcher][0].setSource( "/sfx/towners/drunk10.wav" );
  d_quest_dialogues[Quest::Type::TheButcher][1].setSource( "/sfx/towners/drunk11.wav" );

  d_quest_dialogues.emplace( Quest::Type::PoisonWater, 1 );
  d_quest_dialogues[Quest::Type::PoisonWater][0].setSource( "/sfx/towners/drunk04.wav" );

  d_quest_dialogues.emplace( Quest::Type::KingLeoricsCurse, 1 );
  d_quest_dialogues[Quest::Type::KingLeoricsCurse][0].setSource( "/sfx/towners/drunk01.wav" );

  d_quest_dialogues.emplace( Quest::Type::OdgensSign, 1 );
  d_quest_dialogues[Quest::Type::OdgensSign][0].setSource( "/sfx/towners/drunk02.wav" );

  d_quest_dialogues.emplace( Quest::Type::TheMagicRock,  1 );
  d_quest_dialogues[Quest::Type::TheMagicRock][0].setSource( "/sfx/towners/drunk19.wav" );

  d_quest_dialogues.emplace( Quest::Type::ArmorOfValor, 2 );
  d_quest_dialogues[Quest::Type::ArmorOfValor][0].setSource( "/sfx/towners/drunk06.wav" );
  d_quest_dialogues[Quest::Type::ArmorOfValor][1].setSource( "/sfx/towners/drunk15.wav" );

  d_quest_dialogues.emplace( Quest::Type::TheChamberOfBone, 1 );
  d_quest_dialogues[Quest::Type::TheChamberOfBone][0].setSource( "/sfx/towners/drunk07.wav" );

  d_quest_dialogues.emplace( Quest::Type::HallsOfTheBlind, 1 );
  d_quest_dialogues[Quest::Type::HallsOfTheBlind][0].setSource( "/sfx/towners/drunk12.wav" );

  d_quest_dialogues.emplace( Quest::Type::TheBlackMushroom, 1 );
  d_quest_dialogues[Quest::Type::TheBlackMushroom][0].setSource( "/sfx/towners/drunk20.wav" );

  d_quest_dialogues.emplace( Quest::Type::TheAnvilOfFury, 1 );
  d_quest_dialogues[Quest::Type::TheAnvilOfFury][0].setSource( "/sfx/towners/drunk14.wav" );

  d_quest_dialogues.emplace( Quest::Type::TheWarlordOfBlood, 1 );
  d_quest_dialogues[Quest::Type::TheWarlordOfBlood][0].setSource( "/sfx/towners/drunk17.wav" );

  d_quest_dialogues.emplace( Quest::Type::ArchbishopLazarus, 1 );
  d_quest_dialogues[Quest::Type::ArchbishopLazarus][0].setSource( "/sfx/towners/drunk12.wav" );

  // Load the gossip dialogues
  d_gossip_dialogues[0].setSource( "/sfx/towners/drunk23.wav" );
  d_gossip_dialogues[1].setSource( "/sfx/towners/drunk24.wav" );
  d_gossip_dialogues[2].setSource( "/sfx/towners/drunk25.wav" );
  d_gossip_dialogues[3].setSource( "/sfx/towners/drunk26.wav" );
  d_gossip_dialogues[4].setSource( "/sfx/towners/drunk28.wav" );
  d_gossip_dialogues[5].setSource( "/sfx/towners/drunk29.wav" );
  d_gossip_dialogues[6].setSource( "/sfx/towners/drunk30.wav" );
  d_gossip_dialogues[7].setSource( "/sfx/towners/drunk31.wav" );
  d_gossip_dialogues[8].setSource( "/sfx/towners/drunk32.wav" );
  d_gossip_dialogues[9].setSource( "/sfx/towners/drunk34.wav" );
  d_gossip_dialogues[10].setSource( "/sfx/towners/drunk35.wav" );

  // Load the unused dialogues
  d_unused_dialogues[0].setSource( "/sfx/towners/drunk21.wav" );
  d_unused_dialogues[1].setSource( "/sfx/towners/drunk18.wav" );
  d_unused_dialogues[2].setSource( "/sfx/towners/drunk05.wav" );
  d_unused_dialogues[3].setSource( "/sfx/towners/drunk22.wav" );
  d_unused_dialogues[4].setSource( "/sfx/towners/drunk09.wav" );
  d_unused_dialogues[5].setSource( "/sfx/towners/drunk08.wav" );
  d_unused_dialogues[6].setSource( "/sfx/towners/drunk33.wav" );
  d_unused_dialogues[7].setSource( "/sfx/towners/drunk16.wav" );

  std::cout << "done." << std::endl;
}

// Get the warrior description
QString Farnham::getDescription() const
{
  return QString( "FARNHAM THE DRUNK" );
}

// Get the number of image assets used by the object
int Farnham::getNumberOfImageAssets() const
{
  return 1;
}

// Get the image asset names used by the object
void Farnham::getImageAssetNames( QSet<QString>& image_asset_names ) const
{
  image_asset_names.insert( s_image_asset_name );
}

// Check if an image asset is used
bool Farnham::isImageAssetUsed( const QString& image_asset_name ) const
{
  return image_asset_name == s_image_asset_name;
}

// Check if the image assets have been loaded
bool Farnham::imageAssetsLoaded() const
{
  return d_sprites_loaded;
}

// Load the image asset
void Farnham::loadImageAsset( const QString&,
                              const QVector<QPixmap>& image_asset_frames )
{
  std::shared_ptr<BasicActor::DirectionGameSpriteMap>& direction_game_sprites =
    d_direction_sprites[s_image_asset_name];
  
  if( !direction_game_sprites )
    direction_game_sprites.reset( new BasicActor::DirectionGameSpriteMap );

  GameSprite& game_sprite = (*direction_game_sprites)[Southeast];

  // This is a new game sprite - initialize it
  if( game_sprite.getNumberOfFrames() == 0 )
  {
    QVector<int> source_frame_indices( 18 );

    for( int i = 0; i < source_frame_indices.size(); ++i )
      source_frame_indices[i] = i;

    game_sprite = GameSprite( s_image_asset_name, source_frame_indices );
  }

  game_sprite.setAsset( s_image_asset_name, image_asset_frames );
  game_sprite.setFrameDuration( 10 );
}

// Finalize image asset loading
void Farnham::finalizeImageAssetLoading()
{
  d_sprites_loaded = true;

  std::shared_ptr<NPC::StateDirectionGameSpriteMap> npc_sprites =
    std::make_shared<NPC::StateDirectionGameSpriteMap>();

  (*npc_sprites)[NPC::Standing] =
    d_direction_sprites[s_image_asset_name];
  
  this->setNPCSprites( npc_sprites );
  this->setDirection( Direction::Southeast );
}

// Dump the image assets
void Farnham::dumpImageAssets()
{
  BasicActor::DirectionGameSpriteMap::iterator direction_sprite_it,
    direction_sprite_end;

  direction_sprite_it = d_direction_sprites[s_image_asset_name]->begin();
  direction_sprite_end = d_direction_sprites[s_image_asset_name]->end();

  while( direction_sprite_it != direction_sprite_end )
  {
    direction_sprite_it.value().dumpAsset();

    ++direction_sprite_it;
  }

  d_sprites_loaded = false;
}

// Play quest dialogue
void Farnham::discussQuest( const Quest::Type quest )
{
  auto dialogue_it = d_quest_dialogues.find( quest );
  
  if( dialogue_it != d_quest_dialogues.end() )
    dialogue_it->second.front().playSound();
}

// Play gossip dialogue
void Farnham::gossip()
{
  static int gossip_index = 0;

  d_gossip_dialogues[gossip_index].playSound();

  gossip_index = (gossip_index+1)%d_gossip_dialogues.size();
}

// Greet the character
void Farnham::greet()
{
  d_greeting.playSound();
}

// Get the movement speed (pixels per game tic)
qreal Farnham::getMovementSpeed() const
{
  return 0.0;
}

// Check if the NPC has dialogue for the requested quest
bool Farnham::hasDialogue( const Quest::Type quest ) const
{
  return d_quest_dialogues.find( quest ) != d_quest_dialogues.end();
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Farnham.cpp
//---------------------------------------------------------------------------//
