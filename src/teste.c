#include <stdio.h>
#include <time.h>

int main(void){

    int x = 0;
    int y = 0;
    FILE *fp = NULL;
    FILE *gnupipe = NULL;
    char *GnuCommands [] = {"set title \"Grafico tempo x entrada\"", "plot 'data.tmp'"};
    clock_t comeco, fim;

    fp = fopen("data.tmp", "w");
    gnupipe = _popen("gnuplot -persist", "w");

    comeco = clock();
    for (int i=0; i<1000000; i++){
        //if(i % 10 == 0){
        //    fprintf(fp, "%d %d\n", x, y);
        //}
        x = x+1;
        y = x*x;
        
    }
    fim = clock();
    fprintf(fp, "%d %d\n", 1, (fim - comeco)/ CLOCKS_PER_SEC);
    printf("Diferenca: %d\n", (fim - comeco)/ CLOCKS_PER_SEC);

    comeco = clock();
    for (int i=0; i<2000000; i++){
        //if(i % 10 == 0){
        //    fprintf(fp, "%d %d\n", x, y);
        //}
        x = x+1;
        y = x*x;
        
    }
    fim = clock();
    fprintf(fp, "%d %d\n", 2, (fim - comeco)/ CLOCKS_PER_SEC);
    printf("Diferenca: %d\n", (fim - comeco)/ CLOCKS_PER_SEC);

    comeco = clock();
    for (int i=0; i<10000000; i++){
        //if(i % 10 == 0){
        //    fprintf(fp, "%d %d\n", x, y);
        //}
        x = x+1;
        y = x*x;
        
    }
    fim = clock();
    fprintf(fp, "%d %d\n", 3, (fim - comeco)/ CLOCKS_PER_SEC);
    printf("Diferenca: %d\n", (fim - comeco)/ CLOCKS_PER_SEC);

    comeco = clock();
    for (int i=0; i<200000; i++){
        //if(i % 10 == 0){
         //   fprintf(fp, "%d %d\n", x, y);
        //}
        printf("%d\n", i);
        x = x+1;
        y = x*x;
        
    }
    fim = clock();
    fprintf(fp, "%d %d\n", 4, (fim - comeco)/ CLOCKS_PER_SEC);
    printf("Diferenca: %d\n", (fim - comeco)/ CLOCKS_PER_SEC);

    comeco = clock();
    for (int i=0; i<500000; i++){
        //fprintf(fp, "%d %d\n", x, y);
        printf("%d\n", i);
        x = x+1;
        y = x*x;
        
    }
    fim = clock();
    fprintf(fp, "%d %d\n", 5, (fim - comeco)/ CLOCKS_PER_SEC);

    printf("Diferenca: %d\n", (fim - comeco)/ CLOCKS_PER_SEC);

    for (int i=0; i<2; i++){
        fprintf(gnupipe, "%s\n", GnuCommands[i]);
    }

    return 0;
}