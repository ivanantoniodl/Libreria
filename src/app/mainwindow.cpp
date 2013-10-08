#include "mainwindow.h"
#include "configdialog.h"
#include "faboutplugins.h"

MainWindow *MainWindow::INSTANCE = NULL;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
    /*ProductoModel *model = new ProductoModel;
    model->configureQuery()->Codigo();
    model->configureQuery()->Nombre();
    model->configureQuery()->CategoriaProducto_idCategoriaProducto();
    model->configureQuery()->addGroupBy( "CategoriaProducto_idCategoriaProducto" );
    model->configureQuery()->addHaving( "CategoriaProducto_idCategoriaProducto",1,TSqlG::GREATER_THAN );
    model->select();

    qDebug() << model->lastQuery();
*/

	//abriendo plugins
	loadPlugins();

	//tema
	loadTheme();

	//tabwidget
	createTabWidget();

	//panel
	createTaskPanel();

	//menus
	createMenus();

	//creando primer pestaña
	addTab_action();

	INSTANCE = this;
	configDialog=NULL;

    //se crea el WidgetPluginMainWindow y de una vez se conecta
    connect( WidgetPluginMainWindow::instance(),SIGNAL(showNewPage(QWidget*,QString,closeEater*)),
             this, SLOT(formPluginAddNewPage(QWidget*,QString,closeEater*)));
}

MainWindow::~MainWindow()
{
	qDeleteAll( lstPrincipalFormPlugins );
	qDeleteAll( lstConfigPagePlugins );
	qDeleteAll( lstReportPlugins ) ;
	qDeleteAll( lstIplugins );

    delete WidgetPluginMainWindow::instance();
}

void MainWindow::resizeEvent ( QResizeEvent * event )
{
	Barra->setSize(event->size().height());
}

MainWindow *MainWindow::instance() { return INSTANCE; }

void MainWindow::loadPlugins()
{
    QDir pluginsDir(qApp->applicationDirPath());
	foreach (QString fileName, pluginsDir.entryList(QDir::Files))
	{
        #ifdef QT_OS_LINUX
        if ( fileName.right(3) != ".so" )
            continue;
        #endif
        #ifdef QT_OS_WIN32
        if ( fileName.right(4) != ".dll" )
            continue;
        #endif

		QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));


		QObject *plugin = pluginLoader.instance();
		if (plugin)
		{
			PluginCollection *pluginCollection = qobject_cast<PluginCollection*>(plugin);
			if ( pluginCollection )
			{
				QList<IPlugin*> lstPluginsAbrir = pluginCollection->lstPlugins;
				foreach ( IPlugin* ip, lstPluginsAbrir )
				{
					if ( PrincipalFormPlugin *pfp = dynamic_cast<PrincipalFormPlugin*>(ip) )
					{
                        bool checked;
                        if ( pfp->getTypeForm() == PrincipalFormPlugin::TypeWidget )
                            checked=true;
                        else
                            checked=false;

                        MenuOptions::addMenu( pfp->menuName(),
                                              pfp->menuGroup(),
                                              ":/path",
                                              pfp->description(),
                                              checked);

						lstPrincipalFormPlugins.append(pfp);
						continue;
					}

					if ( ConfigPlugin *cpp = dynamic_cast<ConfigPlugin*>(ip) )
					{
						lstConfigPagePlugins.append( cpp );
						continue;
					}

					if ( ReportPlugin *rp = dynamic_cast<ReportPlugin*>(ip) )
					{
						lstReportPlugins.append( rp );
						continue;
					}

					if ( IPlugin * ipp = dynamic_cast<IPlugin*>(ip) )
					{
						lstIplugins.append( ipp );
						continue;
					}
                }
				continue;
			}

			PrincipalFormPlugin *principalformplugin = qobject_cast<PrincipalFormPlugin*>(plugin);
			if (principalformplugin)
			{
                bool checked;
                if ( principalformplugin->getTypeForm() == PrincipalFormPlugin::TypeWidget )
                    checked=true;
                else
                    checked=false;
				MenuOptions::addMenu( principalformplugin->menuName(),
									  principalformplugin->menuGroup(),
									  ":/path",
                                      principalformplugin->description(),
                                      checked);

				lstPrincipalFormPlugins.append(principalformplugin);
				continue;
			}

			ConfigPlugin *configplugin = qobject_cast<ConfigPlugin*>(plugin);
			if (configplugin)
			{
				lstConfigPagePlugins.append( configplugin );
				continue;
			}

			ReportPlugin *reportplugin = qobject_cast<ReportPlugin*>(plugin);
			if ( reportplugin )
			{
				lstReportPlugins.append( reportplugin );
				continue;
			}

			IPlugin *iplugin = qobject_cast<IPlugin*>(plugin);
			if (iplugin)
			{
				lstIplugins.append( iplugin );
				continue;
			}
		}
        else if ( ! pluginsDir.absoluteFilePath(fileName).contains("coreplugin") )
            qDebug() << "error al abrir el plugin: " << fileName;
	}
}

void MainWindow::loadTheme()
{
	QFile file(":/themes/default/theme.css");
	file.open(QFile::ReadOnly | QFile::Text);
	QTextStream in(&file);
	QString plantilla;
	plantilla=in.readAll();
	file.close();

	qApp->setStyleSheet(plantilla);

	setWindowState(Qt::WindowMaximized);
}

void MainWindow::createTabWidget()
{
	//iniciando tabwidget
	tabWidget = new QTabWidget;
	setCentralWidget(tabWidget);
	connect(tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(tabWidget_tabCloseRequested(int)));
	connect(tabWidget,SIGNAL(currentChanged(int)),this,SLOT(tabWidget_currentChanged(int)));
}

void MainWindow::createTaskPanel()
{
	//iniciando barra
	Barra = new TipTaskPanel(this);
	Barra->setMaximumWidth(220);
	Barra->setMinimumWidth(220);
	Barra->setContentsMargins(0,0,0,0);

	connect(Barra,SIGNAL(buttonClickedPath(QString,QString)),this,
			SLOT(TMenuModel_optionClicked(QString,QString)));

	Barra->buildMenu();

	//iniciando dock de la barra
	dockWidget = new QDockWidget(tr("Dock Widget"), this);
	dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea |
								Qt::RightDockWidgetArea );
	dockWidget->setWidget(Barra);
	dockWidget->setWindowTitle(tr("Menu principal"));
	addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
	connect(dockWidget,SIGNAL(visibilityChanged(bool)),this,SLOT(dock_visibilityChanged(bool)));
}

void MainWindow::createMenus()
{
	//file
	QMenu* fileMenu = menuBar()->addMenu(tr("&Archivo"));
	QAction *actionAddNewTab = new QAction(this);
	actionAddNewTab->setText(tr("Nueva pestaña"));
	connect( actionAddNewTab,SIGNAL(triggered()),this,SLOT(addTab_action()) );

	fileMenu->addAction( actionAddNewTab );

	//view
	QMenu* viewMenu = menuBar()->addMenu(tr("&Ver"));
	actionShowPrincipalMenu = new QAction(this);
	actionShowPrincipalMenu->setText(tr("Mostrar menu principal"));
	actionShowPrincipalMenu->setCheckable(true);
	actionShowPrincipalMenu->setChecked(true);
	connect( actionShowPrincipalMenu,SIGNAL(triggered()),this,SLOT(actionShowPrincipalMenu_triggered()) );

	viewMenu->addAction( actionShowPrincipalMenu );

	//preferences
    if ( lstConfigPagePlugins.size() > 0 )
	{
		QMenu* preferencesMenu = menuBar()->addMenu(tr("&Preferencias"));
		QAction *actionConfigure = new QAction(this);
		actionConfigure->setText(tr("Configurar"));
		connect( actionConfigure,SIGNAL(triggered()),this,SLOT(configure_action()) );

		preferencesMenu->addAction( actionConfigure );
	}

	//reportes
	if ( lstReportPlugins.size() > 0 )
	{
		QMenu* reportMenu = menuBar()->addMenu(tr("&Reportes"));
		QAction *actionReport = new QAction(this);
		actionReport->setText(tr("Reportes"));
		connect( actionReport,SIGNAL(triggered()),this,SLOT(reports_action()) );

		reportMenu->addAction( actionReport );
	}

	//help
	QMenu* helpMenu = menuBar()->addMenu(tr("&Ayuda"));
	QAction *actionAboutPlugins = new QAction(this);
	actionAboutPlugins->setText(tr("Acerca de plugin"));
	connect( actionAboutPlugins,SIGNAL(triggered()),this,SLOT(aboutPlugins_action()) );

	QAction *actionAboutApp = new QAction(this);
	actionAboutApp->setText(tr("Acerca de"));
	connect( actionAboutApp,SIGNAL(triggered()),this,SLOT(aboutApp_action()) );

	helpMenu->addAction( actionAboutPlugins );
	helpMenu->addAction( actionAboutApp );
}

void MainWindow::setActualTabWidget(QWidget* widget,QString menuGroup,QString menuText)
{
	if ( ! menuGroup.isEmpty() )
	{
		if ( ! Permisos::validar(widget,menuText,menuGroup).permisoR )
		{
			QMessageBox::critical(this,"Error","No tiene permisos para entrar a este formulario");
			return;
		}
	}

	disconnect(tabWidget,SIGNAL(currentChanged(int)),this,SLOT(tabWidget_currentChanged(int)));

	if ( lstTabPages.size() > 0 )
	{
		QList<Page*> lst = lstTabPages.at( tabWidget->currentIndex() );

		if ( lst.size() > 0 )
		{
			foreach ( Page *page, lst )
			{
				if ( page->widget != NULL )
				{
					lstEraseWidgets.append( page->widget );
					QTimer::singleShot(1000, this, SLOT(timer_eraseWidgets()));
				}
				delete page;
			}

			lstTabPages.removeAt(tabWidget->currentIndex());
			lst.clear();
		}
	}

	QList<Page*> lst;

	Page *page = new Page;
	page->widget = widget;
	page->menuGroup = menuGroup;
	page->menuText = menuText;
	lst.append(page);

	lstTabPages.insert(tabWidget->currentIndex(),lst);

	int i = tabWidget->currentIndex();

	tabWidget->removeTab( i );
	tabWidget->insertTab( i, widget, menuText );
	tabWidget->setCurrentIndex( i );

	connect(tabWidget,SIGNAL(currentChanged(int)),this,SLOT(tabWidget_currentChanged(int)));
}

void MainWindow::addActualTabWidget(QWidget* widget,QString menuGroup,QString menuText)
{
	if ( ! menuGroup.isEmpty() )
	{
		if ( ! Permisos::validar(widget,menuText,menuGroup).permisoR )
		{
			QMessageBox::critical(this,"Error","No tiene permisos para entrar a este formulario");
			return;
		}
	}

	disconnect(tabWidget,SIGNAL(currentChanged(int)),this,SLOT(tabWidget_currentChanged(int)));

	QList<Page*> lst;

	Page *page = new Page;
	page->widget = widget;
	page->menuGroup = menuGroup;
	page->menuText = menuText;
	lst.append(page);

	lstTabPages.append(lst);

	tabWidget->insertTab( -1, widget, menuText );
	tabWidget->setCurrentIndex(lstTabPages.size()-1);

	connect(tabWidget,SIGNAL(currentChanged(int)),this,SLOT(tabWidget_currentChanged(int)));
}

void MainWindow::addActualTabWidgetPage( QWidget* widget, QString menuText, closeEater *eater )
{
    int i = tabWidget->currentIndex();
    QList<Page*> lst = lstTabPages.at( i );

    disconnect(tabWidget,SIGNAL(currentChanged(int)),this,SLOT(tabWidget_currentChanged(int)));

    Page *page = new Page;
    page->widget = widget;
    lst.append(page);

    lstTabPages.removeAt( i );
    lstTabPages.insert(i,lst);

    connect( eater,SIGNAL(close(QWidget*)),this,SLOT(currentWidgetClosed()) );

    tabWidget->removeTab( i );
    tabWidget->insertTab( i, widget, menuText );
    tabWidget->setCurrentIndex( i );

    connect(tabWidget,SIGNAL(currentChanged(int)),this,SLOT(tabWidget_currentChanged(int)));
}

void MainWindow::TMenuModel_optionClicked(QString group,QString text)
{
	if ( group.isEmpty() )
	{
		//si group esta vacio es porque se hizo clic al menu principal
		FMenuModel *f = new FMenuModel;
		connect(f,SIGNAL(itemClickedPath(QString,QString)),this,
				SLOT(TMenuModel_optionClicked(QString,QString)));
		connect(f,SIGNAL(itemClickedPath(QString,QString)),Barra,
				SLOT(setSelectedMenu(QString,QString)));
		f->showGroup(text);
		setActualTabWidget( f , text, text);
	}
	else
	{
		//si group no es vacio es porque se selecciono un formulario de un submenu
		foreach( PrincipalFormPlugin *plugin, lstPrincipalFormPlugins )
		{
			if ( group == plugin->menuGroup() && text == plugin->menuName() )
			{
                if ( plugin->getTypeForm() == PrincipalFormPlugin::TypeWidget )
                    setActualTabWidget( plugin->widget(), plugin->menuGroup() , plugin->name() );
                else
                {
                    QDialog *d = plugin->dialog();
                    d->exec();
                    delete d;
                }
				return;
			}
		}
	}
}

void MainWindow::timer_eraseWidgets()
{
	qDeleteAll(lstEraseWidgets);
	lstEraseWidgets.clear();
}

void MainWindow::tabWidget_tabCloseRequested(int index)
{
	QList<Page*> lst = lstTabPages.at( index );

	if ( lst.size() > 0 )
	{
		foreach ( Page *page, lst )
		{
			if ( page->widget != NULL )
				delete page->widget;
			delete page;
		}

		lstTabPages.removeAt(index);
		lst.clear();
	}

	if ( lstTabPages.size() == 1 )
		tabWidget->setTabsClosable(false);
}

void MainWindow::tabWidget_currentChanged (int index)
{
	if ( index < 0 )
		return;

	QList<Page*> lst = lstTabPages.at( index );

	if ( lst.size() == 0 )
		return;

	Page *page = lst.at(0);
	Barra->setSelectedMenu( page->menuGroup, page->menuText );
}

void MainWindow::dock_visibilityChanged(bool b)
{
	actionShowPrincipalMenu->setChecked(b);
}

void MainWindow::addTab_action()
{
	FMenuModel *f = new FMenuModel;
	connect(f,SIGNAL(itemClickedPath(QString,QString)),this,
			SLOT(TMenuModel_optionClicked(QString,QString)));
	connect(f,SIGNAL(itemClickedPath(QString,QString)),Barra,
			SLOT(setSelectedMenu(QString,QString)));
	f->showGroup("");
	addActualTabWidget( f , "", "Menu principal" );

	if ( lstTabPages.size() > 1 )
		tabWidget->setTabsClosable(true);
}

void MainWindow::actionShowPrincipalMenu_triggered()
{
	dockWidget->setVisible(actionShowPrincipalMenu->isChecked());
}

void MainWindow::configure_action()
{
	if ( configDialog == NULL )
		configDialog = new ConfigDialog(this);
	configDialog->exec();
}

void MainWindow::aboutPlugins_action()
{
	FAboutPlugins *v=new FAboutPlugins(this);
	v->exec();
	delete v;
}

void MainWindow::aboutApp_action()
{
	FAboutApp *v = new FAboutApp(this);
	v->exec();
	delete v;
}

void MainWindow::reports_action()
{
	FReportes *v = new FReportes(this);
	v->exec();
	delete v;
}

void MainWindow::formPluginAddNewPage(QWidget* widget, QString text, closeEater *eater)
{
    addActualTabWidgetPage( widget, text, eater );
}

void MainWindow::currentWidgetClosed()
{
    //se supone que si se cierra un widget es porque es un widget auxiliar y no el principal
    int i = tabWidget->currentIndex();

    QList<Page*> lst = lstTabPages.at( i );
    Page *page = lst.last();
    delete page;
    lst.removeLast();

    lstTabPages.removeAt( i );
    lstTabPages.insert(i,lst);

    disconnect(tabWidget,SIGNAL(currentChanged(int)),this,SLOT(tabWidget_currentChanged(int)));

    Page* lastPage = lst.last();
    tabWidget->removeTab( i );
    tabWidget->insertTab( i, lastPage->widget, lastPage->menuText );
    tabWidget->setCurrentIndex( i );

    connect(tabWidget,SIGNAL(currentChanged(int)),this,SLOT(tabWidget_currentChanged(int)));
}
