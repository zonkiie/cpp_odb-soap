# cpp_odb-soap
Example for combining ODB and GSOAP in C++ 

# Required: [libzbcl]{https://zonkiies-big-collection-lib.sourceforge.io/}

## How to start with code generation etc
### 1. Create Entities (Header and Source Files)
When using smart pointers, it is highly recommened to define own types with typedefs, otherwise odb will create duplicated functions, definitions etc.
Define friend odb class access with [] brackets as transient, because soapcpp2 will otherwise throw errors.
Use data types which are known by soapcpp2 and odb.
### 2. Create Pragmas in external File
soapcpp2 will not recognise pragmas, even if they are defined as transient (with the '[]' brackets)
### 3. Create Functions
Sometimes getter and setter are not used, I'll try to find out why.
### 4. Generate Soap Code
### 5. Generate ODB Code from generated Soap Code
### 6. Create Main File and support files etc
### 7. Compile everything
