library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity useq is
	generic(
			 mif: string := "uROM_file.mif"
			 );
	port(
		 clk: in std_logic;
		 opcode: in std_logic_vector(3 downto 0);
		 uop: out std_logic_vector(11 downto 0)
		 );
end useq;

architecture structural of useq is

signal uPC_output: std_logic_vector(5 downto 0);
signal uAR_output: std_logic_vector(5 downto 0);
signal uROM_output: std_logic_vector(18 downto 0);
--uROM_output signal diverging
signal uROM_MAP: std_logic;
signal uROM_next_addr: std_logic_vector(5 downto 0);
begin
	uMUX: entity work.mux generic map(n => 6)
									port map(
									        a => uROM_next_addr, --0
											  b  => opcode & "00", --1
											  s => uROM_MAP, --if 0 then next uROM addr from ROM, if 1 then MAP to the instruction
											  output => uPC_output
											  );
											  
	uPC: entity work.d_ff generic map(n => 6)
									 port map(	
											   clk => clk,
												preset => (others => '0'),
												d => uPC_output,
												q => uAR_output
												);
												
	uROM: entity work.ROM generic map(
                                    addr_width => 6,
											   instruction_width => 19, --each addr location is 19 bits wide
											   mif => mif
											   )
									 port map(
											   addr => uAR_output,
											   instruction => uROM_output
											   );

	uROM_MAP <= uROM_output(6);
	uop <= uROM_output(18 downto 7);
	uROM_next_addr <= uROM_output(5 downto 0);
	
end structural;
