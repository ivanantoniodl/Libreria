#ifndef FABOUTPLUGINS_H
#define FABOUTPLUGINS_H

#include <QDialog>
#include <QStringListModel>

class IPlugin;

namespace Ui {
    class FAboutPlugins;
}

class FAboutPlugins : public QDialog
{
    Q_OBJECT

public:
    explicit FAboutPlugins(QWidget *parent = 0);
    ~FAboutPlugins();

private slots:
	void on_lstPlugins_clicked(const QModelIndex &index);

private:
    Ui::FAboutPlugins *ui;
	QList<IPlugin*> lstPlugins;
	QStringListModel *model;
};

#endif // FABOUTPLUGINS_H
