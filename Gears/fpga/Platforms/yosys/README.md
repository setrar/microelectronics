

```sh
# Step 1: Clean old crap (optional but recommended)
brew uninstall yosys ghdl
sudo rm -rf /usr/local/bin/yosys /usr/local/bin/ghdl
sudo rm -rf /usr/local/lib/libghdl* /usr/local/share/yosys

# Step 2: Install prerequisites
brew install gnat llvm bison flex cmake

# Step 3: Build GHDL from source
git clone https://github.com/ghdl/ghdl.git
cd ghdl
./configure --prefix=/usr/local --enable-synth --enable-libghdl --with-llvm-config=/opt/homebrew/opt/llvm@15/bin/llvm-config
make -j$(sysctl -n hw.logicalcpu)
sudo make install

# Step 4: Build Yosys from source
cd ..
git clone https://github.com/YosysHQ/yosys.git
cd yosys
git submodule update --init --recursive
# explicitly use clang and clang++ instead of gcc/g++ as the C and C++ compilers.
make ENABLE_GHDL=1 CC=clang CXX=clang++ -j$(sysctl -n hw.logicalcpu)
sudo make install

# Step 5: Verify
which yosys
yosys -m ghdl
```

```
make ENABLE_GHDL=1 CC=clang CXX=clang++ -j$(sysctl -n hw.logicalcpu) GHDL=/usr/local/bin/ghdl
```
>
```powershell
$BREW_PREFIX is [/opt/homebrew/opt]
[  0%] Building kernel/version_3d1f2161d.cc
[  0%] Building kernel/driver.o
[  0%] Building techlibs/common/simlib_help.inc
[  0%] Building techlibs/common/simcells_help.inc
[  1%] Building kernel/rtlil.o
[  1%] Building kernel/log.o
[  1%] Building kernel/calc.o
[  1%] Building kernel/yosys.o
[  2%] Building kernel/io.o
[  2%] Building kernel/gzip.o
[  2%] Building kernel/binding.o
kernel/rtlil.cc:2380:27: warning: 'get_blackbox_attribute' is deprecated: Use Module::get_blackbox_attribute() instead. [-Wdeprecated-declarations]
                        log_assert(!it.second->get_blackbox_attribute());
                                               ^
./kernel/rtlil.h:871:4: note: 'get_blackbox_attribute' has been explicitly marked deprecated here
        [[deprecated("Use Module::get_blackbox_attribute() instead.")]]
          ^
[  3%] Building kernel/tclapi.o
[  3%] Building kernel/cellaigs.o
[  3%] Building kernel/celledges.o
[  3%] Building kernel/cost.o
kernel/tclapi.cc:209:3: warning: ignoring return value of function declared with 'warn_unused_result' attribute [-Wunused-result]
                mp_neg(a, a);
                ^~~~~~ ~~~~
kernel/tclapi.cc:210:3: warning: ignoring return value of function declared with 'warn_unused_result' attribute [-Wunused-result]
                mp_sub_d(a, 1, a);
                ^~~~~~~~ ~~~~~~~
kernel/tclapi.cc:215:2: warning: ignoring return value of function declared with 'warn_unused_result' attribute [-Wunused-result]
        mp_to_unsigned_bin(a, buf.data());
        ^~~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~
kernel/tclapi.cc:281:34: warning: object backing the pointer will be destroyed at the end of the full-expression [-Wdangling-gsl]
                Tcl_SetResult(interp, (char *) obj->get_string_attribute(attr_id).c_str(), TCL_VOLATILE);
                                               ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/opt/homebrew/Cellar/tcl-tk/9.0.0_1/include/tcl-tk/tclDecls.h:3967:29: note: expanded from macro 'Tcl_SetResult'
            const char *__result = result; \
                                   ^~~~~~
kernel/tclapi.cc:297:34: warning: object backing the pointer will be destroyed at the end of the full-expression [-Wdangling-gsl]
                Tcl_SetResult(interp, (char *) obj->attributes.at(attr_id).as_string().c_str(), TCL_VOLATILE);
                                               ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/opt/homebrew/Cellar/tcl-tk/9.0.0_1/include/tcl-tk/tclDecls.h:3967:29: note: expanded from macro 'Tcl_SetResult'
            const char *__result = result; \
                                   ^~~~~~
kernel/tclapi.cc:343:33: warning: object backing the pointer will be destroyed at the end of the full-expression [-Wdangling-gsl]
        Tcl_SetResult(interp, (char *) std::to_string(obj->has_attribute(attr_id)).c_str(), TCL_VOLATILE);
                                       ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/opt/homebrew/Cellar/tcl-tk/9.0.0_1/include/tcl-tk/tclDecls.h:3967:29: note: expanded from macro 'Tcl_SetResult'
            const char *__result = result; \
                                   ^~~~~~
kernel/tclapi.cc:467:34: warning: object backing the pointer will be destroyed at the end of the full-expression [-Wdangling-gsl]
                Tcl_SetResult(interp, (char *) value.decode_string().c_str(), TCL_VOLATILE);
                                               ^~~~~~~~~~~~~~~~~~~~~
/opt/homebrew/Cellar/tcl-tk/9.0.0_1/include/tcl-tk/tclDecls.h:3967:29: note: expanded from macro 'Tcl_SetResult'
            const char *__result = result; \
                                   ^~~~~~
kernel/tclapi.cc:474:34: warning: object backing the pointer will be destroyed at the end of the full-expression [-Wdangling-gsl]
                Tcl_SetResult(interp, (char *) value.as_string().c_str(), TCL_VOLATILE);
                                               ^~~~~~~~~~~~~~~~~
/opt/homebrew/Cellar/tcl-tk/9.0.0_1/include/tcl-tk/tclDecls.h:3967:29: note: expanded from macro 'Tcl_SetResult'
            const char *__result = result; \
                                   ^~~~~~
[  4%] Building kernel/satgen.o
8 warnings generated.
[  4%] Building kernel/scopeinfo.o
[  4%] Building kernel/qcsat.o
[  5%] Building kernel/mem.o
[  5%] Building kernel/ffmerge.o
[  5%] Building kernel/ff.o
[  5%] Building kernel/yw.o
[  6%] Building kernel/json.o
[  6%] Building kernel/fmt.o
[  6%] Building kernel/sexpr.o
[  6%] Building kernel/drivertools.o
[  7%] Building kernel/functional.o
[  7%] Building kernel/fstdata.o
[  7%] Building libs/bigint/BigIntegerAlgorithms.o
[  8%] Building libs/bigint/BigInteger.o
[  8%] Building libs/bigint/BigIntegerUtils.o
[  8%] Building libs/bigint/BigUnsigned.o
[  8%] Building libs/bigint/BigUnsignedInABase.o
[  9%] Building libs/sha1/sha1.o
[  9%] Building libs/json11/json11.o
[  9%] Building libs/ezsat/ezsat.o
[ 10%] Building libs/ezsat/ezminisat.o
[ 10%] Building libs/minisat/Options.o
[ 10%] Building libs/minisat/SimpSolver.o
[ 10%] Building libs/minisat/Solver.o
[ 11%] Building libs/minisat/System.o
[ 11%] Building libs/fst/fstapi.o
[ 11%] Building libs/fst/fastlz.o
[ 11%] Building libs/fst/lz4.o
[ 12%] Building libs/subcircuit/subcircuit.o
[ 12%] Building frontends/aiger/aigerparse.o
[ 12%] Building frontends/aiger2/xaiger.o
[ 13%] Building frontends/ast/ast.o
[ 13%] Building frontends/ast/simplify.o
[ 13%] Building frontends/ast/genrtlil.o
[ 13%] Building frontends/ast/dpicall.o
[ 14%] Building frontends/ast/ast_binding.o
[ 14%] Building frontends/blif/blifparse.o
1 warning generated.
[ 14%] Building frontends/json/jsonparse.o
[ 15%] Building frontends/liberty/liberty.o
[ 15%] Building frontends/rpc/rpc_frontend.o
[ 15%] Building frontends/rtlil/rtlil_parser.tab.cc
[ 15%] Building frontends/rtlil/rtlil_lexer.cc
[ 16%] Building frontends/rtlil/rtlil_frontend.o
[ 16%] Building frontends/verific/verific.o
[ 16%] Building frontends/verilog/verilog_parser.tab.cc
[ 17%] Building frontends/verilog/preproc.o
[ 17%] Building frontends/verilog/verilog_frontend.o
[ 17%] Building frontends/verilog/const2ast.o
[ 18%] Building passes/cmds/exec.o
[ 18%] Building passes/cmds/add.o
[ 18%] Building passes/cmds/delete.o
[ 18%] Building passes/cmds/design.o
[ 19%] Building passes/cmds/select.o
[ 19%] Building passes/cmds/show.o
[ 19%] Building passes/cmds/viz.o
[ 20%] Building passes/cmds/rename.o
[ 20%] Building passes/cmds/autoname.o
[ 20%] Building passes/cmds/connect.o
[ 20%] Building passes/cmds/scatter.o
[ 21%] Building passes/cmds/setundef.o
[ 21%] Building passes/cmds/splitnets.o
[ 21%] Building passes/cmds/splitcells.o
[ 22%] Building passes/cmds/stat.o
[ 22%] Building passes/cmds/internal_stats.o
[ 22%] Building passes/cmds/setattr.o
[ 22%] Building passes/cmds/copy.o
[ 23%] Building passes/cmds/splice.o
[ 23%] Building passes/cmds/scc.o
[ 23%] Building passes/cmds/glift.o
[ 23%] Building passes/cmds/torder.o
[ 24%] Building passes/cmds/logcmd.o
[ 24%] Building passes/cmds/tee.o
[ 24%] Building passes/cmds/write_file.o
[ 25%] Building passes/cmds/connwrappers.o
[ 25%] Building passes/cmds/cover.o
[ 25%] Building passes/cmds/trace.o
[ 25%] Building passes/cmds/plugin.o
[ 26%] Building passes/cmds/check.o
[ 26%] Building passes/cmds/edgetypes.o
[ 26%] Building passes/cmds/portlist.o
[ 27%] Building passes/cmds/chformal.o
[ 27%] Building passes/cmds/chtype.o
[ 27%] Building passes/cmds/blackbox.o
[ 27%] Building passes/cmds/ltp.o
[ 28%] Building passes/cmds/bugpoint.o
[ 28%] Building passes/cmds/scratchpad.o
[ 28%] Building passes/cmds/logger.o
[ 28%] Building passes/cmds/printattrs.o
[ 29%] Building passes/cmds/sta.o
[ 29%] Building passes/cmds/clean_zerowidth.o
[ 29%] Building passes/cmds/xprop.o
[ 30%] Building passes/cmds/dft_tag.o
[ 30%] Building passes/cmds/future.o
[ 30%] Building passes/cmds/box_derive.o
[ 30%] Building passes/cmds/example_dt.o
[ 31%] Building passes/cmds/portarcs.o
[ 31%] Building passes/cmds/wrapcell.o
[ 31%] Building passes/cmds/setenv.o
[ 32%] Building passes/cmds/abstract.o
[ 32%] Building passes/cmds/test_select.o
[ 32%] Building passes/cmds/timeest.o
[ 32%] Building passes/equiv/equiv_make.o
[ 33%] Building passes/equiv/equiv_miter.o
[ 33%] Building passes/equiv/equiv_simple.o
[ 33%] Building passes/equiv/equiv_status.o
[ 33%] Building passes/equiv/equiv_add.o
[ 34%] Building passes/equiv/equiv_remove.o
[ 34%] Building passes/equiv/equiv_induct.o
[ 34%] Building passes/equiv/equiv_struct.o
[ 35%] Building passes/equiv/equiv_purge.o
[ 35%] Building passes/equiv/equiv_mark.o
[ 35%] Building passes/equiv/equiv_opt.o
[ 35%] Building passes/fsm/fsm.o
[ 36%] Building passes/fsm/fsm_detect.o
[ 36%] Building passes/fsm/fsm_extract.o
[ 36%] Building passes/fsm/fsm_opt.o
[ 37%] Building passes/fsm/fsm_expand.o
[ 37%] Building passes/fsm/fsm_recode.o
[ 37%] Building passes/fsm/fsm_info.o
[ 37%] Building passes/fsm/fsm_export.o
[ 38%] Building passes/fsm/fsm_map.o
[ 38%] Building passes/hierarchy/hierarchy.o
[ 38%] Building passes/hierarchy/uniquify.o
[ 39%] Building passes/hierarchy/submod.o
[ 39%] Building passes/hierarchy/keep_hierarchy.o
[ 39%] Building passes/memory/memory.o
[ 39%] Building passes/memory/memory_dff.o
[ 40%] Building passes/memory/memory_share.o
[ 40%] Building passes/memory/memory_collect.o
[ 40%] Building passes/memory/memory_unpack.o
[ 40%] Building passes/memory/memory_bram.o
[ 41%] Building passes/memory/memory_map.o
[ 41%] Building passes/memory/memory_memx.o
[ 41%] Building passes/memory/memory_nordff.o
[ 42%] Building passes/memory/memory_narrow.o
[ 42%] Building passes/memory/memory_libmap.o
[ 42%] Building passes/memory/memory_bmux2rom.o
[ 42%] Building passes/memory/memlib.o
[ 43%] Building passes/opt/opt.o
[ 43%] Building passes/opt/opt_merge.o
[ 43%] Building passes/opt/opt_mem.o
[ 44%] Building passes/opt/opt_mem_feedback.o
[ 44%] Building passes/opt/opt_mem_priority.o
[ 44%] Building passes/opt/opt_mem_widen.o
[ 44%] Building passes/opt/opt_muxtree.o
[ 45%] Building passes/opt/opt_reduce.o
[ 45%] Building passes/opt/opt_dff.o
[ 45%] Building passes/opt/opt_share.o
[ 45%] Building passes/opt/opt_clean.o
[ 46%] Building passes/opt/opt_expr.o
[ 46%] Building passes/opt/share.o
[ 46%] Building passes/opt/wreduce.o
[ 47%] Building passes/opt/opt_demorgan.o
[ 47%] Building passes/opt/rmports.o
[ 47%] Building passes/opt/opt_lut.o
[ 47%] Building passes/opt/opt_lut_ins.o
[ 48%] Building passes/opt/opt_ffinv.o
[ 48%] Building passes/opt/pmux2shiftx.o
[ 48%] Building passes/opt/peepopt_pm.h
[ 48%] Building passes/opt/muxpack.o
[ 48%] Building passes/pmgen/test_pmgen_pm.h
[ 48%] Building techlibs/ice40/ice40_dsp_pm.h
[ 48%] Building techlibs/xilinx/xilinx_srl_pm.h
[ 49%] Building passes/proc/proc.o
[ 49%] Building passes/proc/proc_prune.o
[ 50%] Building passes/proc/proc_clean.o
[ 50%] Building passes/proc/proc_rmdead.o
[ 50%] Building passes/proc/proc_init.o
[ 50%] Building passes/proc/proc_arst.o
[ 51%] Building passes/proc/proc_rom.o
[ 51%] Building passes/proc/proc_mux.o
[ 51%] Building passes/proc/proc_dlatch.o
[ 52%] Building passes/proc/proc_dff.o
[ 52%] Building passes/proc/proc_memwr.o
[ 52%] Building passes/sat/sat.o
[ 52%] Building passes/sat/freduce.o
[ 53%] Building passes/sat/eval.o
[ 53%] Building passes/sat/sim.o
[ 53%] Building passes/sat/miter.o
[ 54%] Building passes/sat/expose.o
[ 54%] Building passes/sat/assertpmux.o
[ 54%] Building passes/sat/clk2fflogic.o
[ 54%] Building passes/sat/async2sync.o
[ 55%] Building passes/sat/formalff.o
[ 55%] Building passes/sat/supercover.o
[ 55%] Building passes/sat/fmcombine.o
[ 56%] Building passes/sat/mutate.o
[ 56%] Building passes/sat/cutpoint.o
[ 56%] Building passes/sat/fminit.o
[ 56%] Building passes/sat/recover_names.o
[ 57%] Building passes/sat/qbfsat.o
[ 57%] Building passes/sat/synthprop.o
[ 57%] Building passes/techmap/flatten.o
[ 57%] Building passes/techmap/techmap.o
[ 58%] Building passes/techmap/simplemap.o
[ 58%] Building passes/techmap/dfflibmap.o
[ 58%] Building passes/techmap/maccmap.o
[ 59%] Building passes/techmap/booth.o
[ 59%] Building passes/techmap/libparse.o
[ 59%] Building passes/techmap/libcache.o
[ 59%] Building passes/techmap/abc.o
[ 60%] Building passes/techmap/abc9.o
[ 60%] Building passes/techmap/abc9_exe.o
[ 60%] Building passes/techmap/abc9_ops.o
[ 61%] Building passes/techmap/abc_new.o
[ 61%] Building passes/techmap/iopadmap.o
[ 61%] Building passes/techmap/clkbufmap.o
[ 61%] Building passes/techmap/hilomap.o
[ 62%] Building passes/techmap/extract.o
[ 62%] Building passes/techmap/extract_fa.o
[ 62%] Building passes/techmap/extract_counter.o
[ 62%] Building passes/techmap/extract_reduce.o
[ 63%] Building passes/techmap/alumacc.o
[ 63%] Building passes/techmap/dffinit.o
[ 63%] Building passes/techmap/pmuxtree.o
[ 64%] Building passes/techmap/bmuxmap.o
[ 64%] Building passes/techmap/demuxmap.o
[ 64%] Building passes/techmap/bwmuxmap.o
[ 64%] Building passes/techmap/muxcover.o
[ 65%] Building passes/techmap/aigmap.o
[ 65%] Building passes/techmap/tribuf.o
[ 65%] Building passes/techmap/lut2mux.o
[ 66%] Building passes/techmap/nlutmap.o
[ 66%] Building passes/techmap/shregmap.o
[ 66%] Building passes/techmap/deminout.o
[ 66%] Building passes/techmap/insbuf.o
[ 67%] Building passes/techmap/bufnorm.o
[ 67%] Building passes/techmap/attrmvcp.o
[ 67%] Building passes/techmap/attrmap.o
[ 67%] Building passes/techmap/zinit.o
passes/techmap/attrmap.cc:266:31: warning: 'selected_whole_modules' is deprecated: Use select_unboxed_whole_modules() to maintain prior behaviour, or consider one of the other selected whole module helpers. [-Wdeprecated-declarations]
                        for (auto module : design->selected_whole_modules())
                                                   ^
./kernel/rtlil.h:1422:4: note: 'selected_whole_modules' has been explicitly marked deprecated here
        [[deprecated("Use select_unboxed_whole_modules() to maintain prior behaviour, or consider one of the other selected whole module helpers.")]]
          ^
[ 68%] Building passes/techmap/dfflegalize.o
[ 68%] Building passes/techmap/dffunmap.o
[ 68%] Building passes/techmap/flowmap.o
[ 69%] Building passes/techmap/extractinv.o
1 warning generated.
[ 69%] Building passes/techmap/cellmatch.o
[ 69%] Building passes/techmap/clockgate.o
[ 69%] Building passes/techmap/constmap.o
[ 70%] Building passes/tests/test_autotb.o
[ 70%] Building passes/tests/test_cell.o
[ 70%] Building passes/tests/test_abcloop.o
[ 71%] Building backends/aiger/aiger.o
[ 71%] Building backends/aiger/xaiger.o
[ 71%] Building backends/aiger2/aiger.o
[ 71%] Building backends/blif/blif.o
[ 72%] Building backends/btor/btor.o
[ 72%] Building backends/cxxrtl/cxxrtl_backend.o
[ 72%] Building backends/edif/edif.o
[ 73%] Building backends/firrtl/firrtl.o
[ 73%] Building backends/functional/cxx.o
[ 73%] Building backends/functional/smtlib.o
[ 73%] Building backends/functional/smtlib_rosette.o
[ 74%] Building backends/functional/test_generic.o
[ 74%] Building backends/intersynth/intersynth.o
[ 74%] Building backends/jny/jny.o
[ 74%] Building backends/json/json.o
[ 75%] Building backends/rtlil/rtlil_backend.o
[ 75%] Building backends/simplec/simplec.o
[ 75%] Building backends/smt2/smt2.o
[ 76%] Building backends/smv/smv.o
[ 76%] Building backends/spice/spice.o
[ 76%] Building backends/table/table.o
[ 76%] Building backends/verilog/verilog_backend.o
[ 77%] Building techlibs/achronix/synth_achronix.o
[ 77%] Building techlibs/anlogic/synth_anlogic.o
[ 77%] Building techlibs/anlogic/anlogic_eqn.o
[ 78%] Building techlibs/anlogic/anlogic_fixcarry.o
[ 78%] Building techlibs/common/synth.o
[ 78%] Building techlibs/common/prep.o
[ 78%] Building techlibs/coolrunner2/synth_coolrunner2.o
[ 79%] Building techlibs/coolrunner2/coolrunner2_sop.o
[ 79%] Building techlibs/coolrunner2/coolrunner2_fixup.o
[ 79%] Building techlibs/easic/synth_easic.o
[ 79%] Building techlibs/ecp5/synth_ecp5.o
[ 80%] Building techlibs/efinix/synth_efinix.o
[ 80%] Building techlibs/efinix/efinix_fixcarry.o
[ 80%] Building techlibs/fabulous/synth_fabulous.o
[ 81%] Building techlibs/gatemate/synth_gatemate.o
[ 81%] Building techlibs/gatemate/gatemate_foldinv.o
[ 81%] Building techlibs/gowin/synth_gowin.o
[ 81%] Building techlibs/greenpak4/synth_greenpak4.o
[ 82%] Building techlibs/greenpak4/greenpak4_dffinv.o
[ 82%] Building techlibs/ice40/synth_ice40.o
[ 82%] Building techlibs/ice40/ice40_braminit.o
[ 83%] Building techlibs/ice40/ice40_opt.o
[ 83%] Building techlibs/ice40/ice40_dsp.o
[ 83%] Building techlibs/ice40/ice40_wrapcarry_pm.h
[ 83%] Building techlibs/intel_alm/synth_intel_alm.o
[ 84%] Building techlibs/intel/synth_intel.o
[ 84%] Building techlibs/lattice/synth_lattice.o
[ 84%] Building techlibs/lattice/lattice_gsr.o
[ 84%] Building techlibs/microchip/synth_microchip.o
[ 85%] Building techlibs/microchip/microchip_dsp_pm.h
[ 85%] Building techlibs/microchip/microchip_dffopt.o
[ 85%] Building techlibs/microchip/microchip_dsp_CREG_pm.h
[ 85%] Building techlibs/microchip/microchip_dsp_cascade_pm.h
[ 85%] Building techlibs/nanoxplore/synth_nanoxplore.o
[ 86%] Building techlibs/nanoxplore/nx_carry.o
[ 86%] Building techlibs/nexus/synth_nexus.o
[ 86%] Building techlibs/quicklogic/synth_quicklogic.o
[ 86%] Building techlibs/quicklogic/ql_bram_merge.o
[ 87%] Building techlibs/quicklogic/ql_bram_types.o
[ 87%] Building techlibs/quicklogic/ql_dsp_simd.o
[ 87%] Building techlibs/quicklogic/ql_dsp_io_regs.o
[ 88%] Building techlibs/quicklogic/ql_ioff.o
[ 88%] Building techlibs/quicklogic/ql_dsp_macc_pm.h
[ 88%] Building techlibs/sf2/synth_sf2.o
[ 88%] Building techlibs/xilinx/synth_xilinx.o
[ 89%] Building techlibs/xilinx/xilinx_dffopt.o
[ 89%] Building techlibs/xilinx/xilinx_dsp_pm.h
[ 89%] Building techlibs/xilinx/xilinx_dsp48a_pm.h
[ 89%] Building techlibs/xilinx/xilinx_dsp_CREG_pm.h
[ 89%] Building techlibs/xilinx/xilinx_dsp_cascade_pm.h
[ 89%] Building techlibs/xilinx/xilinx_srl.o
[ 99%] Building yosys-config
[ 99%] Building passes/techmap/filterlib.o
[ 99%] Building yosys-smtbmc
[ 99%] Building yosys-witness
[ 99%] Building share/include/kernel/binding.h
[ 99%] Building share/include/kernel/bitpattern.h
[ 99%] Building share/include/kernel/cellaigs.h
[ 99%] Building share/include/kernel/celledges.h
[ 99%] Building share/include/kernel/celltypes.h
[ 99%] Building share/include/kernel/consteval.h
[ 99%] Building share/include/kernel/constids.inc
[ 99%] Building share/include/kernel/cost.h
[ 99%] Building share/include/kernel/drivertools.h
[ 99%] Building share/include/kernel/ff.h
[ 99%] Building share/include/kernel/ffinit.h
[ 99%] Building share/include/kernel/ffmerge.h
[ 99%] Building share/include/kernel/fmt.h
[ 99%] Building share/include/kernel/fstdata.h
[ 99%] Building share/include/kernel/gzip.h
[ 99%] Building share/include/kernel/hashlib.h
[ 99%] Building share/include/kernel/io.h
[ 99%] Building share/include/kernel/json.h
[ 99%] Building share/include/kernel/log.h
[ 99%] Building share/include/kernel/macc.h
[ 99%] Building share/include/kernel/modtools.h
[ 99%] Building share/include/kernel/mem.h
[ 99%] Building share/include/kernel/qcsat.h
[ 99%] Building share/include/kernel/register.h
[ 99%] Building share/include/kernel/rtlil.h
[ 99%] Building share/include/kernel/satgen.h
[ 99%] Building share/include/kernel/scopeinfo.h
[ 99%] Building share/include/kernel/sexpr.h
[ 99%] Building share/include/kernel/sigtools.h
[ 99%] Building share/include/kernel/timinginfo.h
[ 99%] Building share/include/kernel/utils.h
[ 99%] Building share/include/kernel/yosys.h
[ 99%] Building share/include/kernel/yosys_common.h
[ 99%] Building share/include/kernel/yw.h
[ 99%] Building share/include/libs/ezsat/ezsat.h
[ 99%] Building share/include/libs/ezsat/ezminisat.h
[ 99%] Building share/include/libs/fst/fstapi.h
[ 99%] Building share/include/libs/sha1/sha1.h
[ 99%] Building share/include/libs/json11/json11.hpp
[ 99%] Building share/include/passes/fsm/fsmdata.h
[ 99%] Building share/include/frontends/ast/ast.h
[ 99%] Building share/include/frontends/ast/ast_binding.h
[ 99%] Building share/include/frontends/blif/blifparse.h
[ 99%] Building share/include/backends/rtlil/rtlil_backend.h
[ 99%] Building share/include/backends/cxxrtl/runtime/cxxrtl/cxxrtl.h
[ 99%] Building share/include/backends/cxxrtl/runtime/cxxrtl/cxxrtl_vcd.h
[ 99%] Building share/include/backends/cxxrtl/runtime/cxxrtl/cxxrtl_time.h
[ 99%] Building share/include/backends/cxxrtl/runtime/cxxrtl/cxxrtl_replay.h
[ 99%] Building share/include/backends/cxxrtl/runtime/cxxrtl/capi/cxxrtl_capi.cc
[ 99%] Building share/include/backends/cxxrtl/runtime/cxxrtl/capi/cxxrtl_capi.h
[ 99%] Building share/include/backends/cxxrtl/runtime/cxxrtl/capi/cxxrtl_capi_vcd.cc
[ 99%] Building share/include/backends/cxxrtl/runtime/cxxrtl/capi/cxxrtl_capi_vcd.h
[ 99%] Building share/python3/smtio.py
[ 99%] Building share/python3/ywio.py
[ 99%] Building share/achronix/speedster22i/cells_sim.v
[ 99%] Building share/achronix/speedster22i/cells_map.v
[ 99%] Building share/anlogic/cells_map.v
[ 99%] Building share/anlogic/arith_map.v
[ 99%] Building share/anlogic/cells_sim.v
[ 99%] Building share/anlogic/eagle_bb.v
[ 99%] Building share/anlogic/lutrams.txt
[ 99%] Building share/anlogic/lutrams_map.v
[ 99%] Building share/anlogic/brams.txt
[ 99%] Building share/anlogic/brams_map.v
[ 99%] Building share/simlib.v
[ 99%] Building share/simcells.v
[ 99%] Building share/techmap.v
[ 99%] Building share/smtmap.v
[ 99%] Building share/pmux2mux.v
[ 99%] Building share/adff2dff.v
[ 99%] Building share/dff2ff.v
[ 99%] Building share/gate2lut.v
[ 99%] Building share/cmp2lut.v
[ 99%] Building share/cells.lib
[ 99%] Building share/mul2dsp.v
[ 99%] Building share/abc9_model.v
[ 99%] Building share/abc9_map.v
[ 99%] Building share/abc9_unmap.v
[ 99%] Building share/cmp2lcu.v
[ 99%] Building share/cmp2softlogic.v
[ 99%] Building share/choices/kogge-stone.v
[ 99%] Building share/choices/han-carlson.v
[ 99%] Building share/choices/sklansky.v
[ 99%] Building share/coolrunner2/cells_latch.v
[ 99%] Building share/coolrunner2/cells_sim.v
[ 99%] Building share/coolrunner2/cells_counter_map.v
[ 99%] Building share/coolrunner2/tff_extract.v
[ 99%] Building share/coolrunner2/xc2_dff.lib
[ 99%] Building share/ecp5/cells_ff.vh
[ 99%] Building share/ecp5/cells_io.vh
[ 99%] Building share/ecp5/cells_map.v
[ 99%] Building share/ecp5/cells_sim.v
[ 99%] Building share/ecp5/cells_bb.v
[ 99%] Building share/ecp5/lutrams_map.v
[ 99%] Building share/ecp5/lutrams.txt
[ 99%] Building share/ecp5/brams_map.v
[ 99%] Building share/ecp5/brams.txt
[ 99%] Building share/ecp5/arith_map.v
[ 99%] Building share/ecp5/latches_map.v
[ 99%] Building share/ecp5/dsp_map.v
[ 99%] Building share/efinix/cells_map.v
[ 99%] Building share/efinix/arith_map.v
[ 99%] Building share/efinix/cells_sim.v
[ 99%] Building share/efinix/brams_map.v
[ 99%] Building share/efinix/gbuf_map.v
[ 99%] Building share/efinix/brams.txt
[ 99%] Building share/fabulous/cells_map.v
[ 99%] Building share/fabulous/prims.v
[ 99%] Building share/fabulous/latches_map.v
[ 99%] Building share/fabulous/ff_map.v
[ 99%] Building share/fabulous/ram_regfile.txt
[ 99%] Building share/fabulous/regfile_map.v
[ 99%] Building share/fabulous/io_map.v
[ 99%] Building share/fabulous/arith_map.v
[ 99%] Building share/gatemate/reg_map.v
[ 99%] Building share/gatemate/mux_map.v
[ 99%] Building share/gatemate/lut_map.v
[ 99%] Building share/gatemate/mul_map.v
[ 99%] Building share/gatemate/arith_map.v
[ 99%] Building share/gatemate/cells_sim.v
[ 99%] Building share/gatemate/cells_bb.v
[ 99%] Building share/gatemate/brams_map.v
[ 99%] Building share/gatemate/brams.txt
[ 99%] Building share/gatemate/brams_init_20.vh
[ 99%] Building share/gatemate/brams_init_40.vh
[ 99%] Building share/gatemate/inv_map.v
[ 99%] Building share/gatemate/lut_tree_cells.genlib
[ 99%] Building share/gatemate/lut_tree_map.v
[ 99%] Building share/gowin/cells_map.v
[ 99%] Building share/gowin/cells_sim.v
[ 99%] Building share/gowin/cells_xtra_gw1n.v
[ 99%] Building share/gowin/cells_xtra_gw2a.v
[ 99%] Building share/gowin/cells_xtra_gw5a.v
[ 99%] Building share/gowin/arith_map.v
[ 99%] Building share/gowin/brams_map.v
[ 99%] Building share/gowin/brams.txt
[ 99%] Building share/gowin/lutrams_map.v
[ 99%] Building share/gowin/lutrams.txt
[ 99%] Building share/greenpak4/cells_blackbox.v
[ 99%] Building share/greenpak4/cells_latch.v
[ 99%] Building share/greenpak4/cells_map.v
[ 99%] Building share/greenpak4/cells_sim.v
[ 99%] Building share/greenpak4/cells_sim_ams.v
[ 99%] Building share/greenpak4/cells_sim_digital.v
[ 99%] Building share/greenpak4/cells_sim_wip.v
[ 99%] Building share/greenpak4/gp_dff.lib
[ 99%] Building share/ice40/arith_map.v
[ 99%] Building share/ice40/cells_map.v
[ 99%] Building share/ice40/ff_map.v
[ 99%] Building share/ice40/cells_sim.v
[ 99%] Building share/ice40/latches_map.v
[ 99%] Building share/ice40/brams.txt
[ 99%] Building share/ice40/brams_map.v
[ 99%] Building share/ice40/spram.txt
[ 99%] Building share/ice40/spram_map.v
[ 99%] Building share/ice40/dsp_map.v
[ 99%] Building share/ice40/abc9_model.v
[ 99%] Building share/intel_alm/common/abc9_map.v
[ 99%] Building share/intel_alm/common/abc9_unmap.v
[ 99%] Building share/intel_alm/common/abc9_model.v
[ 99%] Building share/intel_alm/common/alm_map.v
[ 99%] Building share/intel_alm/common/alm_sim.v
[ 99%] Building share/intel_alm/common/arith_alm_map.v
[ 99%] Building share/intel_alm/common/dff_map.v
[ 99%] Building share/intel_alm/common/dff_sim.v
[ 99%] Building share/intel_alm/common/dsp_sim.v
[ 99%] Building share/intel_alm/common/dsp_map.v
[ 99%] Building share/intel_alm/common/mem_sim.v
[ 99%] Building share/intel_alm/common/misc_sim.v
[ 99%] Building share/intel_alm/cyclonev/cells_sim.v
[ 99%] Building share/intel_alm/common/bram_m10k.txt
[ 99%] Building share/intel_alm/common/bram_m10k_map.v
[ 99%] Building share/intel_alm/common/lutram_mlab.txt
[ 99%] Building share/intel_alm/common/megafunction_bb.v
[ 99%] Building share/intel/common/m9k_bb.v
[ 99%] Building share/intel/common/altpll_bb.v
[ 99%] Building share/intel/common/brams_m9k.txt
[ 99%] Building share/intel/common/brams_map_m9k.v
[ 99%] Building share/intel/common/ff_map.v
[ 99%] Building share/intel/max10/cells_sim.v
[ 99%] Building share/intel/cyclone10lp/cells_sim.v
[ 99%] Building share/intel/cycloneiv/cells_sim.v
[ 99%] Building share/intel/cycloneive/cells_sim.v
[ 99%] Building share/intel/max10/cells_map.v
[ 99%] Building share/intel/cyclone10lp/cells_map.v
[ 99%] Building share/intel/cycloneiv/cells_map.v
[ 99%] Building share/intel/cycloneive/cells_map.v
[ 99%] Building share/lattice/cells_ff.vh
[ 99%] Building share/lattice/cells_io.vh
[ 99%] Building share/lattice/cells_map.v
[ 99%] Building share/lattice/common_sim.vh
[ 99%] Building share/lattice/ccu2d_sim.vh
[ 99%] Building share/lattice/ccu2c_sim.vh
[ 99%] Building share/lattice/cells_sim_ecp5.v
[ 99%] Building share/lattice/cells_sim_xo2.v
[ 99%] Building share/lattice/cells_sim_xo3.v
[ 99%] Building share/lattice/cells_sim_xo3d.v
[ 99%] Building share/lattice/cells_bb_ecp5.v
[ 99%] Building share/lattice/cells_bb_xo2.v
[ 99%] Building share/lattice/cells_bb_xo3.v
[ 99%] Building share/lattice/cells_bb_xo3d.v
[ 99%] Building share/lattice/lutrams_map.v
[ 99%] Building share/lattice/lutrams.txt
[ 99%] Building share/lattice/brams_map_16kd.v
[ 99%] Building share/lattice/brams_16kd.txt
[ 99%] Building share/lattice/brams_map_8kc.v
[ 99%] Building share/lattice/brams_8kc.txt
[ 99%] Building share/lattice/arith_map_ccu2c.v
[ 99%] Building share/lattice/arith_map_ccu2d.v
[ 99%] Building share/lattice/latches_map.v
[ 99%] Building share/lattice/dsp_map_18x18.v
[ 99%] Building share/microchip/arith_map.v
[ 99%] Building share/microchip/cells_map.v
[ 99%] Building share/microchip/cells_sim.v
[ 99%] Building share/microchip/polarfire_dsp_map.v
[ 99%] Building share/microchip/brams_defs.vh
[ 99%] Building share/microchip/LSRAM_map.v
[ 99%] Building share/microchip/LSRAM.txt
[ 99%] Building share/microchip/uSRAM_map.v
[ 99%] Building share/microchip/uSRAM.txt
[ 99%] Building share/nanoxplore/arith_map.v
[ 99%] Building share/nanoxplore/brams_init.vh
[ 99%] Building share/nanoxplore/brams_map.v
[ 99%] Building share/nanoxplore/brams.txt
[ 99%] Building share/nanoxplore/cells_bb.v
[ 99%] Building share/nanoxplore/cells_bb_l.v
[ 99%] Building share/nanoxplore/cells_bb_m.v
[ 99%] Building share/nanoxplore/cells_bb_u.v
[ 99%] Building share/nanoxplore/cells_map.v
[ 99%] Building share/nanoxplore/cells_sim.v
[ 99%] Building share/nanoxplore/cells_sim_l.v
[ 99%] Building share/nanoxplore/cells_sim_m.v
[ 99%] Building share/nanoxplore/cells_sim_u.v
[ 99%] Building share/nanoxplore/cells_wrap.v
[ 99%] Building share/nanoxplore/cells_wrap_l.v
[ 99%] Building share/nanoxplore/cells_wrap_m.v
[ 99%] Building share/nanoxplore/cells_wrap_u.v
[ 99%] Building share/nanoxplore/io_map.v
[ 99%] Building share/nanoxplore/latches_map.v
[ 99%] Building share/nanoxplore/rf_init.vh
[ 99%] Building share/nanoxplore/rf_rams_l.txt
[ 99%] Building share/nanoxplore/rf_rams_m.txt
[ 99%] Building share/nanoxplore/rf_rams_u.txt
[ 99%] Building share/nanoxplore/rf_rams_map_l.v
[ 99%] Building share/nanoxplore/rf_rams_map_m.v
[ 99%] Building share/nanoxplore/rf_rams_map_u.v
[ 99%] Building share/nexus/cells_map.v
[ 99%] Building share/nexus/cells_sim.v
[ 99%] Building share/nexus/parse_init.vh
[ 99%] Building share/nexus/cells_xtra.v
[ 99%] Building share/nexus/lutrams_map.v
[ 99%] Building share/nexus/lutrams.txt
[ 99%] Building share/nexus/brams_map.v
[ 99%] Building share/nexus/brams.txt
[ 99%] Building share/nexus/lrams_map.v
[ 99%] Building share/nexus/lrams.txt
[ 99%] Building share/nexus/arith_map.v
[ 99%] Building share/nexus/latches_map.v
[ 99%] Building share/nexus/dsp_map.v
[ 99%] Building share/quicklogic/common/cells_sim.v
[ 99%] Building share/quicklogic/pp3/ffs_map.v
[ 99%] Building share/quicklogic/pp3/lut_map.v
[ 99%] Building share/quicklogic/pp3/latches_map.v
[ 99%] Building share/quicklogic/pp3/cells_map.v
[ 99%] Building share/quicklogic/pp3/cells_sim.v
[ 99%] Building share/quicklogic/pp3/abc9_model.v
[ 99%] Building share/quicklogic/pp3/abc9_map.v
[ 99%] Building share/quicklogic/pp3/abc9_unmap.v
[ 99%] Building share/quicklogic/qlf_k6n10f/arith_map.v
[ 99%] Building share/quicklogic/qlf_k6n10f/libmap_brams.txt
[ 99%] Building share/quicklogic/qlf_k6n10f/libmap_brams_map.v
[ 99%] Building share/quicklogic/qlf_k6n10f/brams_map.v
[ 99%] Building share/quicklogic/qlf_k6n10f/brams_sim.v
[ 99%] Building techlibs/quicklogic/qlf_k6n10f/bram_types_sim.v
[ 99%] Building share/quicklogic/qlf_k6n10f/cells_sim.v
[ 99%] Building share/quicklogic/qlf_k6n10f/ffs_map.v
[ 99%] Building share/quicklogic/qlf_k6n10f/dsp_sim.v
[ 99%] Building share/quicklogic/qlf_k6n10f/dsp_map.v
[ 99%] Building share/quicklogic/qlf_k6n10f/dsp_final_map.v
[ 99%] Building share/quicklogic/qlf_k6n10f/TDP18K_FIFO.v
[ 99%] Building share/quicklogic/qlf_k6n10f/ufifo_ctl.v
[ 99%] Building share/quicklogic/qlf_k6n10f/sram1024x18_mem.v
[ 99%] Building share/sf2/arith_map.v
[ 99%] Building share/sf2/cells_map.v
[ 99%] Building share/sf2/cells_sim.v
[ 99%] Building share/xilinx/cells_map.v
[ 99%] Building share/xilinx/cells_sim.v
[ 99%] Building share/xilinx/cells_xtra.v
[ 99%] Building share/xilinx/lutrams_xcv.txt
[ 99%] Building share/xilinx/lutrams_xcv_map.v
[ 99%] Building share/xilinx/lutrams_xc5v.txt
[ 99%] Building share/xilinx/lutrams_xcu.txt
[ 99%] Building share/xilinx/lutrams_xc5v_map.v
[ 99%] Building share/xilinx/brams_xcv.txt
[ 99%] Building share/xilinx/brams_xcv_map.v
[ 99%] Building share/xilinx/brams_defs.vh
[ 99%] Building share/xilinx/brams_xc2v.txt
[ 99%] Building share/xilinx/brams_xc2v_map.v
[ 99%] Building share/xilinx/brams_xc3sda.txt
[ 99%] Building share/xilinx/brams_xc3sda_map.v
[ 99%] Building share/xilinx/brams_xc4v.txt
[ 99%] Building share/xilinx/brams_xc4v_map.v
[ 99%] Building share/xilinx/brams_xc5v_map.v
[ 99%] Building share/xilinx/brams_xc6v_map.v
[ 99%] Building share/xilinx/brams_xcu_map.v
[ 99%] Building share/xilinx/urams.txt
[ 99%] Building share/xilinx/urams_map.v
[ 99%] Building share/xilinx/arith_map.v
[ 99%] Building share/xilinx/ff_map.v
[ 99%] Building share/xilinx/lut_map.v
[ 99%] Building share/xilinx/mux_map.v
[ 99%] Building share/xilinx/xc3s_mult_map.v
[ 99%] Building share/xilinx/xc3sda_dsp_map.v
[ 99%] Building share/xilinx/xc6s_dsp_map.v
[ 99%] Building share/xilinx/xc4v_dsp_map.v
[ 99%] Building share/xilinx/xc5v_dsp_map.v
[ 99%] Building share/xilinx/xc7_dsp_map.v
[ 99%] Building share/xilinx/xcu_dsp_map.v
[ 99%] Building share/xilinx/abc9_model.v
[ 99%] Building yosys-abc
[ 99%] Building kernel/version_3d1f2161d.o
[ 99%] Building kernel/register.o
[ 99%] Building frontends/rtlil/rtlil_parser.tab.o
[ 99%] Building frontends/rtlil/rtlil_lexer.o
[ 99%] Building frontends/verilog/verilog_parser.tab.o
[ 99%] Building frontends/verilog/verilog_lexer.cc
[ 99%] Building passes/opt/peepopt.o
[ 99%] Building passes/pmgen/test_pmgen.o
[ 99%] Building techlibs/ice40/ice40_wrapcarry.o
[ 99%] Building techlibs/microchip/microchip_dsp.o
[ 99%] Building techlibs/quicklogic/ql_dsp_macc.o
[ 99%] Building techlibs/xilinx/xilinx_dsp.o
[ 99%] Building yosys-filterlib
ld: warning: ignoring duplicate libraries: '-lc++'
[ 99%] Building share/quicklogic/qlf_k6n10f/bram_types_sim.v
[ 99%] Building frontends/verilog/verilog_lexer.o
[100%] Building yosys
ld: warning: ignoring duplicate libraries: '-lc++'

  Build successful.

```
