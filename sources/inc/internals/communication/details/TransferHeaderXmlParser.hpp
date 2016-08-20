#pragma once

#include <internals/communication/details/TransferHeader.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <sstream>

namespace Icyus
{
    namespace Communication
    {
        namespace detail
        {
            class TransferHeaderXmlParser
            {
            public:
                template <typename It>
                TransferHeader parse(It begin, It end)
                {
                    std::istringstream iss(begin, end);
                    boost::property_tree::ptree tree;
                    boost::property_tree::xml_parser::read_xml(iss, tree);

                    return { 
                        tree.get<TransferHeader::FileNameType>("header.filename"),
                        tree.get<TransferHeader::FileSizeType>("header.filesize")
                    }
                }
            };
        }
    }
}