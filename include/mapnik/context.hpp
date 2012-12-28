/*****************************************************************************
 *
 * This file is part of Mapnik (c++ mapping toolkit)
 *
 * Copyright (C) 2012 Artem Pavlenko
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *****************************************************************************/

#ifndef MAPNIK_CONTEXT_HPP
#define MAPNIK_CONTEXT_HPP

// mapnik
#include <mapnik/config.hpp>
#include <mapnik/noncopyable.hpp>

// boost
#include <boost/shared_ptr.hpp>

// stl
#include <vector>
#include <map>
#include <stdexcept>

namespace mapnik {

class feature_impl;

template <typename T>
class context : private mapnik::noncopyable

{
    friend class feature_impl;
public:
    typedef T map_type;
    typedef typename map_type::value_type value_type;
    typedef typename map_type::key_type key_type;
    typedef typename map_type::size_type size_type;
    typedef typename map_type::difference_type difference_type;
    typedef typename map_type::iterator iterator;
    typedef typename map_type::const_iterator const_iterator;

    context()
        : mapping_() {}

    size_type push(key_type const& name)
    {
        size_type index = mapping_.size();
        mapping_.insert(std::make_pair(name, index));
        return index;
    }

    void add(key_type const& name, size_type index)
    {
        mapping_.insert(std::make_pair(name, index));
    }

    size_type size() const { return mapping_.size(); }
    const_iterator begin() const { return mapping_.begin();}
    const_iterator end() const { return mapping_.end();}

private:
    map_type mapping_;
};

typedef MAPNIK_DECL context<std::map<std::string,std::size_t> > context_type;
typedef MAPNIK_DECL boost::shared_ptr<context_type> context_ptr;

}

#endif // MAPNIK_CONTEXT_HPP
