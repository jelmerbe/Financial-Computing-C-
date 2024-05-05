/* Policies for result and outcome
(C) 2017-2023 Niall Douglas <http://www.nedproductions.biz/> (6 commits) and Andrzej Krzemieński <akrzemi1@gmail.com> (1 commit)
File Created: Oct 2017


Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#ifndef BOOST_OUTCOME_POLICY_BASE_HPP
#define BOOST_OUTCOME_POLICY_BASE_HPP

#include "../detail/value_storage.hpp"

BOOST_OUTCOME_V2_NAMESPACE_EXPORT_BEGIN

#if BOOST_OUTCOME_ENABLE_LEGACY_SUPPORT_FOR < 220
/*! AWAITING HUGO JSON CONVERSION TOOL
SIGNATURE NOT RECOGNISED
*/
namespace hooks
{
  /*! AWAITING HUGO JSON CONVERSION TOOL
SIGNATURE NOT RECOGNISED
*/
  template <class T, class U> constexpr inline void hook_result_construction(T * /*unused*/, U && /*unused*/) noexcept {}
  /*! AWAITING HUGO JSON CONVERSION TOOL
SIGNATURE NOT RECOGNISED
*/
  template <class T, class U> constexpr inline void hook_result_copy_construction(T * /*unused*/, U && /*unused*/) noexcept {}
  /*! AWAITING HUGO JSON CONVERSION TOOL
SIGNATURE NOT RECOGNISED
*/
  template <class T, class U> constexpr inline void hook_result_move_construction(T * /*unused*/, U && /*unused*/) noexcept {}
  /*! AWAITING HUGO JSON CONVERSION TOOL
SIGNATURE NOT RECOGNISED
*/
  template <class T, class U, class... Args>
  constexpr inline void hook_result_in_place_construction(T * /*unused*/, in_place_type_t<U> /*unused*/, Args &&... /*unused*/) noexcept
  {
  }
  /*! AWAITING HUGO JSON CONVERSION TOOL
SIGNATURE NOT RECOGNISED
*/
  template <class T, class... U> constexpr inline void hook_outcome_construction(T * /*unused*/, U &&... /*unused*/) noexcept {}
  /*! AWAITING HUGO JSON CONVERSION TOOL
SIGNATURE NOT RECOGNISED
*/
  template <class T, class U> constexpr inline void hook_outcome_copy_construction(T * /*unused*/, U && /*unused*/) noexcept {}
  /*! AWAITING HUGO JSON CONVERSION TOOL
SIGNATURE NOT RECOGNISED
*/
  template <class T, class U> constexpr inline void hook_outcome_move_construction(T * /*unused*/, U && /*unused*/) noexcept {}
  /*! AWAITING HUGO JSON CONVERSION TOOL
SIGNATURE NOT RECOGNISED
*/
  template <class T, class U, class... Args>
  constexpr inline void hook_outcome_in_place_construction(T * /*unused*/, in_place_type_t<U> /*unused*/, Args &&... /*unused*/) noexcept
  {
  }
}  // namespace hooks
#endif

namespace policy
{
  namespace detail
  {
    using BOOST_OUTCOME_V2_NAMESPACE::detail::make_ub;
  }
  /*! AWAITING HUGO JSON CONVERSION TOOL
SIGNATURE NOT RECOGNISED
*/
  struct base
  {
    template <class... Args> static constexpr void _silence_unused(Args &&... /*unused*/) noexcept {}
  protected:
    template <class Impl> static constexpr void _make_ub(Impl &&self) noexcept { return detail::make_ub(static_cast<Impl &&>(self)); }
    template <class Impl> static constexpr bool _has_value(Impl &&self) noexcept { return self._state._status.have_value(); }
    template <class Impl> static constexpr bool _has_error(Impl &&self) noexcept { return self._state._status.have_error(); }
    template <class Impl> static constexpr bool _has_exception(Impl &&self) noexcept { return self._state._status.have_exception(); }
    template <class Impl> static constexpr bool _has_error_is_errno(Impl &&self) noexcept { return self._state._status.have_error_is_errno(); }

    template <class Impl> static constexpr void _set_has_value(Impl &&self, bool v) noexcept { self._state._status.set_have_value(v); }
    template <class Impl> static constexpr void _set_has_error(Impl &&self, bool v) noexcept { self._state._status.set_have_error(v); }
    template <class Impl> static constexpr void _set_has_exception(Impl &&self, bool v) noexcept { self._state._status.set_have_exception(v); }
    template <class Impl> static constexpr void _set_has_error_is_errno(Impl &&self, bool v) noexcept { self._state._status.set_have_error_is_errno(v); }

    template <class Impl> static constexpr auto &&_value(Impl &&self) noexcept { return static_cast<Impl &&>(self)._state._value; }
    template <class Impl> static constexpr auto &&_error(Impl &&self) noexcept { return static_cast<Impl &&>(self)._state._error; }

  public:
    template <class R, class S, class P, class NoValuePolicy, class Impl> static inline constexpr auto &&_exception(Impl &&self) noexcept;

    template <class T, class U> static constexpr inline void on_result_construction(T *inst, U &&v) noexcept
    {
#if BOOST_OUTCOME_ENABLE_LEGACY_SUPPORT_FOR < 220
      using namespace hooks;
      hook_result_construction(inst, static_cast<U &&>(v));
#else
      (void) inst;
      (void) v;
#endif
    }
    template <class T, class U> static constexpr inline void on_result_copy_construction(T *inst, U &&v) noexcept
    {
#if BOOST_OUTCOME_ENABLE_LEGACY_SUPPORT_FOR < 220
      using namespace hooks;
      hook_result_copy_construction(inst, static_cast<U &&>(v));
#else
      (void) inst;
      (void) v;
#endif
    }
    template <class T, class U> static constexpr inline void on_result_move_construction(T *inst, U &&v) noexcept
    {
#if BOOST_OUTCOME_ENABLE_LEGACY_SUPPORT_FOR < 220
      using namespace hooks;
      hook_result_move_construction(inst, static_cast<U &&>(v));
#else
      (void) inst;
      (void) v;
#endif
    }
    template <class T, class U, class... Args>
    static constexpr inline void on_result_in_place_construction(T *inst, in_place_type_t<U> _, Args &&... args) noexcept
    {
#if BOOST_OUTCOME_ENABLE_LEGACY_SUPPORT_FOR < 220
      using namespace hooks;
      hook_result_in_place_construction(inst, _, static_cast<Args &&>(args)...);
#else
      (void) inst;
      (void) _;
      _silence_unused(static_cast<Args &&>(args)...);
#endif
    }

    template <class T, class... U> static constexpr inline void on_outcome_construction(T *inst, U &&... args) noexcept
    {
#if BOOST_OUTCOME_ENABLE_LEGACY_SUPPORT_FOR < 220
      using namespace hooks;
      hook_outcome_construction(inst, static_cast<U &&>(args)...);
#else
      (void) inst;
      _silence_unused(static_cast<U &&>(args)...);
#endif
    }
    template <class T, class U> static constexpr inline void on_outcome_copy_construction(T *inst, U &&v) noexcept
    {
#if BOOST_OUTCOME_ENABLE_LEGACY_SUPPORT_FOR < 220
      using namespace hooks;
      hook_outcome_copy_construction(inst, static_cast<U &&>(v));
#else
      (void) inst;
      (void) v;
#endif
    }
    template <class T, class U> static constexpr inline void on_outcome_move_construction(T *inst, U &&v) noexcept
    {
#if BOOST_OUTCOME_ENABLE_LEGACY_SUPPORT_FOR < 220
      using namespace hooks;
      hook_outcome_move_construction(inst, static_cast<U &&>(v));
#else
      (void) inst;
      (void) v;
#endif
    }
    template <class T, class U, class... Args>
    static constexpr inline void on_outcome_in_place_construction(T *inst, in_place_type_t<U> _, Args &&... args) noexcept
    {
#if BOOST_OUTCOME_ENABLE_LEGACY_SUPPORT_FOR < 220
      using namespace hooks;
      hook_outcome_in_place_construction(inst, _, static_cast<Args &&>(args)...);
#else
      (void) inst;
      (void) _;
      _silence_unused(static_cast<Args &&>(args)...);
#endif
    }

    template <class Impl> static constexpr void narrow_value_check(Impl &&self) noexcept
    {
      if(!_has_value(self))
      {
        _make_ub(self);
      }
    }
    template <class Impl> static constexpr void narrow_error_check(Impl &&self) noexcept
    {
      if(!_has_error(self))
      {
        _make_ub(self);
      }
    }
    template <class Impl> static constexpr void narrow_exception_check(Impl &&self) noexcept
    {
      if(!_has_exception(self))
      {
        _make_ub(self);
      }
    }
  };
}  // namespace policy

BOOST_OUTCOME_V2_NAMESPACE_END

#endif
