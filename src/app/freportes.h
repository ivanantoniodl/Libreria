#ifndef FREPORTES_H
#define FREPORTES_H

#include <QDialog>
#include <QTableWidget>

namespace Ui {
    class FReportes;
}

class ReportPlugin;

class FReportes : public QDialog
{
    Q_OBJECT
private:
	QList<ReportPlugin*> lstReports;
	int seleccionado;

public:
    explicit FReportes(QWidget *parent = 0);
    ~FReportes();

private slots:
	void on_btnAbrirReporte_clicked();

	void on_tbvwReportes_clicked(const QModelIndex &index);

	void on_tbvwReportes_doubleClicked(const QModelIndex &index);

private:
    Ui::FReportes *ui;
};

#endif // FREPORTES_H
