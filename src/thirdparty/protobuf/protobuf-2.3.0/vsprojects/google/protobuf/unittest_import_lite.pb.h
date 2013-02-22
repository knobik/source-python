// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unittest_import_lite.proto

#ifndef PROTOBUF_google_2fprotobuf_2funittest_5fimport_5flite_2eproto__INCLUDED
#define PROTOBUF_google_2fprotobuf_2funittest_5fimport_5flite_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2003000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2003000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
// @@protoc_insertion_point(includes)

namespace protobuf_unittest_import {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_google_2fprotobuf_2funittest_5fimport_5flite_2eproto();
void protobuf_AssignDesc_google_2fprotobuf_2funittest_5fimport_5flite_2eproto();
void protobuf_ShutdownFile_google_2fprotobuf_2funittest_5fimport_5flite_2eproto();

class ImportMessageLite;

enum ImportEnumLite {
  IMPORT_LITE_FOO = 7,
  IMPORT_LITE_BAR = 8,
  IMPORT_LITE_BAZ = 9
};
bool ImportEnumLite_IsValid(int value);
const ImportEnumLite ImportEnumLite_MIN = IMPORT_LITE_FOO;
const ImportEnumLite ImportEnumLite_MAX = IMPORT_LITE_BAZ;
const int ImportEnumLite_ARRAYSIZE = ImportEnumLite_MAX + 1;

// ===================================================================

class ImportMessageLite : public ::google::protobuf::MessageLite {
 public:
  ImportMessageLite();
  virtual ~ImportMessageLite();
  
  ImportMessageLite(const ImportMessageLite& from);
  
  inline ImportMessageLite& operator=(const ImportMessageLite& from) {
    CopyFrom(from);
    return *this;
  }
  
  static const ImportMessageLite& default_instance();
  
  void Swap(ImportMessageLite* other);
  
  // implements Message ----------------------------------------------
  
  ImportMessageLite* New() const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const ImportMessageLite& from);
  void MergeFrom(const ImportMessageLite& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::std::string GetTypeName() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // optional int32 d = 1;
  inline bool has_d() const;
  inline void clear_d();
  static const int kDFieldNumber = 1;
  inline ::google::protobuf::int32 d() const;
  inline void set_d(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:protobuf_unittest_import.ImportMessageLite)
 private:
  mutable int _cached_size_;
  
  ::google::protobuf::int32 d_;
  friend void  protobuf_AddDesc_google_2fprotobuf_2funittest_5fimport_5flite_2eproto();
  friend void protobuf_AssignDesc_google_2fprotobuf_2funittest_5fimport_5flite_2eproto();
  friend void protobuf_ShutdownFile_google_2fprotobuf_2funittest_5fimport_5flite_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  // WHY DOES & HAVE LOWER PRECEDENCE THAN != !?
  inline bool _has_bit(int index) const {
    return (_has_bits_[index / 32] & (1u << (index % 32))) != 0;
  }
  inline void _set_bit(int index) {
    _has_bits_[index / 32] |= (1u << (index % 32));
  }
  inline void _clear_bit(int index) {
    _has_bits_[index / 32] &= ~(1u << (index % 32));
  }
  
  void InitAsDefaultInstance();
  static ImportMessageLite* default_instance_;
};
// ===================================================================


// ===================================================================

// ImportMessageLite

// optional int32 d = 1;
inline bool ImportMessageLite::has_d() const {
  return _has_bit(0);
}
inline void ImportMessageLite::clear_d() {
  d_ = 0;
  _clear_bit(0);
}
inline ::google::protobuf::int32 ImportMessageLite::d() const {
  return d_;
}
inline void ImportMessageLite::set_d(::google::protobuf::int32 value) {
  _set_bit(0);
  d_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace protobuf_unittest_import

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_google_2fprotobuf_2funittest_5fimport_5flite_2eproto__INCLUDED
