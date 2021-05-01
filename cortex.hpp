/**
  ***********************************************************
  @author Evgenii Fedoseev
  @file   cortex.hpp
  @brief  Compatible with cortex-m family
  ***********************************************************
**/

#pragma once


namespace mpp::tim
{
  namespace __private { std::uint32_t GetTick(); void IncTick(); } // namespace __private
  
  
  inline namespace cortex {
    
    template< class ClockSystem >
    class Systick {
      public:
        constexpr static std::uint32_t TickPerSec = 1000u;
        
        inline static void Init() { SysTick_Config(ClockSystem::kSysTickClkHz / 1000u); }
        inline static std::uint32_t GetTick() { return __private::GetTick(); }
        static void Interrupt() { __private::IncTick(); }         
    };
    
    
#if ((__CORTEX_M == 3u)||(__CORTEX_M == 4u)||(__CORTEX_M == 7u))
    template< class ClockSystem >
    class ClockCounter {
      public:
        constexpr static std::uint32_t TickPerSec = ClockSystem::kSysClkHz;
        
        inline static void Init() { 
          CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
          DWT->CTRL |=  DWT_CTRL_CYCCNTENA_Msk;
        }
        
        inline static std::uint32_t GetTick() { 
          std::uint32_t ctrl = DWT->CTRL;

          DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk;
          std::uint32_t tmp = DWT->CYCCNT; 
          DWT->CTRL = ctrl;

          return tmp;
        }
    };
#endif
        
  } // inline namespace
} // namespace mpp::tim
