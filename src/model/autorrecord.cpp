#include "autorrecord.h"

AutorRecord::AutorRecord(QObject *qparent,RecordBase *rparent):
AutorRecordBase(qparent,rparent)
{}

AutorRecord::AutorRecord(const AutorRecord &other):
AutorRecordBase(other)
{}

AutorRecord::~AutorRecord()
{}
