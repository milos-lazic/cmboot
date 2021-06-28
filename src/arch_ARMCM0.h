#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

//-----------------------------------------------------------------------------
/// @brief Enable interrupts.
///
/// @details Enables interrupts to the processor by clearing PRIMASK.
///
//
extern void arch_enableInterrupts(void);

//-----------------------------------------------------------------------------
/// @brief Disable interrupts.
///
/// @details Disables interrupts to the processor by setting PRIMASK.
//
extern void arch_disableInterrupts(void);

//-----------------------------------------------------------------------------
/// @brief Read the exception number of the current ISR.
///
/// @details Reads the valud of the IPSR.
///
/// @return Exception number of the current ISR (0-47).
//
extern uint32_t arch_getIPSR(void);

#ifdef __cplusplus
}
#endif // __cplusplus