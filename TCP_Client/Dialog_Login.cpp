#include "Dialog_Login.h"

Dialog_Login::Dialog_Login(QTcpSocket* p_Socket,QWidget *parent):
	QDialog(parent),
	ui(new Ui::Dialog_LoginClass())

{
	ui->setupUi(this);
	raise();
	m_socket = p_Socket;

	Dialog_init();
	Connect_init();

	Load_Setting();


}

Dialog_Login::~Dialog_Login()
{}

void Dialog_Login::Connect_init()
{
	// socket
	connect(m_socket, SIGNAL(readyRead()), this, SLOT(Server_to_Client())); 

	// Setting
	connect(ui->Btn_Setting_2, SIGNAL(clicked()), this, SLOT(on_Btn_Setting_clicked()));

	// return
	connect(ui->Btn_Setting_return, SIGNAL(clicked()), this, SLOT(on_Btn_return_clicked()));

	connect(ui->Btn_quit_2, SIGNAL(clicked()), this, SLOT(on_Btn_return_clicked()));
	connect(ui->Btn_quit_3, SIGNAL(clicked()), this, SLOT(on_Btn_return_clicked()));

}
void Dialog_Login::Dialog_init()
{
	m_timer = new QTimer(this);
	connect(m_timer, &QTimer::timeout, this, [=]() {
		m_timer->stop();
		logining_Dialog->cancel();
		QMessageBox::information(nullptr, "連線失敗", "無法取得連線");
		});

	ui->stackedWidget->setCurrentIndex(PAGEINDEX_LOGIN);

	// 限制lineEdit_IP
	QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
	QRegExp ipRegex("^" + ipRange
		+ "\\." + ipRange
		+ "\\." + ipRange
		+ "\\." + ipRange + "$");
	ui->lineEdit_IP->setValidator(new QRegExpValidator(ipRegex, this));
	ui->Btn_Findpass->hide();

}
void Dialog_Login::Load_Setting()
{

	QString appDir = QCoreApplication::applicationDirPath();
	QString filePath = appDir + "/Setting.ini";

	QSettings settings(filePath, QSettings::IniFormat);
	Save_IP(settings.value("Server_IP", "127.0.0.1").toString(), settings.value("Server_Port", 19999).toInt());
	ui->lineEdit_Account->setText(settings.value("Saving_Account", "").toString());
	if (settings.value("Saving_Account", "").toString() != "")
		ui->CB_Keeppass->setCheckState(Qt::Checked);
	ui->lineEdit_IP->setText(m_Setting.m_IP);
	ui->lineEdit_Port->setText(QString::number(m_Setting.m_Port));
	m_Setting.SetVersion();
}
void Dialog_Login::Save_Setting(QString Account)
{
	QString appDir = QCoreApplication::applicationDirPath();
	QString filePath = appDir + "/Setting.ini";
	QSettings settings(filePath, QSettings::IniFormat);
	settings.setValue("Server_IP", ui->lineEdit_IP->text());
	settings.setValue("Server_Port", ui->lineEdit_Port->text());
	settings.setValue("Version", m_Setting.Version);

	if (ui->CB_Keeppass->checkState() == Qt::Checked)
		settings.setValue("Saving_Account", Account);
	else
		settings.setValue("Saving_Account", "");

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
		Send_Login(ui->lineEdit_Account->text(), ui->lineEdit_Pass->text());
	}
		break;
	case MAIN_C_S_SINGUP: {
		Send_SignUp(ui->LE_Signup_name->text(), ui->LE_Signup_pass->text());
	}
		break;
	default:
		break;
	}
}
void Dialog_Login::Server_to_Client()
{
	// @解密
	MyPacket Packet(Common::Encryption_byXOR(m_socket->readAll(), XOR_KEY));

	switch (Packet.getCommand()){
	case MAIN_S_C_LOGIN:{
		Receive_Login(Packet);
		break;
	}
	case MAIN_S_C_SINGUP: {
		Receive_SignUp(Packet);
		break;
	}
	//case MAIN_S_C_PAUSE: {
	//	QMessageBox::critical(nullptr, "錯誤", "伺服器暫停中");
	//	break;
	//}
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
	if (ui->lineEdit_Account->text() == "") {
		QMessageBox::critical(nullptr, "登入失敗", "未輸入帳號");
		return;
	}
	if (ui->lineEdit_Pass->text() == "") {
		QMessageBox::critical(nullptr, "登入失敗", "未輸入密碼");
		return;
	}
	Client_to_Server(MAIN_C_S_LOGIN);
}
void Dialog_Login::on_Btn_Signup_clicked()
{
	if (ui->LE_Signup_name->text() == "") {
		QMessageBox::critical(nullptr, "創建失敗", "未輸入帳號");
		return;
	}
	if (ui->LE_Signup_pass->text() == "" ||
		ui->LE_Signup_pass_double->text() == "") {
		QMessageBox::critical(nullptr, "創建失敗", "未輸入密碼");
		return;
	}
	if (ui->LE_Signup_pass->text() != ui->LE_Signup_pass_double->text()) {
		QMessageBox::critical(nullptr, "創建失敗", "兩次輸入密碼不相同");
		return;
	}
	Client_to_Server(MAIN_C_S_SINGUP);
}
void Dialog_Login::on_Btn_Setting_clicked()
{
	Load_Setting();
	currentIndex = ui->stackedWidget->currentIndex();
	ui->stackedWidget->setCurrentIndex(PAGEINDEX_SETTING);
}
void Dialog_Login::on_Btn_return_clicked()
{
	if (currentIndex == PAGEINDEX_SETTING)
	{
		ui->LE_Signup_name->setText("");
		ui->LE_Signup_pass->setText("");
		ui->LE_Signup_pass_double->setText("");
	}
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


void Dialog_Login::Send_Login(QString Account, QString Pass)
{

	m_socket->connectToHost(m_Setting.m_IP, m_Setting.m_Port);
	m_timer->start(5000);
	logining_Dialog = new QProgressDialog("連線中...", "取消", 0, 0, this);
	//logining_Dialog->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
	logining_Dialog->setWindowModality(Qt::WindowModal);
	logining_Dialog->setMinimumDuration(0);

	connect(logining_Dialog, &QProgressDialog::canceled, this, [=]() {
		m_timer->stop();
		logining_Dialog->cancel();
		});

	logining_Dialog->show();

	MassageData p_massagedata;
	p_massagedata.m_Account = Account;
	p_massagedata.m_Data["Pass"] = Pass;
	p_massagedata.m_errorcode = Errorcode_OK;
	p_massagedata.m_Time = QDateTime::currentDateTime();

	auto head = Packet_head(m_Setting.Version, "MAIN_C_S_LOGIN");
	auto body = Packet_body(MAIN_C_S_LOGIN, p_massagedata);
	MyPacket receivedPacket(head, body);
	QByteArray Bytes = receivedPacket.toQByteArray();
	m_socket->write(Common::Encryption_byXOR(Bytes, XOR_KEY));
}
void Dialog_Login::Send_SignUp(QString Account, QString Pass)
{

	m_socket->connectToHost(m_Setting.m_IP, m_Setting.m_Port);
	MassageData p_massagedata;
	p_massagedata.m_Account = Account;
	p_massagedata.m_Data["Pass"] = Pass;
	p_massagedata.m_errorcode = Errorcode_OK;
	p_massagedata.m_Time = QDateTime::currentDateTime();

	auto head = Packet_head(m_Setting.Version, "MAIN_C_S_SINGUP");
	auto body = Packet_body(MAIN_C_S_SINGUP, p_massagedata);
	MyPacket receivedPacket(head, body);
	QByteArray Bytes = receivedPacket.toQByteArray();
	m_socket->write(Common::Encryption_byXOR(Bytes, XOR_KEY));
}

void Dialog_Login::Receive_Login(MyPacket packet)
{
	m_timer->stop();
	logining_Dialog->cancel();

	switch (packet.body.massageData.m_errorcode)
	{
	case Errorcode_OK:
	{
		Local_User.m_Account = packet.body.massageData.m_Account;
		m_Setting.m_LoginTime = packet.body.massageData.m_Time;
		m_Setting.m_LoginSec = 0;
		Save_Setting(ui->lineEdit_Account->text());
		disconnect(m_socket, SIGNAL(readyRead()), this, SLOT(Server_to_Client()));
		emit ToRoom();
	}
		break;
	case Errorcode_ACCOUNT_NOTEXIST:
	{
		QMessageBox::critical(nullptr, "登入失敗", "帳號不存在");
	}
		break;
	case Errorcode_PASSWORD_ERROR:
	{
		QMessageBox::critical(nullptr, "登入失敗", "密碼錯誤");
	}
		break;
	case Errorcode_REPEAT_LOGIN:
	{
		QMessageBox::critical(nullptr, "登入失敗", "已經登入");
	}
		break;
	default:
		QMessageBox::critical(nullptr, "登入失敗", "登入失敗");
		break;
	}
}
void Dialog_Login::Receive_SignUp(MyPacket packet)
{
	switch (packet.body.massageData.m_errorcode)
	{
	case Errorcode_OK:
	{
		QMessageBox::information(nullptr, "創建成功", "帳號創造成功");
		on_Btn_return_clicked();
	}
		break;
	case Errorcode_ACCOUNT_EXIST:
	{
		QMessageBox::critical(nullptr, "創建失敗", "帳號已存在");
	}
		break;
	default:
		QMessageBox::critical(nullptr, "創建失敗", "創建失敗");
		break;
	}
}

void Dialog_Login::on_CB_Showpass_stateChanged(int arg1)
{
	switch (arg1) {
	case Qt::Unchecked:
		ui->lineEdit_Pass->setEchoMode(QLineEdit::Password);
		break;
	case Qt::PartiallyChecked:
		ui->lineEdit_Pass->setEchoMode(QLineEdit::Normal);
		break;
	case Qt::Checked:
		ui->lineEdit_Pass->setEchoMode(QLineEdit::Normal);
		break;
	default:
		break;
	}
}
void Dialog_Login::on_CB_Keeppass_stateChanged(int arg1)
{

}

