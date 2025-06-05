set proj_name "zc706_proj"
set proj_dir "./${proj_name}"
set part "xc7z045ffg900-2"

create_project $proj_name $proj_dir -part $part -force
set_property BOARD_PART xilinx.com:zc706:part0:1.4 [current_project]

create_bd_design base_design
create_bd_cell -type ip -vlnv xilinx.com:ip:processing_system7:5.5 ps7
set_property -dict [list CONFIG.PCW_USE_M_AXI_GP0 {0}] [get_bd_cells ps7]

validate_bd_design
save_bd_design

# Generate HDL, handoff, etc.
generate_target all [get_files ./zc706_proj/zc706_proj.srcs/sources_1/bd/base_design/base_design.bd]
export_ip_user_files -of_objects [get_files ./zc706_proj/zc706_proj.srcs/sources_1/bd/base_design/base_design.bd] -no_script -sync -force -quiet

# Create wrapper and add to project
make_wrapper -files [get_files ./zc706_proj/zc706_proj.srcs/sources_1/bd/base_design/base_design.bd] -top
add_files -norecurse ./zc706_proj/zc706_proj.gen/sources_1/bd/base_design/hdl/base_design_wrapper.v

set_property platform.name "zc706_minimal" [current_project]
set_property platform.board_id "zc706" [current_project]

# Build wrapper and generate XSA
update_compile_order -fileset sources_1

# launch_runs synth_1 -jobs 4
# wait_on_run synth_1
# write_hw_platform -fixed -force -include_bit -file ./zc706_minimal.xsa

write_hw_platform -fixed -force -file ./zc706_minimal.xsa
