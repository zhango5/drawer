#include "drawer.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QGroupBox>
#include <QGridLayout>
#include <QToolButton>

Drawer::Drawer(QWidget* parent)
    : QToolBox(parent)
{
    this->layout()->setContentsMargins(0, 0, 0, 0);
    this->layout()->setSpacing(2);
}

Drawer::~Drawer()
{

}

void Drawer::LoadCfgFile(const QString& path)
{
    if (resolveCfgFile(path))
    {
        createDrawer();
    }
}

bool Drawer::resolveCfgFile(const QString& path)
{
    if (path.isEmpty())
    {
        return false;
    }

    QFile fi(path);
    if (!fi.open(QIODevice::ReadOnly))
    {
        return false;
    }

    QByteArray ba = fi.readAll();
    fi.close();

    QJsonDocument doc = QJsonDocument::fromJson(ba);

    if (!doc.isArray())
    {
        return false;
    }

    QJsonArray ja = doc.array();
    drawer.clear();

    for (int i = 0; i < ja.size(); ++i)
    {
        QJsonValue jv = ja.at(i);
        if (!jv.isObject())
        {
            continue;
        }

        box_t box;

        QJsonObject jo = jv.toObject();

        box.name = jo.value("name").toString();

        QJsonArray jva = jo.value("tools").toArray();

        for (int j = 0; j < jva.size(); ++j)
        {
            QJsonValue v = jva.at(j);

            if (v.isObject())
            {
                QJsonObject obj = v.toObject();
                tool_t tool = { 0 };
                tool.name = obj.value("name").toString();
                tool.icon = obj.value("icon").toString();

                box.tools.append(tool);
            }
        }

        drawer.append(box);
    }

    return true;
}

void Drawer::createDrawer()
{
    QGroupBox* group = nullptr;
    QGridLayout* layout = nullptr;
    QToolButton* tb = nullptr;

    for (int i = 0; i < drawer.size(); ++i)
    {
        const box_t& box = drawer[i];
        group = new QGroupBox(this);
        layout = new QGridLayout();
        layout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
        layout->setContentsMargins(10, 10, 10, 10);
        layout->setSpacing(20);

        for (int j = 0; j < box.tools.size(); ++j)
        {
            const tool_t& tool = box.tools[j];

            tb = new QToolButton();
            tb->setToolTip(tool.name);
            tb->setIcon(QIcon(QString(":/res/icon/%1/%2").arg(box.name).arg(tool.icon)));
            tb->setToolButtonStyle(Qt::ToolButtonIconOnly);
            tb->setFixedSize(BUTTON_SIZE, BUTTON_SIZE);
            tb->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
            tb->setAutoRaise(true);

            layout->addWidget(tb, j / COLUMN_NUM, j % COLUMN_NUM);
        }

        group->setLayout(layout);

        this->addItem(group, box.name);
    }
}
