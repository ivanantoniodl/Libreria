#include "empresarecord.h"

EmpresaRecord::EmpresaRecord(QObject *qparent,RecordBase *rparent):
EmpresaRecordBase(qparent,rparent)
{}

EmpresaRecord::EmpresaRecord(const EmpresaRecord &other):
EmpresaRecordBase(other)
{}

EmpresaRecord::~EmpresaRecord()
{}
