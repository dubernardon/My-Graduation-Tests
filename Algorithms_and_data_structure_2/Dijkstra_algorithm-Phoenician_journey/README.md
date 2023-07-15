# ﻿Algoritmo “os fenícios estão chegando” 

Eduardo B. Cozer∗, Luiz Felipe S. Ramalho † 

Engenharia de Computação

PUCRS  

13 de Junho de 2023 

**Resumo** 

Esse  trabalho  trata-se  da  implementação  de  um  algoritmo  de  pesquisa  em  grafos proposta na disciplina de Algoritmos e estrutura de dados 2 no terceiro semestre. Tal algoritmo fornece  a  melhor  rota  para  os  fenícios  se  locomoverem  por  “trirremes”  nos  mapas disponibilizados no enunciado do trabalho. É descrito como tal problema foi  modelado e desenvolvido pelo algoritmo, além dos resultados com os mapas de teste e a conclusão do trabalho. 

**Introdução**

A  proposta  do  trabalho  é  encontrar  o caminho em  que  seria consumido  a  menor quantidade de combustível, ou seja, o menor caminho, para navegar entre os portos.  Um exemplo de mapa para navegação dos fenícios é mostrado abaixo: 

<div align="center"> 
<img src="https://github.com/dubernardon/My-Graduation-Tests/assets/102065589/3aa15f06-1066-4ebf-884a-9b10295ef434" >
  </div>

Nesse mapa, os portos são enumerados de 1 a 9, enquanto a terra firme é indicada por asteriscos e o mar por pontos. Os “trirremes” partem do primeiro porto acessível em direção aos próximos portos disponíveis em ordem crescente, navegando somente em sentidos leste, oeste, norte e sul. Caso algum porto seja contornado por terra firme, ou seja, inacessível, os fenícios seguem para o próximo porto da sequência disponível. Após seguir por todos os portos acessíveis, retornam para o porto de início da viagem. 

Por meio dessa descrição, é possível perceber características, como a utilização de vértices para cada ponto do mapa, que indicam os benefícios do uso de grafos para a resolução do problema proposto e do uso do algoritmo de caminhamento mínimo Dijkstra para encontrar o trajeto mais benéfico para a população fenícia. 

**Modelagem geral do problema:** 

Antes de apresentar os algoritmos de teste, uma visão de como o problema pode ser resolvido pelo algoritmo é necessário. A execução do programa se baseia nas seguintes etapas:** 

1-  Os arquivos de teste “.map” são lidos e é salvo as informações do número de linhas e de 

colunas em inteiros. Com isso, o mapa é colocado em uma matriz de char com o tamanho das linhas e colunas. 

2-  Após isso, cria-se um grafo com todos os vértices e suas conexões a partir da matriz de char. 

Junto a criação do grafo é criado um vetor de inteiros de 10 posições guardando o vértice de cada porto no mapa. 

3-  Para descobrir o gasto de combustível, foi utilizado uma função que recebe o vector da função 

de Dijkstra de um porto, utilizando as coordenadas dos portos seguintes como índice do vector para descobrir a distância entre os portos. Os portos que possuem distância zero não possuem conexão, isto é, o porto de destino é inacessível (os “trirremes” não navegam até portos inacessíveis). 

4-  Após ser calculado a distância para todos os portos disponíveis pelo algoritmo de 

caminhamento mínimo, é calculado a distância do último porto visitado até o porto de origem, terminando o cálculo de combustível da viagem. 

**Processo de solução:**

A solução do problema, após a leitura dos arquivos com os mapas e a construção dos grafos, é realizada pela função principal findDistTo(). Essa função verifica se o vértice de destino é um porto acessível e filtra as distâncias entre dois vértices específicos do mapa, isto é, o menor caminho possível. Para encontrar esses caminhos mínimos, a função caminhamento() é chamada, identificando todos os caminhos mínimos a partir de uma origem para todos os outros vértices disponíveis. Logo, o  caminhamento mínimo Dijkstra é realizado pela função caminhamento(), enquanto o 'source-sink' é realizado  pela  função  findDistTo(),  a  qual  utiliza  todos  os  caminhos  descobertos  pela  função caminhamento (Dijkstra) e usa a coordenada do destino, ou seja, o porto seguinte, para identificar a distância para um vértice específico, ou, a coordenada do porto. 

- caminhamento(): 
1. caminhamento(*navegacao*: Grafo, *origem*: inteiro) -> vetor de inteiros: 
1. *Vértices* ← *navegacao*.retornaVértices() 
1. *Distância* ← vetor de inteiros de tamanho n inicializado com zeros 
1. visitado ← vetor de booleanos de tamanho n inicializado com falso 
1. *Fila\_de\_prioridade* ← fila de prioridade de pares de inteiros, usando como comparação o valor 

mínimo do par 

 
6. *Distância* [*origem*] ← 0 
6. *Fila\_de\_prioridade*.enfileira(fazer\_par(0, *origem*))  
 
6. enquanto pq não estiver vazio faça: 
6. *VérticeU* ← *Fila\_de\_prioridade*.frente().segundo 
6. *Fila\_de\_prioridade*.desenfileira() 
 
6. se *visitado[VérticeU*] for verdadeiro, continue para a próxima iteração 
 
6. *visitado*[*VérticeU*] ← verdadeiro 
 
6. para cada *Conexão* em *navegacao*.retornaConexões(*VérticeU*) faça: 
6. *VérticeV* ← *Conexão* 
6. *Peso* ← 1 
 
6. se *Distância*[*VérticeU*] + *Peso* < *Distância*[*VérticeV*] ou *Distância*[*VérticeV*] < 1 então: 
6. *Distância*[*VérticeV*] ← *Distância*[*VérticeU*] + *Peso* 
6. *Fila\_de\_prioridade*.enfileira(fazer\_par(*Distância*[*VérticeV*], *VérticeV*)) 
 
6. retorne *Distância* 
- findDistTo(): 
1. findDistTo(*portos*: vetor de inteiros, *navegacao*: Grafo, *portoAtual*: ponteiro de inteiro, *destino*: ponteiro de inteiro) -> inteiro: 
1. *Distância* ← caminhamento(*navegacao*, *portos*[\**portoAtual*]) 
 
1. enquanto \**destino* < 10 faça: 
1. se *Distância*[*portos*[\**destino*]] diferente de 0, então: 
1. \**portoAtual* ← \**destino* 
1. retorne *Distância* [portos[\**destino*]] 
1. senão, 
1. \**destino* ← \**destino* + 1 
 
1. retorne 0 

Para realizar o cálculo do consumo total de combustível dos “trirremes”, é executada a função findDistTotal(), a qual chama a função findDistTo() para adquirir a distância necessária entre todos os portos acessíveis, assim, obtendo o consumo total de combustível para toda a viagem. O consumo de combustível é determinado pela quantidade de vértices passados para chegar até o porto de destino. 

1. findDistTotal(*navegacao*: Grafo, *portos*: ponteiro de inteiros) -> inteiro: 
1. *DistânciaTotal* ← 0 
1. *Distância* ← 0 
 
1. *portoAtual* ← novo inteiro 
1. *destino* ← novo inteiro 
1. \**portoAtual* ← 1 
1. \**destino* ← 2 
 
1. *portoInicial* ← 1 
 
1. enquanto \**portoAtual* diferente de 9 e \**destino* < 10 faça: 
13. *Distância* ← findDistTo(*portos*, *navegacao*, *portoAtual*, *destino*) 
13. se *Distância* diferente de 0, então: 
13. \**destino* ← \**portoAtual* + 1 
13. *DistânciaTotal* ← *DistânciaTotal* + *Distância* 
13. senão, 
13. se \**portoAtual* igual a *portoInicial* e \**destino* igual a 10 e *DistânciaTotal* igual a 0, então: 
13. \**portoAtual* ← \**portoAtual* + 1 
13. *portoInicial* ← \**portoAtual* 
13. \**destino* ← \**portoAtual* + 1 
 
13. \**destino* ← *portoInicial* 
13. *DistânciaTotal* ← *DistânciaTotal* + findDistTo(*portos*, *navegacao*, *portoAtual*, *destino*) 
 
13. deletar *portoAtual* 
13. deletar *destino* 
 
13. retorne *DistânciaTotal* 

**Resultados:**

- **Caso 0**: 



|Origem: |Destino: |Distância |
| - | - | - |
|Porto 1 |Porto 2 |27 |
|Porto 2 |Porto 3 |39 |
|Porto 3 |Porto 4 |12 |
|Porto 4  |Porto 5 |11 |
|Porto 5 |Porto 6 |42 |
|Porto 6  |Porto 7 (inacessível) |- |
|Porto 6 |Porto 8 |48 |
|Porto 8 |Porto 9 |42 |
|Porto 9 |Porto 1 (retorno origem) |27 |

Distância total: 248 (combustível total gasto) 

- **Caso 1:** 



|Origem: |Destino: |Distância |
| - | - | - |
|Porto 1 |Porto 2 |61 |
|Porto 2 |Porto 3 |97 |
|Porto 3 |Porto 4 |84 |
|Porto 4  |Porto 5 |72 |
|Porto 5 |Porto 6 (inacessível) |- |
|Porto 5 |Porto 7  |51 |
|Porto 7 |Porto 8 |33 |
|Porto 8 |Porto 9 |63 |
|Porto 9 |Porto 1 (retorno origem) |137 |

Distância total: 598 (combustível total gasto) 

- **Caso 2:** 

|Origem: |Destino: |Distância |
| - | - | - |
|Porto 1 |Porto 2 |102 |
|Porto 2 |Porto 3 |96 |
|Porto 3 |Porto 4 |163 |
|Porto 4  |Porto 5 |113 |
|Porto 5 |Porto 6 |135 |
|Porto 6 |Porto 7  |120 |
|Porto 7 |Porto 8 |114 |
|Porto 8 |Porto 9 |62 |
|Porto 9 |Porto 1 (retorno origem) |207 |

Distância total: 1112 (combustível total gasto) 

- **Caso 3:** 



|Origem: |Destino: |Distância |
| - | - | - |
|Porto 1 |Porto 2 |92 |
|Porto 2 |Porto 3 |402 |
|Porto 3 |Porto 4 |79 |
|Porto 4  |Porto 5 |335 |
|Porto 5 |Porto 6 (inacessível) |- |
|Porto 5 |Porto 7  |283 |
|Porto 7 |Porto 8 |185 |
|Porto 8 |Porto 9 |400 |
|Porto 9 |Porto 1 (retorno origem) |434 |

Distância total: 2210 (combustível total gasto) 

- **Caso 4:** 



|Origem: |Destino: |Distância |
| - | - | - |
|Porto 1 |Porto 2 |649 |
|Porto 2 |Porto 3 (inacessível) |574 |
|Porto 3 |Porto 4 (inacessível) |- |
|Porto 3 |Porto 5 (inacessível) |- |
|Porto 3 |Porto 6  |222 |
|Porto 6 |Porto 7 (inacessível) |340 |
|Porto 7 |Porto 8  |714 |
|Porto 8 |Porto 9 (inacessível) |- |
|Porto 8 |Porto 1 (retorno origem) |1011 |

Distância total: 3510 (combustível total gasto) 

- **Caso 5:** 



|Origem: |Destino: |Distância |
| - | - | - |
|Porto 1 |Porto 2 |1252 |
|Porto 2 |Porto 3 |2355 |
|Porto 3 |Porto 4 |488 |
|Porto 4  |Porto 5 |1425 |
|Porto 5 |Porto 6  |1535 |
|Porto 6 |Porto 7  |949 |
|Porto 7 |Porto 8 |918 |
|Porto 8 |Porto 9 |1154 |
|Porto 9 |Porto 1 (retorno origem) |1442 |

Distância total: 11518 (combustível total gasto) 

**Conclusão:**

A partir do trabalho realizado é possível concluir que o algoritmo de caminhamento mínimo Dijkstra com variante de caminho mínimo “Source-Sink” cumpre sua missão, entregando a menor distância possível entre um vértice e outro (menor consumo de combustível) e tratando possíveis exceções do problema (portos inacessíveis).  O algoritmo Dijkstra implementado na solução do problema possui a complexidade de dez vezes O (|E| + |V| + log|V|) (em que E = número de arestas, V = número de vértices), devido a necessidade de executar o algoritmo para todos os destinos. Logo, é possível notar um bom desempenho na execução do algoritmo Dijkstra para esse problema, mesmo que, com mapas maiores, tenha um consumo de recursos computacionais considerável (caso teste 5). 

