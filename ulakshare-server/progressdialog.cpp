#include "progressdialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QFrame>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include<QApplication>
#include<QScreen>
#include<QDesktopWidget>

ProgressDialog::ProgressDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("UlakShare Dosya Payşalım Paneli");
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    QSize screenSize = qApp->screens()[0]->size();
    h=screenSize.height()/15.1;
    w=h*2;
    int x = (screenGeometry.width()/2 - w*3);
    int y = (screenGeometry.height() - w*3) / 2;
    this->move(x, y);
    //qDebug()<<w<<h<<screenSize.height()/16;
    setStyleSheet(R"(

    QDialog {
        background-color: #f5f7fb;
        color: #1f2a37;
        font-family: Arial;
        font-size: 10px;
    }

    /* BUTTONS */

    QToolButton {
        background-color: #ffffff;
        border: 1px solid #e5eaf2;
        padding: 5px 10px;
        border-radius: 8px;
        color: #1f2a37;
        font-weight:600;
    }

    QToolButton:hover {
        background-color: #f0f6ff;
        border: 1px solid #cfe2ff;
    }

    QToolButton:pressed {
        background-color: #e6f0ff;
    }

    /* PRIMARY BUTTON */
/*
    QToolButton#startButton {
        background-color: #ffffff;
        color: white;
        border: none;
    }

    QToolButton#startButton:hover {
        background-color: #256fd1;
    }*/

    /* TOTAL BAR */

    QProgressBar {
        border: none;
        border-radius: 6px;
        background-color: #e9eef5;
        text-align: center;
        color: #1f2a37;
        height: 10px;
    }

    QProgressBar::chunk {
        background-color: #2f80ed;
        border-radius: 6px;
    }

    QScrollArea {
        border: none;
        background: transparent;
    }

    QRadioButton {
        color: #1f2a37;
        spacing: 5px;
        font-size: 8px;
    }

QLineEdit {
    background-color: #ffffff;
    border: 1px solid #e5eaf2;
    border-radius: 8px;
    padding: 2px 5px;
    color: #1f2a37;
    selection-background-color: #2f80ed;
    selection-color: white;
    font-size: 6px;
}

QLineEdit:hover {
    border: 1px solid #cfe2ff;
    background-color: #fafdff;
}

QLineEdit:focus {
    border: 1px solid #2f80ed;
    background-color: #ffffff;
}

QLineEdit:disabled {
    background-color: #eef2f7;
    color: #8a94a6;
}
    )");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(6,6,6,6);
    mainLayout->setSpacing(4);

    // =====================================================
    // TOP BAR
    // =====================================================

    buttonWidget = new QWidget;
    QHBoxLayout *topBar = new QHBoxLayout(buttonWidget);
    topBar->setContentsMargins(0,0,0,0);
    topBar->setSpacing(0);

    pathWidget = new QWidget;
    //pathWidget->resize(w*6,h*0.5);
    QHBoxLayout *pathLayout = new QHBoxLayout(pathWidget);
    pathLayout->setContentsMargins(0,0,0,0);
    pathLayout->setSpacing(0);

    QLabel *filePathLabel=new QLabel("Dosya Konumu");
    filePathLabel->setFixedSize(w,h*0.5);
    filePathLabel->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    filePathLE = new QLineEdit();
    filePathLE->setFixedSize(w*4.5,h*0.5);
    filePathLE->setStyleSheet("font-size:"+QString::number(font.toInt()+2)+"px;");

    QToolButton *fileSelectButton=new QToolButton();
    fileSelectButton->setFixedSize(w/2,h*0.5);
    fileSelectButton->setAutoRaise(true);
    //fileSelectButton->setAutoFillBackground(true);
    fileSelectButton->setText(tr("..."));
    fileSelectButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    fileSelectButton->setIcon(QIcon(":/icons/file.svg"));
    fileSelectButton->setIconSize(QSize(w/2,h*0.7));
    fileSelectButton->setToolButtonStyle(Qt::ToolButtonIconOnly);

    connect(fileSelectButton, &QToolButton::clicked, [=]() {

       // QString seatUser = helper.detectActiveUser();// 1) Aktif kullanıcıyı bul
        //qDebug()<<"Kullanıcı: "<<sessionUser;
    QString fileName = QFileDialog::getOpenFileName(this,tr("Dosya Seç"),"/home/", tr("Files (*)"));
        filePathLE->setText(fileName);
        updatePath(fileName);

    });
    QToolButton *directorySelectButton=new QToolButton();
    directorySelectButton->setFixedSize(w/2,h*0.5);
    directorySelectButton->setAutoRaise(true);
    //directorySelectButton->setAutoFillBackground(true);
    directorySelectButton->setText(tr("..."));
    directorySelectButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    directorySelectButton->setIcon(QIcon(":/icons/directory.svg"));
    directorySelectButton->setIconSize(QSize(w/2,h*0.7));
    directorySelectButton->setToolButtonStyle(Qt::ToolButtonIconOnly);

    connect(directorySelectButton, &QToolButton::clicked, [=]() {

       // QString seatUser = helper.detectActiveUser();// 1) Aktif kullanıcıyı bul
        //qDebug()<<"Kullanıcı: "<<sessionUser;
        QString dirPath = QFileDialog::getExistingDirectory(
                    this,
                    tr("Dizin Seç"),
                    "/home/"
                    );

        if(dirPath.isEmpty())
            return;

        filePathLE->setText(dirPath);

        updatePath(dirPath);

    });
    pathLayout->addWidget(filePathLabel);
    pathLayout->addWidget(filePathLE);
    pathLayout->addStretch();
    pathLayout->addWidget(fileSelectButton);
    pathLayout->addWidget(directorySelectButton);

    discoveryButton = new QToolButton;
    discoveryButton->setText("Pc Ara");
    discoveryButton->setFixedSize(w,h);
    discoveryButton->setIcon(QIcon(":/icons/search.svg"));
    discoveryButton->setIconSize(QSize(w*0.5,h*0.5));
    discoveryButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    connect(discoveryButton,
            &QToolButton::clicked,
            this,
            &ProgressDialog::onDiscoveryButtonClicked);

    startButton = new QToolButton;
    startButton->setObjectName("startButton");
    startButton->setText("Gönder");
    startButton->setFixedSize(w,h);
    startButton->setIcon(QIcon(":/icons/send.svg"));
    startButton->setIconSize(QSize(w*0.5,h*0.5));
    startButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    /*connect(startButton,
            &QToolButton::clicked,
            this,
            &ProgressDialog::onStartButtonClicked);
    */
    startButton->setMenu(sendMenu());
    startButton->setPopupMode(QToolButton::InstantPopup);


    selectAllButton = new QToolButton;
    selectAllButton->setText("Tümünü Seç");
    selectAllButton->setFixedSize(w,h);
    selectAllButton->setIcon(QIcon(":/icons/select.svg"));
    selectAllButton->setIconSize(QSize(w*0.5,h*0.5));
    selectAllButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    connect(selectAllButton,
            &QToolButton::clicked,
            this,
            &ProgressDialog::selectAllButtonClicked);

    unSelectAllButton = new QToolButton;
    unSelectAllButton->setText("Seçimi Kaldır");
    unSelectAllButton->setFixedSize(w,h);
    unSelectAllButton->setIcon(QIcon(":/icons/unselect.svg"));
    unSelectAllButton->setIconSize(QSize(w*0.5,h*0.5));
    unSelectAllButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    connect(unSelectAllButton,
            &QToolButton::clicked,
            this,
            &ProgressDialog::unSelectAllButtonClicked);

    topBar->addWidget(discoveryButton);
    topBar->addWidget(selectAllButton);
    topBar->addWidget(unSelectAllButton);
    topBar->addStretch();
    topBar->addWidget(startButton);

    mainLayout->addWidget(pathWidget);
    mainLayout->addWidget(buttonWidget);
    //mainLayout->addLayout(topBar);

    // =====================================================
    // TOTAL BAR
    // =====================================================

    totalBar = new QProgressBar;

    totalBar->setRange(0,100);
    totalBar->setValue(0);
    totalBar->setFormat("GENEL İLERLEME : %p%");
    totalBar->setFixedHeight(h*0.4);

    mainLayout->addWidget(totalBar);

    // =====================================================
    // SCROLL
    // =====================================================

    scroll = new QScrollArea;
    scroll->setWidgetResizable(true);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll->setSizePolicy(QSizePolicy::Expanding,
                          QSizePolicy::Ignored);
    //scroll->setMinimumHeight(0);
    container = new QWidget;
    //container->adjustSize();
    listLayout = new QVBoxLayout(container);

    listLayout->setSpacing(2);
    listLayout->setContentsMargins(0,0,0,0);

    listLayout->addStretch();

    scroll->setWidget(container);

    mainLayout->addWidget(scroll);
}

void ProgressDialog::onDiscoveryButtonClicked()
{
    emit sendDiscovery();
}

void ProgressDialog::onStartButtonClicked()
{


    //emit startTransfer();
}

void ProgressDialog::selectAllButtonClicked()
{
    for(ClientRow *client : clients)
    {
        client->select->setChecked(true);
    }

    emit updateSelectClients();
}

void ProgressDialog::unSelectAllButtonClicked()
{
    for(ClientRow *client : clients)
    {
        client->select->setChecked(false);
    }

    emit updateSelectClients();
}

void ProgressDialog::updateProgress(const QString &ip,
                                    int percent,
                                    QString clientHostName)
{
    if(!clients.contains(ip))
    {
        ClientRow *client = new ClientRow;

        // =====================================================
        // ROW
        // =====================================================

        QFrame *row = new QFrame;

        row->setSizePolicy(QSizePolicy::Expanding,
                           QSizePolicy::Fixed);

        row->setFixedHeight(h*0.45);
        row->setStyleSheet(R"(
        QFrame {
            background-color: #ffffff;
            border: 1px solid #e6ebf2;
            border-radius: 8px;
        }
        QFrame:hover {
            border: 1px solid #cfe2ff;
        }
        )");

        auto *shadow = new QGraphicsDropShadowEffect;

        shadow->setBlurRadius(6);
        shadow->setOffset(0,1);
        shadow->setColor(QColor(0,0,0,15));

        row->setGraphicsEffect(shadow);

        // =====================================================
        // LAYOUT
        // =====================================================

        QHBoxLayout *layout = new QHBoxLayout(row);
        layout->setContentsMargins(8,2,8,2);
        layout->setSpacing(6);

        // =====================================================
        // IP
        // =====================================================

        client->ip = new QLabel(ip);

        client->ip->setFixedWidth(w);

        client->ip->setStyleSheet(
            "color:#1f2a37;"
            "font-weight:600;"
        );

        // =====================================================
        // HOSTNAME
        // =====================================================

        client->hostName = new QLabel(clientHostName);

        client->hostName->setFixedWidth(h*1.4);

        client->hostName->setStyleSheet(
            "color:#6b7a90;"
        );

        // =====================================================
        // PROGRESS
        // =====================================================

        client->progresBar = new QProgressBar;

        client->progresBar->setRange(0,100);
        client->progresBar->setValue(0);
        client->progresBar->setFormat("%p%");

        client->progresBar->setSizePolicy(
            QSizePolicy::Expanding,
            QSizePolicy::Fixed
        );

        client->progresBar->setStyleSheet(R"(

        QProgressBar {
            border: none;
            border-radius: 4px;
            background-color: #edf2f7;
            text-align: center;
            color: 1f2a37;

        }

        QProgressBar::chunk {
            background-color: #2f80ed;
            border-radius: 4px;
        }

        )");

        // =====================================================
        // SPEED
        // =====================================================

        client->speedLabel = new QLabel("0 MB/s");

        client->speedLabel->setAlignment(Qt::AlignCenter);

        client->speedLabel->setFixedWidth(h*1.4);

        client->speedLabel->setStyleSheet(
            "color:#4b5563;"
        );

        // =====================================================
        // TIME
        // =====================================================

        client->timeLabel = new QLabel("00:00");

        client->timeLabel->setAlignment(Qt::AlignCenter);

        client->timeLabel->setFixedWidth(h*0.9);

        client->timeLabel->setStyleSheet(
            "color:#6b7280;"
        );

        // =====================================================
        // CHECKBOX
        // =====================================================

        client->select = new QCheckBox;

        client->select->setChecked(true);

        client->select->setStyleSheet(R"(

        QCheckBox {
            spacing: 0px;
        }

        QCheckBox::indicator {
            width: 14px;
            height: 14px;
            border-radius: 4px;
            border: 1px solid #cfd8e3;
            background-color: white;
        }

        QCheckBox::indicator:checked {
            background-color: #2f80ed;
            border: 1px solid #2f80ed;
        }

        )");

        connect(client->select,
                &QCheckBox::clicked,
                this,
                [=](bool checked)
        {
            clients[ip]->select->setChecked(checked);

            emit updateSelectClients();
        });

        // =====================================================
        // ADD
        // =====================================================

        layout->addWidget(client->ip);
        layout->addWidget(client->hostName);
        layout->addWidget(client->progresBar,1);
        layout->addWidget(client->speedLabel);
        layout->addWidget(client->timeLabel);
        layout->addWidget(client->select);

        listLayout->insertWidget(listLayout->count()-1,row);

        clients[ip] = client;
    }

    clients[ip]->progresBar->setValue(percent);

    qint64 now = QDateTime::currentMSecsSinceEpoch();

    clients[ip]->diffTime =
            now - clients[ip]->lastTime;

    clients[ip]->lastTime = now;

    /**************************/
    if(clients[ip]->startTime == 0)
    {
        clients[ip]->startTime = now;
    }

    qint64 elapsed =
            now - clients[ip]->startTime;

    double sec = elapsed / 1000.0;

    if(sec < 0.1)
        sec = 0.1;
    /***************************************/
    double transferredMb =
            ((double)clients[ip]->totalFileSize *
             percent / 100.0)
            / (1024.0*1024.0);

    double speed =
            transferredMb / sec;

    /********************************/
    clients[ip]->speedLabel->setText(
        QString("%1 MB/s")
        .arg(speed,0,'f',1));


    /************************************/
    int totalSec = sec;

    int min = totalSec / 60;

    int remainSec = totalSec % 60;

    clients[ip]->timeLabel->setText(
        QString("%1:%2")
        .arg(min,2,10,QChar('0'))
        .arg(remainSec,2,10,QChar('0')));
    /*******************************/

    updateTotalProgressBars();
    adjustSize();
    resize(w*6,
           pathWidget->height()
           +buttonWidget->height()
           + totalBar->height()
           + container->height()+h);
}

void ProgressDialog::allProgressStart(qint64 totalSize)
{
    for(ClientRow *client : clients)
    {
        client->progresBar->setValue(0);
        client->totalFileSize=totalSize;
        client->startTime=QDateTime::currentMSecsSinceEpoch();
    }
    updateTotalProgressBars();
}

void ProgressDialog::updateTotalProgressBars()
{
    int sum = 0;
    int selectCount = 0;
    qint64 averageTime = 0;
    qint64 sumTime = 0;
    qint64 fileSize;
    for(ClientRow *client : clients)
    {
        if(client->select->isChecked())
        {
            sum += client->progresBar->value();
            sumTime += client->diffTime;
            selectCount++;
            fileSize=client->totalFileSize;
        }
    }

    totalBar->setValue(
        selectCount == 0
        ? 0
        : sum / selectCount
    );

    /*if(totalBar->value() > 90)
    {
        averageTime = sumTime / selectCount;
        ///qDebug()<<"denemem"<<averageTime<<fileSize;
        if((fileSize<10000)||(averageTime>2000))
            emit sendFileTransferAllDone(500);
        else
            emit sendFileTransferAllDone(averageTime);
    }*/
}

void ProgressDialog::markDone(const QString &ip)
{
    if(clients.contains(ip))
    {
        clients[ip]->progresBar->setValue(100);
        clients[ip]->progresBar->setFormat("DONE");
    }
    updateTotalProgressBars();
}

void ProgressDialog::markDebInstallStart(const QString &ip)
{
    if(clients.contains(ip))
    {
        clients[ip]->progresBar->setValue(100);
        clients[ip]->progresBar->setFormat("DEB INSTALL START");
    }
}

void ProgressDialog::markDebInstallDone(const QString &ip,
                                        const QString &status)
{
    Q_UNUSED(status);

    if(clients.contains(ip))
    {
        clients[ip]->progresBar->setValue(100);
        clients[ip]->progresBar->setFormat("DEB INSTALL DONE");
    }
}

void ProgressDialog::markScriptInstallStart(const QString &ip)
{
    if(clients.contains(ip))
    {
        clients[ip]->progresBar->setValue(100);
        clients[ip]->progresBar->setFormat("SCRIPT INSTALL START");
    }
}

void ProgressDialog::markScriptInstallDone(const QString &ip,
                                           const QString &status)
{
    Q_UNUSED(status);
    if(clients.contains(ip))
    {
        clients[ip]->progresBar->setValue(100);
        clients[ip]->progresBar->setFormat("SCRIPT INSTALL DONE");
    }
}

void ProgressDialog::updateTotalBarText(const QString &text)
{
    totalBar->setFormat(text);
}

QMenu *ProgressDialog::sendMenu()
{   QMenu *menu = new QMenu(this);
    QString font="12";
   QPushButton *desktopButton= new QPushButton;
   desktopButton->setFixedSize(w*1.5, h*0.7);
   desktopButton->setIcon(QIcon(":/icons/senddesktop.svg"));
   desktopButton->setIconSize(QSize(w, h*0.6));
   desktopButton->setText(tr(" Masaüstüne"));
   desktopButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");
   desktopButton->setFlat(true);

   connect(desktopButton, &QPushButton::clicked, [=]() {

       emit startTransfer(TransferType::FileCopyDesktop);
       menu->close();
});

   QPushButton *homeButton= new QPushButton;
   homeButton->setFixedSize(w*1.5, h*0.7);
   homeButton->setIcon(QIcon(":/icons/sendhome.svg"));
   homeButton->setIconSize(QSize(w, h*0.6));
   homeButton->setText(tr("Ev Dizini"));
   homeButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");
   homeButton->setFlat(true);

   connect(homeButton, &QPushButton::clicked, [=]() {

       emit startTransfer(TransferType::FileCopyHome);
       menu->close();
});

   QPushButton *tmpButton= new QPushButton;
   tmpButton->setFixedSize(w*1.5, h*0.7);
   tmpButton->setIcon(QIcon(":/icons/sendtmp.svg"));
   tmpButton->setIconSize(QSize(w, h*0.6));
   tmpButton->setText(tr(" tmp"));
   tmpButton->setStyleSheet("Text-align:left;  font-size:"+font+"px;");
   tmpButton->setFlat(true);

   connect(tmpButton, &QPushButton::clicked, [=]() {

       emit startTransfer(TransferType::FileCopyTmp);
       menu->close();
});

   QPushButton *askButton= new QPushButton;
   askButton->setFixedSize(w*1.5, h*0.7);
   askButton->setIcon(QIcon(":/icons/sendcustom.svg"));
   askButton->setIconSize(QSize(w, h*0.6));
   askButton->setText(tr(" Özel Konum"));
   askButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");
   askButton->setFlat(true);

   connect(askButton, &QPushButton::clicked, [=]() {

      emit startTransfer(TransferType::FileCopyCustom);
       menu->close();
});

   QPushButton *scriptExecButton= new QPushButton;
   scriptExecButton->setFixedSize(w*1.5, h*0.7);
   scriptExecButton->setIcon(QIcon(":/icons/scriptexec.svg"));
   scriptExecButton->setIconSize(QSize(w, h*0.6));
   scriptExecButton->setText(tr(" Script Çalıştır"));
   scriptExecButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");
   scriptExecButton->setFlat(true);

   connect(scriptExecButton, &QPushButton::clicked, [=]() {

       emit startTransfer(TransferType::ScriptExecute);
       menu->close();
});
   QPushButton *debInstallButton= new QPushButton;
   debInstallButton->setFixedSize(w*1.5, h*0.7);
   debInstallButton->setIcon(QIcon(":/icons/debinstall.svg"));
   debInstallButton->setIconSize(QSize(w, h*0.6));
   debInstallButton->setText(tr(" Paket Kur"));
   debInstallButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");
   debInstallButton->setFlat(true);

   connect(debInstallButton, &QPushButton::clicked, [=]() {

      emit startTransfer(TransferType::DebInstall);
       menu->close();
});

    /******************************************************/

    auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
    layout->setContentsMargins(0, 0, 0,5);
    layout->setVerticalSpacing(0);
  //  layout->setColumnMinimumWidth(0, 37);
    layout->addWidget(desktopButton, 5,0,1,2);
    layout->addWidget(homeButton, 15,0,1,2);
    layout->addWidget(tmpButton, 20,0,1,2);
    layout->addWidget(askButton, 25,0,1,2);
    layout->addWidget(scriptExecButton, 30,0,1,2);
    layout->addWidget(debInstallButton, 35,0,1,2);

     // add a widget action to the context menu
    auto wa = new QWidgetAction(this);
  //  wa->setIcon(QIcon(":/icon1"));
    wa->setDefaultWidget(widget);
    menu->addAction(wa);

     menu->setStyleSheet("QMenu { width: 130 px; height: 210 px; font-size:"+font+"px;}");
   return menu;
}
