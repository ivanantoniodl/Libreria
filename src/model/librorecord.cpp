#include "librorecord.h"

LibroRecord::LibroRecord(QObject *qparent,RecordBase *rparent):
LibroRecordBase(qparent,rparent)
{}

LibroRecord::LibroRecord(const LibroRecord &other):
LibroRecordBase(other)
{}

LibroRecord::~LibroRecord()
{}
