// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from village_interfaces:srv/SellNovel.idl
// generated code does not contain a copyright notice
#include "village_interfaces/srv/detail/sell_novel__rosidl_typesupport_fastrtps_cpp.hpp"
#include "village_interfaces/srv/detail/sell_novel__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace village_interfaces
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_village_interfaces
cdr_serialize(
  const village_interfaces::srv::SellNovel_Request & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: money
  cdr << ros_message.money;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_village_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  village_interfaces::srv::SellNovel_Request & ros_message)
{
  // Member: money
  cdr >> ros_message.money;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_village_interfaces
get_serialized_size(
  const village_interfaces::srv::SellNovel_Request & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: money
  {
    size_t item_size = sizeof(ros_message.money);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_village_interfaces
max_serialized_size_SellNovel_Request(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;


  // Member: money
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  return current_alignment - initial_alignment;
}

static bool _SellNovel_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const village_interfaces::srv::SellNovel_Request *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _SellNovel_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<village_interfaces::srv::SellNovel_Request *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _SellNovel_Request__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const village_interfaces::srv::SellNovel_Request *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _SellNovel_Request__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_SellNovel_Request(full_bounded, 0);
}

static message_type_support_callbacks_t _SellNovel_Request__callbacks = {
  "village_interfaces::srv",
  "SellNovel_Request",
  _SellNovel_Request__cdr_serialize,
  _SellNovel_Request__cdr_deserialize,
  _SellNovel_Request__get_serialized_size,
  _SellNovel_Request__max_serialized_size
};

static rosidl_message_type_support_t _SellNovel_Request__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_SellNovel_Request__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace village_interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_village_interfaces
const rosidl_message_type_support_t *
get_message_type_support_handle<village_interfaces::srv::SellNovel_Request>()
{
  return &village_interfaces::srv::typesupport_fastrtps_cpp::_SellNovel_Request__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, village_interfaces, srv, SellNovel_Request)() {
  return &village_interfaces::srv::typesupport_fastrtps_cpp::_SellNovel_Request__handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include <limits>
// already included above
// #include <stdexcept>
// already included above
// #include <string>
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
// already included above
// #include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace village_interfaces
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_village_interfaces
cdr_serialize(
  const village_interfaces::srv::SellNovel_Response & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: novels
  {
    cdr << ros_message.novels;
  }
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_village_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  village_interfaces::srv::SellNovel_Response & ros_message)
{
  // Member: novels
  {
    cdr >> ros_message.novels;
  }

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_village_interfaces
get_serialized_size(
  const village_interfaces::srv::SellNovel_Response & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: novels
  {
    size_t array_size = ros_message.novels.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        (ros_message.novels[index].size() + 1);
    }
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_village_interfaces
max_serialized_size_SellNovel_Response(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;


  // Member: novels
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    full_bounded = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  return current_alignment - initial_alignment;
}

static bool _SellNovel_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const village_interfaces::srv::SellNovel_Response *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _SellNovel_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<village_interfaces::srv::SellNovel_Response *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _SellNovel_Response__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const village_interfaces::srv::SellNovel_Response *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _SellNovel_Response__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_SellNovel_Response(full_bounded, 0);
}

static message_type_support_callbacks_t _SellNovel_Response__callbacks = {
  "village_interfaces::srv",
  "SellNovel_Response",
  _SellNovel_Response__cdr_serialize,
  _SellNovel_Response__cdr_deserialize,
  _SellNovel_Response__get_serialized_size,
  _SellNovel_Response__max_serialized_size
};

static rosidl_message_type_support_t _SellNovel_Response__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_SellNovel_Response__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace village_interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_village_interfaces
const rosidl_message_type_support_t *
get_message_type_support_handle<village_interfaces::srv::SellNovel_Response>()
{
  return &village_interfaces::srv::typesupport_fastrtps_cpp::_SellNovel_Response__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, village_interfaces, srv, SellNovel_Response)() {
  return &village_interfaces::srv::typesupport_fastrtps_cpp::_SellNovel_Response__handle;
}

#ifdef __cplusplus
}
#endif

#include "rmw/error_handling.h"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/service_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/service_type_support_decl.hpp"

namespace village_interfaces
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

static service_type_support_callbacks_t _SellNovel__callbacks = {
  "village_interfaces::srv",
  "SellNovel",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, village_interfaces, srv, SellNovel_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, village_interfaces, srv, SellNovel_Response)(),
};

static rosidl_service_type_support_t _SellNovel__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_SellNovel__callbacks,
  get_service_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace village_interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_village_interfaces
const rosidl_service_type_support_t *
get_service_type_support_handle<village_interfaces::srv::SellNovel>()
{
  return &village_interfaces::srv::typesupport_fastrtps_cpp::_SellNovel__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, village_interfaces, srv, SellNovel)() {
  return &village_interfaces::srv::typesupport_fastrtps_cpp::_SellNovel__handle;
}

#ifdef __cplusplus
}
#endif
