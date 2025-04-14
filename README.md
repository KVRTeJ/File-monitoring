# File-monitoring

## Task Definition

Write a program with a console interface that monitors selected files.

We will limit the monitoring to two attributes:

> 1. File existence;  
> 2. File size.

The program will output notifications on the console whenever changes occur in a file.

There are several scenarios for a monitored file:

> 1. The file exists and is not empty – the console displays that the file exists and shows its size.  
> 2. The file exists and has been modified – the console displays that the file exists, shows a message indicating that the file was changed, and shows its size.  
> 3. The file does not exist – the console displays a message that the file does not exist.

Whenever there is a change in the state of a monitored file (an event occurs), a corresponding message must be displayed on the screen.

In this implementation, a signal-slot mechanism is used to handle events corresponding to file changes.

## Proposed Solution

To address this task, a signal-slot connection is employed between the two main entities of the project:  
1. **FileObserver**, which emits signals when the state of a file (or files) changes.  
2. **IFileLog (interface)**, which provides slots that will receive the signals.

## Signals and Slots

*Signals in FileObserver*
```cpp
signals:
    void fileExist(const QString &path, qint64 size);
    void fileChanged(const QString &path, qint64 size);
    void fileNotExist(const QString &path);
```

*Slots in IFileLog*
```cpp
public slots:
    virtual void fileExist(const QString &path, qint64 size) = 0;
    virtual void fileChanged(const QString &path, qint64 size) = 0;
    virtual void fileNotExist(const QString &path) = 0;
```

The signal-slot connection is set up in the `FileObserver` class within the `setLogger(IFileLog*)` method. Before establishing the connections, the code checks whether a null pointer was passed for IFileLog. If so, signals and slots will not be connected.
```cpp
void FileObserver::setLogger(IFileLog *logger) {
    if(!logger) {
        m_logger = nullptr;
        return;
    }

    m_logger = logger;

    connect(this, SIGNAL(fileExist(QString,qint64)), m_logger, SLOT(fileExist(QString,qint64)));
    connect(this, SIGNAL(fileChanged(QString,qint64)), m_logger, SLOT(fileChanged(QString,qint64)));
    connect(this, SIGNAL(fileNotExist(QString)), m_logger, SLOT(fileNotExist(QString)));
}
```

## Console Interface

Because the task required a console interface, a class derived from IFileLog — **ConsoleFileLog** — was created. This class handles logging file changes to the console.

*Example implementation of console logging*
```cpp
void ConsoleFileLog::fileExist(const QString &path, const qint64 size) {
    std::cout << "File " << path.toStdString() << " changed size to " << size << std::endl;
}
```

## Design Patterns

A creational design pattern, **Singleton**, has been implemented for the FileObserver class. The implementation of this pattern resides on a branch derived from `develop` — in the branch `addingSingleton`. The Singleton is used to ensure that there is only one instance of FileObserver, which can be accessed *by reference* through the static `Instance()` method. This method employs "lazy" initialization for the FileObserver object.
```cpp
FileObserver& FileObserver::Instance() {
    static FileObserver observer;
    return observer;
}
```
Thus, we have a method to retrieve a reference to the class instance, and now we need to prevent the creation of new objects. To achieve this, the default constructor (as well as the constructor with arguments) and the destructor have been declared as private.
```cpp
private:
    FileObserver(IFileLog *logger = nullptr);
    ~FileObserver() override = default;
```
Additionally, copy operations (copy constructor and assignment operator) have been deleted using the `delete` operator to forbid any copying of FileObserver objects.
```cpp
FileObserver(const FileObserver &other) = delete;
FileObserver& operator = (const FileObserver &other) = delete;
```

## Testing

The following tests were conducted to verify the functionality of the program:

### 1. Monitoring a Single File

Basic monitoring of a single file has been tested. FileObserver correctly detects the existence, modification, and absence of the file.

```cpp
FileObserver& observer = FileObserver::Instance();
observer.setLogger(new ConsoleFileLog());
observer.add("usr/temp/example.txt");

for(;;) {
    observer.check();   
}
```

### 2. Monitoring Multiple Files

The system successfully monitors multiple files concurrently. Signals regarding the state of each file are generated independently for every file in the monitoring list.

```cpp
FileObserver& observer = FileObserver::Instance();
observer.add("usr/temp/config.txt");
observer.add("usr/temp/data.log");
observer.add("usr/temp/settings.json");
```

### 3. Adding Duplicate File Paths

It has been confirmed that FileObserver is safeguarded against adding duplicate paths. If you attempt to add a path that is already being monitored, the `add()` method will return `false` and the duplicate will not be added to the monitoring list.

```cpp
FileObserver& observer = FileObserver::Instance();
observer.add("usr/temp/config.txt"); // Returns true, file successfully added to monitoring list
observer.add("usr/temp/config.txt"); // Returns false, duplicate is not added
```

All tests verified that the main functions of the program work as expected.

## User Guide

### Basic Configuration

Setting up file monitoring is carried out in a few simple steps:

1. Obtain the FileObserver instance using the Singleton pattern.
2. Set a logger to handle the events.
3. Add the files to be monitored.
4. Periodically call the `check()` method to verify the state of the files.

```cpp
// Obtaining the FileObserver instance
FileObserver& observer = FileObserver::Instance();

// Creating and setting the logger
ConsoleFileLog logger;
observer.setLogger(&logger);

// Adding files for monitoring
observer.add("/path/to/your/file.txt");
observer.add("/path/to/another/file.log");

// Periodic file checking
// You can use a timer or a loop
while (running) {
    observer.check();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
```

### Event Interpretation

When the `check()` method is called, the FileObserver examines the state of all monitored files and generates corresponding events:

- **fileExist** — The file exists and has not changed since the last check.
- **fileChanged** — The file has been modified since the last check.
- **fileNotExist** — The file does not exist.

These events are processed by the logger, which you set using `setLogger()`. By default, `ConsoleFileLog` outputs the event information to the console.

### Setting Up Test Files

To test the library, you can perform the following steps:

1. Create a text file at the path specified in your code.
2. Run the application — you will see the `fileExist` event.
3. Modify the contents of the file — the `fileChanged` event will be triggered.
4. Delete the file — the `fileNotExist` event will occur.
5. Recreate the file — the `fileExist` event will appear again.

### Adjusting the Checking Frequency

In the example, a 100 ms interval is used for checking, ensuring a rapid response to changes but potentially adding extra system load. For real applications, it is recommended to use a longer interval, for example:

```cpp
// Check every second
std::this_thread::sleep_for(std::chrono::seconds(1));

// or

// Check every 5 seconds for files that change infrequently
std::this_thread::sleep_for(std::chrono::seconds(5));
```

### Managing the Monitoring List

Files can be added to or removed from the monitoring list dynamically:

```cpp
// Adding a new file
bool success = observer.add("/path/to/new/file.dat");
if (!success) {
    // The file is already in the monitoring list
}

// Removing a file from monitoring
bool removed = observer.remove("/path/to/old/file.log");
if (!removed) {
    // The file was not found in the monitoring list
}
```

## UML

<img width="944" alt="Снимок экрана 2025-04-14 в 12 49 09" src="https://github.com/user-attachments/assets/9923eb9c-9750-404e-8636-fae2fc9fcacf" />

