#pragma once

#include <internals/system/ISystemInteractor.hpp>

#include <QFileDialog>

namespace Icyus
{
    namespace System
    {
        class QtSystemInteractor final : public Icyus::System::ISystemInteractor
        {
        public:
            std::string chooseFile(const std::string &startPath = {}) override
            {
                auto path = QFileDialog::getOpenFileName(nullptr, "Choose file", QString::fromStdString(startPath));
                return path.toStdString();
            }

        };
    }
}