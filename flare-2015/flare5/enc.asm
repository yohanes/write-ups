    BITS 32
global  encrypt
global xtab

 section .text  
    
encrypt:     
  push   ebx
  push   esi
  push   edi
  mov    edi,edx
  xor    esi,esi
  mov    ebx,ecx
  test   edi,edi
  je     .done
  lea    ecx,[ecx+0x0]

    .loop1:
mov    eax,0x24924925
mul    esi
mov    eax,esi
sub    eax,edx
shr    eax,1
add    eax,edx
shr    eax,0x3
lea    ecx,[eax*8+0x0]
sub    ecx,eax
mov    eax,esi
add    ecx,ecx
sub    eax,ecx
mov    al,BYTE  [eax+xtab]
add    BYTE  [esi+ebx*1],al
inc    esi
cmp    esi,edi
    jb     .loop1
    .done:
pop    edi
pop    esi
pop    ebx
ret    



    
    section .data

    xtab db "flarebearstare"
    
