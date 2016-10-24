#pragma once
template<class tree_t, class iterator_t = typename tree_t::iterator>
struct bind_second
{
	typedef typename iterator_t::iterator_category iterator_category;
	typedef typename tree_t::mapped_type const value_type;
	typedef typename iterator_t::difference_type difference_type;
	typedef value_type &reference;
	typedef value_type *pointer;

	iterator_t it;

	bind_second() = delete;
	bind_second(typename iterator_t const &i) : it(i) {}
	bind_second &operator = (bind_second const &o) = default;

	bool operator == (bind_second const &o) const { return it == o.it; }
	bool operator != (bind_second const &o) const { return it != o.it; }
	bool operator >= (bind_second const &o) const { return it >= o.it; }
	bool operator <= (bind_second const &o) const { return it <= o.it; }
	bool operator > (bind_second const &o) const { return it > o.it; }
	bool operator < (bind_second const &o) const { return it < o.it; }
	bind_second operator + (difference_type d) const { return{ it + d }; }
	bind_second operator - (difference_type d) const { return{ it - d }; }
	bind_second &operator += (difference_type d) { it += d; return *this; }
	bind_second &operator -= (difference_type d) { it -= d; return *this; }
	bind_second &operator ++() { ++it; return *this; }
	bind_second &operator --() { --it; return *this; }
	bind_second operator ++(int) { return{ it++ }; }
	bind_second operator --(int) { return{ it-- }; }
	difference_type operator - (bind_second const &o) const { return it - o.it; }
	reference operator *() { return it->second; }
};
