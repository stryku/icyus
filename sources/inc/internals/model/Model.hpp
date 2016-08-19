#pragma once

#include <internals/model/IModelObserver.hpp>
#include <internals/input/IInputObserver.hpp>

#include <vector>

namespace Icyus
{
    namespace Model
    {
        class Model final : public Icyus::Input::IInputObserver
        {
        public:
            Model() = default;
            ~Model() = default;
            Model(Model&&) = default;
            Model& operator=(Model&&) = default;

            Model(Model&) = delete;
            Model& operator=(Model&) = delete;

            void newFileChoosed(const std::string &path) override;
            void newReceiverAddress(const std::string &address) override;
            void newSenderProgress(size_t progress);
            void newReceiverProgress(size_t progress);
            void newSenderConnectionStatus(const std::string &status);
            void newReceiverListeningStatus(const std::string &status);

            void registerObserver(IModelObserver *observer);

            std::string getSenderFilePath() const;
            std::string getReceiverAddress() const;

        private:
            size_t receiverProgress;
            size_t senderProgress;
            std::string senderFilePath;
            std::string receiverAddress;
            std::string senderConnectionStatus;
            std::string receiverListeningStatus;
            std::vector<IModelObserver*> modelObservers;
        };
    }
}