//---------------------------------------------------------------------------//
//!
//! \file   Wirt.cpp
//! \author Sean Robinson
//! \brief  The Wirt class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "Wirt.h"
#include "WirtInteractionMenu.h"

namespace QtD1{

// Initialize static member data
QString Wirt::s_image_asset_name = "/towners/townboy/pegkid1.cel+levels/towndata/town.pal";

// Constructor
Wirt::Wirt( QGraphicsObject* parent )
  : NPC( parent, false ),
    d_direction_sprites(),
    d_sprites_loaded( false ),
    d_greeting(),
    d_quest_dialogues(),
    d_gossip_dialogues( 10 ),
    d_unused_dialogues( 19 )
{
  // Load the greeting
  d_greeting.setSource( "/sfx/towners/pegboy32.wav" );

  // Load the quest dialogues

  // Butcher quest
  d_quest_dialogues.emplace( Quest::Type::TheButcher, 1 );
  d_quest_dialogues[Quest::Type::TheButcher][0].dialogue_file_name = "/sfx/towners/pegboy10.wav";
  d_quest_dialogues[Quest::Type::TheButcher][0].raw_dialogue_text = 
    "I know more than you'd think about that grisly fiend. His little "
    "friends got a hold of me and managed to get my leg before Griswold "
    "pulled me out of that hole. I'll put it bluntly - kill him before "
    "he kills you and adds your corpse to his collection.";

  // Poisoned Water Supply quest
  d_quest_dialogues.emplace( Quest::Type::PoisonWater, 1 );
  d_quest_dialogues[Quest::Type::PoisonWater][0].dialogue_file_name = "/sfx/towners/pegboy04.wav";
  d_quest_dialogues[Quest::Type::PoisonWater][0].raw_dialogue_text = 
    "For once, I'm with you. My business runs dry - so to speak - if "
    "I have no market to sell to. You better find out what is going "
    "on, and soon!";

  // King Leoric quest
  d_quest_dialogues.emplace( Quest::Type::KingLeoricsCurse, 1 );
  d_quest_dialogues[Quest::Type::KingLeoricsCurse][0].dialogue_file_name = "/sfx/towners/pegboy01.wav";
  d_quest_dialogues[Quest::Type::KingLeoricsCurse][0].raw_dialogue_text = 
    "Look, I'm running a business here. I don't sell information, and "
    "I don't care about some King that's been dead longer than I've "
    "been alive. If you need something to use against this King of the "
    "undead, then I can help you out...";

  // Ogdens Sign quest
  d_quest_dialogues.emplace( Quest::Type::OgdensSign, 1 );
  d_quest_dialogues[Quest::Type::OgdensSign][0].dialogue_file_name = "/sfx/towners/pegboy02.wav";
  d_quest_dialogues[Quest::Type::OgdensSign][0].raw_dialogue_text = 
    "What - is he saying I took that? I suppose that Griswold is on "
    "his side, too. Look, I got over simple sign stealing months ago. "
    "You can't turn a profit on a piece of wood.";

  // Magic Rock quest
  d_quest_dialogues.emplace( Quest::Type::TheMagicRock,  1 );
  d_quest_dialogues[Quest::Type::TheMagicRock][0].dialogue_file_name = "/sfx/towners/pegboy18.wav";
  d_quest_dialogues[Quest::Type::TheMagicRock][0].raw_dialogue_text = 
    "If anyone can make something out of that rock, Griswold can. He "
    "knows what he is doing, and as much as I try to steal his customers, "
    "I respect the quality of his work.";

  // Chamber of Bone quest
  d_quest_dialogues.emplace( Quest::Type::TheChamberOfBone, 1 );
  d_quest_dialogues[Quest::Type::TheChamberOfBone][0].dialogue_file_name = "/sfx/towners/pegboy07.wav";
  d_quest_dialogues[Quest::Type::TheChamberOfBone][0].raw_dialogue_text = 
    "A vast and mysterious treasure, you say? Maybe I could be interested "
    "in picking up a few things from you... or better yet, don't you need "
    "some rare and expensive supplies to get you through this ordeal?";

  // Halls of the Blind quest
  d_quest_dialogues.emplace( Quest::Type::HallsOfTheBlind, 1 );
  d_quest_dialogues[Quest::Type::HallsOfTheBlind][0].dialogue_file_name = "/sfx/towners/pegboy11.wav";
  d_quest_dialogues[Quest::Type::HallsOfTheBlind][0].raw_dialogue_text = 
    "Lets see, am I selling you something? No. Are you giving me money to "
    "tell you about this? No. Are you now leaving and going to talk to the "
    "storyteller who lives for this kind of thing? Yes.";

  // Black mushroom quest
  d_quest_dialogues.emplace( Quest::Type::TheBlackMushroom, 1 );
  d_quest_dialogues[Quest::Type::TheBlackMushroom][0].dialogue_file_name = "/sfx/towners/pegboy19.wav";
  d_quest_dialogues[Quest::Type::TheBlackMushroom][0].raw_dialogue_text = 
    "I don't have any mushrooms of any size or color for sale. How about "
    "something a bit more useful?";

  // Anvil of Fury quest
  d_quest_dialogues.emplace( Quest::Type::TheAnvilOfFury, 1 );
  d_quest_dialogues[Quest::Type::TheAnvilOfFury][0].dialogue_file_name = "/sfx/towners/pegboy13.wav";
  d_quest_dialogues[Quest::Type::TheAnvilOfFury][0].raw_dialogue_text = 
    "If you were to find this artifact for Griswold, it could put a serious "
    "damper on my business here. Awwww, you'll never find it.";

  // Warlord of Blood quest
  d_quest_dialogues.emplace( Quest::Type::TheWarlordOfBlood, 1 );
  d_quest_dialogues[Quest::Type::TheWarlordOfBlood][0].dialogue_file_name = "/sfx/towners/pegboy17.wav";
  d_quest_dialogues[Quest::Type::TheWarlordOfBlood][0].raw_dialogue_text = 
    "I haven't ever dealt with this Warlord you speak of, but he sounds like "
    "he's going through a lot of swords. Wouldn't mind supplying his armies...";

  // Archbishop Lazarus quest
  d_quest_dialogues.emplace( Quest::Type::ArchbishopLazarus, 1 );
  d_quest_dialogues[Quest::Type::ArchbishopLazarus][0].dialogue_file_name = "/sfx/towners/pegboy03.wav";
  d_quest_dialogues[Quest::Type::ArchbishopLazarus][0].raw_dialogue_text = 
    "Yes, the righteous Lazarus, who was sooo effective against those monsters "
    "down there. Didn't help save my leg, did it? Look, I'll give you a free "
    "piece of advice. Ask Farnham, he was there.";

  // Lachdanan quest
  d_quest_dialogues.emplace( Quest::Type::Lachdanan, 1 );
  d_quest_dialogues[Quest::Type::Lachdanan][0].dialogue_file_name = "/sfx/towners/pegboy12.wav";
  d_quest_dialogues[Quest::Type::Lachdanan][0].raw_dialogue_text = 
    "Wait, let me guess. Cain was swallowed up in a gigantic fissure that opened "
    "beneath him. He was incinerated in a ball of hellfire, and can't answer your "
    "questions anymore. Oh, that isn't what happened? Then I guess you'll be buying "
    "something or you'll be on your way.";

  // Armor of Valor quest
  d_quest_dialogues.emplace( Quest::Type::ArmorOfValor, 1 );
  d_quest_dialogues[Quest::Type::ArmorOfValor][0].dialogue_file_name = "/sfx/towners/pegboy14.wav";
  d_quest_dialogues[Quest::Type::ArmorOfValor][0].raw_dialogue_text = 
    "You intend to find the armor known as Valor? No one has ever figured out where "
    "Arkaine stashed the stuff, and if my contacts couldn't find it, I seriously doubt "
    "you ever will either.";

  // Load the gossip dialogues
  d_gossip_dialogues[0].dialogue_file_name = "/sfx/towners/pegboy33.wav";
  d_gossip_dialogues[0].raw_dialogue_text =
    "Not everyone in Tristram has a use - or a market - for everything you will find "
    "in the labyrinth. Not even me, as hard as that is to believe. Sometimes, only you "
    "will be able to find a purpose for some things.";
  
  d_gossip_dialogues[1].dialogue_file_name = "/sfx/towners/pegboy34.wav";
  d_gossip_dialogues[1].raw_dialogue_text =
    "Don't trust everything the drunk says. Too many ales have fogged his vision and "
    "his good sense.";
  
  d_gossip_dialogues[2].dialogue_file_name = "/sfx/towners/pegboy35.wav";
  d_gossip_dialogues[2].raw_dialogue_text =
    "In case you haven't noticed, I don't buy anything from Tristram. I am an importer "
    "of quality goods. If you want to peddle junk, you'll have to see Griswold, Pepin "
    "or that witch, Adria. I'm sure that they will snap up whatever you can bring them...";
  
  d_gossip_dialogues[3].dialogue_file_name = "/sfx/towners/pegboy36.wav";
  d_gossip_dialogues[3].raw_dialogue_text =
    "I guess I owe the blacksmith my life - what there is of it. Sure, Griswold offered "
    "me an apprenticeship at the smithy, and he is a nice enough guy, but I'll never get "
    "enough money to... well, let's just say that I have definite plans that require a "
    "large amount of gold.";
  
  d_gossip_dialogues[4].dialogue_file_name = "/sfx/towners/pegboy37.wav";
  d_gossip_dialogues[4].raw_dialogue_text =
    "If I were a few years older, I would shower her with whatever riches I could muster, "
    "and let me assure you I can get my hands on some very nice stuff. Gillian is a beautiful "
    "girl who should get out of Tristram as soon as it is safe. Hmmm... maybe I'll take her "
    "with me when I go...";
  
  d_gossip_dialogues[5].dialogue_file_name = "/sfx/towners/pegboy38.wav";
  d_gossip_dialogues[5].raw_dialogue_text =
    "Cain knows too much. He scares the life out of me - even more than that woman across "
    "the river. He keeps telling me about how lucky I am to be alive, and how my story is "
    "foretold in legend. I think he's off his crock.";
  
  d_gossip_dialogues[6].dialogue_file_name = "/sfx/towners/pegboy39.wav";
  d_gossip_dialogues[6].raw_dialogue_text =
    "Farnham - now there is a man with serious problems, and I know all about how serious "
    "problems can be. He trusted too much in the integrity of one man, and Lazarus led him "
    "into the very jaws of death. Oh, I know what it's like down there, so don't even start "
    "telling me about your plans to destroy the evil that dwells in that Labyrinth. Just "
    "watch your legs...";
  
  d_gossip_dialogues[7].dialogue_file_name = "/sfx/towners/pegboy40.wav";
  d_gossip_dialogues[7].raw_dialogue_text =
    "As long as you don't need anything reattached, old Pepin is as good as they come. If "
    "I'd have had some of those potions he brews, I might still have my leg...";

  d_gossip_dialogues[8].dialogue_file_name = "/sfx/towners/pegboy42.wav";
  d_gossip_dialogues[8].raw_dialogue_text =
    "Adria truly bothers me. Sure, Cain is creepy in what he can tell you about the past, "
    "but that witch can see into your past. She always has some way to get whatever she "
    "needs, too. Adria gets her hands on more merchandise than I've seen pass through the "
    "gates of the King's Bazaar during High Festival.";

  d_gossip_dialogues[9].dialogue_file_name = "/sfx/towners/pegboy43.wav";
  d_gossip_dialogues[9].raw_dialogue_text =
    "Ogden is a fool for staying here. I could get him out of town for a very reasonable "
    "price, but he insists on trying to make a go of it with that stupid tavern. I guess "
    "at the least he gives Gillian a place to work, and his wife Garda does make a superb "
    "Shepherd's pie...";

  // Load the unused dialogues
  d_unused_dialogues[0].dialogue_file_name = "/sfx/towners/pegboy05.wav";
  d_unused_dialogues[0].raw_dialogue_text = "Test";
  
  d_unused_dialogues[1].dialogue_file_name = "/sfx/towners/pegboy06.wav";
  d_unused_dialogues[1].raw_dialogue_text = "Test";
  
  d_unused_dialogues[2].dialogue_file_name = "/sfx/towners/pegboy08.wav";
  d_unused_dialogues[2].raw_dialogue_text = "Test";
  
  d_unused_dialogues[3].dialogue_file_name = "/sfx/towners/pegboy09.wav";
  d_unused_dialogues[3].raw_dialogue_text = "Test";
  
  d_unused_dialogues[4].dialogue_file_name = "/sfx/towners/pegboy15.wav";
  d_unused_dialogues[4].raw_dialogue_text = "Test";
  
  d_unused_dialogues[5].dialogue_file_name = "/sfx/towners/pegboy16.wav";
  d_unused_dialogues[5].raw_dialogue_text = "Test";
  
  d_unused_dialogues[6].dialogue_file_name = "/sfx/towners/pegboy20.wav";
  d_unused_dialogues[6].raw_dialogue_text = "Test";
  
  d_unused_dialogues[7].dialogue_file_name = "/sfx/towners/pegboy21.wav";
  d_unused_dialogues[7].raw_dialogue_text = "Test";

  d_unused_dialogues[8].dialogue_file_name = "/sfx/towners/pegboy22.wav";
  d_unused_dialogues[8].raw_dialogue_text = "Test";

  d_unused_dialogues[9].dialogue_file_name = "/sfx/towners/pegboy23.wav";
  d_unused_dialogues[9].raw_dialogue_text = "Test";

  d_unused_dialogues[10].dialogue_file_name = "/sfx/towners/pegboy24.wav";
  d_unused_dialogues[10].raw_dialogue_text = "Test";

  d_unused_dialogues[11].dialogue_file_name = "/sfx/towners/pegboy25.wav";
  d_unused_dialogues[11].raw_dialogue_text = "Test";

  d_unused_dialogues[12].dialogue_file_name = "/sfx/towners/pegboy26.wav";
  d_unused_dialogues[12].raw_dialogue_text = "Test";

  d_unused_dialogues[13].dialogue_file_name = "/sfx/towners/pegboy27.wav";
  d_unused_dialogues[13].raw_dialogue_text = "Test";

  d_unused_dialogues[14].dialogue_file_name = "/sfx/towners/pegboy28.wav";
  d_unused_dialogues[14].raw_dialogue_text = "Test";

  d_unused_dialogues[15].dialogue_file_name = "/sfx/towners/pegboy29.wav";
  d_unused_dialogues[15].raw_dialogue_text = "Test";
  
  d_unused_dialogues[16].dialogue_file_name = "/sfx/towners/pegboy30.wav";
  d_unused_dialogues[16].raw_dialogue_text = "Test";

  d_unused_dialogues[17].dialogue_file_name = "/sfx/towners/pegboy31.wav";
  d_unused_dialogues[17].raw_dialogue_text = "Test";

  d_unused_dialogues[18].dialogue_file_name = "/sfx/towners/pegboy41.wav";
  d_unused_dialogues[18].raw_dialogue_text = "Test";
}

// Get the warrior description
QString Wirt::getDescription() const
{
  return QString( "WIRT THE PEG-LEGGED BOY" );
}

// Get the number of image assets used by the object
int Wirt::getNumberOfImageAssets() const
{
  return 1;
}

// Get the image asset names used by the object
void Wirt::getImageAssetNames( QSet<QString>& image_asset_names ) const
{
  image_asset_names.insert( s_image_asset_name );
}

// Check if an image asset is used
bool Wirt::isImageAssetUsed( const QString& image_asset_name ) const
{
  return image_asset_name == s_image_asset_name;
}

// Check if the image assets have been loaded
bool Wirt::imageAssetsLoaded() const
{
  return d_sprites_loaded;
}

// Load the image asset
void Wirt::loadImageAsset( const QString&,
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
    QVector<int> source_frame_indices( 20 );

    for( int i = 0; i < source_frame_indices.size(); ++i )
      source_frame_indices[i] = i;

    game_sprite = GameSprite( s_image_asset_name, source_frame_indices );
  }

  game_sprite.setAsset( s_image_asset_name, image_asset_frames );
  game_sprite.setFrameDuration( 15 );
}

// Finalize image asset loading
void Wirt::finalizeImageAssetLoading()
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
void Wirt::dumpImageAssets()
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
void Wirt::discussQuest( const Quest::Type quest )
{
  auto dialogue_it = d_quest_dialogues.find( quest );
  
  if( dialogue_it != d_quest_dialogues.end() )
    this->playAndDisplayDialogue( dialogue_it->second.front() );
}

// Play gossip dialogue
void Wirt::gossip()
{
  static int gossip_index = 0;

  this->playAndDisplayDialogue( d_gossip_dialogues[gossip_index] );
  
  gossip_index = (gossip_index+1)%d_gossip_dialogues.size();
}

// Greet the character
void Wirt::greet()
{
  d_greeting.playSound();
}

// Get the movement speed (pixels per game tic)
qreal Wirt::getMovementSpeed() const
{
  return 0.0;
}

// Check if the NPC has dialogue for the requested quest
bool Wirt::hasDialogue( const Quest::Type quest ) const
{
  return d_quest_dialogues.find( quest ) != d_quest_dialogues.end();
}

// Load the interaction menu
NPCInteractionMenu* Wirt::createInteractionMenu( QWidget* parent )
{
  return new WirtInteractionMenu( parent );
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Wirt.cpp
//---------------------------------------------------------------------------//
