#pragma once
#include <iostream>
#include "List.h"

// Solution file. Lab 3's ArrayList plus addBack, getFront, isEmpty, size.

template <typename T>
class ArrayList : public List<T> {
public:
    ArrayList() : size_(0) {}

    void addFront(T* value) override {
        if (size_ >= CAPACITY) {
            std::cout << "Max players reached." << std::endl;
            return;
        }
        for (int i = size_; i > 0; --i) {
            data_[i] = data_[i - 1];
        }
        data_[0] = value;
        ++size_;
    }

    void addBack(T* value) override {
        if (size_ >= CAPACITY) {
            std::cout << "Max players reached." << std::endl;
            return;
        }
        data_[size_] = value;       // no shifting needed at the back
        ++size_;
    }

    void deleteFront() override {
        if (size_ == 0) {
            std::cout << "No players to delete." << std::endl;
            return;
        }
        delete data_[0];
        for (int i = 0; i < size_ - 1; i++) {
            data_[i] = data_[i + 1];
        }
        --size_;
    }

    T* getFront() const override {
        if (size_ == 0) {
            return nullptr;
        }
        return data_[0];
    }

    bool isEmpty() const override {
        return size_ == 0;
    }

    int size() const override {
        return size_;
    }

    bool search(T* value) const override {
        for (int i = 0; i < size_; i++) {
            if (*data_[i] == *value) {
                return true;
            }
        }
        return false;
    }

    void print() const override {
        for (int i = 0; i < size_; i++) {
            std::cout << *data_[i] << ",";
        }
        std::cout << std::endl;
    }

    // New for Uno Turn Order Lab
    void addAnywhere(int position, T* value) override {
        if (size_ >= CAPACITY) {
            std::cout << "Max players reached." << std::endl;
            return;
        }

        if (position < 0 || position > size_) {
            std::cout << "Invalid position." << std::endl;
            return;
        }

        for (int i = size_; i > position; i--) {
            data_[i] = data_[i - 1];
        }

        data_[position] = value;
        ++size_;
    }

    void deleteAnywhere(int position) override {
        if (size_ == 0) {
            std::cout << "No players to remove." << std::endl;
            return;
        }

        if (position < 0 || position >= size_) {
            std::cout << "Invalid position." << std::endl;
            return;
        }

        delete data_[position];

        for (int i = position; i < size_-1; i++) {
            data_[i] = data_[i + 1];
        }

        --size_;
    }

    void reverse() override {
        if (size_ <= 1) {
            return;
        }

        int swapIndex = size_ - 1;
        T* tempValue;

        for (int i = 0; i < size_ / 2; i++) {
            tempValue = data_[i];
            data_[i] = data_[swapIndex];
            data_[swapIndex] = tempValue;
            swapIndex--;
        }
    }

    void concat(List<T>* otherGame) override {
        ArrayList<T>* otherGameCast = dynamic_cast<ArrayList<T>*>(otherGame);

        if (otherGameCast == nullptr) {
            std::cout << "Invalid list type." << std::endl;
            return;
        }

        if (size_ + otherGameCast->size_ > CAPACITY) {
            std::cout << "Too many players" << std::endl;
            return;
        }

        for (int i = 0; i < otherGameCast->size_; i++) {
            data_[size_] = otherGameCast->data_[i];
            size_++;
        }

        otherGameCast->size_ = 0;
    }

    ~ArrayList() override {
        for (int i = 0; i < size_; i++) {
            delete data_[i];
        }
    }

private:
    static const int CAPACITY = 20;
    T* data_[CAPACITY];
    int size_;
};
