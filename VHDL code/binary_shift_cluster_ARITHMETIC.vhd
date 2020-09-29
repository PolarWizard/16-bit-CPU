library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity binary_shift_cluster_ARITHMETIC is
	generic( 
			 n: integer := 8
			 );
	port(
		 shift_right_left: in std_logic; --0 = shift right, 1 = shift left
		 preset_no_yes: in std_logic; --0 = disable preset, 1 = enable preset
		 preset: in std_logic_vector(n-1 downto 0);
		 clk: in std_logic;
		 q: out std_logic_vector(n-1 downto 0)
		 );
end binary_shift_cluster_ARITHMETIC;

architecture parameterized of binary_shift_cluster_ARITHMETIC is

signal qHold: std_logic_vector(n-1 downto 0);

begin
	BSC: for i in 0 to n-1 generate
		LSB: if i = 0 generate
			bit0: entity work.binary_shift_unit port map(
																	  clk => clk,
																	  left_in => qHold(i + 1),
																	  right_in => '0',
																	  preset => preset(i),
																	  shift_right_left => shift_right_left,
																	  preset_no_yes => preset_no_yes,
																	  q => qHold(i)
																	  );
		end generate;
																		
		middle_bits: if ( (i > 0) and (i < n-1) )	generate
			middle: entity work.binary_shift_unit port map(
																		 clk => clk,
																		 left_in => qHold(i + 1),
																		 right_in => qHold(i - 1),
																		 preset => preset(i),
																		 shift_right_left => shift_right_left,
																		 preset_no_yes => preset_no_yes,
																		 q => qHold(i)
																	    );
		end generate;
		
		MSB: if i = n-1 generate
			bitx: entity work.binary_shift_unit port map(
															 		  clk => clk,
																	  left_in => qHold(i) and '1',
																	  right_in => qHold(i - 1),
																	  preset => preset(i),
																	  shift_right_left => shift_right_left,
																	  preset_no_yes => preset_no_yes,
																	  q => qHold(i)
																	  );
		end generate;
	end generate;

	q <= qHold;
	
end parameterized;