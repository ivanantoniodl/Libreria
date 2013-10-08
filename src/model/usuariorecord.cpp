#include "usuariorecord.h"

UsuarioRecord::UsuarioRecord(QObject *qparent,RecordBase *rparent):
UsuarioRecordBase(qparent,rparent)
{}

UsuarioRecord::UsuarioRecord(const UsuarioRecord &other):
UsuarioRecordBase(other)
{}

UsuarioRecord::~UsuarioRecord()
{}
