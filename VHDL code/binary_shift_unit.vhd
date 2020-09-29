library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity binary_shift_unit is
	port(
	    clk: in std_logic;
		 preset: in std_logic;
		 left_in, right_in: in std_logic;
		 shift_right_left, preset_no_yes: in std_logic;
		 q: out std_logic
		 );
end binary_shift_unit;

architecture rtl of binary_shift_unit is

signal mux_output_direction: std_logic;
signal mux_output_preset:  std_logic;

begin
	mux_preset: entity work.mux_shift_reg port map(
															 a => left_in,
															 b => right_in,
															 s => shift_right_left,
															 output => mux_output_direction
															 );
	mux_shift: entity work.mux_shift_reg port map(
															 a => '0',
															 b => preset,
															 s => preset_no_yes,
															 output => mux_output_preset
															 );
	binary_shift_register:  entity work.shift_register port map(
																				  clk => clk,
																				  preset => mux_output_preset,
																				  d => mux_output_direction,
																				  q => q
																				  );
end rtl;									
	