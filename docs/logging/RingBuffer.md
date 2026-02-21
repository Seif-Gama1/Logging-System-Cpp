File: logging/inc/RingBuffer.hpp

Purpose
- Fixed-capacity circular buffer template used for buffering LogMessage objects.

Public API / template
- template<typename T> class RingBuffer
  - explicit RingBuffer(std::size_t capacity)
  - template<typename C> bool tryPush(C&& value)
  - std::optional<T> tryPop()
  - bool isEmpty() const
  - bool isFull() const
  - std::size_t size() const
  - std::size_t capacity() const

Key behavior
- `tryPush` fails fast (returns false) when buffer is full — it does not overwrite or block.
- `tryPop` returns optional; `std::nullopt` when empty.
- Implementation uses `std::vector<std::optional<T>>` for storage and supports move-only types.

Notes
- This component is deliberately simple and non-thread-safe; callers must synchronize externally.
- The capacity is fixed at construction time.

Related files
- logging/inc/LogManager.hpp (uses RingBuffer<LogMessage>)
