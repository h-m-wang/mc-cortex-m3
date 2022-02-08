set derate_sdc "None"
if { "$derate_sdc" == "1.30_0.95" } {
  set_timing_derate -net_delay  -late  1.30
  set_timing_derate -net_delay  -early 1.30
  set_timing_derate -cell_delay -late  0.95
  set_timing_derate -cell_delay -early 0.95
}
if { "$derate_sdc" == "1.20_1.20" } {
  set_timing_derate -net_delay  -late  1.20
  set_timing_derate -cell_delay -early 1.20
  set_timing_derate -net_delay  -late  1.20
  set_timing_derate -cell_delay -early 1.20
}
if { "$derate_sdc" == "1.15_1.15" } {
  set_timing_derate -net_delay  -late  1.15 
  set_timing_derate -cell_delay -early 1.15
  set_timing_derate -net_delay  -late  1.15
  set_timing_derate -cell_delay -early 1.15
}
if { "$derate_sdc" == "1.10_1.10" } {
  set_timing_derate -net_delay  -late  1.10
  set_timing_derate -cell_delay -early 1.10
  set_timing_derate -net_delay  -late  1.10
  set_timing_derate -cell_delay -early 1.10
}

