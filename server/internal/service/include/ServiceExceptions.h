#pragma once

class ValidateException : public std::exception {
    std::string _msg;

 public:
    ValidateException(const std::string& msg) : _msg(msg) {}
    virtual const char* what() const noexcept override { return _msg.c_str(); }
};

class LoginException : public std::exception {
    std::string _msg;

 public:
    LoginException(const std::string& msg) : _msg(msg) {}
    virtual const char* what() const noexcept override { return _msg.c_str(); }
};

class FileExtensionException : public std::exception {
    std::string _msg;

 public:
    FileExtensionException(const std::string& msg) : _msg(msg) {}
    virtual const char* what() const noexcept override { return _msg.c_str(); }
};