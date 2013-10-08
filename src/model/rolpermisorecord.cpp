#include "rolpermisorecord.h"

RolPermisoRecord::RolPermisoRecord(QObject *qparent,RecordBase *rparent):
RolPermisoRecordBase(qparent,rparent)
{}

RolPermisoRecord::RolPermisoRecord(const RolPermisoRecord &other):
RolPermisoRecordBase(other)
{}

RolPermisoRecord::~RolPermisoRecord()
{}
