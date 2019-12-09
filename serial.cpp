#include "serial.h"
//construtora do programa
Serial::Serial(QObject *parent) : QObject(parent)
{
    port = new QSerialPort();
    portCam = new QSerialPort();
    portFont = new QSerialPort();
    out_ = new QByteArray();

    tPressao = new QTimer();
    tFluxo = new QTimer();
    tStart = new QTimer();
    dmPressao = new QTimer();
    amPressao = new QTimer();
    dmFluxo = new QTimer();
    amFluxo = new QTimer();
    staStop = new QTimer();
    tConexao =  new QTimer();
    conexaoIns =new QTimer();
    tIntensity = new QTimer;
    tTempled = new QTimer();
    tstandby = new QTimer();
    rQStand = new QTimer();
    rQonScreen = new QTimer();
    respOnscreen = new QTimer();
    flux = new QTimer();
    press = new QTimer();
    rQplusIntensity= new QTimer();
    rQminusIntensity= new QTimer();
    envIntensity = new QTimer();
  //  cont = new QTimer();    // m_batTx = new QByteArray;
    initSerialInsufla();
    initSerialCam();
    initSerialFonte();

    connect(portCam, SIGNAL(readyRead()),this, SLOT(readBytes()));//lê os dados que chega da serial

    connect(port,SIGNAL(readyRead()),this,SLOT(readBytesCam()));

    connect(portFont,SIGNAL(readyRead()),this,SLOT(readBytesFonte()));

    connect(tPressao,&QTimer::timeout,this,&Serial::enviaPressao);

    connect(tFluxo,&QTimer::timeout,this,&Serial::enviaFluxo);

    connect(tStart,&QTimer::timeout,this,&Serial::enviaStart);

    connect(dmPressao,&QTimer::timeout,this,&Serial::dimPressao);

    connect(amPressao,&QTimer::timeout,this,&Serial::aumPressao);

    connect(dmFluxo,&QTimer::timeout,this,&Serial::dimFluxo);

    connect(amFluxo,&QTimer::timeout,this,&Serial::aumFluxo);

    connect(staStop,&QTimer::timeout,this,&Serial::startStop);

    connect(tConexao,&QTimer::timeout,this,&Serial::conexao);

    connect(conexaoIns,&QTimer::timeout,this,&Serial::conFluxun);

    connect(tIntensity,&QTimer::timeout,this,&Serial::enviaIntensity);

    connect(tTempled,&QTimer::timeout,this,&Serial::enviaTempLed);

    connect(tstandby,&QTimer::timeout,this,&Serial::enviaStandby);

    connect(rQStand,&QTimer::timeout,this,&Serial::reqStandby);

    connect(rQonScreen,&QTimer::timeout,this,&Serial::reqOnscreen);

    connect(respOnscreen,&QTimer::timeout,this,&Serial::respOnscreeen);

    connect(flux,&QTimer::timeout,this,&Serial::sendFluxo);

    connect(press,&QTimer::timeout,this,&Serial::sendPressao);

    connect(rQplusIntensity,&QTimer::timeout,this,&Serial::requestPlusIntensity);

    connect(rQminusIntensity,&QTimer::timeout,this,&Serial::requestMinusIntensity);

    connect(envIntensity,&QTimer::timeout,this,&Serial::sendIntensity);


}
//destrutora do programa obs: tudo que vc der NEW "não pode esquecer de dar delete""
Serial::~Serial()
{
    delete port;
    delete portCam;
    delete  out_;
    delete tPressao;
    delete tFluxo;
    delete tStart;
    delete dmFluxo;
    delete dmPressao;
    delete amFluxo;
    delete amPressao;
    delete tStart;
    delete tConexao;
    delete portFont;
    delete tstandby;
    delete  tTempled;
    delete tIntensity;
    delete rQonScreen;
    delete flux;
    delete press;
    delete rQplusIntensity;
    delete rQminusIntensity;
    delete envIntensity;
}
//Abre serial que receberá dados do insuflador
bool Serial::openSerialIsuflador()
{
    port->close();
    port->setPortName("ttyUSB0");
    serialInsufla = port->open(QIODevice::ReadWrite);

   if(serialInsufla)  qDebug("serial do insuflador abriu");
   else qDebug("serial do insuflador nao abriu");

   return serialInsufla;
}
//Abre serial que receberá dados da Fonte
bool Serial::openSerialFonte()
{
    portFont->close();
    portFont->setPortName("ttyUSB2");
    serialFonte = portFont->open(QIODevice::ReadWrite);

   if(serialFonte)  qDebug("serial da Fonte abriu");
   else qDebug("serial da Fonte  nao abriu");

   return serialFonte;
}
//Abre serial que receberá dados da câmera
bool Serial::openSerialCamera()
{
    portCam->close();
    portCam->setPortName("ttyUSB1");
    serialCam = portCam->open(QIODevice::ReadWrite);

   if(serialCam)qDebug("serial da camera abriu");
   else qDebug("serial da nao camera abriu");

   return serialCam;
}
//Configura a serial do insuflador
bool Serial::initSerialInsufla()
{
    if(!openSerialIsuflador()) return 0;

     port->setPortName("ttyUSB0");
     port->setBaudRate(QSerialPort::Baud1200);
     port->setDataBits(QSerialPort::Data8);
     port->setParity(QSerialPort::NoParity);
     port->setStopBits(QSerialPort::OneStop);
     port->setFlowControl(QSerialPort::NoFlowControl);

   //  qDebug("serial insufla configurado com sucesso");
     return 1;

}
//Configura a serial da câmera
bool Serial::initSerialCam()
{ if(!openSerialCamera()) return 0;

    portCam->setPortName("ttyUSB1");
    portCam->setBaudRate(QSerialPort::Baud1200);
    portCam->setDataBits(QSerialPort::Data8);
    portCam->setParity(QSerialPort::NoParity);
    portCam->setStopBits(QSerialPort::OneStop);
    portCam->setFlowControl(QSerialPort::NoFlowControl);
  //  qDebug("serial Camera configurado com sucesso");
    return 1;

}
//Configura a serial da fonte
bool Serial::initSerialFonte()
{
    if(!openSerialFonte()) return 0;

     portFont->setPortName("ttyUSB2");
     portFont->setBaudRate(QSerialPort::Baud1200);
     portFont->setDataBits(QSerialPort::Data8);
     portFont->setParity(QSerialPort::NoParity);
     portFont->setStopBits(QSerialPort::OneStop);
     portFont->setFlowControl(QSerialPort::NoFlowControl);
      //  qDebug("serial Camera configurado com sucesso");
    return 1;
}

bool Serial::isOpenInsufla()
{
    return serialInsufla;
}

bool Serial::isopenSerialCam()
{
    return serialCam;
}

bool Serial::isopenSerialFonte()
{
    return serialFonte;
}

//recebe os dados da câmera
QList<int> Serial::readBytes()
{
    int luis,usb;

    QList<int> *l = new QList<int>();
    bool error= false;
    QByteArray buf =0;


   while(portCam->waitForReadyRead(100)) // aguarda um tempo para receber a resposta
      {
          if (portCam->bytesAvailable())
          {
            // qDebug("recebemos do brasil");
             usb = 0;
              buf.append(portCam->readAll());
              for (int i=0; i<buf.size(); i++){l->append(buf.at(i));
                 luis = buf[i];
                 usbrec[i] =  buf[i];

               //  qDebug()<< luis ;
                usb++;
              }

            }
      }
   if((usbrec[0] == 0x25)&&(usbrec[1] == 0x57)&&(usb >= 6))
   {
       qDebug("conexao ok");
     switch(buf[5])
     {
       case 1: amPressao->start(50); break;
       case 2: dmPressao->start(50); break;
       case 3: amFluxo->start(50);qDebug("set flux+-"); break;
       case 4: dmFluxo->start(50);qDebug("set flux -"); break;
       case 5: tStart->start(50); break;
       case 6: tConexao->start(50);break;
       case 9: rQStand->start(50);break;
       case 10:rQonScreen->start(50);
       case 11: rQplusIntensity->start(50);break;
       case 12: rQminusIntensity->start(50);break;
     }
   }
   else qDebug("conexao bad");

   //   emit resForInsulfla();
  //  geraldao = 0;
    port->clear(QSerialPort::AllDirections);

    return *l;
}
//Recebe os dados do insuflador
QList<int> Serial::readBytesCam()
{
    int luis,i;
    QList<int> *l = new QList<int>();

    QByteArray buf =0;
//     qDebug("recebemos algo do insuflador");
   while(port->waitForReadyRead(100)) // aguarda um tempo para receber a resposta
        {
            if (port->bytesAvailable())
            {
               qDebug("recebemos dados do insuflador");
                buf.append(port->readAll());
                for (int i=0; i<buf.size(); i++){l->append(buf.at(i));
                   luis = buf[i];
                   usbrec[i] = buf[i];
                  // qDebug()<< luis ;
                }

              }
        }
    if((usbrec[0] == 0x25)&&(usbrec[1] == 0x57))
    {
         switch(usbrec[3])
         {
           case 1:{ setPressao = usbrec[5]; tPressao->start(50); /*qDebug()<< usbrec[5];*/}break;
           case 2:{setFluxo = usbrec[5]; tFluxo->start(50); /*qDebug()<< usbrec[5];*/} break;
           case 3:{start = usbrec[5]; staStop->start(50); /*qDebug()<< usbrec[5];*/} break;
           case 4:{conexaoIns->start(50);}break;
           case 5:{onScreen = usbrec[5]; respOnscreen->start(50);}break;
           case 6:{fluxo = usbrec[5]; flux->start(50);}break;
           case 7:{pressao = usbrec[5]; press->start(50);}break;
         }
     }
     for(i=0;i<=10;++i)
     {
       usbrec[i] = 0;
     }

     return *l;
}
//Recebe os dados da Fonte
QList<int> Serial::readBytesFonte()
{
    int luis,i,usb;
    QList<int> *l = new QList<int>();

    QByteArray buf =0;
     qDebug("recebemos dados da Fonte");
   while(portFont->waitForReadyRead(100)) // aguarda um tempo para receber a resposta
        {
            if (portFont->bytesAvailable())
            {
              // qDebug("recebemos algo da serial");
                buf.append(portFont->readAll());
                for (int i=0; i<buf.size(); i++){l->append(buf.at(i));
                   luis = buf[i];
                   usbrec[i] = buf[i];
                  // qDebug()<< luis ;
                   usb++;
                }

              }
        }
    if((usbrec[0] == 0x25)&&(usbrec[1] == 0x57)&&(usbrec[3] == 0x45)&&(usb >= 6))
    {
         switch(usbrec[4])
         {
           case 1:{intensity = usbrec[5]; tIntensity->start(50); qDebug("intensiti");}break;
           case 2:{tempLed = usbrec[5]; tTempled->start(50); qDebug("temperatura"); } break;
           case 3:{standby = usbrec[5]; tstandby->start(50); qDebug("standby"); } break;
           case 4:{intensity = usbrec[5]; envIntensity->start(50); qDebug("intensidade"); } break;
         }
     }
     for(i=0;i<=10;++i)
     {
       usbrec[i] = 0;
        usb = 0;
     }

     return *l;
}
/*essas rotinas pequena serão responsaveis por acionar um timer
 * para escrever nas seriais que ela serão designadas*/
void Serial::dimPressao()
{
     this->escreveserialCam(1);
}

void Serial::aumPressao()
{
     this->escreveserialCam(2);
}

void Serial::dimFluxo()
{
     this->escreveserialCam(3);
}

void Serial::aumFluxo()
{
     this->escreveserialCam(4);
}

void Serial::enviaPressao()
{
    this->escreveserialCam(5);
}

void Serial::enviaFluxo()
{
     this->escreveserialCam(6);
}

void Serial::enviaStart()
{
   this->escreveserialCam(7);
}

void Serial::startStop()
{
    this->escreveserialCam(8);
}

void Serial::conexao()
{
    this->escreveserialCam(9);
}

void Serial::conFluxun()
{
    this->escreveserialCam(10);
}

void Serial::enviaIntensity()
{
    escreveserialCam(11);
}

void Serial::enviaTempLed()
{
     escreveserialCam(12);
}

void Serial::enviaStandby()
{
    escreveserialCam(13);
}

void Serial::reqStandby()
{
    escreveserialCam(14);
}
//Envia um comando para o insuflador habilitar o onscren
void Serial::reqOnscreen()
{
    escreveserialCam(15);
}

void Serial::respOnscreeen()
{
    escreveserialCam(16);
}

void Serial::sendFluxo()
{
     escreveserialCam(17);
}

void Serial::sendPressao()
{
    escreveserialCam(18);
}

void Serial::requestPlusIntensity()
{
   escreveserialCam(19);
}

void Serial::requestMinusIntensity()
{
    escreveserialCam(20);
}

void Serial::sendIntensity()
{
   escreveserialCam(21);
}
//aquelas Rotinas de timers irão dizer quais dessas opçõees executar
void Serial::escreveserialCam(int com)
{
    QByteArray m_batTx;
    int Usb;

    if(com == 1)
    {
        dmPressao->stop();
        m_batTx[0] = 0x25; m_batTx[1] = 0x57;  m_batTx[2] = 0x06; m_batTx[3] = 0x43; m_batTx[4] = 0x44; m_batTx[5] = com;
         Usb =0;
    }

   else if(com == 2)
    {
       amPressao->stop();
        m_batTx[0] = 0x25; m_batTx[1] = 0x57;  m_batTx[2] = 0x06; m_batTx[3] = 0x43; m_batTx[4] = 0x44; m_batTx[5] = com;
         Usb =0;
    }

    else if(com == 3)
     {
        dmFluxo->stop();
         m_batTx[0] = 0x25; m_batTx[1] = 0x57;  m_batTx[2] = 0x06; m_batTx[3] = 0x43; m_batTx[4] = 0x44; m_batTx[5] = com;
         Usb =0;
     }

    else if(com == 4)
     {
        amFluxo->stop();
         m_batTx[0] = 0x25; m_batTx[1] = 0x57;  m_batTx[2] = 0x06; m_batTx[3] = 0x43; m_batTx[4] = 0x44; m_batTx[5] = com;
          Usb =0;
     }

    else if(com == 5)//envia setPressao para a câmera
     {
        tPressao->stop();
        m_batTx[0] = 0x25; m_batTx[1] = 0x57;  m_batTx[2] = 0x06; m_batTx[3] = 0x01; m_batTx[4] = 0x00; m_batTx[5] = setPressao;
         Usb =1;
    }

     else if(com == 6)//envia setFluxo para a câmera
     {
        tFluxo->stop();
        m_batTx[0] = 0x25; m_batTx[1] = 0x57;  m_batTx[2] = 0x06; m_batTx[3] = 0x02; m_batTx[4] = 0x00; m_batTx[5] = setFluxo;
         Usb =1;
     }

    else if(com == 7)
     {
        tStart->stop();
        m_batTx[0] = 0x25; m_batTx[1] = 0x57;  m_batTx[2] = 0x06; m_batTx[3] = 0x43; m_batTx[4] = 0x44; m_batTx[5] = 5;
        Usb =0;
     }

    else if(com == 8)//envia sinal de start para a câmera
     {
        staStop->stop();
        m_batTx[0] = 0x25; m_batTx[1] = 0x57;  m_batTx[2] = 0x06; m_batTx[3] = 0x03; m_batTx[4] = 0x00; m_batTx[5] = start;
        Usb =1;
    }

    else if(com == 9)//envia sinal de conexão com a camera
     {
        tConexao->stop();
        m_batTx[0] = 0x25; m_batTx[1] = 0x57;  m_batTx[2] = 0x06; m_batTx[3] = 0x04; m_batTx[4] = 0x00; m_batTx[5] = 1;
        Usb = 1;  //Usb = 1;
    }

    else if(com == 10)//envia sinal de conexão com o insuflador
     {
        conexaoIns->stop();
        m_batTx[0] = 0x25; m_batTx[1] = 0x57;  m_batTx[2] = 0x06; m_batTx[3] = 0x43; m_batTx[4] = 0x00; m_batTx[5] = 0x50;
        Usb =0;
     }

    else if(com == 11)//envia a intensidade da fonte para a câmera
     {
        tIntensity->stop();
        m_batTx[0] = 0x25; m_batTx[1] = 0x57;  m_batTx[2] = 0x06; m_batTx[3] = 0x05; m_batTx[4] = 0x00; m_batTx[5] = intensity;
        Usb =1;
     }

    else if(com == 12)//envia a temperatura da fonte para a câmera
     {
        tTempled->stop();
        m_batTx[0] = 0x25; m_batTx[1] = 0x57;  m_batTx[2] = 0x06; m_batTx[3] = 0x06; m_batTx[4] = 0x00; m_batTx[5] = tempLed;
        Usb =1;
     }

    else if(com == 13)//envia o standby da fonte para a câmera
     {
        tstandby->stop();
        m_batTx[0] = 0x25; m_batTx[1] = 0x57;  m_batTx[2] = 0x06; m_batTx[3] = 0x07; m_batTx[4] = 0x00; m_batTx[5] = standby;
        Usb =1;
     }

    else if(com == 14)//envia o standby da câmera para a fonte
     {
        rQStand->stop();
        m_batTx[0] = 0x25; m_batTx[1] = 0x57;  m_batTx[2] = 0x06; m_batTx[3] = 0x08; m_batTx[4] = 0x00; m_batTx[5] = 1;
        Usb =2;
     }

    else if(com == 15)//pede para o insuflador mandar fluxo e pressão para a câmera
     {
        rQonScreen->stop();
        m_batTx[0] = 0x25; m_batTx[1] = 0x57;  m_batTx[2] = 0x06; m_batTx[3] = 0x43; m_batTx[4] = 0x00; m_batTx[5] = 0x51;
        Usb =0;
        qDebug("pedido de autorizacao");
     }

    else if(com == 16)//envia para a câmera se esta habilitado ou não onscreen
     {
        respOnscreen->stop();
        m_batTx[0] = 0x25; m_batTx[1] = 0x57;  m_batTx[2] = 0x06; m_batTx[3] = 0x08; m_batTx[4] = 0x00; m_batTx[5] = onScreen;
        Usb =1;
        qDebug("pedido de autorizacao enviado");
     }

    else if(com == 17)//envia para a câmera o valor do fluxo
     {
        flux->stop();
        m_batTx[0] = 0x25; m_batTx[1] = 0x57;  m_batTx[2] = 0x06; m_batTx[3] = 0x09; m_batTx[4] = 0x00; m_batTx[5] = fluxo;
        Usb =1;
        qDebug("fluxo enviado");
     }
    else if(com == 18)//envia para a câmera o valor da pressao
     {
        press->stop();
        m_batTx[0] = 0x25; m_batTx[1] = 0x57;  m_batTx[2] = 0x06; m_batTx[3] = 0x0A; m_batTx[4] = 0x00; m_batTx[5] = pressao;
        Usb =1;
        qDebug("pressao enviada");
     }

    else if(com == 19)//envia a fonte aumentar a intensidade
     {
        rQplusIntensity->stop();
        m_batTx[0] = 0x25; m_batTx[1] = 0x57;  m_batTx[2] = 0x06; m_batTx[3] = 0x09; m_batTx[4] = 0x00; m_batTx[5] = 0x00;
        Usb =2;
     }

    else if(com == 20)//envia a fonte diminuir a intensidade
     {
        rQminusIntensity->stop();
        m_batTx[0] = 0x25; m_batTx[1] = 0x57;  m_batTx[2] = 0x06; m_batTx[3] = 0x0A; m_batTx[4] = 0x00; m_batTx[5] = 0x00;
        Usb =2;
     }
    else if(com == 21)//envia a fonte diminuir a intensidade
     {
        envIntensity->stop();
        m_batTx[0] = 0x25; m_batTx[1] = 0x57;  m_batTx[2] = 0x06; m_batTx[3] = 0x0B; m_batTx[4] = 0x00; m_batTx[5] = intensity;
        qDebug()<<intensity;
        Usb =1;
     }



    if(Usb == 0)//Usb do insuflador
    {
        for(int i = 0; i<= 5;++i)
        {
          m_batTx.append(m_batTx[i]);
          port->write(m_batTx);
          port->flush();
         }
    }

    else if(Usb == 1)//Usb da Câmera
    {
        for(int i = 0; i<= 5;++i)
          {
            m_batTx.append(m_batTx[i]);
            portCam->write(m_batTx);
            portCam->flush();
          }

     }

    else
    {
        for(int i = 0; i<= 5;++i)//Usb da Fonte
          {
            m_batTx.append(m_batTx[i]);
            portFont->write(m_batTx);
            portFont->flush();
          }

     }

}


