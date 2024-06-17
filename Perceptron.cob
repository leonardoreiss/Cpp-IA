       IDENTIFICATION DIVISION.
       PROGRAM-ID. PerceptronTraining.

       ENVIRONMENT DIVISION.
       CONFIGURATION SECTION.

       DATA DIVISION.
       WORKING-STORAGE SECTION.

       01  X1           PIC 99.
       01  X2           PIC 99.
       01  X3           PIC 99.
       01  Y            PIC 9.
       01  W1           PIC S9V99 COMP-3.
       01  W2           PIC S9V99 COMP-3.
       01  W3           PIC S9V99 COMP-3.
       01  WBIAS        PIC S9V99 COMP-3.
       01  TaxaApren    PIC S9V99 COMP-3.
       01  UseBias      PIC X.
       01  Iterations   PIC 9999 VALUE 0.
       01  Saida        PIC 9.
       01  MaxIterations PIC 9999 VALUE 1000.
       01  Temp-X1      PIC 99.
       01  Temp-X2      PIC 99.
       01  Temp-X3      PIC 99.
       01  Temp-Y       PIC 9.
       01  PairCount    PIC 9 VALUE 3.
       01  CASHW1       PIC S9V99 COMP-3.
       01  CASHW2       PIC S9V99 COMP-3.
       01  CASHW3       PIC S9V99 COMP-3.

       PROCEDURE DIVISION.
           DISPLAY "Deseja utilizar o bias? (S/N):"
           ACCEPT UseBias.

           DISPLAY "Entre com a taxa de aprendizagem:"
           ACCEPT TaxaApren.

           MOVE 0.2 TO W1.
           MOVE 0.2 TO W2.
           MOVE 0.2 TO W3.
           MOVE 0.2 TO WBIAS.

           PERFORM VARYING PairCount FROM 1 BY 1 UNTIL PairCount > 3
               DISPLAY "Val e valor esperado para o par " PairCount ":"
               ACCEPT Temp-X1
               ACCEPT Temp-X2
               ACCEPT Temp-X3
               ACCEPT Temp-Y

               PERFORM Train-Perceptron
               END-PERFORM

           DISPLAY "Pesos aprendidos pela rede:"
           DISPLAY "W1 = " W1
           DISPLAY "W2 = " W2
           DISPLAY "W3 = " W3

           IF UseBias = 'S'
               DISPLAY "WBIAS = " WBIAS
           END-IF

           DISPLAY "Qtd de iterações para o aprendizado: " Iterations

           DISPLAY "Teste com novos valores de entrada (x1, x2, x3):"
           ACCEPT X1.
           ACCEPT X2.
           ACCEPT X3.

           COMPUTE Saida = (W1 * X1) + (W2 * X2) + (W3 * X3)

           IF UseBias = 'S'
               ADD WBIAS TO Saida
           END-IF

           IF Saida >= 0
               MOVE 1 TO Saida
           ELSE
               MOVE 0 TO Saida
           END-IF

           DISPLAY "Saída para os novos valores de entrada: " Saida

           STOP RUN.

       Train-Perceptron.
           PERFORM UNTIL Iterations > MaxIterations
               MOVE 0 TO Saida
               COMPUTE Saida = (W1*Temp-X1)+(W2*Temp-X2)+(W3*Temp-X3)
               IF UseBias = 'S'
                   ADD WBIAS TO Saida
               END-IF
               IF Saida >= 0
                   MOVE 1 TO Saida
               ELSE
                   MOVE 0 TO Saida
               END-IF
               IF Saida NOT = Temp-Y
                COMPUTE W1 = W1+(TaxaApren * (Temp-Y - Saida)*Temp-X1)
                COMPUTE W2 = W2+(TaxaApren * (Temp-Y - Saida)*Temp-X2)
                COMPUTE W3 = W3+(TaxaApren * (Temp-Y - Saida)*Temp-X3)
                   IF UseBias = 'S'
                       COMPUTE WBIAS = WBIAS+(TaxaApren*(Temp-Y -Saida))
                   END-IF
               ELSE
                   EXIT PERFORM
               END-IF
               ADD 1 TO Iterations
               COMPUTE Saida = 0
           END-PERFORM.
