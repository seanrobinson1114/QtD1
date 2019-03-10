//---------------------------------------------------------------------------//
//!
//! \file   Farnham.cpp
//! \author Alex Robinson
//! \brief  The Farnham class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "Farnham.h"
#include "FarnhamInteractionMenu.h"

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
  // Load the greeting
  d_greeting.setSource( "/sfx/towners/drunk27.wav" );

  // Load the quest dialogues
  d_quest_dialogues.emplace( Quest::Type::TheButcher, 2 );
  d_quest_dialogues[Quest::Type::TheButcher][0].dialogue_file_name = "/sfx/towners/drunk10.wav";
  d_quest_dialogues[Quest::Type::TheButcher][0].raw_dialogue_text =
    "Big! Big cleaver killing all my friends. Couldn't stop him, had to run "
    "away, couldn't save them. Trapped in a room with so many bodies... so "
    "many friends... NOOOOOOOOOO!";
  
  d_quest_dialogues[Quest::Type::TheButcher][1].dialogue_file_name = "/sfx/towners/drunk11.wav";
  d_quest_dialogues[Quest::Type::TheButcher][1].raw_dialogue_text = "...";

  d_quest_dialogues.emplace( Quest::Type::PoisonWater, 1 );
  d_quest_dialogues[Quest::Type::PoisonWater][0].dialogue_file_name = "/sfx/towners/drunk04.wav";
  d_quest_dialogues[Quest::Type::PoisonWater][0].raw_dialogue_text =
    "You drink water?";

  d_quest_dialogues.emplace( Quest::Type::KingLeoricsCurse, 1 );
  d_quest_dialogues[Quest::Type::KingLeoricsCurse][0].dialogue_file_name = "/sfx/towners/drunk01.wav";
  d_quest_dialogues[Quest::Type::KingLeoricsCurse][0].raw_dialogue_text =
    "I don't care about that. Listen, no skeleton is gonna be MY king. Leoric "
    "is King. King, so you hear me? HAIL TO THE KING!";

  d_quest_dialogues.emplace( Quest::Type::OgdensSign, 1 );
  d_quest_dialogues[Quest::Type::OgdensSign][0].dialogue_file_name = "/sfx/towners/drunk02.wav";
  d_quest_dialogues[Quest::Type::OgdensSign][0].raw_dialogue_text =
    "You know what I think? Somebody took that sign, and they gonna want lots "
    "of money for it. If I was Ogden... and I'm not, but if I was... I'd just "
    "buy a new sign with some pretty drawing on it. Maybe a nice mug of ale "
    "or a piece of cheese...";

  d_quest_dialogues.emplace( Quest::Type::TheMagicRock,  1 );
  d_quest_dialogues[Quest::Type::TheMagicRock][0].dialogue_file_name = "/sfx/towners/drunk19.wav";
  d_quest_dialogues[Quest::Type::TheMagicRock][0].raw_dialogue_text =
    "I used to have a nice ring; it was a really expensive one, with blue and "
    "green and red and silver. Don't remember what happened to it, though. I "
    "really miss that ring...";

  d_quest_dialogues.emplace( Quest::Type::ArmorOfValor, 2 );
  d_quest_dialogues[Quest::Type::ArmorOfValor][0].dialogue_file_name = "/sfx/towners/drunk06.wav";
  d_quest_dialogues[Quest::Type::ArmorOfValor][0].raw_dialogue_text =
    "Zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz...";
  
  d_quest_dialogues[Quest::Type::ArmorOfValor][1].dialogue_file_name = "/sfx/towners/drunk15.wav";
  d_quest_dialogues[Quest::Type::ArmorOfValor][1].raw_dialogue_text = "...";

  d_quest_dialogues.emplace( Quest::Type::TheChamberOfBone, 1 );
  d_quest_dialogues[Quest::Type::TheChamberOfBone][0].dialogue_file_name = "/sfx/towners/drunk07.wav";
  d_quest_dialogues[Quest::Type::TheChamberOfBone][0].raw_dialogue_text =
    "Okay, so listen. There's this chamber of wood, see. And his wife, you "
    "know - her - tells the tree... cause you gotta wait. Then I says, that "
    "might work against him, but if you think I'm gonna PAY for this... "
    "you... uh... yeah.";

  d_quest_dialogues.emplace( Quest::Type::HallsOfTheBlind, 1 );
  d_quest_dialogues[Quest::Type::HallsOfTheBlind][0].dialogue_file_name = "/sfx/towners/drunk12.wav";
  d_quest_dialogues[Quest::Type::HallsOfTheBlind][0].raw_dialogue_text =
    "Look here... that's pretty funny, huh? Get it? Blind - look here?";

  d_quest_dialogues.emplace( Quest::Type::TheBlackMushroom, 1 );
  d_quest_dialogues[Quest::Type::TheBlackMushroom][0].dialogue_file_name = "/sfx/towners/drunk20.wav";
  d_quest_dialogues[Quest::Type::TheBlackMushroom][0].raw_dialogue_text =
    "Ogden mixes a MEAN black mushroom, but I get sick if I drink that. "
    "Listen, listen... here's the secret - moderation is the key!";

  d_quest_dialogues.emplace( Quest::Type::TheAnvilOfFury, 1 );
  d_quest_dialogues[Quest::Type::TheAnvilOfFury][0].dialogue_file_name = "/sfx/towners/drunk14.wav";
  d_quest_dialogues[Quest::Type::TheAnvilOfFury][0].raw_dialogue_text =
    "Griswold can't sell his anvil. What will he do then? And I'd be angry "
    "too if someone took my anvil!";

  d_quest_dialogues.emplace( Quest::Type::TheWarlordOfBlood, 1 );
  d_quest_dialogues[Quest::Type::TheWarlordOfBlood][0].dialogue_file_name = "/sfx/towners/drunk17.wav";
  d_quest_dialogues[Quest::Type::TheWarlordOfBlood][0].raw_dialogue_text =
    "Always you gotta talk about Blood? What about flowers, and sunshine, and "
    "that pretty girl that brings the drinks. Listen here, friend - you're "
    "obsessive, you know that?";

  d_quest_dialogues.emplace( Quest::Type::Lachdanan, 1 );
  d_quest_dialogues[Quest::Type::Lachdanan][0].dialogue_file_name = "/sfx/towners/drunk13.wav";
  d_quest_dialogues[Quest::Type::Lachdanan][0].raw_dialogue_text =
    "Lachdanan is dead. Everybody knows that, and you can't fool me into "
    "thinking any other way. You can't talk to the dead. I know!";

  d_quest_dialogues.emplace( Quest::Type::ArchbishopLazarus, 1 );
  d_quest_dialogues[Quest::Type::ArchbishopLazarus][0].dialogue_file_name = "/sfx/towners/drunk03.wav";
  d_quest_dialogues[Quest::Type::ArchbishopLazarus][0].raw_dialogue_text =
    "They stab, then bite, then they're all around you. Liar! LIAR! They're "
    "all dead! Dead! Do you hear me? They just keep falling and falling... "
    "their blood spilling out all over the floor... all his fault...";

  // Load the gossip dialogues
  d_gossip_dialogues[0].dialogue_file_name = "/sfx/towners/drunk23.wav";
  d_gossip_dialogues[0].raw_dialogue_text =
    "I wanna tell ya somethin', 'cause I know all about this stuff. It's my "
    "specialty! This here is the best! Theee best! That other ale ain't "
    "no good since those stupid dogs...";
  
  d_gossip_dialogues[1].dialogue_file_name = "/sfx/towners/drunk24.wav";
  d_gossip_dialogues[1].raw_dialogue_text =
    "No one ever lis... listens to me. Somewhere, I ain't too sure, but "
    "somewhere under the church is a whole pile o' gold! Gleamin' and "
    "shinin', just waitin' for someone to get it.";
  
  d_gossip_dialogues[2].dialogue_file_name = "/sfx/towners/drunk25.wav";
  d_gossip_dialogues[2].raw_dialogue_text =
    "I know you got your own ideas, and I know you're not going to believe "
    "this, but that weapon you got there? It just ain't no good against "
    "those big brutes. Oh, I don't care what Griswold says, they can't "
    "make anything like they used to 'n the old days.";
  
  d_gossip_dialogues[3].dialogue_file_name = "/sfx/towners/drunk26.wav";
  d_gossip_dialogues[3].raw_dialogue_text =
    "If I was you - and I ain't, but if I was - I'd sell all that stuff "
    "you got, and get out of here. That boy out there, he's always got "
    "somethin' good, but you gotta give him some gold, or he won't event "
    "show you what he's got.";
  
  d_gossip_dialogues[4].dialogue_file_name = "/sfx/towners/drunk28.wav";
  d_gossip_dialogues[4].raw_dialogue_text =
    "The gal who brings the drinks? Oh, yeah. What a pretty lady. So nice, "
    "too!";
  
  d_gossip_dialogues[5].dialogue_file_name = "/sfx/towners/drunk29.wav";
  d_gossip_dialogues[5].raw_dialogue_text =
    "Why don't that old crone do somethin' for a change? Sure, sure, she's "
    "got stuff, but you listen to me - she's unnatural! I ain't never seen "
    "her eat or drink, and you can't trust somebody who doesn't drink at "
    "least a little.";
  
  d_gossip_dialogues[6].dialogue_file_name = "/sfx/towners/drunk30.wav";
  d_gossip_dialogues[6].raw_dialogue_text =
    "Cain isn't what he says he is. Sure, sure, he talks a good story - some "
    "of 'em are real scary, heheh, or funny - but I think he knows more than "
    "he knows he knows.";
  
  d_gossip_dialogues[7].dialogue_file_name = "/sfx/towners/drunk31.wav";
  d_gossip_dialogues[7].raw_dialogue_text =
    "Griswold? Good ol' Griswold. I love him like a brother! We fought "
    "together, you know, back when... we... Lazarus... Lazarus... "
    "LAZARUS!!!";
  
  d_gossip_dialogues[8].dialogue_file_name = "/sfx/towners/drunk32.wav";
  d_gossip_dialogues[8].raw_dialogue_text =
    "Hehehe, I like Pepin. He really tries, ya know. Listen here, you should "
    "make sure you get to know him. Good fella like that with people "
    "always wantin' help. Hey, I guess that would be kinda like you, huh "
    "hero? I was a hero too, ya know, back when I...";
  
  d_gossip_dialogues[9].dialogue_file_name = "/sfx/towners/drunk34.wav";
  d_gossip_dialogues[9].raw_dialogue_text =
    "Wirt is a kid with more problems than even me, and I know all about "
    "problems. Listen here - that kid is gotta sweet deal, but he's been "
    "there, you know? Lost a leg! Gotta walk around on a piece of wood. "
    "So sad, so sad...";
  
  d_gossip_dialogues[10].dialogue_file_name = "/sfx/towners/drunk35.wav";
  d_gossip_dialogues[10].raw_dialogue_text =
    "Ogden is the best man in town. I don't think his wife likes me much, "
    "but as long as she keeps tappin' kegs, I'll like her just fine. Seems "
    "like I been spendin' more time with Ogden than most, but he's so good "
    "to me...";

  // Load the unused dialogues
  d_unused_dialogues[0].dialogue_file_name = "/sfx/towners/drunk21.wav";
  d_unused_dialogues[0].raw_dialogue_text = "Test";
  
  d_unused_dialogues[1].dialogue_file_name = "/sfx/towners/drunk18.wav";
  d_unused_dialogues[1].raw_dialogue_text = "Test";
  
  d_unused_dialogues[2].dialogue_file_name = "/sfx/towners/drunk05.wav";
  d_unused_dialogues[2].raw_dialogue_text = "Test";
  
  d_unused_dialogues[3].dialogue_file_name = "/sfx/towners/drunk22.wav";
  d_unused_dialogues[3].raw_dialogue_text = "Test";
  
  d_unused_dialogues[4].dialogue_file_name = "/sfx/towners/drunk09.wav";
  d_unused_dialogues[4].raw_dialogue_text = "Test";
  
  d_unused_dialogues[5].dialogue_file_name = "/sfx/towners/drunk08.wav";
  d_unused_dialogues[5].raw_dialogue_text = "Test";
  
  d_unused_dialogues[6].dialogue_file_name = "/sfx/towners/drunk33.wav";
  d_unused_dialogues[6].raw_dialogue_text = "Test";
  
  d_unused_dialogues[7].dialogue_file_name = "/sfx/towners/drunk16.wav";
  d_unused_dialogues[7].raw_dialogue_text = "Test";
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
    this->playAndDisplayDialogue( dialogue_it->second.front() );
}

// Play gossip dialogue
void Farnham::gossip()
{
  static int gossip_index = 0;

  this->playAndDisplayDialogue( d_gossip_dialogues[gossip_index] );
  
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

// Load the interaction menu
NPCInteractionMenu* Farnham::createInteractionMenu( QWidget* parent )
{
  return new FarnhamInteractionMenu( parent );
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Farnham.cpp
//---------------------------------------------------------------------------//
