library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ROM is
	generic(
	       addr_width: integer := 8;
			 instruction_width: integer  := 16;
			 mif: string := "ROM_file.mif"
			 );
			 
	port(
		 addr: in std_logic_vector(addr_width - 1 downto 0);
		 instruction: out std_logic_vector(instruction_width - 1 downto 0)
		 );
end ROM;

architecture behavior of ROM is
	type ROM_node is array(0 to 2**addr_width - 1) of std_logic_vector(instruction_width - 1 downto 0);
	signal ROM: ROM_node;
	attribute ram_init_file: string;
	attribute ram_init_file of ROM: signal is mif;
begin
	process (addr, ROM)
	begin
		instruction	<= ROM(to_integer(unsigned(addr)));
	end process;
end behavior;