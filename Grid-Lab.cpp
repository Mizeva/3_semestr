#include <iostream>
#include <cstdint>
#include <cstring>
#include <string>
#include <cassert>

using u32 = uint32_t;
using namespace std;



template <typename T>
class DoubleBracketGrid final {
private:
    T* row;
    using size_type = u32;
    size_type x_size;
public:
    DoubleBracketGrid(T* row, size_type x_size) : row(row), x_size(x_size) {}

    T& operator[](size_type x_idx) const {
        if (x_idx > x_size - 1)
        {
            throw(2);
        }
        return row[x_idx];
    }
};

template <typename T>
class Grid final {
private:

    //using value_type = T;

public:
    T* data;
    using size_type = u32;
    size_type y_size, x_size;


    Grid(const Grid& grid) = default; //конструктор копирования
    Grid<T>& operator=(Grid<T> const &other) { //оператор копирования
        Grid<T> copy( other );
        swap(copy, this);
        return *this;
    }

    Grid(Grid<T>&&) = default; 
    Grid<T>& operator=(Grid<T>&&) = default;


    Grid() : y_size(0), x_size(0), data(nullptr) {}
    ~Grid() { delete data; }

    Grid(T const& t) : y_size(1), x_size(1), data(new T[1]{ t }) { } // done 1.1
    Grid(size_type y_size, size_type x_size) : data(new T[x_size * y_size]{0}), y_size(y_size), x_size(x_size) {}  // done 1.2
    Grid(size_type y_size, size_type x_size, const T& t) : y_size(y_size), x_size(x_size) { // done 1.3
        data = new T[y_size * x_size];
        for (size_t i = 0; i < x_size * y_size; ++i) { *(data + i) = t; }
    } 

    DoubleBracketGrid<T> operator[](size_type y_idx) {
        if (y_idx > y_size - 1) {
            throw(1);
        }
        return DoubleBracketGrid<T>(&data[y_idx * x_size], x_size);
    }



    T& operator()(size_type y_idx, size_type x_idx) const {
        return data[y_idx * x_size + x_idx];
    }

    Grid<T>& operator=(T const& t) {
        for (auto it = data, end = data + x_size * y_size; it != end; ++it)
        {
            *it = t;
        }
        return*this;
    }

    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }
};


int main()
{
    /*u32 data = 77;
    u32 x = 2, y = 2;


    Grid<u32> a(x, y, data);

    try {
        cout << a[1][2] << '\n';
    }
    catch ( const int& e) {
        if (e == 1)
        {
            cout << "Y index is bigger than grid size\n";
        }
        else if (e == 2)
        {
            cout << "X index is bigger than grid size\n";
        }
    }

    std::cerr << "x = " << x << ", y = " << y << " data = {";
    for (size_t i = 0; i < 4; ++i) {
        std::cerr << data << " ";
    }
    std::cerr << "}\n";

    std::cerr << *(a.data) << " " << *(a.data + 1) << " " << *(a.data + 2) << " " << *(a.data + 3);
    */

    Grid<float> g(3, 2, 0.0f);
    assert(3 == g.get_y_size());
    assert(2 == g.get_x_size());

    using gsize_t = Grid<int>::size_type;

    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            assert(0.0f == g[y_idx][x_idx]);

    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            g[y_idx][x_idx] = 1.0f;

    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            assert(1.0f == g(y_idx, x_idx));

    return 0;
}