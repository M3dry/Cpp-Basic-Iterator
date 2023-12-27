#include <vector>
#include <string>
#include <iostream>
#include <ranges>
#include <cstddef>
#include <compare>

template <class T>
class Iter {
public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::contiguous_iterator_tag;

    Iter() : ptr(nullptr) {};
    Iter(T* ptr) : ptr(ptr) {};

    bool operator==(const Iter<T>& sentinel) const {
        return ptr == sentinel.ptr;
    };

    bool operator!=(const Iter& sentinel) const {
        return ptr != sentinel.ptr;
    }

    T& operator*() const {
        return *ptr;
    };

    Iter& operator++() {
        ++ptr;
        return *this;
    }

    Iter operator++(int) {
        Iter tmp = *this;
        ++*this;
        return tmp;
    }

    Iter& operator--() {
        --ptr;
        return *this;
    }

    Iter operator--(int) {
        Iter tmp = *this;
        --*this;
        return tmp;
    }

    Iter& operator+=(const difference_type& other) {
        ptr += other;
        return *this;
    }

    friend Iter operator+(const Iter& lhs, const difference_type& rhs) {
        Iter iter = lhs;
        iter += rhs;
        return iter;
    }

    friend Iter operator+(const difference_type& lhs, const Iter& rhs) {
        return rhs + lhs;
    }

    Iter& operator-=(const difference_type& other) {
        ptr -= other;
        return *this;
    }

    friend Iter operator-(const Iter& lhs, const difference_type& rhs) {
        Iter iter = lhs;
        iter -= rhs;
        return iter;
    }

    friend difference_type operator-(const Iter& i, const Iter& s) {
        return i.ptr - s.ptr;
    }

    value_type& operator[](const difference_type& i) const {
        return *(ptr + i);
    }

    friend std::strong_ordering operator<=>(const Iter& lhs, const Iter& rhs) {
        if (lhs.ptr > rhs.ptr) return std::strong_ordering::greater;
        else if (lhs.ptr == rhs.ptr) return std::strong_ordering::equal;
        else return std::strong_ordering::less;
    }

    T* operator->() const {
        return ptr;
    }
private:
    T* ptr;
};

template <class T, unsigned int S>
class Box {
public:

    Box() = default;

    T& operator[](std::size_t i) {
        return array[i];
    }

    std::size_t size() const {
        return S;
    }

    Iter<T> begin() const {
        return Iter((T*)array);
    }

    Iter<T> end() const {
        return Iter((T*)array + S);
    }
private:
    T array[S];
};

int main()
{
    static_assert(std::contiguous_iterator<Iter<int>>);

    Box<int, 20> box;
    for (std::size_t i = 0; i < 20; i++) {
        box[i] = i;
    }

    std::cout << "[ ";
    for (auto const& i : box | std::views::reverse) {
        std::cout << i << " ";
    }
    std::cout << " ]" << std::endl;
}
