#include "editorialrecord.h"

EditorialRecord::EditorialRecord(QObject *qparent,RecordBase *rparent):
EditorialRecordBase(qparent,rparent)
{}

EditorialRecord::EditorialRecord(const EditorialRecord &other):
EditorialRecordBase(other)
{}

EditorialRecord::~EditorialRecord()
{}
