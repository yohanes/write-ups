    BITS 32
global  func


 section .text  
    
func:     
    push   ebp
    mov    ebp,esp
    sub    esp,0x0
    push   edi
    push   esi
    ;;  make it 0
    xor    eax, eax
    xor    ebx,ebx
    mov    ecx,0x25
    cmp    DWORD [ebp+0x10],ecx
    jl     .done
    mov    esi,DWORD  [ebp+0xc]
    mov    edi,DWORD  [ebp+0x8]
    lea    edi,[edi+ecx*1-0x1]
.loop1:  
    mov    dx,bx
    and    dx,0x3
    mov    ax,0x1c7
    push   eax
    sahf   
    lodsb 
    pushf  
    xor    al,BYTE  [esp+0x4]
    xchg   dl,cl
    rol    ah,cl
    popf   
    adc    al,ah
    xchg       dl,cl            ; dl contains loop counter
    xor    edx,edx
    and    eax,0xff
    add    bx,ax
    scasb
    jne .wrong
    cmovne cx,dx
    pop    eax
    jecxz  .done
    sub    edi,0x2
    loop   .loop1
    jmp    .done
    xor    eax,eax
    jmp .done
    .wrong:
    shl  ecx, 8
    or  eax, ecx
.done:   
    pop    esi
    pop    edi
    mov    esp,ebp
    pop    ebp
    ret    
