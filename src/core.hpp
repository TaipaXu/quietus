#pragma once

#include <list>
#include <memory>
#include <QObject>

namespace Persistence
{
    class Website;
}

namespace Model
{
    class BrowserWebsite;
} // namespace Model

class Core : public QObject
{
    Q_OBJECT

public:
    Core();
    ~Core() = default;

private:
    void createInstance(const std::shared_ptr<Model::BrowserWebsite> &website);

private slots:
    void onNewInstance();
    void onRemoveInstance();

private:
    Persistence::Website *websitePersistence;
};
