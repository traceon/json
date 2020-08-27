//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/json
//

#ifndef BOOST_JSON_IMPL_STATIC_RESOURCE_IPP
#define BOOST_JSON_IMPL_STATIC_RESOURCE_IPP

#include <boost/json/static_resource.hpp>

namespace boost {
namespace json {

static_resource::
~static_resource() noexcept
{
}

static_resource::
static_resource(
    void* buffer,
    std::size_t size) noexcept
    : buffer_(reinterpret_cast<
        char*>(buffer))
    , size_(size)
    , used_(0)
{
}

void*
static_resource::
do_allocate(
    std::size_t n,
    std::size_t align)
{
    (void)align;
    if(n > size_ - used_)
        BOOST_THROW_EXCEPTION(
            std::bad_alloc());
    auto p = buffer_ + used_;
    used_ += n;
    return p;
}

void
static_resource::
do_deallocate(
    void*,
    std::size_t,
    std::size_t)
{
    // do nothing
}

bool
static_resource::
do_is_equal(
    memory_resource const& mr) const noexcept
{
    return this == &mr;
}

} // json
} // boost

#endif
