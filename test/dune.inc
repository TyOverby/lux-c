(rule
 (alias lint)
 (deps
  main.c
  ../test_harness.h
  ../../cpu/lux_cpu.c
  ../../cpu/lux_cpu.h
  ../../shared/lux.h
  ../../shared/lux_priv.h
  ../../compile_flags.txt
  (glob_files ../../utilities/stb/*.h))
 (action
  (run
   clang
   -fsyntax-only
   -I../../utilities/stb
   %{read-lines:../../compile_flags.txt}
   main.c
   ../../cpu/lux_cpu.c)))

; compile the test executable
(rule
 (targets main.exe)
 (deps
  main.c
  ../test_harness.h
  ../../cpu/lux_cpu.c
  ../../shared/lux_priv.c
  ../../shared/lux.h
  ../../shared/lux_priv.h
  ../../cpu/lux_cpu.h
  (glob_files ../../utilities/stb/*.h))
 (action
  (run
   clang
   -O2
   %{read-lines:../test_cc_flags.txt}
   -o %{targets}
   %{read-lines:../test_sources.txt})))

; generate comparison rules (diff workflow: run --auto-promote to sync)
(rule
 (with-stdout-to dune.inc.gen
  (run ./main.exe --generate-comparisons)))

(rule
 (alias runtest)
 (action (diff dune.inc dune.inc.gen)))

; --- sanitizer builds ---

(rule
 (targets main-asan.exe)
 (deps
  main.c
  ../test_harness.h
  ../../cpu/lux_cpu.c
  ../../shared/lux_priv.c
  ../../shared/lux.h
  ../../shared/lux_priv.h
  ../../cpu/lux_cpu.h
  (glob_files ../../utilities/stb/*.h))
 (action
  (run
   clang
   %{read-lines:../test_sanitizer_flags.txt}
   -fsanitize=address
   %{read-lines:../test_cc_flags.txt}
   -o %{targets}
   %{read-lines:../test_sources.txt})))

(rule
 (targets main-ubsan.exe)
 (deps
  main.c
  ../test_harness.h
  ../../cpu/lux_cpu.c
  ../../shared/lux_priv.c
  ../../shared/lux.h
  ../../shared/lux_priv.h
  ../../cpu/lux_cpu.h
  (glob_files ../../utilities/stb/*.h))
 (action
  (run
   clang
   %{read-lines:../test_sanitizer_flags.txt}
   -fsanitize=undefined
   %{read-lines:../test_cc_flags.txt}
   -o %{targets}
   %{read-lines:../test_sources.txt})))

; msan: Linux only (Apple clang doesn't support -fsanitize=memory)
(rule
 (targets main-msan.exe)
 (enabled_if (= %{system} linux))
 (deps
  main.c
  ../test_harness.h
  ../../cpu/lux_cpu.c
  ../../shared/lux_priv.c
  ../../shared/lux.h
  ../../shared/lux_priv.h
  ../../cpu/lux_cpu.h
  (glob_files ../../utilities/stb/*.h))
 (action
  (run
   clang
   %{read-lines:../test_sanitizer_flags.txt}
   -fsanitize=memory
   %{read-lines:../test_cc_flags.txt}
   -o %{targets}
   %{read-lines:../test_sources.txt})))

(rule
 (alias runtest)
 (deps main-asan.exe)
 (action (run ./main-asan.exe --no-images)))

(rule
 (alias runtest)
 (deps main-ubsan.exe)
 (action (run ./main-ubsan.exe --no-images)))

(rule
 (alias runtest)
 (enabled_if (= %{system} linux))
 (deps main-msan.exe)
 (action (run ./main-msan.exe --no-images)))
