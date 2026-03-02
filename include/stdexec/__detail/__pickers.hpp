#pragma once

#include "__execution_fwd.hpp"

namespace STDEXEC
{
  template <class _Picker, class... _As>
  concept __always_pick = requires(_Picker __fn) { requires __fn.template operator()<_As...>(); };

  template <class _Picker, class... _As>
  concept __never_pick = requires(_Picker __fn) { requires !__fn.template operator()<_As...>(); };

  template <class _ResultPicker, class... _Results>
    requires(sizeof...(_Results) > 1)
  constexpr auto __unpick_transform(_ResultPicker&& __result_picker, _Results&&... __results)
  {}

  template <class _Receiver, class _Picker, class... _Results>
  constexpr void __pick_result(_Receiver&& __rcvr, _Picker&& __picker, _Results&&... __results)
  {
    if constexpr (__always_pick<_Picker, _Results...>)
      STDEXEC::set_value(std::forward<_Receiver>(__rcvr), std::forward<_Results>(__results)...);
    else if constexpr (__never_pick<_Picker, _Results...>)
      STDEXEC::__
  }

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