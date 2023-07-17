onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /tb/clock
add wave -noupdate /tb/reset
add wave -noupdate -divider Controle
add wave -noupdate /tb/start
add wave -noupdate /tb/op
add wave -noupdate -radix unsigned /tb/DUT/op_reg
add wave -noupdate -radix unsigned /tb/DUT/count_left
add wave -noupdate -radix unsigned /tb/DUT/count_right
add wave -noupdate -radix unsigned /tb/DUT/count_test
add wave -noupdate -radix unsigned /tb/DUT/pos_1
add wave -noupdate -radix unsigned /tb/DUT/add_zero
add wave -noupdate -radix unsigned /tb/DUT/remove_zero
add wave -noupdate -radix unsigned /tb/DUT/calculo_test
add wave -noupdate -radix unsigned /tb/DUT/igual_test
add wave -noupdate -divider Estados
add wave -noupdate -radix unsigned /tb/DUT/EA
add wave -noupdate -divider Dados
add wave -noupdate -radix binary /tb/data_a
add wave -noupdate -radix binary /tb/DUT/data_a_reg
add wave -noupdate -radix binary /tb/DUT/expoente_a
add wave -noupdate -radix unsigned /tb/DUT/signal_A
add wave -noupdate -radix binary /tb/data_b
add wave -noupdate -radix binary /tb/DUT/data_b_reg
add wave -noupdate -radix binary /tb/DUT/expoente_b
add wave -noupdate -radix unsigned /tb/DUT/signal_B
add wave -noupdate -radix unsigned /tb/DUT/deslocamento
add wave -noupdate -radix binary /tb/DUT/operador_wire
add wave -noupdate -radix binary /tb/DUT/resultado_wire
add wave -noupdate -radix binary /tb/DUT/operador_total
add wave -noupdate -radix binary /tb/DUT/resultado
add wave -noupdate -radix binary /tb/DUT/data_o_reg
add wave -noupdate -radix unsigned /tb/DUT/arredondamento
add wave -noupdate -radix unsigned /tb/DUT/expoente_maior
add wave -noupdate /tb/DUT/signal_Resultado
add wave -noupdate -divider Saida
add wave -noupdate -radix unsigned /tb/DUT/data_o
add wave -noupdate /tb/DUT/busy
add wave -noupdate /tb/DUT/ready


TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {911 ns} 0}
quietly wave cursor active 1
configure wave -namecolwidth 150
configure wave -valuecolwidth 100
configure wave -justifyvalue left
configure wave -signalnamewidth 1
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ps
update
WaveRestoreZoom {0 ns} {32130 ns}
