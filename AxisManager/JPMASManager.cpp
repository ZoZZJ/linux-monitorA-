
#include "JPMASManager.h"

JPMASManager::JPMASManager(
        #ifdef J_QT_PLATFORM
            QObject *parent
        #endif
        )
#ifdef J_QT_PLATFORM
    : QObject(parent)
#endif
{

}

JPMASManager::~JPMASManager()
{
    if(ctx)
    {
        modbus_close(ctx);
        modbus_free(ctx);
        ctx = nullptr;
//        qDebug("delete");
    }
}

int JPMASManager::init(int axesNum)
{
    baseSetting.axesNum = axesNum;

    if(ctx)
    {
        modbus_close(ctx);
        modbus_free(ctx);
        ctx = nullptr;
    }
    ctx = modbus_new_tcp("192.168.1.3",502);
//    ctx = modbus_new_tcp("127.0.0.1",502);

//    modbus_set_debug(ctx,true);

    modbus_set_response_timeout(ctx, 0, 1000 * 100);

    modbus_set_slave(ctx,1);

    int ret_ = modbus_connect(ctx);

    int read_num_ = modbus_read_registers(ctx,MOTION_CONTROL_START_INDEX,64,read_holdingReg);

    if(read_num_ > 0)
    {
        for(int i=0;i<10;i++)
        {
            //qDebug(" r %x ",read_holdingReg[i]);
        }
    }
    if(ret_==-1)
    {
        modbus_close(ctx);
        modbus_free(ctx);
        ctx = nullptr;
    }

    return ret_ != -1;
}

double JPMASManager::cnt2ang_s(int cnt,uint32_t cnt_per_round)
{
    return (  cnt / cnt_per_round * 360.0  );
}
double JPMASManager::cnt2ang_u(unsigned int cnt,uint32_t cnt_per_round)
{
    return (  cnt / cnt_per_round * 360.0  );
}

int JPMASManager::ang2cnt_s(double ang,uint32_t cnt_per_round)
{
    return (  ang / 360.0 * cnt_per_round );
}
unsigned int JPMASManager::ang2cnt_u(double ang,uint32_t cnt_per_round)
{
    return (  ang / 360.0 * cnt_per_round );
}


int JPMASManager::setAxesFunc(std::vector<int> axesList,std::vector<uint16_t> func_list)
{
    for(int axid:axesList)
    {
        if(axid >= baseSetting.axesNum || axid < 0)
        {
            return -1;
        }
    }
    if(axesList.size()<=0 || !ctx)
        return -1;
    if(axesList.size()!=func_list.size())
        return -1;

    int ret_cnt_ = 0;
    for(int i=0;i<axesList.size();i++)
    {
        ret_cnt_ += modbus_write_register(ctx,MOTION_CONTROL_START_INDEX + axesList.at(i) * 10,func_list.at(i));

    }
#ifdef J_QT_PLATFORM
    if(ret_cnt_ > 0)
    {
        QList<int> qaxesl;
        QList<uint16_t> qfuncl;
        for(int el:axesList)
            qaxesl.append(el);
        for(uint16_t el:func_list)
            qfuncl.append(el);
        emit axesFuncSetCpltSignal(qaxesl,qfuncl);
    }
#endif

    return ret_cnt_;
}


std::vector<uint32_t> JPMASManager::getAxesVel_cnt(std::vector<int> axesList)
{
    std::vector<uint32_t> resultset;
    for(int axid:axesList)
    {
        if(axid >= baseSetting.axesNum || axid < 0)
        {
            return resultset;
        }
    }
    if(axesList.size()<=0)
    {
        return resultset;
    }
    if(ctx)
    {

        uint16_t read_buffer_[64] = {0};
        int read_num_ = modbus_read_registers(ctx,MOTION_CONTROL_START_INDEX,64,read_buffer_);

        if(read_num_!=-1)
        {
            for(int i=0;i<axesList.size();i++)
            {
                uint16_t r1,r2;
                r1 = read_buffer_[axesList.at(i) * 10 + 3];
                r2 = read_buffer_[axesList.at(i) * 10 + 4];
                uint32_t vel_cnt_ = ((uint32_t)r2 << 16 & 0xffff0000) |  ( (uint32_t)r1 & 0x0000ffff);
                resultset.push_back(vel_cnt_);
            }
#ifdef J_QT_PLATFORM
            QList<int> qaxesl;
            QList<uint32_t> qvell;
            for(int el:axesList)
                qaxesl.append(el);
            for(uint32_t el:resultset)
                qvell.append(el);
            emit axesVelCNTFetchCpltSignal(qaxesl,qvell);
#endif
        }
    }
    return resultset;
}
std::vector<int32_t> JPMASManager::getAxesAbsPos_cnt(std::vector<int> axesList)
{
    std::vector<int32_t> resultset;
    for(int axid:axesList)
    {
        if(axid >= baseSetting.axesNum || axid < 0)
        {
            return resultset;
        }
    }
    if(axesList.size()<=0)
    {
        return resultset;
    }
    if(ctx)
    {

        uint16_t read_buffer_[64] = {0};
        int read_num_ = modbus_read_registers(ctx,MOTION_STATUS_START_INDEX,64,read_buffer_);

        if(read_num_!=-1)
        {
            for(int i=0;i<axesList.size();i++)
            {
                uint16_t r1,r2;
                r1 = read_buffer_[axesList.at(i) * 6 + 2];
                r2 = read_buffer_[axesList.at(i) * 6 + 3];
                int32_t apos_cnt_ = ((int32_t)r2 << 16 & 0xffff0000) |  ( (int32_t)r1 & 0x0000ffff);
                resultset.push_back(apos_cnt_);
            }
#ifdef J_QT_PLATFORM
            QList<int> qaxesl;
            QList<int32_t> qabsposl;
            for(int el:axesList)
                qaxesl.append(el);
            for(uint32_t el:resultset)
                qabsposl.append(el);
            emit axesAbsPosCNTFetchCpltSignal(qaxesl,qabsposl);
#endif
        }
    }
    return resultset;
}
std::vector<uint32_t> JPMASManager::getAxesAcc_cnt(std::vector<int> axesList)
{
    std::vector<uint32_t> resultset;
    for(int axid:axesList)
    {
        if(axid >= baseSetting.axesNum || axid < 0)
        {
            return resultset;
        }
    }
    if(axesList.size()<=0)
    {
        return resultset;
    }
    if(ctx)
    {

        uint16_t read_buffer_[64] = {0};
        int read_num_ = modbus_read_registers(ctx,MOTION_CONTROL_START_INDEX,64,read_buffer_);

        if(read_num_!=-1)
        {
            for(int i=0;i<axesList.size();i++)
            {
                uint16_t r1,r2;
                r1 = read_buffer_[axesList.at(i) * 10 + 5];
                r2 = read_buffer_[axesList.at(i) * 10 + 6];
                uint32_t acc_cnt_ = ((uint32_t)r2 << 16 & 0xffff0000) |  ( (uint32_t)r1 & 0x0000ffff);
                resultset.push_back(acc_cnt_);
            }
#ifdef J_QT_PLATFORM
            QList<int> qaxesl;
            QList<uint32_t> qaccl;
            for(int el:axesList)
                qaxesl.append(el);
            for(uint32_t el:resultset)
                qaccl.append(el);
            emit axesAccCNTFetchCpltSignal(qaxesl,qaccl);
#endif
        }
    }
    return resultset;
}
std::vector<uint32_t> JPMASManager::getAxesDcc_cnt(std::vector<int> axesList)
{
    std::vector<uint32_t> resultset;
    for(int axid:axesList)
    {
        if(axid >= baseSetting.axesNum || axid < 0)
        {
            return resultset;
        }
    }
    if(axesList.size()<=0)
    {
        return resultset;
    }
    if(ctx)
    {

        uint16_t read_buffer_[64] = {0};
        int read_num_ = modbus_read_registers(ctx,MOTION_CONTROL_START_INDEX,64,read_buffer_);

        if(read_num_!=-1)
        {
            for(int i=0;i<axesList.size();i++)
            {
                uint16_t r1,r2;
                r1 = read_buffer_[axesList.at(i) * 10 + 7];
                r2 = read_buffer_[axesList.at(i) * 10 + 8];
                uint32_t dcc_cnt_ = ((uint32_t)r2 << 16 & 0xffff0000) |  ( (uint32_t)r1 & 0x0000ffff);
                resultset.push_back(dcc_cnt_);
            }
#ifdef J_QT_PLATFORM
            QList<int> qaxesl;
            QList<uint32_t> qdccl;
            for(int el:axesList)
                qaxesl.append(el);
            for(uint32_t el:resultset)
                qdccl.append(el);
            emit axesDccCNTFetchCpltSignal(qaxesl,qdccl);
#endif
        }
    }
    return resultset;
}

std::vector<int> JPMASManager::getAxesIsMoving(std::vector<int> axesList)
{
    std::vector<int> resultset;
    for(int axid:axesList)
    {
        if(axid >= baseSetting.axesNum || axid < 0)
        {
            return resultset;
        }
    }
    if(axesList.size()<=0)
    {
        return resultset;
    }
    if(ctx)
    {
        uint16_t read_buffer_[64] = {0};
        int read_num_ = modbus_read_registers(ctx,MOTION_STATUS_START_INDEX,64,read_buffer_);

        if(read_num_ != -1)
        {
            for(int i=0;i<axesList.size();i++)
            {
                uint16_t r1,r2;
                r1 = read_buffer_[axesList.at(i) * 6 + 0];
                r2 = read_buffer_[axesList.at(i) * 6 + 1];
                resultset.push_back(r1 != 128);
            }
#ifdef J_QT_PLATFORM
            QList<int> qaxesl;
            QList<int> qismoving;
            for(int el:axesList)
                qaxesl.append(el);
            for(int el:resultset)
                qismoving.append(el);
            emit axesIsMovingFetchCpltSignal(qaxesl,qismoving);
#endif
        }
    }
    return resultset;
}


int JPMASManager::setAxesVel_cnt(std::vector<int> axesList,std::vector<uint32_t> vel_cnt_list)
{
    for(int axid:axesList)
    {
        if(axid >= baseSetting.axesNum || axid < 0)
        {
            return -1;
        }
    }
    if(axesList.size()<=0 || !ctx)
        return -1;
    if(axesList.size()!=vel_cnt_list.size())
        return -1;

    int ret_cnt_ = 0;
    for(int i=0;i<axesList.size();i++)
    {
        uint32_t thisVel_cnt = vel_cnt_list.at(i);
        int thisAxis = axesList.at(i);

        uint16_t r12[2] = {0};
        r12[0] = (uint16_t)thisVel_cnt;
        r12[1] = (uint16_t)(thisVel_cnt>>16);
        ret_cnt_ += modbus_write_registers(ctx,MOTION_CONTROL_START_INDEX + thisAxis * 10 + 3,2,r12);
    }
#ifdef J_QT_PLATFORM
    if(ret_cnt_ > 0)
    {
        QList<int> qaxesl;
        QList<uint32_t> qvell;
        for(int el:axesList)
            qaxesl.append(el);
        for(uint32_t el:vel_cnt_list)
            qvell.append(el);
        emit axesVelCNTSetCpltSignal(qaxesl,qvell);
    }
#endif
    return ret_cnt_;
}
int JPMASManager::setAxesAbsPos_cnt(std::vector<int> axesList,std::vector<int> absPos_cnt_list)
{
    for(int axid:axesList)
    {
        if(axid >= baseSetting.axesNum || axid < 0)
        {
            return -1;
        }
    }
    if(axesList.size()<=0 || !ctx)
        return -1;
    if(axesList.size()!=absPos_cnt_list.size())
        return -1;

    int ret_cnt_ = 0;
    for(int i=0;i<axesList.size();i++)
    {
        int32_t thisVel_cnt = absPos_cnt_list.at(i);
        int thisAxis = axesList.at(i);

        uint16_t r12[2] = {0};
        r12[0] = (uint16_t)thisVel_cnt;
        r12[1] = (uint16_t)(thisVel_cnt>>16);
        ret_cnt_ += modbus_write_registers(ctx,MOTION_CONTROL_START_INDEX + thisAxis * 10 + 1,2,r12);

        ret_cnt_ += modbus_write_register(ctx,MOTION_CONTROL_START_INDEX + thisAxis * 10 + 0 , 2);
    }
#ifdef J_QT_PLATFORM
    if(ret_cnt_ > 0)
    {
        QList<int> qaxesl;
        QList<int32_t> qabsposl;
        for(int el:axesList)
            qaxesl.append(el);
        for(int32_t el:absPos_cnt_list)
            qabsposl.append(el);
        emit axesAbsPosCNTSetCpltSignal(qaxesl,qabsposl);
    }
#endif
    return ret_cnt_;
}
int JPMASManager::setAxesAcc_cnt(std::vector<int> axesList,std::vector<uint32_t> acc_cnt_list)
{
    for(int axid:axesList)
    {
        if(axid >= baseSetting.axesNum || axid < 0)
        {
            return -1;
        }
    }
    if(axesList.size()<=0 || !ctx)
        return -1;
    if(axesList.size()!=acc_cnt_list.size())
        return -1;

    int ret_cnt_ = 0;
    for(int i=0;i<axesList.size();i++)
    {
        uint32_t thisVel_cnt = acc_cnt_list.at(i);
        int thisAxis = axesList.at(i);

        uint16_t r12[2] = {0};
        r12[0] = (uint16_t)thisVel_cnt;
        r12[1] = (uint16_t)(thisVel_cnt>>16);
        ret_cnt_ += modbus_write_registers(ctx,MOTION_CONTROL_START_INDEX + thisAxis * 10 + 5,2,r12);
    }
#ifdef J_QT_PLATFORM
    if(ret_cnt_ > 0)
    {
        QList<int> qaxesl;
        QList<uint32_t> qaccl;
        for(int el:axesList)
            qaxesl.append(el);
        for(uint32_t el:acc_cnt_list)
            qaccl.append(el);
        emit axesAccCNTSetCpltSignal(qaxesl,qaccl);
    }
#endif
    return ret_cnt_;
}
int JPMASManager::setAxesDcc_cnt(std::vector<int> axesList,std::vector<uint32_t> dcc_cnt_list)
{
    for(int axid:axesList)
    {
        if(axid >= baseSetting.axesNum || axid < 0)
        {
            return -1;
        }
    }
    if(axesList.size()<=0 || !ctx)
        return -1;
    if(axesList.size()!=dcc_cnt_list.size())
        return -1;

    int ret_cnt_ = 0;
    for(int i=0;i<axesList.size();i++)
    {
        uint32_t thisVel_cnt = dcc_cnt_list.at(i);
        int thisAxis = axesList.at(i);

        uint16_t r12[2] = {0};
        r12[0] = (uint16_t)thisVel_cnt;
        r12[1] = (uint16_t)(thisVel_cnt>>16);
        ret_cnt_ += modbus_write_registers(ctx,MOTION_CONTROL_START_INDEX + thisAxis * 10 + 7,2,r12);
    }
#ifdef J_QT_PLATFORM
    if(ret_cnt_ > 0)
    {
        QList<int> qaxesl;
        QList<uint32_t> qdccl;
        for(int el:axesList)
            qaxesl.append(el);
        for(uint32_t el:dcc_cnt_list)
            qdccl.append(el);
        emit axesDccCNTSetCpltSignal(qaxesl,qdccl);
    }
#endif
    return ret_cnt_;

}

int JPMASManager::axesHalt(std::vector<int> axesList)
{
    std::vector<uint16_t> halt_func_list;
    for(int i=0;i<axesList.size();i++)
    {
        halt_func_list.push_back(JPMASManager::JPMAS_MOTION_FUNC_HALT);
    }
    int ret_ = setAxesFunc(axesList,halt_func_list);
#ifdef J_QT_PLATFORM
    QList<int> qaxesl;
    for(int el:axesList)
        qaxesl.append(el);
    emit axesTrigglerHaltCpltSignal(qaxesl);
#endif
    return ret_;
}


int JPMASManager::check_connect_sync()
{
    if(!ctx)
        return 0;

    modbus_write_register(ctx,63,1);
#ifdef J_QT_PLATFORM
    non_blocking_delay(10);
#elif WIN32
    Sleep(10);
#else
    usleep(1000 * 10);
#endif
    uint16_t res_=100;
    modbus_read_registers(ctx,63,1,&res_);

#ifdef J_QT_PLATFORM
    emit checkConnectCpltSignal(res_ == 0);
#endif
    return res_ == 0;

}

#ifdef J_QT_PLATFORM
int JPMASManager::setAxesFunc(QList<int> axesList,QList<uint16_t> func_list)
{
    return setAxesFunc(axesList.toVector().toStdVector(),func_list.toVector().toStdVector());
}

QList<uint32_t> JPMASManager::getAxesVel_cnt(QList<int> axesList)
{
    std::vector<uint32_t> cnt_v = getAxesVel_cnt(axesList.toVector().toStdVector() );
    return QList<uint32_t>::fromVector(  QVector<uint32_t>::fromStdVector(cnt_v)  );
}
QList<int32_t> JPMASManager::getAxesAbsPos_cnt(QList<int> axesList)
{
    std::vector<int32_t> cnt_v = getAxesAbsPos_cnt(axesList.toVector().toStdVector());
    return QList<int32_t>::fromVector(  QVector<int32_t>::fromStdVector(cnt_v)  );
}
QList<uint32_t> JPMASManager::getAxesAcc_cnt(QList<int> axesList)
{
    std::vector<uint32_t> cnt_v = getAxesAcc_cnt(axesList.toVector().toStdVector());
    return QList<uint32_t>::fromVector(  QVector<uint32_t>::fromStdVector(cnt_v)  );
}
QList<uint32_t> JPMASManager::getAxesDcc_cnt(QList<int> axesList)
{
    std::vector<uint32_t> cnt_v = getAxesDcc_cnt(axesList.toVector().toStdVector());
    return QList<uint32_t>::fromVector(  QVector<uint32_t>::fromStdVector(cnt_v)  );
}

QList<int> JPMASManager::getAxesIsMoving(QList<int> axesList)
{
    std::vector<int> ismoving = getAxesIsMoving(axesList.toVector().toStdVector());
    return  QList<int>::fromVector( QVector<int>::fromStdVector(ismoving));
}

int JPMASManager::setAxesVel_cnt(QList<int> axesList,QList<uint32_t> vel_cnt_list)
{
    return setAxesVel_cnt(  axesList.toVector().toStdVector(),vel_cnt_list.toVector().toStdVector()   );
}
int JPMASManager::setAxesAbsPos_cnt(QList<int> axesList,QList<int> absPos_cnt_list)
{
    return setAxesAbsPos_cnt(axesList.toVector().toStdVector() , absPos_cnt_list.toVector().toStdVector());
}
int JPMASManager::setAxesAcc_cnt(QList<int> axesList,QList<uint32_t> acc_cnt_list)
{
    return setAxesAcc_cnt(axesList.toVector().toStdVector() , acc_cnt_list.toVector().toStdVector());
}
int JPMASManager::setAxesDcc_cnt(QList<int> axesList,QList<uint32_t> dcc_cnt_list)
{
    return setAxesDcc_cnt(axesList.toVector().toStdVector(),dcc_cnt_list.toVector().toStdVector());
}

int JPMASManager::axesHalt(QList<int> axesList)
{
    return axesHalt(axesList.toVector().toStdVector());
}

void JPMASManager::non_blocking_delay(unsigned int msec)
{
    QTime _Timer = QTime::currentTime().addMSecs(msec);

    while( QTime::currentTime() < _Timer )

        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

}



void JPMASManager::slotConnectSlot()
{
    connect(this,&JPMASManager::axesVelCNTSetSignal,this,&JPMASManager::axesVelCNTSetSlot);
    connect(this,&JPMASManager::axesAccCNTSetSignal,this,&JPMASManager::axesAccCNTSetSlot);
    connect(this,&JPMASManager::axesDccCNTSetSignal,this,&JPMASManager::axesDccCNTSetSlot);
    connect(this,&JPMASManager::axesAbsPosCNTSetSignal,this,&JPMASManager::axesAbsPosCNTSetSlot);

    connect(this,&JPMASManager::axesVelCNTFetchSignal,this,&JPMASManager::axesVelCNTFetchSlot);
    connect(this,&JPMASManager::axesAccCNTFetchSignal,this,&JPMASManager::axesAccCNTFetchSlot);
    connect(this,&JPMASManager::axesDccCNTFetchSignal,this,&JPMASManager::axesDccCNTFetchSlot);
    connect(this,&JPMASManager::axesAbsPosCNTFetchSignal,this,&JPMASManager::axesAbsPosCNTFetchSlot);
    connect(this,&JPMASManager::axesIsMovingFetchSignal,this,&JPMASManager::axesIsMovingFetchSlot);

    connect(this,&JPMASManager::axesTrigglerHaltSignal,this,&JPMASManager::axesTrigglerHaltSlot);


    connect(this,&JPMASManager::chcekConnectSignal,this,&JPMASManager::checkConnectSlot);
}

void JPMASManager::axesFuncSetSlot(QList<int> axesList,QList<uint16_t> func_list)
{
    this->setAxesFunc(axesList,func_list);
}
void JPMASManager::axesVelCNTSetSlot(QList<int> axesList,QList<uint32_t> velList)
{
    this->setAxesVel_cnt(axesList,velList);
}
void JPMASManager::axesAccCNTSetSlot(QList<int> axesList,QList<uint32_t> accList)
{
    this->setAxesAcc_cnt(axesList,accList);
}
void JPMASManager::axesDccCNTSetSlot(QList<int> axesList,QList<uint32_t> dccList)
{
    this->setAxesDcc_cnt(axesList,dccList);
}
void JPMASManager::axesAbsPosCNTSetSlot(QList<int> axesList,QList<int> posList)
{
    this->setAxesAbsPos_cnt(axesList,posList);
}

void JPMASManager::axesVelCNTFetchSlot(QList<int> axesList)
{
    this->getAxesVel_cnt(axesList);
}
void JPMASManager::axesAccCNTFetchSlot(QList<int> axesList)
{
    this->getAxesAcc_cnt(axesList);
}
void JPMASManager::axesDccCNTFetchSlot(QList<int> axesList)
{
    this->getAxesDcc_cnt(axesList);
}
void JPMASManager::axesAbsPosCNTFetchSlot(QList<int> axesList)
{
    this->getAxesAbsPos_cnt(axesList);
}
void JPMASManager::axesIsMovingFetchSlot(QList<int> axesList)
{
    this->getAxesIsMoving(axesList);
}
void JPMASManager::axesTrigglerHaltSlot(QList<int> axesList)
{
    this->axesHalt(axesList);
}
void JPMASManager::checkConnectSlot()
{
    this->check_connect_sync();
}

#endif
