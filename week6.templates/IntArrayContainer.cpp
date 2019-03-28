#include "IntArrayContainer.h"
#include <iostream>

template<typename T>
bool ArrayContainer<T>::allocateMemory(const int& capacity) {
    this->array = new(std::nothrow) int[capacity];
    this->capacity = !this->array ? 0 : capacity;
    return this->array != nullptr;
}

template<typename T>
ArrayContainer<T>::ArrayContainer() {
    this->size = 0;
    this->allocateMemory(4);
}


ArrayContainer::ArrayContainer(const int& capacity) {
    this->size = 0;
    this->allocateMemory(capacity);
}


ArrayContainer::ArrayContainer(const ArrayContainer& other) {
    copy(other);
}

ArrayContainer& ArrayContainer::operator=(const ArrayContainer& other) {
    if (this != &other) {
        destroy();
        copy(other);
    }
    return *this;
}

ArrayContainer::~ArrayContainer() {
    destroy();
}

void ArrayContainer::destroy() {
    delete [] array;
    this->array = nullptr;
    this->capacity = 0;
    this->size = 0;
}

void ArrayContainer::copy(const ArrayContainer& other) {
    this->size = 0;
    if (this->allocateMemory(other.capacity)) {
        this->size = other.size;
        for(int indx = 0; indx <this->size; indx++) {
            this->array[indx] = other.array[indx];
        }
    }
}

void ArrayContainer::resize() {
    int* tempContainer = this->array;
    int oldCapacity = this->capacity;

    if (this->allocateMemory(this->capacity*2)) {
        for(int indx = 0; indx <this->size; indx++) {
            this->array[indx] = tempContainer[indx];
        }
        delete [] tempContainer;
    } else {
        // in case we cannot allocate memory - we need to fallback to the old container and dimensions
        this->array = tempContainer;
        this->capacity = oldCapacity;
    }

}

bool ArrayContainer::empty() const {
    return this->size == 0;
}

bool ArrayContainer::full() const {
    return this->size == this->capacity;
}

void ArrayContainer::add(const int& elem) {
    if (full()) {
        resize();
    }
    this->array[size++] = elem;
}

int ArrayContainer::count() const {
    return this->size;
}

void ArrayContainer::pop() {
    if (!empty()) {
        this->size--;
    }
}

int ArrayContainer::locate(const int& elem) const {
    if (empty()) {
        return -1;
    }

    int i = 0;
    for(;i<this->size && this->array[i] != elem;i++) { }

    return i < this->size ? i : -1;
}

void ArrayContainer::remove(const int& elem) {
    if (this->empty()) {
        return;
    }

    int i=0;
    const int elemIndex = this->locate(elem);

    if (elemIndex != -1) {
        std::swap(this->array[i], this->array[size-1]);
        pop();
    }
}

void ArrayContainer::print() const {
    for(int i=0; i< this->size; i++) {
        std::cout<<this->array[i] << " ";
    }
    std::cout<< std::endl;
}

bool ArrayContainer::member(const int& elem) const {
    const int elementIndex = this->locate(elem);
    return elementIndex != -1;
}

//not the best solution at all
int ArrayContainer::find(predicate p) const {
    int dummy;

    if (this->empty()) {
        return dummy;
    }

    int elemIndex = 0;
    for(;elemIndex < this->size && !p(this->array[elemIndex]); elemIndex++) {}

    // assert(elemIndex < this->size);
    int foundElement = elemIndex < this->size ? this->array[elemIndex] : dummy;
    return foundElement;
}

ArrayContainer ArrayContainer::filter(predicate p) const {
    ArrayContainer result;

    for(int i=0;i<this->size; i++) {
        if (p(this->array[i])) {
            result.add(this->array[i]);
        }
    }

    return result;
}

void ArrayContainer::map(mapper m) {
    for(int i=0; i<this->size; i++) {
        m(this->array[i]);
    }
}

ArrayContainer ArrayContainer::intersection(const ArrayContainer& other) const {
    ArrayContainer result;

    for(int i=0; i<this->size; i++) {
        if(other.member(this->array[i]) && !result.member(this->array[i])) {
            result.add(this->array[i]);
        }
    }

    return result;
}

ArrayContainer ArrayContainer::complement(const ArrayContainer& other) const {
    ArrayContainer result;

    for(int i=0; i<this->size; i++) {
        if(!other.member(this->array[i]) && !result.member(this->array[i])) {
            result.add(this->array[i]);
        }
    }

    return result;
}

ArrayContainer ArrayContainer::unionWith(const ArrayContainer& other) const {
    ArrayContainer result;

    for(int i=0; i<this->size; i++) {
        result.add(this->array[i]);
    }

    for(int i=0; i<other.size; i++) {
        result.add(other.array[i]);
    }
    return result;
}

ArrayContainer ArrayContainer::operator+(const int& elem) const {
    ArrayContainer result(*this);
    result.add(elem);
    return result;
}

void ArrayContainer::operator+=(const int& elem) {
    this->add(elem);
}

ArrayContainer ArrayContainer::operator+(const ArrayContainer& other) const {
    return this->unionWith(other);
}

void ArrayContainer::operator --(int) {
    this->pop();
}

ArrayContainer::operator bool() const {
    return !this->empty();
}