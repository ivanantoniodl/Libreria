#include "permisorecord.h"

PermisoRecord::PermisoRecord(QObject *qparent,RecordBase *rparent):
PermisoRecordBase(qparent,rparent)
{}

PermisoRecord::PermisoRecord(const PermisoRecord &other):
PermisoRecordBase(other)
{}

PermisoRecord::~PermisoRecord()
{}
