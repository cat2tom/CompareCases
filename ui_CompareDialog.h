/********************************************************************************
** Form generated from reading UI file 'CompareDialog.ui'
**
** Created: Thu May 12 13:22:32 2011
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPAREDIALOG_H
#define UI_COMPAREDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "qvtkwidget.h"

QT_BEGIN_NAMESPACE

class Ui_CompareDialog
{
public:
    QAction *action_SelectQuery;
    QAction *action_SelectMatch;
    QWidget *centralwidget;
    QGroupBox *ctAxisGroupBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QRadioButton *axialRadioButton;
    QRadioButton *sagittalRadioButton;
    QRadioButton *coronalRadioButton;
    QLabel *sliceSelectionLabel;
    QSpinBox *sliceSelectionSpinBox;
    QSlider *sliceSelectionSlider;
    QLabel *maxSliceLabel;
    QPushButton *autoPlayPushButton;
    QLabel *dvhLabel;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *queryGroupBox;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QPushButton *queryInstitutionPushButton;
    QSpinBox *querySelectSpinBox;
    QVTKWidget *queryCTImageWidget;
    QVTKWidget *queryProjectionWidget;
    QGroupBox *legendGroupBox;
    QVBoxLayout *verticalLayout;
    QLabel *PTVLabel;
    QLabel *rectumLabel;
    QLabel *bladderLabel;
    QLabel *leftFemLabel;
    QLabel *rightFemLabel;
    QVTKWidget *queryDVHWidget;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *matchGroupBox;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QPushButton *matchInstitutionPushButton;
    QSpinBox *matchSelectSpinBox;
    QVTKWidget *matchCTImageWidget;
    QVTKWidget *matchProjectionWidget;
    QVTKWidget *matchDVHWidget;
    QWidget *layoutWidget3;
    QGridLayout *gridLayout_3;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *okPushButton;
    QPushButton *cancelPushButton;
    QGroupBox *projectionDisplayGroupBox;
    QPushButton *gantryAnglePushButton;
    QCheckBox *flatShadedCheckBox;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *transparencyLabel;
    QSpinBox *transparencySpinBox;
    QSlider *transparencySlider;
    QLabel *maxTransparencyLabel;
    QCheckBox *originCheckBox;
    QCheckBox *viewFemoralHeadsCheckBox;
    QCheckBox *overlayDVHCheckBox;
    QStatusBar *statusbar;
    QPushButton *historyPushButton;

    void setupUi(QDialog *CompareDialog)
    {
        if (CompareDialog->objectName().isEmpty())
            CompareDialog->setObjectName(QString::fromUtf8("CompareDialog"));
        CompareDialog->resize(1858, 1122);
        action_SelectQuery = new QAction(CompareDialog);
        action_SelectQuery->setObjectName(QString::fromUtf8("action_SelectQuery"));
        action_SelectMatch = new QAction(CompareDialog);
        action_SelectMatch->setObjectName(QString::fromUtf8("action_SelectMatch"));
        centralwidget = new QWidget(CompareDialog);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setGeometry(QRect(0, 1, 1846, 1091));
        ctAxisGroupBox = new QGroupBox(centralwidget);
        ctAxisGroupBox->setObjectName(QString::fromUtf8("ctAxisGroupBox"));
        ctAxisGroupBox->setGeometry(QRect(110, 2, 483, 51));
        layoutWidget = new QWidget(ctAxisGroupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 19, 463, 26));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        axialRadioButton = new QRadioButton(layoutWidget);
        axialRadioButton->setObjectName(QString::fromUtf8("axialRadioButton"));
        axialRadioButton->setChecked(true);

        horizontalLayout->addWidget(axialRadioButton);

        sagittalRadioButton = new QRadioButton(layoutWidget);
        sagittalRadioButton->setObjectName(QString::fromUtf8("sagittalRadioButton"));

        horizontalLayout->addWidget(sagittalRadioButton);

        coronalRadioButton = new QRadioButton(layoutWidget);
        coronalRadioButton->setObjectName(QString::fromUtf8("coronalRadioButton"));

        horizontalLayout->addWidget(coronalRadioButton);

        sliceSelectionLabel = new QLabel(layoutWidget);
        sliceSelectionLabel->setObjectName(QString::fromUtf8("sliceSelectionLabel"));

        horizontalLayout->addWidget(sliceSelectionLabel);

        sliceSelectionSpinBox = new QSpinBox(layoutWidget);
        sliceSelectionSpinBox->setObjectName(QString::fromUtf8("sliceSelectionSpinBox"));
        sliceSelectionSpinBox->setMinimum(0);
        sliceSelectionSpinBox->setMaximum(512);

        horizontalLayout->addWidget(sliceSelectionSpinBox);

        sliceSelectionSlider = new QSlider(layoutWidget);
        sliceSelectionSlider->setObjectName(QString::fromUtf8("sliceSelectionSlider"));
        sliceSelectionSlider->setMinimum(1);
        sliceSelectionSlider->setMaximum(141);
        sliceSelectionSlider->setOrientation(Qt::Horizontal);
        sliceSelectionSlider->setTickPosition(QSlider::TicksAbove);
        sliceSelectionSlider->setTickInterval(16);

        horizontalLayout->addWidget(sliceSelectionSlider);

        maxSliceLabel = new QLabel(layoutWidget);
        maxSliceLabel->setObjectName(QString::fromUtf8("maxSliceLabel"));

        horizontalLayout->addWidget(maxSliceLabel);

        autoPlayPushButton = new QPushButton(layoutWidget);
        autoPlayPushButton->setObjectName(QString::fromUtf8("autoPlayPushButton"));

        horizontalLayout->addWidget(autoPlayPushButton);

        dvhLabel = new QLabel(centralwidget);
        dvhLabel->setObjectName(QString::fromUtf8("dvhLabel"));
        dvhLabel->setGeometry(QRect(1376, 24, 223, 25));
        QFont font;
        font.setPointSize(16);
        dvhLabel->setFont(font);
        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 58, 1838, 514));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        queryGroupBox = new QGroupBox(layoutWidget1);
        queryGroupBox->setObjectName(QString::fromUtf8("queryGroupBox"));
        queryGroupBox->setFont(font);
        verticalLayout_3 = new QVBoxLayout(queryGroupBox);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        queryInstitutionPushButton = new QPushButton(queryGroupBox);
        queryInstitutionPushButton->setObjectName(QString::fromUtf8("queryInstitutionPushButton"));
        queryInstitutionPushButton->setMinimumSize(QSize(59, 23));
        queryInstitutionPushButton->setMaximumSize(QSize(59, 23));
        QFont font1;
        font1.setPointSize(8);
        queryInstitutionPushButton->setFont(font1);

        verticalLayout_2->addWidget(queryInstitutionPushButton);

        querySelectSpinBox = new QSpinBox(queryGroupBox);
        querySelectSpinBox->setObjectName(QString::fromUtf8("querySelectSpinBox"));
        querySelectSpinBox->setFont(font1);
        querySelectSpinBox->setFrame(true);
        querySelectSpinBox->setReadOnly(false);
        querySelectSpinBox->setMinimum(1);
        querySelectSpinBox->setMaximum(500);
        querySelectSpinBox->setValue(12);

        verticalLayout_2->addWidget(querySelectSpinBox);


        verticalLayout_3->addLayout(verticalLayout_2);


        horizontalLayout_2->addWidget(queryGroupBox);

        queryCTImageWidget = new QVTKWidget(layoutWidget1);
        queryCTImageWidget->setObjectName(QString::fromUtf8("queryCTImageWidget"));
        queryCTImageWidget->setMinimumSize(QSize(512, 512));
        queryCTImageWidget->setAutoFillBackground(true);

        horizontalLayout_2->addWidget(queryCTImageWidget);

        queryProjectionWidget = new QVTKWidget(layoutWidget1);
        queryProjectionWidget->setObjectName(QString::fromUtf8("queryProjectionWidget"));
        queryProjectionWidget->setMinimumSize(QSize(512, 512));
        queryProjectionWidget->setAutoFillBackground(true);
        legendGroupBox = new QGroupBox(queryProjectionWidget);
        legendGroupBox->setObjectName(QString::fromUtf8("legendGroupBox"));
        legendGroupBox->setGeometry(QRect(432, 12, 72, 109));
        legendGroupBox->setAutoFillBackground(false);
        legendGroupBox->setStyleSheet(QString::fromUtf8("background-color:  rgba(0, 0, 0, 255)"));
        legendGroupBox->setAlignment(Qt::AlignCenter);
        verticalLayout = new QVBoxLayout(legendGroupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        PTVLabel = new QLabel(legendGroupBox);
        PTVLabel->setObjectName(QString::fromUtf8("PTVLabel"));
        QPalette palette;
        QBrush brush(QColor(230, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(0, 0, 230, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        QBrush brush3(QColor(120, 120, 120, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        PTVLabel->setPalette(palette);
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        PTVLabel->setFont(font2);
        PTVLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(PTVLabel);

        rectumLabel = new QLabel(legendGroupBox);
        rectumLabel->setObjectName(QString::fromUtf8("rectumLabel"));
        QPalette palette1;
        QBrush brush4(QColor(139, 69, 19, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush5(QColor(172, 0, 172, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush5);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        rectumLabel->setPalette(palette1);
        rectumLabel->setFont(font2);
        rectumLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(rectumLabel);

        bladderLabel = new QLabel(legendGroupBox);
        bladderLabel->setObjectName(QString::fromUtf8("bladderLabel"));
        QPalette palette2;
        QBrush brush6(QColor(255, 215, 0, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush6);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        bladderLabel->setPalette(palette2);
        bladderLabel->setFont(font2);
        bladderLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(bladderLabel);

        leftFemLabel = new QLabel(legendGroupBox);
        leftFemLabel->setObjectName(QString::fromUtf8("leftFemLabel"));
        QPalette palette3;
        QBrush brush7(QColor(85, 85, 102, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush7);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush7);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        leftFemLabel->setPalette(palette3);
        leftFemLabel->setFont(font2);
        leftFemLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(leftFemLabel);

        rightFemLabel = new QLabel(legendGroupBox);
        rightFemLabel->setObjectName(QString::fromUtf8("rightFemLabel"));
        QPalette palette4;
        QBrush brush8(QColor(171, 171, 171, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush8);
        palette4.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette4.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette4.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush8);
        palette4.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette4.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        rightFemLabel->setPalette(palette4);
        rightFemLabel->setFont(font2);
        rightFemLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(rightFemLabel);


        horizontalLayout_2->addWidget(queryProjectionWidget);

        queryDVHWidget = new QVTKWidget(layoutWidget1);
        queryDVHWidget->setObjectName(QString::fromUtf8("queryDVHWidget"));
        queryDVHWidget->setMinimumSize(QSize(713, 512));
        queryDVHWidget->setAutoFillBackground(true);

        horizontalLayout_2->addWidget(queryDVHWidget);

        queryDVHWidget->raise();
        queryCTImageWidget->raise();
        queryProjectionWidget->raise();
        queryGroupBox->raise();
        layoutWidget2 = new QWidget(centralwidget);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 578, 1838, 514));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        matchGroupBox = new QGroupBox(layoutWidget2);
        matchGroupBox->setObjectName(QString::fromUtf8("matchGroupBox"));
        matchGroupBox->setFont(font);
        verticalLayout_5 = new QVBoxLayout(matchGroupBox);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        matchInstitutionPushButton = new QPushButton(matchGroupBox);
        matchInstitutionPushButton->setObjectName(QString::fromUtf8("matchInstitutionPushButton"));
        matchInstitutionPushButton->setMinimumSize(QSize(59, 23));
        matchInstitutionPushButton->setMaximumSize(QSize(59, 23));
        matchInstitutionPushButton->setFont(font1);

        verticalLayout_4->addWidget(matchInstitutionPushButton);

        matchSelectSpinBox = new QSpinBox(matchGroupBox);
        matchSelectSpinBox->setObjectName(QString::fromUtf8("matchSelectSpinBox"));
        matchSelectSpinBox->setFont(font1);
        matchSelectSpinBox->setMinimum(1);
        matchSelectSpinBox->setMaximum(500);
        matchSelectSpinBox->setValue(12);

        verticalLayout_4->addWidget(matchSelectSpinBox);


        verticalLayout_5->addLayout(verticalLayout_4);


        horizontalLayout_3->addWidget(matchGroupBox);

        matchCTImageWidget = new QVTKWidget(layoutWidget2);
        matchCTImageWidget->setObjectName(QString::fromUtf8("matchCTImageWidget"));
        matchCTImageWidget->setMinimumSize(QSize(512, 512));
        matchCTImageWidget->setAutoFillBackground(true);

        horizontalLayout_3->addWidget(matchCTImageWidget);

        matchProjectionWidget = new QVTKWidget(layoutWidget2);
        matchProjectionWidget->setObjectName(QString::fromUtf8("matchProjectionWidget"));
        matchProjectionWidget->setMinimumSize(QSize(512, 512));
        matchProjectionWidget->setAutoFillBackground(true);

        horizontalLayout_3->addWidget(matchProjectionWidget);

        matchDVHWidget = new QVTKWidget(layoutWidget2);
        matchDVHWidget->setObjectName(QString::fromUtf8("matchDVHWidget"));
        matchDVHWidget->setMinimumSize(QSize(713, 512));
        matchDVHWidget->setAutoFillBackground(true);

        horizontalLayout_3->addWidget(matchDVHWidget);

        layoutWidget3 = new QWidget(centralwidget);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(0, 4, 2, 2));
        gridLayout_3 = new QGridLayout(layoutWidget3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        layoutWidget4 = new QWidget(centralwidget);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(1678, 16, 158, 25));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        okPushButton = new QPushButton(layoutWidget4);
        okPushButton->setObjectName(QString::fromUtf8("okPushButton"));

        horizontalLayout_4->addWidget(okPushButton);

        cancelPushButton = new QPushButton(layoutWidget4);
        cancelPushButton->setObjectName(QString::fromUtf8("cancelPushButton"));

        horizontalLayout_4->addWidget(cancelPushButton);

        projectionDisplayGroupBox = new QGroupBox(centralwidget);
        projectionDisplayGroupBox->setObjectName(QString::fromUtf8("projectionDisplayGroupBox"));
        projectionDisplayGroupBox->setGeometry(QRect(623, 2, 495, 51));
        gantryAnglePushButton = new QPushButton(projectionDisplayGroupBox);
        gantryAnglePushButton->setObjectName(QString::fromUtf8("gantryAnglePushButton"));
        gantryAnglePushButton->setGeometry(QRect(258, 21, 86, 23));
        flatShadedCheckBox = new QCheckBox(projectionDisplayGroupBox);
        flatShadedCheckBox->setObjectName(QString::fromUtf8("flatShadedCheckBox"));
        flatShadedCheckBox->setGeometry(QRect(355, 24, 79, 17));
        layoutWidget_3 = new QWidget(projectionDisplayGroupBox);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(10, 20, 229, 26));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        transparencyLabel = new QLabel(layoutWidget_3);
        transparencyLabel->setObjectName(QString::fromUtf8("transparencyLabel"));

        horizontalLayout_6->addWidget(transparencyLabel);

        transparencySpinBox = new QSpinBox(layoutWidget_3);
        transparencySpinBox->setObjectName(QString::fromUtf8("transparencySpinBox"));
        transparencySpinBox->setMinimum(0);
        transparencySpinBox->setMaximum(100);

        horizontalLayout_6->addWidget(transparencySpinBox);

        transparencySlider = new QSlider(layoutWidget_3);
        transparencySlider->setObjectName(QString::fromUtf8("transparencySlider"));
        transparencySlider->setMinimum(0);
        transparencySlider->setMaximum(100);
        transparencySlider->setValue(0);
        transparencySlider->setOrientation(Qt::Horizontal);
        transparencySlider->setTickPosition(QSlider::TicksAbove);
        transparencySlider->setTickInterval(10);

        horizontalLayout_6->addWidget(transparencySlider);

        maxTransparencyLabel = new QLabel(layoutWidget_3);
        maxTransparencyLabel->setObjectName(QString::fromUtf8("maxTransparencyLabel"));

        horizontalLayout_6->addWidget(maxTransparencyLabel);

        originCheckBox = new QCheckBox(projectionDisplayGroupBox);
        originCheckBox->setObjectName(QString::fromUtf8("originCheckBox"));
        originCheckBox->setGeometry(QRect(440, 24, 51, 17));
        viewFemoralHeadsCheckBox = new QCheckBox(centralwidget);
        viewFemoralHeadsCheckBox->setObjectName(QString::fromUtf8("viewFemoralHeadsCheckBox"));
        viewFemoralHeadsCheckBox->setGeometry(QRect(1125, 26, 119, 17));
        overlayDVHCheckBox = new QCheckBox(centralwidget);
        overlayDVHCheckBox->setObjectName(QString::fromUtf8("overlayDVHCheckBox"));
        overlayDVHCheckBox->setGeometry(QRect(1250, 26, 61, 17));
        statusbar = new QStatusBar(CompareDialog);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setGeometry(QRect(0, 4, 3, 18));
        historyPushButton = new QPushButton(CompareDialog);
        historyPushButton->setObjectName(QString::fromUtf8("historyPushButton"));
        historyPushButton->setGeometry(QRect(14, 1096, 75, 23));
#ifndef QT_NO_SHORTCUT
        sliceSelectionLabel->setBuddy(sliceSelectionSpinBox);
#endif // QT_NO_SHORTCUT

        retranslateUi(CompareDialog);
        QObject::connect(sliceSelectionSpinBox, SIGNAL(valueChanged(int)), sliceSelectionSlider, SLOT(setValue(int)));
        QObject::connect(sliceSelectionSlider, SIGNAL(valueChanged(int)), sliceSelectionSpinBox, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(CompareDialog);
    } // setupUi

    void retranslateUi(QDialog *CompareDialog)
    {
        CompareDialog->setWindowTitle(QApplication::translate("CompareDialog", "Compare Cases", 0, QApplication::UnicodeUTF8));
        action_SelectQuery->setText(QApplication::translate("CompareDialog", "select query", 0, QApplication::UnicodeUTF8));
        action_SelectMatch->setText(QApplication::translate("CompareDialog", "select matching case", 0, QApplication::UnicodeUTF8));
        ctAxisGroupBox->setTitle(QApplication::translate("CompareDialog", "CT Display", 0, QApplication::UnicodeUTF8));
        axialRadioButton->setText(QApplication::translate("CompareDialog", "Axial", 0, QApplication::UnicodeUTF8));
        sagittalRadioButton->setText(QApplication::translate("CompareDialog", "Sagittal", 0, QApplication::UnicodeUTF8));
        coronalRadioButton->setText(QApplication::translate("CompareDialog", "Coronal", 0, QApplication::UnicodeUTF8));
        sliceSelectionLabel->setText(QApplication::translate("CompareDialog", "Z slice:", 0, QApplication::UnicodeUTF8));
        maxSliceLabel->setText(QApplication::translate("CompareDialog", "max", 0, QApplication::UnicodeUTF8));
        autoPlayPushButton->setText(QApplication::translate("CompareDialog", "Auto-play", 0, QApplication::UnicodeUTF8));
        dvhLabel->setText(QApplication::translate("CompareDialog", "Dose Volume Histogram", 0, QApplication::UnicodeUTF8));
        queryGroupBox->setTitle(QApplication::translate("CompareDialog", "Query", 0, QApplication::UnicodeUTF8));
        queryInstitutionPushButton->setText(QApplication::translate("CompareDialog", "Duke", 0, QApplication::UnicodeUTF8));
        querySelectSpinBox->setPrefix(QString());
        legendGroupBox->setTitle(QString());
        PTVLabel->setText(QApplication::translate("CompareDialog", "PTV", 0, QApplication::UnicodeUTF8));
        rectumLabel->setText(QApplication::translate("CompareDialog", "rectum", 0, QApplication::UnicodeUTF8));
        bladderLabel->setText(QApplication::translate("CompareDialog", "bladder", 0, QApplication::UnicodeUTF8));
        leftFemLabel->setText(QApplication::translate("CompareDialog", "left fem", 0, QApplication::UnicodeUTF8));
        rightFemLabel->setText(QApplication::translate("CompareDialog", "right fem", 0, QApplication::UnicodeUTF8));
        matchGroupBox->setTitle(QApplication::translate("CompareDialog", "Match", 0, QApplication::UnicodeUTF8));
        matchInstitutionPushButton->setText(QApplication::translate("CompareDialog", "Duke", 0, QApplication::UnicodeUTF8));
        okPushButton->setText(QApplication::translate("CompareDialog", "OK", 0, QApplication::UnicodeUTF8));
        cancelPushButton->setText(QApplication::translate("CompareDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        projectionDisplayGroupBox->setTitle(QApplication::translate("CompareDialog", "Projection Display", 0, QApplication::UnicodeUTF8));
        gantryAnglePushButton->setText(QApplication::translate("CompareDialog", "Gantry Angle", 0, QApplication::UnicodeUTF8));
        flatShadedCheckBox->setText(QApplication::translate("CompareDialog", "Flat shaded", 0, QApplication::UnicodeUTF8));
        transparencyLabel->setText(QApplication::translate("CompareDialog", "%Transparency", 0, QApplication::UnicodeUTF8));
        maxTransparencyLabel->setText(QApplication::translate("CompareDialog", "100", 0, QApplication::UnicodeUTF8));
        originCheckBox->setText(QApplication::translate("CompareDialog", "Axes", 0, QApplication::UnicodeUTF8));
        viewFemoralHeadsCheckBox->setText(QApplication::translate("CompareDialog", "View Femoral Heads", 0, QApplication::UnicodeUTF8));
        overlayDVHCheckBox->setText(QApplication::translate("CompareDialog", "Overlay", 0, QApplication::UnicodeUTF8));
        historyPushButton->setText(QApplication::translate("CompareDialog", "History", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CompareDialog: public Ui_CompareDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPAREDIALOG_H
