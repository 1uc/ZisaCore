#ifndef AL_INTEGRAL_H_AM7Z3
#define AL_INTEGRAL_H_AM7Z3

#include "zisa/config.hpp"
#include "zisa/meta/all_true.hpp"

namespace zisa {

template <class... Ints>
struct all_integral {
  static constexpr bool value
      = all_true<std::is_integral<Ints>::value...>::value;
};

} // namespace zisa
#endif /* end of include guard */
