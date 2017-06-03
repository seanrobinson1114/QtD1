//---------------------------------------------------------------------------//
//!
//! \file   QMLRegistrationHelper.h
//! \author Alex Robinson
//! \brief  Qml registration helper class declaration
//!
//---------------------------------------------------------------------------//

#ifndef QML_REGISTRATION_HELPER_H
#define QML_REGISTRATION_HELPER_H

// Std Lib Includes
#include <functional>
#include <iostream>

// Qt Includes
#include <QtDeclarative>

/*! Macro used to declare the QML name of a class
 * \details It is best to call this macro after calling the standard Qt
 * macros in a class declaration.
 */
#define Q_IMPORT_ALIAS( LIB_NAME, LIB_VERSION_MAJOR, LIB_VERSION_MINOR, NAME )\
  private:                                                              \
  static const char* qmlName()                                          \
  { return NAME; }                                                      \
  static const char* qmlLibName()                                       \
  { return LIB_NAME; }                                                  \
  static int qmlLibVersionMajor()                                       \
  { return LIB_VERSION_MAJOR; }                                         \
  static int qmlLibVersionMinor()                                       \
  { return LIB_VERSION_MINOR; }                                         \
  static const int qml_type_id;                                         \
  static const int meta_type_id;                                        \
  static const int meta_type_ptr_id;                                    

/*! Macro used to register a base type with qml
 * \details This macro should appear in a class's implementation file.
 */
#define QML_REGISTER_BASE_TYPE( Type )          \
  const int Type::qml_type_id =                 \
    QtD1::QMLRegistrationHelper::registerUncreatableType<Type>( \
                               Type::qmlLibName(), \
                               Type::qmlLibVersionMajor(),              \
                               Type::qmlLibVersionMinor(),              \
                               Type::qmlName(), \
                               "QML cannot create objects of type " #Type "!" )
                                                        

/*! Macro used to register a type with qml
 * \details This macro should appear in a class's implementation file.
 */
#define QML_REGISTER_TYPE( Type )                                       \
  const int Type::qml_type_id =                      \
    QtD1::QMLRegistrationHelper::registerType<Type>( \
                                                  Type::qmlLibName(), \
                                                  Type::qmlLibVersionMajor(), \
                                                  Type::qmlLibVersionMinor(), \
                                                  Type::qmlName() )

/*! Macro used to register a base type with qml and with the meta type system
 * \details This macro should appear in a class's implementation file.
 */
#define QML_REGISTER_BASE_META_TYPE( Type )          \
  QML_REGISTER_BASE_TYPE( Type );                    \
                                                                        \
  const int Type::meta_type_ptr_id =                                    \
    QtD1::QMLRegistrationHelper::registerMetaTypePtr<Type>(Type::qmlName())

/*! Macro used to register a type with qml and with the meta type system
 * \details This macro should appear in a class's implementation file.
 */
#define QML_REGISTER_META_TYPE( Type )          \
  QML_REGISTER_TYPE( Type );                    \
                                                \
  const int Type::meta_type_id =                \
    QtD1::QMLRegistrationHelper::registerMetaType<Type>(Type::qmlName()); \
                                                                        \
  const int Type::meta_type_ptr_id =                                    \
    QtD1::QMLRegistrationHelper::registerMetaTypePtr<Type>(Type::qmlName())
    

namespace QtD1 {
  
//! The QML registration helper class
class QMLRegistrationHelper
{

public:

  //! The qml uncreatable type registration function
  template<typename T>
  static int registerUncreatableType( const char* qml_lib_name,
                                      int lib_version_major,
                                      int lib_version_minor,
                                      const char* qml_name,
                                      const char* error_message );

  //! The qml registration function 
  template<typename T>
  static int registerType( const char* qml_lib_name,
                           int lib_version_major,
                           int lib_version_minor,
                           const char* qml_name );

  //! The meta type registration function
  template<typename T>
  static int registerMetaType( const char* meta_type_name );

  //! The meta type pointer registration function
  template<typename T>
  static int registerMetaTypePtr( const char* meta_type_name );
};

// The qml interface registration function
template<typename T>
int QMLRegistrationHelper::registerUncreatableType( const char* qml_lib_name,
                                                    int lib_version_major,
                                                    int lib_version_minor,
                                                    const char* qml_name,
                                                    const char* error_message )
{
  return qmlRegisterUncreatableType<T>( qml_lib_name,
                                        lib_version_major,
                                        lib_version_minor,
                                        qml_name,
                                        error_message );
}

// Register the child type with qml
template<typename T>
int QMLRegistrationHelper::registerType( const char* qml_lib_name,
                                         int lib_version_major,
                                         int lib_version_minor,
                                         const char* qml_name )
{
  return qmlRegisterType<T>( qml_lib_name,
                             lib_version_major,
                             lib_version_minor,
                             qml_name );
}

// The meta type registration function
template<typename T>
int QMLRegistrationHelper::registerMetaType( const char* meta_type_name )
{
  return qRegisterMetaType<T>( meta_type_name );
}

// The meta type registration function
template<typename T>
int QMLRegistrationHelper::registerMetaTypePtr( const char* meta_type_name )
{
  std::string meta_type_ptr_name( meta_type_name );
  meta_type_ptr_name += "*";
  
  return qRegisterMetaType<T*>( meta_type_ptr_name.c_str() );
}
  
} // end QtD1 namespace

#endif // end QML_REGISTRATION_HELPER_H

//---------------------------------------------------------------------------//
// end QMLRegistrationHelper.h
//---------------------------------------------------------------------------//
