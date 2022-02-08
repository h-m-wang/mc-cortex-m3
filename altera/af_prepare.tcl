set AGM_SUPRA true
load_package flow

if { ! [is_project_open] } {
  if { [llength $quartus(args)] == 0 } {
    return false
  } else {
    project_open [lindex $quartus(args) 0]
  }
}


### Setup IP ###
set IPLIST { alta_bram alta_bram9k alta_sram alta_pll alta_pllx alta_pllv alta_pllve alta_boot alta_osc alta_mult alta_ufm alta_ufms alta_ufml alta_i2c alta_spi alta_irda alta_mcu alta_mcu_m3 alta_saradc }
proc set_alta_partition {inst tag} {
  set full_name [get_name_info -observable_type pre_synthesis -info full_path $inst]
  set inst_name [get_name_info -observable_type pre_synthesis -info short_full_path $inst]
  set base_name [get_name_info -observable_type pre_synthesis -info instance_name $inst]
  set section_id [string map { [ _ ] _ . _ | _} $inst_name]
  catch {
    eval "set_global_assignment -name PARTITION_COLOR 52377 -section_id $section_id -tag $tag";
    eval "set_global_assignment -name PARTITION_NETLIST_TYPE SOURCE -section_id $section_id -tag $tag";
    eval "set_global_assignment -name PARTITION_FITTER_PRESERVATION_LEVEL PLACEMENT_AND_ROUTING -section_id $section_id -tag $tag";
    eval "set_instance_assignment -name PARTITION_HIERARCHY $section_id -to $full_name -section_id $section_id -tag $tag";
    eval "set_global_assignment -name EDA_MAINTAIN_DESIGN_HIERARCHY PARTITION_ONLY -section_id eda_simulation"
  }
}
set tag alta_auto
if { [llength $IPLIST] > 0 } {
  catch {
    eval "remove_all_global_assignments -name PARTITION_COLOR -tag $tag";
    eval "remove_all_global_assignments -name PARTITION_NETLIST_TYPE -tag $tag";
    eval "remove_all_global_assignments -name PARTITION_FITTER_PRESERVATION_LEVEL -tag $tag";
    eval "remove_all_instance_assignments -name PARTITION_HIERARCHY -tag $tag";
  }

  execute_module -tool map;
  foreach ip $IPLIST {
    foreach_in_collection inst [get_names -node_type hierarchy -observable_type pre_synthesis -filter "$ip:*"] {
      set_alta_partition $inst $tag
    }
    foreach_in_collection inst [get_names -node_type hierarchy -observable_type pre_synthesis -filter "*|$ip:*"] {
      set_alta_partition $inst $tag
    }
  }
}


### Setup ModelSim ###
set_global_assignment -name EDA_SIMULATION_TOOL "ModelSim (Verilog)"

### Setup Timing Derate ###
set_global_assignment -name SDC_FILE "./af_prepare.sdc"

### Run Compile and ###
set PIN_MAP "C:/altera/20180608/etc/AG16KSDE176.pinmap"
set VE_FILE "E:/00_Workspace/0608_AG16KSDE176_DemoBoard/src/top.ve"
if { [file exists $VE_FILE] && [file exist $PIN_MAP] } {
  puts "Processing $VE_FILE with $PIN_MAP"
  set pin_map [open $PIN_MAP r]
  while { [gets $pin_map line] >= 0 } {
    set words [regexp -all -inline {\S+} $line]
    if { [llength $words] >= 2 } {
      set pin_map_arr([lindex $words 0]) [lindex $words 1]
    }
  }
  set ve_file [open $VE_FILE r]
  while { [gets $ve_file line] >= 0 } {
    set words [regexp -all -inline {\S+} $line]
    if { [llength $words] >= 2 } {
      set pin [lindex $words 0]
      set loc [lindex $words 1]
      if { [string index $pin 0] == "#" } {
        continue
      }
      if { [info exists pin_map_arr($loc)] } {
        set_location_assignment $pin_map_arr($loc) -to $pin
      }
    }
  }
}
export_assignments -reorganize
execute_flow -compile

