#include "Dialog_Login.h"

Dialog_Login::Dialog_Login(QTcpSocket* p_Socket,QWidget *parent):
	QDialog(parent),
	ui(new Ui::Dialog_LoginClass())

{
	ui->setupUi(this);
	m_socket = p_Socket;
	//m_socket = new QTcpSocket(this);

	Dialog_init();
	Connect_init();

	Load_Setting();
}

Dialog_Login::~Dialog_Login()
{}

void Dialog_Login::Connect_init()
{
	// socket
	connect(m_socket, SIGNAL(readyRead()), this, SLOT(Server_to_client()));   // 告诉socket, 要用slot_readMessage()去处理接收的消息.

	// Setting
	connect(ui->Btn_Setting_2, SIGNAL(clicked()), this, SLOT(on_Btn_Setting_clicked()));

	// return
	connect(ui->Btn_Setting_return, SIGNAL(clicked()), this, SLOT(on_Btn_return_clicked()));

	connect(ui->Btn_quit_2, SIGNAL(clicked()), this, SLOT(on_Btn_return_clicked()));
	connect(ui->Btn_quit_3, SIGNAL(clicked()), this, SLOT(on_Btn_return_clicked()));

}
void Dialog_Login::Dialog_init()
{
	ui->stackedWidget->setCurrentIndex(PAGEINDEX_LOGIN);

	// 限制lineEdit_IP
	QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
	QRegExp ipRegex("^" + ipRange
		+ "\\." + ipRange
		+ "\\." + ipRange
		+ "\\." + ipRange + "$");
	ui->lineEdit_IP->setValidator(new QRegExpValidator(ipRegex, this));
}
void Dialog_Login::Load_Setting()
{
	QString appDir = QCoreApplication::applicationDirPath();
	QString filePath = appDir + "/Setting.ini";

	QSettings settings(filePath, QSettings::IniFormat);
	Save_IP(settings.value("Server_IP", "127.0.0.1").toString(), settings.value("Server_Port", 19999).toInt());

	ui->lineEdit_IP->setText(m_Setting.m_IP);
	ui->lineEdit_Port->setText(QString::number(m_Setting.m_Port));


}
void Dialog_Login::Save_Setting()
{
	QString appDir = QCoreApplication::applicationDirPath();
	QString filePath = appDir + "/Setting.ini";
	QSettings settings(filePath, QSettings::IniFormat);
	settings.setValue("Server_IP", ui->lineEdit_IP->text());
	settings.setValue("Server_Port", ui->lineEdit_Port->text());
	Save_IP(ui->lineEdit_IP->text(),ui->lineEdit_Port->text().toInt());
}
void Dialog_Login::Save_IP(QString IP, int Port)
{
	m_Setting.m_IP = IP;
	m_Setting.m_Port = Port;
}


void Dialog_Login::Client_to_Server(Command command)
{
	switch (command) {
	case MAIN_C_S_LOGIN: {
		Send_Login();
	}
		break;
	default:
		break;
	}
}
void Dialog_Login::Server_to_client()
{
	if (0) {
		close();
		emit ToRoom();
		return;
	}
	qDebug() << m_socket->bytesAvailable();

	MyPacket Packet;
	Packet.deserialize(m_socket->readAll());

	switch (Packet.getCommand()){
	case MAIN_S_C_LOGIN:{
		Receive_Login(Packet);
	}
		break;
	default:
		break;
	}
}

void Dialog_Login::on_Btn_ToSignup_clicked()
{
	currentIndex = ui->stackedWidget->currentIndex();
	ui->stackedWidget->setCurrentIndex(PAGEINDEX_CREATE);

}
void Dialog_Login::on_Btn_Login_clicked()
{
	Client_to_Server(MAIN_C_S_LOGIN);
}
void Dialog_Login::on_Btn_Setting_clicked()
{
	Load_Setting();
	currentIndex = ui->stackedWidget->currentIndex();
	ui->stackedWidget->setCurrentIndex(PAGEINDEX_SETTING);
}
void Dialog_Login::on_Btn_return_clicked()
{
	if (currentIndex == ui->stackedWidget->currentIndex())
		currentIndex = PAGEINDEX_LOGIN;
	ui->stackedWidget->setCurrentIndex(currentIndex);
}
void Dialog_Login::on_Btn_quit_clicked()
{
	exit(0);
}
void Dialog_Login::on_Btn_Setting_OK_clicked()
{
	Save_Setting();
	on_Btn_return_clicked();
}



void Dialog_Login::Receive_Login(MyPacket packet)
{
	// TODO 處理更複雜的登入失敗訊息
	if (packet.massageData.m_errorcode == 0) {
		m_Setting.m_User = packet.massageData.m_User;
		m_Setting.m_LoginTime = packet.massageData.m_Time;
		m_Setting.m_LoginSec = 0;
		close();
		emit ToRoom();
	}
	else
	{	
		QMessageBox::critical(nullptr, "Error", "登入失敗!");
	}
}

void Dialog_Login::Send_Login()
{
	m_socket->connectToHost(m_Setting.m_IP, m_Setting.m_Port);
	MyPacket packet;
	packet.setCommand(MAIN_C_S_LOGIN);
	packet.massageData.m_User = ui->lineEdit_User->text();
	packet.massageData.m_Pass = ui->lineEdit_Pass->text();
	packet.massageData.m_errorcode = 0;
	packet.massageData.m_Time = QDateTime::currentDateTime();
	// 將封包序列化成 QByteArray 以便發送
	QByteArray serializedPacket = packet.serialize();
	m_socket->write(serializedPacket);

}