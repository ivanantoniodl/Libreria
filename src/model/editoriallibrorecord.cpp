#include "editoriallibrorecord.h"

EditorialLibroRecord::EditorialLibroRecord(QObject *qparent,RecordBase *rparent):
EditorialLibroRecordBase(qparent,rparent)
{}

EditorialLibroRecord::EditorialLibroRecord(const EditorialLibroRecord &other):
EditorialLibroRecordBase(other)
{}

EditorialLibroRecord::~EditorialLibroRecord()
{}
