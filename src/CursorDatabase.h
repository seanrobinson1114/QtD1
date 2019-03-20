//---------------------------------------------------------------------------//
//!
//! \file   CursorDatabase.h
//! \author Alex Robinson
//! \brief  The cursor database class declaration
//!
//---------------------------------------------------------------------------//

#ifndef CURSOR_DATABASE_H
#define CURSOR_DATABASE_H

// Std Lib Includes
#include <memory>

// Qt Includes
#include <QString>
#include <QImage>
#include <QtDeclarative/QDeclarativeView>

// QtD1 Includes
#include "QMLRegistrationHelper.h"

namespace QtD1{

//! The cursor database class
class CursorDatabase : public QObject
{
  Q_OBJECT
  Q_IMPORT_ALIAS( "QtD1", 1, 0, "CursorDatabase" )

public:

  //! The game cursor enum
  enum GameCursor
  {
    DefaultGameCursor = 0,
    IdentifyItemGameCursor = 1,
    RepairItemGameCursor = 2,
    RechargeItemGameCursor = 3,
    UnlockChestGameCursor = 4,
    DisarmTrapGameCursor = 5,
    TelekinesisGameCursor = 6,
    HealTargetGameCursor = 7,
    SelectTargetGameCursor = 8,
    DeselectTargetGameCursor = 9,
    LoadingGameCursor = 10,
    ManaPotionGameCursor = 11,
    WhiteScrollGameCursor = 12,
    YellowScrollGameCursor = 13,
    BlueScrollGameCursor = 14,
    SmallGoldPileGameCursor = 15,
    MediumGoldPileGameCursor = 16,
    LargeGoldPileGameCursor = 17,
    BasicGoldRingGameCursor = 18,
    RubyGoldRingGameCursor = 19,
    ThornyRingGameCursor = 20,
    SaphireSilverRingGameCursor = 21,
    SkullRingGameCursor = 22,
    SilverRingGameCursor = 23,
    MeteorGoldRingGameCursor = 24,
    AmberGoldRingGameCursor = 25,
    ThinRedPotionGameCursor = 26,
    RainbowPotionGameCursor = 27,
    GreenPotionGameCursor = 28,
    SaphireSteelRingGameCursor = 29,
    SeveredEarWithSilverRingGameCursor = 30,
    SeveredEarGameCursor = 31,
    SeveredEarWithGoldRingGameCursor = 32,
    GoldOrbGameCursor = 33,
    GoldCubeGameCursor = 34,
    GoldPyramidGameCursor = 35,
    FlawlessRubyGameCursor = 36,
    RubySphereGameCursor = 37,
    SaphireCubeGameCursor = 38,
    OrangePyramidGameCursor = 39,
    ThinBlackPotionGameCursor = 40,
    BlackPotionGameCursor = 41,
    WhitePotionGameCursor = 42,
    SmallHealthPostionGameCursor = 43,
    SmallRejuvenationPotionGameCursor = 44,
    OrangePotionGameCursor = 45,
    HealthPotionGameCursor = 46,
    LargeBlackPotionGameCursor = 47,
    LargeRejuvenationPotionGameCursor = 48,
    LargeWhitePotionGameCursor = 49,
    SmallManaPotionGameCursor = 50,
    BrainGameCursor = 51,
    ClawsGameCursor = 52,
    BeakGameCursor = 53,
    LoafGameCursor = 54,
    SilverLoopAmuletGameCursor = 55,
    SilverBibNecklaceGameCursor = 56,
    LeatherWithGoldClaspNecklaceGameCursor = 57,
    GoldSaphireBeetleGameCursor = 58,
    SilverCrossAmuletGameCursor = 59,
    LeatherPurseGameCursor = 60,
    WavyDaggerGameCursor = 61,
    BasicDaggerGameCursor = 62,
    WineBottleGameCursor = 63,
    OrnateDaggerGameCursor = 64,
    BasicShortSwordGameCursor = 65,
    FistSpikeGameCursor = 66,
    BasicSwordGameCursor = 67,
    OrnateSwordGameCursor = 68,
    FangedSwordGameCursor = 69,
    BasicMaceGameCursor = 70,
    OrnateShortSwordGameCursor = 71,
    BlackAndGoldShortSwordGameCursor = 72,
    ScimitarGameCursor = 73,
    SpikeBallMaceGameCursor = 74,
    SilverAndLeatherDaggerGameCursor = 75,
    BlueSteelShortSwordGameCursor = 76,
    BasicSpikedClubRightGameCursor = 77,
    HandGuardShortSwordGameCursor = 78,
    GoldAndBlueSteelShortSwordGameCursor = 79,
    BoneClubGameCursor = 80,
    OrnateSpikedClubGameCursor = 81,
    BasicSpikedClubLeftGameCursor = 82,
    ThinScimitarGameCursor = 83,
    BlackAndBlueSteelShortSwordGameCursor = 84,
    BlackBoneShortSwordGameCursor = 85,
    FullHelmGameCursor = 86,
    MeteorGameCursor = 87,
    SkeletonKingCrownGameCursor = 88,
    SkullCircletGameCursor = 89,
    SamuraiHelmetGameCursor = 90,
    JesterHatGameCursor = 91,
    GoldRubyFullHelmGameCursor = 92,
    RomanFullHelmGameCursor = 93,
    BucklerGameCursor = 94,
    WingedHelmGameCursor = 95,
    OrnateWingedHelmGameCursor = 96,
    BlackSpellBookGameCursor = 97,
    RedSpellBookGameCursor = 98,
    BlueSpellBookGameCursor = 99,
    BlackMushroomGameCursor = 100,
    SpikedGoldSkullCapGameCursor = 101,
    LeatherCapGameCursor = 102,
    RaggedGoldShieldGameCursor = 103,
    SpikedRedSkullCapGameCursor = 104,
    TatteredRobesGameCursor = 105,
    GoldCrownGameCursor = 106,
    MapGameCursor = 107,
    DustyBookGameCursor = 108,
    SilverRomanFullHelmGameCursor = 109,
    GoldSamuraiHelmetGameCursor = 110,
    BlueGoldShieldGameCursor = 111,
    DoubleAxeGameCursor = 112,
    WoodGoldBowGameCursor = 113,
    BlackGoldPlateMailGameCursor = 114,
    SilverAxeGameCursor = 115,
    WoodSilverSmallShieldGameCursor = 116,
    BloodyCleaverGameCursor = 117,
    BlackLeatherArmorGameCursor = 118,
    BoneBowGameCursor = 119,
    WoodLeatherStaffGameCursor = 120,
    LeatherBoundOrnateSwordGameCursor = 121,
    BlackGoldChainMailGameCursor = 122,
    SteelAxeGameCursor = 123,
    KiteShieldGameCursor = 124,
    ChainMailGameCursor = 125,
    BlackGoldOrnateLargeShieldGameCursor = 126,
    SkullShieldGameCursor = 127,
    DemonShieldGameCursor = 128,
    WoodBowGameCursor = 129,
    WingedBowGameCursor = 130,
    MetalSpikeBowGameCursor = 131,
    WarHammerGameCursor = 132,
    MaulGameCursor = 133,
    GoldRubyStaffGameCursor = 134,
    SteelLeatherStaffGameCursor = 135,
    WitchDoctorStaffGameCursor = 136,
    InnSigneGameCursor = 137,
    RedLeatherArmorGameCursor = 138,
    RagsGameCursor = 139,
    StuddedLeatherArmorGameCursor = 140,
    TripleSpikeBallFlailGameCursor = 141,
    SingleSpikeBallFlailGameCursor = 142,
    BlackGoldCrossTowerShieldGameCursor = 143,
    SteelLeatherBowGameCursor = 144,
    SamuraiSwordGameCursor = 145,
    LeatherArmorGameCursor = 146,
    SamuraiArmorGameCursor = 147,
    WhiteRobeGameCursor = 148,
    BlackGoldRobeGameCursor = 149,
    GoldStuddedLeatherArmorGameCursor = 150,
    AnvilGameCursor = 151,
    LargeSteelAxeGameCursor = 152,
    SteelDoubleAxeGameCursor = 153,
    OrnateSteelDoubleAxeGameCursor = 154,
    LargeIronAxeGameCursor = 155,
    OrnateBlackIronClubGameCursor = 156,
    GoldLionKiteShieldGameCursor = 157,
    BlackEagleKiteShieldGameCursor = 158,
    GoldGriffinKiteShieldGameCursor = 159,
    WhiteCloakGameCursor = 160,
    RedCapeGameCursor = 161,
    SteelFullPlateArmorGameCursor = 162,
    GothicArmorGameCursor = 163,
    GothicBreastPlateGameCursor = 164,
    OrnateBreastPlateGameCursor = 165,
    GoldRubySkullStaffGameCursor = 166,
    OrnateSteelAxeGameCursor = 167,
    SteelLightArmorGameCursor = 168,
    CrossbowGameCursor = 169,
    OrnateLightArmorGameCursor = 170,
    OrnateExecutionersSwordGameCursor = 171,
    OrnateSamuraiSwordGameCursor = 172,
    OrnateMaceGameCursor = 173,
    OrnateGoldDoubleAxeGameCursor = 174,
    OrnateGoldLeatherBowGameCursor = 175,
    BlueGoldBowGameCursor = 176,
    SpikedStaffGameCursor = 177,
    OrnateGoldBowGameCursor = 178
  };
  Q_ENUMS(GameCursor)

  //! Get the singleton instance
  static CursorDatabase* getInstance();

  //! Default Constructor (this is only included for qml registration)
  CursorDatabase( QObject* parent = 0 );

  //! Destructor
  ~CursorDatabase()
  { /* ... */ }

  //! Get the cursor pixmap
  QPixmap getCursorPixmap( const GameCursor cursor ) const;

  //! Set the widget that will be managed
  void setWidgetToManage( QWidget* widget );

  //! Reset the cursor on the managed widget
  void resetCursorOnManagedWidget() const;

  //! Reset the cursor on the managed widget
  Q_INVOKABLE static void resetCursor();

  //! Activate the UI cursor on the managed widget
  void activateUICursorOnManagedWidget() const;

  //! Activate the UI cursor on the managed widget
  Q_INVOKABLE static void activateUICursor();

  //! Activate the desired game cursor on the managed widget
  void activateGameCursorOnManagedWidget( const GameCursor cursor ) const;

  //! Activate the desired game cursor on the managed widget
  Q_INVOKABLE static void activateGameCursor( const GameCursor cursor );

private:

  // Constructor
  CursorDatabase( const bool load_cursors );

  // The singleton instance
  static std::unique_ptr<CursorDatabase> s_instance;

  // The ui cursor
  QCursor d_ui_cursor;
  
  // The game cursors
  QVector<QCursor> d_game_cursors;

  // The parent graphics item
  QWidget* d_managed_widget;
};
  
} // end QtD1 namespace

#endif // end CURSOR_DATABASE_H

//---------------------------------------------------------------------------//
// end CursorDatabase.h
//---------------------------------------------------------------------------//
