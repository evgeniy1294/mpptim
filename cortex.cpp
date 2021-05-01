#include <cstdint>

namespace mpp::tim::__private {
  volatile std::uint32_t systime = 0u;

  std::uint32_t GetTick() { return systime; }
  void IncTick() { systime++; }
}

