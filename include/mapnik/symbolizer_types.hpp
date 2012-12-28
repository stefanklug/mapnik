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

#ifndef MAPNIK_SYMBOLIZER_TYPES_HPP
#define MAPNIK_SYMBOLIZER_TYPES_HPP

// boost
#include <boost/variant.hpp>

// stl
#include <string>
#include <vector>

namespace mapnik { struct text_symbolizer; }
namespace mapnik { struct shield_symbolizer; }
namespace mapnik { struct point_symbolizer; }
namespace mapnik { struct markers_symbolizer; }
namespace mapnik { struct line_symbolizer; }
namespace mapnik { struct polygon_pattern_symbolizer; }
namespace mapnik { struct line_pattern_symbolizer; }
namespace mapnik { struct building_symbolizer; }
namespace mapnik { struct debug_symbolizer; }
namespace mapnik { struct polygon_symbolizer; }
namespace mapnik { struct raster_symbolizer; }

namespace mapnik
{

typedef boost::variant<point_symbolizer,
                       line_symbolizer,
                       line_pattern_symbolizer,
                       polygon_symbolizer,
                       polygon_pattern_symbolizer,
                       raster_symbolizer,
                       shield_symbolizer,
                       text_symbolizer,
                       building_symbolizer,
                       markers_symbolizer,
                       debug_symbolizer> symbolizer;

typedef std::vector<symbolizer> symbolizers;

}

#endif // MAPNIK_SYMBOLIZER_TYPES_HPP
