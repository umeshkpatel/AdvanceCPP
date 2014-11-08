#include <ULogging.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <algorithm>
#include <cstring>
#include <ostream>
#include <string>

namespace utl {

typedef FILE* FileHandle;

namespace {

const char* const log_severity_names[LOG_NUM_SEVERITIES] = {
  "INFO", "WARNING", "ERROR", "FATAL" };

const char* log_severity_name(int severity)
{
  if (severity >= 0 && severity < LOG_NUM_SEVERITIES)
    return log_severity_names[severity];
  return "VERBOSE";
}

int min_log_level = -1;

LoggingDestination logging_destination = LOG_TO_ALL;

// For LOG_ERROR and above, always print to stderr.
const int kAlwaysPrintErrorLevel = LOG_ERROR;

typedef std::string PathString;

PathString* log_file_name = NULL;

// this file is lazily opened and the handle may be NULL
FileHandle log_file = NULL;

std::string GetDefaultLogFile() {
  return std::string("debug.log");
}


bool InitializeLogFileHandle() {
  if (log_file)
    return true;

  if (!log_file_name) {
    log_file_name = new PathString(GetDefaultLogFile());
  }

  if ((logging_destination & LOG_TO_FILE) != 0) {
    log_file = fopen(log_file_name->c_str(), "a");
    if (log_file == NULL)
      return false;
  }

  return true;
}

void CloseFile(FileHandle log) {
  fclose(log);
}

void CloseLogFileUnlocked() {
  if (!log_file)
    return;

  CloseFile(log_file);
  log_file = NULL;
}

}  // namespace

void SetMinLogLevel(int level) {
  min_log_level = std::min(LOG_FATAL, level);
}

int GetMinLogLevel() {
  return -1;
}


LogMessage::LogMessage(const char* file, int line, LogSeverity severity)
    : severity_(severity), file_(file), line_(line) {
  Init(file, line);
}

LogMessage::LogMessage(const char* file, int line, std::string* result)
    : severity_(LOG_FATAL), file_(file), line_(line) {
  Init(file, line);
  stream_ << "Check failed: " << *result;
  delete result;
}

LogMessage::LogMessage(const char* file, int line, LogSeverity severity,
                       std::string* result)
    : severity_(severity), file_(file), line_(line) {
  Init(file, line);
  stream_ << "Check failed: " << *result;
  delete result;
}

LogMessage::~LogMessage() {

  stream_ << std::endl;
  std::string str_newline(stream_.str());

  if ((logging_destination & LOG_TO_SYSTEM_DEBUG_LOG) != 0) {
    fwrite(str_newline.data(), str_newline.size(), 1, stderr);
    fflush(stderr);
  } else if (severity_ >= kAlwaysPrintErrorLevel) {
    fwrite(str_newline.data(), str_newline.size(), 1, stderr);
    fflush(stderr);
  }

  // write to log file
  if ((logging_destination & LOG_TO_FILE) != 0) {
    if (InitializeLogFileHandle()) {
      fwrite(str_newline.data(), str_newline.size(), 1, log_file);
      fflush(log_file);
    }
  }

  if (severity_ == LOG_FATAL) {
    // Ensure the first characters of the string are on the stack so they
    // are contained in minidumps for diagnostic purposes.
    char str_stack[1024];
    str_newline.copy(str_stack, 1024);
  }
}

// writes the common header info to the stream
void LogMessage::Init(const char* file, int line) {
  std::string filename(file);
  size_t last_slash_pos = filename.find_last_of("\\/");
  filename.erase(0, last_slash_pos + 1);

  stream_ <<  '[' << log_severity_name(severity_);

  stream_ << "] [" << filename << ":" << line << "] ";

  message_start_ = stream_.tellp();
}

void CloseLogFile() {
  CloseLogFileUnlocked();
}

void RawLog(int level, const char* message) {
  if (level >= min_log_level) {
    size_t bytes_written = 0;
    const size_t message_len = strlen(message);
    int rv;
    while (bytes_written < message_len) {
      rv = fwrite(message + bytes_written,
                message_len - bytes_written, 1, stdout);
      if (rv < 0) {
        // Give up, nothing we can do now.
        break;
      }
      bytes_written += rv;
    }

    if (message_len > 0 && message[message_len - 1] != '\n') {
      do {
        rv = fwrite("\n", 1, 1, stdout);
        if (rv < 0) {
          // Give up, nothing we can do now.
          break;
        }
      } while (rv != 1);
    }
  }
}

}  // utl
