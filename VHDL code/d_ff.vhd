library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity d_ff is
	generic(
			 n: integer := 8
			 );
	port(
		 clk: in std_logic;
		 preset: in std_logic_vector(n-1 downto 0);
		 d: in std_logic_vector(n-1 downto 0);
		 q: out std_logic_vector(n-1 downto 0)
		 );
end d_ff;

architecture behavior of d_ff is
begin
	process (clk, d, preset)
	begin
		if preset = (preset'range => '1') then
			q <=  (others => '1');
		elsif rising_edge(clk) then
		  	q <= d;
		end if;
	end process;
end behavior;
