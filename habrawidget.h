#ifndef HABRAWIDGET_H
#define HABRAWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QUrl>

namespace Ui {
class HabraWidget;
}

class HabraWidget : public QWidget
{
	Q_OBJECT
	
public:
	explicit HabraWidget(QWidget *parent = 0);
	~HabraWidget();

public slots:
	void loadImage(const QString & urlString);
	void setImage(const QImage & image);
	void resetImage();

private slots:
	void onLoadButton();
	void updateImages();
	void onRotateTimer();
	void onImageRead(const QUrl & imageUrl, const QImage & image);
private:
	Ui::HabraWidget *ui;
	QTimer * rotateTimer;
	QImage currentImage;
};

#endif // HABRAWIDGET_H
