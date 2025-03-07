# File-monitoring

### 1. Постановка задачи
 Написать программу с консольным интерфейсом, которая выполняет слежение за выбранными файлами.

Ограничимся  двумя характеристиками за изменениями которых выполняется слежение  :

> 1. Существование файла;
> 2. Размер файла.

Программа будет выводить на консоль уведомление о произошедших изменениях в файле.

Существует несколько ситуаций для наблюдаемого файла:

> 1. Файл существует , файл не  пустой - на экран выводится факт  существования файла и его  размер.
> 2. Файл существует, файл был изменен - на экран выводится факт существования файла, сообщение о том что файл был изменен и его размер.  
> 3. Файл не существует - на экран выводится информация о том что файл не существует.

При возникновении изменения состояния наблюдаемого файла ( возникновение события ), необходимо выводить на экран соответствующее сообщение.

В данной реализации используем механизм сигнально-слотового соединения для обеспечения обработки события изменения наблюдаемого файла.

### 2. Предлагаемое решение.

Для решения данной задачи была использована сигнально-слотовая связь, между двумя основными сущностями проекта: 
 1. FileObserver, который испускает сигналы, при изменении состояния файла/файлов
 2. IFileLog(интерфейс), который имеет слоты - они и будут принимать сигналы. 

**Сигналы и слоты** 

*Сигналы в FileObserver*
```cpp
signals:
    void fileExist(const QString &path, qint64 size);
    void fileChanged(const QString &path, qint64 size);
    void fileNotExist(const QString &path);
```

*Слоты в IFileLog*
```cpp
public slots:
    virtual void fileExist(const QString &path, qint64 size) = 0;
    virtual void fileChanged(const QString &path, qint64 size) = 0;
    virtual void fileNotExist(const QString &path) = 0;
```

Сигнально-слотовая связь настраивается в классе FileObserver, в методе setLogger(IFileLog*). 
При этом заранее проверяется, не передан ли нулевой указатель IFileLog. В этом случае сигналы и слоты связываться не будут. 
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

**Консольный интерфейс**

В задаче было условие написать программу с консольным интерфейсом, поэтому был создан порожденный класс от IFileLog - ConsoleFileLog, он и отвечает за логирование изменений файла/файлов в консоль.

*Пример реализации логирования в консоль*
```cpp
void ConsoleFileLog::fileExist(const QString &path, const qint64 size) {
    std::cout << "File " << path.toStdString() << " changed size to " << size << std::endl;
}
```

**Паттерны проектирования** 

Был реализован пораждающий паттерн проектирования Singleton(одиночка) для класса FileObserver, реализация данного паттерна находится во ветвлении от develop - в ветке addingSingleton. Одиночка использован для гарантии того, что у FileObserver будет только один экземпляр, который будет доступен *по ссылке* через static метод класса Instance(). В этом методе используется "ленивая" инициализация объекта типа FileObserver. 
```cpp
FileObserver& FileObserver::Instance() {
    static FileObserver observer;
    return observer;
}
```
Итак, у нас есть метод для полчения ссылки на экземпляр класса, теперь нужно запретить создание новых объектов, для этого конструктор(по умолчанию, с аргументом) и деструктор были вынесены в private. 
```cpp
private:
    FileObserver(IFileLog *logger = nullptr);
    ~FileObserver() override = default;
```

Также удалены способы копирования(конструктор копирования, оператор присваивания), это сделано через оператор delete, который запрещает любое копирование объектов типа FileObserver.

```cpp
 FileObserver(const FileObserver &other) = delete;
 FileObserver& operator = (const FileObserver &other) = delete;
```

