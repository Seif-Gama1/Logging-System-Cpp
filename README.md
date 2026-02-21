# Logging-System-Cpp

A compact, pragmatic C++ logging & telemetry demo that integrates file/socket/SOME-IP telemetry sources, policy-based formatting, thread-pool dispatch, and multiple sinks (console + file).

This repository is a working demo that wires a few pieces together to explore real-time telemetry pipelines and SOME/IP (CommonAPI) event delivery. It is tuned for local development and experiments rather than being a production-ready framework.

## Highlights (this project)

- Policy-based formatters for telemetry (CPU / GPU / RAM).
- ThreadPool-based asynchronous dispatch to sinks (console + file).
- RingBuffer-backed, bounded in-memory buffer in `LogManager` with safe fallback to avoid silent drops.
- SOME/IP client glue: a CommonAPI proxy subscriber that receives GPU broadcast events and invokes a user callback.
- Simple RAII wrappers for POSIX file/socket: `SafeFile` and `SafeSocket`.

Compared to the reference README you shared, this project intentionally keeps the design small and easy to iterate on. See the `docs/` folder for generated per-file documentation.

## Quick status / known differences

- C++ standard: the codebase currently targets C++17 (check your compiler flags in CMake). If you want C++23 features, please update CMake and toolchain.
- ThreadPool: a simple fixed-size worker pool is implemented. It does not yet support prioritized submission (`submit_front`) — there is a TODO to add this so GPU events can preempt backlog tasks without using a separate pool.
- LogManager: the ring buffer is non-blocking (tryPush). To avoid silent message loss, `LogManager::log()` now synchronously routes the message to sinks when the buffer is full.
- FileTelemetrySrc: currently returns `false` on EOF. There is a documented follow/tail enhancement you can enable if you want `tail -f` behaviour.
- SOME/IP: CommonAPI-generated sources are included and linked so proxy/stub static registration happens correctly. The client uses async RPC and broadcast subscription to avoid blocking the CommonAPI dispatch threads.

## Project structure

```
Logging-System-Cpp/
├── CMakeLists.txt                # Root CMake
├── README.md                     # <- this file
├── docs/                         # Per-file docs generated for logging/app
├── src-gen/                      # Generated CommonAPI headers & sources
├── logging/                      # Logging library (headers + src)
│   ├── inc/                      # Public headers
│   └── src/                      # Implementation
├── app/                          # Small demo app and facade (DataLogger)
└── build/                        # Out-of-tree build artifacts (gitignored)
```

Main components (brief)

- `logging/inc` + `logging/src`
  - `LogManager` — central router and bounded buffer
  - `LogFormatter<Policy>` — template formatter for Cpu/Gpu/Ram policies
  - `ILogSink` + Console/File sink implementations
  - `ThreadPool`, `RingBuffer`, `SafeFile`, `SafeSocket`
  - `SomeIPTelemetrySrcImpl` — CommonAPI client wrapper (singleton)

- `app/src`
  - `DataLogger` — small facade wiring the LogManager, sinks, telemetry sources and worker pools
  - `main.cpp` — constructs `DataLogger` with `AppConfig` and runs `start()`
  - `someipmain.cpp` — small helper/demo that can run a server side telemetry updater (uses `GpuTelemetryServer`)

## Dependencies

- CMake (3.10+ recommended)
- A modern C++ compiler (GCC or Clang) supporting C++17
- libCommonAPI-SomeIP / CommonAPI (for SOME/IP client/server)
- vsomeip3 (runtime for SOME/IP)
- magic_enum (optional, used by formatters; includes are present in repo under third_party)

On Debian/Ubuntu you can typically install CommonAPI/vsomeip with your distribution packages or build from sources. For development, ensure the headers and shared libraries are discoverable (this repo's CMake expects system-installed CommonAPI/vsomeip under /usr/local or system paths).

## Build (quick)

```bash
mkdir -p build && cd build
cmake .. -G "Unix Makefiles"
cmake --build . -j$(nproc)
```

This builds:

- `app` — main demo application (located at `build/app/app`)
- `logging` — static library used by the app
- `gpu_generated` — generated CommonAPI sources compiled into a static lib

## Run

- Run the app (client + logging facade):

```bash
./build/app/app
```

- Run the local GPU telemetry server (optional — useful for testing broadcasts):

```bash
./build/logging/GpuTelemetryServer  # NOTE: the server build may be part of the logging binary depending on CMake
```

In the project the server code lives in `logging/src/GPUTelemetryServer.cpp` and registers a CommonAPI service that fires frequent simulated GPU-load broadcasts.

## How to use the demo (code)

The app uses the `DataLogger` facade. A minimal example is `app/src/main.cpp`:

```cpp
#include "DataLogger.hpp"

int main(){
    AppConfig cfg;
    cfg.enableCpu = true;
    cfg.enableRam = true;
    cfg.enableGpu = true;
    cfg.enableConsoleSink = true;
    cfg.enableFileSink = true;
    cfg.parseRateMs = 1;
    cfg.logDelayMs = 0;
    cfg.numWorkers = 3;
    cfg.gpuWorkers = 2; // currently DataLogger uses a dedicated gpuPool; see TODOs

    DataLogger app(cfg, "data.txt");
    app.start();
}
```

`DataLogger::start()` reads telemetry from `data.txt` (FileTelemetrySrc) and submits formatting + logging tasks to the worker pool. SOME/IP GPU events are delivered via `SomeIPTelemetrySourceImpl` and submitted to `gpuPool` as they arrive.

## Documentation

Auto-generated per-file docs live under `docs/logging/` and `docs/app/` (these were generated by a helper script). They summarize public APIs and implementation notes.

## Testing / Debugging tips

- If CommonAPI `buildProxy()` returns `nullptr`, ensure generated `src-gen` sources are compiled into the final binary (CMake in this repo already adds them to the `app` target). Linker-time missing static initializers are a common cause.
- To observe message buffering behavior, adjust the `LogManager` buffer size (constructed in `DataLogger` as `LogManager logger(150)` by default) and toggle `cfg.logDelayMs` to simulate slower sink writes.
- If you want `tail -f` behavior for file telemetry, consider modifying `FileTelemetrySrc::readSource` to sleep-and-retry on EOF (follow mode) instead of returning `false`.

## License

This project uses the MIT license.