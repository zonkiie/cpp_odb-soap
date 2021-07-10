# cpp_odb-soap
Example for combining ODB and GSOAP in C++ 

# Required: libboost-filesystem for filesize detection

# Links
(https://stackoverflow.com/questions/42306646/gsoap-serialized-xml-to-string)[https://stackoverflow.com/questions/42306646/gsoap-serialized-xml-to-string]

## How to start with code generation etc
The best strategy currenty is to take my example project and modify it, until the tutorial is complete.
Also, use my Makefile.
I will optimize this tutorial in the next time.
Finding the solution cost me many try & error, so I try to explain the way so that others can work with my experience.
### 1. Create Entities (Header and Source Files)
When using smart pointers, it is highly recommened to define own types with typedefs, otherwise odb will create duplicated functions, definitions etc.
Define friend odb class access with [] brackets as transient, because soapcpp2 will otherwise throw errors.
Use data types which are known by both soapcpp2 and odb. This is the main problem of the combination of these two code genrators. You can only use classes or data types, which are known to both genrators.
It is possible to include other headers in entities.hh and entities-pragmas.hh . In entities.hh, we have to #import other header files, while in entities-pragmas.hh, we have to #include other header files. If distributing dependend classes, you maybe have to forward-declare classes which are not yet known to the compiler.
### 2. Create Pragmas in external File
soapcpp2 will not recognise pragmas, even if they are defined as transient (with the '[]' brackets). So put the pragmas in an external file. The odb Compiler allows to append Pragmas when compiling.
### 3. Create Functions
Sometimes getter and setter are not used, I'll try to find out why.
### 4. Generate Soap Code

    OUT_DIR := build
    GSOAP_ROOT_DIR := /usr/share/gsoap/
    GSOAP_PLUGIN_DIR := $(GSOAP_ROOT_DIR)/plugin
    GSOAP_IMPORT_DIR := $(GSOAP_ROOT_DIR)/import
    soapcpp2 -2 -b -x -SL -d$(OUT_DIR) -I$(GSOAP_IMPORT_DIR) -c++11 soap_functions.hh

This is already implemented in my Makefile.
### 5. Generate ODB Code from generated Soap Code
The trick here is to create odb code from code generated by soapcpp2. Additional Included headers can be defined via command line.

    odb --hxx-suffix .hh --cxx-suffix .cpp --std c++11 -d common -d pgsql -d mysql -d sqlite -m dynamic --generate-query --generate-schema  --generate-session -I . -I $(GSOAP_IMPORT_DIR) -o $(OUT_DIR) --odb-epilogue '#include "entities-pragmas.hh"' $(OUT_DIR)/soapStub.h
This is also already implemented in my Makefile.
### 6. Create Main File and support files etc
A good staring point should be my main.cpp file, which can call every c and c++ soap function defined in soap_functions.hh.
### 7. Compile everything
To use my Makefile, you need to install and configure ccache, the compiler cache. If you have to compile a code very often, you will be very happy about this cache.

The best is to look to the example code ans Makefile it it's not explained in this README file.

Note: Don't add -lgsoap -lgsoapssl to LDLIBS because it creates undefined symbols.

## Problems which might be unsolvable
### 1. Lazy loading
When creating cyclic or self referencing objects, parent objects are sent via soap. So it seems to create endless loading, bit it's not endless loading. It's read for some levels from the Result Cache, so the database roundtrips are keept to a minimum. (It's in strong contrast to PHP's doctrine ORM, which loads really infinitely.) As we can't use every datatype, it's maybe unsolvable. The transfered data amount is larger than needed, so we have here a little inefficiency.
If using smart pointers on return variables, there is no unneccessary data transfer.

### 2. Memory Leak
In this example, there is a small memory leak of 386 Bytes per query. The solution is hard to find. If no programmable solution is possible, one solution would be to restart the process if memory usage is too large.

## Testing
The Test Program is a PHP script, because PHP has a very easy-to-use SOAP Client and with print_r we can see the structures result.
To debug memory errors, use the memory debugger valgrind.

Use this command line to check the Server process for memory errors:
    valgrind --show-leak-kinds=all --leak-check=full --track-origins=yes ./build/cpp_odb_soap.cgi --port=8080
If you want to log the results into a text file, set 
	--log-file=logfile.txt
as valgrind option.
If you want to increase the function call stack, set
    --num-callers=<num>
as another valgrind option.
Open another terminal window, chage to this project's php subdir and call
    php main.php

