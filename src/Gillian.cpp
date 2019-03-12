//---------------------------------------------------------------------------//
//!
//! \file   Gillian.cpp
//! \author Sean Robinson
//! \brief  The Gillian class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "Gillian.h"
#include "GillianInteractionMenu.h"

namespace QtD1{

// Initialize static member data
QString Gillian::s_image_asset_name = "/towners/townwmn1/wmnn.cel+levels/towndata/town.pal";

// Constructor
Gillian::Gillian( QGraphicsObject* parent )
  : NPC( parent, false ),
    d_direction_sprites(),
    d_sprites_loaded( false ),
    d_greeting(),
    d_quest_dialogues(),
    d_gossip_dialogues( 8 ),
    d_unused_dialogues( 18 )
{
  // Load the greeting
  d_greeting.setSource( "/sfx/towners/bmaid31.wav" );

  // Load the quest dialogues

  // Butcher quest
  d_quest_dialogues.emplace( Quest::Type::TheButcher, 1 );
  d_quest_dialogues[Quest::Type::TheButcher][0].dialogue_file_name = "/sfx/towners/bmaid08.wav";
  d_quest_dialogues[Quest::Type::TheButcher][0].raw_dialogue_text = 
    "When Farnham said something about a butcher killing people, I "
    "immediately discounted it. But since you brought it up, maybe "
    "it is true.";

  // Poisoned Water Supply quest
  d_quest_dialogues.emplace( Quest::Type::PoisonWater, 1 );
  d_quest_dialogues[Quest::Type::PoisonWater][0].dialogue_file_name = "/sfx/towners/bmaid04.wav";
  d_quest_dialogues[Quest::Type::PoisonWater][0].raw_dialogue_text = 
    "My grandmother is very weak, and Garda says that we cannot drink "
    "the water from the wells. Please, can you do something to help us?";

  // King Leoric quest
  d_quest_dialogues.emplace( Quest::Type::KingLeoricsCurse, 1 );
  d_quest_dialogues[Quest::Type::KingLeoricsCurse][0].dialogue_file_name = "/sfx/towners/bmaid01.wav";
  d_quest_dialogues[Quest::Type::KingLeoricsCurse][0].raw_dialogue_text = 
    "I don't like to think about how the King died. I like to remember "
    "him for the kind and just ruler that he was. His death was so sad "
    "and seemed very wrong, somehow.";

  // Ogdens Sign quest
  d_quest_dialogues.emplace( Quest::Type::OgdensSign, 1 );
  d_quest_dialogues[Quest::Type::OgdensSign][0].dialogue_file_name = "/sfx/towners/bmaid02.wav";
  d_quest_dialogues[Quest::Type::OgdensSign][0].raw_dialogue_text = 
    "Oh my! Is that where the sign went? My Grandmother and I must have "
    "slept right through the whole thing. Thank the Light that those "
    "monsters didn't attack the inn.";

  // Magic Rock quest
  d_quest_dialogues.emplace( Quest::Type::TheMagicRock,  1 );
  d_quest_dialogues[Quest::Type::TheMagicRock][0].dialogue_file_name = "/sfx/towners/bmaid18.wav";
  d_quest_dialogues[Quest::Type::TheMagicRock][0].raw_dialogue_text = 
    "Well, a caravan of some very important people did stop here, but that "
    "was quite a while ago. They had strange accents and were starting on a "
    "long journey, as I recall. I don't see how you could hope to find anything "
    "that they would have been carrying.";

  // Chamber of Bone quest
  d_quest_dialogues.emplace( Quest::Type::TheChamberOfBone, 1 );
  d_quest_dialogues[Quest::Type::TheChamberOfBone][0].dialogue_file_name = "/sfx/towners/bmaid06.wav";
  d_quest_dialogues[Quest::Type::TheChamberOfBone][0].raw_dialogue_text = 
    "I am afraid that I haven't heard anything about that. Perhaps Cain the "
    "Storyteller could be of some help.";

  // Halls of the Blind quest
  d_quest_dialogues.emplace( Quest::Type::HallsOfTheBlind, 1 );
  d_quest_dialogues[Quest::Type::HallsOfTheBlind][0].dialogue_file_name = "/sfx/towners/bmaid10.wav";
  d_quest_dialogues[Quest::Type::HallsOfTheBlind][0].raw_dialogue_text = 
    "If you have questions about blindness, you should talk to Pepin. I know "
    "that he gave my grandmother a potion that helped clear her vision, so maybe "
    "he can help you, too.";

  // Black mushroom quest
  d_quest_dialogues.emplace( Quest::Type::TheBlackMushroom, 1 );
  d_quest_dialogues[Quest::Type::TheBlackMushroom][0].dialogue_file_name = "/sfx/towners/bmaid19.wav";
  d_quest_dialogues[Quest::Type::TheBlackMushroom][0].raw_dialogue_text = 
    "I think Ogden might have some mushrooms in the storage cellar. Why don't "
    "you ask him?";

  // Anvil of Fury quest
  d_quest_dialogues.emplace( Quest::Type::TheAnvilOfFury, 1 );
  d_quest_dialogues[Quest::Type::TheAnvilOfFury][0].dialogue_file_name = "/sfx/towners/bmaid12.wav";
  d_quest_dialogues[Quest::Type::TheAnvilOfFury][0].raw_dialogue_text = 
    "Griswold's father used to tell some of us when we were growing up about a "
    "giant anvil that was used to make mighty weapons. He said that when a hammer "
    "was struck upon this anvil, the ground would shake with a great fury. Whenever "
    "the earth moves, I always remember that story.";

  // Warlord of Blood quest
  d_quest_dialogues.emplace( Quest::Type::TheWarlordOfBlood, 1 );
  d_quest_dialogues[Quest::Type::TheWarlordOfBlood][0].dialogue_file_name = "/sfx/towners/bmaid16.wav";
  d_quest_dialogues[Quest::Type::TheWarlordOfBlood][0].raw_dialogue_text = 
    "If you are to battle such a fierce opponent, may Light be your guide and your "
    "defender. I will keep you in my thoughts.";

  // Archbishop Lazarus quest
  d_quest_dialogues.emplace( Quest::Type::ArchbishopLazarus, 1 );
  d_quest_dialogues[Quest::Type::ArchbishopLazarus][0].dialogue_file_name = "/sfx/towners/bmaid03.wav";
  d_quest_dialogues[Quest::Type::ArchbishopLazarus][0].raw_dialogue_text = 
    "I remember Lazarus as being a very kind and giving man. He spoke at my mother's "
    "funeral, and was supportive of my grandmother and myself in a very troubled time. "
    "I pray every night that somehow, he is still alive and safe.";

  // Lachdanan quest
  d_quest_dialogues.emplace( Quest::Type::Lachdanan, 1 );
  d_quest_dialogues[Quest::Type::Lachdanan][0].dialogue_file_name = "/sfx/towners/bmaid11.wav";
  d_quest_dialogues[Quest::Type::Lachdanan][0].raw_dialogue_text = 
    "I've never heard of a Lachdanan before. I'm sorry, but I don't think that I can be "
    "of much help to you.";

  // Armor of Valor quest
  d_quest_dialogues.emplace( Quest::Type::ArmorOfValor, 1 );
  d_quest_dialogues[Quest::Type::ArmorOfValor][0].dialogue_file_name = "/sfx/towners/bmaid13.wav";
  d_quest_dialogues[Quest::Type::ArmorOfValor][0].raw_dialogue_text = 
    "The story of the magic armor called Valor is something I often heard the boys talk about. "
    "You had better ask one of the men in the village.";

  // Load the gossip dialogues
  d_gossip_dialogues[0].dialogue_file_name = "/sfx/towners/bmaid32.wav";
  d_gossip_dialogues[0].raw_dialogue_text =
    "My grandmother had a dream that you would come and talk to me. "
    "She has visions, you know and can see into the future.";
  
  d_gossip_dialogues[1].dialogue_file_name = "/sfx/towners/bmaid33.wav";
  d_gossip_dialogues[1].raw_dialogue_text =
    "The woman at the edge of town is a witch! She seems nice enough, "
    "and her name, Adria, is very pleasing to the ear, but I am very "
    "afraid of her. It would take someone quite brave, like you, to "
    "see what she is doing out there.";
  
  d_gossip_dialogues[2].dialogue_file_name = "/sfx/towners/bmaid34.wav";
  d_gossip_dialogues[2].raw_dialogue_text =
    "Our Blacksmith is a point of pride to the people of Tristram. "
    "Not only is he a master craftsman who has won many contests "
    "within his guild, but he received praises from our King Leoric "
    "himself - may his soul rest in peace. Griswold is also a great "
    "hero; just ask Cain.";
  
  d_gossip_dialogues[3].dialogue_file_name = "/sfx/towners/bmaid35.wav";
  d_gossip_dialogues[3].raw_dialogue_text =
    "Cain has been the storyteller of Tristram for as long as I can "
    "remember. He knows so much, and can tell you just about anything about almost everything.";
  
  d_gossip_dialogues[4].dialogue_file_name = "/sfx/towners/bmaid36.wav";
  d_gossip_dialogues[4].raw_dialogue_text =
    "Farnham is a drunkard who fills his belly with ale and everyone "
    "else's ears with nonsense. I know that both Pepin and Ogden feel "
    "sympathy for him, but I get so frustrated watching him slip farther "
    "and farther into a befuddled stupor every night.";
  
  d_gossip_dialogues[5].dialogue_file_name = "/sfx/towners/bmaid37.wav";
  d_gossip_dialogues[5].raw_dialogue_text =
    "Pepin saved my grandmother's life, and I know that I can never repay "
    "him for that. His ability to heal any sickness is more powerful than "
    "the mightiest sword and more mysterious than any spell you can name. "
    "If you ever are in need of healing, Pepin can help you.";
  
  d_gossip_dialogues[6].dialogue_file_name = "/sfx/towners/bmaid39.wav";
  d_gossip_dialogues[6].raw_dialogue_text =
    "I grew up with Wirt's mother, Canace. Although she was only slightly "
    "hurt when those hideous creatures stole him, she never recovered. I "
    "think she died of a broken heart. Wirt has become a mean-spirited youngster, "
    "looking only to profit from the sweat of others. I know that he suffered "
    "and has seen horrors that I cannot even imagine, but some of that darkness "
    "hangs over him still.";
  
  d_gossip_dialogues[7].dialogue_file_name = "/sfx/towners/bmaid40.wav";
  d_gossip_dialogues[7].raw_dialogue_text =
    "Ogden and his wife have taken me and my grandmother into their home and have "
    "even let me earn a few gold pieces by working at the inn. I owe so much to them, "
    "and hope one day to leave this place and help them start a grand hotel in the east.";

  // Load the unused dialogues
  d_unused_dialogues[0].dialogue_file_name = "/sfx/towners/bmaid05.wav";
  d_unused_dialogues[0].raw_dialogue_text = "Test";
  
  d_unused_dialogues[1].dialogue_file_name = "/sfx/towners/bmaid07.wav";
  d_unused_dialogues[1].raw_dialogue_text = "Test";
  
  d_unused_dialogues[2].dialogue_file_name = "/sfx/towners/bmaid09.wav";
  d_unused_dialogues[2].raw_dialogue_text = "Test";
  
  d_unused_dialogues[3].dialogue_file_name = "/sfx/towners/bmaid14.wav";
  d_unused_dialogues[3].raw_dialogue_text = "Test";
  
  d_unused_dialogues[4].dialogue_file_name = "/sfx/towners/bmaid15.wav";
  d_unused_dialogues[4].raw_dialogue_text = "Test";
  
  d_unused_dialogues[5].dialogue_file_name = "/sfx/towners/bmaid17.wav";
  d_unused_dialogues[5].raw_dialogue_text = "Test";
  
  d_unused_dialogues[6].dialogue_file_name = "/sfx/towners/bmaid20.wav";
  d_unused_dialogues[6].raw_dialogue_text = "Test";
  
  d_unused_dialogues[7].dialogue_file_name = "/sfx/towners/bmaid21.wav";
  d_unused_dialogues[7].raw_dialogue_text = "Test";

  d_unused_dialogues[8].dialogue_file_name = "/sfx/towners/bmaid22.wav";
  d_unused_dialogues[8].raw_dialogue_text = "Test";

  d_unused_dialogues[9].dialogue_file_name = "/sfx/towners/bmaid23.wav";
  d_unused_dialogues[9].raw_dialogue_text = "Test";

  d_unused_dialogues[10].dialogue_file_name = "/sfx/towners/bmaid24.wav";
  d_unused_dialogues[10].raw_dialogue_text = "Test";

  d_unused_dialogues[11].dialogue_file_name = "/sfx/towners/bmaid25.wav";
  d_unused_dialogues[11].raw_dialogue_text = "Test";

  d_unused_dialogues[12].dialogue_file_name = "/sfx/towners/bmaid26.wav";
  d_unused_dialogues[12].raw_dialogue_text = "Test";

  d_unused_dialogues[13].dialogue_file_name = "/sfx/towners/bmaid28.wav";
  d_unused_dialogues[13].raw_dialogue_text = "Test";

  d_unused_dialogues[14].dialogue_file_name = "/sfx/towners/bmaid27.wav";
  d_unused_dialogues[14].raw_dialogue_text = "Test";

  d_unused_dialogues[15].dialogue_file_name = "/sfx/towners/bmaid30.wav";
  d_unused_dialogues[15].raw_dialogue_text = "Test";

  d_unused_dialogues[16].dialogue_file_name = "/sfx/towners/bmaid29.wav";
  d_unused_dialogues[16].raw_dialogue_text = "Test";

  d_unused_dialogues[17].dialogue_file_name = "/sfx/towners/bmaid38.wav";
  d_unused_dialogues[17].raw_dialogue_text = "Test";
}

// Get the warrior description
QString Gillian::getDescription() const
{
  return QString( "GILLIAN THE BARMAID" );
}

// Get the number of image assets used by the object
int Gillian::getNumberOfImageAssets() const
{
  return 1;
}

// Get the image asset names used by the object
void Gillian::getImageAssetNames( QSet<QString>& image_asset_names ) const
{
  image_asset_names.insert( s_image_asset_name );
}

// Check if an image asset is used
bool Gillian::isImageAssetUsed( const QString& image_asset_name ) const
{
  return image_asset_name == s_image_asset_name;
}

// Check if the image assets have been loaded
bool Gillian::imageAssetsLoaded() const
{
  return d_sprites_loaded;
}

// Load the image asset
void Gillian::loadImageAsset( const QString&,
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
void Gillian::finalizeImageAssetLoading()
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
void Gillian::dumpImageAssets()
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
void Gillian::discussQuest( const Quest::Type quest )
{
  auto dialogue_it = d_quest_dialogues.find( quest );
  
  if( dialogue_it != d_quest_dialogues.end() )
    this->playAndDisplayDialogue( dialogue_it->second.front() );
}

// Play gossip dialogue
void Gillian::gossip()
{
  static int gossip_index = 0;

  this->playAndDisplayDialogue( d_gossip_dialogues[gossip_index] );
  
  gossip_index = (gossip_index+1)%d_gossip_dialogues.size();
}

// Greet the character
void Gillian::greet()
{
  d_greeting.playSound();
}

// Get the movement speed (pixels per game tic)
qreal Gillian::getMovementSpeed() const
{
  return 0.0;
}

// Check if the NPC has dialogue for the requested quest
bool Gillian::hasDialogue( const Quest::Type quest ) const
{
  return d_quest_dialogues.find( quest ) != d_quest_dialogues.end();
}

// Load the interaction menu
NPCInteractionMenu* Gillian::createInteractionMenu( QWidget* parent )
{
  return new GillianInteractionMenu( parent );
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Gillian.cpp
//---------------------------------------------------------------------------//
