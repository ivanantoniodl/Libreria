#include "maquinarecord.h"

MaquinaRecord::MaquinaRecord(QObject *qparent,RecordBase *rparent):
MaquinaRecordBase(qparent,rparent)
{}

MaquinaRecord::MaquinaRecord(const MaquinaRecord &other):
MaquinaRecordBase(other)
{}

MaquinaRecord::~MaquinaRecord()
{}
