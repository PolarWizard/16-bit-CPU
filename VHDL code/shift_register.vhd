library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity shift_register is
	port(
		 clk: in std_logic;
		 preset: in std_logic;
		 d: in std_logic;
		 q: out std_logic
		 );
end shift_register;

architecture behavior of shift_register is
begin
	process (clk, d, preset)
	begin
		if rising_edge(clk) then
			if preset = '1' then
				q <= '1';
			else
				q <= d;
			end if;
		end if;
	end process;
end behavior;
