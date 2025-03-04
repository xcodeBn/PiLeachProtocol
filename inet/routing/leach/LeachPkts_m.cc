//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/routing/leach/LeachPkts.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "LeachPkts_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace inet {

Register_Enum(inet::LeachPktType, (inet::LeachPktType::CH, inet::LeachPktType::ACK, inet::LeachPktType::SCH, inet::LeachPktType::DATA, inet::LeachPktType::BS));

Register_Class(ScheduleEntry)

ScheduleEntry::ScheduleEntry() : ::omnetpp::cObject()
{
}

ScheduleEntry::ScheduleEntry(const ScheduleEntry& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

ScheduleEntry::~ScheduleEntry()
{
}

ScheduleEntry& ScheduleEntry::operator=(const ScheduleEntry& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void ScheduleEntry::copy(const ScheduleEntry& other)
{
    this->nodeAddress = other.nodeAddress;
    this->TDMAdelay = other.TDMAdelay;
}

void ScheduleEntry::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->nodeAddress);
    doParsimPacking(b,this->TDMAdelay);
}

void ScheduleEntry::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->nodeAddress);
    doParsimUnpacking(b,this->TDMAdelay);
}

const Ipv4Address& ScheduleEntry::getNodeAddress() const
{
    return this->nodeAddress;
}

void ScheduleEntry::setNodeAddress(const Ipv4Address& nodeAddress)
{
    this->nodeAddress = nodeAddress;
}

double ScheduleEntry::getTDMAdelay() const
{
    return this->TDMAdelay;
}

void ScheduleEntry::setTDMAdelay(double TDMAdelay)
{
    this->TDMAdelay = TDMAdelay;
}

class ScheduleEntryDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_nodeAddress,
        FIELD_TDMAdelay,
    };
  public:
    ScheduleEntryDescriptor();
    virtual ~ScheduleEntryDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(ScheduleEntryDescriptor)

ScheduleEntryDescriptor::ScheduleEntryDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ScheduleEntry)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

ScheduleEntryDescriptor::~ScheduleEntryDescriptor()
{
    delete[] propertyNames;
}

bool ScheduleEntryDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ScheduleEntry *>(obj)!=nullptr;
}

const char **ScheduleEntryDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ScheduleEntryDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ScheduleEntryDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int ScheduleEntryDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_nodeAddress
        FD_ISEDITABLE,    // FIELD_TDMAdelay
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *ScheduleEntryDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "nodeAddress",
        "TDMAdelay",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int ScheduleEntryDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "nodeAddress") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "TDMAdelay") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *ScheduleEntryDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv4Address",    // FIELD_nodeAddress
        "double",    // FIELD_TDMAdelay
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **ScheduleEntryDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *ScheduleEntryDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int ScheduleEntryDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ScheduleEntry *pp = omnetpp::fromAnyPtr<ScheduleEntry>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ScheduleEntryDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ScheduleEntry *pp = omnetpp::fromAnyPtr<ScheduleEntry>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ScheduleEntry'", field);
    }
}

const char *ScheduleEntryDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ScheduleEntry *pp = omnetpp::fromAnyPtr<ScheduleEntry>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ScheduleEntryDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ScheduleEntry *pp = omnetpp::fromAnyPtr<ScheduleEntry>(object); (void)pp;
    switch (field) {
        case FIELD_nodeAddress: return pp->getNodeAddress().str();
        case FIELD_TDMAdelay: return double2string(pp->getTDMAdelay());
        default: return "";
    }
}

void ScheduleEntryDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ScheduleEntry *pp = omnetpp::fromAnyPtr<ScheduleEntry>(object); (void)pp;
    switch (field) {
        case FIELD_TDMAdelay: pp->setTDMAdelay(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ScheduleEntry'", field);
    }
}

omnetpp::cValue ScheduleEntryDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ScheduleEntry *pp = omnetpp::fromAnyPtr<ScheduleEntry>(object); (void)pp;
    switch (field) {
        case FIELD_nodeAddress: return omnetpp::toAnyPtr(&pp->getNodeAddress()); break;
        case FIELD_TDMAdelay: return pp->getTDMAdelay();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ScheduleEntry' as cValue -- field index out of range?", field);
    }
}

void ScheduleEntryDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ScheduleEntry *pp = omnetpp::fromAnyPtr<ScheduleEntry>(object); (void)pp;
    switch (field) {
        case FIELD_TDMAdelay: pp->setTDMAdelay(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ScheduleEntry'", field);
    }
}

const char *ScheduleEntryDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr ScheduleEntryDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ScheduleEntry *pp = omnetpp::fromAnyPtr<ScheduleEntry>(object); (void)pp;
    switch (field) {
        case FIELD_nodeAddress: return omnetpp::toAnyPtr(&pp->getNodeAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ScheduleEntryDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ScheduleEntry *pp = omnetpp::fromAnyPtr<ScheduleEntry>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ScheduleEntry'", field);
    }
}

Register_Class(LeachControlPkt)

LeachControlPkt::LeachControlPkt() : ::inet::FieldsChunk()
{
}

LeachControlPkt::LeachControlPkt(const LeachControlPkt& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

LeachControlPkt::~LeachControlPkt()
{
    delete [] this->schedule;
}

LeachControlPkt& LeachControlPkt::operator=(const LeachControlPkt& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void LeachControlPkt::copy(const LeachControlPkt& other)
{
    this->packetType = other.packetType;
    this->srcAddress = other.srcAddress;
    this->fingerprint = other.fingerprint;
    delete [] this->schedule;
    this->schedule = (other.schedule_arraysize==0) ? nullptr : new ScheduleEntry[other.schedule_arraysize];
    schedule_arraysize = other.schedule_arraysize;
    for (size_t i = 0; i < schedule_arraysize; i++) {
        this->schedule[i] = other.schedule[i];
    }
}

void LeachControlPkt::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->packetType);
    doParsimPacking(b,this->srcAddress);
    doParsimPacking(b,this->fingerprint);
    b->pack(schedule_arraysize);
    doParsimArrayPacking(b,this->schedule,schedule_arraysize);
}

void LeachControlPkt::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->packetType);
    doParsimUnpacking(b,this->srcAddress);
    doParsimUnpacking(b,this->fingerprint);
    delete [] this->schedule;
    b->unpack(schedule_arraysize);
    if (schedule_arraysize == 0) {
        this->schedule = nullptr;
    } else {
        this->schedule = new ScheduleEntry[schedule_arraysize];
        doParsimArrayUnpacking(b,this->schedule,schedule_arraysize);
    }
}

LeachPktType LeachControlPkt::getPacketType() const
{
    return this->packetType;
}

void LeachControlPkt::setPacketType(LeachPktType packetType)
{
    handleChange();
    this->packetType = packetType;
}

const Ipv4Address& LeachControlPkt::getSrcAddress() const
{
    return this->srcAddress;
}

void LeachControlPkt::setSrcAddress(const Ipv4Address& srcAddress)
{
    handleChange();
    this->srcAddress = srcAddress;
}

const char * LeachControlPkt::getFingerprint() const
{
    return this->fingerprint.c_str();
}

void LeachControlPkt::setFingerprint(const char * fingerprint)
{
    handleChange();
    this->fingerprint = fingerprint;
}

size_t LeachControlPkt::getScheduleArraySize() const
{
    return schedule_arraysize;
}

const ScheduleEntry& LeachControlPkt::getSchedule(size_t k) const
{
    if (k >= schedule_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)schedule_arraysize, (unsigned long)k);
    return this->schedule[k];
}

void LeachControlPkt::setScheduleArraySize(size_t newSize)
{
    handleChange();
    ScheduleEntry *schedule2 = (newSize==0) ? nullptr : new ScheduleEntry[newSize];
    size_t minSize = schedule_arraysize < newSize ? schedule_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        schedule2[i] = this->schedule[i];
    delete [] this->schedule;
    this->schedule = schedule2;
    schedule_arraysize = newSize;
}

void LeachControlPkt::setSchedule(size_t k, const ScheduleEntry& schedule)
{
    if (k >= schedule_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)schedule_arraysize, (unsigned long)k);
    handleChange();
    this->schedule[k] = schedule;
}

void LeachControlPkt::insertSchedule(size_t k, const ScheduleEntry& schedule)
{
    if (k > schedule_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)schedule_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = schedule_arraysize + 1;
    ScheduleEntry *schedule2 = new ScheduleEntry[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        schedule2[i] = this->schedule[i];
    schedule2[k] = schedule;
    for (i = k + 1; i < newSize; i++)
        schedule2[i] = this->schedule[i-1];
    delete [] this->schedule;
    this->schedule = schedule2;
    schedule_arraysize = newSize;
}

void LeachControlPkt::appendSchedule(const ScheduleEntry& schedule)
{
    insertSchedule(schedule_arraysize, schedule);
}

void LeachControlPkt::eraseSchedule(size_t k)
{
    if (k >= schedule_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)schedule_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = schedule_arraysize - 1;
    ScheduleEntry *schedule2 = (newSize == 0) ? nullptr : new ScheduleEntry[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        schedule2[i] = this->schedule[i];
    for (i = k; i < newSize; i++)
        schedule2[i] = this->schedule[i+1];
    delete [] this->schedule;
    this->schedule = schedule2;
    schedule_arraysize = newSize;
}

class LeachControlPktDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_packetType,
        FIELD_srcAddress,
        FIELD_fingerprint,
        FIELD_schedule,
    };
  public:
    LeachControlPktDescriptor();
    virtual ~LeachControlPktDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(LeachControlPktDescriptor)

LeachControlPktDescriptor::LeachControlPktDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LeachControlPkt)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

LeachControlPktDescriptor::~LeachControlPktDescriptor()
{
    delete[] propertyNames;
}

bool LeachControlPktDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LeachControlPkt *>(obj)!=nullptr;
}

const char **LeachControlPktDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LeachControlPktDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LeachControlPktDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int LeachControlPktDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_packetType
        0,    // FIELD_srcAddress
        FD_ISEDITABLE,    // FIELD_fingerprint
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISRESIZABLE,    // FIELD_schedule
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *LeachControlPktDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "packetType",
        "srcAddress",
        "fingerprint",
        "schedule",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int LeachControlPktDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "packetType") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "srcAddress") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "fingerprint") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "schedule") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *LeachControlPktDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::LeachPktType",    // FIELD_packetType
        "inet::Ipv4Address",    // FIELD_srcAddress
        "string",    // FIELD_fingerprint
        "inet::ScheduleEntry",    // FIELD_schedule
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **LeachControlPktDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_packetType: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *LeachControlPktDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_packetType:
            if (!strcmp(propertyName, "enum")) return "inet::LeachPktType";
            return nullptr;
        default: return nullptr;
    }
}

int LeachControlPktDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LeachControlPkt *pp = omnetpp::fromAnyPtr<LeachControlPkt>(object); (void)pp;
    switch (field) {
        case FIELD_schedule: return pp->getScheduleArraySize();
        default: return 0;
    }
}

void LeachControlPktDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LeachControlPkt *pp = omnetpp::fromAnyPtr<LeachControlPkt>(object); (void)pp;
    switch (field) {
        case FIELD_schedule: pp->setScheduleArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LeachControlPkt'", field);
    }
}

const char *LeachControlPktDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LeachControlPkt *pp = omnetpp::fromAnyPtr<LeachControlPkt>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LeachControlPktDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LeachControlPkt *pp = omnetpp::fromAnyPtr<LeachControlPkt>(object); (void)pp;
    switch (field) {
        case FIELD_packetType: return enum2string(pp->getPacketType(), "inet::LeachPktType");
        case FIELD_srcAddress: return pp->getSrcAddress().str();
        case FIELD_fingerprint: return oppstring2string(pp->getFingerprint());
        case FIELD_schedule: return pp->getSchedule(i).str();
        default: return "";
    }
}

void LeachControlPktDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LeachControlPkt *pp = omnetpp::fromAnyPtr<LeachControlPkt>(object); (void)pp;
    switch (field) {
        case FIELD_packetType: pp->setPacketType((inet::LeachPktType)string2enum(value, "inet::LeachPktType")); break;
        case FIELD_fingerprint: pp->setFingerprint((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LeachControlPkt'", field);
    }
}

omnetpp::cValue LeachControlPktDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LeachControlPkt *pp = omnetpp::fromAnyPtr<LeachControlPkt>(object); (void)pp;
    switch (field) {
        case FIELD_packetType: return static_cast<int>(pp->getPacketType());
        case FIELD_srcAddress: return omnetpp::toAnyPtr(&pp->getSrcAddress()); break;
        case FIELD_fingerprint: return pp->getFingerprint();
        case FIELD_schedule: return omnetpp::toAnyPtr(&pp->getSchedule(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LeachControlPkt' as cValue -- field index out of range?", field);
    }
}

void LeachControlPktDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LeachControlPkt *pp = omnetpp::fromAnyPtr<LeachControlPkt>(object); (void)pp;
    switch (field) {
        case FIELD_packetType: pp->setPacketType(static_cast<inet::LeachPktType>(value.intValue())); break;
        case FIELD_fingerprint: pp->setFingerprint(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LeachControlPkt'", field);
    }
}

const char *LeachControlPktDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_schedule: return omnetpp::opp_typename(typeid(ScheduleEntry));
        default: return nullptr;
    };
}

omnetpp::any_ptr LeachControlPktDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LeachControlPkt *pp = omnetpp::fromAnyPtr<LeachControlPkt>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddress: return omnetpp::toAnyPtr(&pp->getSrcAddress()); break;
        case FIELD_schedule: return omnetpp::toAnyPtr(&pp->getSchedule(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LeachControlPktDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LeachControlPkt *pp = omnetpp::fromAnyPtr<LeachControlPkt>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LeachControlPkt'", field);
    }
}

Register_Class(LeachDataPkt)

LeachDataPkt::LeachDataPkt() : ::inet::LeachControlPkt()
{
}

LeachDataPkt::LeachDataPkt(const LeachDataPkt& other) : ::inet::LeachControlPkt(other)
{
    copy(other);
}

LeachDataPkt::~LeachDataPkt()
{
}

LeachDataPkt& LeachDataPkt::operator=(const LeachDataPkt& other)
{
    if (this == &other) return *this;
    ::inet::LeachControlPkt::operator=(other);
    copy(other);
    return *this;
}

void LeachDataPkt::copy(const LeachDataPkt& other)
{
    this->temperature = other.temperature;
    this->humidity = other.humidity;
}

void LeachDataPkt::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::LeachControlPkt::parsimPack(b);
    doParsimPacking(b,this->temperature);
    doParsimPacking(b,this->humidity);
}

void LeachDataPkt::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::LeachControlPkt::parsimUnpack(b);
    doParsimUnpacking(b,this->temperature);
    doParsimUnpacking(b,this->humidity);
}

double LeachDataPkt::getTemperature() const
{
    return this->temperature;
}

void LeachDataPkt::setTemperature(double temperature)
{
    handleChange();
    this->temperature = temperature;
}

double LeachDataPkt::getHumidity() const
{
    return this->humidity;
}

void LeachDataPkt::setHumidity(double humidity)
{
    handleChange();
    this->humidity = humidity;
}

class LeachDataPktDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_temperature,
        FIELD_humidity,
    };
  public:
    LeachDataPktDescriptor();
    virtual ~LeachDataPktDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(LeachDataPktDescriptor)

LeachDataPktDescriptor::LeachDataPktDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LeachDataPkt)), "inet::LeachControlPkt")
{
    propertyNames = nullptr;
}

LeachDataPktDescriptor::~LeachDataPktDescriptor()
{
    delete[] propertyNames;
}

bool LeachDataPktDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LeachDataPkt *>(obj)!=nullptr;
}

const char **LeachDataPktDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LeachDataPktDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LeachDataPktDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int LeachDataPktDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_temperature
        FD_ISEDITABLE,    // FIELD_humidity
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *LeachDataPktDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "temperature",
        "humidity",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int LeachDataPktDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "temperature") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "humidity") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *LeachDataPktDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "double",    // FIELD_temperature
        "double",    // FIELD_humidity
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **LeachDataPktDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *LeachDataPktDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int LeachDataPktDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LeachDataPkt *pp = omnetpp::fromAnyPtr<LeachDataPkt>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LeachDataPktDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LeachDataPkt *pp = omnetpp::fromAnyPtr<LeachDataPkt>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LeachDataPkt'", field);
    }
}

const char *LeachDataPktDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LeachDataPkt *pp = omnetpp::fromAnyPtr<LeachDataPkt>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LeachDataPktDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LeachDataPkt *pp = omnetpp::fromAnyPtr<LeachDataPkt>(object); (void)pp;
    switch (field) {
        case FIELD_temperature: return double2string(pp->getTemperature());
        case FIELD_humidity: return double2string(pp->getHumidity());
        default: return "";
    }
}

void LeachDataPktDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LeachDataPkt *pp = omnetpp::fromAnyPtr<LeachDataPkt>(object); (void)pp;
    switch (field) {
        case FIELD_temperature: pp->setTemperature(string2double(value)); break;
        case FIELD_humidity: pp->setHumidity(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LeachDataPkt'", field);
    }
}

omnetpp::cValue LeachDataPktDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LeachDataPkt *pp = omnetpp::fromAnyPtr<LeachDataPkt>(object); (void)pp;
    switch (field) {
        case FIELD_temperature: return pp->getTemperature();
        case FIELD_humidity: return pp->getHumidity();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LeachDataPkt' as cValue -- field index out of range?", field);
    }
}

void LeachDataPktDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LeachDataPkt *pp = omnetpp::fromAnyPtr<LeachDataPkt>(object); (void)pp;
    switch (field) {
        case FIELD_temperature: pp->setTemperature(value.doubleValue()); break;
        case FIELD_humidity: pp->setHumidity(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LeachDataPkt'", field);
    }
}

const char *LeachDataPktDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr LeachDataPktDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LeachDataPkt *pp = omnetpp::fromAnyPtr<LeachDataPkt>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LeachDataPktDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LeachDataPkt *pp = omnetpp::fromAnyPtr<LeachDataPkt>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LeachDataPkt'", field);
    }
}

Register_Class(LeachBSPkt)

LeachBSPkt::LeachBSPkt() : ::inet::LeachControlPkt()
{
}

LeachBSPkt::LeachBSPkt(const LeachBSPkt& other) : ::inet::LeachControlPkt(other)
{
    copy(other);
}

LeachBSPkt::~LeachBSPkt()
{
}

LeachBSPkt& LeachBSPkt::operator=(const LeachBSPkt& other)
{
    if (this == &other) return *this;
    ::inet::LeachControlPkt::operator=(other);
    copy(other);
    return *this;
}

void LeachBSPkt::copy(const LeachBSPkt& other)
{
    this->CHAddr = other.CHAddr;
}

void LeachBSPkt::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::LeachControlPkt::parsimPack(b);
    doParsimPacking(b,this->CHAddr);
}

void LeachBSPkt::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::LeachControlPkt::parsimUnpack(b);
    doParsimUnpacking(b,this->CHAddr);
}

const Ipv4Address& LeachBSPkt::getCHAddr() const
{
    return this->CHAddr;
}

void LeachBSPkt::setCHAddr(const Ipv4Address& CHAddr)
{
    handleChange();
    this->CHAddr = CHAddr;
}

class LeachBSPktDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_CHAddr,
    };
  public:
    LeachBSPktDescriptor();
    virtual ~LeachBSPktDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(LeachBSPktDescriptor)

LeachBSPktDescriptor::LeachBSPktDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LeachBSPkt)), "inet::LeachControlPkt")
{
    propertyNames = nullptr;
}

LeachBSPktDescriptor::~LeachBSPktDescriptor()
{
    delete[] propertyNames;
}

bool LeachBSPktDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LeachBSPkt *>(obj)!=nullptr;
}

const char **LeachBSPktDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LeachBSPktDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LeachBSPktDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int LeachBSPktDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_CHAddr
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *LeachBSPktDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "CHAddr",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int LeachBSPktDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "CHAddr") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *LeachBSPktDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv4Address",    // FIELD_CHAddr
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **LeachBSPktDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *LeachBSPktDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int LeachBSPktDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LeachBSPkt *pp = omnetpp::fromAnyPtr<LeachBSPkt>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LeachBSPktDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LeachBSPkt *pp = omnetpp::fromAnyPtr<LeachBSPkt>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LeachBSPkt'", field);
    }
}

const char *LeachBSPktDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LeachBSPkt *pp = omnetpp::fromAnyPtr<LeachBSPkt>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LeachBSPktDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LeachBSPkt *pp = omnetpp::fromAnyPtr<LeachBSPkt>(object); (void)pp;
    switch (field) {
        case FIELD_CHAddr: return pp->getCHAddr().str();
        default: return "";
    }
}

void LeachBSPktDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LeachBSPkt *pp = omnetpp::fromAnyPtr<LeachBSPkt>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LeachBSPkt'", field);
    }
}

omnetpp::cValue LeachBSPktDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LeachBSPkt *pp = omnetpp::fromAnyPtr<LeachBSPkt>(object); (void)pp;
    switch (field) {
        case FIELD_CHAddr: return omnetpp::toAnyPtr(&pp->getCHAddr()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LeachBSPkt' as cValue -- field index out of range?", field);
    }
}

void LeachBSPktDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LeachBSPkt *pp = omnetpp::fromAnyPtr<LeachBSPkt>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LeachBSPkt'", field);
    }
}

const char *LeachBSPktDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr LeachBSPktDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LeachBSPkt *pp = omnetpp::fromAnyPtr<LeachBSPkt>(object); (void)pp;
    switch (field) {
        case FIELD_CHAddr: return omnetpp::toAnyPtr(&pp->getCHAddr()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LeachBSPktDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LeachBSPkt *pp = omnetpp::fromAnyPtr<LeachBSPkt>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LeachBSPkt'", field);
    }
}

Register_Class(LeachAckPkt)

LeachAckPkt::LeachAckPkt() : ::inet::LeachControlPkt()
{
}

LeachAckPkt::LeachAckPkt(const LeachAckPkt& other) : ::inet::LeachControlPkt(other)
{
    copy(other);
}

LeachAckPkt::~LeachAckPkt()
{
}

LeachAckPkt& LeachAckPkt::operator=(const LeachAckPkt& other)
{
    if (this == &other) return *this;
    ::inet::LeachControlPkt::operator=(other);
    copy(other);
    return *this;
}

void LeachAckPkt::copy(const LeachAckPkt& other)
{
}

void LeachAckPkt::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::LeachControlPkt::parsimPack(b);
}

void LeachAckPkt::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::LeachControlPkt::parsimUnpack(b);
}

class LeachAckPktDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    LeachAckPktDescriptor();
    virtual ~LeachAckPktDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(LeachAckPktDescriptor)

LeachAckPktDescriptor::LeachAckPktDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LeachAckPkt)), "inet::LeachControlPkt")
{
    propertyNames = nullptr;
}

LeachAckPktDescriptor::~LeachAckPktDescriptor()
{
    delete[] propertyNames;
}

bool LeachAckPktDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LeachAckPkt *>(obj)!=nullptr;
}

const char **LeachAckPktDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LeachAckPktDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LeachAckPktDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int LeachAckPktDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *LeachAckPktDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int LeachAckPktDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *LeachAckPktDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **LeachAckPktDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *LeachAckPktDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int LeachAckPktDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LeachAckPkt *pp = omnetpp::fromAnyPtr<LeachAckPkt>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LeachAckPktDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LeachAckPkt *pp = omnetpp::fromAnyPtr<LeachAckPkt>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LeachAckPkt'", field);
    }
}

const char *LeachAckPktDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LeachAckPkt *pp = omnetpp::fromAnyPtr<LeachAckPkt>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LeachAckPktDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LeachAckPkt *pp = omnetpp::fromAnyPtr<LeachAckPkt>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void LeachAckPktDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LeachAckPkt *pp = omnetpp::fromAnyPtr<LeachAckPkt>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LeachAckPkt'", field);
    }
}

omnetpp::cValue LeachAckPktDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LeachAckPkt *pp = omnetpp::fromAnyPtr<LeachAckPkt>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LeachAckPkt' as cValue -- field index out of range?", field);
    }
}

void LeachAckPktDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LeachAckPkt *pp = omnetpp::fromAnyPtr<LeachAckPkt>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LeachAckPkt'", field);
    }
}

const char *LeachAckPktDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr LeachAckPktDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LeachAckPkt *pp = omnetpp::fromAnyPtr<LeachAckPkt>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LeachAckPktDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LeachAckPkt *pp = omnetpp::fromAnyPtr<LeachAckPkt>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LeachAckPkt'", field);
    }
}

Register_Class(LeachSchedulePkt)

LeachSchedulePkt::LeachSchedulePkt() : ::inet::LeachControlPkt()
{
}

LeachSchedulePkt::LeachSchedulePkt(const LeachSchedulePkt& other) : ::inet::LeachControlPkt(other)
{
    copy(other);
}

LeachSchedulePkt::~LeachSchedulePkt()
{
}

LeachSchedulePkt& LeachSchedulePkt::operator=(const LeachSchedulePkt& other)
{
    if (this == &other) return *this;
    ::inet::LeachControlPkt::operator=(other);
    copy(other);
    return *this;
}

void LeachSchedulePkt::copy(const LeachSchedulePkt& other)
{
}

void LeachSchedulePkt::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::LeachControlPkt::parsimPack(b);
}

void LeachSchedulePkt::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::LeachControlPkt::parsimUnpack(b);
}

class LeachSchedulePktDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    LeachSchedulePktDescriptor();
    virtual ~LeachSchedulePktDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(LeachSchedulePktDescriptor)

LeachSchedulePktDescriptor::LeachSchedulePktDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LeachSchedulePkt)), "inet::LeachControlPkt")
{
    propertyNames = nullptr;
}

LeachSchedulePktDescriptor::~LeachSchedulePktDescriptor()
{
    delete[] propertyNames;
}

bool LeachSchedulePktDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LeachSchedulePkt *>(obj)!=nullptr;
}

const char **LeachSchedulePktDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LeachSchedulePktDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LeachSchedulePktDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int LeachSchedulePktDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *LeachSchedulePktDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int LeachSchedulePktDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *LeachSchedulePktDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **LeachSchedulePktDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *LeachSchedulePktDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int LeachSchedulePktDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LeachSchedulePkt *pp = omnetpp::fromAnyPtr<LeachSchedulePkt>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LeachSchedulePktDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LeachSchedulePkt *pp = omnetpp::fromAnyPtr<LeachSchedulePkt>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LeachSchedulePkt'", field);
    }
}

const char *LeachSchedulePktDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LeachSchedulePkt *pp = omnetpp::fromAnyPtr<LeachSchedulePkt>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LeachSchedulePktDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LeachSchedulePkt *pp = omnetpp::fromAnyPtr<LeachSchedulePkt>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void LeachSchedulePktDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LeachSchedulePkt *pp = omnetpp::fromAnyPtr<LeachSchedulePkt>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LeachSchedulePkt'", field);
    }
}

omnetpp::cValue LeachSchedulePktDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LeachSchedulePkt *pp = omnetpp::fromAnyPtr<LeachSchedulePkt>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LeachSchedulePkt' as cValue -- field index out of range?", field);
    }
}

void LeachSchedulePktDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LeachSchedulePkt *pp = omnetpp::fromAnyPtr<LeachSchedulePkt>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LeachSchedulePkt'", field);
    }
}

const char *LeachSchedulePktDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr LeachSchedulePktDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LeachSchedulePkt *pp = omnetpp::fromAnyPtr<LeachSchedulePkt>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LeachSchedulePktDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LeachSchedulePkt *pp = omnetpp::fromAnyPtr<LeachSchedulePkt>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LeachSchedulePkt'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

