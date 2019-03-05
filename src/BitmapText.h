//---------------------------------------------------------------------------//
//!
//! \file   BitmapText.h
//! \author Alex Robinson
//! \brief  The bitmap text class declaration
//!
//---------------------------------------------------------------------------//

#ifndef BITMAP_TEXT_H
#define BITMAP_TEXT_H

// Std Lib Includes
#include <map>
#include <memory>

// Qt Includes
#include <QDeclarativeItem>
#include <QString>
#include <QVector>

// QtD1 Includes
#include "BitmapFont.h"
#include "Viewport.h"
#include "QMLRegistrationHelper.h"

namespace QtD1{

//! The text image class
class BitmapText : public QDeclarativeItem
{
  Q_OBJECT
  Q_PROPERTY(QString text READ getText WRITE setText)
  Q_PROPERTY(QString font READ getFontName WRITE setFontName)
  Q_PROPERTY(TextBehavior textBehavior READ getTextBehavior WRITE setTextBehavior)
  Q_PROPERTY(QtD1::Viewport::DisplayPolicy display READ getDisplayPolicy WRITE setDisplayPolicy)
  Q_PROPERTY(int lineCount READ getLineCount)
  Q_PROPERTY(qreal paintedLineHeight READ getPaintedLineHeight)
  Q_PROPERTY(qreal paintedLineWidth READ getPaintedLineWidth)
  Q_PROPERTY(int lineHeight READ getLineHeight)
  Q_PROPERTY(int lineWidth READ getLineWidth)
  Q_PROPERTY(int containerWidth READ getContainerWidth WRITE setContainerWidth )
  Q_IMPORT_ALIAS( "QtD1", 1, 0, "BitmapText" )

public:

  //! The text behavior enum
  enum TextBehavior{
    NoTextWrap,
    TextWrap,
    WordWrap
  };
  Q_ENUMS( TextBehavior )

  //! Constructor
  BitmapText( QDeclarativeItem* parent = 0 );

  //! Destructor
  ~BitmapText()
  { /* ...*/ }

  //! Get the text
  QString getText() const;

  //! Set the text
  void setText( const QString& text );

  //! Set the text without wrapping
  void setTextWithNoWrap( const QString& text );

  //! Set the text with text wrapping
  void setTextWithTextWrap( const QString& text );

  //! Set the text with word wrapping
  void setTextWithWordWrap( const QString& text );

  //! Get the font name
  QString getFontName() const;

  //! Set the font name
  void setFontName( const QString& font_name );

  //! Get the text behavior policy
  TextBehavior getTextBehavior() const;

  //! Set the text behavior policy
  void setTextBehavior( const TextBehavior behavior );

  //! Get the display policy
  Viewport::DisplayPolicy getDisplayPolicy() const;

  //! Set the display policy
  void setDisplayPolicy( const Viewport::DisplayPolicy policy );

  //! Set the text mixing color
  void setMixingColor( const QColor& color );

  //! Get the number of lines
  int getLineCount() const;

  //! Get the painted line height
  qreal getPaintedLineHeight() const;

  //! Get the painted line width
  qreal getPaintedLineWidth() const;

  //! Get the line height
  int getLineHeight() const;

  //! Get the line width
  int getLineWidth() const;

  //! Get the container width
  int getContainerWidth() const;

  //! Set the container width
  void setContainerWidth( const int width );

  //! Get the text pixmap
  QPixmap getPixmap() const;

  //! Paint the text bitmap
  void paint( QPainter* painter,
              const QStyleOptionGraphicsItem* option,
              QWidget* widget = 0 ) override;

  //! Register the font
  template<typename FontClass>
  static void registerFont( const QString& font_alias );

  //! Load standard fonts
  static void loadStandardFonts();

public slots:

  // Load the text bitmap
  void load();

private:

  // The registered fonts
  static std::map<QString,BitmapFont*> s_registered_fonts;

  // The text
  QStringList d_text_lines;

  // The text image
  QPixmap d_text_image;

  // The container width
  int d_container_width;

  // The text behavior
  BitmapText::TextBehavior d_text_behavior;

  // The display policy
  Viewport::DisplayPolicy d_display_policy;

  // The text source viewport
  QRectF d_text_source_viewport;

  // The text target viewport
  QRectF d_text_target_viewport;

  // The mixing color
  QColor d_mixing_color;

  // The font name
  QString d_font_name;

  // The bitmap font
  BitmapFont* d_font;
};

// Register the font
/*! \details Using an alias again will override any previously set fonts
 * registered with that alias. All font classes must be singletons.
 */
template<typename FontClass>
inline void BitmapText::registerFont( const QString& font_alias )
{
  s_registered_fonts[font_alias] = FontClass::getInstance();
}

} // end QtD1 namespace

#endif // end BITMAP_TEXT_H

//---------------------------------------------------------------------------//
// end BitmapText.h
//---------------------------------------------------------------------------//
