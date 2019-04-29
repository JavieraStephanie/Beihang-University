--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   18:19:48 11/09/2017
-- Design Name:   
-- Module Name:   D:/HW/JiSuanJiZuCheng/Verilog/splitter/splitter.vhd
-- Project Name:  splitter
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: splitter
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY splitter IS
END splitter;
 
ARCHITECTURE behavior OF splitter IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT splitter
    PORT(
         A : IN  std_logic_vector(31 downto 0);
         O1 : OUT  std_logic_vector(7 downto 0);
         O2 : OUT  std_logic_vector(7 downto 0);
         O3 : OUT  std_logic_vector(7 downto 0);
         O4 : OUT  std_logic_vector(7 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal A : std_logic_vector(31 downto 0) := (others => '0');

 	--Outputs
   signal O1 : std_logic_vector(7 downto 0);
   signal O2 : std_logic_vector(7 downto 0);
   signal O3 : std_logic_vector(7 downto 0);
   signal O4 : std_logic_vector(7 downto 0);
   -- No clocks detected in port list. Replace <clock> below with 
   -- appropriate port name 
 
   constant <clock>_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: splitter PORT MAP (
          A => A,
          O1 => O1,
          O2 => O2,
          O3 => O3,
          O4 => O4
        );

   -- Clock process definitions
   <clock>_process :process
   begin
		<clock> <= '0';
		wait for <clock>_period/2;
		<clock> <= '1';
		wait for <clock>_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	

      wait for <clock>_period*10;

      -- insert stimulus here 

      wait;
   end process;

END;
