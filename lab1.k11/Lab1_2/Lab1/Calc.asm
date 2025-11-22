extern printf : proc
EXTERN K : QWORD

.data
    msg db 'Output from asm module is: %d', 0

.code
calc PROC
    ; Пролог
    sub rsp, 28h                     ; Виділяємо місце для вирівнювання стеку

    ; Переміщення аргументів у регістри
    mov rax, K                       ; Завантажуємо K у rax
    movsxd rcx, ecx                  ; Завантажуємо A у rcx (sign-extend до 64 біт)
    movsx rdx, dx                  ; Завантажуємо B у rdx (sign-extend до 64 біт)
    movsxd r8, r8d                   ; Завантажуємо E у r8 (sign-extend до 64 біт)

    ; Обчислення (A - B - K)
    sub rcx, rdx                     ; A - B
    sub rcx, rax                     ; (A - B) - K

    ; Обчислення ((A - B - K) * 2)
    lea rcx, [rcx*2]                 ; (A - B - K) * 2

    ; Перевірка знаку E та коригування для ділення
    test r8, r8
    jns positive_d
    add r8, 3

positive_d:
    sar r8, 2                        ; Ділимо E на 4 (арифметичний зсув вправо на 2)

    ; Додавання результатів: (A - B - K) * 2 + E / 4
    add rcx, r8                      ; Додаємо E / 4 до (A - B - K) * 2

    ; Збереження результату
    mov rax, rcx                     ; Результат у rax (для повернення)
    mov r12, rax                     ; Зберігаємо результат в r12

    ; Підготовка до виклику printf
    lea rcx, msg                     ; Форматоване повідомлення для printf
    mov rdx, rax                     ; Значення для виведення

    ; Виклик printf
    call printf

    ; Епілог
    mov rax, r12                     ; Повертаємо результат
    add rsp, 28h                     ; Відновлюємо стек
    ret                              ; Повертаємо результат у rax
calc ENDP
END
