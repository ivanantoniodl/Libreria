#include "lugarrecord.h"

LugarRecord::LugarRecord(QObject *qparent,RecordBase *rparent):
LugarRecordBase(qparent,rparent)
{}

LugarRecord::LugarRecord(const LugarRecord &other):
LugarRecordBase(other)
{}

LugarRecord::~LugarRecord()
{}
