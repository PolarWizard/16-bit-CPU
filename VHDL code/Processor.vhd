library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Processor is
	port(
	    sys_clk: in std_logic;
		 PC_out: out std_logic_vector(7 downto 0);
		 ROM_out: out std_logic_vector(15 downto 0);
		 IR_out: out std_logic_vector(3 downto 0);
		 useq_out: out std_logic_vector(11 downto 0);
		 mux1_out: out std_logic_vector(2 downto 0);
		 mux2_out: out std_logic_vector(15 downto 0);
		 DR_out: out std_logic_vector(15 downto 0);
		 AC_out: out std_logic_vector(15 downto 0);
		 ALU_cmp_out: out std_logic;
		 ALU_result_out: out std_logic_vector(15 downto 0);
		 RAM_out: out std_logic_vector(15 downto 0)
		 );
end Processor;

architecture structural of Processor is

--output from components
signal output_from_pc: std_logic_vector(7 downto 0);
signal output_from_AR: std_logic_vector(7 downto 0);
signal output_from_ROM: std_logic_vector(15 downto 0);
signal output_from_IR: std_logic_vector(3 downto 0);
signal output_from_DR: std_logic_vector(15 downto 0);
signal output_from_AC: std_logic_vector(15 downto 0);
signal output_from_ALU_result: std_logic_vector(15 downto 0);
signal output_from_ALU_cmp: std_logic;
signal output_from_RAM: std_logic_vector(15 downto 0);
signal output_from_mux1: std_logic_vector(2 downto 0);
signal output_from_mux2: std_logic_vector(15 downto 0);

--control signals
signal control_signals: std_logic_vector(11 downto 0);

begin
	PC: entity work.counter generic map(n => 8)
	                        port map(
											  clk => sys_clk,
									        clr => control_signals(10),
											  load => output_from_ALU_cmp or control_signals(11),
											  increment => control_signals(9),
											  address_in => output_from_ROM(7 downto 0),
											  q => output_from_pc
											  );							  
											  
	AR: entity work.d_ff generic map(n => 8)
								port map(
								        clk => control_signals(8),
										  preset => (others => '0'),
										  d => output_from_pc,
										  q => output_from_AR
										  );			 
										 
	ROM_memory: entity work.ROM port map(
													addr => output_from_AR,
													instruction => output_from_ROM
													);								
													
	IR: entity work.d_ff generic map(n => 4)
	                     port map(
								        clk => control_signals(7),
										  preset => (others => '0'),
										  d => output_from_ROM(15 downto 12),
										  q => output_from_IR
										  );
	
	uSequencer: entity work.useq generic map(mif => "uROM_file.mif")
	                             port map(
													 clk => sys_clk,
													 opcode => output_from_IR,
													 uop => control_signals
													 );
													 
	DR: entity work.register_node port map(
													  clk => sys_clk,
													  write_enable => control_signals(4),
													  write_to_register => output_from_ROM(11 downto 9),
													  read_register => output_from_mux1,
													  dataIn => output_from_mux2,
													  register_dataOut => output_from_DR
													  );
													  
	AC: entity work.d_ff generic map(n => 16)
                        port map(
							           clk => control_signals(6),
										  preset => (others => '0'),
										  d => output_from_DR,
										  q => output_from_AC
										  );
										  
	ALU: entity work.arithmetic_logic_unit generic map(n => 16)
														port map(
															     A => output_from_AC,
																  B => output_from_DR,
																  opcode => output_from_IR,
																  result => output_from_ALU_result,
																  clk => sys_clk,
																  preset => control_signals(5),
																  cmp => output_from_ALU_cmp
																  );
							
	RAM_memory: entity work.RAM port map(
													clk => sys_clk,
												   addr => output_from_ROM(7 downto 0),
												   dataIn => output_from_DR,
												   read_enable => control_signals(3),
													write_enable => control_signals(2),
												   dataOut => output_from_RAM
												   );	
							
	mux1: entity work.mux generic map(n => 3)
								 port map(
											a => output_from_ROM(8 downto 6),
											b => output_from_ROM(11 downto 9),
											s => control_signals(1),
											output => output_from_mux1
											);	
						
	mux2: entity work.mux generic map(n => 16)
								 port map(
											a => output_from_RAM,
											b => output_from_ALU_result,
											s => control_signals(0),
											output => output_from_mux2
											);		
															
	PC_out <= output_from_pc;
	ROM_out <= output_from_ROM;
	IR_out <= output_from_IR;
   useq_out <= control_signals;
	mux1_out <= output_from_mux1;
   mux2_out <= output_from_mux2;
   DR_out <= output_from_DR;
	AC_out <= output_from_AC;
	ALU_cmp_out <= output_from_ALU_cmp;
	ALU_result_out <= output_from_ALU_result;
	RAM_out <= output_from_RAM;
		 												 
end structural;
										  
										         
	
								
								        
	
												
												
	     