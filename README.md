## Rundown
A header only, C++14 implementation of the Boost::Optional library.

Optional objects wrap any type and allow them to occupy a 'null' state. The
status of the object can be queried with an explicit bool conversion. If true,
the Optional object is valid and can be accessed through a dereference. If
false, the object is in a null(empty) state.

## Code Example
    opt::Optional<int> opt_int;
    if (opt_int) {
        std::cout << "This is never reached.\n";
    } else {
        *opt_int += 7;
    }

    opt::Optional<std::string> opt_str{"Hello, World!"};
    if (opt_str) {
        std::cout << *opt_str << " is " << opt_str->size() << " bytes long.\n";
    } else {
        std::cout << "This is never reached.\n";
    }

    opt::Optional<char> opt_char{opt::none};
    if (!opt_char) {
        std::cout << "opt_char was initialized empty with opt::none.\n";
    }

## Motivation
This class wrapper is useful when a default constructed object, or 'zero', or
any other valid state is not sufficient to convey the idea of empty, or
non-existant.

This particular implementation was largly created for personal practice. It is
also used by the [TWidgets Framework](
https://github.com/a-n-t-h-o-n-y/TWidgets).

## Installation
This is a header only library, copying the contents of the include/ directory
to whichever destination folder you desire will work fine.

If you wish to run the tests, use cmake to setup the build environment by
running `cmake ..` from the build/ directory. From here you can run `make
tests` to create the test executable and `make install` to install the headers
to a location specified in [CMakeLists.txt](CMakeLists.txt).

## Wiki
This project utilizes the [GitHub wiki pages](
https://github.com/a-n-t-h-o-n-y/Optional/wiki). These contain more information
on the specifics of using the library.

## Documentation
Doxygen documentation can be found [here](
https://a-n-t-h-o-n-y.github.io/Optional/).

The documentation can also be generated by running `make docs`, output will
appear in the docs/ folder.

## Tests
This library uses the google testing framework. After setting up the build/
directory with cmake, run `make test`. The test executable will be create in
the bin/ directory.

## Contributions
All help is welcome, add your contribution to this project by creating a pull
request. Append your name to the [CONTRIBUTORS.md](CONTRIBUTORS.md) file as
well. Issues and questions can be directed to the GitHub issue tracker.

## License
This software is distributed under the [MIT License](LICENSE.txt).
