library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity mux is
	generic(
	       n: integer := 4
	       );
	port(
	    a: in std_logic_vector(n-1 downto 0);
		 b: in std_logic_vector(n-1 downto 0);
		 s: in std_logic;
		 output: out std_logic_vector(n-1 downto 0)
		 );
end mux;

architecture behavior of mux is
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