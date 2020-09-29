library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity counter is
	generic(
			 n: integer := 8
			 );

	port(
		 clk: in std_logic;
		 clr: in std_logic;
		 load: in std_logic;
		 increment: in std_logic;
		 address_in: in std_logic_vector(n-1 downto 0);
		 q: out std_logic_vector(n-1 downto 0)
		 );
end counter;

--counter where priority is clr, load, increment in that order
architecture behavior of counter is
	signal address: unsigned(n-1 downto 0) := (others => '0');
begin
	process (clk, clr, load, increment, address_in)
	begin
		if rising_edge(clk) then
			if clr = '1' then
				address <= (others => '0');
			elsif load = '1' then
				address <= unsigned(address_in);
			elsif increment = '1' then
				address <= address + 1;
			end if;
		end if;
		q <= std_logic_vector(address);
	end process;

end behavior;	
	
	