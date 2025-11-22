.686
.model flat, c
printf proto c : vararg
EXTERN K : DWORD      ; Зовнішня змінна K, яку ми будемо використовувати

.data
msg db 'Result from calc: %d', 0

.code
calc PROC
    push ebp                    ; Зберігаємо старий вказівник стеку
    mov ebp, esp                ; Створюємо нову базу для стеку

    ; Завантажуємо аргументи
    mov eax, dword ptr [ebp + 8]    ; eax = a
    movsx ebx, word ptr [ebp + 12]   ; ebx = b
    mov edx, dword ptr [ebp + 16]   ; edx = e

    ; Обчислення: A - B
    sub eax, ebx                    ; eax = a - b

    ; Обчислення: A - B - K
    sub eax, K                      ; eax = a - b - K

    ; Обчислення: (A - B - K) * 2
    shl eax, 1                      ; eax = (a - b - K) * 2

    ; Корекція для від'ємних значень перед діленням на 4
    test edx, edx
    jns positive_d
    add edx, 3

positive_d:
    sar edx, 2                      ; edx = e / 4 (арифметичний зсув вправо на 2 біти)

    ; Додавання: (A - B - K) * 2 + E / 4
    add eax, edx                    ; eax = (a - b - K) * 2 + e / 4
    push eax    

    ; Підготовка до виклику printf
    push eax                        ; Аргумент результату для printf
    push offset msg                 ; Форматоване повідомлення
    call printf                     ; Викликаємо printf для виведення результату
    add esp, 8                      ; Очищуємо стек після виклику printf

    ; Відновлення стеку і повернення результату
    pop eax                         ; Відновлюємо esp
    pop ebp                         ; Відновлюємо старий вказівник стеку
    ret                             ; Повертаємо результат

calc ENDP
END
