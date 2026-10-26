# CMake generated Testfile for 
# Source directory: C:/Users/albas/OneDrive/Documentos/GitHub/MSoA-1-/Nori2/ext/openexr/IlmBase/ImathTest
# Build directory: C:/Users/albas/OneDrive/Documentos/GitHub/MSoA-1-/Nori2/build/ext_build/openexr/IlmBase/ImathTest
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(IlmBase.Imath "C:/Users/albas/OneDrive/Documentos/GitHub/MSoA-1-/Nori2/build/bin/Debug/ImathTest.exe")
  set_tests_properties(IlmBase.Imath PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/albas/OneDrive/Documentos/GitHub/MSoA-1-/Nori2/ext/openexr/IlmBase/ImathTest/CMakeLists.txt;37;add_test;C:/Users/albas/OneDrive/Documentos/GitHub/MSoA-1-/Nori2/ext/openexr/IlmBase/ImathTest/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(IlmBase.Imath "C:/Users/albas/OneDrive/Documentos/GitHub/MSoA-1-/Nori2/build/bin/Release/ImathTest.exe")
  set_tests_properties(IlmBase.Imath PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/albas/OneDrive/Documentos/GitHub/MSoA-1-/Nori2/ext/openexr/IlmBase/ImathTest/CMakeLists.txt;37;add_test;C:/Users/albas/OneDrive/Documentos/GitHub/MSoA-1-/Nori2/ext/openexr/IlmBase/ImathTest/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(IlmBase.Imath "C:/Users/albas/OneDrive/Documentos/GitHub/MSoA-1-/Nori2/build/bin/MinSizeRel/ImathTest.exe")
  set_tests_properties(IlmBase.Imath PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/albas/OneDrive/Documentos/GitHub/MSoA-1-/Nori2/ext/openexr/IlmBase/ImathTest/CMakeLists.txt;37;add_test;C:/Users/albas/OneDrive/Documentos/GitHub/MSoA-1-/Nori2/ext/openexr/IlmBase/ImathTest/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(IlmBase.Imath "C:/Users/albas/OneDrive/Documentos/GitHub/MSoA-1-/Nori2/build/bin/RelWithDebInfo/ImathTest.exe")
  set_tests_properties(IlmBase.Imath PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/albas/OneDrive/Documentos/GitHub/MSoA-1-/Nori2/ext/openexr/IlmBase/ImathTest/CMakeLists.txt;37;add_test;C:/Users/albas/OneDrive/Documentos/GitHub/MSoA-1-/Nori2/ext/openexr/IlmBase/ImathTest/CMakeLists.txt;0;")
else()
  add_test(IlmBase.Imath NOT_AVAILABLE)
endif()
