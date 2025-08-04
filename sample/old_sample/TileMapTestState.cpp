#include <TileMapTestState.h>
#include <string>
#include <vector>
int w = 400;
int h = 600;
Canvas* pencil;
std::string tetromino[7];
int nFieldWidth = 12;
int nFieldHeight = 18;
int nScreenWidth = 80;  // Console Screen Size X (columns)
int nScreenHeight = 30; // Console Screen Size Y (rows)
// Game Logic
bool bKey[4];
int nCurrentPiece = 0;
int nCurrentRotation = 0;
int nCurrentX = nFieldWidth / 2;
int nCurrentY = 0;
int nSpeed = 20;
int nSpeedCount = 0;
bool bForceDown = false;
bool bRotateHold = true;
int nPieceCount = 0;
int nScore = 0;
std::vector<int> vLines;
bool bGameOver = false;
unsigned char* pField = nullptr;
wchar_t* screen; /// = new wchar_t[nScreenWidth*nScreenHeight];
int Rotate(int px, int py, int r)
{
    int pi = 0;
    switch (r % 4)
    {
    case 0:               // 0 degrees			// 0  1  2  3
        pi = py * 4 + px; // 4  5  6  7
        break;            // 8  9 10 11
                          // 12 13 14 15

    case 1:                      // 90 degrees			//12  8  4  0
        pi = 12 + py - (px * 4); // 13  9  5  1
        break;                   // 14 10  6  2
                                 // 15 11  7  3

    case 2:                      // 180 degrees			//15 14 13 12
        pi = 15 - (py * 4) - px; // 11 10  9  8
        break;                   // 7  6  5  4
                                 // 3  2  1  0

    case 3:                     // 270 degrees			// 3  7 11 15
        pi = 3 - py + (px * 4); // 2  6 10 14
        break;                  // 1  5  9 13
    }                           // 0  4  8 12

    return pi;
}
bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY)
{
    // All Field cells >0 are occupied
    for (int px = 0; px < 4; px++)
        for (int py = 0; py < 4; py++)
        {
            // Get index into piece
            int pi = Rotate(px, py, nRotation);

            // Get index into field
            int fi = (nPosY + py) * nFieldWidth + (nPosX + px);

            // Check that test is in bounds. Note out of bounds does
            // not necessarily mean a fail, as the long vertical piece
            // can have cells that lie outside the boundary, so we'll
            // just ignore them
            if (nPosX + px >= 0 && nPosX + px < nFieldWidth)
            {
                if (nPosY + py >= 0 && nPosY + py < nFieldHeight)
                {
                    // In Bounds so do collision check
                    if (tetromino[nTetromino][pi] != L'.' && pField[fi] != 0)
                        return false; // fail on first hit
                }
            }
        }

    return true;
}

void TileMapTestState::OnEnter()
{
    Event::AddKeydownEventListener(this);
    tetromino[0].append("..X...X...X...X."); // Tetronimos 4x4
    tetromino[1].append("..X..XX...X.....");
    tetromino[2].append(".....XX..XX.....");
    tetromino[3].append("..X..XX..X......");
    tetromino[4].append(".X...XX...X.....");
    tetromino[5].append(".X...X...XX.....");
    tetromino[6].append("..X...X..XX.....");
    pencil = new Canvas(window);
    pencil->setRect({window->getW() / 2 - w, window->getH() - h - 100, w, h});
    pencil->setCanvasBackgroundColor({255, 255, 0, 255});
    pField = new unsigned char[nFieldWidth *
                               nFieldHeight]; // Create play field buffer
    for (int x = 0; x < nFieldWidth; x++)     // Board Boundary
        for (int y = 0; y < nFieldHeight; y++)
            pField[y * nFieldWidth + x] =
                (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9
                                                                          : 0;
    wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
}
void TileMapTestState::OnExit()
{
}
void TileMapTestState::Update(float elapsed)
{
    if (bForceDown)
    {
        // Update difficulty every 50 pieces
        nSpeedCount = 0;
        nPieceCount++;
        if (nPieceCount % 50 == 0)
            if (nSpeed >= 10)
                nSpeed--;

        // Test if piece can be moved down
        if (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX,
                         nCurrentY + 1))
            nCurrentY++; // It can, so do it!
        else
        {
            // It can't! Lock the piece in place
            for (int px = 0; px < 4; px++)
                for (int py = 0; py < 4; py++)
                    if (tetromino[nCurrentPiece]
                                 [Rotate(px, py, nCurrentRotation)] != L'.')
                        pField[(nCurrentY + py) * nFieldWidth +
                               (nCurrentX + px)] = nCurrentPiece + 1;

            // Check for lines
            for (int py = 0; py < 4; py++)
                if (nCurrentY + py < nFieldHeight - 1)
                {
                    bool bLine = true;
                    for (int px = 1; px < nFieldWidth - 1; px++)
                        bLine &=
                            (pField[(nCurrentY + py) * nFieldWidth + px]) != 0;

                    if (bLine)
                    {
                        // Remove Line, set to =
                        for (int px = 1; px < nFieldWidth - 1; px++)
                            pField[(nCurrentY + py) * nFieldWidth + px] = 8;
                        vLines.push_back(nCurrentY + py);
                    }
                }

            nScore += 25;
            if (!vLines.empty())
                nScore += (1 << vLines.size()) * 100;

            // Pick New Piece
            nCurrentX = nFieldWidth / 2;
            nCurrentY = 0;
            nCurrentRotation = 0;
            nCurrentPiece = rand() % 7;

            // If piece does not fit straight away, game over!
            bGameOver = !DoesPieceFit(nCurrentPiece, nCurrentRotation,
                                      nCurrentX, nCurrentY);
        }
    }
}
void TileMapTestState::Render()
{

    for (int x = 0; x < nFieldWidth; x++)
        for (int y = 0; y < nFieldHeight; y++)
        {
            int iter1 = (y + 2) * nScreenWidth + (x + 2);
            int iter2 = pField[y * nFieldWidth + x];
            ////SDL_Log("%ld %ld", iter1, iter2);
            SDL_Log("%c", " ABCDEFG=#"[pField[y * nFieldWidth + x]]);
            /// screen[] = L" ABCDEFG=#"[pField[y*nFieldWidth + x]];
        }
#if 0
		// Draw Current Piece
		for (int px = 0; px < 4; px++)
			for (int py = 0; py < 4; py++)
				if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] != L'.')
					screen[(nCurrentY + py + 2)*nScreenWidth + (nCurrentX + px + 2)] = nCurrentPiece + 65;

#endif

    pencil->clearCanvas();
    pencil->update();
}

void TileMapTestState::OnKeydown(int code)
{
    SDL_Log("%ld", code);
    if (code == 27)
        this->window->Quit();

    // Rotate, but latch to stop wild spinning
    if (code == 1073741906)
    {
        nCurrentRotation +=
            (bRotateHold && DoesPieceFit(nCurrentPiece, nCurrentRotation + 1,
                                         nCurrentX, nCurrentY))
                ? 1
                : 0;
        bRotateHold = false;
    }
    else
        bRotateHold = true;

    nCurrentX +=
        (code == 1073741904 && DoesPieceFit(nCurrentPiece, nCurrentRotation,
                                            nCurrentX + 1, nCurrentY))
            ? 1
            : 0;
    nCurrentX -=
        (code == 1073741904 && DoesPieceFit(nCurrentPiece, nCurrentRotation,
                                            nCurrentX - 1, nCurrentY))
            ? 1
            : 0;
    nCurrentY +=
        (code == 1073741905 && DoesPieceFit(nCurrentPiece, nCurrentRotation,
                                            nCurrentX, nCurrentY + 1))
            ? 1
            : 0;
}