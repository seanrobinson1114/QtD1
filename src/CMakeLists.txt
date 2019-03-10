# Create the qtd1 core library
ADD_LIBRARY(qtd1_core
  MPQProperties.cpp
  MPQFileEngine.cpp
  CustomMPQFileHeader.cpp
  MPQHandler.cpp

  CelPalette.cpp
  StandardImageProperties.cpp
  CelImageProperties.cpp
  Cl2ImageProperties.cpp
  CelImagePixelSetter.cpp
  CelFrameDecoder.cpp
  CelDecoder.cpp

  AVFrameWrapper.cpp
  AVPacketWrapper.cpp
  AVPictureWrapper.cpp
  AVIOContextWrapper.cpp
  SWRContextWrapper.cpp
  SWSContextWrapper.cpp
  VideoFile.cpp
  AudioStream.cpp
  VideoStream.cpp
  Video.cpp

  MixChunkWrapper.cpp
  MixMusicWrapper.cpp
  AudioDevice.cpp
  Sound.cpp
  Music.cpp
  Viewport.cpp
  FrameLoader.cpp
  PCXFrameLoader.cpp
  CelFrameLoader.cpp
  UIArtLoader.cpp
  MenuSprite.cpp
  MenuPushButton.cpp
  PentSpinMenuPushButton.cpp
  SmallPentSpinMenuPushButton.cpp
  LargePentSpinMenuPushButton.cpp
  PentSpinMenuPushButtonBox.cpp
  CursorDatabase.cpp

  BitmapFont.cpp
  11BitmapFont.cpp
  White11BitmapFont.cpp
  Blue11BitmapFont.cpp
  Gold11BitmapFont.cpp
  Gold16BitmapFont.cpp
  Silver16BitmapFont.cpp
  Gold22BitmapFont.cpp
  Gold24BitmapFont.cpp
  Silver24BitmapFont.cpp
  Gold30BitmapFont.cpp
  Silver30BitmapFont.cpp
  Gold42BitmapFont.cpp
  Silver42BitmapFont.cpp
  Gold45BitmapFont.cpp
  BitmapText.cpp

  GameSpriteData.cpp
  GameSprite.cpp
  Direction.cpp
  Quest.cpp
  QuestManager.cpp
  QuestMenuPushButton.cpp
  QuestPentSpinMenuPushButtonBox.cpp
  CharacterStats.cpp
  Inventory.cpp
  RogueInventory.cpp
  SorcererInventory.cpp
  WarriorInventory.cpp
  SpellBook.cpp
  SpellBookPage.cpp
  RogueSpellBook.cpp
  SorcererSpellBook.cpp
  WarriorSpellBook.cpp
  QuestLog.cpp
  QuestTheButcher.cpp
  QuestPoisonedWaterSupply.cpp
  QuestTheCurseOfKingLeoric.cpp
  QuestGharbadTheWeak.cpp
  QuestOgdensSign.cpp
  QuestTheMagicRock.cpp
  QuestValor.cpp
  QuestTheChamberOfBone.cpp
  QuestHallsOfTheBlind.cpp
  QuestZharTheMad.cpp
  QuestBlackMushroom.cpp
  QuestAnvilOfFury.cpp
  QuestWarlordOfBlood.cpp
  QuestLachdanan.cpp
  QuestArchbishopLazarus.cpp
  QuestDiablo.cpp
  LevelObject.cpp
  InteractiveLevelObject.cpp
  ImageAssetLoader.cpp
  BasicActor.cpp
  ActorAttackingTargetTransition.cpp
  BasicActorStandingByTargetTransition.cpp
  Actor.cpp
  Character.cpp
  CharacterFrontendProxy.cpp
  Rogue.cpp
  Sorcerer.cpp
  Warrior.cpp
  NPCInteractionMenu.cpp
  NPCDialogueBox.cpp
  NPC.cpp
  Farnham.cpp
  Adria.cpp
  Ogden.cpp
  LevelPillarData.cpp
  LevelPillar.cpp
  TownLevelPillar.cpp
  LevelPillarFactory.cpp
  LevelSquare.cpp
  LevelSquareFactory.cpp
  LevelSector.cpp
  LevelSectorFactory.cpp
  Level.cpp
  Town.cpp
  CathedralLevel.cpp
  CatacombLevel.cpp
  CaveLevel.cpp
  HellLevel.cpp
  LoadingScreen.cpp
  Game.cpp
  ControlPanel.cpp
  GameFrontendProxy.cpp
  MainWindow.cpp
  MainWindowFrontendProxy.cpp

  Grid.cpp
  GridElement.cpp
  PathNode.cpp)

SET_TARGET_PROPERTIES(qtd1_core PROPERTIES COMPILE_FLAGS "${QTD1_CXX_FLAGS}")

# Create the qtd1 plugins
ADD_LIBRARY(qtd1_pcx_plugin STATIC PCXHandler.cpp)
SET_TARGET_PROPERTIES(qtd1_pcx_plugin PROPERTIES COMPILE_FLAGS "${QTD1_CXX_FLAGS}")

ADD_LIBRARY(qtd1_cel_plugin STATIC
  CelHandler.cpp
  MPQHandler.cpp
  CelPalette.cpp
  CelImageProperties.cpp
  Cl2ImageProperties.cpp
  CelImagePixelSetter.cpp
  CelFrameDecoder.cpp
  CelDecoder.cpp)
SET_TARGET_PROPERTIES(qtd1_cel_plugin PROPERTIES COMPILE_FLAGS "${QTD1_CXX_FLAGS}")

# Create the qtd1 executable
ADD_EXECUTABLE(qtd1 qtd1.cpp)
SET_TARGET_PROPERTIES(qtd1 PROPERTIES COMPILE_FLAGS "${QTD1_CXX_FLAGS}")
TARGET_LINK_LIBRARIES(qtd1 qtd1_core qtd1_pcx_plugin qtd1_cel_plugin)

# Install the libraries
INSTALL(TARGETS qtd1_core qtd1_pcx_plugin qtd1_cel_plugin
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

# Install the qtd1 executable
INSTALL(TARGETS qtd1
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
