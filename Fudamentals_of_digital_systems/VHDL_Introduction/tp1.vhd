--------------------------------------
-- Biblioteca
--------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;

--------------------------------------
-- Entidade
--------------------------------------
entity tp1 is
  port(
      din, reset, clock : in std_logic;
      prog : in std_logic_vector(2 downto 0);
      padrao : in std_logic_vector(7 downto 0);
      dout, alarme : out std_logic);
end entity; 

--------------------------------------
-- Arquitetura
--------------------------------------
architecture tp1 of tp1 is 

  signal reg_din : std_logic_vector(7 downto 0); --saida registrador de deslocamento;
  signal p1, p2, p3 : std_logic_vector(7 downto 0); -- saida registrador;
  signal ent1, ent2, ent3: std_logic;--enable registradores do comparador
  signal valid_p1, valid_p2, valid_p3: std_logic;
  signal C_p1, C_p2, C_p3: std_logic;
  signal match, match_p1, match_p2, match_p3: std_logic; -- saida dos comparadores
  signal alarme_int, entAlarme: std_logic; -- alarme
  
  TYPE state IS (Espera, Buscando, Perigo, Blocking); -- m�quina de estados;
  signal EA,PE : state;  -- estado atual/proximo estado - m�quina de estados;
  signal cont : std_logic_vector(1 downto 0); -- cont m�quina de estados;  
  
  begin
  
 -- Registrador de deslocamento: 
  
process(clock, reset)
begin

if(reset='1') then 

reg_din<="00000000";
elsif rising_edge(clock) then 

reg_din(7)<=din;
reg_din(6)<=reg_din(7);
reg_din(5)<=reg_din(6);
reg_din(4)<=reg_din(5);
reg_din(3)<=reg_din(4);
reg_din(2)<=reg_din(3);
reg_din(1)<=reg_din(2);
reg_din(0)<=reg_din(1);
end if;
end process;



--    P1    --
process(reset, clock)
begin 
if reset = '1' then
   p1 <= "00000000";
elsif rising_edge(clock) then
  if ent1 = '1' then
  p1 <= padrao;
  end if;
end if;
end process;

process(reset, clock)
begin 
if reset = '1' then
   valid_p1 <= '0';
elsif rising_edge(clock) then
  if ent1 = '1' then
  valid_p1 <= '1';
  end if;
end if;
end process;

-- comparador --
C_p1 <= '1' when reg_din = p1 else '0';

-- AND --
match_p1 <= C_p1 and valid_p1;

--    P2    --
process(reset, clock)
begin 
if reset = '1' then
   p2 <= "00000000";
elsif rising_edge(clock) then
  if ent2 = '1' then
  p2 <= padrao;
  end if;
end if;
end process;

process(reset, clock)
begin 
if reset = '1' then
   valid_p2 <= '0';
elsif rising_edge(clock) then
  if ent2 = '1' then
  valid_p2 <= '1';
  end if;
end if;
end process;

-- comparador --
C_p2 <= '1' when reg_din = p2 else '0';

-- AND --
match_p2 <= C_p2 and valid_p2;




--    P3    --
process(reset, clock)
begin 
if reset = '1' then
   p3 <= "00000000";
elsif rising_edge(clock) then
  if ent3 = '1' then
  p3 <= padrao;
  end if;
end if;
end process;

process(reset, clock)
begin 
if reset = '1' then
   valid_p3 <= '0';
elsif rising_edge(clock) then
  if ent3 = '1' then
  valid_p3 <= '1';
  end if;
end if;
end process;

-- comparador --
C_p3 <= '1' when reg_din = p3 else '0';

-- AND --
match_p3 <= C_p3 and valid_p3;

-- OR --
match <= match_p1 or match_p2 or match_p3;

-- Registrador alarme --       

process(reset, clock)
begin             
if reset = '1' then alarme_int <= '0';
elsif rising_edge(clock) then 
if entAlarme = '1' then alarme_int <=match;
else alarme_int <='0';
end if;
if PE= Buscando then alarme_int<=match; 
elsif PE=Perigo then alarme_int <='1';
elsif PE=Blocking then alarme_int <='1';
else alarme_int <='0';
end if;       
end if;    
end process;

alarme<=alarme_int; 

--and dout:

 dout <= din and not alarme_int;

--M�quina de estados:

process( reset, clock)
begin                      

if reset = '1' then 
   EA<=Espera;
   elsif rising_edge(clock)then 
   EA<=PE;
   end if;
   end process;   
   
   process(EA,prog,cont,match)     
   begin 
   case EA is  
   
   when Espera => 
   entAlarme<='0'; 
   if prog = "100" then PE <= Buscando;
   else PE <= Espera;
   if prog = "001" then ent1 <= '1';
   else ent1 <= '0';
   end if;

   if prog = "010" then ent2 <= '1';
   else ent2 <= '0';
   end if;

   if prog = "011" then ent3 <= '1';
   else ent3 <= '0';
   end if;
   
   end if;     
                                     
   when Buscando => 
   if match='1' then PE<=Perigo;
   elsif prog= "101" then PE <= Blocking;   
   elsif prog= "111" then PE <=Espera;
   else PE<= Buscando;
 end if;          
 
   when Perigo =>       
   if prog="101" then PE <= Blocking;  
   elsif cont="011" then PE <=Buscando;  
   else PE<=Perigo;
   end if;  
   
   when Blocking => 
   if prog= "111" then PE <=Espera; 
   elsif prog="110" then PE <= Buscando;
   else PE<=Blocking; 
   end if;      
   
   when OTHERS => PE <=Espera;   
   
   end case;            
     
   end process;                  
   
   --contador de clock:
   
   process(clock, reset)
   begin 
   
   if reset='1' then cont<="00";	
   elsif rising_edge(clock) then 
   if EA=Perigo then cont<=cont+1;
   else
   cont<="00";
   end if;  
   if EA=Blocking then entAlarme <='1';
   end if;
   end if; 
   	
   end process;  
 
end architecture;                                                                      