# Traffic Filter using state machines

<div align="center"> 
In this traffic filter, a combination is expected. When this combination is detected, the alarm is triggered and the system is locked, preventing an attack. More information in the report bellow.
 </div>
 <div align="center"> 
This traffic filter was a test of my graduation in computer engineering.
 </div>
<div align="center"> 
<img src="https://media0.giphy.com/media/qi29MoLjWNPUI/giphy.gif?cid=ecf05e475d54lco64cgouxmhrd1qjycjye72z01yts9ascc2&rid=giphy.gif&ct=g" >
  </div>
  <div align="center"> 
 🙋‍♂️ Thanks for visiting my repository!
</div>

# Traffic Filter (Portuguese)

<div align="left"> 
 A máquina de estados implementada possui quatro estados: espera, buscando, perigo e blocking. Cada estado recebe um valor de “prog” ou, enquanto no estado buscando, um 
“match” e executa determinada ação. Assim, gerando o funcionamento correto do sistema.
 </div>
 <div align="left"> 
-**Estado espera**: esse estado é ativado quando o sistema está esperando um valor de 
“prog” para executar determinada ação, ou seja, enquanto o prog continua com valor 
zero, continuará esse estado ativo. Assim, quando o estado receber prog=1 ativará a
comparação com o padrão 1 (ent1=’1’), quando receber prog=2 ativará a comparação 
com o padrão 2 (ent2=’1’), e quando receber prog=3 ativará a comparação com o 
padrão 3 do sistema (ent3=’1’)
 </div>
 <div align="left"> 
-**Estado buscando**: é ativado no momento em que é recebido um prog=4 no estado espera. Enquanto estiver nesse estado, é verificado se ocorre alguma igualdade no sistema, assim, se ocorrer (recebe um match dos comparadores), é ativado o estado perigo. Caso receba um prog=5, é ativado diretamente o estado blocking. Se receber um prog=7 o sistema reativa o estado espera. Nesse estado, o contador de clocks 
(cont) está sempre em 0.
 </div>
  <div align="left"> 
-**Estado Perigo**: É acionado, como explicado anteriormente, pelo match=1 recebido pelo estado buscando. Ele fica ativo até quatro clocks com o alarme ativado e retorna, 
posteriormente, ao estado buscando, caso não receba prog=5 (ativaria o estado blocking) e zera o contador de clocks (cont).
 </div>
 <div align="left"> 
-**Estado Blocking**: fica ativo quando recebe um prog=5 (ataque) no estado perigo ou buscando, os quais podem detectar um ataque, e ativa o alarme. Após o bloqueio dos 
dados, quando recebe um prog=7, o estado espera é reativado. Também, o estado blocking pode reativar o estado buscando quando receber um prog=6.
 </div>
 
 
 
 # Traffic Filter (English)

<div align="left"> 
 The implemented state machine has four states: waiting, searching, danger and blocking. Each state receives a “prog” value or, while in the searching state, a match and performs a certain action. Therefore, generating the correct functioning of the system.
 </div>
 <div align="left"> 
-**Waiting state**: this state is activated when the system is waiting for a “prog” value to execute a certain action, that is, while "prog=0", this state stay actived. When the state receives prog=1 it will activate the comparison with the comparison 1 (ent1='1'), when it receives prog=2 it will activate the comparison with the comparison 2 (ent2='1'), and when it receives prog=3 will activate the comparison with the comparison 3 (ent3='1').
 </div>
 <div align="left"> 
-**Searching state**: is activated when prog=4 is received in the waiting state. While in this state, it is checked if there is any equality in the comparison system, so, if it occurs (it receives a match from the comparators), the danger state is activated. If it receives a prog=5, the blocking state is activated directly. If you receive a prog=7, the system reactivates the waiting state. In this state, the clock counter (cont) is always equal to 0.
 </div>
  <div align="left"> 
-**Danger State**: It is triggered, as explained before, by "match=1" received by the searching state. It continue active for up to four clocks with the alarm activated and returns to the searching state later, if it does not receive "prog=5" (it would activate the blocking state) and resets the clock counter (cont).
</div>
 <div align="left"> 
-**Blocking state**: Is active when receives "prog=5" (attack) in the danger or searching state, which can detect an attack, and activates the alarm. After blocking the data traffic, when it receives "prog=7", the waiting state is reactivated. Also, the blocking state can reactivate the searching state when it receives "prog=6".
 </div>
 
 

