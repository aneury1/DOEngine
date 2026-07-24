
/*
 * ============================================================================
 * DOEngine
 * Copyright (c) 2026 Victor D. Montero, Aneury Perez
 * All Rights Reserved.
 *
 * Licensed under the MIT License.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * 1. The above copyright notice, this license notice, and this disclaimer
 *    MUST be included in all copies or substantial portions of the Software.
 *
 * 2. This notice may not be removed from the original source files distributed
 *    as part of this project.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * ============================================================================
 */
#ifndef CIRCULAR_ARRAY_H_DEFINED
#define CIRCULAR_ARRAY_H_DEFINED
#include <array>

template <typename T, const int size>
class CircularArray
{

    
    static_assert(size > 0, "Size must be higher than zero");
   public:
    typedef unsigned int IndexType;
    
    std::array<T, size> _array;
 
    IndexType cursor = 0;

    void fixBound()
    {
      if(cursor >= _array.size())
         cursor = 0;
    }

    T operator++(int)
    {
        T v = _array[cursor];
        cursor++;
        fixBound();
        return v;
    }

    T& operator[](const IndexType& index)
    {
        if (index > _array.size())
        {
            return _array[0];
        }
        return _array[index];
    }
};

#endif // CIRCULAR_ARRAY_H_DEFINED