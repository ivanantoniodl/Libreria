#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>

class QListWidget;
class QListWidgetItem;
class QStackedWidget;
class ConfigPlugin;
class QLabel;

class ConfigDialog : public QDialog
{
Q_OBJECT

public:
	ConfigDialog(QWidget *parent = 0);
    ~ConfigDialog();

private slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
    void changeCurrentPluginIndex(int);
    void tabWidget_currentChanged(int);
	void apply();
    void ok();

private:

	void loadPages();

	int currentPluginIndex;
    QListWidget *contentsWidget;
    QPushButton *applyButton;
    QPushButton *okButton;
    QStackedWidget *pagesWidget;
	QList<ConfigPlugin*> lstConfigPagePlugin;
};

#endif
