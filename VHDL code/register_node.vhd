library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity register_node is
	port(
	    clk: in std_logic;
		 write_enable: in std_logic;
		 write_to_register: in std_logic_vector(2 downto 0);
		 read_register: in std_logic_vector(2 downto 0);
		 dataIn: in std_logic_vector(15 downto 0);
		 register_dataOut: out std_logic_vector(15 downto 0)
		 );
end register_node;

architecture rtl of register_node is

type register_array is array (0 to 7) of std_logic_vector(15 downto 0);
signal which_register: register_array; 

begin
	process (clk, write_enable, write_to_register, read_register, dataIn)
	begin
		if rising_edge(clk) then
			if write_enable = '1' then
				which_register(to_integer(unsigned(write_to_register))) <= dataIn;
			end if;
		end if;
	end process;
	register_dataOut <= which_register(to_integer(unsigned(read_register)));
end rtl;	