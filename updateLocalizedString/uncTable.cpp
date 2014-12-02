//
//  uncTable.cpp
//  updateLocalizedString
//
//  Created by liaogang on 14/11/20.
//  Copyright (c) 2014年 gang.liao. All rights reserved.
//

#include "uncTable.h"
#include "stringConv.h"


/** Unicode Table
 
 0000−001F Control character
 0020−007F Basic Latin
 0080−00FF Latin-1 Supplement
 0100−017F Latin Extended-A
 0180−024F Latin Extended-B
 0250−02AF IPA Extensions
 02B0−02FF Spacing Modifier Letters
 0300−036F Combining Diacritical Marks
 0370−03FF Greek and Coptic
 0400−04FF Cyrillic
 0500−052F Cyrillic Supplement
 0530−058F Armenian
 0590−05FF Hebrew
 0600−06FF Arabic
 0700−074F Syriac
 0750−077F Arabic Supplement
 0780−07BF Thaana
 07C0−07FF NKo
 0800−083F Samaritan
 0840−085F Mandaic
 08A0−08FF Arabic Extended-A
 0900−097F Devanagari
 0980−09FF Bengali
 0A00−0A7F Gurmukhi
 0A80−0AFF Gujarati
 0B00−0B7F Oriya
 0B80−0BFF Tamil
 0C00−0C7F Telugu
 0C80−0CFF Kannada
 0D00−0D7F Malayalam
 0D80−0DFF Sinhala
 0E00−0E7F Thai
 0E80−0EFF Lao
 0F00−0FFF Tibetan
 1000−109F Myanmar
 10A0−10FF Georgian
 1100−11FF Hangul Jamo
 1200−137F Ethiopic
 1380−139F Ethiopic Supplement
 13A0−13FF Cherokee
 1400−167F Unified Canadian Aboriginal Syllabics
 1680−169F Ogham
 16A0−16FF Runic
 1700−171F Tagalog
 1720−173F Hanunoo
 1740−175F Buhid
 1760−177F Tagbanwa
 1780−17FF Khmer
 1800−18AF Mongolian
 18B0−18FF Unified Canadian Aboriginal Syllabics Extended
 1900−194F Limbu
 1950−197F Tai Le
 1980−19DF New Tai Lue
 19E0−19FF Khmer Symbols
 1A00−1A1F Buginese
 1A20−1AAF Tai Tham
 1AB0−1AFF Combining Diacritical Marks Extended
 1B00−1B7F Balinese
 1B80−1BBF Sundanese
 1BC0−1BFF Batak
 1C00−1C4F Lepcha
 1C50−1C7F Ol Chiki
 1CC0−1CCF Sundanese Supplement
 1CD0−1CFF Vedic Extensions
 1D00−1D7F Phonetic Extensions
 1D80−1DBF Phonetic Extensions Supplement
 1DC0−1DFF Combining Diacritical Marks Supplement
 1E00−1EFF Latin Extended Additional
 1F00−1FFF Greek Extended
 2000−206F General Punctuation
 2070−209F Superscripts and Subscripts
 20A0−20CF Currency Symbols
 20D0−20FF Combining Diacritical Marks for Symbols
 2100−214F Letterlike Symbols
 2150−218F Number Forms
 2190−21FF Arrows
 2200−22FF Mathematical Operators
 2300−23FF Miscellaneous Technical
 2400−243F Control Pictures
 2440−245F Optical Character Recognition
 2460−24FF Enclosed Alphanumerics
 2500−257F Box Drawing
 2580−259F Block Elements
 25A0−25FF Geometric Shapes
 2600−26FF Miscellaneous Symbols
 2700−27BF Dingbats
 27C0−27EF Miscellaneous Mathematical Symbols-A
 27F0−27FF Supplemental Arrows-A
 2800−28FF Braille Patterns
 2900−297F Supplemental Arrows-B
 2980−29FF Miscellaneous Mathematical Symbols-B
 2A00−2AFF Supplemental Mathematical Operators
 2B00−2BFF Miscellaneous Symbols and Arrows
 2C00−2C5F Glagolitic
 2C60−2C7F Latin Extended-C
 2C80−2CFF Coptic
 2D00−2D2F Georgian Supplement
 2D30−2D7F Tifinagh
 2D80−2DDF Ethiopic Extended
 2DE0−2DFF Cyrillic Extended-A
 2E00−2E7F Supplemental Punctuation
 2E80−2EFF CJK Radicals Supplement
 2F00−2FDF Kangxi Radicals
 2FF0−2FFF Ideographic Description Characters
 3000−303F CJK Symbols and Punctuation
 3040−309F Hiragana
 30A0−30FF Katakana
 3100−312F Bopomofo
 3130−318F Hangul Compatibility Jamo
 3190−319F Kanbun
 31A0−31BF Bopomofo Extended
 31C0−31EF CJK Strokes
 31F0−31FF Katakana Phonetic Extensions
 3200−32FF Enclosed CJK Letters and Months
 3300−33FF CJK Compatibility
 3400−4DB5 CJK Unified Ideographs Extension A
 4DC0−4DFF Yijing Hexagram Symbols
 4E00−9FCC CJK Unified Ideographs
 A000−A48F Yi Syllables
 A490−A4CF Yi Radicals
 A4D0−A4FF Lisu
 A500−A63F Vai
 A640−A69F Cyrillic Extended-B
 A6A0−A6FF Bamum
 A700−A71F Modifier Tone Letters
 A720−A7FF Latin Extended-D
 A800−A82F Syloti Nagri
 A830−A83F Common Indic Number Forms
 A840−A87F Phags-pa
 A880−A8DF Saurashtra
 A8E0−A8FF Devanagari Extended
 A900−A92F Kayah Li
 A930−A95F Rejang
 A960−A97F Hangul Jamo Extended-A
 A980−A9DF Javanese
 A9E0−A9FF Myanmar Extended-B
 AA00−AA5F Cham
 AA60−AA7F Myanmar Extended-A
 AA80−AADF Tai Viet
 AAE0−AAFF Meetei Mayek Extensions
 AB00−AB2F Ethiopic Extended-A
 AB30−AB6F Latin Extended-E
 ABC0−ABFF Meetei Mayek
 AC00−D7A3 Hangul Syllables
 D7B0−D7FF Hangul Jamo Extended-B
 D800−DB7F High Surrogates
 DB80−DBFF High Private Use Surrogates
 DC00−DFFF Low Surrogates
 E000−F8FF Private Use Area
 F900−FAFF CJK Compatibility Ideographs
 FB00−FB4F Alphabetic Presentation Forms
 FB50−FDFF Arabic Presentation Forms-A
 FE00−FE0F Variation Selectors
 FE10−FE1F Vertical Forms
 FE20−FE2F Combining Half Marks
 FE30−FE4F CJK Compatibility Forms
 FE50−FE6F Small Form Variants
 FE70−FEFF Arabic Presentation Forms-B
 FF00−FFEF Halfwidth and Fullwidth Forms
 FFF0−FFFF Specials
 10000−1007F Linear B Syllabary
 10080−100FF Linear B Ideograms
 10100−1013F Aegean Numbers
 10140−1018F Ancient Greek Numbers
 10190−101CF Ancient Symbols
 101D0−101FF Phaistos Disc
 10280−1029F Lycian
 102A0−102DF Carian
 102E0−102FF Coptic Epact Numbers
 10300−1032F Old Italic
 10330−1034F Gothic
 10350−1037F Old Permic
 10380−1039F Ugaritic
 103A0−103DF Old Persian
 10400−1044F Deseret
 10450−1047F Shavian
 10480−104AF Osmanya
 10500−1052F Elbasan
 10530−1056F Caucasian Albanian
 10600−1077F Linear A
 10800−1083F Cypriot Syllabary
 10840−1085F Imperial Aramaic
 10860−1087F Palmyrene
 10880−108AF Nabataean
 10900−1091F Phoenician
 10920−1093F Lydian
 10980−1099F Meroitic Hieroglyphs
 109A0−109FF Meroitic Cursive
 10A00−10A5F Kharoshthi
 10A60−10A7F Old South Arabian
 10A80−10A9F Old North Arabian
 10AC0−10AFF Manichaean
 10B00−10B3F Avestan
 10B40−10B5F Inscriptional Parthian
 10B60−10B7F Inscriptional Pahlavi
 10B80−10BAF Psalter Pahlavi
 10C00−10C4F Old Turkic
 10E60−10E7F Rumi Numeral Symbols
 11000−1107F Brahmi
 11080−110CF Kaithi
 110D0−110FF Sora Sompeng
 11100−1114F Chakma
 11150−1117F Mahajani
 11180−111DF Sharada
 111E0−111FF Sinhala Archaic Numbers
 11200−1124F Khojki
 112B0−112FF Khudawadi
 11300−1137F Grantha
 11480−114DF Tirhuta
 11580−115FF Siddham
 11600−1165F Modi
 11680−116CF Takri
 118A0−118FF Warang Citi
 11AC0−11AFF Pau Cin Hau
 12000−123FF Cuneiform
 12400−1247F Cuneiform Numbers and Punctuation
 13000−1342F Egyptian Hieroglyphs
 16800−16A3F Bamum Supplement
 16A40−16A6F Mro
 16AD0−16AFF Bassa Vah
 16B00−16B8F Pahawh Hmong
 16F00−16F9F Miao
 1B000−1B0FF Kana Supplement
 1BC00−1BC9F Duployan
 1BCA0−1BCAF Shorthand Format Controls
 1D000−1D0FF Byzantine Musical Symbols
 1D100−1D1FF Musical Symbols
 1D200−1D24F Ancient Greek Musical Notation
 1D300−1D35F Tai Xuan Jing Symbols
 1D360−1D37F Counting Rod Numerals
 1D400−1D7FF Mathematical Alphanumeric Symbols
 1E800−1E8DF Mende Kikakui
 1EE00−1EEFF Arabic Mathematical Alphabetic Symbols
 1F000−1F02F Mahjong Tiles
 1F030−1F09F Domino Tiles
 1F0A0−1F0FF Playing Cards
 1F100−1F1FF Enclosed Alphanumeric Supplement
 1F200−1F2FF Enclosed Ideographic Supplement
 1F300−1F5FF Miscellaneous Symbols and Pictographs
 1F600−1F64F Emoticons (Emoji)
 1F650−1F67F Ornamental Dingbats
 1F680−1F6FF Transport and Map Symbols
 1F700−1F77F Alchemical Symbols
 1F780−1F7FF Geometric Shapes Extended
 1F800−1F8FF Supplemental Arrows-C
*/



/**
 
 
 　　0000-007F：C0控制符及基本拉丁文 (C0 Control and Basic Latin)
 
 
 　　0080-00FF：C1控制符及拉丁文补充-1 (C1 Control and Latin 1 Supplement)
 
 
 　　0100-017F：拉丁文扩展-A (Latin Extended-A)
 
 
 　　0180-024F：拉丁文扩展-B (Latin Extended-B)
 
 
 　　0250-02AF：国际音标扩展 (IPA Extensions)
 
 
 　　02B0-02FF：空白修饰字母 (Spacing Modifiers)
 
 
 　　0300-036F：结合用读音符号 (Combining Diacritics Marks)
 
 
 　　0370-03FF：希腊文及科普特文 (Greek and Coptic)
 
 0400-04FF：西里尔字母 (Cyrillic)
 
 
 　　0500-052F：西里尔字母补充 (Cyrillic Supplement)
 
 
 　　0530-058F：亚美尼亚语 (Armenian)
 
 
 　　0590-05FF：希伯来文 (Hebrew)
 
 
 　　0600-06FF：阿拉伯文 (Arabic)
 
 
 　　0700-074F：叙利亚文 (Syriac)
 
 
 　　0750-077F：阿拉伯文补充 (Arabic Supplement)
 
 
 　　0780-07BF：马尔代夫语 (Thaana)
 
 
 　　07C0-077F：西非书面语言 (N'Ko)
 
 
 　　0800-085F：阿维斯塔语及巴列维语 (Avestan and Pahlavi)
 
 
 　　0860-087F：Mandaic
 
 
 　　0880-08AF：撒马利亚语 (Samaritan)
 
 
 　　0900-097F：天城文书 (Devanagari)
 
 
 　　0980-09FF：孟加拉语 (Bengali)
 
 
 　　0A00-0A7F：锡克教文 (Gurmukhi)
 
 
 　　0A80-0AFF：古吉拉特文 (Gujarati)
 
 
 　　0B00-0B7F：奥里亚文 (Oriya)
 
 
 　　0B80-0BFF：泰米尔文 (Tamil)
 
 
 　　0C00-0C7F：泰卢固文 (Telugu)
 
 
 　　0C80-0CFF：卡纳达文 (Kannada)
 
 
 　　0D00-0D7F：德拉维族语 (Malayalam)
 
 
 　　0D80-0DFF：僧伽罗语 (Sinhala)
 
 
 　　0E00-0E7F：泰文 (Thai)
 
 
 　　0E80-0EFF：老挝文 (Lao)
 
 
 　　0F00-0FFF：藏文 (Tibetan)
 
 
 　　1000-109F：缅甸语 (Myanmar)
 
 
 　　10A0-10FF：格鲁吉亚语 (Georgian)
 
 
 　　1100-11FF：朝鲜文 (Hangul Jamo)
 
 
 　　1200-137F：埃塞俄比亚语 (Ethiopic)
 
 
 　　1380-139F：埃塞俄比亚语补充 (Ethiopic Supplement)
 
 
 　　13A0-13FF：切罗基语 (Cherokee)
 
 
 　　1400-167F：统一加拿大土著语音节 (Unified Canadian Aboriginal Syllabics)
 
 
 　　1680-169F：欧甘字母 (Ogham)
 
 
 　　16A0-16FF：如尼文 (Runic)
 
 
 　　1700-171F：塔加拉语 (Tagalog)
 
 
 　　1720-173F：Hanunóo
 
 
 　　1740-175F：Buhid
 
 
 　　1760-177F：Tagbanwa
 
 
 　　1780-17FF：高棉语 (Khmer)
 
 
 　　1800-18AF：蒙古文 (Mongolian)
 
 
 　　18B0-18FF：Cham
 
 
 　　1900-194F：Limbu
 
 
 　　1950-197F：德宏泰语 (Tai Le)
 
 
 　　1980-19DF：新傣仂语 (New Tai Lue)
 
 
 　　19E0-19FF：高棉语记号 (Kmer Symbols)
 
 
 　　1A00-1A1F：Buginese
 
 
 　　1A20-1A5F：Batak
 
 
 　　1A80-1AEF：Lanna
 
 
 　　1B00-1B7F：巴厘语 (Balinese)
 
 
 　　1B80-1BB0：巽他语 (Sundanese)
 
 
 　　1BC0-1BFF：Pahawh Hmong
 
 
 　　1C00-1C4F：雷布查语(Lepcha)
 
 
 　　1C50-1C7F：Ol Chiki
 
 
 　　1C80-1CDF：曼尼普尔语 (Meithei/Manipuri)
 
 
 　　1D00-1D7F：语音学扩展 (Phonetic Extensions)
 
 
 　　1D80-1DBF：语音学扩展补充 (Phonetic Extensions Supplem
 
 ent)
 
 
 　　1DC0-1DFF：结合用读音符号补充 (Combining Diacritics Marks Supplement)
 
 
 　　1E00-1EFF：拉丁文扩充附加 (Latin Extended Additional)
 
 
 　　1F00-1FFF：希腊语扩充 (Greek Extended)
 
 
 　　2000-206F：常用标点 (General Punctuation)
 
 
 　　2070-209F：上标及下标 (Superscripts and Subscripts)
 
 
 　　20A0-20CF：货币符号 (Currency Symbols)
 
 
 　　20D0-20FF：组合用记号 (Combining Diacritics Marks for Symbols)
 
 
 　　2100-214F：字母式符号 (Letterlike Symbols)
 
 
 　　2150-218F：数字形式 (Number Form)
 
 
 　　2190-21FF：箭头 (Arrows)
 
 
 　　2200-22FF：数学运算符 (Mathematical Operator)
 
 
 　　2300-23FF：杂项工业符号 (Miscellaneous Technical)
 
 
 　　2400-243F：控制图片 (Control Pictures)
 
 
 　　2440-245F：光学识别符 (Optical Character Recognition)
 
 
 　　2460-24FF：封闭式字母数字 (Enclosed Alphanumerics)
 
 
 　　2500-257F：制表符 (Box Drawing)
 
 
 　　2580-259F：方块元素 (Block Element)
 
 
 　　25A0-25FF：几何图形 (Geometric Shapes)
 
 
 　　2600-26FF：杂项符号 (Miscellaneous Symbols)
 
 
 　　2700-27BF：印刷符号 (Dingbats)
 
 
 　　27C0-27EF：杂项数学符号-A (Miscellaneous Mathematical Symbols-A)
 
 
 　　27F0-27FF：追加箭头-A (Supplemental Arrows-A)
 
 
 　　2800-28FF：盲文点字模型 (Braille Patterns)
 
 
 　　2900-297F：追加箭头-B (Supplemental Arrows-B)
 
 
 　　2980-29FF：杂项数学符号-B (Miscellaneous Mathematical Symbols-B)
 
 
 　　2A00-2AFF：追加数学运算符 (Supplemental Mathematical Operator)
 
 
 　　2B00-2BFF：杂项符号和箭头 (Miscellaneous Symbols and Arrows)
 
 
 　　2C00-2C5F：格拉哥里字母 (Glagolitic)
 
 
 　　2C60-2C7F：拉丁文扩展-C (Latin Extended-C)
 
 
 　　2C80-2CFF：古埃及语 (Coptic)
 
 
 　　2D00-2D2F：格鲁吉亚语补充 (Georgian Supplement)
 
 
 　　2D30-2D7F：提非纳文 (Tifinagh)
 
 
 　　2D80-2DDF：埃塞俄比亚语扩展 (Ethiopic Extended)
 
 
 　　2E00-2E7F：追加标点 (Supplemental Punctuation)
 
 
 　　2E80-2EFF：CJK 部首补充 (CJK Radicals Supplement)
 
 
 　　2F00-2FDF：康熙字典部首 (Kangxi Radicals)
 
 
 　　2FF0-2FFF：表意文字描述符 (Ideographic Description Characters)
 
 
 　　3000-303F：CJK 符号和标点 (CJK Symbols and Punctuation)
 
 
 　　3040-309F：日文平假名 (Hiragana)
 
 
 　　30A0-30FF：日文片假名 (Katakana)
 
 
 　　3100-312F：注音字母 (Bopomofo)
 
 
 　　3130-318F：朝鲜文兼容字母 (Hangul Compatibility Jamo)
 
 
 　　3190-319F：象形字注释标志 (Kanbun)
 
 
 　　31A0-31BF：注音字母扩展 (Bopomofo Extended)
 
 
 　　31C0-31EF：CJK 笔画 (CJK Strokes)
 
 
 　　31F0-31FF：日文片假名语音扩展 (Katakana Phonetic Extensions)
 
 
 　　3200-32FF：封闭式 CJK 文字和月份 (Enclosed CJK Letters and Months)
 
 
 　　3300-33FF：CJK 兼容 (CJK Compatibility)
 
 
 　　3400-4DBF：CJK 统一表意符号扩展 A (CJK Unified Ideographs Extension A)
 
 
 　　4DC0-4DFF：易经六十四卦符号 (Yijing Hexagrams Symbols)
 
 
 　　4E00-9FBF：CJK 统一表意符号 (CJK Unified Ideographs)
 
 
 　　A000-A48F：彝文音节 (Yi Syllables)
 
 
 　　A490-A4CF：彝文字根 (Yi Radicals)
 
 
 　　A500-A61F：Vai
 
 
 　　A660-A6FF：统一加拿大土著语音节补充 (Unified Canadian Aboriginal Syllabics Supplement)
 
 
 　　A700-A71F：声调修饰字母 (Modifier Tone Letters)
 
 
 　　A720-A7FF：拉丁文扩展-D (Latin Extended-D)
 
 
 　　A800-A82F：Syloti Nagri
 
 
 　　A840-A87F：八思巴字 (Phags-pa)
 
 
 　　A880-A8DF：Saurashtra
 
 
 　　A900-A97F：爪哇语 (Javanese)
 
 
 　　A980-A9DF：Chakma
 
 
 　　AA00-AA3F：Varang Kshiti
 
 
 　　AA40-AA6F：Sorang Sompeng
 
 
 　　AA80-AADF：Newari
 
 
 　　AB00-AB5F：越南傣语 (Vi?t Thái)
 
 
 　　AB80-ABA0：Kayah Li
 
 
 　　AC00-D7AF：朝鲜文音节 (Hangul Syllables)
 
 
 　　D800-DBFF：High-half zone of UTF-16
 
 
 　　DC00-DFFF：Low-half zone of UTF-16
 
 
 　　E000-F8FF：自行使用区域 (Private Use Zone)
 
 
 　　F900-FAFF：CJK 兼容象形文字 (CJK Compatibility Ideographs)
 
 
 　　FB00-FB4F：字母表达形式 (Alphabetic Presentation Form)
 
 
 　　FB50-FDFF：阿拉伯表达形式A (Arabic Presentation Form-A)
 
 
 　　FE00-FE0F：变量选择符 (Variation Selector)
 
 
 　　FE10-FE1F：竖排形式 (Vertical Forms)
 
 
 　　FE20-FE2F：组合用半符号 (Combining Half Marks)
 
 
 　　FE30-FE4F：CJK 兼容形式 (CJK Compatibility Forms)
 
 
 　　FE50-FE6F：小型变体形式 (Small Form Variants)
 
 
 　　FE70-FEFF：阿拉伯表达形式B (Arabic Presentation Form-B)
 
 
 　　FF00-FFEF：半型及全型形式 (Halfwidth and Fullwidth Form)全角标点、全角ASCII
 
 
 　　FFF0-FFFF：特殊 (Specials)
 
 
 
 10300..1032F; Old Italic
 
 
 10330..1034F; Gothic
 
 
 10400..1044F; Deseret
 
 
 1D000..1D0FF; Byzantine Musical Symbols
 
 
 1D100..1D1FF; Musical Symbols
 
 
 1D400..1D7FF; Mathematical Alphanumeric Symbols
 
 
 20000..2A6D6; CJK Unified Ideographs Extension B   
 
 
 2F800..2FA1F; CJK Compatibility Ideographs Supplement   
 
 
 E0000..E007F; Tags   
 
 
 F0000..FFFFD; Private Use   
 
 
 100000..10FFFD; Private Use  
 
 
 */


const struct UNCStruct
{
    unsigned short range;
    char const *value;
} uncTable[]=
{
    {0x0000 ,"Control character"},
    {0x0020 ,"Basic Latin"},
    {0x0080 ,"Latin-1 Supplement"},
    {0x0100 ,"Latin Extended-A"},
    {0x0180 ,"Latin Extended-B"},
    {0x0250 ,"IPA Extensions"},
    {0x02B0 ,"Spacing Modifier Letters"},
    {0x0300 ,"Combining Diacritical Marks"},
    {0x0370 ,"Greek and Coptic"},
    {0x0400 ,"Cyrillic"},
    {0x0500 ,"Cyrillic Supplement"},
    {0x0530 ,"Armenian"},
    {0x0590 ,"Hebrew"},
    {0x0600 ,"Arabic"},
    {0x0700 ,"Syriac"},
    {0x0750 ,"Arabic Supplement"},
    {0x0780 ,"Thaana"},
    {0x07C0 ,"NKo"},
    {0x0800 ,"Samaritan"},
    {0x0840 ,"Mandaic"},
    {0x08A0 ,"Arabic Extended-A"},
    {0x0900 ,"Devanagari"},
    {0x0980 ,"Bengali"},
    {0x0A00 ,"Gurmukhi"},
    {0x0A80 ,"Gujarati"},
    {0x0B00 ,"Oriya"},
    {0x0B80 ,"Tamil"},
    {0x0C00 ,"Telugu"},
    {0x0C80 ,"Kannada"},
    {0x0D00 ,"Malayalam"},
    {0x0D80 ,"Sinhala"},
    {0x0E00 ,"Thai"},
    {0x0E80 ,"Lao"},
    {0x0F00 ,"Tibetan"},
    {0x1000 ,"Myanmar"},
    {0x10A0 ,"Georgian"},
    {0x1100 ,"Hangul Jamo"},
    {0x1200 ,"Ethiopic"},
    {0x1380 ,"Ethiopic Supplement"},
    {0x13A0 ,"Cherokee"},
    {0x1400 ,"Unified Canadian Aboriginal Syllabics"},
    {0x1680 ,"Ogham"},
    {0x16A0 ,"Runic"},
    {0x1700 ,"Tagalog"},
    {0x1720 ,"Hanunoo"},
    {0x1740 ,"Buhid"},
    {0x1760 ,"Tagbanwa"},
    {0x1780 ,"Khmer"},
    {0x1800 ,"Mongolian"},
    {0x18B0 ,"Unified Canadian Aboriginal Syllabics Extended"},
    {0x1900 ,"Limbu"},
    {0x1950 ,"Tai Le"},
    {0x1980 ,"New Tai Lue"},
    {0x19E0 ,"Khmer Symbols"},
    {0x1A00 ,"Buginese"},
    {0x1A20 ,"Tai Tham"},
    {0x1AB0 ,"Combining Diacritical Marks Extended"},
    {0x1B00 ,"Balinese"},
    {0x1B80 ,"Sundanese"},
    {0x1BC0 ,"Batak"},
    {0x1C00 ,"Lepcha"},
    {0x1C50 ,"Ol Chiki"},
    {0x1CC0 ,"Sundanese Supplement"},
    {0x1CD0 ,"Vedic Extensions"},
    {0x1D00 ,"Phonetic Extensions"},
    {0x1D80 ,"Phonetic Extensions Supplement"},
    {0x1DC0 ,"Combining Diacritical Marks Supplement"},
    {0x1E00 ,"Latin Extended Additional"},
    {0x1F00 ,"Greek Extended"},
    {0x2000 ,"General Punctuation"},
    {0x2070 ,"Superscripts and Subscripts"},
    {0x20A0 ,"Currency Symbols"},
    {0x20D0 ,"Combining Diacritical Marks for Symbols"},
    {0x2100 ,"Letterlike Symbols"},
    {0x2150 ,"Number Forms"},
    {0x2190 ,"Arrows"},
    {0x2200 ,"Mathematical Operators"},
    {0x2300 ,"Miscellaneous Technical"},
    {0x2400 ,"Control Pictures"},
    {0x2440 ,"Optical Character Recognition"},
    {0x2460 ,"Enclosed Alphanumerics"},
    {0x2500 ,"Box Drawing"},
    {0x2580 ,"Block Elements"},
    {0x25A0 ,"Geometric Shapes"},
    {0x2600 ,"Miscellaneous Symbols"},
    {0x2700 ,"Dingbats"},
    {0x27C0 ,"Miscellaneous Mathematical Symbols-A"},
    {0x27F0 ,"Supplemental Arrows-A"},
    {0x2800 ,"Braille Patterns"},
    {0x2900 ,"Supplemental Arrows-B"},
    {0x2980 ,"Miscellaneous Mathematical Symbols-B"},
    {0x2A00 ,"Supplemental Mathematical Operators"},
    {0x2B00 ,"Miscellaneous Symbols and Arrows"},
    {0x2C00 ,"Glagolitic"},
    {0x2C60 ,"Latin Extended-C"},
    {0x2C80 ,"Coptic"},
    {0x2D00 ,"Georgian Supplement"},
    {0x2D30 ,"Tifinagh"},
    {0x2D80 ,"Ethiopic Extended"},
    {0x2DE0 ,"Cyrillic Extended-A"},
    {0x2E00 ,"Supplemental Punctuation"},
    {0x2E80 ,"CJK Radicals Supplement"},
    {0x2F00 ,"Kangxi Radicals"},
    {0x2FF0 ,"Ideographic Description Characters"},
    {0x3000 ,"CJK Symbols and Punctuation"},
    {0x3040 ,"Hiragana"},
    {0x30A0 ,"Katakana"},
    {0x3100 ,"Bopomofo"},
    {0x3130 ,"Hangul Compatibility Jamo"},
    {0x3190 ,"Kanbun"},
    {0x31A0 ,"Bopomofo Extended"},
    {0x31C0 ,"CJK Strokes"},
    {0x31F0 ,"Katakana Phonetic Extensions"},
    {0x3200 ,"Enclosed CJK Letters and Months"},
    {0x3300 ,"CJK Compatibility"},
    {0x3400 ,"CJK Unified Ideographs Extension A"},
    {0x4DC0 ,"Yijing Hexagram Symbols"},
    {0x4E00 ,"CJK Unified Ideographs"},
    {0xA000 ,"Yi Syllables"},
    {0xA490 ,"Yi Radicals"},
    {0xA4D0 ,"Lisu"},
    {0xA500 ,"Vai"},
    {0xA640 ,"Cyrillic Extended-B"},
    {0xA6A0 ,"Bamum"},
    {0xA700 ,"Modifier Tone Letters"},
    {0xA720 ,"Latin Extended-D"},
    {0xA800 ,"Syloti Nagri"},
    {0xA830 ,"Common Indic Number Forms"},
    {0xA840 ,"Phags-pa"},
    {0xA880 ,"Saurashtra"},
    {0xA8E0 ,"Devanagari Extended"},
    {0xA900 ,"Kayah Li"},
    {0xA930 ,"Rejang"},
    {0xA960 ,"Hangul Jamo Extended-A"},
    {0xA980 ,"Javanese"},
    {0xA9E0 ,"Myanmar Extended-B"},
    {0xAA00 ,"Cham"},
    {0xAA60 ,"Myanmar Extended-A"},
    {0xAA80 ,"Tai Viet"},
    {0xAAE0 ,"Meetei Mayek Extensions"},
    {0xAB00 ,"Ethiopic Extended-A"},
    {0xAB30 ,"Latin Extended-E"},
    {0xABC0 ,"Meetei Mayek"},
    {0xAC00 ,"Hangul Syllables"},
    {0xD7B0 ,"Hangul Jamo Extended-B"},
    {0xD800 ,"High Surrogates"},
    {0xDB80 ,"High Private Use Surrogates"},
    {0xDC00 ,"Low Surrogates"},
    {0xE000 ,"Private Use Area"},
    {0xF900 ,"CJK Compatibility Ideographs"},
    {0xFB00 ,"Alphabetic Presentation Forms"},
    {0xFB50 ,"Arabic Presentation Forms-A"},
    {0xFE00 ,"Variation Selectors"},
    {0xFE10 ,"Vertical Forms"},
    {0xFE20 ,"Combining Half Marks"},
    {0xFE30 ,"CJK Compatibility Forms"},
    {0xFE50 ,"Small Form Variants"},
    {0xFE70 ,"Arabic Presentation Forms-B"},
    {0xFF00 ,"Halfwidth and Fullwidth Forms"},
    {0xFFF0 ,"Specials"}
    /*, utf16里面暂时用不到下面这些
    {0x10000 ,"Linear B Syllabary"},
    {0x10080 ,"Linear B Ideograms"},
    {0x10100 ,"Aegean Numbers"},
    {0x10140 ,"Ancient Greek Numbers"},
    {0x10190 ,"Ancient Symbols"},
    {0x101D0 ,"Phaistos Disc"},
    {0x10280 ,"Lycian"},
    {0x102A0 ,"Carian"},
    {0x102E0 ,"Coptic Epact Numbers"},
    {0x10300 ,"Old Italic"},
    {0x10330 ,"Gothic"},
    {0x10350 ,"Old Permic"},
    {0x10380 ,"Ugaritic"},
    {0x103A0 ,"Old Persian"},
    {0x10400 ,"Deseret"},
    {0x10450 ,"Shavian"},
    {0x10480 ,"Osmanya"},
    {0x10500 ,"Elbasan"},
    {0x10530 ,"Caucasian Albanian"},
    {0x10600 ,"Linear A"},
    {0x10800 ,"Cypriot Syllabary"},
    {0x10840 ,"Imperial Aramaic"},
    {0x10860 ,"Palmyrene"},
    {0x10880 ,"Nabataean"},
    {0x10900 ,"Phoenician"},
    {0x10920 ,"Lydian"},
    {0x10980 ,"Meroitic Hieroglyphs"},
    {0x109A0 ,"Meroitic Cursive"},
    {0x10A00 ,"Kharoshthi"},
    {0x10A60 ,"Old South Arabian"},
    {0x10A80 ,"Old North Arabian"},
    {0x10AC0 ,"Manichaean"},
    {0x10B00 ,"Avestan"},
    {0x10B40 ,"Inscriptional Parthian"},
    {0x10B60 ,"Inscriptional Pahlavi"},
    {0x10B80 ,"Psalter Pahlavi"},
    {0x10C00 ,"Old Turkic"},
    {0x10E60 ,"Rumi Numeral Symbols"},
    {0x11000 ,"Brahmi"},
    {0x11080 ,"Kaithi"},
    {0x110D0 ,"Sora Sompeng"},
    {0x11100 ,"Chakma"},
    {0x11150 ,"Mahajani"},
    {0x11180 ,"Sharada"},
    {0x111E0 ,"Sinhala Archaic Numbers"},
    {0x11200 ,"Khojki"},
    {0x112B0 ,"Khudawadi"},
    {0x11300 ,"Grantha"},
    {0x11480 ,"Tirhuta"},
    {0x11580 ,"Siddham"},
    {0x11600 ,"Modi"},
    {0x11680 ,"Takri"},
    {0x118A0 ,"Warang Citi"},
    {0x11AC0 ,"Pau Cin Hau"},
    {0x12000 ,"Cuneiform"},
    {0x12400 ,"Cuneiform Numbers and Punctuation"},
    {0x13000 ,"Egyptian Hieroglyphs"},
    {0x16800 ,"Bamum Supplement"},
    {0x16A40 ,"Mro"},
    {0x16AD0 ,"Bassa Vah"},
    {0x16B00 ,"Pahawh Hmong"},
    {0x16F00 ,"Miao"},
    {0x1B000 ,"Kana Supplement"},
    {0x1BC00 ,"Duployan"},
    {0x1BCA0 ,"Shorthand Format Controls"},
    {0x1D000 ,"Byzantine Musical Symbols"},
    {0x1D100 ,"Musical Symbols"},
    {0x1D200 ,"Ancient Greek Musical Notation"},
    {0x1D300 ,"Tai Xuan Jing Symbols"},
    {0x1D360 ,"Counting Rod Numerals"},
    {0x1D400 ,"Mathematical Alphanumeric Symbols"},
    {0x1E800 ,"Mende Kikakui"},
    {0x1EE00 ,"Arabic Mathematical Alphabetic Symbols"},
    {0x1F000 ,"Mahjong Tiles"},
    {0x1F030 ,"Domino Tiles"},
    {0x1F0A0 ,"Playing Cards"},
    {0x1F100 ,"Enclosed Alphanumeric Supplement"},
    {0x1F200 ,"Enclosed Ideographic Supplement"},
    {0x1F300 ,"Miscellaneous Symbols and Pictographs"},
    {0x1F600 ,"Emoticons (Emoji)"},
    {0x1F650 ,"Ornamental Dingbats"},
    {0x1F680 ,"Transport and Map Symbols"},
    {0x1F700 ,"Alchemical Symbols"},
    {0x1F780 ,"Geometric Shapes Extended"},
    {0x1F800 ,"Arrows-C"},
    {0x1F8FF ,"NULL"}*/
};



const char *uncTableConvert(const char *unicodeC)
{
    unsigned short unicodeChar = 0;
    
    memcpy(&unicodeChar, unicodeC, 2);
    
    
    static int lastI = 0;
    int tableLen = sizeof(uncTable)/sizeof(uncTable[0]);
    
    int lastItemsRange = 0x1F8FF;
    for (int i = 0; i < tableLen; i++)
    {
        UNCStruct item = uncTable[i];
        
        if ( unicodeChar >= lastItemsRange && unicodeChar < item.range)
        {
            lastI = i-1;
            return uncTable[lastI].value;
        }
        
        lastItemsRange = item.range;
    }
    
    return NULL;
}


const char* uncTableConvert(const char *c ,int len)
{
    char buf[800] ={0};
    int converted = UTF8StrToUnicodeStr((unsigned char*)c,(unsigned short*)buf,800);
    
    int uLen = wcslen((wchar_t*)buf);
    
    
    printf("unicode string's len: %d\n\n",uLen);
    
    int bytes = uLen*2;
    for (int i = 0; i < bytes; i+=2)
    {
        const char *tableValue = uncTableConvert(buf+i);
        printf("%s\n",tableValue);
    }
    
    
    
    
    return 0;
}
