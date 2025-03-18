#ifndef JPMASMANAGER_H
#define JPMASMANAGER_H


#include <modbus.h>
#include <vector>


#if WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif



#ifdef J_QT_PLATFORM
#include <QObject>
#include <QList>
#include <QVector>
#include <QTime>
#include <QCoreApplication>
#endif


class JPMASManager

#ifdef J_QT_PLATFORM
    : public QObject
#endif

{
#ifdef J_QT_PLATFORM
    Q_OBJECT
#endif

private:
#define HOLDING_REG_MAX_NUM	(128)
#define MOTION_CONTROL_START_INDEX	(0)
#define MOTION_STATUS_START_INDEX	(MOTION_CONTROL_START_INDEX+64)


#define ENCODER_21BIT_MAX_VAL   (2097152.0f)
#define ENCODER_10BIT_MAX_VAL   (1024.0f)
#define MOTOR_C_REDUCTION   (1526.0f)


enum MOTION_UNIT{
    JPMAS_MOTION_UNIT_CNT = 0,
    JPMAS_MOTION_UNIT_ANG ,
    JPMAS_MOTION_UNIT_RAD ,
};


public:
    explicit JPMASManager(
            #ifdef J_QT_PLATFORM
            QObject *parent = nullptr
            #endif
            );
    ~JPMASManager();

    int init(int axesNum);

    double cnt2ang_s(int cnt,uint32_t cnt_per_round);
    double cnt2ang_u(unsigned int cnt,uint32_t cnt_per_round);

    int ang2cnt_s(double ang,uint32_t cnt_per_round);
    unsigned int ang2cnt_u(double ang,uint32_t cnt_per_round);


    enum MOTION_CONTROL_FUNC{
        JPMAS_MOTION_FUNC_HALT = 1,
        JPMAS_MOTION_FUNC_PTP	,
        JPMAS_MOTION_FUNC_RPTP	,
        JPMAS_MOTION_FUNC_VEL ,
    };

    int setAxesFunc(std::vector<int> axesList,std::vector<uint16_t> func_list);

    std::vector<uint32_t> getAxesVel_cnt(std::vector<int> axesList);
    std::vector<int32_t> getAxesAbsPos_cnt(std::vector<int> axesList);
    std::vector<uint32_t> getAxesAcc_cnt(std::vector<int> axesList);
    std::vector<uint32_t> getAxesDcc_cnt(std::vector<int> axesList);
    std::vector<int> getAxesIsMoving(std::vector<int> axesList);

    int setAxesVel_cnt(std::vector<int> axesList,std::vector<uint32_t> vel_cnt_list);
    int setAxesAbsPos_cnt(std::vector<int> axesList,std::vector<int> absPos_cnt_list);
    int setAxesAcc_cnt(std::vector<int> axesList,std::vector<uint32_t> acc_cnt_list);
    int setAxesDcc_cnt(std::vector<int> axesList,std::vector<uint32_t> dcc_cnt_list);

    int axesHalt(std::vector<int> axesList);




    int check_connect_sync();




#ifdef J_QT_PLATFORM
    int setAxesFunc(QList<int> axesList,QList<uint16_t> func_list);

    QList<uint32_t> getAxesVel_cnt(QList<int> axesList);
    QList<int32_t> getAxesAbsPos_cnt(QList<int> axesList);
    QList<uint32_t> getAxesAcc_cnt(QList<int> axesList);
    QList<uint32_t> getAxesDcc_cnt(QList<int> axesList);
    QList<int> getAxesIsMoving(QList<int> axesList);

    int setAxesVel_cnt(QList<int> axesList,QList<uint32_t> vel_cnt_list);
    int setAxesAbsPos_cnt(QList<int> axesList,QList<int> absPos_cnt_list);
    int setAxesAcc_cnt(QList<int> axesList,QList<uint32_t> acc_cnt_list);
    int setAxesDcc_cnt(QList<int> axesList,QList<uint32_t> dcc_cnt_list);

    int axesHalt(QList<int> axesList);

    void non_blocking_delay(unsigned int msec);

#endif



private:
    typedef union{
        unsigned int hex;
        unsigned int toUint32;
        signed int toSInt32;
        float toFloat32;
    }hex32bitVal;

    modbus_t* ctx = nullptr;

    uint16_t read_holdingReg[128] = {0};
    uint16_t write_holdingReg[128] = {0};

    int id = -1;

    typedef enum{

        CONTROLLER_DISCONNECT_ERROR = 10,
        VEL_VAL_TOO_BIG_ERROR,
        ACC_VAL_TOO_BIG_ERROR,
        DEC_VAL_TOO_BIG_ERROR,
        AXES_ARGS_NUM_NOT_EQUAL_ERROR,
        AXES_INPUT_NUM_ERROR,
        AXES_ABS_POS_OUT_OF_LIMIT_ERROR,

    }ERROR_TYPE_N;

    struct {
        int axesNum = 0;

        double max_vel = 0.5;
        double max_acc = 0.5;
        double max_dec = 0.5;

        double* each_axes_max_absPos = nullptr;
        double* each_axes_min_absPos = nullptr;
    }baseSetting;

#ifdef J_QT_PLATFORM
signals:
    void axesFuncSetSignal(QList<int> axesList,QList<uint16_t> func_list);
    void axesFuncSetCpltSignal(QList<int> axesList,QList<uint16_t> func_list);

    void axesVelCNTSetSignal(QList<int> axesList,QList<uint32_t> velList);
    void axesVelCNTSetCpltSignal(QList<int> axesList,QList<uint32_t> velList);
    void axesVelCNTFetchSignal(QList<int> axesList);
    void axesVelCNTFetchCpltSignal(QList<int> axesList,QList<uint32_t> velList);

    void axesAccCNTSetSignal(QList<int> axesList,QList<uint32_t> accList);
    void axesAccCNTSetCpltSignal(QList<int> axesList,QList<uint32_t> accList);
    void axesAccCNTFetchSignal(QList<int> axesList);
    void axesAccCNTFetchCpltSignal(QList<int> axesList,QList<uint32_t> accList);

    void axesDccCNTSetSignal(QList<int> axesList,QList<uint32_t> decList);
    void axesDccCNTSetCpltSignal(QList<int> axesList,QList<uint32_t> decList);
    void axesDccCNTFetchSignal(QList<int> axesList);
    void axesDccCNTFetchCpltSignal(QList<int> axesList,QList<uint32_t> decList);

    void axesIsMovingFetchSignal(QList<int> axesList);
    void axesIsMovingFetchCpltSignal(QList<int> axesList,QList<int> isMoving);

    void axesAbsPosCNTSetSignal(QList<int> axesList,QList<int> posList);
    void axesAbsPosCNTSetCpltSignal(QList<int> axesList,QList<int> posList);
    void axesAbsPosCNTFetchSignal(QList<int> axesList);
    void axesAbsPosCNTFetchCpltSignal(QList<int> axesList,QList<int> posList);

    void axesTrigglerHaltSignal(QList<int> axesList);
    void axesTrigglerHaltCpltSignal(QList<int> axesList);


    void chcekConnectSignal();
    void checkConnectCpltSignal(int isConnected);

public slots:

    void slotConnectSlot();

private slots:
    void axesFuncSetSlot(QList<int> axesList,QList<uint16_t> func_list);
    void axesVelCNTSetSlot(QList<int> axesList,QList<uint32_t> velList);
    void axesAccCNTSetSlot(QList<int> axesList,QList<uint32_t> accList);
    void axesDccCNTSetSlot(QList<int> axesList,QList<uint32_t> dccList);
    void axesAbsPosCNTSetSlot(QList<int> axesList,QList<int> posList);


    void axesVelCNTFetchSlot(QList<int> axesList);
    void axesAccCNTFetchSlot(QList<int> axesList);
    void axesDccCNTFetchSlot(QList<int> axesList);
    void axesAbsPosCNTFetchSlot(QList<int> axesList);
    void axesIsMovingFetchSlot(QList<int> axesList);

    void axesTrigglerHaltSlot(QList<int> axesList);

    void checkConnectSlot();

#endif
};

#endif // JPMASMANAGER_H
