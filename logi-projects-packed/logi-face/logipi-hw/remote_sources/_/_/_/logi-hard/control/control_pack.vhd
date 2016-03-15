

-- ----------------------------------------------------------------------
--LOGI-hard
--Copyright (c) 2013, Jonathan Piat, Michael Jones, All rights reserved.
--
--This library is free software; you can redistribute it and/or
--modify it under the terms of the GNU Lesser General Public
--License as published by the Free Software Foundation; either
--version 3.0 of the License, or (at your option) any later version.
--
--This library is distributed in the hope that it will be useful,
--but WITHOUT ANY WARRANTY; without even the implied warranty of
--MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
--Lesser General Public License for more details.
--
--You should have received a copy of the GNU Lesser General Public
--License along with this library.
-- ----------------------------------------------------------------------



--
--	Package File Template
--
--	Purpose: This package defines supplemental types, subtypes, 
--		 constants, and functions 
--
--   To use any of the example code shown below, uncomment the lines and modify as necessary
--

library IEEE;
use IEEE.STD_LOGIC_1164.all;

package control_pack is

type slv16_array is array(natural range <>) of std_logic_vector(15 downto 0);

component servo_controller is
  generic(
	 pos_width	:	integer := 8 ;
    clock_period             : integer := 10;
    minimum_high_pulse_width : integer := 1000000;
    maximum_high_pulse_width : integer := 2000000
    );
  port (clk            : in  std_logic;
        rst            : in  std_logic;
        servo_position : in  std_logic_vector (pos_width-1 downto 0);
        servo_out       : out std_logic);
end component;


component mcp3002_interface is
generic(CLK_DIV : positive := 1024;
		  SAMPLING_DIV : positive := 2048);
port(

		  clk, resetn : std_logic ;

		  sample : out std_logic_vector(9 downto 0);
		  dv : out std_logic ;
		  chan : in std_logic ;
		
		  -- spi signals
		  DOUT : out std_logic ;
		  DIN : in std_logic ;
		  SCLK : out std_logic ;
		  SSN : out std_logic

);
end component;


component pwm is
generic(NB_CHANNEL : positive := 3);
port(
	clk, resetn : in std_logic ;
	divider : in std_logic_vector(15 downto 0);
	period : in std_logic_vector(15 downto 0);
	pulse_width : in slv16_array(0 to NB_CHANNEL-1) ;
	pwm : out std_logic_vector(0 to NB_CHANNEL-1) 
);
end component;

component heart_beat is
    generic(clk_period_ns : positive := 10; 
				beat_period_ns : positive := 1_000_000_000;
				beat_length_ns : positive := 200_000_000);
	 port ( gls_clk : in  STD_LOGIC;
           gls_reset : in  STD_LOGIC;
           beat_out : out  STD_LOGIC);
end component;


end control_pack;


package body control_pack is


 
end control_pack;
