#pragma once

#include "__execution_fwd.hpp"

namespace STDEXEC
{
  template <class _Picker, class... _As>
  concept __always_pick = requires(_Picker __fn) { requires __fn.template operator()<_As...>(); };

  template <class _Picker, class... _As>
  concept __never_pick = requires(_Picker __fn) { requires !__fn.template operator()<_As...>(); };

  struct default_result_picker
  {
    template <class... _As>
    static consteval bool operator()() noexcept
    {
      return true;
    }
  };

  struct default_error_picker
  {
    template <class _Error>
    static consteval bool operator()() noexcept
    {
      using _Decayed = std::decay_t<_Error>;
      return !std::same_as<_Decayed, std::exception_ptr>
          && !std::derived_from<_Decayed, std::exception>;
    }
  };
}  // namespace STDEXEC