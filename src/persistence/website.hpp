#pragma once

#include "./persistence.hpp"
#include "models/browserWebsite.hpp"
#include <memory>
#include <list>

namespace Persistence
{
    class Website : public Persistence
    {
    public:
        Website(const Website &) = delete;
        Website(Website &&) = delete;
        Website &operator=(const Website &) = delete;
        Website &operator=(Website &&) = delete;
        static Website *getInstance();

        const std::list<std::shared_ptr<Model::BrowserWebsite>> &getWebsites() const;
        void addWebsite(const std::shared_ptr<Model::BrowserWebsite> &website);
        void removeWebsite(const std::shared_ptr<Model::BrowserWebsite> &website);
        void updateWebsites();

    private:
        Website();
        ~Website();

    private:
        void readSettings() override;
        void writeSettings() override;

        QString getDataFilePath() const;
        void checkDataFile() const;

    private:
        std::list<std::shared_ptr<Model::BrowserWebsite>> websites;
    };
} // namespace Persistence
