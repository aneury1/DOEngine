
#include "Application.h"
#include "GameObject.h"
#include "Grids.h"
#include <Event.h>
#include <GameState.h>
#include "DOEngine_SDL_includes.h"
#include <iostream>
#include <map>
#include <memory>
#include <string>
using namespace doengine;

constexpr int ROWS = 20;
constexpr int COLUMNS = 10;

std::vector<doengine::Color> GetCellColors()
{
    return {
        doengine::Colors::blue,    doengine::Colors::darkGrey,
        doengine::Colors::green,   doengine::Colors::red,
        doengine::Colors::orange,  doengine::Colors::yellow1,
        doengine::Colors::purple1, doengine::Colors::cyan,
        doengine::Colors::blue,    doengine::Colors::black,
    };
}
struct Position
{
    int row;
    int col;

    Position(int r, int c)
    {
        row = r;
        col = c;
    }
};

struct Block
{

    doengine::Renderer* renderer;
    Block();
    void Draw(int offsetX, int offsetY);
    void Move(int rows, int columns);
    std::vector<Position> GetCellPositions();
    void Rotate();
    void UndoRotation();
    int id;
    std::map<int, std::vector<Position>> cells;

    int cellSize;
    int rotationState;
    std::vector<Color> colors;
    int rowOffset;
    int columnOffset;
};
Block::Block()
{
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;
    columnOffset = 0;
}

void Block::Draw(int offsetX, int offsetY)
{
    std::vector<Position> tiles = GetCellPositions();
    for (Position item : tiles)
    {
        renderer->DrawFillRect({item.col * cellSize + offsetX,
                                item.row * cellSize + offsetY, cellSize - 1,
                                cellSize - 1},
                               colors[id]);
    }
}

void Block::Move(int rows, int columns)
{
    rowOffset += rows;
    columnOffset += columns;
}

std::vector<Position> Block::GetCellPositions()
{
    std::vector<Position> tiles = cells[rotationState];
    std::vector<Position> movedTiles;
    for (Position item : tiles)
    {
        Position newPos =
            Position(item.row + rowOffset, item.col + columnOffset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}

void Block::Rotate()
{
    rotationState++;
    if (rotationState == (int)cells.size())
    {
        rotationState = 0;
    }
}

void Block::UndoRotation()
{
    rotationState--;
    if (rotationState == -1)
    {
        rotationState = cells.size() - 1;
    }
}
class LBlock : public Block
{
  public:
    LBlock()
    {
        id = 1;
        cells[0] = {Position(0, 2), Position(1, 0), Position(1, 1),
                    Position(1, 2)};
        cells[1] = {Position(0, 1), Position(1, 1), Position(2, 1),
                    Position(2, 2)};
        cells[2] = {Position(1, 0), Position(1, 1), Position(1, 2),
                    Position(2, 0)};
        cells[3] = {Position(0, 0), Position(0, 1), Position(1, 1),
                    Position(2, 1)};
        Move(0, 3);
    }
};

class JBlock : public Block
{
  public:
    JBlock()
    {
        id = 2;
        cells[0] = {Position(0, 0), Position(1, 0), Position(1, 1),
                    Position(1, 2)};
        cells[1] = {Position(0, 1), Position(0, 2), Position(1, 1),
                    Position(2, 1)};
        cells[2] = {Position(1, 0), Position(1, 1), Position(1, 2),
                    Position(2, 2)};
        cells[3] = {Position(0, 1), Position(1, 1), Position(2, 0),
                    Position(2, 1)};
        Move(0, 3);
    }
};

class IBlock : public Block
{
  public:
    IBlock()
    {
        id = 3;
        cells[0] = {Position(1, 0), Position(1, 1), Position(1, 2),
                    Position(1, 3)};
        cells[1] = {Position(0, 2), Position(1, 2), Position(2, 2),
                    Position(3, 2)};
        cells[2] = {Position(2, 0), Position(2, 1), Position(2, 2),
                    Position(2, 3)};
        cells[3] = {Position(0, 1), Position(1, 1), Position(2, 1),
                    Position(3, 1)};
        Move(-1, 3);
    }
};

class OBlock : public Block
{
  public:
    OBlock()
    {
        id = 4;
        cells[0] = {Position(0, 0), Position(0, 1), Position(1, 0),
                    Position(1, 1)};
        Move(0, 4);
    }
};

class SBlock : public Block
{
  public:
    SBlock()
    {
        id = 5;
        cells[0] = {Position(0, 1), Position(0, 2), Position(1, 0),
                    Position(1, 1)};
        cells[1] = {Position(0, 1), Position(1, 1), Position(1, 2),
                    Position(2, 2)};
        cells[2] = {Position(1, 1), Position(1, 2), Position(2, 0),
                    Position(2, 1)};
        cells[3] = {Position(0, 0), Position(1, 0), Position(1, 1),
                    Position(2, 1)};
        Move(0, 3);
    }
};

class TBlock : public Block
{
  public:
    TBlock()
    {
        id = 6;
        cells[0] = {Position(0, 1), Position(1, 0), Position(1, 1),
                    Position(1, 2)};
        cells[1] = {Position(0, 1), Position(1, 1), Position(1, 2),
                    Position(2, 1)};
        cells[2] = {Position(1, 0), Position(1, 1), Position(1, 2),
                    Position(2, 1)};
        cells[3] = {Position(0, 1), Position(1, 0), Position(1, 1),
                    Position(2, 1)};
        Move(0, 3);
    }
};

class ZBlock : public Block
{
  public:
    ZBlock()
    {
        id = 7;
        cells[0] = {Position(0, 0), Position(0, 1), Position(1, 1),
                    Position(1, 2)};
        cells[1] = {Position(0, 2), Position(1, 1), Position(1, 2),
                    Position(2, 1)};
        cells[2] = {Position(1, 0), Position(1, 1), Position(2, 1),
                    Position(2, 2)};
        cells[3] = {Position(0, 1), Position(1, 0), Position(1, 1),
                    Position(2, 0)};
        Move(0, 3);
    }
};

struct Grid
{
    doengine::Renderer* renderer;
    int rows;
    int cols;
    int cell_size;
    int grid[ROWS][COLUMNS];
    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowDown(int row, int numRows);
    int numRows;
    int numCols;
    int cellSize;
    std::vector<Color> colors;
    Grid()
    {
        renderer = doengine::Application::getApplication()->getRender();
        cell_size = 32;
    }

    void reset()
    {
        for (int r = 0; r < ROWS; r++)
        {
            for (int c = 0; c < COLUMNS; c++)
            {
                grid[r][c] = 1;
            }
        }
    }
    void Render()
    {
        for (int r = 0; r < ROWS; r++)
        {
            for (int c = 0; c < COLUMNS; c++)
            {
                doengine::Rect offset;
                doengine::LogOuput(doengine::logger_type::Error, "(%d, %d)", r,
                                   c);
                offset.x = c * cell_size;
                offset.y = r * cell_size;
                offset.w = cell_size;
                offset.h = cell_size;

                int cell_value = grid[r][c];

                renderer->DrawFillRect(offset, GetCellColors()[cell_value]);
                offset.LogIt();
                renderer->DrawRect(offset, doengine::Colors::white);
            }
        }
    }
    bool IsCellOutside(int row, int column);
    bool IsCellEmpty(int row, int column);
    int ClearFullRows();
};
bool Grid::IsCellOutside(int row, int column)
{
    if (row >= 0 && row < numRows && column >= 0 && column < numCols)
    {
        return false;
    }
    return true;
}

bool Grid::IsCellEmpty(int row, int column)
{
    if (grid[row][column] == 0)
    {
        return true;
    }
    return false;
}

int Grid::ClearFullRows()
{
    int completed = 0;
    for (int row = numRows - 1; row >= 0; row--)
    {
        if (IsRowFull(row))
        {
            ClearRow(row);
            completed++;
        }
        else if (completed > 0)
        {
            MoveRowDown(row, completed);
        }
    }
    return completed;
}

bool Grid::IsRowFull(int row)
{
    for (int column = 0; column < numCols; column++)
    {
        if (grid[row][column] == 0)
        {
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int row)
{
    for (int column = 0; column < numCols; column++)
    {
        grid[row][column] = 0;
    }
}

void Grid::MoveRowDown(int row, int numRows)
{
    for (int column = 0; column < numCols; column++)
    {
        grid[row + numRows][column] = grid[row][column];
        grid[row][column] = 0;
    }
}

struct TetrisState : public doengine::GameState
{
    doengine::Renderer* render;
    bool gameOver;
    int score;
    void MoveBlockLeft()
    {
        if (!gameOver)
        {
            currentBlock.Move(0, -1);
            if (IsBlockOutside() || BlockFits() == false)
            {
                currentBlock.Move(0, 1);
            }
        }
    }
    void MoveBlockRight()
    {
        if (!gameOver)
        {
            currentBlock.Move(0, 1);
            if (IsBlockOutside() || BlockFits() == false)
            {
                currentBlock.Move(0, -1);
            }
        }
    }
    Block GetRandomBlock()
    {
        if (blocks.empty())
        {
            blocks = GetAllBlocks();
        }
        int randomIndex = rand() % blocks.size();
        Block block = blocks[randomIndex];
        blocks.erase(blocks.begin() + randomIndex);
        return block;
    }
    std::vector<Block> GetAllBlocks()
    {
        return {IBlock(), JBlock(), LBlock(), OBlock(),
                SBlock(), TBlock(), ZBlock()};
    }
    bool IsBlockOutside()
    {
        std::vector<Position> tiles = currentBlock.GetCellPositions();
        for (Position item : tiles)
        {
            if (grid.IsCellOutside(item.row, item.col))
            {
                return true;
            }
        }
        return false;
    }
    void RotateBlock()
    {
        if (!gameOver)
        {
            currentBlock.Rotate();
            if (IsBlockOutside() || BlockFits() == false)
            {
                currentBlock.UndoRotation();
            }
            else
            {
                /// PlaySound(rotateSound);
            }
        }
    }
    void LockBlock()
    {
        std::vector<Position> tiles = currentBlock.GetCellPositions();
        for (Position item : tiles)
        {
            grid.grid[item.row][item.col] = currentBlock.id;
        }
        currentBlock = nextBlock;
        if (BlockFits() == false)
        {
            gameOver = true;
        }
        nextBlock = GetRandomBlock();
        int rowsCleared = grid.ClearFullRows();
        if (rowsCleared > 0)
        {
            ///PlaySound(clearSound);
            UpdateScore(rowsCleared, 0);
        }
    }
    bool BlockFits()
    {
        std::vector<Position> tiles = currentBlock.GetCellPositions();
        for (Position item : tiles)
        {
            if (grid.IsCellEmpty(item.row, item.col) == false)
            {
                return false;
            }
        }
        return true;
    }
    void Reset()
    {
        grid.reset();
        blocks = GetAllBlocks();
        currentBlock = GetRandomBlock();
        nextBlock = GetRandomBlock();
        score = 0;
    }
    void UpdateScore(int linesCleared, int moveDownPoints)
    {
        switch (linesCleared)
        {
        case 1:
            score += 100;
            break;
        case 2:
            score += 300;
            break;
        case 3:
            score += 500;
            break;
        default:
            break;
        }

        score += moveDownPoints;
    }
    Grid grid;
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    virtual void OnEnter()
    {
        render = Application::getApplication()->getRender();
        grid.reset();
        blocks = GetAllBlocks();
        currentBlock = GetRandomBlock();
        nextBlock = GetRandomBlock();
        gameOver = false;
        score = 0;
    }
    virtual void OnExit()
    {
    }
    virtual void Update(float elapsed)
    {

        if (doengine::Event::getLastKeyPressed(SDL_SCANCODE_LEFT))
        {
            MoveBlockLeft();
        }

        if (doengine::Event::getLastKeyPressed(SDL_SCANCODE_RIGHT))
        {
            MoveBlockRight();
        }

        if (doengine::Event::getLastKeyPressed(SDL_SCANCODE_DOWN))
        {
            MoveBlockDown();
            UpdateScore(0, 1);
        }
        if (doengine::Event::getLastKeyPressed(SDL_SCANCODE_UP))
        {
            RotateBlock();
        }
    }
    virtual void Render()
    {
        render->setDrawColor(doengine::Colors::black);
        render->clear();
        grid.Render();
        currentBlock.Draw(11, 11);
        switch (nextBlock.id)
        {
        case 3:
            nextBlock.Draw(255, 290);
            break;
        case 4:
            nextBlock.Draw(255, 280);
            break;
        default:
            nextBlock.Draw(270, 270);
            break;
        }
    }
    ///     void HandleInput();
    void MoveBlockDown()
    {
        if (!gameOver)
        {
            currentBlock.Move(1, 0);
            if (IsBlockOutside() || BlockFits() == false)
            {
                currentBlock.Move(-1, 0);
                LockBlock();
            }
        }
    }
};

enum SampleStateId : int
{
    TetrisStateID = 1
};

int main(int argc, char* argv[])
{
    auto app = doengine::Application::getApplication();
    doengine::Rect rect{800, 900};
    app->createWindow(rect);
    auto game = new TetrisState();
    app->addState(game, TetrisStateID);
    app->setState(TetrisStateID);
    while (app->IsRunning())
    {
        app->PollEvent();
        app->Update();
        app->Render();
    }
    app->Quit();
    return 0;
}
