#include "libroautorrecord.h"

LibroAutorRecord::LibroAutorRecord(QObject *qparent,RecordBase *rparent):
LibroAutorRecordBase(qparent,rparent)
{}

LibroAutorRecord::LibroAutorRecord(const LibroAutorRecord &other):
LibroAutorRecordBase(other)
{}

LibroAutorRecord::~LibroAutorRecord()
{}
