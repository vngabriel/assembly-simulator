# assembly-simulator

Simulador assembly escrito na linguagem C, este projeto é uma simplificação do seguinte simulador assembly: <https://schweigi.github.io/assembler-simulator/>.

O simulador roda no terminal e tem a seguinte interface:
![Screenshot 2020-10-30 at 13 30 00](https://user-images.githubusercontent.com/67594575/97733507-b05a2580-1ab6-11eb-81a9-89f398931ba8.png)

Ele aceita os seguintes comandos:
* MOV registrador, constante
* MOV endereço de memória, constante
* MOV endereço de memória, registrador
* MOV registrador, endereço de memória
* ADD registrador, registrador
* ADD registrador, constante
* HLT fim da simulação

Observações: uma constante é indicada por um número inteiro, um endereço de memória é indicado por um número inteiro entre colchetes, exemplo: [10], e um registrador é indicado pelas letras A, B, C e D. O comando MOV é usada para mover um valor, e o comando ADD soma dois valores (O resultado da soma sempre fica no registrador).

O simulador na prática:

![Screenshot 2020-10-30 at 13 53 01](https://user-images.githubusercontent.com/67594575/97734107-7b9a9e00-1ab7-11eb-86cb-a45ff27a3c49.png)
