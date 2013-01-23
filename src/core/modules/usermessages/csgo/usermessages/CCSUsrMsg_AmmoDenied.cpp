#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_AmmoDenied & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_AmmoDenied & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_AmmoDenied & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_AmmoDenied & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_AmmoDenied isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_AmmoDenied_bindings()
{
    bpl::class_<CCSUsrMsg_AmmoDenied, bpl::bases<google::protobuf::Message>> binder("CCSUsrMsg_AmmoDenied");
    binder.def(bpl::init<const CCSUsrMsg_AmmoDenied &>());

    void (CCSUsrMsg_AmmoDenied::*copy_from_ptr)(const CCSUsrMsg_AmmoDenied &) = \
        &CCSUsrMsg_AmmoDenied::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_AmmoDenied::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_AmmoDenied::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_AmmoDenied::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_AmmoDenied::ByteSize);

    binder.def("has_ammoidx", &CCSUsrMsg_AmmoDenied::has_ammoidx);
    binder.def("set_ammoidx", &CCSUsrMsg_AmmoDenied::set_ammoidx);
    binder.def("clear_ammoidx", &CCSUsrMsg_AmmoDenied::clear_ammoidx);
    binder.add_property("ammoidx", &CCSUsrMsg_AmmoDenied::ammoidx);
;
}