// include/adaptq/storage_backend.h
#ifndef ADAPTQ_STORAGE_BACKEND_H
#define ADAPTQ_STORAGE_BACKEND_H

#include <cstddef>
#include <cstdint>
#include <vector>

namespace adaptq {

/**
 * @brief Minimal Storage Backend Interface (v0.2.3 Foundation)
 *
 * Defines the memory management and layout abstraction for the KV cache.
 *
 * Allocation/Deallocation Semantics:
 * - Implementations are responsible for managing the lifecycle of the underlying memory.
 * - Memory must remain valid for the lifetime of the backend instance.
 *
 * Capacity Behavior:
 * - Backends must track their maximum capacity and current size to prevent overflows.
 */
class IStorageBackend {
public:
    virtual ~IStorageBackend() = default;

    /**
     * @brief Retrieves a pointer to the underlying continuous memory if supported.
     * @return uint8_t* Pointer to the data, or nullptr if not contiguous.
     */
    virtual uint8_t* get_data_ptr() = 0;
    virtual const uint8_t* get_data_ptr() const = 0;

    /**
     * @brief Gets the maximum capacity in bytes.
     */
    virtual size_t get_capacity() const = 0;

    /**
     * @brief Gets the currently used size in bytes.
     */
    virtual size_t get_size() const = 0;
};

/**
 * @brief Contiguous Storage implementation preserving v0.2.2 memory layout.
 * 
 * Future implementations (v0.2.4+) will introduce Paged, MMAP, and NUMA storage.
 */
class ContiguousStorageBackend : public IStorageBackend {
private:
    std::vector<uint8_t> buffer_;
    size_t capacity_;
    size_t current_size_;

public:
    explicit ContiguousStorageBackend(size_t capacity_bytes) 
        : capacity_(capacity_bytes), current_size_(0) {
        buffer_.reserve(capacity_bytes);
    }

    ~ContiguousStorageBackend() override = default;

    uint8_t* get_data_ptr() override {
        return buffer_.data();
    }

    const uint8_t* get_data_ptr() const override {
        return buffer_.data();
    }

    size_t get_capacity() const override {
        return capacity_;
    }

    size_t get_size() const override {
        return current_size_;
    }
};

} // namespace adaptq

#endif // ADAPTQ_STORAGE_BACKEND_H
