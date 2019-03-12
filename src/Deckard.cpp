//---------------------------------------------------------------------------//
//!
//! \file   Deckard.cpp
//! \author Sean Robinson
//! \brief  The Deckard class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "Deckard.h"
#include "DeckardInteractionMenu.h"

namespace QtD1{

// Initialize static member data
QString Deckard::s_image_asset_name = "/towners/strytell/strytell.cel+levels/towndata/town.pal";

// Constructor
Deckard::Deckard( QGraphicsObject* parent )
  : NPC( parent, false ),
    d_direction_sprites(),
    d_sprites_loaded( false ),
    d_greeting(),
    d_quest_dialogues(),
    d_gossip_dialogues( 9 ),
    d_unused_dialogues( 13 )
{
  // Load the greeting
  d_greeting.setSource( "/sfx/towners/storyt25.wav" );

  // Load the quest dialogues

  // Butcher quest
  d_quest_dialogues.emplace( Quest::Type::TheButcher, 1 );
  d_quest_dialogues[Quest::Type::TheButcher][0].dialogue_file_name = "/sfx/towners/storyt10.wav";
  d_quest_dialogues[Quest::Type::TheButcher][0].raw_dialogue_text = 
    "It seems that the Archbishop Lazarus goaded many of the townsmen "
    "into venturing into the Labyrinth to find the King's missing son. "
    "He played upon their fears and whipped them into a frenzied mob. "
    "None of them were prepared for what lay within the cold earth... "
    "Lazarus abandoned them down there - left in the clutches of unspeakable "
    "horrors - to die.";

  // Poisoned Water Supply quest
  d_quest_dialogues.emplace( Quest::Type::PoisonWater, 1 );
  d_quest_dialogues[Quest::Type::PoisonWater][0].dialogue_file_name = "/sfx/towners/storyt04.wav";
  d_quest_dialogues[Quest::Type::PoisonWater][0].raw_dialogue_text = 
    "Hmm, I don't know what I can really tell you about this that will be "
    "of any help. The water that fills our wells comes from an underground "
    "spring. I have heard of a tunnel that leads to a great lake - perhaps "
    "they are one and the same. Unfortunately, I do not know what would cause "
    "our water supply to be tainted.";

  // King Leoric quest
  d_quest_dialogues.emplace( Quest::Type::KingLeoricsCurse, 1 );
  d_quest_dialogues[Quest::Type::KingLeoricsCurse][0].dialogue_file_name = "/sfx/towners/storyt01.wav";
  d_quest_dialogues[Quest::Type::KingLeoricsCurse][0].raw_dialogue_text = 
    "Ahh, the story of our King, is it? The tragic fall of Leoric was a harsh "
    "blow to this land. The people always loved the King, and now they live in "
    "mortal fear of him. The question that I keep asking myself is how he could "
    "have fallen so far from the Light, as Leoric had always been the holiest of "
    "men. Only the vilest powers of Hell could so utterly destroy a man from within...";

  // Ogdens Sign quest
  d_quest_dialogues.emplace( Quest::Type::OgdensSign, 1 );
  d_quest_dialogues[Quest::Type::OgdensSign][0].dialogue_file_name = "/sfx/towners/storyt02.wav";
  d_quest_dialogues[Quest::Type::OgdensSign][0].raw_dialogue_text = 
    "I see that this strange behavior puzzles you as well. I would surmise that "
    "since many demons fear the light of the sun and believe that it holds great "
    "power, it may be that the rising sun depicted on the sign you speak of has "
    "led them to believe that it too holds some arcane powers. Hmm, perhaps they "
    "are not all as smart as we had feared...";

  // Magic Rock quest
  d_quest_dialogues.emplace( Quest::Type::TheMagicRock,  1 );
  d_quest_dialogues[Quest::Type::TheMagicRock][0].dialogue_file_name = "/sfx/towners/storyt20.wav";
  d_quest_dialogues[Quest::Type::TheMagicRock][0].raw_dialogue_text = 
    "Griswold speaks of the Heaven Stone that was destined for the enclave located "
    "in the east. It was being taken there for further study. This stone glowed with "
    "an energy that somehow granted vision beyond that which a normal man could "
    "possess. I do not know what secrets it holds, my friend, but finding this stone "
    "would certainly prove most valuable.";

  // Chamber of Bone quest
  d_quest_dialogues.emplace( Quest::Type::TheChamberOfBone, 1 );
  d_quest_dialogues[Quest::Type::TheChamberOfBone][0].dialogue_file_name = "/sfx/towners/storyt07.wav";
  d_quest_dialogues[Quest::Type::TheChamberOfBone][0].raw_dialogue_text = 
    "A book that speaks of a chamber of human bones? Well, a Chamber of Bone is mentioned "
    "in certain archaic writings that I studied in the libraries of the East. These tomes "
    "inferred that when the Lords of the underworld desired to protect great treasures, they "
    "would create domains where those who died in the attempt to steal that treasure would be "
    "forever bound to defend it. A twisted, but strangely fitting, end?";

  // Halls of the Blind quest
  d_quest_dialogues.emplace( Quest::Type::HallsOfTheBlind, 1 );
  d_quest_dialogues[Quest::Type::HallsOfTheBlind][0].dialogue_file_name = "/sfx/towners/storyt12.wav";
  d_quest_dialogues[Quest::Type::HallsOfTheBlind][0].raw_dialogue_text = 
    "You recite an interesting rhyme written in a style that reminds me of other works. Let me "
    "think now - what was it? ...Darkness shrouds the Hidden. Eyes glowing unseen with only the "
    "sounds of razor claws briefly scraping to torment those poor souls who have been made sightless "
    "for all eternity. The prison for those so damned is named the Halls of the Blind...";

  // Black mushroom quest
  d_quest_dialogues.emplace( Quest::Type::TheBlackMushroom, 1 );
  d_quest_dialogues[Quest::Type::TheBlackMushroom][0].dialogue_file_name = "/sfx/towners/storyt21.wav";
  d_quest_dialogues[Quest::Type::TheBlackMushroom][0].raw_dialogue_text = 
    "The witch Adria seeks a black mushroom? I know as much about Black Mushrooms as I do about "
    "Red Herrings. Perhaps Pepin the Healer could tell you more, but this is something that cannot "
    "be found in any of my stories or books.";

  // Anvil of Fury quest
  d_quest_dialogues.emplace( Quest::Type::TheAnvilOfFury, 1 );
  d_quest_dialogues[Quest::Type::TheAnvilOfFury][0].dialogue_file_name = "/sfx/towners/storyt14.wav";
  d_quest_dialogues[Quest::Type::TheAnvilOfFury][0].raw_dialogue_text = 
    "Griswold speaks of The Anvil of Fury - a legendary artifact long searched for, but never found. "
    "Crafted from the metallic bones of the Razor Pit demons, the Anvil of Fury was smelt around the "
    "skulls of the five most powerful magi of the underworld. Carved with runes of power and chaos, "
    "any weapon or armor forged upon this Anvil will be immersed into the realm of Chaos, imbedding "
    "it with magical properties. It is said that the unpredictable nature of Chaos makes it difficult "
    "to know what the outcome of this smithing will be...";

  // Warlord of Blood quest
  d_quest_dialogues.emplace( Quest::Type::TheWarlordOfBlood, 1 );
  d_quest_dialogues[Quest::Type::TheWarlordOfBlood][0].dialogue_file_name = "/sfx/towners/storyt18.wav";
  d_quest_dialogues[Quest::Type::TheWarlordOfBlood][0].raw_dialogue_text = 
    "I know of only one legend that speaks of such a warrior as you describe. "
    "His story is found within the ancient chronicles of the Sin War... Stained "
    "by a thousand years of war, blood and death, the Warlord of Blood stands upon "
    "a mountain of his tattered victims. His dark blade screams a black curse to the "
    "living; a tortured invitation to any who would stand before this Executioner of "
    "Hell. It is also written that although he was once a mortal who fought beside "
    "the Legion of Darkness during the Sin War, he lost his humanity to his insatiable "
    "hunger for blood.";

  // Archbishop Lazarus quest
  d_quest_dialogues.emplace( Quest::Type::ArchbishopLazarus, 3 );
  d_quest_dialogues[Quest::Type::ArchbishopLazarus][0].dialogue_file_name = "/sfx/towners/storyt36.wav";
  d_quest_dialogues[Quest::Type::ArchbishopLazarus][0].raw_dialogue_text = 
    "This does not bode well, for it confirms my darkest fears. While I did not allow myself to believe "
    "the ancient legends, I cannot deny them now. Perhaps the time has come to reveal who I am. My true "
    "name is Deckard Cain the Elder, and I am the last descendant of an ancient Brotherhood that was "
    "dedicated to safeguarding the secrets of a timeless evil. An evil that quite obviously has now been "
    "released. The Archbishop Lazarus, once King Leoric's most trusted advisor, led a party of simple "
    "townsfolk into the Labyrinth to find the King's missing son, Albrecht. Quite some time passed before "
    "they returned, and only a few of them escaped with their lives. Curse me for a fool! I should have "
    "suspected his veiled treachery then. It must have been Lazarus himself who kidnapped Albrecht and has "
    "since hidden him within the Labyrinth. I do not understand why the Archbishop turned to the darkness, "
    "or what his interest is in the child. unless he means to sacrifice him to his dark masters! That must "
    "be what he has planned! The survivors of his 'rescue party' say that Lazarus was last seen running into "
    "the deepest bowels of the labyrinth. You must hurry and save the prince from the sacrificial blade of "
    "this demented fiend!";
  d_quest_dialogues[Quest::Type::ArchbishopLazarus][1].dialogue_file_name = "/sfx/towners/storyt37.wav";
  d_quest_dialogues[Quest::Type::ArchbishopLazarus][1].raw_dialogue_text = 
    "You must hurry and rescue Albrecht from the hands of Lazarus. The prince and the people of this "
    "kingdom are counting on you!";
  d_quest_dialogues[Quest::Type::ArchbishopLazarus][2].dialogue_file_name = "/sfx/towners/storyt38.wav";
  d_quest_dialogues[Quest::Type::ArchbishopLazarus][2].raw_dialogue_text = 
    "Your story is quite grim, my friend. Lazarus will surely burn in Hell for his horrific deed. The boy that "
    "you describe is not our prince, but I believe that Albrecht may yet be in danger. The symbol of power that "
    "you speak of must be a portal in the very heart of the labyrinth. Know this, my friend - The evil that you "
    "move against is the dark Lord of Terror. He is known to mortal men as Diablo. It was he who was imprisoned "
    "within the Labyrinth many centuries ago and I fear that he seeks to once again sow chaos in the realm of "
    "mankind. You must venture through the portal and destroy Diablo before it is too late!";

  // Lachdanan quest
  d_quest_dialogues.emplace( Quest::Type::Lachdanan, 1 );
  d_quest_dialogues[Quest::Type::Lachdanan][0].dialogue_file_name = "/sfx/towners/storyt13.wav";
  d_quest_dialogues[Quest::Type::Lachdanan][0].raw_dialogue_text = 
    "You claim to have spoken with Lachdanan? He was a great hero during his life. Lachdanan was an honorable "
    "and just man who served his King faithfully for years. But of course, you already know that. Of those who "
    "were caught within the grasp of the King's Curse, Lachdanan would be the least likely to submit to the "
    "darkness without a fight, so I suppose that your story could be true. If I were in your place, my friend, "
    "I would find a way to release him from his torture.";

  // Armor of Valor quest
  d_quest_dialogues.emplace( Quest::Type::ArmorOfValor, 1 );
  d_quest_dialogues[Quest::Type::ArmorOfValor][0].dialogue_file_name = "/sfx/towners/storyt15.wav";
  d_quest_dialogues[Quest::Type::ArmorOfValor][0].raw_dialogue_text = 
    "The Gateway of Blood and the Halls of Fire are landmarks of mystic origin. Wherever this book you read "
    "from resides it is surely a place of great power. Legends speak of a pedestal that is carved from obsidian "
    "stone and has a pool of boiling blood atop its bone encrusted surface. There are also allusions to Stones of "
    "Blood that will open a door that guards an ancient treasure... The nature of this treasure is shrouded in "
    "speculation, my friend, but it is said that the ancient hero Arkaine placed the holy armor Valor in a secret "
    "vault. Arkaine was the first mortal to turn the tide of the Sin War and chase the legions of darkness back to "
    "the Burning Hells. Just before Arkaine died, his armor was hidden away in a secret vault. It is said that when "
    "this holy armor is again needed, a hero will arise to don Valor once more. Perhaps you are that hero...";

  // Load the gossip dialogues
  d_gossip_dialogues[0].dialogue_file_name = "/sfx/towners/storyt26.wav";
  d_gossip_dialogues[0].raw_dialogue_text =
    "While you are venturing deeper into the Labyrinth you may find tomes of great knowledge hidden there. Read them "
    "carefully for they can tell you things that even I cannot.";
  
  d_gossip_dialogues[1].dialogue_file_name = "/sfx/towners/storyt27.wav";
  d_gossip_dialogues[1].raw_dialogue_text =
    "I know of many myths and legends that may contain answers to questions that may arise in your journeys into the "
    "Labyrinth. If you come across challenges and questions to which you seek knowledge, seek me out and I will tell "
    "you what I can.";
  
  d_gossip_dialogues[2].dialogue_file_name = "/sfx/towners/storyt28.wav";
  d_gossip_dialogues[2].raw_dialogue_text =
    "Griswold - a man of great action and great courage. I bet he never told you "
    "about the time he went into the Labyrinth to save Wirt, did he? He knows his "
    "fair share of the dangers to be found there, but then again - so do you. He is "
    "a skilled craftsman, and if he claims to be able to help you in any way, you can "
    "count on his honesty and his skill.";
  
  d_gossip_dialogues[3].dialogue_file_name = "/sfx/towners/storyt29.wav";
  d_gossip_dialogues[3].raw_dialogue_text =
    "Ogden has owned and run the Rising Sun Inn and Tavern for almost four years now. "
    "He purchased it just a few short months before everything here went to hell. He "
    "and his wife Garda do not have the money to leave as they invested all they had "
    "in making a life for themselves here. He is a good man with a deep sense of "
    "responsibility.";
  
  d_gossip_dialogues[4].dialogue_file_name = "/sfx/towners/storyt30.wav";
  d_gossip_dialogues[4].raw_dialogue_text =
    "Poor Farnham. He is a disquieting reminder of the doomed assembly that entered "
    "into the Cathedral with Lazarus on that dark day. He escaped with his life, but "
    "his courage and much of his sanity were left in some dark pit. He finds comfort "
    "only at the bottom of his tankard nowadays, but there are occasional bits of truth "
    "buried within his constant ramblings.";
  
  d_gossip_dialogues[5].dialogue_file_name = "/sfx/towners/storyt31.wav";
  d_gossip_dialogues[5].raw_dialogue_text =
    "The witch, Adria, is an anomaly here in Tristram. She arrived shortly after the "
    "Cathedral was desecrated while most everyone else was fleeing. She had a small hut "
    "constructed at the edge of town, seemingly overnight, and has access to many strange "
    "and arcane artifacts and tomes of knowledge that even I have never seen before.";
  
  d_gossip_dialogues[6].dialogue_file_name = "/sfx/towners/storyt33.wav";
  d_gossip_dialogues[6].raw_dialogue_text =
    "The story of Wirt is a frightening and tragic one. He was taken from the arms of his "
    "mother and dragged into the labyrinth by the small, foul demons that wield wicked spears. "
    "There were many other children taken that day, including the son of King Leoric. The "
    "Knights of the palace went below, but never returned. The Blacksmith found the boy, "
    "but only after the foul beasts had begun to torture him for their sadistic pleasures.";
  
  d_gossip_dialogues[7].dialogue_file_name = "/sfx/towners/storyt34.wav";
  d_gossip_dialogues[7].raw_dialogue_text =
    "Ah, Pepin. I count him as a true friend - perhaps the closest I have here. He is a bit "
    "addled at times, but never a more caring or considerate soul has existed. His knowledge "
    "and skills are equaled by few, and his door is always open.";
    
  d_gossip_dialogues[8].dialogue_file_name = "/sfx/towners/storyt35.wav";
  d_gossip_dialogues[8].raw_dialogue_text =
    "Gillian is a fine woman. Much adored for her high spirits and her quick laugh, she holds "
    "a special place in my heart. She stays on at the tavern to support her elderly grandmother "
    "who is too sick to travel. I sometimes fear for her safety, but I know that any man in the "
    "village would rather die than see her harmed.";

  // Load the unused dialogues
  d_unused_dialogues[0].dialogue_file_name = "/sfx/towners/storyt03.wav";
  d_unused_dialogues[0].raw_dialogue_text = "Test";
  
  d_unused_dialogues[1].dialogue_file_name = "/sfx/towners/storyt05.wav";
  d_unused_dialogues[1].raw_dialogue_text = "Test";
  
  d_unused_dialogues[2].dialogue_file_name = "/sfx/towners/storyt06.wav";
  d_unused_dialogues[2].raw_dialogue_text = "Test";
  
  d_unused_dialogues[3].dialogue_file_name = "/sfx/towners/storyt08.wav";
  d_unused_dialogues[3].raw_dialogue_text = "Test";
  
  d_unused_dialogues[4].dialogue_file_name = "/sfx/towners/storyt09.wav";
  d_unused_dialogues[4].raw_dialogue_text = "Test";
  
  d_unused_dialogues[5].dialogue_file_name = "/sfx/towners/storyt11.wav";
  d_unused_dialogues[5].raw_dialogue_text = "Test";
  
  d_unused_dialogues[6].dialogue_file_name = "/sfx/towners/storyt16.wav";
  d_unused_dialogues[6].raw_dialogue_text = "Test";
  
  d_unused_dialogues[7].dialogue_file_name = "/sfx/towners/storyt17.wav";
  d_unused_dialogues[7].raw_dialogue_text = "Test";

  d_unused_dialogues[8].dialogue_file_name = "/sfx/towners/storyt19.wav";
  d_unused_dialogues[8].raw_dialogue_text = "Test";

  d_unused_dialogues[9].dialogue_file_name = "/sfx/towners/storyt22.wav";
  d_unused_dialogues[9].raw_dialogue_text = "Test";

  d_unused_dialogues[10].dialogue_file_name = "/sfx/towners/storyt23.wav";
  d_unused_dialogues[10].raw_dialogue_text = "Test";

  d_unused_dialogues[11].dialogue_file_name = "/sfx/towners/storyt24.wav";
  d_unused_dialogues[11].raw_dialogue_text = "Test";

  d_unused_dialogues[12].dialogue_file_name = "/sfx/towners/storyt32.wav";
  d_unused_dialogues[12].raw_dialogue_text = "Test";
}

// Get the warrior description
QString Deckard::getDescription() const
{
  return QString( "CAIN THE ELDER" );
}

// Get the number of image assets used by the object
int Deckard::getNumberOfImageAssets() const
{
  return 1;
}

// Get the image asset names used by the object
void Deckard::getImageAssetNames( QSet<QString>& image_asset_names ) const
{
  image_asset_names.insert( s_image_asset_name );
}

// Check if an image asset is used
bool Deckard::isImageAssetUsed( const QString& image_asset_name ) const
{
  return image_asset_name == s_image_asset_name;
}

// Check if the image assets have been loaded
bool Deckard::imageAssetsLoaded() const
{
  return d_sprites_loaded;
}

// Load the image asset
void Deckard::loadImageAsset( const QString&,
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
    QVector<int> source_frame_indices( 25 );

    for( int i = 0; i < source_frame_indices.size(); ++i )
      source_frame_indices[i] = i;

    game_sprite = GameSprite( s_image_asset_name, source_frame_indices );
  }

  game_sprite.setAsset( s_image_asset_name, image_asset_frames );
  game_sprite.setFrameDuration( 15 );
}

// Finalize image asset loading
void Deckard::finalizeImageAssetLoading()
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
void Deckard::dumpImageAssets()
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
void Deckard::discussQuest( const Quest::Type quest )
{
  auto dialogue_it = d_quest_dialogues.find( quest );
  
  if( dialogue_it != d_quest_dialogues.end() )
    this->playAndDisplayDialogue( dialogue_it->second.front() );
}

// Play gossip dialogue
void Deckard::gossip()
{
  static int gossip_index = 0;

  this->playAndDisplayDialogue( d_gossip_dialogues[gossip_index] );
  
  gossip_index = (gossip_index+1)%d_gossip_dialogues.size();
}

// Greet the character
void Deckard::greet()
{
  d_greeting.playSound();
}

// Get the movement speed (pixels per game tic)
qreal Deckard::getMovementSpeed() const
{
  return 0.0;
}

// Check if the NPC has dialogue for the requested quest
bool Deckard::hasDialogue( const Quest::Type quest ) const
{
  return d_quest_dialogues.find( quest ) != d_quest_dialogues.end();
}

// Load the interaction menu
NPCInteractionMenu* Deckard::createInteractionMenu( QWidget* parent, Character* character )
{
  return new DeckardInteractionMenu( parent );
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Deckard.cpp
//---------------------------------------------------------------------------//
