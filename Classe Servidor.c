#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
  
    // Parte onde ficam os Dados da Mensagem!
 
struct bufferMensagem {  
    long tipomensagem;
    int resultado;    
    int numero1;
    int numero2;
} mensagem; 
  
int main() 
{ 
    key_t key; 
    int mensagemidentificacao; 
  
    // Precisa-se utilizar o Comando ("Ftok" - Correspondente Ã  FunÃ§Ã£o que vai gerar Ã  chave!)
 
    key = ftok("arquivo", 65); 
  
    // Precisa-se utilizar o Comando ("Msgget" - Funciona para criar a fila de mensagens e retornando a mesma!)

    mensagemidentificacao = msgget(key, 0666 | IPC_CREAT); 
  
    // Precisa-se utilizar o Comando ("Msgrcv" - Funciona para receber a mensagem do cliente!)

    msgrcv(mensagemidentificacao, &mensagem, sizeof(mensagem), 1, 0); 
    
    // Precisa-se realizar Ã  soma dos numeros enviados do cliente!

    mensagem.resultado = (mensagem.numero1 + mensagem.numero2);
     
    printf("Querido UsuÃ¡rio, os NÃºmeros recebidos em nosso Sistema sÃ£o: %d  %d \n", mensagem.numero1, mensagem.numero2); 

    // Precisa-se reenviar o bloco de dados com a soma!

    msgsnd(mensagemidentificacao, &mensagem, sizeof(mensagem), 0);  
  
    // Precisa-se fechar a fila de mensagem!

    msgctl(mensagemidentificacao, IPC_RMID, NULL);
 
    // Fim do CÃ³digo!

    return 0; 
}
