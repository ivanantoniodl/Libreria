#include "lugartiporecord.h"

LugarTipoRecord::LugarTipoRecord(QObject *qparent,RecordBase *rparent):
LugarTipoRecordBase(qparent,rparent)
{}

LugarTipoRecord::LugarTipoRecord(const LugarTipoRecord &other):
LugarTipoRecordBase(other)
{}

LugarTipoRecord::~LugarTipoRecord()
{}
