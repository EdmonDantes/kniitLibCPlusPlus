# Changelog

## [0.3.9] - 2021-03-06
### Added
- Class `Status`
- - Method `checkMask`
- - Method `getValue`
- - Operator `=` for `T`
- Class `TestContext` for pretty testing    
### Changed
- Class `Status`
- - Set `explicit` constructor from `T`
- Class `Number`
- - Using class `Status` instead `uint8` for field `status`
- - Using compile time expression for compute size for field `number`    
### Removed
- Class `Number`
- - Method `checkNumber`
- - Method `checkMask`    


## [0.3.8] - 2021-02-22
### Fixed
- Fixed building for linux operation system.
- Using self types for library classes.
- Optimize `reverse()` method in `List` class

### Changed
- Change some definitions in `core.h`
- Change names in enum `ByteOrder`
- Changed namespace name from `kniitLibrary` to `kniit_library`


## [0.3.6] - 2021-02-13
### Changed
- Change delimiters arguments in `ReaderInputStream` methods

### Added
- Override method `what` in class `Exception`
- Add method `getMessage` in class `Exception`. It possible to add different count of tabs 
- Add method `find` to `List`
- Add class `DelimiterStrategy`
- Add methods `readHex`, `readNumberList`, `readList` in `ReaderInputStream`
- Add pretty printers in lldb debugger

## [0.3.5] - 2021-02-05
### Fixed
- Fixed `Number` internal storage for value

### Changed
- Optimize `Number` copy constructor
- Changed sizeof type for temporary storage for number in `readNumber()` in `ReaderInputStream`

### Added
- Added private construct in `String` for pre init internal storage
- Added implementation for `toLower()` and `toUpper()` for `String`
- Added implementation for `readColor()` in `ReaderInputStream`
