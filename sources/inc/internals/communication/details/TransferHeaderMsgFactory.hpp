#pragma once

#include <internals/communication/details/TransferHeader.hpp>

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
            struct XmlType {};

            template <typename Msg, typename TransferHeaderFormat>
            class TransferHeaderMsgFactory
            {
            public:
                template <typename = std::enable_if_t<std::is_same<TransferHeaderFormat, XmlType>::value>>
                static Msg create(TransferHeaderFormat type, const TransferHeader &header)
                {
                    std::ostringstream oss;

                    auto tree = createTree(header);

                    boost::property_tree::write_xml(oss, tree);

                    const auto str = oss.str();

                    return { str.cbegin(), str.cend() };
                }

            private:
                auto createTree(const TransferHeader &header) const
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