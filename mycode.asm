org 100h
         
; *
; ax = c
; bx = b
mov ax, 2
mov bx, 4
mul bx
push ax

; +
; uno de sus operadores es un resultado anterior
; a
pop ax
add ax, 1
push ax

; / 
; ax = d
; bx = e
; ax / bx
mov ax, 6
mov bx, 3
div bx
push ax

; -
; los dos operadores son resultados anteriores
pop bx ; división
pop ax ; suma
sub ax, bx
push ax


