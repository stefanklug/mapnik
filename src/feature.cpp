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

//mapnik
#include <mapnik/feature_factory.hpp>
#include <mapnik/geometry.hpp>
#include <mapnik/feature_kv_iterator.hpp>
#include <mapnik/feature.hpp>
#include <mapnik/value_types.hpp>
#include <mapnik/value.hpp>

// boost
#include <boost/make_shared.hpp>
//#include <boost/pool/pool_alloc.hpp>

//stl
#include <string>
#include <sstream>

namespace mapnik { 

boost::shared_ptr<feature_impl> feature_factory::create(context_ptr const& ctx, mapnik::value_integer fid)
{
    //return boost::allocate_shared<feature_impl>(boost::pool_allocator<feature_impl>(),fid);
    //return boost::allocate_shared<feature_impl>(boost::fast_pool_allocator<feature_impl>(),fid);
    return boost::make_shared<feature_impl>(ctx,fid);
}

feature_impl::feature_impl(context_ptr const& ctx, mapnik::value_integer id)
    : id_(id),
    ctx_(ctx),
    data_(ctx_->mapping_.size()),
    geom_cont_(),
    raster_()
    {}

template <>
void feature_impl::put(context_type::key_type const& key, value_null const& val)
{
    // TODO - reduce copying
    put(key,value(val));
}

template <>
void feature_impl::put_new(context_type::key_type const& key, value_null const& val)
{
    put_new(key,value(val));
}

template <>
void feature_impl::put(context_type::key_type const& key, value_bool const& val)
{
    put(key,value(val));
}

template <>
void feature_impl::put_new(context_type::key_type const& key, value_bool const& val)
{
    put_new(key,value(val));
}

template <>
void feature_impl::put(context_type::key_type const& key, value_integer const& val)
{
    put(key,value(val));
}

template <>
void feature_impl::put_new(context_type::key_type const& key, value_integer const& val)
{
    put_new(key,value(val));
}

template <>
void feature_impl::put(context_type::key_type const& key, int const& val)
{
    put(key,value(static_cast<value_integer>(val)));
}

template <>
void feature_impl::put_new(context_type::key_type const& key, int const& val)
{
    put_new(key,value(static_cast<value_integer>(val)));
}

template <>
void feature_impl::put(context_type::key_type const& key, unsigned int const& val)
{
    put(key,value(static_cast<value_integer>(val)));
}

template <>
void feature_impl::put_new(context_type::key_type const& key, unsigned int const& val)
{
    put_new(key,value(static_cast<value_integer>(val)));
}

template <>
void feature_impl::put(context_type::key_type const& key, value_double const& val)
{
    put(key,value(val));
}

template <>
void feature_impl::put_new(context_type::key_type const& key, value_double const& val)
{
    put_new(key,value(val));
}

template <>
void feature_impl::put(context_type::key_type const& key, value_unicode_string const& val)
{
    put(key,value(val));
}

template <>
void feature_impl::put_new(context_type::key_type const& key, value_unicode_string const& val)
{
    put_new(key,value(val));
}

mapnik::value_integer feature_impl::id() const
{
    return id_;
}

void feature_impl::set_id(mapnik::value_integer id)
{
    id_ = id;
}

void feature_impl::put(context_type::key_type const& key, value const& val)
{
    context_type::map_type::const_iterator itr = ctx_->mapping_.find(key);
    if (itr != ctx_->mapping_.end()
        && itr->second < data_.size())
    {
        data_[itr->second] = val;
    }
    else
    {
        throw std::out_of_range(std::string("Key does not exist: '") + key + "'");
    }
}

void feature_impl::put_new(context_type::key_type const& key, value const& val)
{
    context_type::map_type::const_iterator itr = ctx_->mapping_.find(key);
    if (itr != ctx_->mapping_.end()
        && itr->second < data_.size())
    {
        data_[itr->second] = val;
    }
    else
    {
        cont_type::size_type index = ctx_->push(key);
        if (index == data_.size())
            data_.push_back(val);
    }
}

bool feature_impl::has_key(context_type::key_type const& key) const
{
    return (ctx_->mapping_.find(key) != ctx_->mapping_.end());
}

feature_impl::value_type const& feature_impl::get(context_type::key_type const& key) const
{
    context_type::map_type::const_iterator itr = ctx_->mapping_.find(key);
    if (itr != ctx_->mapping_.end())
        return get(itr->second);
    else
        return default_value;
}

feature_impl::value_type const& feature_impl::get(std::size_t index) const
{
    if (index < data_.size())
        return data_[index];
    return default_value;
}

std::size_t feature_impl::size() const
{
    return data_.size();
}

feature_impl::cont_type const& feature_impl::get_data() const
{
    return data_;
}

void feature_impl::set_data(cont_type const& data)
{
    data_ = data;
}

context_ptr feature_impl::context()
{
    return ctx_;
}

boost::ptr_vector<geometry_type> const& feature_impl::paths() const
{
    return geom_cont_;
}

boost::ptr_vector<geometry_type> & feature_impl::paths()
{
    return geom_cont_;
}

void feature_impl::add_geometry(geometry_type * geom)
{
    geom_cont_.push_back(geom);
}

feature_impl::size_type feature_impl::num_geometries() const
{
    return geom_cont_.size();
}

geometry_type const& feature_impl::get_geometry(unsigned index) const
{
    return geom_cont_[index];
}

geometry_type& feature_impl::get_geometry(unsigned index)
{
    return geom_cont_[index];
}

box2d<double> feature_impl::envelope() const
{
    // TODO - cache this
    box2d<double> result;
    for (unsigned i=0;i<num_geometries();++i)
    {
        geometry_type const& geom = get_geometry(i);
        if (i==0)
        {
            box2d<double> const& box = geom.envelope();
            result.init(box.minx(),box.miny(),box.maxx(),box.maxy());
        }
        else
        {
            result.expand_to_include(geom.envelope());
        }
    }
    return result;
}

raster_ptr const& feature_impl::get_raster() const
{
    return raster_;
}

void feature_impl::set_raster(raster_ptr const& raster)
{
    raster_ = raster;
}

feature_kv_iterator feature_impl::begin() const
{
    return feature_kv_iterator(*this,true);
}

feature_kv_iterator feature_impl::end() const
{
    return feature_kv_iterator(*this);
}

std::string feature_impl::to_string() const
{
    std::stringstream ss;
    ss << "Feature ( id=" << id_ << std::endl;
    context_type::map_type::const_iterator itr = ctx_->mapping_.begin();
    context_type::map_type::const_iterator end = ctx_->mapping_.end();
    for ( ;itr!=end; ++itr)
    {
        std::size_t index = itr->second;
        if (index < data_.size())
        {
            if (data_[itr->second] == mapnik::value_null())
            {
                ss << "  " << itr->first  << ":null" << std::endl;
            }
            else
            {
                ss << "  " << itr->first  << ":" <<  data_[itr->second] << std::endl;
            }
        }
    }
    ss << ")" << std::endl;
    return ss.str();
}

}
