#include <iostream>
#include <cstdint>
#include <cstring>
#include <string>
#include <cassert>

using u32 = uint32_t;
using namespace std;
using size_type = uint32_t;

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



template <typename T, size_t N>
class Grid final {
private:

    //using value_type = T;

public:
    using size_type = u32;
    size_type size;
    Grid<T, N - 1> g;
    T* data = nullptr;


    Grid(const Grid<T, N>& grid) = default; //конструктор копирования
    Grid<T, N>& operator=(Grid<T, N> const& other) = default; //оператор копирования

    Grid(Grid<T, N>&&) = default;
    Grid<T, N>& operator=(Grid<T, N>&&) = default;


    Grid() : size(0), g(new Grid<T, N - 1>()), data(nullptr) {}
    ~Grid() { delete data; }

    Grid(T const& t) : size(1), g(new Grid<T, N - 1>(t)), data(new T[1]{ t }) { } //fixed

    template <typename ...Args>
    Grid(size_type first, Args... args) : size(first), g(args...) { }


    template <typename ...Args> 
    Grid(size_type first, Args... args, const T& t)
    {
        Grid(first, args..., t, data);
    }

    template <typename ...Args>
    Grid(size_type first, Args... args, const T& t, T* data) : size(first), g(args..., t)
    {
        if (data == nullptr)
        {
            data = new size_type[1]{ first };
            cerr << "one " << size << '\n';
        }
        else
        {
            *data *= first;
            cerr << "ne one " << size << '\n';
            if (N == 2)
            {
                cerr << "все плохо";
                throw(3);
            }
        }
    }

    /*DoubleBracketGrid<T> operator[](size_type y_idx) {
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
    size_type get_size()
    {
        return size * get_size();
    }*/
};


template <typename T>
class Grid<T, 2> final {
private:

    //using value_type = T;

public:
    T* data;
    using size_type = u32;
    size_type y_size, x_size;


    Grid(const Grid<T, 2>& grid) = default; //конструктор копирования
    Grid<T, 2>& operator=(Grid<T, 2> const& other) = default; //оператор копирования

    Grid(Grid<T, 2>&&) = default;
    Grid<T, 2>& operator=(Grid<T, 2>&&) = default;

    Grid() : y_size(0), x_size(0), data(nullptr) {}
    ~Grid() { delete data; }

    Grid(T const& t) : y_size(1), x_size(1), data(new T[1]{ t }) { } // done 1.1
    Grid(size_type y_size, size_type x_size) : data(new T[x_size * y_size]{ 0 }), y_size(y_size), x_size(x_size) {}  // done 1.2
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

    Grid<T, 2>& operator=(T const& t) {
        for (auto it = data, end = data + x_size * y_size; it != end; ++it)
        {
            *it = t;
        }
        return*this;
    }

    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }
    size_type get_size()
    {
        return x_size * y_size;
    }
};





int main()
{
    try {
        Grid<int, 5> grid(1, 2, 3, 4, 5, 77);
    }
    catch (int& e)
    {
        if (e == 3)
        {
            cerr << "все плохо 2";
        }
    }

    

    return 0;
}