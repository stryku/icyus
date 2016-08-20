#pragma once

#include <internals/communication/details/TransferHeader.hpp>
#include <internals/communication/details/FormatTraits.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <sstream>

namespace Icyus
{
    namespace Communication
    {
        namespace detail
        {
            namespace TransferHeader
            {
                template <typename Format>
                class Parser
                {
                public:
                    template <typename It, typename = std::enable_if_t<isXmlFormat<Format>>>
                    static Header parse(It begin, It end)
                    {
                        std::istringstream iss({ begin, end });
                        boost::property_tree::ptree tree;
                        boost::property_tree::xml_parser::read_xml(iss, tree);

                        return Header(tree.get<Header::FileNameType>("header.filename"),
                                      tree.get<Header::FileSizeType>("header.filesize"));
                    }
                };
            }
        }
    }
}