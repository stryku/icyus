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

            void newFileChoosed(const std::string &path, void *notifier) override
            {
                senderFilePath = path;

                for (auto observer : modelObservers)
                    if (observer != notifier)
                        observer->senderFilePathChanged(senderFilePath);
            }

            void newReceiverAddress(const std::string &address, void *notifier) override
            {
                receiverAddress = address;

                for (auto observer : modelObservers)
                    if(observer != notifier)
                        observer->newReceiverAddress(receiverAddress);
            }

            void newSenderProgress(size_t progress)
            {
                senderProgress = progress;

                for (auto observer : modelObservers)
                    observer->newSenderProgress(senderProgress);
            }

            void newSenderConnectionStatus(const std::string &status)
            {
                senderConnectionStatus = status;

                for (auto observer : modelObservers)
                    observer->newSenderConnectionStatus(senderConnectionStatus);
            }

            void registerObserver(IModelObserver *observer)
            {
                modelObservers.push_back(observer);
            }

            auto getSenderFilePath() const
            {
                return senderFilePath;
            }

            auto getReceiverAddress() const
            {
                return receiverAddress;
            }

        private:
            size_t senderProgress;
            std::string senderFilePath;
            std::string receiverAddress;
            std::string senderConnectionStatus;
            std::vector<IModelObserver*> modelObservers;
        };
    }
}