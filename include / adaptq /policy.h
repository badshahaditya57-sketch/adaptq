// include/adaptq/policy.h
#ifndef ADAPTQ_POLICY_H
#define ADAPTQ_POLICY_H

#include <cstdint>
#include <memory>

namespace adaptq {

/**
 * @brief Minimal Runtime Policy Interface (v0.2.3 Foundation)
 *
 * Defines the quantization and compression policy parameters for the AdapTQ engine.
 *
 * Ownership & Lifetime Rules:
 * - Policy instances are created by the RuntimeFactory.
 * - They should be managed via std::unique_ptr or std::shared_ptr by the main Engine/Context.
 * - The lifetime of a policy must exceed any active attention computations using it.
 *
 * Thread-Safety Expectations:
 * - Implementations MUST be strictly thread-safe and stateless.
 * - Policy getters will be accessed concurrently across multiple threads during inference.
 * - Performance Rule: DO NOT call these virtual methods inside hot SIMD loops. 
 *   Extract policy parameters into local variables before entering the kernel execution.
 */
class IPolicy {
public:
    virtual ~IPolicy() = default;

    /**
     * @brief Retrieves the quantization bit-width.
     * Must be evaluated outside of hot loops.
     */
    virtual uint8_t get_bit_width() const = 0;
    
    // Note: Future query-aware or adaptive policies (v0.2.4+) will expand this interface.
};

/**
 * @brief Default implementation strictly preserving v0.2.2 baseline behavior.
 */
class DefaultPolicy : public IPolicy {
public:
    DefaultPolicy() = default;
    ~DefaultPolicy() override = default;

    /**
     * @brief Preserves the baseline fixed-bit behavior.
     * @return uint8_t The default quantization bit-width (e.g., 8-bit).
     */
    uint8_t get_bit_width() const override {
        return 8; // Preserving 0.2.2 fixed-bit baseline
    }
};

} // namespace adaptq

#endif // ADAPTQ_POLICY_H
