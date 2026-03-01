#pragma once

#include <tuple>

namespace STDEXEC
{
  template <class _Ty, class _Completions>
  concept completion_transformer_of = true;  // TODO

  struct default_completion_transformer
  {
    template <class... _As>
    constexpr bool result_is_error(_As const &...) const noexcept
    {
      return false;
    }

    template <class... _As>
    constexpr auto get_error(_As &&...__as) const noexcept -> std::tuple<_As...>
    {
      return {std::forward<_As>(__as)...};
    }

    template <class E>
    constexpr bool error_is_exception(E const &) const noexcept
    {
      return true;
    }
  };
}  // namespace STDEXEC