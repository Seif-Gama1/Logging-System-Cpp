#pragma once

#include <vector>
#include <optional>
#include <cstddef>
#include <utility>

template <typename T>
class RingBuffer {
    private:
        std::vector<std::optional<T>> buf;
        std::size_t capacity_;
        std::size_t head_;
        std::size_t tail_;
        std::size_t size_;
        
        std::size_t nextIndex(std::size_t index) const noexcept {
            return (index + 1) % capacity_;
        }
    public:
        explicit RingBuffer(std::size_t capacity_)
            : buf(capacity_), capacity_(capacity_),
            head_(0), tail_(0), size_(0) 
        {

        }
        
        /* No copy semantics */
        RingBuffer(const RingBuffer&) = delete;
        RingBuffer& operator=(const RingBuffer&) = delete;
        
        /* default move semantics */
        RingBuffer(RingBuffer&&) noexcept = default;
        RingBuffer& operator=(RingBuffer&&) noexcept = default;

        template <typename C>
        bool tryPush(C&& value) {
            if(isFull()) {
                return false;
            }

            buf[tail_] = std::move(value);
            tail_ = nextIndex(tail_);
            size_++;
            return true;
        }

        // Try to pop (fails if empty)
        std::optional<T> tryPop() {
            if(isEmpty()){
                return std::nullopt;
            }

            std::optional<T> value = std::move(buf[head_]);
            buf[head_].reset();
            head_ = nextIndex(head_);
            size_--;
            return value;
        }

        bool isEmpty() const {
            return size_ == 0;
        }

        bool isFull() const {
            return size_ == capacity_;
        }

        std::size_t size() const {
            return size_;
        }

        std::size_t capacity() const {
            return capacity_;
        }
};