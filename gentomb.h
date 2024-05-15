#ifndef GENTOMB_HPP
#define GENTOMB_HPP

template<typename T>
class GenTomb {
private:
    int size; // Tömb mérete
    T *data; // Pointer a dinamikusan lefoglalt tömbre

public:
    // Konstruktor: inicializálja a méretet és lefoglalja a memóriát
    GenTomb() : size(0), data(nullptr) {}

    // Destruktor: felszabadítja a lefoglalt memóriát
    ~GenTomb() { delete[] data; }

    //Konstruktor: átmásolja egy másik azonos típusú tömbből az elemeket
    GenTomb(const GenTomb &copy) : size(copy.size), data(new T[copy.size]) {
        for (int i = 0; i < size; ++i) {
            data[i] = copy.data[i];
        }
    }

    // Elem hozzáadása a tömbhöz
    void add(T item) {
        T *newData = new T[size + 1];
        for (int i = 0; i < size; ++i)
            newData[i] = data[i];
        newData[size] = item;
        delete[] data;
        data = newData;
        ++size;
    }

    // Elem törlése a tömbből
    void remove(T item) {
        T* temp = new T[size-1];
        for (int i = 0, j = 0; i < size; i++, j++)
            if (data[i] != item && size != 0)
                temp[j] = data[i];
        --size;
        delete[] data;
        data = temp;

    }

    T &operator[](int index) { return data[index]; }

    GenTomb &operator=(T temp) {
        for (int i = 0; i < size; i++)
            data[i] = temp;
        return *this;
    }

    int getSize() { return size; }
};

#endif // GENTOMB_HPP
