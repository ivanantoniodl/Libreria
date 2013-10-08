#include "usuariocargorecord.h"

UsuarioCargoRecord::UsuarioCargoRecord(QObject *qparent,RecordBase *rparent):
UsuarioCargoRecordBase(qparent,rparent)
{}

UsuarioCargoRecord::UsuarioCargoRecord(const UsuarioCargoRecord &other):
UsuarioCargoRecordBase(other)
{}

UsuarioCargoRecord::~UsuarioCargoRecord()
{}
