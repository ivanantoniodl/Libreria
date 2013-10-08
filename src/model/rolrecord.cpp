#include "rolrecord.h"

RolRecord::RolRecord(QObject *qparent,RecordBase *rparent):
RolRecordBase(qparent,rparent)
{}

RolRecord::RolRecord(const RolRecord &other):
RolRecordBase(other)
{}

RolRecord::~RolRecord()
{}
