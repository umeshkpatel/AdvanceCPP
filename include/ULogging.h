// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef _ULOGGING_H_
#define _ULOGGING_H_

#include <cassert>
#include <string>
#include <cstring>
#include <sstream>
#include <UDefines.h>


namespace utl {

enum LoggingDestination {
  LOG_NONE                = 0,
  LOG_TO_FILE             = 1 << 0,
  LOG_TO_SYSTEM_DEBUG_LOG = 1 << 1,
  LOG_TO_ALL = LOG_TO_FILE | LOG_TO_SYSTEM_DEBUG_LOG,
  LOG_DEFAULT = LOG_TO_FILE,
};


typedef int LogSeverity;
const LogSeverity LOG_VERBOSE = -1;
const LogSeverity LOG_INFO    = 0;
const LogSeverity LOG_WARNING = 1;
const LogSeverity LOG_ERROR   = 2;
const LogSeverity LOG_FATAL   = 3;
const LogSeverity LOG_NUM_SEVERITIES = 4;

#define COMPACT_LOG_EX_INFO(ClassName, ...) \
  utl::ClassName(__FILE__, __LINE__, utl::LOG_INFO , ##__VA_ARGS__)
#define COMPACT_LOG_EX_WARNING(ClassName, ...) \
  utl::ClassName(__FILE__, __LINE__, utl::LOG_WARNING , ##__VA_ARGS__)
#define COMPACT_LOG_EX_ERROR(ClassName, ...) \
  utl::ClassName(__FILE__, __LINE__, utl::LOG_ERROR , ##__VA_ARGS__)
#define COMPACT_LOG_EX_FATAL(ClassName, ...) \
  utl::ClassName(__FILE__, __LINE__, utl::LOG_FATAL , ##__VA_ARGS__)


#define COMPACT_LOG_INFO \
  COMPACT_LOG_EX_INFO(LogMessage)
#define COMPACT_LOG_WARNING \
  COMPACT_LOG_EX_WARNING(LogMessage)
#define COMPACT_LOG_ERROR \
  COMPACT_LOG_EX_ERROR(LogMessage)
#define COMPACT_LOG_FATAL \
  COMPACT_LOG_EX_FATAL(LogMessage)
#define COMPACT_LOG_DFATAL \
  COMPACT_LOG_EX_DFATAL(LogMessage)

void SetMinLogLevel(int level);

int GetMinLogLevel();

#define LOG_IS_ON(severity) \
  ((::utl::LOG_ ## severity) >= ::utl::GetMinLogLevel())

#define LAZY_STREAM(stream, condition)                                  \
  !(condition) ? (void) 0 : ::utl::LogMessageVoidify() & (stream)

#define LOG_STREAM(severity) COMPACT_LOG_ ## severity.stream()

#define LOG(severity) LAZY_STREAM(LOG_STREAM(severity), LOG_IS_ON(severity))

#define EAT_STREAM_PARAMETERS                                           \
  true ? (void) 0 : ::utl::LogMessageVoidify() & LOG_STREAM(FATAL)

#define CHECK(condition)                       \
  LAZY_STREAM(LOG_STREAM(FATAL), !(condition)) \
  << "Check failed: " #condition ". "

// Build the error message string.  This is separate from the "Impl"
// function template because it is not performance critical and so can
// be out of line, while the "Impl" code should be inline.  Caller
// takes ownership of the returned string.
template<class t1, class t2>
std::string* MakeCheckOpString(const t1& v1, const t2& v2, const char* names) {
  std::ostringstream ss;
  ss << names << " (" << v1 << " vs. " << v2 << ")";
  std::string* msg = new std::string(ss.str());
  return msg;
}

class LogMessage {
 public:
  // Used for LOG(severity).
  LogMessage(const char* file, int line, LogSeverity severity);

  // Used for CHECK_EQ(), etc. Takes ownership of the given string.
  // Implied severity = LOG_FATAL.
  LogMessage(const char* file, int line, std::string* result);

  // Used for DCHECK_EQ(), etc. Takes ownership of the given string.
  LogMessage(const char* file, int line, LogSeverity severity,
             std::string* result);

  ~LogMessage();

  std::ostream& stream() { return stream_; }

 private:
  void Init(const char* file, int line);

  LogSeverity severity_;
  std::ostringstream stream_;
  size_t message_start_;  // Offset of the start of the message (past prefix
                          // info).
  // The file and line information passed in to the constructor.
  const char* file_;
  const int line_;
  /* DisAllow Copy and Assignment of Object */
  DISALLOW_COPY_AND_ASSIGN(LogMessage)
};

// A non-macro interface to the log facility; (useful
// when the logging level is not a compile-time constant).
inline void LogAtLevel(int const log_level, std::string const &msg) {
  LogMessage(__FILE__, __LINE__, log_level).stream() << msg;
}

// This class is used to explicitly ignore values in the conditional
// logging macros.  This avoids compiler warnings like "value computed
// is not used" and "statement has no effect".
class LogMessageVoidify {
 public:
  LogMessageVoidify() { }
  // This has to be an operator with a precedence lower than << but
  // higher than ?:
  void operator&(std::ostream&) { }
};


// Closes the log file explicitly if open.
void CloseLogFile();

// Async signal safe logging mechanism.
void RawLog(int level, const char* message);

#define RAW_LOG(level, message) utl::RawLog(utl::LOG_ ## level, message)

#define RAW_CHECK(condition)                                                   \
  do {                                                                         \
    if (!(condition))                                                          \
      utl::RawLog(utl::LOG_FATAL, "Check failed: " #condition "\n");   \
  } while (0)

}  // utl

namespace std {
  std::ostream& operator<<(std::ostream& out, const wchar_t* wstr);
  inline std::ostream& operator<<(std::ostream& out, const std::wstring& wstr) {
    return out << wstr.c_str();
  }
}  // namespace std

#endif  // _ULOGGING_H_
