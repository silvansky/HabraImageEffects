#include "habrawidget.h"
#include "ui_habrawidget.h"
#include "networking.h"
#include "imagemanager.h"

#include <QDebug>

#define I2P(image) QPixmap::fromImage(image)

HabraWidget::HabraWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::HabraWidget)
{
	ui->setupUi(this);

	connect(ui->pbtLoad, SIGNAL(clicked()), SLOT(onLoadButton()));
	connect(ui->pbtReset, SIGNAL(clicked()), SLOT(resetImage()));

	rotateTimer = new QTimer();
	rotateTimer->setInterval(100);
	rotateTimer->setProperty("angle", 0.0);
	connect(rotateTimer, SIGNAL(timeout()), SLOT(onRotateTimer()));
	resetImage();
}

HabraWidget::~HabraWidget()
{
	delete ui;
}

void HabraWidget::loadImage(const QString & urlString)
{
	Networking::httpGetImageAsync(QUrl(urlString), this, "onImageRead");
}

void HabraWidget::setImage(const QImage & image)
{
	currentImage = ImageManager::normallyResized(image, 150);
	updateImages();
}

void HabraWidget::resetImage()
{
	setImage(QImage(":/habr_logo.png"));
}

void HabraWidget::onLoadButton()
{
	loadImage(ui->lneUrlString->text());
}

void HabraWidget::updateImages()
{
	ui->lblOriginal->setPixmap(I2P(currentImage));
	ui->lblGrayscaled->setPixmap(I2P(ImageManager::grayscaled(currentImage)));
	QColor colorizationColor = ImageManager::resolveColor(ui->lneColorize->text());
	ui->lblColorized->setPixmap(I2P(ImageManager::colorized(currentImage, colorizationColor)));
	QColor shadowColor = ImageManager::resolveColor(ui->lneShadow->text());
	ui->lblShadowed->setPixmap(I2P(ImageManager::addShadow(currentImage, shadowColor, QPoint(3, 7), true)));
	double opacity = ui->dsbOpacity->value();
	ui->lblOpacitized->setPixmap(I2P(ImageManager::opacitized(currentImage, opacity)));
	ui->lblRotated->setPixmap(I2P(currentImage));
	rotateTimer->setProperty("angle", 0.0);
	rotateTimer->start();
	ui->lblSquared->setPixmap(I2P(ImageManager::squared(currentImage, 100)));
	ui->lblRoundSquared->setPixmap(I2P(ImageManager::roundSquared(currentImage, 100, 6)));
}

void HabraWidget::onRotateTimer()
{
	qreal angle = rotateTimer->property("angle").toReal();
	ui->lblRotated->setPixmap(I2P(ImageManager::rotatedImage(currentImage, angle)));
	rotateTimer->setProperty("angle", angle + 1.0);
}

void HabraWidget::onImageRead(const QUrl & imageUrl, const QImage & image)
{
	Q_UNUSED(imageUrl)
	setImage(image);
}
