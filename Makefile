CXX := ccache $(CXX)
CC := ccache $(CC)
ODB := odb
OUT_DIR := build
INSTALL_DIR := ~/public_html/cpp_odb_soap/
EXECUTABLE := $(OUT_DIR)/cpp_odb_soap.cgi
GSOAP_ROOT_DIR := /usr/share/gsoap/
GSOAP_PLUGIN_DIR := $(GSOAP_ROOT_DIR)/plugin
GSOAP_IMPORT_DIR := $(GSOAP_ROOT_DIR)/import
ALL_CPP_FILES := $(wildcard *.cpp)
ALL_HH_FILES := $(wildcard *.hh)
ALL_C_FILES := $(wildcard *.c)
COMPILERFLAGS := -fdiagnostics-color=always -W -Wall -Wno-unused-parameter
STATIC_LIBS :=  /usr/lib/zbcl/libzbcl.a /usr/lib/`uname -i`-linux-gnu/libcrypt.a
INCLUDE_DIRS :=  -I. -I$(OUT_DIR) -I$(GSOAP_ROOT_DIR) -I$(GSOAP_PLUGIN_DIR) -I/usr/include/zbcl
LDFLAGS := -lgsoap++ -lgsoapssl++ -lcrypt -lpthread -lssl -lcrypto -lboost_filesystem -lboost_iostreams -lboost_signals -lboost_system -lpam
CXXFLAGS := $(COMPILERFLAGS) -std=c++11 -g -D WITH_IPV6 -DWITH_OPENSSL $(INCLUDE_DIRS)
CFLAGS := $(COMPILERFLAGS) -g -D WITH_IPV6 -DWITH_OPENSSL $(INCLUDE_DIRS)
ODBFLAGS := -D ODB --hxx-suffix .hh --cxx-suffix .cpp --std c++11 -d common -m dynamic -I . -I $(GSOAP_IMPORT_DIR) -o $(OUT_DIR)
GENERATED_SOURCE_FILES := $(OUT_DIR)/soapC.cpp $(OUT_DIR)/soapServer.cpp
#GENERATED_SOURCE_FILES := $(wildcard build/*.cpp)
ALL_SOURCE_FILES := $(ALL_CPP_FILES) $(ALL_C_FILES) $(GENERATED_SOURCE_FILES)
#ALL_OBJECT_FILES := $(addprefix $(OUT_DIR)/, $(ALL_CPP_FILES:.cpp=.o))
#ALL_OBJECT_FILES := $(ALL_SOURCE_FILES:.cpp=.o)
ALL_OBJECT_FILES := $(ALL_CPP_FILES:%.cpp=$(OUT_DIR)/%.cpp.o) $(ALL_C_FILES:%.c=$(OUT_DIR)/%.c.o) $(GENERATED_SOURCE_FILES:.cpp=.o)
#wsseapi.o
all: $(EXECUTABLE)
odb_files: $(ALL_HH_FILES) | $(OUT_DIR)
	$(ODB) $(ODBFLAGS) $(ALL_HH_FILES)
#$(EXECUTABLE): $(OUT_DIR) $(ALL_SOURCE_FILES)
#	g++ $(CXXFLAGS) -o $@ $(ALL_SOURCE_FILES) $(LDFLAGS)
$(EXECUTABLE): $(ALL_OBJECT_FILES) | $(OUT_DIR)
	$(CXX) -std=c++11 -o $@ $(ALL_OBJECT_FILES) $(LDFLAGS) $(STATIC_LIBS)
$(OUT_DIR):
	mkdir -p $(OUT_DIR)
$(OUT_DIR)/soapC.cpp $(OUT_DIR)/soapServer.cpp: panelsoap.h
	soapcpp2 -2 -b -x -SL -d$(OUT_DIR) -I$(GSOAP_IMPORT_DIR) -c++11 $<
$(OUT_DIR)/wsseapi.o: $(GSOAP_PLUGIN_DIR)/wsseapi.cpp
$(OUT_DIR)/%.cpp.o: %.cpp | $(OUT_DIR)
	$(CXX) -c $(CXXFLAGS) $< -o $@
$(OUT_DIR)/%.c.o: %.c | $(OUT_DIR)
	$(CC) -c $(CFLAGS) $< -o $@
$(ALL_OBJECT_FILES): $(ALL_SOURCE_FILES) | $(OUT_DIR)
mrproper: clean
clean:
	-rm -rf $(OUT_DIR) *.o
install: $(EXECUTABLE)
	mkdir -p $(INSTALL_DIR)
	cp -a $(OUT_DIR)/*.wsdl $(OUT_DIR)/*.xsd $(INSTALL_DIR)
	cp -a $(EXECUTABLE) $(INSTALL_DIR)

uninstall:
	-rm -rvf $(INSTALL_DIR)
print:
	@echo $(ALL_SOURCE_FILES)
	@echo $(ALL_OBJECT_FILES)

