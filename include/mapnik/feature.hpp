/*****************************************************************************
 *
 * This file is part of Mapnik (c++ mapping toolkit)
 *
 * Copyright (C) 2011 Artem Pavlenko
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

#ifndef MAPNIK_FEATURE_HPP
#define MAPNIK_FEATURE_HPP

// mapnik
#include <mapnik/config.hpp>
#include <mapnik/box2d.hpp>
#include <mapnik/value_types.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <mapnik/geometry.hpp>
#include <mapnik/noncopyable.hpp>
#include <mapnik/context.hpp>

// boost
#include <boost/shared_ptr.hpp>

// stl
#include <vector>
#include <map>
#include <stdexcept>

namespace mapnik {

namespace value_adl_barrier { class value; }
using value_adl_barrier::value;
class raster;
typedef boost::shared_ptr<raster> raster_ptr;
class feature_kv_iterator;

class MAPNIK_DECL feature_impl : private mapnik::noncopyable
{
    friend class feature_kv_iterator;
public:

    typedef mapnik::value value_type;
    typedef std::vector<value_type> cont_type;
    typedef cont_type::size_type size_type;
    typedef feature_kv_iterator iterator;

    feature_impl(context_ptr const& ctx, mapnik::value_integer id);

    template <typename T>
    void put(context_type::key_type const& key, T const& val);

    template <typename T>
    void put_new(context_type::key_type const& key, T const& val);

    mapnik::value_integer id() const;
    void set_id(mapnik::value_integer id);
    void put(context_type::key_type const& key, value const& val);
    void put_new(context_type::key_type const& key, value const& val);
    bool has_key(context_type::key_type const& key) const;
    value_type const& get(context_type::key_type const& key) const;
    value_type const& get(std::size_t index) const;
    std::size_t size() const;
    cont_type const& get_data() const;
    void set_data(cont_type const& data);
    context_ptr context();
    boost::ptr_vector<geometry_type> const& paths() const;
    boost::ptr_vector<geometry_type> & paths();
    void add_geometry(geometry_type * geom);
    size_type num_geometries() const;
    geometry_type const& get_geometry(unsigned index) const;
    geometry_type& get_geometry(unsigned index);
    box2d<double> envelope() const;
    raster_ptr const& get_raster() const;
    void set_raster(raster_ptr const& raster);
    feature_kv_iterator begin() const;
    feature_kv_iterator end() const;
    std::string to_string() const;

private:
    mapnik::value_integer id_;
    context_ptr ctx_;
    cont_type data_;
    boost::ptr_vector<geometry_type> geom_cont_;
    raster_ptr raster_;
};

inline std::ostream& operator<< (std::ostream & out,feature_impl const& f)
{
    out << f.to_string();
    return out;
}

typedef MAPNIK_DECL boost::shared_ptr<feature_impl> feature_ptr;

typedef feature_impl Feature;

}

#endif // MAPNIK_FEATURE_HPP
