.text  

  .globl main 

   

main:   la $s1, vet 		#endereço do vetor 

	la $s2, vet 		#endereço do vetor para trocar o endereço de teste 

	lw $t1, 0($s1) 		#valor do endereço do vetor 

	lw $t2, 0($s2) 		#valor do endereço do vetor testado 

	lw $t3, n 		#tamanho do vetor 

	move $t4, $zero 	#zera o contador do loop 

	move $t5, $zero 	#zera o contador de loops 

	move $t6, $zero 	#zera o contador do valor testado 

	move $t7, $zero 	#zera a moda encontrada até o momento 

	lw $t0, 0($s1) 		#assume como moda o primeiro valor do vetor 

   

modaCalc: 	bgt $t4, $t3,testeModa	#se o contador passou por todo o vetor, testa se passou por todos os valores 

	beq $t2, $t1, aumenta 	#se for o mesmo valor aumenta a quantidade da moda 

	addi $s1, $s1, 4 	#proxima posicao do vetor 

	lw $t1, 0($s1) 		#pega o valor do endereço $s1 

	addi $t4, $t4, 1 	#soma o contador 

	j modaCalc 		#faz o loop 

   

testeModa: 	bgt $t6, $t7, trocaModa 

	beq $t5, $t3, finalizaModa 

	addi $t5, $t5, 1 	#soma no contador de loop 

	move $t4, $zero 	#zera o contador do loop 

	move $t6, $zero 	#zera o contador do valor testado 

	la $s1, vet 		#volta para o endereço  inicial do vetor 

	lw $t1, 0($s1) 		#volta para o valor inicial 

	addi $s2, $s2, 4 	#avança uma posição para testar o próximo valor  

	lw $t2, 0($s2) 		#pega o valor do endereço $s2 

	j modaCalc 		#volta para o loop 

   

   

trocaModa: 	move $t7,$t6 		#assume a quantidade da nova moda 

	move $t0, $t2 		#assume o novo valor da moda 

	j testeModa 

  

aumenta: addi $t6, $t6, 1 	#soma no contador do valor testado 

	addi $t4, $t4, 1 	#soma o contador 

	addi $s1, $s1, 4 	#passa para a proxima posição do vetor 

	lw $t1, 0($s1) 		#pega o valor da próxima posição do vetor 

	j modaCalc 

   

   

finalizaModa: 	sw $t0, moda            #retorna a moda 

    	la $a0, resModa		#string da moda 

    	li $v0, 4		#printar string 

    	syscall			#print 

    	move $a0, $t0		#passa a moda para printar 

    	li $v0, 1		#printar int 

    	syscall			#print 

    	sw $t7, vezes           #retorna quantas vezes a moda repete 

    	la $a0, resVezesModa	#string da quatidade da moda 

    	li $v0, 4		#printar string 

    	syscall			#print 

    	move $a0, $t7		#passa a quantidade da moda para printar 

    	li $v0, 1		#printar int 

    	syscall			#print 

 

mediaInic: 	la $s1, vet 		#endereço do vetor 

	lw $t1, 0($s1) 		#valor do endereço do vetor 

	lw $t3, n 		#tamanho do vetor 

	move $t4, $zero 	#zera o contador 

	move $t2, $zero 	#zera a soma para média 

 

mediaCalc: 	beq  $t4, $t3, finalizaMedia 	#já passou por todo vetor, finaliza 

	add $t2, $t2, $t1 		# += no $t2     

	addi $s1, $s1, 4 		#avança uma posição no vetor 

	lw $t1, 0($s1)			#pega o valor do endereço 

	addi $t4, $t4, 1 		#adiciona no contador 

	j mediaCalc 

 

finalizaMedia: 		move $s0, $t3 		#passa para divisão o tamanho do vetor 

	move $s1, $t2 		#passa para divisão a soma da média 

	jal divider 

	sw $v1, media           #retorna a divisão (media) -> $v1 -> resultado da divisão 

	move $t2, $v1		#passa a media para o $t2 

    	la $a0, resMedia	#string da quatidade da moda 

    	li $v0, 4		#printar string 

    	syscall			#print 

    	move $a0, $t2		#passa a quantidade da moda para printar 

    	li $v0, 1		#printar int 

    	syscall			#print 

 

bubleSort: 	la $s1, vet 		#endereço do vetor 

	la $s2, vet 		#endereço do vetor testar a posição a frente 

	add $s2, $s2, 4 	#avança uma posição 

	lw $t1, 0($s1) 		#valor do endereço do vetor 

	lw $t2, 0($s2) 		#valor do endereço do vetor testado 

	li $t4, 1 		#um no contador do loop para não passar do vetor 

	lw $t3, n 		#tamanho do vetor 

	move $t5, $zero 	#zera o contador que verifica se está tudo ordenado ou não 

 

loop: 	beq $t4, $t3, testaOrdenado 	#se chegar até o final do vetor, verifica se ta tudo ordenado 

	blt $t2, $t1, swap 		#testa se é maior 

	addi $t4, $t4, 1 		#adiciona um no contador 

	addi $s1, $s1, 4 		#avança uma posição no vetor 

	addi $s2, $s2, 4 		#avança uma posição no vetor 

	lw $t1, 0($s1) 			#pega o valor do endereço 

	lw $t2, 0($s2) 			#pega o valor do endereço 

	j loop 

 

 

testaOrdenado: 		beqz $t5, ordenado 	#se estiver ordenado, acaba 

	move $t5, $zero		#zera o contador de troca 

	move $t4, $zero 	#zera o contador 

	la $s1, vet 		# pega o endereço do vetor 

	la $s2, vet 		#pega o endereço do vetor 

	addi $s2, $s2, 4 	#avança uma posição para teste 

	lw $t1, 0($s1) 		#valor do endereço do vetor 

	lw $t2, 0($s2) 		#valor do endereço do vetor testado 

	j loop 

 

swap:   move $t6, $t1 		# passa o valor de $t1 para um reg auxiliar 

	move $t1, $t2 		#troca 

	move $t2, $t6 		#troca 

	addi $t5, $t5, 1 	#soma uma troca no contador 

	sw $t1, 0($s1) 		#coloca no endereço do $s1 

	sw $t2, 0($s2) 		#coloca no endereço do $s2 

	j loop 

  

  

ordenado: 	la $a0, resSort		#string do sort 

    	li $v0, 4		#printar string 

    	syscall			#print 

    	 

medianaCalc: 	move $t1, $zero 	#zera o %$t1 

	lw $s1, n 		#tamanho do vetor 

	# $t4 -> valor do resto 

	li $s0, 2 		#valor para dividir e testar 

	jal divider 

	move $t7, $zero 	#contador 

	la $s1, vet 		#endereço do vetor 

	la $s2, vet 		#endereço do vetor para trocar o endereço de teste 

	beqz $v0, medianaPar 	#se o resto for zero, é par 

	la $a0, resMediadaImpar	#string da da mediana imapr 

    	li $v0, 4		#printar string 

    	syscall			#print 

 

medianaImpar:	beq $t7, $t6, finalizaMediana 

	addi $s1, $s1, 4 	#avança posições 

	lw $t1, 0($s1) 		#pega o valor do endereço $s1 

	addi $t7, $t7, 1 	#soma contador 

	j medianaImpar 

 

avancaMediana:	beq $t7, $t6, finalizaMediana 

	addi $s1, $s1, 4 	#avança posições 

	lw $t1, 0($s1) 		#pega o valor do endereço $s1 

	addi $t7, $t7, 1 	#soma contador 

	j avancaMediana 

  

medianaPar:	la $a0, resMediadaPar	#string da mediana par 

    	li $v0, 4		#printar string 

    	syscall			#print 

	subi $t6, $t6, 1	#pega uma posição anterior da metade 

	j avancaMedianaPar 

  

avancaMedianaPar: 	addi $s1, $s1, 4 	#avança posições 

	addi $t7, $t7, 1 	#soma contador 

	beq $t7, $t6, soma 	#valor para somar 

	j avancaMedianaPar 

 

soma: 	lw $t1, 0($s1) 		#pega o valor do endereço $s1 

	addi $s1, $s1, 4 	#vai para a proxima posicao 

	lw $t2, 0($s1) 		#pega o proximo valor 

	add $t1, $t1, $t2 	#soma os dois valores 

	li $s0, 2 		#divide para achar a mediana 

	move $s1, $t1 		#divide para achar a mediana 

	jal divider   		#divide para achar a mediana 

	move $t1, $v1 		#passa o resultado da divisão de volta para o $t1 

	j finalizaMediana	 

  

finalizaMediana: 

    	move $a0, $t1		#passa o valor da mediana 

    	li $v0, 1		#printar int 

    	syscall			#print 

  

	li $v0, 10		#acaba o programa 

    	syscall			#exit   

  

  

#divisor serial: (utilizado para ser possível realizar divisões e ser aceito no ambiente do modelsim) 

###################################################### 

### $s1/ $s0 --> $v0--> resto $v1 --> divis�o 

###################################################### 

divider: lui $t0, 0x8000 	#m�scara para isolar bit mais significativo 

	li $t1, 32 			# contador de itera��es 

	xor $v0, $v0, $v0 		# registrador P($v0)-A($v1) com 0 e o dividendo ($s1) 

	add $v1, $s1, $0 

dloop: and $t2, $v1, $t0 	# isola em t2 o bit mais significativo do reg 'A' ($v1) 

	sll $v0, $v0, 1 		# desloca para a esquerda o registrado P-A 

	sll $v1, $v1, 1  

	beq $t2, $0, di1  

	ori $v0, $v0, 1 		# coloca 1 no bit menos significativo do registador 'P'($v0) 

di1: sub $t2, $v0, $s0 		# subtrai 'P'($v0) do divisor ($s0) 

	blt $t2, $0, di2 

	add $v0, $t2, $0 		# se subtra��o positiva,'P'($v0) recebe o valor da subtra��o 

	ori $v1, $v1, 1 		# e 'A'($v1) recebe 1 no bit menos significativo 

di2: addi $t1, $t1, -1 		# decrementa o n�mero de itera��es  

	bne $t1, $0, dloop  

	jr $ra    

   

   

  

.data 

.align 2 

n:              .word 10 

mediana:	.word 0 

media:		.word 0 

moda:		.word 0 

vezes:		.word 0 

vet:		.word 3 5 8 4 1 8 6 7 4 4 

resMediadaPar:	.asciiz "\nMediana par: " 

resMediadaImpar:.asciiz "\nMediana impar: " 

resMedia:	.asciiz "\nMedia: " 

resModa:	.asciiz "Moda: " 

resVezesModa:	.asciiz "\nModaVezes: " 

resSort:	.asciiz "\nOrdenado com BubleSort" 

espaco:		.asciiz " " 