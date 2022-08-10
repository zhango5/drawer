#ifndef DRAWER_H
#define DRAWER_H

#include <QToolBox>

typedef struct
{
    QString name;
    QString icon;
} tool_t;

typedef struct
{
    QString name;
    QList<tool_t> tools;
} box_t;

class Drawer : public QToolBox
{
    Q_OBJECT
public:
    explicit Drawer(QWidget* parent = nullptr);
    ~Drawer() override;

public:
    void LoadCfgFile(const QString& path);

private:
    bool resolveCfgFile(const QString& path);
    void createDrawer();

    QList<box_t> drawer;
    const int BUTTON_SIZE = 36;
    const int ICON_SIZE = 32;
    const int COLUMN_NUM = 2;
};

#endif // DRAWER_H
