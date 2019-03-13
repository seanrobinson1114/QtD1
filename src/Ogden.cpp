//---------------------------------------------------------------------------//
//!
//! \file   Ogden.cpp
//! \author Sean Robinson
//! \brief  The Ogden class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "Ogden.h"
#include "OgdenInteractionMenu.h"

namespace QtD1{

// Initialize static member data
QString Ogden::s_image_asset_name = "/towners/twnf/twnfn.cel+levels/towndata/town.pal";

// Constructor
Ogden::Ogden( QGraphicsObject* parent )
  : NPC( parent, false ),
    d_direction_sprites(),
    d_sprites_loaded( false ),
    d_intro(),
    d_greeting(),
    d_quest_dialogues(),
    d_gossip_dialogues( 8 ),
    d_unused_dialogues( 20 )
{
  // Load the intro
  d_intro.dialogue_file_name =  "/sfx/towners/tavown00.wav";
  d_intro.raw_dialogue_text = 
    "Thank goodness you've returned! Much has changed "
    "since you lived here, my friend. All was peaceful "
    "until the dark riders came and destroyed our village. "
    "Many were cut down where they stood, and those who "
    "took up arms were slain or dragged away to become "
    "slaves - or worse. The church at the edge of town "
    "has been desecrated and is being used for dark rituals. "
    "The screams that echo in the night are inhuman, but "
    "some of our townsfolk may yet survive. Follow the path "
    "that lies between my tavern and the blacksmith shop to "
    "find the church and save who you can. Perhaps I can tell "
    "you more if we speak again. Good luck.";

  // Load the greeting
  d_greeting.setSource( "/sfx/towners/tavown36.wav" );

  // Load the quest dialogues

  // Butcher quest
  d_quest_dialogues.emplace( Quest::Type::TheButcher, 1 );
  d_quest_dialogues[Quest::Type::TheButcher][0].dialogue_file_name = "/sfx/towners/tavown08.wav";
  d_quest_dialogues[Quest::Type::TheButcher][0].raw_dialogue_text = 
    "Yes, Farnham has mumbled something about a hulking brute who wielded "
    "a fierce weapon. I believe he called him a butcher.";

  // Poisoned Water Supply quest
  d_quest_dialogues.emplace( Quest::Type::PoisonWater, 1 );
  d_quest_dialogues[Quest::Type::PoisonWater][0].dialogue_file_name = "/sfx/towners/tavown02.wav";
  d_quest_dialogues[Quest::Type::PoisonWater][0].raw_dialogue_text = 
    "I have always tried to keep a large supply of foodstuffs and drink "
    "in our storage cellar, but with the entire town having no source of "
    "fresh water, even our stores will soon run dry. Please, do what you "
    "can or I don't know what we will do.";

  // King Leoric quest
  d_quest_dialogues.emplace( Quest::Type::KingLeoricsCurse, 3 );
  d_quest_dialogues[Quest::Type::KingLeoricsCurse][0].dialogue_file_name = "/sfx/towners/tavown21.wav";
  d_quest_dialogues[Quest::Type::KingLeoricsCurse][0].raw_dialogue_text = 
    "The village needs your help, good master! Some months ago King Leoric's "
    "son, Prince Albrecht, was kidnapped. The King went into a rage and scoured "
    "the village for his missing child. With each passing day, Leoric seemed to "
    "slip deeper into madness. He sought to blame innocent townsfolk for the boy's "
    "disappearance and had them brutally executed. Less than half of us survived his "
    "insanity... The King's Knights and Priests tried to placate him, but he turned "
    "against them and sadly, they were forced to kill him. With his dying breath the "
    "King called down a terrible curse upon his former followers. He vowed that they "
    "would serve him in darkness forever... This is where things take an even darker "
    "twist than I thought possible! Our former King has risen from his eternal sleep "
    "and now commands a legion of undead minions within the Labyrinth. His body was "
    "buried in a tomb three levels beneath the Cathedral. Please, good master, put his "
    "soul at ease by destroying his now cursed form...";
  d_quest_dialogues[Quest::Type::KingLeoricsCurse][1].dialogue_file_name = "/sfx/towners/tavown22.wav";
  d_quest_dialogues[Quest::Type::KingLeoricsCurse][1].raw_dialogue_text = 
    "As I told you, good master, the King was entombed three levels below. He's down "
    "there, waiting in the putrid darkness for his chance to destroy this land...";
  d_quest_dialogues[Quest::Type::KingLeoricsCurse][2].dialogue_file_name = "/sfx/towners/tavown23.wav";
  d_quest_dialogues[Quest::Type::KingLeoricsCurse][2].raw_dialogue_text = 
    "The curse of our King has passed, but I fear that it was only part of a greater "
    "evil at work. However, we may yet be saved from the darkness that consumes our "
    "land, for your victory is a good omen. May Light guide you on your way, good master.";

  // Ogdens Sign quest
  d_quest_dialogues.emplace( Quest::Type::OgdensSign, 2 );
  d_quest_dialogues[Quest::Type::OgdensSign][0].dialogue_file_name = "/sfx/towners/tavown24.wav";
  d_quest_dialogues[Quest::Type::OgdensSign][0].raw_dialogue_text = 
    "Master, I have a strange experience to relate. I know that you have a great knowledge "
    "of those monstrosities that inhabit the labyrinth, and this is something that I cannot "
    "understand for the very life of me... I was awakened during the night by a scraping sound "
    "just outside of my tavern. When I looked out from my bedroom, I saw the shapes of small "
    "demon-like creatures in the inn yard. After a short time, they ran off, but not before "
    "stealing the sign to my inn. I don't know why the demons would steal my sign but leave "
    "my family in peace... 'tis strange, no?";
  d_quest_dialogues[Quest::Type::OgdensSign][1].dialogue_file_name = "/sfx/towners/tavown25.wav";
  d_quest_dialogues[Quest::Type::OgdensSign][1].raw_dialogue_text = 
    "Oh, you didn't have to bring back my sign, but I suppose that it does save me the expense "
    "of having another one made. Well, let me see, what could I give you as a fee for finding it? "
    "Hmmm, what have we here... ah, yes! This cap was left in one of the rooms by a magician who "
    "stayed here some time ago. Perhaps it may be of some value to you.";

  // Magic Rock quest
  d_quest_dialogues.emplace( Quest::Type::TheMagicRock,  1 );
  d_quest_dialogues[Quest::Type::TheMagicRock][0].dialogue_file_name = "/sfx/towners/tavown18.wav";
  d_quest_dialogues[Quest::Type::TheMagicRock][0].raw_dialogue_text = 
    "The caravan stopped here to take on some supplies for "
    "their journey to the east. I sold them quite an array "
    "of fresh fruits and some excellent sweetbreads that "
    "Garda has just finished baking. Shame what happened to them...";

  // Chamber of Bone quest
  d_quest_dialogues.emplace( Quest::Type::TheChamberOfBone, 1 );
  d_quest_dialogues[Quest::Type::TheChamberOfBone][0].dialogue_file_name = "/sfx/towners/tavown05.wav";
  d_quest_dialogues[Quest::Type::TheChamberOfBone][0].raw_dialogue_text = 
    "I am afraid that I don't know anything about that, good "
    "master. Cain has many books that may be of some help.";

  // Halls of the Blind quest
  d_quest_dialogues.emplace( Quest::Type::HallsOfTheBlind, 1 );
  d_quest_dialogues[Quest::Type::HallsOfTheBlind][0].dialogue_file_name = "/sfx/towners/tavown10.wav";
  d_quest_dialogues[Quest::Type::HallsOfTheBlind][0].raw_dialogue_text = 
    "I never much cared for poetry. Occasionally, I had cause to "
    "hire minstrels when the inn was doing well, but that seems "
    "like such a long time ago now. What? Oh, yes... uh, well, I "
    "suppose you could see what someone else knows.";

  // Black mushroom quest
  d_quest_dialogues.emplace( Quest::Type::TheBlackMushroom, 1 );
  d_quest_dialogues[Quest::Type::TheBlackMushroom][0].dialogue_file_name = "/sfx/towners/tavown19.wav";
  d_quest_dialogues[Quest::Type::TheBlackMushroom][0].raw_dialogue_text = 
    "Let me just say this. Both Garda and I would never, EVER "
    "serve black mushrooms to our honored guests. If Adria wants "
    "some mushrooms in her stew, then that is her business, but "
    "I can't help you find any. Black mushrooms... disgusting!";

  // Anvil of Fury quest
  d_quest_dialogues.emplace( Quest::Type::TheAnvilOfFury, 1 );
  d_quest_dialogues[Quest::Type::TheAnvilOfFury][0].dialogue_file_name = "/sfx/towners/tavown12.wav";
  d_quest_dialogues[Quest::Type::TheAnvilOfFury][0].raw_dialogue_text = 
    "Don't you think that Griswold would be a better person to "
    "ask about this? He's quite handy, you know.";

  // Warlord of Blood quest
  d_quest_dialogues.emplace( Quest::Type::TheWarlordOfBlood, 1 );
  d_quest_dialogues[Quest::Type::TheWarlordOfBlood][0].dialogue_file_name = "/sfx/towners/tavown16.wav";
  d_quest_dialogues[Quest::Type::TheWarlordOfBlood][0].raw_dialogue_text = 
    "I am afraid that I haven't heard anything about such a "
    "vicious warrior, good master. I hope that you do not have "
    "to fight him, for he sounds extremely dangerous.";

  // Archbishop Lazarus quest
  d_quest_dialogues.emplace( Quest::Type::ArchbishopLazarus, 1 );
  d_quest_dialogues[Quest::Type::ArchbishopLazarus][0].dialogue_file_name = "/sfx/towners/tavown01.wav";
  d_quest_dialogues[Quest::Type::ArchbishopLazarus][0].raw_dialogue_text = 
    "Lazarus was the Archbishop who led many of the townspeople into the "
    "labyrinth. I lost many good friends that day, and Lazarus never "
    "returned. I suppose he was killed along with most of the others. If you "
    "would do me a favor, good master - please do not talk to Farnham about "
    "that day.";

  // Lachdanan quest
  d_quest_dialogues.emplace( Quest::Type::Lachdanan, 1 );
  d_quest_dialogues[Quest::Type::Lachdanan][0].dialogue_file_name = "/sfx/towners/tavown11.wav";
  d_quest_dialogues[Quest::Type::Lachdanan][0].raw_dialogue_text = 
    "You speak of a brave warrior long dead! I'll have no such "
    "talk of speaking with departed souls in my inn yard, thank "
    "you very much.";

  // Armor of Valor quest
  d_quest_dialogues.emplace( Quest::Type::ArmorOfValor, 1 );
  d_quest_dialogues[Quest::Type::ArmorOfValor][0].dialogue_file_name = "/sfx/towners/tavown13.wav";
  d_quest_dialogues[Quest::Type::ArmorOfValor][0].raw_dialogue_text = 
    "Every child hears the story of the warrior Arkaine and his "
    "mystic armor known as Valor. If you could find its resting "
    "place, you would be well protected against the evil in "
    "the Labyrinth.";

  // Load the gossip dialogues
  d_gossip_dialogues[0].dialogue_file_name = "/sfx/towners/tavown37.wav";
  d_gossip_dialogues[0].raw_dialogue_text =
    "Many adventurers have graced the tables of my tavern, and ten times "
    "as many stories have been told over as much ale. The only thing that "
    "I ever heard any of them agree on was this old axiom. Perhaps it will "
    "help you. You can cut the flesh, but you must crush the bone.";
  
  d_gossip_dialogues[1].dialogue_file_name = "/sfx/towners/tavown38.wav";
  d_gossip_dialogues[1].raw_dialogue_text =
    "Griswold the blacksmith is extremely knowledgeable about weapons and "
    "armor. If you ever need work done on your gear, he is definitely the "
    "man to see.";
  
  d_gossip_dialogues[2].dialogue_file_name = "/sfx/towners/tavown39.wav";
  d_gossip_dialogues[2].raw_dialogue_text =
    "Farnham spends far too much time here, drowning his sorrows in cheap "
    "ale. I would make him leave, but he did suffer so during his time in "
    "the Labyrinth.";
  
  d_gossip_dialogues[3].dialogue_file_name = "/sfx/towners/tavown40.wav";
  d_gossip_dialogues[3].raw_dialogue_text =
    "Adria is wise beyond her years, but I must admit - she frightens me "
    "a little. Well, no matter. If you ever have need to trade in items "
    "of sorcery, she maintains a strangely well-stocked hut just across "
    "the river.";
  
  d_gossip_dialogues[4].dialogue_file_name = "/sfx/towners/tavown41.wav";
  d_gossip_dialogues[4].raw_dialogue_text =
    "If you want to know more about the history of our village, the "
    "storyteller Cain knows quite a bit about the past.";
  
  d_gossip_dialogues[5].dialogue_file_name = "/sfx/towners/tavown43.wav";
  d_gossip_dialogues[5].raw_dialogue_text =
    "Wirt is a rapscallion and a little scoundrel. He was always "
    "getting into trouble, and it's no surprise what happened to "
    "him. He probably went fooling about someplace that he shouldn't "
    "have been. I feel sorry for the boy, but I don't abide the "
    "company that he keeps.";
  
  d_gossip_dialogues[6].dialogue_file_name = "/sfx/towners/tavown44.wav";
  d_gossip_dialogues[6].raw_dialogue_text =
    "Pepin is a good man - and certainly the most generous in the "
    "village. He is always attending to the needs of others, but "
    "trouble of some sort or another does seem to follow him wherever "
    "he goes...";
  
  d_gossip_dialogues[7].dialogue_file_name = "/sfx/towners/tavown45.wav";
  d_gossip_dialogues[7].raw_dialogue_text =
    "Gillian, my Barmaid? If it were not for her sense of duty to her "
    "grand-dam, she would have fled from here long ago. Goodness knows "
    "I begged her to leave, telling her that I would watch after the "
    "old woman, but she is too sweet and caring to have done so.";

  // Load the unused dialogues
  d_unused_dialogues[0].dialogue_file_name = "/sfx/towners/tavown03.wav";
  d_unused_dialogues[0].raw_dialogue_text = "Test";
  
  d_unused_dialogues[1].dialogue_file_name = "/sfx/towners/tavown04.wav";
  d_unused_dialogues[1].raw_dialogue_text = "Test";
  
  d_unused_dialogues[2].dialogue_file_name = "/sfx/towners/tavown06.wav";
  d_unused_dialogues[2].raw_dialogue_text = "Test";
  
  d_unused_dialogues[3].dialogue_file_name = "/sfx/towners/tavown07.wav";
  d_unused_dialogues[3].raw_dialogue_text = "Test";
  
  d_unused_dialogues[4].dialogue_file_name = "/sfx/towners/tavown09.wav";
  d_unused_dialogues[4].raw_dialogue_text = "Test";
  
  d_unused_dialogues[5].dialogue_file_name = "/sfx/towners/tavown14.wav";
  d_unused_dialogues[5].raw_dialogue_text = "Test";
  
  d_unused_dialogues[6].dialogue_file_name = "/sfx/towners/tavown15.wav";
  d_unused_dialogues[6].raw_dialogue_text = "Test";
  
  d_unused_dialogues[7].dialogue_file_name = "/sfx/towners/tavown17.wav";
  d_unused_dialogues[7].raw_dialogue_text = "Test";

  d_unused_dialogues[8].dialogue_file_name = "/sfx/towners/tavown20.wav";
  d_unused_dialogues[8].raw_dialogue_text = "Test";

  d_unused_dialogues[9].dialogue_file_name = "/sfx/towners/tavown26.wav";
  d_unused_dialogues[9].raw_dialogue_text = "Test";

  d_unused_dialogues[10].dialogue_file_name = "/sfx/towners/tavown27.wav";
  d_unused_dialogues[10].raw_dialogue_text = "Test";

  d_unused_dialogues[11].dialogue_file_name = "/sfx/towners/tavown28.wav";
  d_unused_dialogues[11].raw_dialogue_text = "Test";

  d_unused_dialogues[12].dialogue_file_name = "/sfx/towners/tavown29.wav";
  d_unused_dialogues[12].raw_dialogue_text = "Test";

  d_unused_dialogues[13].dialogue_file_name = "/sfx/towners/tavown30.wav";
  d_unused_dialogues[13].raw_dialogue_text = "Test";

  d_unused_dialogues[14].dialogue_file_name = "/sfx/towners/tavown31.wav";
  d_unused_dialogues[14].raw_dialogue_text = "Test";

  d_unused_dialogues[15].dialogue_file_name = "/sfx/towners/tavown32.wav";
  d_unused_dialogues[15].raw_dialogue_text = "Test";
  
  d_unused_dialogues[16].dialogue_file_name = "/sfx/towners/tavown33.wav";
  d_unused_dialogues[16].raw_dialogue_text = "Test";

  d_unused_dialogues[17].dialogue_file_name = "/sfx/towners/tavown34.wav";
  d_unused_dialogues[17].raw_dialogue_text = "Test";

  d_unused_dialogues[18].dialogue_file_name = "/sfx/towners/tavown35.wav";
  d_unused_dialogues[18].raw_dialogue_text = "Test";

  d_unused_dialogues[19].dialogue_file_name = "/sfx/towners/tavown42.wav";
  d_unused_dialogues[19].raw_dialogue_text = "Test";
}

// Get the warrior description
QString Ogden::getDescription() const
{
  return QString( "OGDEN THE THE TAVERN OWNER" );
}

// Get the number of image assets used by the object
int Ogden::getNumberOfImageAssets() const
{
  return 1;
}

// Get the image asset names used by the object
void Ogden::getImageAssetNames( QSet<QString>& image_asset_names ) const
{
  image_asset_names.insert( s_image_asset_name );
}

// Check if an image asset is used
bool Ogden::isImageAssetUsed( const QString& image_asset_name ) const
{
  return image_asset_name == s_image_asset_name;
}

// Check if the image assets have been loaded
bool Ogden::imageAssetsLoaded() const
{
  return d_sprites_loaded;
}

// Load the image asset
void Ogden::loadImageAsset( const QString&,
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
void Ogden::finalizeImageAssetLoading()
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
void Ogden::dumpImageAssets()
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
void Ogden::discussQuest( const Quest::Type quest )
{
  auto dialogue_it = d_quest_dialogues.find( quest );
  
  if( dialogue_it != d_quest_dialogues.end() )
    this->playAndDisplayDialogue( dialogue_it->second.front() );
}

// Play gossip dialogue
void Ogden::gossip()
{
  static int gossip_index = 0;

  this->playAndDisplayDialogue( d_gossip_dialogues[gossip_index] );
  
  gossip_index = (gossip_index+1)%d_gossip_dialogues.size();
}

// Greet the character
void Ogden::greet()
{
  static bool first_encounter = true;

  // Check for first encounter
  if( first_encounter )
  {
    this->playAndDisplayDialogue( d_intro );
    first_encounter = false;
  }
  else
    d_greeting.playSound();
  
}

// Get the movement speed (pixels per game tic)
qreal Ogden::getMovementSpeed() const
{
  return 0.0;
}

// Check if the NPC has dialogue for the requested quest
bool Ogden::hasDialogue( const Quest::Type quest ) const
{
  return d_quest_dialogues.find( quest ) != d_quest_dialogues.end();
}

// Load the interaction menu
NPCInteractionMenu* Ogden::createInteractionMenu( QWidget* parent, Character* )
{
  return new OgdenInteractionMenu( parent );
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Ogden.cpp
//---------------------------------------------------------------------------//
