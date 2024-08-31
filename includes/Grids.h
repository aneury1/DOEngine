#pragma once
namespace doengine
{
template <const unsigned int R, const unsigned int C, typename T>
struct Grid2D
{
    T grid[R][C];

    void setValue(int r, int c, T value)
    {
        if (r < R && r >= 0)
        {
            if (c < C && c >= 0)
                grid[r][c] = value;
        }
    }

    T getValue(int r, int c)
    {
        if (r < R && r >= 0)
        {
            if (c < C && c >= 0)
                return grid[r][c];
        }
        return grid[0][0];
    }

    int getRow()
    {
        return R;
    }

    int getCol()
    {
        return C;
    }
};

} // namespace doengine