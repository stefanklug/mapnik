/*****************************************************************************
 *
 * This file is part of Mapnik (c++ mapping toolkit)
 *
 * Copyright (C) 2010 Artem Pavlenko
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

#include <mapnik/map.hpp>
#include <mapnik/load_map.hpp>
#include <mapnik/svg/output/svg_renderer.hpp>
#include <mapnik/datasource_cache.hpp>
#include <mapnik/font_engine_freetype.hpp>
#include <mapnik/expression.hpp>
#include <mapnik/color_factory.hpp>
#include <mapnik/version.hpp>

// boost
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/program_options.hpp>

// stl
#include <fstream>
#include <iterator>
#include <iostream>
#include <sstream>

int main (int argc,char** argv)
{
    namespace po = boost::program_options;

    bool verbose = false;
    int return_value = 0;
    std::string xml;
    mapnik::logger logger;
    logger.set_severity(mapnik::logger::error);

    try
    {
        po::options_description desc("map2svg utility");
        desc.add_options()
            ("help,h", "produce usage message")
            ("version,V","print version string")
            ("verbose,v","verbose output")
            ("xml",po::value<std::string>(),"xml file to read")
            ;

        po::positional_options_description p;
        p.add("xml",-1);
        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
        po::notify(vm);

        if (vm.count("version"))
        {
            std::clog <<"version " << MAPNIK_VERSION_STRING << std::endl;
            return 1;
        }

        if (vm.count("help"))
        {
            std::clog << desc << std::endl;
            return 1;
        }

        if (vm.count("verbose"))
        {
            verbose = true;
        }

        if (vm.count("xml"))
        {
            xml=vm["xml"].as<std::string>();
        }
        else
        {
            std::clog << "please provide an xml file!" << std::endl;
            return -1;
        }

        std::string mapnik_dir("/usr/local/lib/mapnik/");
        mapnik::datasource_cache::instance().register_datasources(mapnik_dir + "input/");
        mapnik::freetype_engine::register_fonts(mapnik_dir + "/fonts/");
        mapnik::Map m(256,256);
        mapnik::load_map(m,xml);
        m.zoom_all();
        std::ostringstream svg_stream;
        //std::ofstream svg_stream(output_filename.c_str());
        typedef mapnik::svg_renderer<std::ostream_iterator<char> > svg_ren;
        std::ostream_iterator<char> output_stream_iterator(svg_stream);
        svg_ren renderer(m, output_stream_iterator);
        renderer.apply();
        std::cout << svg_stream.str() << "\n";
        //svg_stream.close();
        //fs::path output_filename_path =
        //    fs::system_complete(fs::path(".")) / fs::path(output_filename);
    }
    catch (std::exception const& ex)
    {
        std::clog << "Error:" << ex.what() << std::endl;
        return -1;
    }
    catch (...)
    {
        std::clog << "Exception of unknown type!" << std::endl;
        return -1;
    }
    return return_value;
}
