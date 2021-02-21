# KNIIT library
![Build check](https://github.com/EdmonDantes/kniitLibCPlusPlus/workflows/Build%20check/badge.svg)
## English
### Support coding
`ReaderInputStream` and `WriterOutputStream` support `UTF-16LE`, `UTF-16BE` and `UTF-8`
### Core
All header in this library import main header with name `core.h`

For configure this header before import header you can set some parameters with `#define` precompile derictive 

* `KNIIT_LIB_EXTERN_C_PLUS_PLUS` - `extern "C"` will be replace to `extern "C++"`,
* `KNIIT_LIB_IMPORT` - use `dllimport` instead `dllexport`,
* `KNIIT_LIB_DISABLE_AUTO_DETECT_OS` - disable auto detect operation system. You must add `KNIIT_LIB_USE_WIN` or `KNIIT_LIB_USE_UNIX`,
* `KNIIT_LIB_DISABLE_AUTO_DETECT_ARCHITECTURE` - disable auto detect computer's architecture. You must add `KNIIT_LIB_USE_X64` or `KNIIT_LIB_USE_X32`,
* `KNIIT_LIB_DISABLE_MAX_TYPES` - remove library max types (like `uintmax` and `intmax`),
* `KNIIT_LIB_DEFAULT_BYTE_ORDER_LITTLE_ENDIAN` - little endian will use for default byte order,
* `NO_BODY` - add after method in classes without body.
### Namespace
All classes and data were contained in special namespace. 

You can use `using KNIIT_LIB_NAMESPACE` or `using namespace KNIIT_LIB_NAMESPACE_NAME`

### ReaderInputStream
#### Import
`#include "data/reader_input_stream.h`
#### Create
`auto reader = ReaderInputStream("fileForRead": string);`
### WriterOutputStream
#### Import
`#include "data/writer_output_stream.h`
#### Create
`auto writer = WriterOutputStream("fileForWrite": string, isAppendFile: bool)`





## Russian
### Поддерживаемые кодировки
`ReaderInputStream` и `WriterOutputStream` поддерживаю `UTF-16LE`, `UTF-16BE` и `UTF-8`
### Ядро
Все заголовочные файлы в этой библиотеки импортирую главный заголовочный файл с именем `core.h`

Для того чтобы сконфигурировать это заголовочный файл вы можете установить несколько параметров с помощью директивы препроцессора `#define`

* `KNIIT_LIB_EXTERN_C_PLUS_PLUS` - `extern "C"` будет заменено на `extern "C++"`,
* `KNIIT_LIB_IMPORT` - использование `dllimport` вместо `dllexport`,
* `KNIIT_LIB_DISABLE_AUTO_DETECT_OS` - отключение автоопределение типа операционной системы. Вы должны добавить `KNIIT_LIB_USE_WIN` или `KNIIT_LIB_USE_UNIX`,
* `KNIIT_LIB_DISABLE_AUTO_DETECT_ARCHITECTURE` - отключение автоопределение типа архитектуры компьютера. Вы должны добавить `KNIIT_LIB_USE_X64` или `KNIIT_LIB_USE_X32`,
* `KNIIT_LIB_DISABLE_MAX_TYPES` - удаление библиотечных максимальных типов (таких как `uintmax` и `intmax`),
* `KNIIT_LIB_DEFAULT_BYTE_ORDER_LITTLE_ENDIAN` - порядок байтов little endian будет использоваться по-умолчанию
* `NO_BODY` - добавляется после методов не имеющих тела метода
### Пространство имён
Все классы и данные находяться в специальном пространстве имён

Вы можете использовать `using KNIIT_LIB_NAMESPACE` или `using namespace KNIIT_LIB_NAMESPACE_NAME`

### ReaderInputStream
#### Импорт
`#include "data/reader_input_stream.h`
#### Создание
`auto reader = ReaderInputStream("fileForRead": string);`
### WriterOutputStream
#### Импорт
`#include "data/writer_output_stream.h`
#### Создание
`auto writer = WriterOutputStream("fileForWrite": string, isAppendFile: bool)`
