# CMake generated Testfile for 
# Source directory: C:/Users/albas/OneDrive/Documentos/GitHub/MSoA-1-/Nori2/ext/openexr/IlmBase/IexTest
# Build directory: C:/Users/albas/OneDrive/Documentos/GitHub/MSoA-1-/Nori2/build/ext_build/openexr/IlmBase/IexTest
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(IlmBase.Iex "C:/Users/albas/OneDrive/Documentos/GitHub/MSoA-1-/Nori2/build/bin/Debug/IexTest.exe")
  set_tests_properties(IlmBase.Iex PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/albas/OneDrive/Documentos/GitHub/MSoA-1-/Nori2/ext/openexr/IlmBase/IexTest/CMakeLists.txt;16;add_test;C:/Users/albas/OneDrive/Documentos/GitHub/MSoA-1-/Nori2/ext/openexr/IlmBase/IexTest/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(IlmBase.Iex "C:/Users/albas/OneDrive/Documentos/GitHub/MSoA-1-/Nori2/build/bin/Release/IexTest.exe")
  set_tests_properties(IlmBase.Iex PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/albas/OneDrive/Documentos/GitHub/MSoA-1-/Nori2/ext/openexr/IlmBase/IexTest/CMakeLists.txt;16;add_test;C:/Users/albas/OneDrive/Documentos/GitHub/MSoA-1-/Nori2/ext/openexr/IlmBase/IexTest/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(IlmBase.Iex "C:/Users/albas/OneDrive/Documentos/GitHub/MSoA-1-/Nori2/build/bin/MinSizeRel/IexTest.exe")
  set_tests_properties(IlmBase.Iex PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/albas/OneDrive/Documentos/GitHub/MSoA-1-/Nori2/ext/openexr/IlmBase/IexTest/CMakeLists.txt;16;add_test;C:/Users/albas/OneDrive/Documentos/GitHub/MSoA-1-/Nori2/ext/openexr/IlmBase/IexTest/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(IlmBase.Iex "C:/Users/albas/OneDrive/Documentos/GitHub/MSoA-1-/Nori2/build/bin/RelWithDebInfo/IexTest.exe")
  set_tests_properties(IlmBase.Iex PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/albas/OneDrive/Documentos/GitHub/MSoA-1-/Nori2/ext/openexr/IlmBase/IexTest/CMakeLists.txt;16;add_test;C:/Users/albas/OneDrive/Documentos/GitHub/MSoA-1-/Nori2/ext/openexr/IlmBase/IexTest/CMakeLists.txt;0;")
else()
  add_test(IlmBase.Iex NOT_AVAILABLE)
endif()
