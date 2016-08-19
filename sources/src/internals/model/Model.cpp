#include <internals/model/Model.hpp>

namespace Icyus
{
    namespace Model
    {
        void Model::newFileChoosed(const std::string &path)
        {
            senderFilePath = path;

            for (auto observer : modelObservers)
                observer->senderFilePathChanged(senderFilePath);
        }

        void Model::newReceiverAddress(const std::string &address)
        {
            receiverAddress = address;

            for (auto observer : modelObservers)
                observer->newModelReceiverAddress(receiverAddress);
        }

        void Model::newSenderProgress(size_t progress)
        {
            senderProgress = progress;

            for (auto observer : modelObservers)
                observer->newSenderProgress(senderProgress);
        }

        void Model::newReceiverProgress(size_t progress)
        {
            receiverProgress = progress;

            for (auto observer : modelObservers)
                observer->newReceiverProgress(receiverProgress);
        }

        void Model::newSenderConnectionStatus(const std::string &status)
        {
            senderConnectionStatus = status;

            for (auto observer : modelObservers)
                observer->newSenderConnectionStatus(senderConnectionStatus);
        }


        void Model::newReceiverListeningStatus(const std::string &status)
        {
            receiverListeningStatus = status;

            for (auto observer : modelObservers)
                observer->newReceiverListeningStatus(senderConnectionStatus);
        }

        void Model::registerObserver(IModelObserver *observer)
        {
            modelObservers.push_back(observer);
        }

        std::string Model::getSenderFilePath() const
        {
            return senderFilePath;
        }

        std::string Model::getReceiverAddress() const
        {
            return receiverAddress;
        }
    }
}