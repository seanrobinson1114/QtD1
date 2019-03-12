//---------------------------------------------------------------------------//
//!
//! \file   Griswold.cpp
//! \author Sean Robinson
//! \brief  The Griswold class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "Griswold.h"
#include "GriswoldInteractionMenu.h"

namespace QtD1{

// Initialize static member data
QString Griswold::s_image_asset_name = "/towners/smith/smithn.cel+levels/towndata/town.pal";

// Constructor
Griswold::Griswold( QGraphicsObject* parent )
  : NPC( parent, false ),
    d_direction_sprites(),
    d_sprites_loaded( false ),
    d_greeting(),
    d_quest_dialogues(),
    d_gossip_dialogues( 11 ),
    d_unused_dialogues( 27 )
{
  // Load the greeting
  d_greeting.setSource( "/sfx/towners/bsmith44.wav" );

  // Load the quest dialogues

  // Butcher quest
  d_quest_dialogues.emplace( Quest::Type::TheButcher, 1 );
  d_quest_dialogues[Quest::Type::TheButcher][0].dialogue_file_name = "/sfx/towners/bsmith10.wav";
  d_quest_dialogues[Quest::Type::TheButcher][0].raw_dialogue_text = 
    "I saw what Farnham calls the Butcher as it swathed a path through the bodies of "
    "my friends. He swung a cleaver as large as an axe, hewing limbs and cutting down "
    "brave men where they stood. I was separated from the fray by a host of small "
    "screeching demons and somehow found the stairway leading out. I never saw that "
    "hideous beast again, but his blood-stained visage haunts me to this day.";

  // Poisoned Water Supply quest
  d_quest_dialogues.emplace( Quest::Type::PoisonWater, 1 );
  d_quest_dialogues[Quest::Type::PoisonWater][0].dialogue_file_name = "/sfx/towners/bsmith04.wav";
  d_quest_dialogues[Quest::Type::PoisonWater][0].raw_dialogue_text = 
    "Pepin has told you the truth. We will need fresh water badly, and soon. I "
    "have tried to clear one of the smaller wells, but it reeks of stagnant filth. "
    "It must be getting clogged at the source.";

  // King Leoric quest
  d_quest_dialogues.emplace( Quest::Type::KingLeoricsCurse, 1 );
  d_quest_dialogues[Quest::Type::KingLeoricsCurse][0].dialogue_file_name = "/sfx/towners/bsmith01.wav";
  d_quest_dialogues[Quest::Type::KingLeoricsCurse][0].raw_dialogue_text = 
    "I made many of the weapons and most of the armor that King Leoric used to outfit his "
    "knights. I even crafted a huge two-handed sword of the finest mithril for him, as well "
    "as a field crown to match. I still cannot believe how he died, but it must have been "
    "some sinister force that drove him insane!";

  // Ogdens Sign quest
  d_quest_dialogues.emplace( Quest::Type::OgdensSign, 1 );
  d_quest_dialogues[Quest::Type::OgdensSign][0].dialogue_file_name = "/sfx/towners/bsmith02.wav";
  d_quest_dialogues[Quest::Type::OgdensSign][0].raw_dialogue_text = 
    "Demons stole Ogden's sign, you say? That doesn't sound much like the atrocities I've "
    "heard of - or seen. Demons are concerned with ripping out your heart, not your signpost.";

  // Magic Rock quest
  d_quest_dialogues.emplace( Quest::Type::TheMagicRock,  3 );
  d_quest_dialogues[Quest::Type::TheMagicRock][0].dialogue_file_name = "/sfx/towners/bsmith24.wav";
  d_quest_dialogues[Quest::Type::TheMagicRock][0].raw_dialogue_text = 
    "Stay for a moment - I have a story you might find interesting. A caravan that was "
    "bound for the eastern kingdoms passed through here some time ago. It was supposedly "
    "carrying a piece of the heavens that had fallen to earth! The caravan was ambushed "
    "by cloaked riders just north of here along the roadway. I searched the wreckage for "
    "this sky rock, but it was nowhere to be found. If you should find it, I believe that "
    "I can fashion something useful from it.";
  d_quest_dialogues[Quest::Type::TheMagicRock][1].dialogue_file_name = "/sfx/towners/bsmith25.wav";
  d_quest_dialogues[Quest::Type::TheMagicRock][1].raw_dialogue_text = 
    "I am still waiting for you to bring me that stone from the heavens. I know that I "
    "can make something powerful out of it.";
  d_quest_dialogues[Quest::Type::TheMagicRock][2].dialogue_file_name = "/sfx/towners/bsmith26.wav";
  d_quest_dialogues[Quest::Type::TheMagicRock][2].raw_dialogue_text = 
    "Let me see that - aye... aye, it is as I believed. Give me a moment... Ah, Here you "
    "are. I arranged pieces of the stone within a silver ring that my father left me. I "
    "hope it serves you well.";

  // Chamber of Bone quest
  d_quest_dialogues.emplace( Quest::Type::TheChamberOfBone, 1 );
  d_quest_dialogues[Quest::Type::TheChamberOfBone][0].dialogue_file_name = "/sfx/towners/bsmith07.wav";
  d_quest_dialogues[Quest::Type::TheChamberOfBone][0].raw_dialogue_text = 
    "I know nothing of this place, but you may try asking Cain. He talks about many things, "
    "and it would not surprise me if he had some answers to your question.";

  // Halls of the Blind quest
  d_quest_dialogues.emplace( Quest::Type::HallsOfTheBlind, 1 );
  d_quest_dialogues[Quest::Type::HallsOfTheBlind][0].dialogue_file_name = "/sfx/towners/bsmith12.wav";
  d_quest_dialogues[Quest::Type::HallsOfTheBlind][0].raw_dialogue_text = 
    "I am afraid that I have neither heard nor seen a place that matches your vivid "
    "description, my friend. Perhaps Cain the Storyteller could be of some help.";

  // Black mushroom quest
  d_quest_dialogues.emplace( Quest::Type::TheBlackMushroom, 1 );
  d_quest_dialogues[Quest::Type::TheBlackMushroom][0].dialogue_file_name = "/sfx/towners/bsmith19.wav";
  d_quest_dialogues[Quest::Type::TheBlackMushroom][0].raw_dialogue_text = 
    "If Adria doesn't have one of these, you can bet that's a rare thing indeed. "
    "I can offer you no more help than that, but it sounds like... a huge, "
    "gargantuan, swollen, bloated mushroom! Well, good hunting, I suppose.";

  // Anvil of Fury quest
  d_quest_dialogues.emplace( Quest::Type::TheAnvilOfFury, 3 );
  d_quest_dialogues[Quest::Type::TheAnvilOfFury][0].dialogue_file_name = "/sfx/towners/bsmith21.wav";
  d_quest_dialogues[Quest::Type::TheAnvilOfFury][0].raw_dialogue_text = 
    "Greetings! It's always a pleasure to see one of my best customers! I know "
    "that you have been venturing deeper into the Labyrinth, and there is a story "
    "I was told that you may find worth the time to listen to... One of the men who "
    "returned from the Labyrinth told me about a mystic anvil that he came across "
    "during his escape. His description reminded me of legends I had heard in my "
    "youth about the burning Hellforge where powerful weapons of magic are crafted. "
    "The legend had it that deep within the Hellforge rested the Anvil of Fury! This "
    "Anvil contained within it the very essence of the demonic underworld... It is "
    "said that any weapon crafted upon the burning Anvil is imbued with great power. "
    "If this anvil is indeed the Anvil of Fury, I may be able to make you a weapon "
    "capable of defeating even the darkest lord of Hell! Find the Anvil for me, and "
    "I'll get to work!";
  d_quest_dialogues[Quest::Type::TheAnvilOfFury][1].dialogue_file_name = "/sfx/towners/bsmith22.wav";
  d_quest_dialogues[Quest::Type::TheAnvilOfFury][1].raw_dialogue_text = 
    "Nothing yet, eh? Well, keep searching. A weapon forged upon the Anvil could be "
    "your best hope, and I am sure that I can make you one of legendary proportions.";
  d_quest_dialogues[Quest::Type::TheAnvilOfFury][2].dialogue_file_name = "/sfx/towners/bsmith23.wav";
  d_quest_dialogues[Quest::Type::TheAnvilOfFury][2].raw_dialogue_text = 
    "I can hardly believe it! This is the Anvil of Fury - good work, my friend. Now "
    "we'll show those bastards that there are no weapons in Hell more deadly than "
    "those made by men! Take this and may Light protect you.";

  // Warlord of Blood quest
  d_quest_dialogues.emplace( Quest::Type::TheWarlordOfBlood, 1 );
  d_quest_dialogues[Quest::Type::TheWarlordOfBlood][0].dialogue_file_name = "/sfx/towners/bsmith17.wav";
  d_quest_dialogues[Quest::Type::TheWarlordOfBlood][0].raw_dialogue_text = 
    "Dark and wicked legends surrounds the one Warlord of Blood. Be well prepared, "
    "my friend, for he shows no mercy or quarter.";

  // Archbishop Lazarus quest
  d_quest_dialogues.emplace( Quest::Type::ArchbishopLazarus, 1 );
  d_quest_dialogues[Quest::Type::ArchbishopLazarus][0].dialogue_file_name = "/sfx/towners/bsmith03.wav";
  d_quest_dialogues[Quest::Type::ArchbishopLazarus][0].raw_dialogue_text = 
    "I was there when Lazarus led us into the labyrinth. He spoke of holy retribution, "
    "but when we started fighting those hellspawn, he did not so much as lift his mace "
    "against them. He just ran deeper into the dim, endless chambers that were filled "
    "with the servants of darkness!";

  // Lachdanan quest
  d_quest_dialogues.emplace( Quest::Type::Lachdanan, 1 );
  d_quest_dialogues[Quest::Type::Lachdanan][0].dialogue_file_name = "/sfx/towners/bsmith13.wav";
  d_quest_dialogues[Quest::Type::Lachdanan][0].raw_dialogue_text = 
    "If it is actually Lachdanan that you have met, then I would advise that you aid "
    "him. I dealt with him on several occasions and found him to be honest and loyal "
    "in nature. The curse that fell upon the followers of King Leoric would fall "
    "especially hard upon him.";

  // Armor of Valor quest
  d_quest_dialogues.emplace( Quest::Type::ArmorOfValor, 1 );
  d_quest_dialogues[Quest::Type::ArmorOfValor][0].dialogue_file_name = "/sfx/towners/bsmith14.wav";
  d_quest_dialogues[Quest::Type::ArmorOfValor][0].raw_dialogue_text = 
    "The armor known as Valor could be what tips the scales in your favor. I will "
    "tell you that many have looked for it - including myself. Arkaine hid it well, "
    "my friend, and it will take more than a bit of luck to unlock the secrets that "
    "have kept it concealed oh, lo these many years.";

  // Load the gossip dialogues
  d_gossip_dialogues[0].dialogue_file_name = "/sfx/towners/bsmith45.wav";
  d_gossip_dialogues[0].raw_dialogue_text =
    "If you're looking for a good weapon, let me show this to you. Take "
    "your basic blunt weapon, such as a mace. Works like a charm against "
    "most of those undying horrors down there, and there's nothing better "
    "to shatter skinny little skeletons!";
  
  d_gossip_dialogues[1].dialogue_file_name = "/sfx/towners/bsmith46.wav";
  d_gossip_dialogues[1].raw_dialogue_text =
    "The axe? Aye, that's a good weapon, balanced against any foe. Look "
    "how it cleaves the air, and then imagine a nice fat demon head in "
    "its path. Keep in mind, however, that it is slow to swing - but talk "
    "about dealing a heavy blow!";
  
  d_gossip_dialogues[2].dialogue_file_name = "/sfx/towners/bsmith47.wav";
  d_gossip_dialogues[2].raw_dialogue_text =
    "Look at that edge, that balance. A sword in the right hands, and "
    "against the right foe, is the master of all weapons. Its keen blade "
    "finds little to hack or pierce on the undead, but against a living, "
    "breathing enemy, a sword will better slice their flesh!";
  
  d_gossip_dialogues[3].dialogue_file_name = "/sfx/towners/bsmith48.wav";
  d_gossip_dialogues[3].raw_dialogue_text =
    "Your weapons and armor will show the signs of your struggles against "
    "the Darkness. If you bring them to me, with a bit of work and a hot "
    "forge, I can restore them to top fighting form.";
  
  d_gossip_dialogues[4].dialogue_file_name = "/sfx/towners/bsmith49.wav";
  d_gossip_dialogues[4].raw_dialogue_text =
    "While I have to practically smuggle in the metals and tools I need "
    "from caravans that skirt the edges of our damned town, that witch, "
    "Adria, always seems to get whatever she needs. If I knew even the "
    "smallest bit about how to harness magic as she did, I could make "
    "some truly incredible things.";
  
  d_gossip_dialogues[5].dialogue_file_name = "/sfx/towners/bsmith50.wav";
  d_gossip_dialogues[5].raw_dialogue_text =
    "Gillian is a nice lass. Shame that her gammer is in such poor health "
    "or I would arrange to get both of them out of here on one of the "
    "trading caravans.";
  
  d_gossip_dialogues[6].dialogue_file_name = "/sfx/towners/bsmith51.wav";
  d_gossip_dialogues[6].raw_dialogue_text =
    "Sometimes I think that Cain talks too much, but I guess that is his "
    "calling in life. If I could bend steel as well as he can bend your ear, "
    "I could make a suit of court plate good enough for an Emperor!";
  
  d_gossip_dialogues[7].dialogue_file_name = "/sfx/towners/bsmith52.wav";
  d_gossip_dialogues[7].raw_dialogue_text =
    "I was with Farnham that night that Lazarus led us into Labyrinth. "
    "I never saw the Archbishop again, and I may not have survived if "
    "Farnham was not at my side. I fear that the attack left his soul "
    "as crippled as, well, another did my leg. I cannot fight this battle "
    "for him now, but I would if I could.";

  d_gossip_dialogues[8].dialogue_file_name = "/sfx/towners/bsmith53.wav";
  d_gossip_dialogues[8].raw_dialogue_text =
    "A good man who puts the needs of others above his own. You won't find "
    "anyone left in Tristram - or anywhere else for that matter - who has "
    "a bad thing to say about the healer.";

  d_gossip_dialogues[9].dialogue_file_name = "/sfx/towners/bsmith55.wav";
  d_gossip_dialogues[9].raw_dialogue_text =
    "That lad is going to get himself into serious trouble... or I guess "
    "I should say, again. I've tried to interest him in working here and "
    "learning an honest trade, but he prefers the high profits of dealing "
    "in goods of dubious origin. I cannot hold that against him after what "
    "happened to him, but I do wish he would at least be careful.";

  d_gossip_dialogues[10].dialogue_file_name = "/sfx/towners/bsmith56.wav";
  d_gossip_dialogues[10].raw_dialogue_text =
    "The Innkeeper has little business and no real way of turning a profit. "
    "He manages to make ends meet by providing food and lodging for those who "
    "occasionally drift through the village, but they are as likely to sneak "
    "off into the night as they are to pay him. If it weren't for the stores "
    "of grains and dried meats he kept in his cellar, why, most of us would "
    "have starved during that first year when the entire countryside was "
    "overrun by demons.";

  // Load the unused dialogues
  d_unused_dialogues[0].dialogue_file_name = "/sfx/towners/bsmith05.wav";
  d_unused_dialogues[0].raw_dialogue_text = "Test";
  
  d_unused_dialogues[1].dialogue_file_name = "/sfx/towners/bsmith06.wav";
  d_unused_dialogues[1].raw_dialogue_text = "Test";
  
  d_unused_dialogues[2].dialogue_file_name = "/sfx/towners/bsmith08.wav";
  d_unused_dialogues[2].raw_dialogue_text = "Test";
  
  d_unused_dialogues[3].dialogue_file_name = "/sfx/towners/bsmith09.wav";
  d_unused_dialogues[3].raw_dialogue_text = "Test";
  
  d_unused_dialogues[4].dialogue_file_name = "/sfx/towners/bsmith11.wav";
  d_unused_dialogues[4].raw_dialogue_text = "Test";
  
  d_unused_dialogues[5].dialogue_file_name = "/sfx/towners/bsmith15.wav";
  d_unused_dialogues[5].raw_dialogue_text = "Test";
  
  d_unused_dialogues[6].dialogue_file_name = "/sfx/towners/bsmith16.wav";
  d_unused_dialogues[6].raw_dialogue_text = "Test";
  
  d_unused_dialogues[7].dialogue_file_name = "/sfx/towners/bsmith18.wav";
  d_unused_dialogues[7].raw_dialogue_text = "Test";

  d_unused_dialogues[8].dialogue_file_name = "/sfx/towners/bsmith20.wav";
  d_unused_dialogues[8].raw_dialogue_text = "Test";

  d_unused_dialogues[9].dialogue_file_name = "/sfx/towners/bsmith27.wav";
  d_unused_dialogues[9].raw_dialogue_text = "Test";

  d_unused_dialogues[10].dialogue_file_name = "/sfx/towners/bsmith28.wav";
  d_unused_dialogues[10].raw_dialogue_text = "Test";

  d_unused_dialogues[11].dialogue_file_name = "/sfx/towners/bsmith29.wav";
  d_unused_dialogues[11].raw_dialogue_text = "Test";

  d_unused_dialogues[12].dialogue_file_name = "/sfx/towners/bsmith30.wav";
  d_unused_dialogues[12].raw_dialogue_text = "Test";

  d_unused_dialogues[13].dialogue_file_name = "/sfx/towners/bsmith31.wav";
  d_unused_dialogues[13].raw_dialogue_text = "Test";

  d_unused_dialogues[14].dialogue_file_name = "/sfx/towners/bsmith32.wav";
  d_unused_dialogues[14].raw_dialogue_text = "Test";

  d_unused_dialogues[15].dialogue_file_name = "/sfx/towners/bsmith33.wav";
  d_unused_dialogues[15].raw_dialogue_text = "Test";
  
  d_unused_dialogues[16].dialogue_file_name = "/sfx/towners/bsmith34.wav";
  d_unused_dialogues[16].raw_dialogue_text = "Test";

  d_unused_dialogues[17].dialogue_file_name = "/sfx/towners/bsmith35.wav";
  d_unused_dialogues[17].raw_dialogue_text = "Test";

  d_unused_dialogues[18].dialogue_file_name = "/sfx/towners/bsmith36.wav";
  d_unused_dialogues[18].raw_dialogue_text = "Test";

  d_unused_dialogues[19].dialogue_file_name = "/sfx/towners/bsmith37.wav";
  d_unused_dialogues[19].raw_dialogue_text = "Test";

  d_unused_dialogues[20].dialogue_file_name = "/sfx/towners/bsmith38.wav";
  d_unused_dialogues[20].raw_dialogue_text = "Test";

  d_unused_dialogues[21].dialogue_file_name = "/sfx/towners/bsmith39.wav";
  d_unused_dialogues[21].raw_dialogue_text = "Test";

  d_unused_dialogues[22].dialogue_file_name = "/sfx/towners/bsmith40.wav";
  d_unused_dialogues[22].raw_dialogue_text = "Test";

  d_unused_dialogues[23].dialogue_file_name = "/sfx/towners/bsmith41.wav";
  d_unused_dialogues[23].raw_dialogue_text = "Test";

  d_unused_dialogues[24].dialogue_file_name = "/sfx/towners/bsmith42.wav";
  d_unused_dialogues[24].raw_dialogue_text = "Test";

  d_unused_dialogues[25].dialogue_file_name = "/sfx/towners/bsmith43.wav";
  d_unused_dialogues[25].raw_dialogue_text = "Test";

  d_unused_dialogues[26].dialogue_file_name = "/sfx/towners/bsmith54.wav";
  d_unused_dialogues[26].raw_dialogue_text = "Test";
}

// Get the warrior description
QString Griswold::getDescription() const
{
  return QString( "GRISWOLD THE BLACKSMITH" );
}

// Get the number of image assets used by the object
int Griswold::getNumberOfImageAssets() const
{
  return 1;
}

// Get the image asset names used by the object
void Griswold::getImageAssetNames( QSet<QString>& image_asset_names ) const
{
  image_asset_names.insert( s_image_asset_name );
}

// Check if an image asset is used
bool Griswold::isImageAssetUsed( const QString& image_asset_name ) const
{
  return image_asset_name == s_image_asset_name;
}

// Check if the image assets have been loaded
bool Griswold::imageAssetsLoaded() const
{
  return d_sprites_loaded;
}

// Load the image asset
void Griswold::loadImageAsset( const QString&,
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
void Griswold::finalizeImageAssetLoading()
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
void Griswold::dumpImageAssets()
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
void Griswold::discussQuest( const Quest::Type quest )
{
  auto dialogue_it = d_quest_dialogues.find( quest );
  
  if( dialogue_it != d_quest_dialogues.end() )
    this->playAndDisplayDialogue( dialogue_it->second.front() );
}

// Play gossip dialogue
void Griswold::gossip()
{
  static int gossip_index = 0;

  this->playAndDisplayDialogue( d_gossip_dialogues[gossip_index] );
  
  gossip_index = (gossip_index+1)%d_gossip_dialogues.size();
}

// Greet the character
void Griswold::greet()
{
  d_greeting.playSound();
}

// Get the movement speed (pixels per game tic)
qreal Griswold::getMovementSpeed() const
{
  return 0.0;
}

// Check if the NPC has dialogue for the requested quest
bool Griswold::hasDialogue( const Quest::Type quest ) const
{
  return d_quest_dialogues.find( quest ) != d_quest_dialogues.end();
}

// Load the interaction menu
NPCInteractionMenu* Griswold::createInteractionMenu( QWidget* parent )
{
  return new GriswoldInteractionMenu( parent );
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Griswold.cpp
//---------------------------------------------------------------------------//
