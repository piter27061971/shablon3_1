#include <iostream>
#include <string>
#include <fstream>

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

class ConsoleLogCommand : public LogCommand {
public:
    ConsoleLogCommand(const std::string& message) : message_(message) {}
    void print(const std::string& message) override {
        std::cout << message_ << std::endl;
    }
private:
    const std::string message_;
};

class FileLogCommand : public LogCommand {
public:
    explicit FileLogCommand(const std::string& message, std::ofstream& file) : message_(message), file_(file) {}
    void print(const std::string& message) override {
        if (file_.is_open()) {
            file_ << message_ << std::endl;
        }
        else
            std::cout << "File not open" << std::endl;
    }
private:
    std::string message_;
    std::ofstream& file_;
};

class PrintMessage {
public:
    PrintMessage(LogCommand& ptr, const std::string& message) : ptr_command(ptr), message_(message) {}

    void print(LogCommand& ptr_cmd) {
        ptr_command = ptr_cmd;
    }
    void invokeCommand() {
        ptr_command.print(message_);
    }
private:
    LogCommand& ptr_command;
    const std::string& message_;
};

int main(int argc, char* argv[]) {
    std::string message = "Hello world!";
    std::ofstream file("message.txt");

    ConsoleLogCommand consoleLog(message);
    PrintMessage consolePrint(consoleLog, message);

    FileLogCommand fileLog(message, file);
    PrintMessage filePrint(fileLog, message);

    consolePrint.print(consoleLog);
    consolePrint.invokeCommand();

    filePrint.print(fileLog);
    filePrint.invokeCommand();

    file.close();
    return 0;
}
