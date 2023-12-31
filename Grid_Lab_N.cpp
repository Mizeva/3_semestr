#include <iostream>
#include <cstdint>
#include <cstring>
#include <string>
#include <cassert>

using u32 = uint32_t;
using namespace std;



template <typename T>
class DoubleBracketGrid final {                 // для последней итерации
private:
    T* row;
    using size_type = u32;
    size_type size;
public:
    DoubleBracketGrid(T* row, size_type _size) : row(row), size(_size) {}

    T& operator[](size_type _idx) const {
        if (_idx > size - 1)
        {
            throw(2);
        }
        return row[_idx];
    }
};

template <typename T, size_t N>
class Grid {
private:

    //using value_type = T;

public:
    T* data = nullptr;
    using size_type = u32;
    size_type* sizes = nullptr;
    Grid<T, N - 1> g;


    Grid(const Grid<T, N>& grid) = default; //конструктор копирования
    Grid<T, N>& operator=(Grid<T, N> const& other) = default; //оператор копирования

    Grid(Grid<T, N>&&) = default;
    Grid<T, N>& operator=(Grid<T, N>&&) = default;


    Grid()
    {
        //cerr << "1\n";
        sizes = nullptr;
        data = nullptr;

    }
    ~Grid() { delete data; }


    Grid(T const& t, T* _data = nullptr) : data(_data)
    {
        //cerr << "2\n";
        if (sizes == nullptr)
        {
            sizes = new size_type[N + 1]{ 0 };
            *sizes = N;
        }
        for (int i = 0; i < N; ++i)
            *(sizes + i + 1) = 1;
        Grid<T, N - 1> g(data, t);
    }

    template <typename ...Args>
    Grid(size_type first, Args... args) : Grid(nullptr, nullptr, first, args...) {}
    template <typename ...Args>
    Grid(T* _data, size_type* _sizes, size_type first, Args... args) : sizes(_sizes), data(_data)
    {
        //cerr << "3\n";
        if (sizes == nullptr)
        {
            sizes = new size_type[N + 1]{ 0 };
            *sizes = N;
            *(sizes + N) = first;
        }

        else
        {
            *(sizes + N) = first;
        }
        /*for (size_t i = 0; i < sizes[0] + 1; ++i) {
            cerr << sizes[i];
        }
        //cerr << '\n' << first << '\n';*/
        Grid<T, N - 1> g(data, sizes, args...);
    }

    template <typename ...Args>
    Grid(size_type first, Args... args, const T& t) : Grid(nullptr, nullptr, first, args...) {}
    template <typename ...Args>
    Grid(T* _data, size_type* _sizes, size_type first, Args... args, const T& t) : sizes(_sizes), data(_data)
    {
        //cerr << "4\n";
        if (sizes == nullptr)
        {
            sizes = new size_type[N + 1]{ first };
            *sizes = N;
        }
        else
        {
            *(sizes + N) = first;
        }
        Grid<T, N - 1> g(data, sizes, args..., t);
    }

    //DoubleBracketGrid<T> operator[](size_type _idx) {
    //    if (_idx > *(sizes + N)) {
    //        throw(1);
    //    }
    //    size_type part_size = 1;
    //    for (int i = 0; i < N; ++i)
    //    {

    //    }
    //    //return DoubleBracketGrid<T>(&data[y_idx * x_size], x_size);
    //}


    /*
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
    size_type get_x_size() const { return x_size; }*/
};


template <typename T>
class Grid<T, 2> {
private:

    //using value_type = T;

public:
    T* data = nullptr;
    using size_type = u32;
    size_type* sizes = nullptr;


    Grid(const Grid<T, 2>& grid) = default; //конструктор копирования
    Grid<T, 2>& operator=(Grid<T, 2> const& other) = default; //оператор копирования

    Grid(Grid<T, 2>&&) = default;
    Grid<T, 2>& operator=(Grid<T, 2>&&) = default;


    Grid()
    {
        //cerr << "5\n";
        data = nullptr;
        sizes = nullptr;
    }
    ~Grid() { delete data; }

    Grid(T const& t) : Grid(nullptr, t) {}
    Grid(T* _data, T const& t) : data(_data)
    {
        //cerr << "6\n";
        if (sizes == nullptr)
        {
            sizes = new size_type[2 + 1]{ 0 };
            *sizes = 2;
        }
        for (int i = 1; i < 2 + 1; ++i)
            *(sizes + i) = 1;
        size_type total_size = 1;
        for (size_type i = 1; i < (*sizes) + 1; ++i)
        {
            total_size *= *(sizes + i);
        }
        data = new T[total_size]{ 0 };
        for (int i = 0; i < total_size; ++i)
        {
            *(data + i) = t;
            cerr << *(data + i);
        }
    }

    Grid(size_type first, size_type second) : Grid(nullptr, nullptr, first, second) {}
    Grid(T* _data, size_type* _sizes, size_type first, size_type second) : sizes(_sizes), data(_data)
    {
        //cerr << "7\n";
        if (sizes == nullptr)
        {
            sizes = new size_type[2 + 1]{ 0 };
            *sizes = 2;
        }
        else
        {
            *(sizes + 1) = first;
            *(sizes + 2) = second;
        }
        size_type total_size = 1;
        for (size_type i = 1; i < (*sizes) + 1; ++i)
        {
            total_size *= *(sizes + i);
        }
        data = new T[total_size]{ 0 };
        //for (int i = 0; i < total_size; ++i)
            //cerr << *(data + i);
    }

    Grid(size_type first, size_type second, const T& t) : Grid(nullptr, nullptr, first, second) {}
    Grid(T* _data, size_type* _sizes, size_type first, size_type second, const T& t) : sizes(_sizes), data(_data)
    {
        //cerr << "8\n";
        if (sizes == nullptr)
        {
            sizes = new size_type[2 + 1]{ 0 };
            *sizes = 2;
        }
        else
        {
            *(sizes + 1) = first;
            *(sizes + 2) = second;
        }
        size_t total_size = 1;
        for (int i = 1; i < (*sizes) + 1; ++i)
        {
            total_size *= *(sizes + i);
        }
        /*for (size_t i = 0; i < sizes[0] + 1; ++i) {
            cerr << sizes[i];
        }*/
        //cerr << "ts\n" << total_size << "\n";
        data = new T[total_size]{ 0 };

        for (int i = 0; i < total_size; ++i)
        {
            *(data + i) = t;
            //cerr << *(data + i);
        }
    }

    /*DoubleBracketGrid<T> operator[](size_type _idx) {
        if (_idx > *(sizes + 2) - 1) {
            throw(1);
        }
        return DoubleBracketGrid<T>(&data[_idx * *(sizes + 1)], *(sizes + 1));
    }*/


    /*
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
    size_type get_x_size() const { return x_size; }*/
};


int main()
{

    //Grid<int, 3> g(1);
    //Grid<int, 3> g1(1, 2, 3);

    return 0;
}
