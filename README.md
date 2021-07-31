# Lab3
Resultados de desempenho

Vetor com 10⁵ elementos
  * tempo sequencial = 0,003774s
  * tempo concorrente (2 threads) = 0,004138s
    * aceleração = 0,912035
  * tempo concorrente (4 threads) = 0,004064s
    * aceleração = 0,928642

Vetor com 10⁷ elementos
  * tempo sequencial = 0,143246s
  * tempo concorrente (2 threads) = 0,140144s 
    * aceleração = 1,022134
  * tempo concorrente (4 threads) = 0,127870s
    * aceleração = 1,120247

vetor com 10⁹ elementos
  * tempo sequencial = 13,381455s
  * tempo concorrente (2 threads) = 12,486374s 
    * aceleração = 1,071685
  * tempo concorrente (4 threads) = 11,772082s
    * aceleração = 1,136711
 
 O tempo de inicialização foi muito grande, fazendo que o aumento de threads não melhorasse tanto o desempenho.
 Com 10⁹ elementos, por exemplo, a inicialização demorou 10 segundos.
