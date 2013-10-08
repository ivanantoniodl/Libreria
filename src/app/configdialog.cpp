#include <QtGui>

#include "configdialog.h"
#include "mainwindow.h"

ConfigDialog::ConfigDialog(QWidget *parent):
	QDialog(parent)
{
    resize(800,500);

	contentsWidget = new QListWidget(this);
	contentsWidget->setViewMode(QListView::ListMode);
	contentsWidget->setIconSize(QSize(32,32));
    contentsWidget->setMovement(QListView::Static);
	contentsWidget->setMaximumWidth(150);
	contentsWidget->setMinimumWidth(150);
	contentsWidget->setGridSize(QSize(147,34));
	contentsWidget->setWrapping(true);
	contentsWidget->setSelectionRectVisible(true);

	pagesWidget = new QStackedWidget(this);

    QPushButton *closeButton = new QPushButton(tr("Cerrar"));
	closeButton->setIcon(QIcon(":/pics/dialog-close.png"));

    applyButton = new QPushButton(tr("Aplicar"));
	applyButton->setIcon(QIcon(":/pics/dialog-ok-apply.png"));

    okButton = new QPushButton(tr("Aceptar"));
    okButton->setIcon(QIcon(":/pics/dialog-ok.png"));

	loadPages();

    connect(contentsWidget,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
    connect(contentsWidget,SIGNAL(currentRowChanged(int)),this,SLOT(changeCurrentPluginIndex(int)));

	connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(applyButton,SIGNAL(clicked()),this,SLOT(apply()));
    connect(okButton,SIGNAL(clicked()),this,SLOT(ok()));

    contentsWidget->setCurrentRow(0);

    QVBoxLayout *verticallayoutwidgetprin = new QVBoxLayout;
	verticallayoutwidgetprin->addWidget(pagesWidget);

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget);
	horizontalLayout->addLayout( verticallayoutwidgetprin );

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
	buttonsLayout->addWidget(applyButton);
    buttonsLayout->addWidget(okButton);
	buttonsLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

	setWindowTitle(tr("Configurar"));
}

ConfigDialog::~ConfigDialog()
{
    qDebug() << "simon borrando";
}

void ConfigDialog::loadPages()
{
	lstConfigPagePlugin = MainWindow::instance()->getLstConfigPagePlugins();

    foreach ( ConfigPlugin *plugin, lstConfigPagePlugin )
	{
        QTabWidget *w = new QTabWidget(this);
		foreach ( ConfigPage *page, plugin->lstPages )
            w->insertTab( -1, page->widget(), page->shortTitle() );

		pagesWidget->addWidget( w );

        QListWidgetItem *configButton = new QListWidgetItem(contentsWidget);
		configButton->setIcon(plugin->icon());
		configButton->setText(plugin->shortTitle());
		configButton->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter );
		configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        connect(w,SIGNAL(currentChanged(int)),this,SLOT(tabWidget_currentChanged(int)));
	}
}

void ConfigDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    pagesWidget->setCurrentIndex(contentsWidget->row(current));    
}

void ConfigDialog::changeCurrentPluginIndex(int index)
{
	currentPluginIndex = index;
    QTabWidget *w = dynamic_cast<QTabWidget*>( pagesWidget->widget( currentPluginIndex ) );
    tabWidget_currentChanged( w->currentIndex() );
}

void ConfigDialog::tabWidget_currentChanged(int index)
{
    QTabWidget *w = dynamic_cast<QTabWidget*>( pagesWidget->widget( currentPluginIndex ) );
    ConfigPage *page = lstConfigPagePlugin.at(currentPluginIndex)->lstPages.at( w->currentIndex() );

    applyButton->setVisible( page->showApplyOk() );
    okButton->setVisible( page->showApplyOk() );

    page->updatePage();
}

void ConfigDialog::apply()
{
    QTabWidget *w = dynamic_cast<QTabWidget*>( pagesWidget->widget( currentPluginIndex ) );
	lstConfigPagePlugin.at(currentPluginIndex)->lstPages.at( w->currentIndex() )->apply();
}

void ConfigDialog::ok()
{
    apply();
    close();
}
