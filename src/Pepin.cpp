//---------------------------------------------------------------------------//
//!
//! \file   Pepin.cpp
//! \author Sean Robinson
//! \brief  The Pepin class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "Pepin.h"
#include "PepinInteractionMenu.h"

namespace QtD1{

// Initialize static member data
QString Pepin::s_image_asset_name = "/towners/healer/healer.cel+levels/towndata/town.pal";

// Constructor
Pepin::Pepin( QGraphicsObject* parent )
  : NPC( parent, false ),
    d_direction_sprites(),
    d_sprites_loaded( false ),
    d_greeting(),
    d_quest_dialogues(),
    d_gossip_dialogues( 9 ),
    d_unused_dialogues( 21 )
{
  // Load the greeting
  d_greeting.setSource( "/sfx/towners/healer37.wav" );

  // Load the quest dialogues

  // Butcher quest
  d_quest_dialogues.emplace( Quest::Type::TheButcher, 1 );
  d_quest_dialogues[Quest::Type::TheButcher][0].dialogue_file_name = "/sfx/towners/healer08.wav";
  d_quest_dialogues[Quest::Type::TheButcher][0].raw_dialogue_text = 
    "By the Light, I know of this vile demon. There were many that bore "
    "the scars of his wrath upon their bodies when the few survivors of "
    "the charge led by Lazarus crawled from the Cathedral. I don't know "
    "what he used to slice open his victims, but it could not have been "
    "of this world. It left wounds festering with disease and even I found "
    "them almost impossible to treat. Beware if you plan to battle this fiend...";

  // Poisoned Water Supply quest
  d_quest_dialogues.emplace( Quest::Type::PoisonWater, 3 );
  d_quest_dialogues[Quest::Type::PoisonWater][0].dialogue_file_name = "/sfx/towners/healer20.wav";
  d_quest_dialogues[Quest::Type::PoisonWater][0].raw_dialogue_text = 
    "I'm glad I caught up to you in time! Our wells have become brackish "
    "and stagnant and some of the townspeople have become ill drinking "
    "from them. Our reserves of fresh water are quickly running dry. I "
    "believe that there is a passage that leads to the springs that serve "
    "our town. Please find what has caused this calamity, or we all will "
    "surely perish.";
  d_quest_dialogues[Quest::Type::PoisonWater][1].dialogue_file_name = "/sfx/towners/healer21.wav";
  d_quest_dialogues[Quest::Type::PoisonWater][1].raw_dialogue_text = 
    "Please, you must hurry. Every hour that passes brings us closer to "
    "having no water to drink.";
  d_quest_dialogues[Quest::Type::PoisonWater][2].dialogue_file_name = "/sfx/towners/healer22.wav";
  d_quest_dialogues[Quest::Type::PoisonWater][2].raw_dialogue_text = 
    "What's that you say - the mere presence of the demons had caused "
    "the water to become tainted? Oh, truly a great evil lurks beneath "
    "our town, but your perseverance and courage gives us hope. Please "
    "take this ring - perhaps it will aid you in the destruction of such "
    "vile creatures.";

  // King Leoric quest
  d_quest_dialogues.emplace( Quest::Type::KingLeoricsCurse, 1 );
  d_quest_dialogues[Quest::Type::KingLeoricsCurse][0].dialogue_file_name = "/sfx/towners/healer01.wav";
  d_quest_dialogues[Quest::Type::KingLeoricsCurse][0].raw_dialogue_text = 
    "The loss of his son was too much for King Leoric. I did what I could "
    "to ease his madness, but in the end it overcame him. A black curse has "
    "hung over this kingdom from that day forward, but perhaps if you were "
    "to free his spirit from his earthly prison, the curse would be lifted...";

  // Ogdens Sign quest
  d_quest_dialogues.emplace( Quest::Type::OgdensSign, 1 );
  d_quest_dialogues[Quest::Type::OgdensSign][0].dialogue_file_name = "/sfx/towners/healer02.wav";
  d_quest_dialogues[Quest::Type::OgdensSign][0].raw_dialogue_text = 
    "My goodness, demons running about the village at night, pillaging "
    "our homes - is nothing sacred? I hope that Ogden and Garda are all "
    "right. I suppose that they would come to see me if they were hurt...";

  // Magic Rock quest
  d_quest_dialogues.emplace( Quest::Type::TheMagicRock,  1 );
  d_quest_dialogues[Quest::Type::TheMagicRock][0].dialogue_file_name = "/sfx/towners/healer18.wav";
  d_quest_dialogues[Quest::Type::TheMagicRock][0].raw_dialogue_text = 
    "I don't know what it is that they thought they could see with "
    "that rock, but I will say this. If rocks are falling from the "
    "sky, you had better be careful!";

  // Chamber of Bone quest
  d_quest_dialogues.emplace( Quest::Type::TheChamberOfBone, 1 );
  d_quest_dialogues[Quest::Type::TheChamberOfBone][0].dialogue_file_name = "/sfx/towners/healer05.wav";
  d_quest_dialogues[Quest::Type::TheChamberOfBone][0].raw_dialogue_text = 
    "This sounds like a very dangerous place. If you venture "
    "there, please take great care.";

  // Halls of the Blind quest
  d_quest_dialogues.emplace( Quest::Type::HallsOfTheBlind, 1 );
  d_quest_dialogues[Quest::Type::HallsOfTheBlind][0].dialogue_file_name = "/sfx/towners/healer10.wav";
  d_quest_dialogues[Quest::Type::HallsOfTheBlind][0].raw_dialogue_text = 
    "This does seem familiar, somehow. I seem to recall reading "
    "something very much like that poem while researching the "
    "history of demonic afflictions. It spoke of a place of great "
    "evil that... wait - you're not going there are you?";

  // Black mushroom quest
  d_quest_dialogues.emplace( Quest::Type::TheBlackMushroom, 2 );
  d_quest_dialogues[Quest::Type::TheBlackMushroom][0].dialogue_file_name = "/sfx/towners/healer26.wav";
  d_quest_dialogues[Quest::Type::TheBlackMushroom][0].raw_dialogue_text = 
    "The witch told me that you were searching for the brain of a "
    "demon to assist me in creating my elixir. It should be of great "
    "value to the many who are injured by those foul beasts, if I can "
    "just unlock the secrets I suspect that its alchemy holds. If you "
    "can remove the brain of a demon when you kill it, I would be "
    "grateful if you could bring it to me.";
  d_quest_dialogues[Quest::Type::TheBlackMushroom][0].dialogue_file_name = "/sfx/towners/healer27.wav";
  d_quest_dialogues[Quest::Type::TheBlackMushroom][0].raw_dialogue_text = 
    "Excellent, this is just what I had in mind. I was able to finish "
    "the elixir without this, but it can't hurt to have this to study. "
    "Would you please carry this to the witch? I believe that she is "
    "expecting it.";

  // Anvil of Fury quest
  d_quest_dialogues.emplace( Quest::Type::TheAnvilOfFury, 1 );
  d_quest_dialogues[Quest::Type::TheAnvilOfFury][0].dialogue_file_name = "/sfx/towners/healer12.wav";
  d_quest_dialogues[Quest::Type::TheAnvilOfFury][0].raw_dialogue_text = 
    "If you had been looking for information on the Pestle of "
    "Curing or the Silver Chalice of Purification, I could have "
    "assisted you, my friend. However, in this matter, you would "
    "be better served to speak to either Griswold or Cain.";

  // Warlord of Blood quest
  d_quest_dialogues.emplace( Quest::Type::TheWarlordOfBlood, 1 );
  d_quest_dialogues[Quest::Type::TheWarlordOfBlood][0].dialogue_file_name = "/sfx/towners/healer16.wav";
  d_quest_dialogues[Quest::Type::TheWarlordOfBlood][0].raw_dialogue_text = 
    "Cain would be able to tell you much more about something like this than I would ever wish to know.";

  // Archbishop Lazarus quest
  d_quest_dialogues.emplace( Quest::Type::ArchbishopLazarus, 1 );
  d_quest_dialogues[Quest::Type::ArchbishopLazarus][0].dialogue_file_name = "/sfx/towners/healer03.wav";
  d_quest_dialogues[Quest::Type::ArchbishopLazarus][0].raw_dialogue_text = 
    "I was shocked when I heard of what the townspeople were planning "
    "to do that night. I thought that of all people, Lazarus would have "
    "had more sense than that. He was an Archbishop, and always seemed "
    "to care so much for the townsfolk of Tristram. So many were injured, "
    "I could not save them all...";

  // Lachdanan quest
  d_quest_dialogues.emplace( Quest::Type::Lachdanan, 1 );
  d_quest_dialogues[Quest::Type::Lachdanan][0].dialogue_file_name = "/sfx/towners/healer11.wav";
  d_quest_dialogues[Quest::Type::Lachdanan][0].raw_dialogue_text = 
    "A golden elixir, you say. I have never concocted a potion "
    "of that color before, so I can't tell you how it would effect "
    "you if you were to try to drink it. As your healer, I strongly "
    "advise that should you find such an elixir, do as Lachdanan "
    "asks and DO NOT try to use it.";

  // Armor of Valor quest
  d_quest_dialogues.emplace( Quest::Type::ArmorOfValor, 1 );
  d_quest_dialogues[Quest::Type::ArmorOfValor][0].dialogue_file_name = "/sfx/towners/healer13.wav";
  d_quest_dialogues[Quest::Type::ArmorOfValor][0].raw_dialogue_text = 
    "Hmm... it sounds like something I should remember, but I've "
    "been so busy learning new cures and creating better elixirs "
    "that I must have forgotten. Sorry...";

  // Load the gossip dialogues
  d_gossip_dialogues[0].dialogue_file_name = "/sfx/towners/healer38.wav";
  d_gossip_dialogues[0].raw_dialogue_text =
    "I have made a very interesting discovery. Unlike us, the creatures "
    "in the Labyrinth can heal themselves without the aid of potions or "
    "magic. If you hurt one of the monsters, make sure it is dead or it "
    "very well may regenerate itself.";
  
  d_gossip_dialogues[1].dialogue_file_name = "/sfx/towners/healer39.wav";
  d_gossip_dialogues[1].raw_dialogue_text =
    "Before it was taken over by, well, whatever lurks below, the Cathedral "
    "was a place of great learning. There are many books to be found there. "
    "If you find any, you should read them all, for some may hold secrets "
    "to the workings of the Labyrinth.";
  
  d_gossip_dialogues[2].dialogue_file_name = "/sfx/towners/healer40.wav";
  d_gossip_dialogues[2].raw_dialogue_text =
    "Griswold knows as much about the art of war as I do about the art of "
    "healing. He is a shrewd merchant, but his work is second to none. Oh, "
    "I suppose that may be because he is the only blacksmith left here.";
  
  d_gossip_dialogues[3].dialogue_file_name = "/sfx/towners/healer41.wav";
  d_gossip_dialogues[3].raw_dialogue_text =
    "Cain is a true friend and a wise sage. He maintains a vast library "
    "and has an innate ability to discern the true nature of many things. "
    "If you ever have any questions, he is the person to go to.";
  
  d_gossip_dialogues[4].dialogue_file_name = "/sfx/towners/healer42.wav";
  d_gossip_dialogues[4].raw_dialogue_text =
    "Even my skills have been unable to fully heal Farnham. Oh, I have been "
    "able to mend his body, but his mind and spirit are beyond anything I can do.";
  
  d_gossip_dialogues[5].dialogue_file_name = "/sfx/towners/healer43.wav";
  d_gossip_dialogues[5].raw_dialogue_text =
    "While I use some limited forms of magic to create the potions and elixirs "
    "I store here, Adria is a true sorceress. She never seems to sleep, and "
    "she always has access to many mystic tomes and artifacts. I believe her "
    "hut may be much more than the hovel it appears to be, but I can never "
    "seem to get inside the place.";
  
  d_gossip_dialogues[6].dialogue_file_name = "/sfx/towners/healer45.wav";
  d_gossip_dialogues[6].raw_dialogue_text =
    "Poor Wirt. I did all that was possible for the child, but I know he "
    "despises that wooden peg that I was forced to attach to his leg. His "
    "wounds were hideous. No one - and especially such a young child - should "
    "have to suffer the way he did.";
  
  d_gossip_dialogues[7].dialogue_file_name = "/sfx/towners/healer46.wav";
  d_gossip_dialogues[7].raw_dialogue_text =
    "I really don't understand why Ogden stays here in Tristram. He suffers "
    "from a slight nervous condition, but he is an intelligent and industrious "
    "man who would do very well wherever he went. I suppose it may be the fear "
    "of the many murders that happen in the surrounding countryside, or perhaps "
    "the wishes of his wife that keep him and his family where they are.";

  d_gossip_dialogues[8].dialogue_file_name = "/sfx/towners/healer47.wav";
  d_gossip_dialogues[8].raw_dialogue_text =
    "Ogden's barmaid is a sweet girl. Her grandmother is quite ill, and suffers "
    "from delusions. She claims that they are visions, but I have no proof of "
    "that one way or the other.";

  // Load the unused dialogues
  d_unused_dialogues[0].dialogue_file_name = "/sfx/towners/healer04.wav";
  d_unused_dialogues[0].raw_dialogue_text = "Test";
  
  d_unused_dialogues[1].dialogue_file_name = "/sfx/towners/healer06.wav";
  d_unused_dialogues[1].raw_dialogue_text = "Test";
  
  d_unused_dialogues[2].dialogue_file_name = "/sfx/towners/healer07.wav";
  d_unused_dialogues[2].raw_dialogue_text = "Test";
  
  d_unused_dialogues[3].dialogue_file_name = "/sfx/towners/healer09.wav";
  d_unused_dialogues[3].raw_dialogue_text = "Test";
  
  d_unused_dialogues[4].dialogue_file_name = "/sfx/towners/healer14.wav";
  d_unused_dialogues[4].raw_dialogue_text = "Test";
  
  d_unused_dialogues[5].dialogue_file_name = "/sfx/towners/healer15.wav";
  d_unused_dialogues[5].raw_dialogue_text = "Test";
  
  d_unused_dialogues[6].dialogue_file_name = "/sfx/towners/healer17.wav";
  d_unused_dialogues[6].raw_dialogue_text = "Test";
  
  d_unused_dialogues[7].dialogue_file_name = "/sfx/towners/healer19.wav";
  d_unused_dialogues[7].raw_dialogue_text = "Test";

  d_unused_dialogues[8].dialogue_file_name = "/sfx/towners/healer23.wav";
  d_unused_dialogues[8].raw_dialogue_text = "Test";

  d_unused_dialogues[9].dialogue_file_name = "/sfx/towners/healer24.wav";
  d_unused_dialogues[9].raw_dialogue_text = "Test";

  d_unused_dialogues[10].dialogue_file_name = "/sfx/towners/healer25.wav";
  d_unused_dialogues[10].raw_dialogue_text = "Test";

  d_unused_dialogues[11].dialogue_file_name = "/sfx/towners/healer28.wav";
  d_unused_dialogues[11].raw_dialogue_text = "Test";

  d_unused_dialogues[12].dialogue_file_name = "/sfx/towners/healer29.wav";
  d_unused_dialogues[12].raw_dialogue_text = "Test";

  d_unused_dialogues[13].dialogue_file_name = "/sfx/towners/healer30.wav";
  d_unused_dialogues[13].raw_dialogue_text = "Test";

  d_unused_dialogues[14].dialogue_file_name = "/sfx/towners/healer31.wav";
  d_unused_dialogues[14].raw_dialogue_text = "Test";

  d_unused_dialogues[15].dialogue_file_name = "/sfx/towners/healer32.wav";
  d_unused_dialogues[15].raw_dialogue_text = "Test";
  
  d_unused_dialogues[16].dialogue_file_name = "/sfx/towners/healer33.wav";
  d_unused_dialogues[16].raw_dialogue_text = "Test";

  d_unused_dialogues[17].dialogue_file_name = "/sfx/towners/healer34.wav";
  d_unused_dialogues[17].raw_dialogue_text = "Test";

  d_unused_dialogues[18].dialogue_file_name = "/sfx/towners/healer35.wav";
  d_unused_dialogues[18].raw_dialogue_text = "Test";

  d_unused_dialogues[19].dialogue_file_name = "/sfx/towners/healer36.wav";
  d_unused_dialogues[19].raw_dialogue_text = "Test";

  d_unused_dialogues[20].dialogue_file_name = "/sfx/towners/healer44.wav";
  d_unused_dialogues[20].raw_dialogue_text = "Test";
}

// Get the warrior description
QString Pepin::getDescription() const
{
  return QString( "PEPIN THE HEALER" );
}

// Get the number of image assets used by the object
int Pepin::getNumberOfImageAssets() const
{
  return 1;
}

// Get the image asset names used by the object
void Pepin::getImageAssetNames( QSet<QString>& image_asset_names ) const
{
  image_asset_names.insert( s_image_asset_name );
}

// Check if an image asset is used
bool Pepin::isImageAssetUsed( const QString& image_asset_name ) const
{
  return image_asset_name == s_image_asset_name;
}

// Check if the image assets have been loaded
bool Pepin::imageAssetsLoaded() const
{
  return d_sprites_loaded;
}

// Load the image asset
void Pepin::loadImageAsset( const QString&,
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
    QVector<int> source_frame_indices( 16 );

    for( int i = 0; i < source_frame_indices.size(); ++i )
      source_frame_indices[i] = i;

    game_sprite = GameSprite( s_image_asset_name, source_frame_indices );
  }

  game_sprite.setAsset( s_image_asset_name, image_asset_frames );
  game_sprite.setFrameDuration( 15 );
}

// Finalize image asset loading
void Pepin::finalizeImageAssetLoading()
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
void Pepin::dumpImageAssets()
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
void Pepin::discussQuest( const Quest::Type quest )
{
  auto dialogue_it = d_quest_dialogues.find( quest );
  
  if( dialogue_it != d_quest_dialogues.end() )
    this->playAndDisplayDialogue( dialogue_it->second.front() );
}

// Play gossip dialogue
void Pepin::gossip()
{
  static int gossip_index = 0;

  this->playAndDisplayDialogue( d_gossip_dialogues[gossip_index] );
  
  gossip_index = (gossip_index+1)%d_gossip_dialogues.size();
}

// Greet the character
void Pepin::greet()
{
  d_greeting.playSound();
}

// Get the movement speed (pixels per game tic)
qreal Pepin::getMovementSpeed() const
{
  return 0.0;
}

// Check if the NPC has dialogue for the requested quest
bool Pepin::hasDialogue( const Quest::Type quest ) const
{
  return d_quest_dialogues.find( quest ) != d_quest_dialogues.end();
}

// Load the interaction menu
NPCInteractionMenu* Pepin::createInteractionMenu( QWidget* parent, Character* character )
{
  return new PepinInteractionMenu( character, parent );
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Pepin.cpp
//---------------------------------------------------------------------------//
