#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include "plateforme.h"

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif // WX_PRECOMP

#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/sizer.h>


class Board : public wxPanel
{
    //DECLARE_EVENT_TABLE()
public:
    Board(wxFrame *parent);
    void Start();
    void Pause();
    void lineRemovedChanged(int numLines);

protected:
    void OnPaint(wxPaintEvent& event);
    void OnKeyDOwn(wxKeyEvent& event);
    void OnTimer(wxCommandEvent& event);

private:
    enum {BoardWidth = 10, BoardHeigth = 22};

    Tetrominos& ShapeAt(int x, int y) {return board[(y*BoardWidth) + x];}

    int SquareWidth(){return GetClientSize().GetWidth()/BoardWidth;}
    int SquareHeigth(){return GetClientSize().GetHeight()/BoardHeigth;}

    void ClearBoard();
    void DropDown();
    void OneLineDown();
    void PieceDropped();
    void RemoveFullLines();
    void NewPiece();

    bool TryMove(const Shape& newPiece, int newX, int newY);
    void DrawSquare(wxPaintDC &dc, int x, int y, Tetrominos shape);

    wxTimer *timer;
    bool isStarted;
    bool isPaused;
    bool isFallingFinished;
    Shape curPiece;
    int curX;
    int curY;
    int numLinesRemoved;
    Tetrominos board[BoardWidth * BoardHeigth];
    wxStatusBar *m_stsbar;

};


#endif // BOARD_H_INCLUDED
