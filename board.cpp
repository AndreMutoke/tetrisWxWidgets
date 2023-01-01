#include "board.h"

Board::Board(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    timer = new wxTimer(this, 1);
    m_stsbar = parent->GetStatusBar();

    isFallingFinished = false;
    isStarted = false;
    isPaused = false;
    numLinesRemoved = 0;

    curX = 0; curY = 0;

    ClearBoard();

    Connect(wxEVT_PAINT, wxPaintEventHandler(Board::OnPaint));
    Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(Board::OnKeyDOwn));
    Connect(wxEVT_TIMER, wxCommandEventHandler(Board::OnTimer));
}
void Board::Start()
{
    if(isPaused)
        return;
    isStarted = true;
    isFallingFinished = false;
    numLinesRemoved = 0;
    ClearBoard();

    NewPiece();

    timer->Start(300);
}
void Board::Pause()
{
    if(!isStarted)
        return;
    isPaused = !isPaused;
    if(isPaused)
    {
        timer->Stop();
        m_stsbar->SetStatusText(wxT("paused"));
    }
    else
    {
        timer->Start(300);
        wxString str;
        str.Printf(wxT("%d"), numLinesRemoved);
        m_stsbar->SetStatusText(str);
    }
    Refresh();
}
void Board::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);

    wxSize sizee = GetClientSize();
    int boardTop = sizee.GetHeight() - BoardHeigth * SquareHeigth();

    for(int i=0; i<BoardHeigth; ++i)
    {
        for(int j=0; j<BoardWidth; ++j)
        {
            Tetrominos shape = ShapeAt(j, BoardHeigth-i-1);
            if(shape != NoShape)
            {
                DrawSquare(dc, 0+j*SquareWidth(), boardTop +i*SquareHeigth(), shape);
            }
        }
    }

    if(curPiece.GetShape() != NoShape)
    {
        for(int i=0; i<4; ++i)
        {
            int x = curX + curPiece.x(i);
            int y = curY - curPiece.y(i);
            DrawSquare(dc, 0 + x*SquareWidth(), boardTop + (BoardHeigth -y-1)*SquareHeigth(), curPiece.GetShape());
        }
    }
    event.Skip();
}
void Board::OnKeyDOwn(wxKeyEvent& event)
{
    if(!isStarted || curPiece.GetShape()== NoShape)
    {
        event.Skip();
        return;
    }
    int keyCode = event.GetKeyCode();
    if(keyCode == 'p' || keyCode =='P')
    {
        Pause();
        return;
    }
    if(isPaused)
        return;
    switch(keyCode)
    {
    case WXK_LEFT:
        TryMove(curPiece, curX-1, curY);
        break;
    case WXK_RIGHT:
        TryMove(curPiece, curX+1, curY);
        break;
    case WXK_DOWN:
        TryMove(curPiece.RotateRight(), curX, curY);
        break;
    case WXK_UP:
        TryMove(curPiece.RotateLeft(), curX, curY);
        break;
    case WXK_SPACE:
        DropDown();
        break;
    case 'd':
        OneLineDown();
        break;
    case 'D':
        OneLineDown();
        break;
    default:
        event.Skip();

    }
    event.Skip();
}

void Board::OnTimer(wxCommandEvent& event)
{
    if(isFallingFinished)
    {
        isFallingFinished = false;
        NewPiece();
    }
    else
    {
        OneLineDown();
    }
}

void Board::ClearBoard()
{
    for(int i=0; i<BoardHeigth*BoardWidth; ++i)
        board[i] = NoShape;
}

void Board::DropDown()
{
    int newY = curY;
    while(newY>0)
    {
        if(!TryMove(curPiece, curX, newY-1))
            break;
        --newY;
    }
    PieceDropped();
}
void Board::OneLineDown()
{
    if(!TryMove(curPiece, curX, curY-1))
        PieceDropped();
}
void Board::PieceDropped()
{
    for(int i=0; i<4; ++i)
    {
        int x = curX + curPiece.x(i);
        int y = curY - curPiece.y(i);
        ShapeAt(x, y) = curPiece.GetShape();
    }
    RemoveFullLines();

    if(!isFallingFinished)
        NewPiece();
}
void Board::RemoveFullLines()
{
    int numFullLines = 0;
    for(int i = BoardHeigth-1; i>=0; --i)
    {
        bool lineIsFull = true;
        for(int j=0; j<BoardWidth; ++j)
        {
            if(ShapeAt(j, i) == NoShape)
            {
                lineIsFull = false;
                break;
            }
        }
        if(lineIsFull)
        {
            ++numFullLines;
            for(int k=i; k<BoardHeigth - 1; ++k)
            {
                for(int j=0; j<BoardWidth; ++j)
                    ShapeAt(j, k) = ShapeAt(j, k+1);
            }
        }
    }

    if(numFullLines > 0)
    {
        numLinesRemoved += numFullLines;
        wxString str;
        str.Printf(wxT("%d"), numLinesRemoved);
        m_stsbar->SetStatusText(str);

        isFallingFinished = true;
        curPiece.SetShape(NoShape);
        Refresh();
    }
}
void Board::NewPiece()
{
    curPiece.SetRandomShape();
    curX = BoardWidth/2 + 1;
    curY = BoardHeigth-1 + curPiece.MinY();

    if(!TryMove(curPiece, curX, curY))
    {
        curPiece.SetShape(NoShape);
        timer->Stop();
        isStarted = false;
        m_stsbar->SetStatusText(wxT("Game Over"));
    }
}
bool Board::TryMove(const Shape& newPiece, int newX, int newY)
{
    for(int i=0;i<4;++i)
    {
        int x = newX + newPiece.x(i);
        int y = newY - newPiece.y(i);

        if(x<0 || x >=BoardWidth || y<0 || y>BoardHeigth)
            return false;
        if(ShapeAt(x, y) != NoShape)
            return false;

    }
    curPiece = newPiece;
    curX = newX;
    curY = newY;
    Refresh();
    return true;
}
void Board::DrawSquare(wxPaintDC& dc, int x, int y, Tetrominos shape)
{
    static wxColour colour[] = {
             wxColour(0, 0, 0),
             wxColour(204, 102, 102),
             wxColour(102, 204, 102),
             wxColour(102, 102, 204),
             wxColour(204, 204, 102),
             wxColour(204, 102, 204),
             wxColour(102, 204, 204),
             wxColour(218, 170, 0)
    };
    static wxColour light[] = {
             wxColour(0, 0, 0),
             wxColour(248, 159, 171),
             wxColour(121, 252, 121),
             wxColour(121, 121, 252),
             wxColour(252, 252, 121),
             wxColour(252, 121, 252),
             wxColour(121, 252, 252),
             wxColour(252, 198, 0)
    };
    static wxColour dark[] = {
             wxColour(0, 0, 0),
             wxColour(128, 59, 59),
             wxColour(59, 128, 59),
             wxColour(59, 59, 128),
             wxColour(128, 128, 59),
             wxColour(128, 59, 128),
             wxColour(59, 128, 128),
             wxColour(128, 98, 0)
    };

    wxPen pen(light[int(shape)]);
    pen.SetCap(wxCAP_PROJECTING);
    dc.SetPen(pen);

    dc.DrawLine(x, y + SquareHeigth() -1 , x, y);
    dc.DrawLine(x, y, x+ SquareWidth() - 1, y);

    wxPen darkPen(dark[int(shape)]);
    darkPen.SetCap(wxCAP_PROJECTING);
    dc.SetPen(darkPen);

    dc.DrawLine(x+1, y+SquareHeigth() -1, x + SquareWidth() -1, y + SquareHeigth() -1);
    dc.DrawLine(x+SquareWidth()-1, y+SquareHeigth()-1, x+SquareWidth()-1, y+1);

    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.SetBrush(wxBrush(colour[int(shape)]));
    dc.DrawRectangle(x+1, y+1, SquareWidth()-2, SquareHeigth()-2);
}
