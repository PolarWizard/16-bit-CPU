library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity RAM is
	port(
		 addr: in std_logic_vector(7 downto 0);
		 dataIn: in std_logic_vector(15 downto 0);
		 read_enable, write_enable: in std_logic;
		 clk: in std_logic;
		 dataOut: out std_logic_vector(15 downto 0)
		 );
end RAM;

architecture behavior of RAM is
	type RAM_node is array(0 to 255) of std_logic_vector(15 downto 0);
	signal RAM: RAM_node;
	attribute ram_init_file: string;
	attribute ram_init_file of RAM: signal is "RAM_file.mif";
begin
	process (clk, read_enable, write_enable, dataIn, addr)
	begin
		if rising_edge(clk) then
			if read_enable = '1' then
				dataOut <= RAM(to_integer(unsigned(addr)));
			elsif write_enable = '1' then
				RAM(to_integer(unsigned(addr))) <= dataIn;
			end if;
		end if;
	end process;
end behavior;
				