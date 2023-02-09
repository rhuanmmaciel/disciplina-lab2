.data

input: .asciiz "Digite o ângulo em graus cos(x): "
output_1: .asciiz "cos("
output_2: .asciiz ") = : "
pi: .float 3.14159265359
pi_graus: .float 180.0

.text

.main:
	li $v0, 4
	la $a0, input
	syscall
	
	li $v0, 6
	syscall
	
	mov.s $f13, $f0
	
	mfc1 $a0, $f0
	jal conversor
	
	mov.s $f11, $f12

	mfc1 $a0, $f11
	jal taylor
	
	li $v0, 4
	la $a0, output_1
	syscall	

	li $v0, 2
	mov.s $f12, $f13
	syscall

	li $v0, 4
	la $a0, output_2
	syscall					
												
	li $v0, 2
	mov.s $f12, $f0
	syscall	
		
	li $v0, 10
	syscall

taylor:
	
	mtc1 $zero, $f0 # soma dos valores
	li $t6, -1
	move $t7, $ra
	
	loop: # repetirá 7 vezes
		addi $t6, $t6, 1
	
		mfc1 $a1, $f11
		move $a0, $t6
		jal potencia
		
		move $a0, $t6
		mul $a0, $a0, 2
		jal fatorial
		
		mtc1 $v0, $f9
		cvt.s.w $f9, $f9
		
		div.s $f12, $f10, $f9
		
		div $t5, $t6, 2
		mfhi $t5
		
		beqz $t5, par
		
		sub.s $f0, $f0, $f12
		j fim_loop
		
		par:
			add.s $f0, $f12, $f0
		
		fim_loop:
		blt $t6, 7, loop
	
	mfc1 $v0, $f0
	
	jr $t7

potencia:

	mul $a0, $a0, 2 # potencia
	mov.s $f10, $f11
	li $t0, 0
	
	beqz $a0, potencia_0
	potencia_repete:
		
		mul.s $f10, $f10, $f11
		
		addi $t0, $t0, 1
		move $t2, $t0
		addi $t2, $t2, 1
		
		bne $t2, $a0, potencia_repete
	
	mfc1 $v0, $f10
	j sair_potencia
	
	potencia_0:
	
		li $t2, 1
		mtc1 $t2, $f10
		cvt.s.w $f10, $f10
		mfc1 $v0, $f10
	
	sair_potencia:
	
	jr $ra

conversor:
	
	lwc1 $f1, pi # carrega pi para $f0
	lwc1 $f2, pi_graus # carrega 180 para #f2 
	
	mul.s $f12, $f0, $f1 # multiplica a entrada por pi
	div.s $f12, $f12, $f2 # divide o resultado por 180
	
	mfc1 $v0, $f12 # move o resultado para saída da função
	
	jr $ra

fatorial:

 	addiu $sp, $sp, -8      # ajusta a pilha para receber 2 itens
        sw    $ra, 4($sp)       # salva o endereço de retorno
        sw    $a0, 0($sp)       # salva o argumento da função

        bne   $zero, $a0, n_nao_igual_0 # se n!=0  calcule n*fatorial(n-1)

n_igual_0:

        add   $v0, $zero, 1     # retorna 1 = 0!
        j fatorial_epilogo      # epílogo  do procedimento

n_nao_igual_0:

        addi  $a0, $a0, -1      # a0 <- n-1
        jal   fatorial          # chamamos fatorial(n-1)
        lw    $a0, 0($sp)       # a0 <- n, restauramos n
	mul   $v0, $a0, $v0     # v0 <- n*fatorial(n-1), v0 valor de retorno
	lw    $ra, 4($sp)       # restaura o endereço de retorno

fatorial_epilogo:

        add   $sp, $sp, 8       # restaura a pilha - eliminamos 2 itens
        jr    $ra               # retorna para o procedimento chamador
					
