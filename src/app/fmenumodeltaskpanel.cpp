#include "fmenumodeltaskpanel.h"
#include "ui_fmenumodel.h"

//MenuOptions
//***********************************************************************************************************

QList< menuconf* > MenuOptions::lstMenuConf;

void MenuOptions::addMenu(QString text,
						  QString menu,
						  QString iconpath,
						  QString description,
						  bool checkable)
{
	if ( menu.isEmpty() || text.isEmpty() )
		return;

	bool menuPrinEncontrado=false;
	foreach ( menuconf *conf, getLstMenuConf() )
	{
		if ( conf->menu == menu )
			menuPrinEncontrado=true;

		if ( conf->text == text && conf->menu == menu )
		{
			qDebug() << "el boton " << text << "en el menu " << menu << "ya existe";
			return;
		}
	}

	//agregando el menu principal
	if ( ! menuPrinEncontrado )
	{
		menuconf *conf = new menuconf;
		conf->text = menu;
		lstMenuConf.append( conf );
	}

	//agregnado el menu
	menuconf *conf = new menuconf;

	conf->text = text;
	conf->menu = menu;
	conf->checkable = checkable;
	conf->icon = iconpath;
	conf->description = description;
	lstMenuConf.append(conf);
}

QList<menuconf*> MenuOptions::getLstMenuConf(QString group)
{
	QList<menuconf*> lst;
	foreach ( menuconf *mc, getLstMenuConf() )
	{
		if ( mc->menu == group )
			lst.append(mc);
	}
	return lst;
}

//TipTaskPanel
//***********************************************************************************************************

TipTaskPanel::TipTaskPanel(QWidget *parent) :
	QWidget(parent)
{
	Parent=parent;
	signalMapper = new QSignalMapper(this);

	connect(signalMapper,SIGNAL(mapped(QWidget*)),
				this,SIGNAL(buttonClicked(QWidget*)));

	connect(this,SIGNAL(buttonClicked(QWidget*)),this,SLOT(privateButtonClicked_widget(QWidget*)));

	abrirColores();
}

void TipTaskPanel::setSize(int h)
{
	height = h;
	view->setSceneRect(0,0,153,height-75);

	int x1,y1,x2,y2;
	QLinearGradient linearGrad(x1,y1,x2,y2);
	linearGrad.setColorAt(0, QColor(color1) );
	linearGrad.setColorAt(1, QColor(color2) );
	linearGrad.setSpread(QGradient::PadSpread);
	linearGrad.setStart(0,0);
	linearGrad.setFinalStop(0,height-150);

	scene->setBackgroundBrush(linearGrad);
}

void TipTaskPanel::actualizarColores()
{
 abrirColores();
}

void TipTaskPanel::abrirColores()
{
	QSettings settings;
	settings.beginGroup("Apariencia");
	color1 = settings.value("MenuPrinColor1").value<QColor>();
	color2 = settings.value("MenuPrinColor2").value<QColor>();
	settings.endGroup();

	if ( !color1.isValid()  || !color2.isValid())
	{
        //color1.setRgb(55,129,150);
        //color2.setRgb(0,10,14);
        color1.setRgb(16,32,55);
        color2.setRgb(21,42,71);
	}
}

void TipTaskPanel::buildMenu()
{
	//creando el menu principal
	buildedMenu *bmenuprincipal = new buildedMenu;
	bmenuprincipal->widget = new TMenuWidget;
	bmenuprincipal->widget->setAttribute(Qt::WA_TranslucentBackground);

	QLabel *lblOpcionesMenuPrincipal = new QLabel("Opciones:",this);
	bmenuprincipal->widget->layout()->addWidget(lblOpcionesMenuPrincipal);

	//creando el logo
	pixmap=new TPixmap(QPixmap(":/anexa.png"));

	//creando el escenario
	scene =  new QGraphicsScene(0, 0, 180, 300);
	scene->setBackgroundBrush(scene->palette().window());
	scene->addItem(pixmap); //agregando el logo

	//creando el panel principal
	QGraphicsProxyWidget *panelPrincipalProxy = new QGraphicsProxyWidget;
	panelPrincipalProxy->setWidget( bmenuprincipal->widget );
	QGraphicsWidget *widgetPrincipal = new QGraphicsWidget;
	QGraphicsLinearLayout *lytPrincipal = new QGraphicsLinearLayout(Qt::Vertical, widgetPrincipal);
	lytPrincipal->addItem(panelPrincipalProxy);
	widgetPrincipal->setLayout(lytPrincipal);

	scene->addItem(widgetPrincipal); //agregando el panel principal al escenario

	// estado principal
	QState *statePrincipal = new QState(&machine);
	statePrincipal->assignProperty(pixmap,"pos",QPointF(-18,11));
	statePrincipal->assignProperty(widgetPrincipal, "geometry", QRectF(-5,85,212,300));
	statePrincipal->assignProperty(widgetPrincipal,"opacity", qreal(1));
	machine.setInitialState(statePrincipal);

	//creando los menus
	foreach ( menuconf *conf, MenuOptions::getLstMenuConf() )
	{
		int btnCount;
		if ( conf->menu.isEmpty() )
			continue;

		buildedMenu *bmenu;

		//verificando si ya se creo el menu, si si se usa ese, si no se crea uno nuevo
		bool encontrado=false;
		foreach ( buildedMenu *bm, lstBuildedMenus )
		{
			if ( bm->menu == conf->menu )
			{
				encontrado = true;
				bmenu = bm;
				btnCount=bmenu->widget->getLstButtons().size()+1;
				break;
			}
		}
		if ( !encontrado )
		{
			bmenu = new buildedMenu;
			bmenu->menu = conf->menu;
			bmenu->widget = new TMenuWidget;
			bmenu->widget->setAttribute(Qt::WA_TranslucentBackground);
			lstBuildedMenus.append(bmenu);
			btnCount=1;
		}

		//Creando el boton
		TMenuButton *btn = new TMenuButton(this);
		if ( conf->checkable )
		{
			btn->setCheckable(true);
			btn->setAutoExclusive(true);
		}
		btn->setText( QString::number(btnCount)+". "+conf->text );
		btn->setMenu( bmenu->menu );
		btn->setIText( conf->text );

		connect(btn, SIGNAL(clicked()), signalMapper, SLOT(map()));
		signalMapper->setMapping(btn,btn);

		//agregando
		bmenu->widget->lytAddButton( btn );

		btnCount++;
	}


	//Agregando menus al escenario
	int btnCount=1;
	foreach ( buildedMenu *bm, lstBuildedMenus )
	{
		//creando el boton en el menu principal de este submenu
		TMenuButton *btnPrincipal = new TMenuButton(this);
		btnPrincipal->setText( QString::number(btnCount)+". "+bm->menu );
		btnPrincipal->setIText( bm->menu );

		connect(btnPrincipal, SIGNAL(clicked()), signalMapper, SLOT(map()));
		signalMapper->setMapping(btnPrincipal,btnPrincipal);

		bmenuprincipal->widget->lytAddButton( btnPrincipal );

		//agregando resorte al menu
		QSpacerItem *sp = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);
		bm->widget->layout()->addItem( sp );

		//agregando boton atras
		TMenuButton *btnAtras = new TMenuButton;
		btnAtras->setIcon(QIcon(":/themes/default/pics/arrow-left.png"));
		btnAtras->setText("Menu principal");
		btnAtras->setIText("MenuPrincipal");
		btnAtras->setMenu( bm->menu );
		bm->widget->lytAddButton( btnAtras, 0 );

		//agregando label
		QLabel *lbl = new QLabel(bm->menu+":");
		bm->widget->layout()->insertWidget(1, lbl );

		//creando el panel
		QGraphicsProxyWidget *panelProxy = new QGraphicsProxyWidget;
		panelProxy->setWidget( bm->widget );
		QGraphicsWidget *widget = new QGraphicsWidget;
		QGraphicsLinearLayout *lyt = new QGraphicsLinearLayout(Qt::Vertical, widget);
		lyt->addItem(panelProxy);
		widget->setLayout(lyt);

		scene->addItem(widget); //agregando el panel principal al escenario

		statePrincipal->assignProperty(widget,"geometry", QRectF(250,85,212,300));
		statePrincipal->assignProperty(widget,"opacity", qreal(0));

		QState *state = new QState(&machine);
		if ( bm->widget->getLstButtons().size() > 4 )
			state->assignProperty(widgetPrincipal, "geometry", QRectF(-350,85,212,300));
		else
			state->assignProperty(widgetPrincipal, "geometry", QRectF(-15,200,212,300));

		state->assignProperty(widgetPrincipal,"opacity", qreal(0));
		state->assignProperty(widget, "geometry", QRectF(-5,85,212,300));
		state->assignProperty(widget,"opacity", qreal(1));

		//transicion hacia actual
		QAbstractTransition *trans =statePrincipal->addTransition(btnPrincipal,SIGNAL(clicked()), state);
		trans->addAnimation(new QPropertyAnimation(widgetPrincipal, "geometry"));
		trans->addAnimation(new QPropertyAnimation(widget, "geometry"));
		trans->addAnimation(new QPropertyAnimation(widgetPrincipal, "opacity"));
		trans->addAnimation(new QPropertyAnimation(widget, "opacity"));

		//transicion de actual
		QAbstractTransition *transact = state->addTransition(btnAtras,SIGNAL(clicked()),statePrincipal);
		transact->addAnimation(new QPropertyAnimation(widget, "geometry"));
		transact->addAnimation(new QPropertyAnimation(widgetPrincipal, "geometry"));
		transact->addAnimation(new QPropertyAnimation(widget, "opacity"));
		transact->addAnimation(new QPropertyAnimation(widgetPrincipal, "opacity"));

		btnCount++;
	}
	QSpacerItem *sp = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);
	bmenuprincipal->widget->layout()->addItem( sp );

	lstBuildedMenus.append(bmenuprincipal);

	machine.start();

	view = new QGraphicsView(scene,this);
	view->setFrameShape(QFrame::NoFrame);
	view->setFrameShadow(QFrame::Plain);
	view->setLineWidth(0);
	view->setStyleSheet("border: 0px; padding: 0px; margin: opx;");
	layoutWidget = new QVBoxLayout(this);
	layoutWidget ->setContentsMargins(0,0,0,0);
	layoutWidget->addWidget(view);
	setLayout(layoutWidget);
	setStyleSheet("border: 0px; padding: 0px; margin: opx;");
}

void TipTaskPanel::privateButtonClicked_widget(QWidget *w)
{
	TMenuButton *b = (TMenuButton *)w;
	emit buttonClickedPath(b->menu(),b->itext());
}

void TipTaskPanel::setSelectedMenu(QString group,QString text)
{
	//mostrando el grupo
	if ( group != lastGroup )
	{
		//yendo al menu principal
		foreach ( buildedMenu *bm, lstBuildedMenus )
		{
			if ( bm->menu != lastGroup )
				continue;

			foreach ( QWidget* w, bm->widget->getLstButtons() )
			{
				TMenuButton *button = (TMenuButton *)w;
				if ( button->itext() == "MenuPrincipal" )
				{
					button->click();
					break;
				}
			}
		}

		disconnect(signalMapper,SIGNAL(mapped(QWidget*)),
					this,SIGNAL(buttonClicked(QWidget*)));

		//yendo al nuevo menu
		buildedMenu *bm = lstBuildedMenus.last();

		foreach ( QWidget* w, bm->widget->getLstButtons() )
		{
			TMenuButton *button = (TMenuButton *)w;
			if ( button->itext() == group )
			{
				button->click();
				break;
			}
		}

		lastGroup = group;
	}
	else
		disconnect(signalMapper,SIGNAL(mapped(QWidget*)),
					this,SIGNAL(buttonClicked(QWidget*)));

	if ( group.isEmpty() )
	{
		connect(signalMapper,SIGNAL(mapped(QWidget*)),
					this,SIGNAL(buttonClicked(QWidget*)));
		return;
	}

	//mostrando el boton seleccionado
	for ( int c=0; c<lstBuildedMenus.size()-1; c++ )
	{
		buildedMenu* bm = lstBuildedMenus.at(c);
		foreach ( QWidget* w, bm->widget->getLstButtons() )
		{
			TMenuButton *button = (TMenuButton *)w;

			if ( button->menu() == group && button->itext() == text )
			{
				if ( ! button->isChecked() )
					button->click();
				connect(signalMapper,SIGNAL(mapped(QWidget*)),
							this,SIGNAL(buttonClicked(QWidget*)));
				return;
			}
		}
	}
	connect(signalMapper,SIGNAL(mapped(QWidget*)),
				this,SIGNAL(buttonClicked(QWidget*)));
}

//OptionModel
//***********************************************************************************************************
OptionModel::OptionModel(QObject* parent):
	QAbstractTableModel(parent) {}

QVariant OptionModel::data(const QModelIndex &index, int role ) const
{
	int r;
	if (index.isValid())
	{
		r = index.row();
		switch (role)
		{
			case Qt::DisplayRole :
			{
				if ( index.column() == 0 )
					return QString::number(index.row()+1)+". "+MenuOptions::getLstMenuConf(group).at(r)->text;
				else
					return MenuOptions::getLstMenuConf(group).at(r)->description;
				break;
			}
			case Qt::DecorationRole :
			{
				if ( index.column() == 0 )
					return MenuOptions::getLstMenuConf(group).at(r)->icon;
				break;
			}
		};
	}
	return QVariant();
}

int OptionModel::rowCount(const QModelIndex &parent ) const
{
	return MenuOptions::getLstMenuConf(group).size();
}

int OptionModel::columnCount(const QModelIndex & parent) const
{
	Q_UNUSED(parent);
	return 2;
}

void OptionModel::showGroup(QString Group)
{
	group = Group;
	reset();
}

//FmenuModel
//***********************************************************************************************************

FMenuModel::FMenuModel(QWidget *parent) :
	QWidget(parent),
	m_ui(new Ui::FMenuModel)
{
	m_ui->setupUi(this);
	Parent = parent;
//	m_ui->label->setAttribute(Qt::WA_TranslucentBackground);
//	m_ui->label_2->setAttribute(Qt::WA_TranslucentBackground);

	m_ui->tabla->setAttribute(Qt::WA_TranslucentBackground);
	m_ui->tabla->setShowGrid(false);
	m_ui->tabla->setIconSize ( QSize(32,32) );
	m_ui->tabla->setColumnWidth(0,900);
	m_ui->tabla->setColumnWidth(1,800);
	m_ui->tabla->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_ui->tabla->setSelectionMode(QAbstractItemView::NoSelection);
	m_ui->tabla->verticalHeader()->setVisible(false);
	m_ui->tabla->horizontalHeader()->setVisible(false);
	m_ui->tabla->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_ui->tabla->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_ui->tabla->setAttribute(Qt::WA_TranslucentBackground);

	m_ui->tabla->viewport()->setAttribute(Qt::WA_StaticContents);
	m_ui->tabla->viewport()->setAttribute(Qt::WA_TranslucentBackground);

	model = new OptionModel;

	connect(m_ui->tabla, SIGNAL(clicked(const QModelIndex)),
			this, SLOT(privateModelClicked_widget(const QModelIndex)));
}

FMenuModel::~FMenuModel()
{
	delete m_ui;
}

void FMenuModel::showGroup(QString Group)
{
	model->showGroup( Group );
	group = Group;

	m_ui->lblTitulo->setText(group);
	m_ui->lblTitulo->setAttribute(Qt::WA_TranslucentBackground);

	m_ui->tabla->setModel(model);
	m_ui->tabla->setAttribute(Qt::WA_TranslucentBackground);
	m_ui->tabla->viewport()->setAttribute(Qt::WA_TranslucentBackground);
	m_ui->frmeOpciones->setFixedHeight( (m_ui->tabla->model()->rowCount() * 31) + 80 );
	m_ui->tabla->setFixedHeight( (m_ui->tabla->model()->rowCount() * 31) + 10 );
	m_ui->tabla->resizeColumnsToContents();
	m_ui->tabla->setColumnWidth(0, m_ui->tabla->columnWidth(0) + 20 );
	m_ui->tabla->resizeRowsToContents();
}

void FMenuModel::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type())
	{
	case QEvent::LanguageChange:
		m_ui->retranslateUi(this);
		break;
	default:
		break;
	}
}

void FMenuModel::privateModelClicked_widget(const QModelIndex index)
{
	QString seleccionado = m_ui->tabla->currentIndex().sibling(index.row(),0).data(0).toString();
	seleccionado = seleccionado.mid(seleccionado.indexOf(".")+2);
	emit itemClickedPath(group,seleccionado);
}
