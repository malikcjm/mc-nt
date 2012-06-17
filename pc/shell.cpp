/* Shell for MC.EXE for Windows systems.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

  Written by Siegward Jaekel

  Compiler: mingw

*/
#include <conio.h>
#include <iostream>
#include <string>
#include <vector>
#include <direct.h>
#include <process.h>
#include <windows.h>
#include "keyboard.h"
#include "shell.h"
#include "slang.h"
#include <cstdlib>
extern "C"
{
#include "../src/cons.saver.h"
extern HANDLE hStdin;
}

using namespace std;

/***************************************************************************
* class History
***************************************************************************/
class History
  {
    int Index;
    vector<string> Strings;

    static string Empty;
  public:
    History();
    void Push(string &line_buffer);
    bool GetEarlier(string &line_buffer);
    bool GetLater(string &line_buffer);
  };

/***************************************************************************
* class LineEditor
***************************************************************************/
class LineEditor
  {
    int X;
    int Y;
    int StartX;
    int StartY;
    int CursorPos;
    int ScreenWidth;
    int ScreenHeight;
    string *Buffer;
    History &MyHistory;
  public:
    LineEditor(History &history);
    int Input(string &buffer);
  private:
    void CursorForwards();
    void CursorBackwards();
    void OverwriteLine(int last_length);
    void CursorToEnd();
  };

/***************************************************************************
* Consts
***************************************************************************/
#define FILE_NAME_LENGTH 260 // long file names

/***************************************************************************
* Prototypes
***************************************************************************/
void execute_command(string &command);
void prompt();
bool chdir_and_disk(const char *path);
WORD map_to_key_list(_KEY_EVENT_RECORD *record);
int wherex();
int wherey();
void gotoxy(int x, int y);
int screen_x();
int screen_y();

/***************************************************************************
* Global variables
***************************************************************************/

// we don't have cerr, just a dummy cerr, needed for exceptions
//_IO_ostream_withassign cerr;

static HANDLE hShell;
string History::Empty("");
History CommandHistory;

/*****************************************************************************
* internal_shell()
*
* Shell for MC.EXE
*****************************************************************************/
void internal_shell(const char *command)
{
  int c;
  string line_buffer;
  LineEditor editor(CommandHistory);

  if (command)
    {
    line_buffer = command;
    CommandHistory.Push(line_buffer);
    execute_command(line_buffer);
    return;
    }

  handle_console (CONSOLE_RESTORE);
  hShell = GetStdHandle (STD_OUTPUT_HANDLE);

  prompt();

  do
    {
    switch (c = editor.Input(line_buffer))
      {
      case CR:
        // cd
        if (tolower(line_buffer[0]) == 'c' && tolower(line_buffer[1]) == 'd'
                                                     && line_buffer[2] == ' ')
            {
          if (!chdir_and_disk(line_buffer.c_str()+3))
            printf("%s does not exist\n",line_buffer.c_str()+3);
                line_buffer.erase();
          prompt();
          }

        // a:
        else if(line_buffer[1] == ':' && isalpha(line_buffer[0]))
            {
                if (_chdrive(toupper(line_buffer[0])-'A'+1))
            printf("%s does not exist\n",line_buffer.c_str());
                line_buffer.erase();
          prompt();
          }

        else
            execute_command(line_buffer);
        break;
      }
    } while (c != CTRL_O);
  }

/***************************************************************************
* execute_command()
*
* Executes a command and shows the prompt for the next command
***************************************************************************/
void execute_command(string &command)
    {
    SetConsoleTitle (command.c_str());
  system(command.c_str());
  command.erase();
  SetConsoleTitle ("GNU Midnight Commander");
  prompt();
  }

/***************************************************************************
* prompt()
*
* Prints the prompt
***************************************************************************/
void prompt()
    {
  char buffer[FILE_NAME_LENGTH];
  printf("%s>",_getcwd(buffer,FILE_NAME_LENGTH));
  }

/***************************************************************************
* chdir_and_disk()
*
* Changes the directory and drive
*
* Return value:
*					true, if directory was changed
*         false, if directory does not exist
***************************************************************************/
bool chdir_and_disk(const char *path)
  {
  if (strchr(path,':'))
    if (_chdrive(toupper(*path)-'A'+1))
        return false;
  return _chdir(path)
    ? false
    : true;
  }

/***************************************************************************
* map_to_key_list()
*
* Mapes the keycodes to the codes defined in 'keycode.h'
*
* Return value:
*					keycode
*         or 0 if unkown keycode
***************************************************************************/
WORD map_to_key_list(_KEY_EVENT_RECORD *record)
  {
  char c = record->uChar.AsciiChar;
  switch (c)
    {
    case 0:
      switch (record->wVirtualKeyCode)
        {
        case 0x2e:
          return DEL;
          break;
        case 0x25:
          return CLEFT;
          break;
        case 0x27:
          return CRIGHT;
          break;
        case 0x26:
          return CUP;
          break;
        case 0x28:
          return CDOWN;
          break;
        default:
          return 0;
        }
    default: return c;
    }
  }

/***************************************************************************
* endl()
*
* Dummy endl (for exeptions only)
***************************************************************************/
ostream &endl(ostream &stream)
  {
  return stream;
  }

/***************************************************************************
* ostream::operator<<()
*
* Dummy ostream::operator<< (for exeptions only)
***************************************************************************/
//ostream &ostream::operator<<(char const *text)
//  {
//  return *this;
//  }

/***************************************************************************
* __out_of_range()
*
* Dummy __out_of_range (for exeptions only)
***************************************************************************/
void __out_of_range(char const *text)
  {
  }

/***************************************************************************
* __length_error()
*
* Dummy __length_error (for exeptions only)
***************************************************************************/
void __length_error(char const *text)
  {
  }

/*****************************************************************************
* wherex()
*****************************************************************************/
int wherex()
  {
  CONSOLE_SCREEN_BUFFER_INFO screenInfo;
  if (GetConsoleScreenBufferInfo(hShell, &screenInfo) == TRUE)
      return screenInfo.dwCursorPosition.X;
    else
    return 0;
  }

/*****************************************************************************
* wherexy()
*****************************************************************************/
int wherey()
  {
  CONSOLE_SCREEN_BUFFER_INFO screenInfo;
  if (GetConsoleScreenBufferInfo(hShell, &screenInfo) == TRUE)
      return screenInfo.dwCursorPosition.Y;
    else
    return 0;
  }

/*****************************************************************************
* gotoxy()
*****************************************************************************/
void gotoxy(int x, int y)
  {
  COORD newPosition;
  newPosition.X = x;
  newPosition.Y = y;
  SetConsoleCursorPosition(hShell, newPosition);
  }

/*****************************************************************************
* screen_x()
*****************************************************************************/
int screen_x()
  {
  CONSOLE_SCREEN_BUFFER_INFO screenInfo;
  if (GetConsoleScreenBufferInfo(hShell, &screenInfo) == TRUE)
      return screenInfo.dwSize.X;
    else
    return 0;
  }

/*****************************************************************************
* screen_y()
*****************************************************************************/
int screen_y()
  {
  CONSOLE_SCREEN_BUFFER_INFO screenInfo;
  if (GetConsoleScreenBufferInfo(hShell, &screenInfo) == TRUE)
      return screenInfo.dwSize.Y;
    else
    return 0;
  }

/***************************************************************************
* History::History()
***************************************************************************/
History::History()
      : Index(0)
  {
  Strings.push_back(Empty);
  }

/***************************************************************************
* History::Push()
***************************************************************************/
void History::Push(string &line_buffer)
  {
  Index = Strings.size();

  if (line_buffer.size() == 0)
    {
    --Index;
    return;
    }

  if (Strings.size() > 1 && line_buffer == Strings[Strings.size()-2])
    {
    --Index;
    return;
    }
  Strings[Strings.size()-1] = line_buffer;
  Strings.push_back(Empty);
  }

/***************************************************************************
* History::GetEarlier()
***************************************************************************/
bool History::GetEarlier(string &line_buffer)
  {
  bool result = true;

  if (Index > 0)
    --Index;
  else
    result = false;
  line_buffer = Strings[Index];
  return result;
  }

/***************************************************************************
* History::GetLater()
***************************************************************************/
bool History::GetLater(string &line_buffer)
  {
  bool result = true;

  if (Index < int(Strings.size()) - 1)
    ++Index;
  else
    result = false;
  line_buffer = Strings[Index];
  return result;
  }

/***************************************************************************
* LineEditor::LineEditor()
***************************************************************************/
LineEditor::LineEditor(History &history)
      : MyHistory(history)
  {
  }

/***************************************************************************
* LineEditor::CursorForwards()
***************************************************************************/
void LineEditor::CursorForwards()
  {
  if (X == ScreenWidth -1)
    {
    X = 0;
    if (Y < ScreenHeight -1)
      ++Y;
    else
      ++StartY;
    }
  else
    ++X;

  gotoxy(X,Y);
  ++CursorPos;
  }

/***************************************************************************
* LineEditor::CursorBackwards()
***************************************************************************/
void LineEditor::CursorBackwards()
  {
  if (X == 0)
    {
    X = ScreenWidth -1;
    --Y;
    }
  else
    --X;

  gotoxy(X,Y);
  --CursorPos;
  }

/***************************************************************************
* LineEditor::CursorToEnd()
***************************************************************************/
void LineEditor::CursorToEnd()
  {
  X = (StartX + Buffer->size()) % ScreenWidth;
  Y = StartY + (StartX + Buffer->size()) / ScreenWidth;
  gotoxy(X,Y);
  CursorPos = Buffer->size();
  }

/***************************************************************************
* LineEditor::OverwriteLine()
***************************************************************************/
void LineEditor::OverwriteLine(int last_length)
  {
  gotoxy(StartX,StartY);
  for (int i=0; i<last_length; ++i)
    _putch(' ');
    gotoxy(StartX,StartY);
  CursorPos = Buffer->size();
  printf("%s",Buffer->c_str());
  if (StartY == ScreenHeight -1)
    {
    StartY -= (StartX + Buffer->size()) / ScreenWidth;
    }
  Y = wherey();
  X = wherex();
  }

/***************************************************************************
* LineEditor::Input()
***************************************************************************/
int LineEditor::Input(string &buffer)
  {
  StartX = X = wherex();
  StartY = Y = wherey();
  CursorPos = 0;
  ScreenWidth = screen_x();
  ScreenHeight = screen_y();
  Buffer = &buffer;

  INPUT_RECORD record;
  DWORD bytesRead;

  for (;;)
    {
    int c = 0;

    if (!PeekConsoleInput(hStdin, &record, 1, &bytesRead)
                  || bytesRead == 0
                  || !ReadConsoleInput(hStdin, &record, 1, &bytesRead))
      {
      Sleep(25);
      continue;
      }

    if (record.EventType == KEY_EVENT && record.Event.KeyEvent.bKeyDown)
      c = map_to_key_list(&record.Event.KeyEvent);
    else
      {
      Sleep(25);
      continue;
      }
    if (c == 0)
      {
      Sleep(25);
      continue;
      }

    switch (c)
            {
            case CTRL_O:
              return CTRL_O;
      case CR:
        CursorToEnd();
        _putch('\n');
        _putch('\r');
        MyHistory.Push(buffer);
        return CR;

      case BS:
        if (CursorPos > 0)
            {
          buffer.erase(CursorPos-1,1);
          CursorBackwards();
          printf("%s ",buffer.c_str()+CursorPos);
          gotoxy(X,Y);
          }
        break;

      case DEL:
        if (static_cast<std::size_t>(CursorPos) < buffer.size())
            {
          buffer.erase(CursorPos,1);
          printf("%s ",buffer.c_str()+CursorPos);
          gotoxy(X,Y);
          }
        break;

      case CLEFT:
        if (CursorPos > 0)
            CursorBackwards();
        break;

      case CRIGHT:
        if (static_cast<std::size_t>(CursorPos) < buffer.size())
            CursorForwards();
        break;

      case CUP:
        {
        int last_length = buffer.size();
        if (MyHistory.GetEarlier(buffer))
          OverwriteLine(last_length);
        }
        break;

      case CDOWN:
        {
        int last_length = buffer.size();
        if (MyHistory.GetLater(buffer))
          OverwriteLine(last_length);
        }
        break;

      default:
            if ((c >= ' ') && (c < 0x100))
            {
                _putch(c);
                if (CursorPos == buffer.size())
            {
            buffer += c;
            CursorForwards();
            }
          else
            {
            buffer.insert(CursorPos,1,c);
            CursorForwards();
            printf("%s",buffer.c_str()+CursorPos);
            gotoxy(X,Y);
            }
          }
      }
    }
  }




