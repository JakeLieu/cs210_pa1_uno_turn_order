#pragma once
#include <iostream>
#include "Node.h"
#include "List.h"

// Solution file. Lab 3's LinkedList plus addBack, getFront, isEmpty, size.
// tail_ is back so addBack is O(1). size_ is new so size() is O(1).

template <typename T>
class LinkedList : public List<T> {
public:
    LinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}

    void addFront(T* value) override {
        Node<T>* fresh = new Node<T>(value);
        fresh->next = head_;
        head_ = fresh;
        if (tail_ == nullptr) {
            tail_ = fresh;          // first node is both head and tail
        }
        ++size_;
    }

    void addBack(T* value) override {
        Node<T>* fresh = new Node<T>(value);
        if (tail_ == nullptr) {
            head_ = fresh;          // first node is both head and tail
            tail_ = fresh;
        } else {
            tail_->next = fresh;
            tail_ = fresh;
        }
        ++size_;
    }

    void deleteFront() override {
        if (head_ == nullptr) {
            std::cout << "LinkedList is empty." << std::endl;
            return;
        }
        Node<T>* doomed = head_;
        head_ = head_->next;
        if (head_ == nullptr) {
            tail_ = nullptr;        // list is empty again
        }
        delete doomed->data;
        delete doomed;
        --size_;
    }

    T* getFront() const override {
        if (head_ == nullptr) {
            return nullptr;
        }
        return head_->data;
    }

    bool isEmpty() const override {
        return head_ == nullptr;
    }

    int size() const override {
        return size_;
    }

    bool search(T* value) const override {
        Node<T>* current = head_;
        while (current != nullptr) {
            if (*current->data == *value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void print() const override {
        Node<T>* current = head_;
        while (current != nullptr) {
            std::cout << *current->data << ",";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // New for Uno Turn Order Lab
    void addAnywhere(int position, T* value) override {
        if (position < 0 || position > size_) {
            std::cout << "Invalid position." << std::endl;
            return;
        }

        if (position == 0) {
            addFront(value);
            return;
        }

        if (position == size_) {
            addBack(value);
            return;
        }

        Node<T>* currentNode = head_;
        for (int i = 0; i < position - 1; i++) {
            currentNode = currentNode->next;
        }

        Node<T>* newNode = new Node<T>(value);
        newNode->next = currentNode->next;
        currentNode->next = newNode;

        size_++;
    }

    void deleteAnywhere(int position) override {
        if (position < 0 || position > size_) {
            std::cout << "Invalid position." << std::endl;
            return;
        }

        if (position == 0) {
            deleteFront();
            return;
        }

        Node<T>* currentNode = head_;
        for (int i = 0; i < position - 1; i++) {
            currentNode = currentNode->next;
        }

        Node<T>* deleteNode = currentNode->next;
        currentNode->next = deleteNode->next;

        if (deleteNode == tail_) {
            tail_ = currentNode;
        }

        delete deleteNode->data;
        delete deleteNode;

        size_--;
    }

    void reverse() override {
        if (size_ <= 1) {
            return;
        }

        Node<T>* newNextNode = nullptr;
        Node<T>* currentNode = head_;
        Node<T>* savedNode = nullptr;

        tail_ = head_;

        for (int i = 0; i < size_; i++) {
            savedNode = currentNode->next;
            currentNode->next = newNextNode;
            newNextNode = currentNode;
            currentNode = savedNode;
        }

        head_ = newNextNode;
    }

    void concat(List<T>* otherGame) override {
        LinkedList<T>* otherGameCast = dynamic_cast<LinkedList<T>*>(otherGame);

        if (otherGameCast == nullptr) {
            std::cout << "Invalid list." << std::endl;
            return;
        }

        if (otherGameCast->size_ == 0) {
            return;
        }

        if (size_ == 0) {
            head_ = otherGameCast->head_;
            tail_ = otherGameCast->tail_;
            size_ = otherGameCast->size_;
        }
        else {
            Node<T>* currentNode = head_;

            for (int i = 0; i < size_ - 1; i++) {
                currentNode = currentNode->next;
            }

            currentNode->next = otherGameCast->head_;

            tail_ = otherGameCast->tail_;
            size_ += otherGameCast->size_;
        }

        otherGameCast->head_ = nullptr;
        otherGameCast->tail_ = nullptr;
        otherGameCast->size_ = 0;
    }

    ~LinkedList() override {
        while (head_ != nullptr) {
            Node<T>* doomed = head_;
            head_ = head_->next;
            delete doomed->data;
            delete doomed;
        }
    }

private:
    Node<T>* head_;
    Node<T>* tail_;
    int size_;
};
