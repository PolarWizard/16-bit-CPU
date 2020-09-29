library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity arithmetic_logic_unit is
	generic(
			 n: integer := 16
			 );
	port(
		 A, B: in std_logic_vector(n-1 downto 0);
		 opcode: in std_logic_vector(3 downto 0);
		 result: out std_logic_vector(n-1 downto 0);
		 clk: in std_logic;
		 preset: in std_logic; --0 = no preset, 1 = preset
		 cmp: out std_logic
		 );
end arithmetic_logic_unit;

architecture behavior of arithmetic_logic_unit is

signal arith_q: std_logic_vector(n-1 downto 0);
signal logic_q: std_logic_vector(n-1 downto 0);

begin
	
	Arithmetic_Shift: entity work.binary_shift_cluster_ARITHMETIC generic map(
																									 n => n
																									 )
																						  port map(
																									 shift_right_left => opcode(0), --0 = right, 1 = left
																									 preset_no_yes => preset,
																									 preset => A,
																									 clk => clk,
																									 q => arith_q
																									 );
																	 
	Logical_Shift: entity work.binary_shift_cluster_LOGICAL generic map(
																							 n => n
																							 )
																				  port map(
																							 shift_right_left => opcode(0),
																							 preset_no_yes => preset,
																							 preset => A,
																							 clk => clk,
																							 q => logic_q
																							 );
	
	process (A, B, opcode, arith_q, logic_q)
	begin
		result <= (others => '0');
		cmp <= '0';
		case opcode is
			when "0001" => --addition
				result <= std_logic_vector(signed(A) + signed(B));
			when "0010" => --subtraction
				result <= std_logic_vector(signed(A) - signed(B));
			when "0011" => --AND
				result <= A and B;
			when "0100" => --XOR
				result <= A xor B;
			when "0101" => --NOT
				result <= not A;
			when "1001" => --ASL
				result <= arith_q;
			when "1010" => --ASR
				result <= arith_q;
			when "1011" => --LSL
				result <= logic_q;
			when "1100" => --LSR
				result <= logic_q;
			when "0111" => --CMP
				if A = B then
					cmp <= '0';
				else
					cmp <= '1';
				end if;
			when others =>  
				result <= (others => '0');
				cmp <= '0';
		end case;
	end process;
end behavior;