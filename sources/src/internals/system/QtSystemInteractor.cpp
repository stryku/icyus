#include <internals/system/QtSystemInteractor.hpp>

namespace Icyus
{
    namespace System
    {
        std::string QtSystemInteractor::chooseFile(const std::string &startPath)
        {
            auto path = QFileDialog::getOpenFileName(nullptr, "Choose file", QString::fromStdString(startPath));
            return path.toStdString();
        }
    }
}