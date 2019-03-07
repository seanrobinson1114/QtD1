//---------------------------------------------------------------------------//
//!
//! \file   Adria.cpp
//! \author Sean Robinson
//! \brief  The Adria class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "Adria.h"

namespace QtD1{

// Initialize static member data
QString Adria::s_image_asset_name = "/towners/townwmn1/witch.cel+levels/towndata/town.pal";

// Constructor
Adria::Adria( QGraphicsObject* parent )
  : NPC( parent, false ),
    d_direction_sprites(),
    d_sprites_loaded( false ),
    d_greeting(),
    d_quest_dialogues(),
    d_gossip_dialogues( 11 ),
    d_unused_dialogues( 21 )
{
  // Load the greeting
  d_greeting.setSource( "/sfx/towners/witch38.wav" );

  // Load the quest dialogues

  // Butcher quest
  d_quest_dialogues.emplace( Quest::Type::TheButcher, 1 );
  d_quest_dialogues[Quest::Type::TheButcher][0].dialogue_file_name = "/sfx/towners/witch10.wav";
  d_quest_dialogues[Quest::Type::TheButcher][0].raw_dialogue_text = 
    "The Butcher is a sadistic creature that delights "
    "in the torture and pain of others. You have seen his "
    "handiwork in the drunkard Farnham. His destruction "
    "will do much to ensure the safety of this village.";

  // Poisoned Water Supply quest
  d_quest_dialogues.emplace( Quest::Type::PoisonWater, 1 );
  d_quest_dialogues[Quest::Type::PoisonWater][0].dialogue_file_name = "/sfx/towners/witch04.wav";
  d_quest_dialogues[Quest::Type::PoisonWater][0].raw_dialogue_text = 
    "The people of Tristram will die if you cannot "
    "restore fresh water to their wells. Know this - demons are at the heart "
    "of this matter, but they remain ignorant of what they have spawned.";

  // King Leoric quest
  d_quest_dialogues.emplace( Quest::Type::KingLeoricsCurse, 1 );
  d_quest_dialogues[Quest::Type::KingLeoricsCurse][0].dialogue_file_name = "/sfx/towners/witch01.wav";
  d_quest_dialogues[Quest::Type::KingLeoricsCurse][0].raw_dialogue_text = 
    "The dead who walk among the living follow the cursed King. "
    "He holds the power to raise yet more warriors for an ever "
    "growing army of the undead. If you do not stop his reign, "
    "he will surely march across this land and slay all who still "
    "live here.";

  // Ogdens Sign quest
  d_quest_dialogues.emplace( Quest::Type::OgdensSign, 1 );
  d_quest_dialogues[Quest::Type::OgdensSign][0].dialogue_file_name = "/sfx/towners/witch02.wav";
  d_quest_dialogues[Quest::Type::OgdensSign][0].raw_dialogue_text = 
    "No mortal can truly understand the mind of the demon. "
    "Never let their erratic actions confuse you, as that "
    "too may be their plan.";

  // Magic Rock quest
  d_quest_dialogues.emplace( Quest::Type::TheMagicRock,  1 );
  d_quest_dialogues[Quest::Type::TheMagicRock][0].dialogue_file_name = "/sfx/towners/witch20.wav";
  d_quest_dialogues[Quest::Type::TheMagicRock][0].raw_dialogue_text = 
    "The Heaven Stone is very powerful, and were it any but "
    "Griswold who bid you find it, I would prevent it. He will "
    "harness its powers and its use will be for the good of us all.";

  // Chamber of Bone quest
  d_quest_dialogues.emplace( Quest::Type::TheChamberOfBone, 1 );
  d_quest_dialogues[Quest::Type::TheChamberOfBone][0].dialogue_file_name = "/sfx/towners/witch07.wav";
  d_quest_dialogues[Quest::Type::TheChamberOfBone][0].raw_dialogue_text = 
    "You will become an eternal servant of the dark lords should "
    "you perish within this cursed domain. Enter the Chamber of "
    "Bone at your own peril.";

  // Halls of the Blind quest
  d_quest_dialogues.emplace( Quest::Type::HallsOfTheBlind, 1 );
  d_quest_dialogues[Quest::Type::HallsOfTheBlind][0].dialogue_file_name = "/sfx/towners/witch12.wav";
  d_quest_dialogues[Quest::Type::HallsOfTheBlind][0].raw_dialogue_text = 
    "This is a place of great anguish and terror, and so serves "
    "its master well. Tread carefully or you may yourself be "
    "staying much longer than you had anticipated.";

  // Black mushroom quest
  d_quest_dialogues.emplace( Quest::Type::TheBlackMushroom, 5 );
  d_quest_dialogues[Quest::Type::TheBlackMushroom][0].dialogue_file_name = "/sfx/towners/witch22.wav";
  d_quest_dialogues[Quest::Type::TheBlackMushroom][0].raw_dialogue_text = 
    "What do we have here? Interesting, it looks like a book of "
    "reagents. Keep your eyes open for a black mushroom. It "
    "should be fairly large and easy to identify. If you find "
    "it, bring it to me, won't you?";
  d_quest_dialogues[Quest::Type::TheBlackMushroom][1].dialogue_file_name = "/sfx/towners/witch23.wav";
  d_quest_dialogues[Quest::Type::TheBlackMushroom][1].raw_dialogue_text = 
    "It's a big, black mushroom that I need. Now run off and "
    "get it for me so that I can use it for a special concoction "
    "that I am working on.";
  d_quest_dialogues[Quest::Type::TheBlackMushroom][2].dialogue_file_name = "/sfx/towners/witch24.wav";
  d_quest_dialogues[Quest::Type::TheBlackMushroom][2].raw_dialogue_text =
    "Yes, this will be perfect for a brew that I am creating. "
    "By the way, the healer is looking for the brain of some "
    "demon or another so he can treat those who have been afflicted "
    "by their poisonous venom. I believe that he intends to make "
    "an elixir from it. If you help him find what he needs, "
    "please see if you can get a sample of the elixir for me."; 
  d_quest_dialogues[Quest::Type::TheBlackMushroom][3].dialogue_file_name = "/sfx/towners/witch25.wav";
  d_quest_dialogues[Quest::Type::TheBlackMushroom][3].raw_dialogue_text =
    "Why have you brought that here? I have no need for a demon's "
    "brain at this time. I do need some of the elixir that the "
    "Healer is working on. He needs that grotesque organ that "
    "you are holding, and then bring me the elixir. Simple when "
    "you think about it, isn't it?";
  d_quest_dialogues[Quest::Type::TheBlackMushroom][4].dialogue_file_name = "/sfx/towners/witch26.wav";
  d_quest_dialogues[Quest::Type::TheBlackMushroom][4].raw_dialogue_text =
    "What? Now you bring me that elixir from the healer? I was "
    "able to finish my brew without it. Why don't you just keep it...";

  // Anvil of Fury quest
  d_quest_dialogues.emplace( Quest::Type::TheAnvilOfFury, 1 );
  d_quest_dialogues[Quest::Type::TheAnvilOfFury][0].dialogue_file_name = "/sfx/towners/witch14.wav";
  d_quest_dialogues[Quest::Type::TheAnvilOfFury][0].raw_dialogue_text = 
    "There are many artifacts within the Labyrinth that hold powers "
    "beyond the comprehension of mortals. Some of these hold fantastic "
    "power that can be used by either the Light or the Darkness. "
    "Securing the Anvil from below could shift the course of the "
    "Sin War towards the Light.";

  // Warlord of Blood quest
  d_quest_dialogues.emplace( Quest::Type::TheWarlordOfBlood, 1 );
  d_quest_dialogues[Quest::Type::TheWarlordOfBlood][0].dialogue_file_name = "/sfx/towners/witch18.wav";
  d_quest_dialogues[Quest::Type::TheWarlordOfBlood][0].raw_dialogue_text = 
    "His prowess with the blade is awesome, and he has lived for "
    "thousands of years knowing only warfare. I am sorry... I can "
    "not see if you will defeat him.";

  // Archbishop Lazarus quest
  d_quest_dialogues.emplace( Quest::Type::ArchbishopLazarus, 1 );
  d_quest_dialogues[Quest::Type::ArchbishopLazarus][0].dialogue_file_name = "/sfx/towners/witch03.wav";
  d_quest_dialogues[Quest::Type::ArchbishopLazarus][0].raw_dialogue_text = 
    "I did not know this Lazarus of whom you speak, but I do sense "
    "a great conflict within his being. He poses a great danger, "
    "and will stop at nothing to serve the powers of darkness which "
    "have claimed him as theirs.";

  // Lachdanan quest
  d_quest_dialogues.emplace( Quest::Type::Lachdanan, 1 );
  d_quest_dialogues[Quest::Type::Lachdanan][0].dialogue_file_name = "/sfx/towners/witch13.wav";
  d_quest_dialogues[Quest::Type::Lachdanan][0].raw_dialogue_text = 
    "You may meet people who are trapped within the Labyrinth, "
    "such as Lachdanan. I sense in him honor and great guilt. "
    "Aid him, and you aid all of Tristram.";

  // Armor of Valor quest
  d_quest_dialogues.emplace( Quest::Type::ArmorOfValor, 1 );
  d_quest_dialogues[Quest::Type::ArmorOfValor][0].dialogue_file_name = "/sfx/towners/witch15.wav";
  d_quest_dialogues[Quest::Type::ArmorOfValor][0].raw_dialogue_text = 
    "Should you find these Stones of Blood, use them carefully. "
    "The way is fraught with danger and your only hope rests "
    "within your self trust.";

  // Load the gossip dialogues
  d_gossip_dialogues[0].dialogue_file_name = "/sfx/towners/witch39.wav";
  d_gossip_dialogues[0].raw_dialogue_text =
    "Wisdom is earned, not given. If you discover a tome of knowledge, "
    "devour its words. Should you already have knowledge of the racane "
    "mysteries scribed whithin a book, remember - that level of mastery "
    "can always be increased.";
  
  d_gossip_dialogues[1].dialogue_file_name = "/sfx/towners/witch40.wav";
  d_gossip_dialogues[1].raw_dialogue_text =
    "The greatest power is often the shortest lived. You may find ancient "
    "words of power written upon scrolls of parchment. The strength of "
    "these scrolls lies in the ability of either apprentice or adept to "
    "cast them with equal ability. Their weakness is that they must first "
    "be read aloud and can never be kept at the ready in your mind. Know "
    "also that these scrolls can be read but once, so use them with care.";
  
  d_gossip_dialogues[2].dialogue_file_name = "/sfx/towners/witch41.wav";
  d_gossip_dialogues[2].raw_dialogue_text =
    "Though the heat of the sun is beyond measure, the mere flame of a candle "
    "is of greater danger. No energies, no matter how great, can be used without "
    "the proper focus. For many spells, ensorcelled Staves may be charged with "
    "magical energies many times over. I have the ability to restore their "
    "power - but know that nothing is done without a price.";
  
  d_gossip_dialogues[3].dialogue_file_name = "/sfx/towners/witch42.wav";
  d_gossip_dialogues[3].raw_dialogue_text =
    "The sum of our knowledge is in the sum of its people. Should you find a book "
    "or scroll that you cannot decipher, do not hesitate to bring it to me. If I "
    "can make sense of it I will share what I find.";
  
  d_gossip_dialogues[4].dialogue_file_name = "/sfx/towners/witch43.wav";
  d_gossip_dialogues[4].raw_dialogue_text =
    "To a man who only knows Iron, there is no greater magic than Steel. "
    "The blacksmith Griswold is more of a sorcerer than he knows. His "
    "ability to meld fire and metal is unequaled in this land.";
  
  d_gossip_dialogues[5].dialogue_file_name = "/sfx/towners/witch44.wav";
  d_gossip_dialogues[5].raw_dialogue_text =
    "Corruption has the strength of deceit, but innocence holds the power "
    "of purity. The young woman Gillian has a pure heart, placing the "
    "needs of her matriarch over her own. She fears me, but it is only "
    "because she does not understand me.";
  
  d_gossip_dialogues[6].dialogue_file_name = "/sfx/towners/witch45.wav";
  d_gossip_dialogues[6].raw_dialogue_text =
    "A chest opened in darkness holds no greater treasure than when it "
    "is opened in the light. The storyteller Cain is an enigma, but only "
    "to those who do not look. His knowledge of what lies beneath the "
    "cathedral is far greater than even he allows himself to realize.";
  
  d_gossip_dialogues[7].dialogue_file_name = "/sfx/towners/witch46.wav";
  d_gossip_dialogues[7].raw_dialogue_text =
    "The higher you place your faith in one man, the farther it has to fall. "
    "Farnham has lost his soul, but not to any demon. It was lost when he "
    "saw his fellow townspeople betrayed by the Archbishop Lazarus. He has "
    "knowledge to be gleaned, but you must separate fact from fantasy.";
  
  d_gossip_dialogues[8].dialogue_file_name = "/sfx/towners/witch47.wav";
  d_gossip_dialogues[8].raw_dialogue_text =
    "The hand, the heart and the mind can perform miracles when they are in "
    "perfect harmony. The healer Pepin sees into the body in a way that even "
    "I cannot. His ability to restore the sick and injured is magnified by "
    "his understanding of the creation of elixirs and potions. He is as great "
    "an ally as you have in Tristram.";
  
  d_gossip_dialogues[9].dialogue_file_name = "/sfx/towners/witch49.wav";
  d_gossip_dialogues[9].raw_dialogue_text =
    "There is much about the future we cannot see, but when it comes it will "
    "be the children who wield it. The boy Wirt has a blackness upon his soul, "
    "but he poses no threat to the town or its people. His secretive dealings "
    "with the urchins and unspoken guilds of nearby towns gain him access to "
    "many devices that cannot be easily found in Tristram. While his methods "
    "may be reproachful, Wirt can provide assistance for your battle against "
    "the encroaching Darkness.";
  
  d_gossip_dialogues[10].dialogue_file_name = "/sfx/towners/witch50.wav";
  d_gossip_dialogues[10].raw_dialogue_text =
    "Earthen walls and thatched canopy do not a home create. The innkeeper Ogden "
    "serves more of a purpose in this town than many understand. He provides "
    "shelter for Gillian and her matriarch, maintains what life Farnham has left "
    "to him, and provides an anchor for all who are left in the town to what "
    "Tristram once was. His tavern, and the simple pleasures that can still be "
    "found there, provide a glimpse of a life that the people here remember. It "
    "is that memory that continues to feed their hopes for your success.";

  // Load the unused dialogues
  d_unused_dialogues[0].dialogue_file_name = "/sfx/towners/witch05.wav";
  d_unused_dialogues[0].raw_dialogue_text = "Test";
  
  d_unused_dialogues[1].dialogue_file_name = "/sfx/towners/witch06.wav";
  d_unused_dialogues[1].raw_dialogue_text = "Test";
  
  d_unused_dialogues[2].dialogue_file_name = "/sfx/towners/witch08.wav";
  d_unused_dialogues[2].raw_dialogue_text = "Test";
  
  d_unused_dialogues[3].dialogue_file_name = "/sfx/towners/witch09.wav";
  d_unused_dialogues[3].raw_dialogue_text = "Test";
  
  d_unused_dialogues[4].dialogue_file_name = "/sfx/towners/witch11.wav";
  d_unused_dialogues[4].raw_dialogue_text = "Test";
  
  d_unused_dialogues[5].dialogue_file_name = "/sfx/towners/witch16.wav";
  d_unused_dialogues[5].raw_dialogue_text = "Test";
  
  d_unused_dialogues[6].dialogue_file_name = "/sfx/towners/witch17.wav";
  d_unused_dialogues[6].raw_dialogue_text = "Test";
  
  d_unused_dialogues[7].dialogue_file_name = "/sfx/towners/witch19.wav";
  d_unused_dialogues[7].raw_dialogue_text = "Test";

  d_unused_dialogues[8].dialogue_file_name = "/sfx/towners/witch21.wav";
  d_unused_dialogues[8].raw_dialogue_text = "Test";

  d_unused_dialogues[9].dialogue_file_name = "/sfx/towners/witch27.wav";
  d_unused_dialogues[9].raw_dialogue_text = "Test";

  d_unused_dialogues[10].dialogue_file_name = "/sfx/towners/witch28.wav";
  d_unused_dialogues[10].raw_dialogue_text = "Test";

  d_unused_dialogues[11].dialogue_file_name = "/sfx/towners/witch29.wav";
  d_unused_dialogues[11].raw_dialogue_text = "Test";

  d_unused_dialogues[12].dialogue_file_name = "/sfx/towners/witch30.wav";
  d_unused_dialogues[12].raw_dialogue_text = "Test";

  d_unused_dialogues[13].dialogue_file_name = "/sfx/towners/witch31.wav";
  d_unused_dialogues[13].raw_dialogue_text = "Test";

  d_unused_dialogues[14].dialogue_file_name = "/sfx/towners/witch32.wav";
  d_unused_dialogues[14].raw_dialogue_text = "Test";

  d_unused_dialogues[15].dialogue_file_name = "/sfx/towners/witch33.wav";
  d_unused_dialogues[15].raw_dialogue_text = "Test";
  
  d_unused_dialogues[16].dialogue_file_name = "/sfx/towners/witch34.wav";
  d_unused_dialogues[16].raw_dialogue_text = "Test";

  d_unused_dialogues[17].dialogue_file_name = "/sfx/towners/witch35.wav";
  d_unused_dialogues[17].raw_dialogue_text = "Test";

  d_unused_dialogues[18].dialogue_file_name = "/sfx/towners/witch36.wav";
  d_unused_dialogues[18].raw_dialogue_text = "Test";

  d_unused_dialogues[19].dialogue_file_name = "/sfx/towners/witch37.wav";
  d_unused_dialogues[19].raw_dialogue_text = "Test";

  d_unused_dialogues[20].dialogue_file_name = "/sfx/towners/witch48.wav";
  d_unused_dialogues[20].raw_dialogue_text = "Test";
}

// Get the warrior description
QString Adria::getDescription() const
{
  return QString( "ADRIA THE WITCH" );
}

// Get the number of image assets used by the object
int Adria::getNumberOfImageAssets() const
{
  return 1;
}

// Get the image asset names used by the object
void Adria::getImageAssetNames( QSet<QString>& image_asset_names ) const
{
  image_asset_names.insert( s_image_asset_name );
}

// Check if an image asset is used
bool Adria::isImageAssetUsed( const QString& image_asset_name ) const
{
  return image_asset_name == s_image_asset_name;
}

// Check if the image assets have been loaded
bool Adria::imageAssetsLoaded() const
{
  return d_sprites_loaded;
}

// Load the image asset
void Adria::loadImageAsset( const QString&,
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
  game_sprite.setFrameDuration( 15 );
}

// Finalize image asset loading
void Adria::finalizeImageAssetLoading()
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
void Adria::dumpImageAssets()
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
void Adria::discussQuest( const Quest::Type quest )
{
  auto dialogue_it = d_quest_dialogues.find( quest );
  
  if( dialogue_it != d_quest_dialogues.end() )
    this->playAndDisplayDialogue( dialogue_it->second.front() );
}

// Play gossip dialogue
void Adria::gossip()
{
  static int gossip_index = 0;

  this->playAndDisplayDialogue( d_gossip_dialogues[gossip_index] );
  
  gossip_index = (gossip_index+1)%d_gossip_dialogues.size();
}

// Greet the character
void Adria::greet()
{
  d_greeting.playSound();
}

// Get the movement speed (pixels per game tic)
qreal Adria::getMovementSpeed() const
{
  return 0.0;
}

// Check if the NPC has dialogue for the requested quest
bool Adria::hasDialogue( const Quest::Type quest ) const
{
  return d_quest_dialogues.find( quest ) != d_quest_dialogues.end();
}

// Get the NPC name (used in interaction menu)
QString Adria::getName() const
{
  return "Adria";
}

// Get the NPC title (used in interaction menu)
QString Adria::getMenuTitle() const
{
  return "Witch's Shack";
}

// Get the NPC fairwell (used in interaction menu)
QString Adria::getMenuFairwell() const
{
  return "Leave The Shack";
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Adria.cpp
//---------------------------------------------------------------------------//
