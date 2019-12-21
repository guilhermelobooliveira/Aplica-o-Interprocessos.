#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
  
struct bufferMensagem {     
    long tipodamensagem;
    int resultado;    
    int numero1;
    int numero2;         
} mensagem; 
  
int main() 
{ 
    key_t key; 
    int mensagemidentificacao; 
  
    // Precisa-se utilizar o Comando ("Ftok" - Corresponde Ã  uma FunÃ§Ã£o que vai gerar Ã  chave!)
 
    key = ftok("arquivo", 65); 
  
    // Precisa-se utilizar o Comando ("Msgget" - Funciona para criar a fila de mensagens e retornando a mesma!)

    mensagemidentificacao = msgget(key, 0666 | IPC_CREAT); 
    mensagem.tipodamensagem = 1; 
  
    printf("Por favor, querido usuÃ¡rio, em nosso Sistema, digite dois nÃºmeros: ");
    scanf("%d %d", &mensagem.numero1,&mensagem.numero2); 
       
    // Precisa-se utilizar o Comando ("Msgsnd" - Funciona para Enviar para o Servidor!)
 
    msgsnd(mensagemidentificacao, &mensagem, sizeof(mensagem), 0);

    // Precisa-se utilizar o Comando ("Msgrcv" - Funciona para receber a mensagem do cliente!)

    msgrcv(mensagemidentificacao, &mensagem, sizeof(mensagem), 1, 0); 
  
    // Precisa-se mostrar o Resultado!

    printf("Querido UsuÃ¡rio, o Resultado da SomatÃ³ria em nosso Sistema Ã©: %d \n", mensagem.resultado);

    // Fim do CÃ³digo-Fonte! 
  
    return 0; 
} 
