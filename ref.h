
template <typename T>
struct remove_reference
{
	typedef T type;
};

template <typename T>
struct remove_reference<T&>
{
	typedef T type;
};

template <typename T>
struct remove_reference<T&&>
{
	typedef T type;
};

template <typename T>
[[nodiscard]] inline constexpr typename remove_reference<T>::type&& move(T&& t) noexcept
{
	return static_cast<typename remove_reference<T>::type&&>(t);
}

template <typename T>
[[nodiscard]] inline constexpr T&& forward(typename remove_reference<T>::type& t) noexcept
{
	return static_cast<T&&>(t);
}

template <typename _Fn>
class ScopeGuard
{
public:
	ScopeGuard(_Fn func) :
		_m_fun(func), _m_is_active(true)
	{
	}

	// disable copy ctor
	ScopeGuard(const ScopeGuard&)            = delete;
	ScopeGuard& operator=(const ScopeGuard&) = delete;
	// only allowed move ctor
	ScopeGuard(ScopeGuard&& rhs)
	{
		_m_fun           = rhs._m_fun;
		rhs._m_is_active = false;
	}
	ScopeGuard& operator=(ScopeGuard&& rhs)
	{
		_m_fun           = move(rhs._m_fun);
		rhs._m_is_active = false;
	}

	// dtor
	~ScopeGuard()
	{
		if (_m_is_active)
		{
			_m_fun();
		}
	}

private:
	bool _m_is_active;
	_Fn  _m_fun;
};

template <typename _Fn>
auto MakeScopeGuard(_Fn&& f) -> ScopeGuard<_Fn>
{
	return ScopeGuard(forward<_Fn>(f));
}


#define S_CONCATENATE_IMPL(s1, s2) s1##s2
#define S_CONCATENATE(s1, s2)      S_CONCATENATE_IMPL(s1, s2)
#define S_ANONYMOUS_VARIABLE(str)  S_CONCATENATE(str, __LINE__)
#define SCOPE_EXIT auto S_ANONYMOUS_VARIABLE(SCOPE_EXIT_STATE) = ::KernelEx::MakeScopeGuard([&]()
#define SCOPE_EXIT_END )