/* Get the type of objects, thanks to [1].
 *
 * Requires C++11.
 *
 * [1]: http://stackoverflow.com/a/20170989/5103043
 *
 * Authors: Luc Grosheintz <forbugrep@zoho.com>
 *    Date: 2015-08-21
 */
#ifndef TYPEOF_H_FTOYTX9N
#define TYPEOF_H_FTOYTX9N

#include <type_traits>
#include <typeinfo>

// The Stackoverflow version does not demangle for MSC. You can
// detect MSC by the macro _MSC_VER.
#ifdef _MSC_VER
#define ZISA_DONT_DEMANGLE
#endif

#ifndef ZISA_DONT_DEMANGLE
#include <cxxabi.h>
#endif

#include <cstdlib>
#include <memory>
#include <string>

template <class T>
std::string type_name(bool with_decoration = true) {
  using TR = typename std::remove_reference<T>::type;

  std::unique_ptr<char, void (*)(void *)> demangled(
#ifndef ZISA_DONT_DEMANGLE
      abi::__cxa_demangle(typeid(TR).name(), nullptr, nullptr, nullptr),
#else
      nullptr,
#endif
      std::free);

  std::string r = (demangled != nullptr ? demangled.get() : typeid(TR).name());

  if (with_decoration) {
    if (std::is_const<TR>::value)
      r += " const";
    if (std::is_volatile<TR>::value)
      r += " volatile";
    if (std::is_lvalue_reference<T>::value)
      r += "&";
    else if (std::is_rvalue_reference<T>::value)
      r += "&&";
  }

  return r;
}

#endif /* end of include guard: TYPEOF_H_FTOYTX9N */
