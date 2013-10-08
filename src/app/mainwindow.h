#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fmenumodeltaskpanel.h>
#include "faboutapp.h"
#include "permisos.h"
#include "freportes.h"

#include "principalformplugin.h"
#include "configplugin.h"
#include "plugincollection.h"
#include "reportplugin.h"

#include "maquinamodel.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
	void resizeEvent ( QResizeEvent * event );

public:
    explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	static MainWindow *instance();
	QList<ConfigPlugin*> getLstConfigPagePlugins() { return lstConfigPagePlugins; }
	QList<PrincipalFormPlugin*> getLstPrincipalFormPlugins() { return lstPrincipalFormPlugins; }
	QList<ReportPlugin*> getLstReportPlugins() { return lstReportPlugins; }
	QList<IPlugin*> getLstIplugins() { return lstIplugins; }

private:
	QVBoxLayout *lytBase;
	TipTaskPanel *Barra;
	QTabWidget *tabWidget;
	QList<PrincipalFormPlugin*> lstPrincipalFormPlugins;
	QList<ConfigPlugin*> lstConfigPagePlugins;
	QList<ReportPlugin*> lstReportPlugins;
	QList<IPlugin*> lstIplugins;
	static MainWindow *INSTANCE;
	QWidgetList lstEraseWidgets;

	ConfigDialog *configDialog;

	QAction *actionShowPrincipalMenu;
	QDockWidget *dockWidget;

	//administrador de paginas
	struct Page
	{
		QWidget *widget;
		QString menuGroup;
		QString menuText;

		Page()
		{
			widget=NULL;
		}
	};
	QList< QList<Page*> > lstTabPages;

	void loadPlugins();
	void loadTheme();
	void createTabWidget();
	void createTaskPanel();
	void createMenus();

	void setActualTabWidget(QWidget*,QString menuGroup,QString menuText);
	void addActualTabWidget(QWidget*,QString menuGroup,QString menuText);
    void addActualTabWidgetPage(QWidget* widget, QString menuText, closeEater *eater);

private slots:
	void TMenuModel_optionClicked(QString,QString);
	void timer_eraseWidgets();

	void tabWidget_tabCloseRequested(int);
	void tabWidget_currentChanged (int);

    void formPluginAddNewPage(QWidget* widget, QString text, closeEater *eater);
    void currentWidgetClosed();

	void dock_visibilityChanged(bool);

	//acciones de los menus
	void addTab_action();
	void actionShowPrincipalMenu_triggered();
	void configure_action();
	void aboutPlugins_action();
	void aboutApp_action();
	void reports_action();
};

#endif // MAINWINDOW_H
