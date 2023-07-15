#  Otimização do algoritmo “os macaquinhos” 

Eduardo B. Cozer, Luiz Felipe S. Ramalho, Engenharia de Computação — PUCRS  

17 de abril de 2023 

**Resumo** 

Esse trabalho trata-se de uma comparação entre um algoritmo não otimizado em relação a otimização. Nesse caso teste, o algoritmo será sobre uma suposta atividade realizada entre macacos proposta na disciplina de Algoritmos e estrutura de dados 2 no terceiro semestre. São descritos dois algoritmos distintos os quais suprem a mesma necessidade e analisados. Logo após, é apresentado o resultado de cada algoritmo (tempo de execução e o macaco vencedor), e uma conclusão do trabalho.   

**Introdução** 

Os algoritmos computacionais podem ser desenvolvidos de inúmeras formas para o mesmo objetivo. Entretanto, cada algoritmo possui seu desempenho de execução individual, o que pode demorar mais ou não para ser executado completamente. Tal desempenho não é restrito somente aos algoritmos, posto que o tempo de execução de qualquer tarefa pode ser reduzido com melhorias na execução e organização. 

Para exemplificar melhor, podemos relacionar com o caso teste disponibilizado: 

- Macacos, em uma brincadeira, distribuem cocos para outros macacos. Cada coco tem uma quantidade determinada de pedrinhas. 
- Essa brincadeira possui diversas rodadas e, em cada rodada, todos os macacos trocam todos seus cocos. Para realizar essa troca, é determinado um macaco específico para enviar os cocos com número de pedrinhas par e outro para a quantidade de pedrinhas ímpar. 
- Após realizar todas as rodadas, diversas trocas ocorreram e um macaco possuirá uma maior quantidade de cocos. Esse será o vencedor da brincadeira. 

Ao associar essa brincadeira a velocidade, notamos que a organização dos cocos pelos macacos pode influenciar diretamente no tempo de conclusão.  

- Organização 1: 

Os macacos recebem seus cocos e é verificado a quantidade de pedrinhas em cada coco antes de enviar para seu parceiro de brincadeira, ou seja, durante as rodadas. 

- Organização 2: 

Os macacos recebem seus cocos e imediatamente separam quais cocos possuem quantidade par e ímpar de pedrinhas. Dessa forma, aceleram o futuro envio de cocos para seu parceiro, já que, somente necessita pegar todos os cocos separados corretamente e entregar para o parceiro. ![](Aspose.Words.ab001eaa-fd4c-45af-9878-420922bd49f8.001.png)

É possível notar uma diferença significativa na eficiência de cada caso. Na organização 1, cada macaco iria demorar mais tempo para conseguir contar todas as pedrinhas e depois passar para seu parceiro, enquanto, na organização 2, os macacos só necessitam repassar seus cocos. 

Tal comparativo pode ser aplicado em dois algoritmos retratando o mesmo cenário, os quais terão maior diferença de tempo de execução, já que, não se trata apenas de uma contagem, se trata de dezenas de instruções para realizar uma #  Pizzeria and pastry shop simulatorúnica contagem. 

**Modelagem geral do problema:** 

Antes de apresentar os algoritmos de teste, uma visão de como o problema pode ser resolvido pelo algoritmo é necessário. A execução do programa se baseia nas seguintes etapas: 

1-  O arquivo com os casos teste são lidos e as informações salvas em um objeto para cada macaco. 

2-  Após isso, cria-se um “loop” para realizar todas as rodadas e um outro “loop” para passar em todos os 

macacos do jogo. Dentro daquele “loop”, é passado cada coco para o macaco predeterminado. 

3-  Ao fim do programa, verifica-se qual macaco é o vencedor, passando por todos os macacos e testando 

a quantidade de cocos em cada macaco. 

**Algoritmo 1:** 

Nesse algoritmo, de forma semelhante aos macacos, o algoritmo necessita realizar diversas instruções para realizar as trocas. Para cada rodada, é necessário: 

1-  Passar por todos os cocos; 

2-  Verificar se ainda possui cocos para entregar; 

3-  Pegar um coco com pedrinhas; 

4-  Verificar se é um coco com pedrinhas pares ou ímpares; 5-  Entregar para outro macaco; 

6-  Reduzir um coco de sua quantidade. 

1. Classe Macaquinho{ 
1. int cocos, endereçoÍmpar,  endereçoPar 
1. int pedrinhas[cocos] 
1. } 
 
1. procedimento Algoritimo 2 
1. para *i ← 1 até Número de Rodadas* faça 
1. para *j ← 1 até Número de Macaquinhos* faça 
1. enquanto *Macaquinho[ j ].pedrinhas[ k ] != 0* faça 
1. se *Macaquinho[ j ].pedrinhas[ k ] % 2 == 0* então 
1. *Macaquinho[endereçoPar].setPedrinhas( Macaquinho[ j ].pedrinhas[ k ] )* 
1. *Macaquinho[endereçoPar].cocos++* 
1. senão  
1. *Macaquinho[endereçoÍmpar].setPedrinhas( Macaquinho[ j ].pedrinhas[ k ] )* 
1. *Macaquinho[endereçoÍmpar].cocos++* 
1. fim 
1. fim 
1. fim 
1. fim 
1. fim     

**Algoritmo 2:** 

No  algoritmo  aperfeiçoado,  é  preciso  executar  uma  quantidade  consideravelmente  reduzida  de instruções por rodada. Vale salientar que para indicar o macaco vencedor, precisa somente saber a quantidade de cocos, ou seja, não precisa realizar operações de teste de número par ou ímpar nem a troca de cada coco individual. Essas operações que consomem muitos recursos podem ser operadas logo na leitura do arquivo, definindo a quantidade de cocos pares e ímpares para o macaco, o que evita o alto consumo de tempo na troca de cocos. Com isso, somente é necessário: 

1-  Pegar todos os cocos pares; 2-  Entregar todos os pares; 

3-  Pegas todos os cocos ímpares; 4-  Entregar todos os ímpares. 

1. Classe Macaquinho{ 
1. int cocos, endereçoÍmpar,  endereçoPar, cocosÍmpar, cocosPar 
1. } 
 
1. procedimento Algoritimo 2 
1. para *i ← 1 até Número de Rodadas* faça 
1. para *j ← 1 até Número de Macaquinhos* faça 
1. se *Macaquinho[ j ] != 0* então 
1. *Macaquinho[endereçoÍmpar].cocosÍmpar  += cocosÍmpar* 
1. *Macaquinho[endereçoPar].cocosPar  += cocosPar* 
1. *Macaquinho[ j ].cocosÍmpar  -= cocosPar* 
1. *Macaquinho[ j ].cocosPar  -= cocosPar* 
1. fim
1. fim
1. fim
1. fim 

` `**Resultados:** 

Para comparar o aperfeiçoamento do algoritmo 2 em relação ao 1, foi realizado a medição do tempo de execução dos dois. Na tabela abaixo, é possível verificar o tempo e qual foi o macaco vencedor em cada caso de teste disponibilizado pelo professor.



|**Casos de teste:** |**Algoritmo 1** |**Algoritmo 2** |**Resultados (macaco vencedor):** |
| - | - | - | :- |
|50 macacos – 5000 rodadas |11,328054 segundos|0,002338 segundos |19|
|100 macacos – 10000 rodadas |186,176980 segundos |0,009820 segundos |75 |
|200 macacos – 20000 rodadas |Excedeu o tempo de teste|0,030272 segundos |99 |
|400 macacos – 40000 rodadas |Excedeu o tempo de teste|0,082166 segundos |70 |
|600 macacos – 60000 rodadas |Excedeu o tempo de teste|0,192119 segundos |105|

|||||
| :- | :- | :- | :- |
|800 macacos – 80000 rodadas |Excedeu o tempo de teste|0,256203 segundos |622 |
|900 macacos – 90000 rodadas |Excedeu o tempo de teste|0,415437 segundos |346 |
|1000 macacos – 100000 rodadas |Excedeu o tempo de teste|0,484419 segundos |649 |

**\*Tempo de teste = 30 minutos.** 
**\*Alguns casos de teste não estão disponíveis no github devido ao tamanho do arquivo (excede 25mb).**
**\*O tempo calculado foi adquirido pela função “clock()” da biblioteca “time.h”.** 

**Conclusão:** 

A primeira solução desenvolvida foi a abordagem mais óbvia e literal do problema. Já a segunda solução  foi  desenvolvida  após  um  melhor  entendimento  do  problema,  excluindo  partes  desnecessárias  e ignorando informações irrelevantes para o resultado final. Acreditamos que a segunda solução desenvolvida para  este  problema  é  suficiente,  entregando  bons  resultados,  com  baixo  tempo  de  execução.  Sua  maior otimização foi a remoção das pedrinhas de cada macaco, apenas usando o número de coco de cada um e guardando  quantos  tem  um  número  de  pedrinhas  ímpares  e  pares.  Transformando  um  vetor  de  inteiros extensivo em dois inteiros relativamente pequenos. Essa mudança, além de fazer o programa realizar menos operações por laço, também diminui o número total de laços, transformando um programa que funcionava com uma complexidade de *número de rodadas* vezes o *número de macaquinhos* vezes o *número de pedrinhas*, para apenas o *número de rodadas* vezes o *número de macaquinhos.* Essa mudança pode ser observada na tabela de resultados, com a primeira solução aumentando exponencialmente e com a segunda aumentado pouco*.* 
