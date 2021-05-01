/**
  ***********************************************************
  @author Evgenii Fedoseev
  @file   timers.hpp
  @brief  Compatible series: all
  ***********************************************************
**/

#pragma once


namespace mpp::tim {


  template < class Source >
  class Timer
  {
    public:
      void Start(std::uint32_t interval)
      {
        this->timestamp = Source::GetTick(); 
        this->interval  = interval;
        this->active    = true;
      }
      
      void Reload()
      {
        this->timestamp = Source::GetTick();   
      }

      bool IsTimeOut()
      {
        return (((Source::GetTick() - this->timestamp) > this->interval) && this->active);
      };

      void Delay(std::uint32_t tick)
      {
        std::uint32_t start = Source::GetTick();
        while((Source::GetTick() - start) < tick);
      }
      
    private:
      bool active = false;
      std::uint32_t interval  = 0u;
      std::uint32_t timestamp = 0u;
  };

}  // namespace timers
