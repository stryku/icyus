#pragma once

#include <internals/communication/details/TransferHeader.hpp>
#include <internals/communication/details/FormatTraits.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <type_traits>
#include <sstream>

namespace Icyus
{
    namespace Communication
    {
        namespace detail
        {
            namespace TransferHeader
            {
                template <typename Msg, typename Format>
                class MsgFactory
                {
                public:
                    template <typename = std::enable_if_t<isXmlFormat<Format>>
                    static Msg create(const Header &header)
                    {
                        std::ostringstream oss;

                        auto tree = createTree(header);

                        boost::property_tree::write_xml(oss, tree);

                        const auto str = oss.str();

                        return{ str.cbegin(), str.cend() };
                    }

                private:
                    auto createTree(const Header &header) const
                    {
                        boost::property_tree::ptree tree;

                        tree.put("header.filename", header.fileName);
                        tree.put("header.filesize", header.fileSize);

                        return tree;
                    }
                };
            }
        }
    }
}