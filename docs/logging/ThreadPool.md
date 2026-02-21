File: logging/inc/ThreadPool.hpp

Purpose
- Simple fixed-size worker thread pool for dispatching background tasks.

Public API / behavior
- ThreadPool(std::size_t numThreads)
- ~ThreadPool()
- bool submit(std::function<void()> func)

Key behavior
- Uses a `std::queue<std::function<void()>>` for tasks and worker threads that pop tasks and execute them.
- `submit` returns false if the pool is stopped.
- Destructor signals stop and joins workers.

Notes / next steps
- The current implementation does not support priority submission (submit_front) or resizing.
- If you want GPU events to preempt other tasks without a separate gpuPool, consider replacing `std::queue` with `std::deque` and adding `submit_front`.

Related files
- app/src/DataLogger.cpp (uses two ThreadPool instances currently)
