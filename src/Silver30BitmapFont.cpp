//---------------------------------------------------------------------------//
//!
//! \file   Silver30BitmapFont.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The silver 30 bitmap font class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "Silver30BitmapFont.h"

namespace QtD1{

// Initialize static members
std::unique_ptr<Silver30BitmapFont> Silver30BitmapFont::s_instance;

// The character widths
const QVector<int> Silver30BitmapFont::s_widths = {
  /*ASCII Table Index : ASCII Table Value*/
  /*0:*/     0,
  /*1:*/     0,
  /*2:*/     0,
  /*3:*/     0,
  /*4:*/     0,
  /*5:*/     0,
  /*6:*/     0,
  /*7:*/     0,
  /*8:*/     0,
  /*9:*/     0,
  /*10:*/    0,
  /*11:*/    0,
  /*12:*/    0,
  /*13:*/    0,
  /*14:*/    0,
  /*15:*/    0,
  /*16:*/    0,
  /*17:*/    0,
  /*18:*/    0,
  /*19:*/    0,
  /*20:*/    0,
  /*21:*/    0,
  /*22:*/    0,
  /*23:*/    0,
  /*24:*/    0,
  /*25:*/    0,
  /*26:*/    0,
  /*27:*/    0,
  /*28:*/    0,
  /*29:*/    0,
  /*30:*/    0,
  /*31:*/    0,
  /*32: */  13,
  /*33:!*/   9,
  /*34:"*/  15,
  /*35:#*/  15,
  /*36:$*/  16,
  /*37:%*/  24,
  /*38:&*/  22,
  /*39:'*/   9,
  /*40:(*/   11,
  /*41:)*/   10,
  /*42:**/   12,
  /*43:+*/  13,
  /*44:,*/   9,
  /*45:-*/   11,
  /*46:.*/   9,
  /*47:/*/  17,
  /*48:0*/  23,
  /*49:1*/  10,
  /*50:2*/  16,
  /*51:3*/  16,
  /*52:4*/  17,
  /*53:5*/  16,
  /*54:6*/  15,
  /*55:7*/  16,
  /*56:8*/  16,
  /*57:9*/  15,
  /*58::*/   9,
  /*59:;*/   9,
  /*60:<*/   11,
  /*61:=*/   13,
  /*62:>*/   11,
  /*63:?*/  16,
  /*64:@*/  22,
  /*65:A*/  21,
  /*66:B*/  16,
  /*67:C*/  18,
  /*68:D*/  19,
  /*69:E*/  16,
  /*70:F*/  16,
  /*71:G*/  18,
  /*72:H*/  17,
  /*73:I*/   9,
  /*74:J*/   9,
  /*75:K*/  18,
  /*76:L*/  15,
  /*77:M*/  23,
  /*78:N*/  20,
  /*79:O*/  22,
  /*80:P*/  15,
  /*81:Q*/  22,
  /*82:R*/  19,
  /*83:S*/  15,
  /*84:T*/  21,
  /*85:U*/  24,
  /*86:V*/  24,
  /*87:W*/  32,
  /*88:X*/  23,
  /*89:Y*/  23,
  /*90:Z*/  17,
  /*91:[*/   10,
  /*92:\*/  17,
  /*93:]*/   9,
  /*94:^*/   11,
  /*95:_*/  16,
  /*96:`*/   9,
  /*97:a*/  18,
  /*98:b*/  13,
  /*99:c*/  16,
  /*100:d*/ 17,
  /*101:e*/ 14,
  /*102:f*/ 13,
  /*103:g*/ 16,
  /*104:h*/ 15,
  /*105:i*/  8,
  /*106:j*/  9,
  /*107:k*/ 15,
  /*108:l*/ 13,
  /*109:m*/ 20,
  /*110:n*/ 17,
  /*111:o*/ 19,
  /*112:p*/ 14,
  /*113:q*/ 19,
  /*114:r*/ 17,
  /*115:s*/ 14,
  /*116:t*/ 18,
  /*117:u*/ 20,
  /*118:v*/ 20,
  /*119:w*/ 25,
  /*120:x*/ 19,
  /*121:y*/ 20,
  /*122:z*/ 15,
            13,
            17,
  /*123:{*/ 13,
  /*124:|*/ 12,
  /*125:}*/ 9,
  /*126:~*/ 9,
  /*127:*/  10,
  /*128:*/  14,
  /*129:*/  15,
  /*130:*/  15,
  /*131:*/  23,
  /*132:*/  8,
  /*133:*/  13,
  /*134:*/  11,
  /*135:*/  22,
  /*136:*/  15,
  /*137:*/  15,
  /*138:*/  19,
  /*139:*/  11,
  /*140:*/  22,
  /*141:*/  11,
  /*142:*/  12,
  /*143:*/  16,
  /*144:*/  12,
  /*145:*/  12,
  /*146:*/  10,
  /*147:*/  25,
  /*148:*/  16,
  /*149:*/  15,
  /*150:*/  16,
  /*151:*/  8,
  /*152:*/  15,
  /*153:*/  14,
  /*154:*/  21,
  /*155:*/  21,
  /*156:*/  23,
  /*157:*/  16,
  /*158:*/  23,
  /*159:*/  24,
  /*160:*/  23,
  /*161:*/  23,
  /*162:*/  23,
  /*163:*/  23,
  /*164:*/  22,
  /*165:*/  18,
  /*166:*/  16,
  /*167:*/  16,
  /*168:*/  16,
  /*169:*/  16,
  /*170:*/  10,
  /*171:*/  10,
  /*172:*/  10,
  /*173:*/  11,
  /*174:*/  19,
  /*175:*/  20,
  /*176:*/  22,
  /*177:*/  22,
  /*178:*/  21,
  /*179:*/  22,
  /*180:*/  22,
  /*181:*/  16,
  /*182:*/  22,
  /*183:*/  24,
  /*184:*/  25,
  /*185:*/  24,
  /*186:*/  24,
  /*187:*/  23,
  /*188:*/  15,
  /*189:*/  17,
  /*190:*/  19,
  /*191:*/  19,
  /*192:*/  19,
  /*193:*/  19,
  /*194:*/  19,
  /*195:*/  20,
  /*196:*/  19,
  /*197:*/  16,
  /*198:*/  14,
  /*199:*/  13,
  /*200:*/  13,
  /*201:*/  13,
  /*202:*/  9,
  /*203:*/  9,
  /*204:*/  10,
  /*205:*/  10,
  /*206:*/  15,
  /*207:*/  17,
  /*208:*/  19,
  /*209:*/  19,
  /*210:*/  19,
  /*211:*/  19,
  /*212:*/  19,
  /*213:*/  15,
  /*214:*/  19,
  /*215:*/  20,
  /*216:*/  20,
  /*217:*/  20,
  /*218:*/  20,
  /*219:*/  19,
  /*220:*/  13,
  /*221:*/  19,
  /*224:*/   0,
  /*225:*/   0,
  /*226:*/   0,
  /*227:*/   0,
  /*228:*/   0,
  /*229:*/   0,
  /*230:*/   0,
  /*231:*/   0,
  /*232:*/   0,
  /*233:*/   0,
  /*234:*/   0,
  /*235:*/   0,
  /*236:*/   0,
  /*237:*/   0,
  /*238:*/   0,
  /*239:*/   0,
  /*240:*/   0,
  /*241:*/   0,
  /*242:*/   0,
  /*243:*/   0,
  /*244:*/   0,
  /*245:*/   0,
  /*246:*/   0,
  /*247:*/   0,
  /*248:*/   0,
  /*249:*/   0,
  /*250:*/   0,
  /*251:*/   0,
  /*252:*/   0,
  /*253:*/   0,
  /*254:*/   0,
  /*255:*/   0};

// Constructor
Silver30BitmapFont::Silver30BitmapFont()
  : BitmapFont( this->getName(), s_widths )
{ /* ... */ }

// Get the Silver30BitmapFont instance
Silver30BitmapFont* Silver30BitmapFont::getInstance()
{
  // Just-in-time initialization
  if( !s_instance )
    s_instance.reset( new Silver30BitmapFont );

  return s_instance.get();
}

// Get the font name
QString Silver30BitmapFont::getName() const
{
  return "/ui_art/font30s.pcx";
}

// Return the font size
int Silver30BitmapFont::getSize() const
{
  return 30;
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Silver30BitmapFont.cpp
//---------------------------------------------------------------------------//
