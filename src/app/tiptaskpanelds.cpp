#include "tiptaskpanel.h"

TipTaskPanel::TipTaskPanel(QWidget *parent) :
    QWidget(parent)
{	
	Parent=parent;
	signalMapper = new QSignalMapper(this);

	connect(signalMapper,SIGNAL(mapped(QWidget*)),
				this,SIGNAL(buttonClicked(QWidget*)));

	connect(this,SIGNAL(buttonClicked(QWidget*)),this,SLOT(mie(QWidget*)));

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
//	QSettings settings;
//	settings.beginGroup("Apariencia");
//	color1 = settings.value("MenuPrinColor1").value<QColor>();
//	color2 = settings.value("MenuPrinColor2").value<QColor>();
//	settings.endGroup();

//	if ( !color1.isValid()  || !color2.isValid())
//	{
//		color1.setRgb(0,140,200);
//		color2.setRgb(0,24,36);
//	}
//	setSize(this->height);
}

void TipTaskPanel::addMenu(QString text,QString menu,bool checkable)
{
	if ( menu.isEmpty() || text.isEmpty() )
		return;

	foreach ( menuconf *conf, lstMenuConf )
	{
		if ( conf->text == text && conf->menu == menu )
		{
			qDebug() << "el boton " << text << "en el menu " << menu << "ya existe";
			return;
		}
	}

	menuconf *conf = new menuconf;
	conf->text = text;
	conf->menu = menu;
	conf->checkable = checkable;
	lstMenuConf.append(conf);
}

void TipTaskPanel::buildMenu()
{
	//creando el menu principal
	buildedMenu *bmenuprincipal = new buildedMenu;
	bmenuprincipal->widget = new TMenuWidget;
	bmenuprincipal->widget->setAttribute(Qt::WA_TranslucentBackground);

	QLabel *lblOpcionesMenuPrincipal = new QLabel("Opciones:");
	bmenuprincipal->widget->lyt->addWidget(lblOpcionesMenuPrincipal);

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
	foreach ( menuconf *conf, lstMenuConf )
	{
		buildedMenu *bmenu;

		//verificando si ya se creo el menu, si si se usa ese, si no se crea uno nuevo
		bool encontrado=false;
		foreach ( buildedMenu *bm, lstBuildedMenus )
		{
			if ( bm->menu == conf->menu )
			{
				encontrado = true;
				bmenu = bm;
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
		}

		//Creando el boton
		TMenuButton *btn = new TMenuButton(this);
		if ( conf->checkable )
		{
			btn->setCheckable(true);
			btn->setAutoExclusive(true);
		}
		btn->setText( conf->text );
		btn->setMenu( bmenu->menu );
		btn->setIText( conf->text );

		connect(btn, SIGNAL(clicked()), signalMapper, SLOT(map()));
		signalMapper->setMapping(btn,btn);

		//agregando
		bmenu->widget->lyt->addWidget( btn,1 );
	}

	//Agregando menus al escenario
	foreach ( buildedMenu *bm, lstBuildedMenus )
	{
		//creando el boton en el menu principal de este submenu
		TMenuButton *btnPrincipal = new TMenuButton(this);
		btnPrincipal->setText( bm->menu );
		btnPrincipal->setIText( bm->menu );

		connect(btnPrincipal, SIGNAL(clicked()), signalMapper, SLOT(map()));
		signalMapper->setMapping(btnPrincipal,btnPrincipal);

		bmenuprincipal->widget->lyt->addWidget( btnPrincipal,1 );

		//agregando resorte al menu
		QSpacerItem *sp = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);
		bm->widget->lyt->addItem( sp );

		//agregando boton atras
		TMenuButton *btnAtras = new TMenuButton;
		btnAtras->setText("Menu principal");
		btnAtras->setMenu( bm->menu );
		bm->widget->lyt->insertWidget(0, btnAtras );

		//agregando label
		QLabel *lbl = new QLabel(bm->menu+":");
		bm->widget->lyt->insertWidget(1, lbl );

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
		state->assignProperty(widgetPrincipal, "geometry", QRectF(-350,85,212,300));
		state->assignProperty(widget, "geometry", QRectF(-5,85,212,300));
		state->assignProperty(widgetPrincipal,"opacity", qreal(0));
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
	}
	QSpacerItem *sp = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);
	bmenuprincipal->widget->lyt->addItem( sp );

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

void TipTaskPanel::mie(QWidget *w)
{
	TMenuButton *b = (TMenuButton *)w;
	qDebug() << "boton precionado" << "menu: " << b->menu() << "texto: " << b->itext();
}
