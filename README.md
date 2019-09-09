# cpp_odb-soap
Example for combining ODB and GSOAP in C++ 

# Required: [libzbcl](https://zonkiies-big-collection-lib.sourceforge.io/)

## How to start with code generation etc
The best strategy currenty is to take my example project and modify it, until the tutorial is complete.
Also, use my Makefile.
I will optimize this tutorial in the next time.
### 1. Create Entities (Header and Source Files)
When using smart pointers, it is highly recommened to define own types with typedefs, otherwise odb will create duplicated functions, definitions etc.
Define friend odb class access with [] brackets as transient, because soapcpp2 will otherwise throw errors.
Use data types which are known by both soapcpp2 and odb.
It is possible to include other headers in entities.hh and entities-pragmas.hh . In entities.hh, we have to #import other header files, while in entities-pragmas.hh, we have to #include other header files. If distributing dependend classes, you maybe have to forward-declare classes which are not yet known to the compiler.
### 2. Create Pragmas in external File
soapcpp2 will not recognise pragmas, even if they are defined as transient (with the '[]' brackets). So put the pragmas in an external file. The odb Compiler allows to append Pragmas when compiling.
### 3. Create Functions
Sometimes getter and setter are not used, I'll try to find out why.
### 4. Generate Soap Code
### 5. Generate ODB Code from generated Soap Code
### 6. Create Main File and support files etc
### 7. Compile everything

## Problems which might be unsolvable
### 1. Lazy loading
When creating cyclic or self referencing objects, parent objects are sent via soap. So it seems to create endless loading, bit it's not endless loading. It's read for some levels from the Result Cache, so the database roundtrips are keept to a minimum. (It's in strong contrast to PHP's doctrine ORM, which loads really infinitely.) As we can't use every datatype, it's maybe unsolvable. The transfered data amount is larger than needed, so we have here a little inefficiency.

## Testing
The Test Program is a PHP script, because PHP has a very easy-to-use SOAP Client and with print_r we can see the structures result.
