#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QtSerialPort/QSerialPortInfo>
#include <QString>
#include <QSerialPort>
#include <QIODevice>
#include <QTimer>
#include <QFile>
#include <QProcess>
#include <QDebug>
#include <QFileSystemWatcher>
#include <QTextStream>


class Serial: public QObject
{
    Q_OBJECT
public:
    explicit Serial(QObject *parent = nullptr);
    ~Serial();
    bool openSerialIsuflador(void);
    bool openSerialFonte(void);
    bool openSerialCamera(void);
    bool initSerialInsufla(void);
    bool initSerialCam(void);
    bool initSerialFonte(void);
    bool isOpenInsufla(void);
    bool isopenSerialCam(void);
    bool isopenSerialFonte(void);

    Q_INVOKABLE void escreveserialCam(int com);

public slots:
  QList<int>readBytes(void);
  QList<int>readBytesCam(void);
  QList<int>readBytesFonte(void);

  //  void resForCam(void);
 //   void resForInsulfla(void);
    void dimPressao(void);
    void aumPressao(void);
    void dimFluxo(void);
    void aumFluxo(void);
    void enviaPressao(void);
    void enviaFluxo(void);
    void enviaStart(void);
    void startStop(void);//envia para o insuflador dar o start ou stop
    void conexao(void);
    void conFluxun(void);
    void enviaIntensity(void);
    void enviaTempLed(void);
    void enviaStandby(void);
    void reqStandby(void);
    void reqOnscreen(void);
    void respOnscreeen(void);
    void sendFluxo(void);
    void sendPressao(void);
    void requestPlusIntensity(void);
    void requestMinusIntensity(void);
    void sendIntensity(void);

private :
    QSerialPort *port;
    QSerialPort *portCam;
    QSerialPort *portFont;
    QByteArray *out_;
    QTimer *cont;
    QTimer *tPressao;
    QTimer *tFluxo;
    QTimer *tStart;
    QTimer *dmPressao;
    QTimer *amPressao;
    QTimer *dmFluxo;
    QTimer *amFluxo;
    QTimer *staStop;
    QTimer *tConexao;
    QTimer *conexaoIns;
    QTimer *tIntensity, *tTempled,*tstandby;
    QTimer *rQStand;
    QTimer *rQonScreen;
    QTimer *respOnscreen;
    QTimer *flux;
    QTimer *press;
    QTimer *rQplusIntensity,*rQminusIntensity,*envIntensity;

  //  QByteArray m_batTx;
    bool serialInsufla,serialCam,serialFonte,start;
    bool geraldao,standby,onScreen;
    int pontUsb,bytesUsb,setPressao,setFluxo,intensity,tempLed,fluxo,pressao;
    int usbrec[10];
};

#endif // SERIAL_H
