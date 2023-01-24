.data
	
	mensagemInicial: .asciiz "Para jogar deves digitar o número correspondente a casa.\nDigite 1 para prosseguir, caso contrário o jogo encerrará.\n"
	mensagemRodada: .asciiz "Digite em qual posição marcar: \n"
	msgPosicaoInvalida: .asciiz "Essa não é uma posição válida. Digite novamente.\n"
	msgPosicaoOcupada: .asciiz "Essa casa já está ocupada, digite outra.\n"
	msgRematch: .asciiz "\nQuer jogar novamente?\nDigite 1 para prosseguir, caso contrário o jogo encerrará.\n"
	msgPontuacao: .asciiz "\nPlayer: "
	msgPontuacao2: .asciiz " X Computador: "
	
	pontuacaoPlayer: .word 0
	pontuacaoMaquina: .word 0
	
	turno: .word 1
	
	
	valorCasa:		# 1 | 2 | 3
		.align 2       	#___|___|___
		.space 36 	# 4 | 5 | 6
				#___|___|___
				# 7 | 8 | 9
				#   |   |
	tabColuna: .asciiz "\n     |     |     \n"
	tabLinha: .asciiz "\n_ _ _|_ _ _|_ _ _\n     |     |   \n"
	tabDivisao: .ascii "  |  "
	
.text
	
	.main:
		move $t0, $zero # define o $t0 como o i que percorrerá a função
		li $t1, 36
		li $t2, 1
	
		demonstracao: #inicializa os valores de cada casa com sua posição
			sw $t2, valorCasa($t0)
			addi $t0, $t0, 4
			addi $t2, $t2, 1
			bne $t0, $t1, demonstracao
			
		li $v0, 4
		la $a0, mensagemInicial
		syscall
			
		la $a1, valorCasa # carrega o endereço do array em $a0	
		jal imprimeTabuleiro
		
		li $v0, 5 # lendo inteiro para prosseguir
		syscall
		
		bne $v0, 1, end # caso inteiro lido seja diferente de 1 o jogo termina
		recomeca:
		li $t1, 1
		sw $t1, turno
		
		move $t0, $zero
		li $t1, 36
		arrayZerado: #inicializa os valores de cada casa com o número 0
			sw $zero, valorCasa($t0)
			addi $t0, $t0, 4
			bne $t0, $t1, arrayZerado	
		
		partida:						
														
		jal imprimeTabuleiro # imprime o tabuleiro	
		
		lw $t0, turno # descobre de quem é o turno, se turno % 2 = 1 -> jogador, se turno % 2 = 0 -> computador
		li $t1, 2
		div $t0, $t1
		mfhi $t0
		beq $t0, 0, turnoComputador
		
		jal setaPosicao # verifica se é possível colocar o X naquela posição
		li $t0, -1
		sw $t0, valorCasa($v0) # coloca o X na posição correta q veio da função 
		
		j turnoJogador # pula o turno do computador
		
		turnoComputador:
		
		jal maquina # verifica se é possível colocar o O naquela posição
		li $t0, -2
		sw $t0, valorCasa($v0) # coloca o O na posição correta q veio da função
		
		turnoJogador:
		
		jal verificadorVitoria # verificação se houve vitória
		
		beq $v0, 1, vitoria
		
		# alternância de turnos
		
		lw $t0, turno # carrega o conteudo da variável para %t0
		addi $t0, $t0, 1 # soma 1 turno
		sw $t0, turno # altera o valor dentro da variável 
		bgt $t0, 9, end 
			
		j partida
	
		vitoria:
		
		lw $t0, turno # descobre de quem é o turno, se turno % 2 = 1 -> jogador, se turno % 2 = 0 -> computador
		li $t1, 2
		div $t0, $t1
		mfhi $t0
		beq $t0, 0, compVenceu

		lw $t0, pontuacaoPlayer
		addi $t0, $t0, 1
		sw $t0, pontuacaoPlayer
		j end				
		
		compVenceu:
		lw $t0, pontuacaoMaquina
		addi $t0, $t0, 1
		sw $t0, pontuacaoMaquina
	
		j end
	
	maquina:
		
		la $t0, ($a1) # recebe o array do tab
		la $v1, ($ra) # guarda o endereço da main
		
		jal jogoTerminal
		bne $v0, 1, primeiraPosicao		
		
		la $a1, valorCasa # recebe array p/ a1
		lw $a2, turno # recebe turno 
				
		jal decisao
		move $t2, $v0
		
		j sair	
		
		primeiraPosicao:
		
		la $t0, ($a1) # recebe o array do tab
		li $t2, 1 # i = 1
	
		looping:		
		
		lw $t1, ($t0) 
		
		beq $t1, 0, sair
		
		addi $t2, $t2, 1 # próx pos do array
		addi $t0, $t0, 4 # i++
		ble $t2, 9, looping
			
		sair:
		
		move $a2, $t2 
		jal setaPosicao
		
		la $ra, ($v1) # devolve o endereço da main para $ra
		
		jr $ra
	
	decisao:
		
		la $s7, ($ra)
		la $t0, ($a1) # carrega array
		lw $t1, ($t0) # carrega primeira posição
		
		beq $a2, 2, primeiraJogada
		jal vitoriaProximaRodada
		bgtz $v0, sairDecisao
		j segundaJogada
		
		primeiraJogada:
		seq $t1, $t1, 0
		beq $t1, 1, posicao1
		j posicao3
		
		segundaJogada:
		la $t0, valorCasa
		li $t2, 1
		ateAchar:
		lw $t1, ($t0)
		beqz $t1, achouVago
		addi $t0, $t0, 4
		addi $t2, $t2, 1		
		j ateAchar
		achouVago:
		move $v0, $t2
		j sairDecisao
		
		posicao9:
		li $v0, 9
		j sairDecisao		
		
		posicao8:
		li $v0, 8
		j sairDecisao		
		
		posicao7:
		li $v0, 7
		j sairDecisao		
		
		posicao6:
		li $v0, 6
		j sairDecisao		
		
		posicao5:
		li $v0, 5
		j sairDecisao		
				
		posicao4:
		li $v0, 4
		j sairDecisao		
		
		posicao3:
		li $v0, 3
		j sairDecisao
				
		posicao2:
		li $v0, 2
		j sairDecisao
		
		posicao1:
		li $v0, 1
		
		sairDecisao:
		jr $s7
	
	vitoriaProximaRodada:
		
		li $s0, -1
		la $t0, valorCasa
		move $t4, $zero # iterador 
		
		linhaQ: # verifica se algo é igual nas linhas
		
		move $t5, $zero
		move $t6, $zero
		
		bge $t4, 3, fimLinhaQ # enquanto i < 3
		
		lw $t1, ($t0) # pos 1, 4, 7
		addi $t0, $t0, 4
		lw $t2, ($t0) # pos 2, 5, 8
		addi $t0, $t0, 4
		lw $t3, ($t0) # pos 3, 6, 9
		addi $t0, $t0, 4
		
		addi $t4, $t4, 1 # i++
		
		beqz $t1, zeroLinha
		beqz $t2, zeroLinha
		beqz $t3, zeroLinha
		
		j linhaQ 				 						
		zeroLinha:
		beqz $t1, linha23 
		beqz $t2, linha13
		j linha12
		
		linha23:
		beqz $t2, linhaQ
		beq $t2, $t3, achouLinha
		j linhaQ
		
		linha13:
		beqz $t1, linhaQ
		beq $t1, $t3, achouLinha
		j linhaQ
		
		linha12:
		beqz $t1, linhaQ    
		beq $t1, $t2, achouLinha
		j linhaQ
		
		achouLinha:
		move $s0, $t4
		subi $s0, $s0, 1
		j fimVitoria
		
		fimLinhaQ:	
	
		move $t4, $zero # i = 0
		subi $t0, $t0, 36 # retorna para o início do array
		
		colunaQ: # verifica se algo é igual nas colunas
		
		bge $t4, 3, fimColunaQ # enquanto i < 3
		
		lw $t1, ($t0) # pos 1, 2, 3
		addi $t0, $t0, 12
		lw $t2, ($t0) # pos 4, 5, 6
		addi $t0, $t0, 12
		lw $t3, ($t0) # pos 7, 8, 9
		subi $t0, $t0, 20
		
		addi $t4, $t4, 1 # i++
		
		beqz $t1, zeroColuna
		beqz $t2, zeroColuna
		beqz $t3, zeroColuna
		
		j colunaQ 				 						
		zeroColuna:
		beqz $t1, coluna23 
		beqz $t2, coluna13
		j coluna12
		
		coluna23:
		beq $t2, $t3, achouColuna
		j colunaQ
		
		coluna13:
		beq $t1, $t3, achouColuna
		j colunaQ
		
		coluna12:    
		beq $t1, $t2, achouColuna
		j colunaQ
		
		achouColuna:
		addi $t4, $t4, 2
		move $s0, $t4
		j fimVitoria
		
		fimColunaQ:			
	
		move $t4, $zero # i = 0
		subi $t0, $t0, 12 # retorna para o início do array
		
		diagonalQ: # verifica se algo é igual nas diagonais
		
		li $t5, 1
		li $t6, 16
		add $t5, $t5, $t4
		div $t6, $t5 
		mflo $t5
		
		bge $t4, 2, fimDiagonalQ # enquanto i < 2
		
		lw $t1, ($t0) # pos 1, 3
		add $t0, $t0, $t5
		lw $t2, ($t0) # pos 5, 5
		add $t0, $t0, $t5
		lw $t3, ($t0) # pos 9, 7
		subi $t0, $t0, 24
		
		addi $t4, $t4, 1 # i++
		
		beqz $t1, zeroDiagonal
		beqz $t2, zeroDiagonal
		beqz $t3, zeroDiagonal
		
		j diagonalQ 				 						
		zeroDiagonal:
		beqz $t1, diagonal23 
		beqz $t2, diagonal13
		j diagonal12
		
		diagonal23:
		beq $t2, $t3, achouDiagonal
		j diagonalQ
		
		diagonal13:
		beq $t1, $t3, achouDiagonal
		j diagonalQ
		
		diagonal12:    
		beq $t1, $t2, achouDiagonal
		j diagonalQ
		
		achouDiagonal:
		addi $t4, $t4, 5
		move $s0, $t4
		j fimVitoria
		
		fimDiagonalQ:		
		
		j sairQuase
		fimVitoria:
		
		blt $s0, 3, vitLinha
		blt $s0, 6, vitColuna
		j vitDiagonal
		
		vitLinha:
		la $t0, valorCasa
		mul $s0, $s0, 3
		mul $t2, $s0, 4
		addi $s0, $s0, 1
		
		add $t0, $t0, $t2
		lw $t1, ($t0)
		
		beqz $t1, sairQuase
		addi $t0, $t0, 4
		addi $s0, $s0, 1
		lw $t1, ($t0)
		
		beqz $t1, sairQuase
		addi $t0, $t0, 4
		addi $s0, $s0, 1
		
		j sairQuase
				
		vitColuna:
		sub $s0, $s0, 2
		sub $t2, $s0, 1
		mul $t2, $t2, 4
		
		la $t0, valorCasa
		add $t0, $t0, $t2
		
		lw $t1, ($t0)
		beqz $t1, sairQuase
		addi $t0, $t0, 12
		addi $s0, $s0, 3
		lw $t1, ($t0)
		beqz $t1, sairQuase
		addi $t0, $t0, 12
		addi $s0, $s0, 3
		
		j sairQuase
		
		vitDiagonal:
		
		beq $s0, 6, diagonalPrimeira
		
		li $s0, 3

		addi $t0, $t0, 8

		lw $t1, ($t0)
		beqz $t1, sairQuase
		
		addi $t0, $t0, 8
		addi $s0, $s0, 2
		lw $t1, ($t0)
		beqz $t1, sairQuase
		
		addi $t0, $t0, 8
		addi $s0, $s0, 2
		
		j sairQuase			
						
		diagonalPrimeira:
		li $s0, 1
		
		sub $t0, $t0, 8
		lw $t1, ($t0)
		beqz $t1, sairQuase
		
		addi $t0, $t0, 16
		addi $s0, $s0, 4
		lw $t1, ($t0)
		beqz $t1, sairQuase
		
		addi $t0, $t0, 16
		addi $s0, $s0, 4
		
		j sairQuase		
		
		sairQuase:
		move $v0, $s0
		jr $ra
	
	jogoTerminal: # função que determina quando não existe mais possibilidade de vitória para nenhum
	
		la $t0, ($a1)
		
		### verificação de 2 casa vazia na mesma reta
		
		move $t4, $zero # iterador 
		li $t7, 0
		
		linhaT: # verifica se o jogo é terminal nas linhas
		
		lw $t1, ($t0) # pos 1, 4, 7
		addi $t0, $t0, 4
		lw $t2, ($t0) # pos 2, 5, 8
		addi $t0, $t0, 4
		lw $t3, ($t0) # pos 3, 6, 9
		addi $t0, $t0, 4
		
		addi $t4, $t4, 1 # i++
		
		beqz $t1, verificacaoLinha
		beqz $t2, verificacaoLinha2
		j repeticaoLinha
		
		verificacaoLinha:
		
		beqz $t2, naoTerminal
		beqz $t3, naoTerminal
		j repeticaoLinha
		
		verificacaoLinha2:
		
		beqz $t3, naoTerminal		 
		
		repeticaoLinha:
		blt $t4, 3, linhaT # enquanto i < 3						
		
		fimLinhaT:
		
		move $t4, $zero # i = 0
		subi $t0, $t0, 36 # retorna para o início do array
		
		colunaT: # verifica se o jogo é terminal nas colunas
		
		lw $t1, ($t0) # pos 1, 2, 3
		addi $t0, $t0, 12
		lw $t2, ($t0) # pos 4, 5, 6
		addi $t0, $t0, 12
		lw $t3, ($t0) # pos 7, 8, 9
		subi $t0, $t0, 20
		
		addi $t4, $t4, 1 # i++
		
		beqz $t1, verificacaoColuna
		beqz $t2, verificacaoColuna2
		j repeticaoColuna
		
		verificacaoColuna:
		
		beqz $t2, naoTerminal
		beqz $t3, naoTerminal
		j repeticaoColuna
		
		verificacaoColuna2:
		
		beqz $t3, naoTerminal
		
		repeticaoColuna:
		blt $t4, 3, colunaT # enquanto i < 3			
		
		fimColunaT:		
		
		move $t4, $zero # i = 0
		subi $t0, $t0, 12 # retorna para o início do array
		
		diagonalT: # verifica se o jogo é terminal nas diagonais
		
		li $t5, 1
		li $t6, 16
		add $t5, $t5, $t4
		div $t6, $t5 
		mflo $t5
		
		lw $t1, ($t0) # pos 1, 3
		add $t0, $t0, $t5
		lw $t2, ($t0) # pos 5, 5
		add $t0, $t0, $t5
		lw $t3, ($t0) # pos 9, 7
		subi $t0, $t0, 24
		
		addi $t4, $t4, 1 # i++
		
		beqz $t1, verificacaoDiagonal
		beqz $t2, verificacaoDiagonal2
		j repeticaoDiagonal
		
		verificacaoDiagonal:
		
		beqz $t2, naoTerminal
		beqz $t3, naoTerminal
		j repeticaoDiagonal
		
		verificacaoDiagonal2:
		
		beqz $t3, naoTerminal
		
		repeticaoDiagonal:
		blt $t4, 2, diagonalT # enquanto i < 2	
		
		### verificação de X e O na mesma reta
		
		move $t4, $zero # iterador 
		
		linhaTA: # verifica se o jogo é terminal nas linhas
		
		lw $t1, ($t0) # pos 1, 4, 7
		addi $t0, $t0, 4
		lw $t2, ($t0) # pos 2, 5, 8
		addi $t0, $t0, 4
		lw $t3, ($t0) # pos 3, 6, 9
		addi $t0, $t0, 4
		
		addi $t4, $t4, 1 # i++
		
		beq $t1, -1, verificacaoLinhaA
		beq $t2, -2, verificacaoLinhaA2
		beq $t3, -1, verificacaoLinhaA3
		j naoTerminal
		
		verificacaoLinhaA:
		
		beq $t2, -2, repeticaoLinhaA
		beq $t3, -2, repeticaoLinhaA
		j naoTerminal
		
		verificacaoLinhaA2:
		
		beq $t3, -1, repeticaoLinhaA 
		j naoTerminal		 
		
		verificacaoLinhaA3:
		
		beq $t2, -2, repeticaoLinhaA
		j naoTerminal
		
		repeticaoLinhaA:
		blt $t4, 3, linhaTA # enquanto i < 3						
		
		fimLinhaTA:
		
		move $t4, $zero # i = 0
		subi $t0, $t0, 36 # retorna para o início do array
		
		colunaTA: # verifica se o jogo é terminal nas colunas
		
		lw $t1, ($t0) # pos 1, 2, 3
		addi $t0, $t0, 12
		lw $t2, ($t0) # pos 4, 5, 6
		addi $t0, $t0, 12
		lw $t3, ($t0) # pos 7, 8, 9
		subi $t0, $t0, 20
		
		addi $t4, $t4, 1 # i++
		
		beq $t1, -1, verificacaoColunaA
		beq $t2, -2, verificacaoColunaA2
		beq $t3, -1, verificacaoColunaA3
		j naoTerminal
		
		verificacaoColunaA:
		
		beq $t2, -2, repeticaoColunaA
		beq $t3, -2, repeticaoColunaA
		j naoTerminal
		
		verificacaoColunaA2:
		
		beq $t3, -1, repeticaoColunaA 
		j naoTerminal		 
		
		verificacaoColunaA3:
		
		beq $t2, -2, repeticaoColunaA
		j naoTerminal
		
		repeticaoColunaA:
		blt $t4, 3, colunaTA # enquanto i < 3			
		
		fimColunaTA:		
		
		move $t4, $zero # i = 0
		subi $t0, $t0, 12 # retorna para o início do array
		
		diagonalTA: # verifica se o jogo é terminal nas diagonais
		
		li $t5, 1
		li $t6, 16
		add $t5, $t5, $t4
		div $t6, $t5 
		mflo $t5
		
		lw $t1, ($t0) # pos 1, 3
		add $t0, $t0, $t5
		lw $t2, ($t0) # pos 5, 5
		add $t0, $t0, $t5
		lw $t3, ($t0) # pos 9, 7
		subi $t0, $t0, 24
		
		addi $t4, $t4, 1 # i++
		
		beq $t1, -1, verificacaoDiagonalA
		beq $t2, -2, verificacaoDiagonalA2
		beq $t3, -1, verificacaoDiagonalA3
		j naoTerminal
		
		verificacaoDiagonalA:
		
		beq $t2, -2, repeticaoDiagonalA
		beq $t3, -2, repeticaoDiagonalA
		j naoTerminal
		
		verificacaoDiagonalA2:
		
		beq $t3, -1, repeticaoDiagonalA 
		j naoTerminal		 
		
		verificacaoDiagonalA3:
		
		beq $t2, -2, repeticaoDiagonalA
		j naoTerminal
		
		repeticaoDiagonalA:
		blt $t4, 2, diagonalTA # enquanto i < 2													
		
		j terminal																								
		naoTerminal:
		li $t7, 1
		
		terminal:								
		
		move $v0, $t7
		jr $ra
	
	setaPosicao:
		
		lw $t3, turno
		li $s6, 2
		div $t3, $s6
		mfhi $t3
		beq $t3, 0, semPerguntar 
		
		li $v0, 4
		la $a0, mensagemRodada
		syscall
		
		entrada:
		
		li $v0, 5 # posição desejada
		syscall
		
		j entradaPronta
		
		semPerguntar:
		move $v0, $a2 
		
		entradaPronta:
		bgt $v0, 9, posicaoInvalida # verificam se o valor digitado está entre [1, 9]
		blt $v0, 1, posicaoInvalida
		
		move $t1, $v0 # move a entrada digitada para $t1
		
		subi $t1, $t1, 1 # (n-1)*4 → fórmula para saber a posição da memória para inteiro que é de 4 em 4,
		mul $t1, $t1, 4  #           convertendo a posição convencionada de 1 a 9 
		
		la $t0, ($a1) # carrega o endereço do array para $t0
		
		add $t0, $t0, $t1 # avança para a posição correta do array
		
		lw $t2, ($t0) # pega o valor dessa posição do array 
		
		bnez $t2, posicaoOcupada # verifica se essa casa está ocupada
		
		move $v0, $t1 # retorno da função = posição para colocar o X
		
		jr $ra
		
		posicaoInvalida:
		
		li $v0, 4
		la $a0, msgPosicaoInvalida
		syscall
		
		j entrada
		
		posicaoOcupada:
		
		li $v0, 4
		la $a0, msgPosicaoOcupada
		syscall
		
		j entrada
	
	verificadorVitoria:
			
		la $t0, ($a1)
		
		move $t4, $zero # iterador 
		
		linha: # verifica se algo é igual nas linhas
		
		bge $t4, 3, fimLinha # enquanto i < 3
		
		lw $t1, ($t0) # pos 1, 4, 7
		addi $t0, $t0, 4
		lw $t2, ($t0) # pos 2, 5, 8
		addi $t0, $t0, 4
		lw $t3, ($t0) # pos 3, 6, 9
		addi $t0, $t0, 4
		
		addi $t4, $t4, 1 # i++
		
		beqz $t1, linha
		bne $t1, $t2, linha # 1 == 2
		bne $t1, $t3, linha # 1 == 3
		
		j fimDoJogo # se chegou até aqui é pq são iguais 				 						
		
		fimLinha:
		
		move $t4, $zero # i = 0
		subi $t0, $t0, 36 # retorna para o início do array
		
		coluna: # verifica se algo é igual nas colunas
		
		bge $t4, 3, fimColuna # enquanto i < 3
		
		lw $t1, ($t0) # pos 1, 2, 3
		addi $t0, $t0, 12
		lw $t2, ($t0) # pos 4, 5, 6
		addi $t0, $t0, 12
		lw $t3, ($t0) # pos 7, 8, 9
		subi $t0, $t0, 20
		
		addi $t4, $t4, 1 # i++
		
		beqz $t1, coluna
		bne $t1, $t2, coluna # 1 == 2
		bne $t1, $t3, coluna # 1 == 3
		
		j fimDoJogo # se chegou até aqui é pq são iguais
		
		fimColuna:		
		
		move $t4, $zero # i = 0
		subi $t0, $t0, 12 # retorna para o início do array
		
		diagonal: # verifica se algo é igual nas diagonais
		
		li $t5, 1
		li $t6, 16
		add $t5, $t5, $t4
		div $t6, $t5 
		mflo $t5
		
		bge $t4, 2, fimDiagonal # enquanto i < 2
		
		lw $t1, ($t0) # pos 1, 3
		add $t0, $t0, $t5
		lw $t2, ($t0) # pos 5, 5
		add $t0, $t0, $t5
		lw $t3, ($t0) # pos 9, 7
		subi $t0, $t0, 24
		
		addi $t4, $t4, 1 # i++
		
		beqz $t1, diagonal
		bne $t1, $t2, diagonal # 1 == 2
		bne $t1, $t3, diagonal # 1 == 3
		
		j fimDoJogo # se chegou até aqui é pq são iguais		
		
		fimDiagonal:
		
		li $v0, 0
		jr $ra
														
		fimDoJogo:						
		
		li $v0, 1									
																													
		jr $ra												
																				
	imprimeTabuleiro:
		
		la $t0, ($a1) # carrega o endereço do array para $t0 
		li $t2, 0
		
		li $v0, 4
		la $a0, tabColuna
		syscall
			
		li $v0, 11
		li $a0, 32
		syscall
		syscall	 	  	
		
		j imprimirValor
		pularCasa1:
		addi $t2, $t2, 4
		
		li $v0, 4
		la $a0, tabDivisao
		syscall
		
		j imprimirValor
		pularCasa2:
		addi $t2, $t2, 4
			
		li $v0, 4
		la $a0, tabDivisao
		syscall
				
		j imprimirValor
		pularCasa3:
		addi $t2, $t2, 4		
				
		li $v0, 4
		la $a0, tabLinha
		syscall	
		
		li $v0, 11
		li $a0, 32
		syscall	  
		syscall	
		
		j imprimirValor
		pularCasa4:
		addi $t2, $t2, 4
		
		li $v0, 4
		la $a0, tabDivisao
		syscall
		
		j imprimirValor
		pularCasa5:
		addi $t2, $t2, 4
			
		li $v0, 4
		la $a0, tabDivisao
		syscall
				
		j imprimirValor
		pularCasa6:
		addi $t2, $t2, 4
		
		li $v0, 4
		la $a0, tabLinha
		syscall														
				
		li $v0, 11
		li $a0, 32
		syscall	  
		syscall	
		
		j imprimirValor
		pularCasa7:
		addi $t2, $t2, 4
		
		li $v0, 4
		la $a0, tabDivisao
		syscall
		
		j imprimirValor
		pularCasa8:
		addi $t2, $t2, 4
			
		li $v0, 4
		la $a0, tabDivisao
		syscall
				
		j imprimirValor
		pularCasa9:
		addi $t2, $t2, 4
		
		li $v0, 4
		la $a0, tabColuna
		syscall
										
		jr $ra
		
		imprimirValor:
		
		beq $t2, 4, casa2
		beq $t2, 8, casa3
		beq $t2, 12, casa4
		beq $t2, 16, casa5		
		beq $t2, 20, casa6
		beq $t2, 24, casa7
		beq $t2, 28, casa8
		beq $t2, 32, casa9
		
		lw $t1, 0($t0)
		lw $a0, 0($t0)		
		j casaDecidida
		
		casa2:
		lw $t1, 4($t0)
		lw $a0, 4($t0)		
		j casaDecidida
		
		casa3:
		lw $t1, 8($t0)
		lw $a0, 8($t0)		
		j casaDecidida
		
		casa4:
		lw $t1, 12($t0)
		lw $a0, 12($t0)		
		j casaDecidida
		
		casa5:
		lw $t1, 16($t0)
		lw $a0, 16($t0)		
		j casaDecidida
		
		casa6:
		lw $t1, 20($t0)
		lw $a0, 20($t0)		
		j casaDecidida
		
		casa7:
		lw $t1, 24($t0)
		lw $a0, 24($t0)		
		j casaDecidida
		
		casa8:
		lw $t1, 28($t0)
		lw $a0, 28($t0)
		j casaDecidida
		
		casa9:
		lw $t1, 32($t0)
		lw $a0, 32($t0)
		
		casaDecidida:
		blez $t1, casaXouO 
		
		li $v0, 1 
		j pularCasa
		
		casaXouO:
		li $v0, 11
		
		bltz $t1, casaNaoZero 
		li $a0, 32
		j pularCasa
				
		casaNaoZero:
		
		beq $t1, -1, casaX
		li $a0, 79
		j pularCasa
		
		casaX:
		li $a0, 88
						
		pularCasa:
		syscall
		
		beq $t2, 4, pularCasa2
		beq $t2, 8, pularCasa3	 			 			 			 		
		beq $t2, 12, pularCasa4
		beq $t2, 16, pularCasa5
		beq $t2, 20, pularCasa6
		beq $t2, 24, pularCasa7
		beq $t2, 28, pularCasa8
		beq $t2, 32, pularCasa9
		j pularCasa1
	
	end:
			
		la $a0, valorCasa 
		jal imprimeTabuleiro 
		
		li $v0, 4
		la $a0, msgPontuacao
		syscall	
		li $v0, 1
		lw $a0, pontuacaoPlayer
		syscall
		
		li $v0, 4
		la $a0, msgPontuacao2
		syscall	
		li $v0, 1
		lw $a0, pontuacaoMaquina
		syscall
		
		li $v0, 4
		la $a0, msgRematch
		syscall
		
		li $v0, 5
		syscall
		beq $v0, 1, recomeca
				
		li $v0, 10
		syscall
