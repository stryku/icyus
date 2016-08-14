#pragma once

#include <internals/model/IModelObserver.hpp>
#include <internals/input/IInputObserver.hpp>

namespace Icyus
{
    namespace Model
    {
        class Model final : public Icyus::Input::IInputObserver
        {
        public:
            Model() = default;
            ~Model() = default;
            Model(Model&) = default;
            Model& operator=(Model&) = default;
            Model(Model&&) = default;
            Model& operator=(Model&&) = default;

            void newFileChoosed(const std::string &path)
            {
                senderFilePath = path;

                for (auto observer : modelObservers)
                    observer->senderFilePathChanged(senderFilePath);
            }

            void registerObserver(IModelObserver *observer)
            {
                modelObservers.push_back(observer);
            }

        private:

            std::string senderFilePath;
            std::vector<IModelObserver*> modelObservers;
        };
    }
}