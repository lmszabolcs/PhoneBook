#ifndef GENTOMB_HPP
#define GENTOMB_HPP

#include "memtrace.h"
/**
 * @class GenTomb
 * @brief A generic, dynamically-sized array template class.
 * @tparam T The type of elements stored in the array.
 */
template<typename T>
class GenTomb {
private:
    size_t size; ///< The current number of elements in the array.
    T *data;  ///< Pointer to the dynamically allocated array.

public:
    /**
     * @brief Default constructor.
     * Creates an empty GenTomb with size 0.
     */
    GenTomb() : size(0) { data = new T[size]; }

    /**
     * @brief Destructor.
     * Deallocates the dynamically allocated memory.
     */
    ~GenTomb() { delete[] data; }

    /**
     * @brief Copy constructor.
     * Creates a new GenTomb as a deep copy of another GenTomb.
     * @param copy The GenTomb to copy from.
     */
    GenTomb(const GenTomb &copy) : size(copy.size), data(new T[copy.size]) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = copy.data[i];
        }
    }

    /**
     * @brief Adds an element to the end of the array.
     * @param item The element to add.
     */
    void add(T item) {
        T *newData = new T[size + 1];
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        newData[size] = item;
        delete[] data;
        data = newData;
        ++size;
    }

    /**
     * @brief Removes the first occurrence of an element from the array.
     * @param item The element to remove.
     */
    void remove(T item) {
        int j = 0;
        for (size_t i = 0; i < size; i++) {
            if (data[i] != item) {
                data[j++] = data[i];
            }
        }

        size = j;
        if (j == 0) {
            delete[] data;
            data = nullptr;
        }
    }

    /**
     * @brief Accesses an element at a specific index.
     * @param index The index of the element to access.
     * @return A reference to the element at the specified index.
     */
    T &operator[](size_t index) const { return data[index]; }

    /**
     * @brief Assignment operator overload.
     * @param temp The value to assign.
     * @return A reference to the modified GenTomb object.
     */
    GenTomb &operator=(T temp) {
        for (size_t i = 0; i < size; i++) {
            data[i] = temp;
        }
        return *this;
    }

    /**
     * @brief Gets the current size of the array.
     * @return The number of elements in the array.
     */
    size_t getSize() const { return size; }
};

#endif // GENTOMB_HPP
