#pragma once

#include <internals/model/IModelObserver.hpp>
#include <internals/input/IInputHandler.hpp>

namespace Icyus
{
    namespace Model
    {
        class Model final : public Icyus::Input::IInputHandler
        {
        public:
            Model() = default;
            ~Model() = default;
            Model(Model&) = default;
            Model& operator=(Model&) = default;
            Model(Model&&) = default;
            Model& operator=(Model&&) = default;

            void registerObserver(IModelObserver *observer)
            {
                modelObservers.push_back(observer);
            }

        private:
            std::vector<IModelObserver*> modelObservers;
        };
    }
}