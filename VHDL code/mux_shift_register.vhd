library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity mux_shift_reg is
	port(
	    a: in std_logic;
		 b: in std_logic;
		 s: in std_logic;
		 output: out std_logic
		 );
end mux_shift_reg;

architecture behavior of mux_shift_reg is
begin
	process (a, b, s)
	begin
		if s = '0' then
			output <= a;
		else
			output <= b;
		end if;
	end process;
end behavior;