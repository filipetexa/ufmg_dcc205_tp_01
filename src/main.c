#include "../include/OrdInd.h"
#include <stdio.h>

int main()
{
    OrdInd *ord = createOrdInd(1000); // Supondo que temos 1000 registros
    if (!loadFromFile(ord, "../tests/cad.r1000.p1000.xcsv"))
    {
        printf("Falha ao carregar dados\n");
    }
    else
    {
        printf("Dados carregados com sucesso\n");
        // Teste adicional: imprimir os primeiros 10 registros para verificar
        for (int i = 0; i < 10; i++)
        {
            printf("Nome: %s, ID: %s, Endereço: %s\n", ord->records[i].name, ord->records[i].id, ord->records[i].address);
        }
    }
    destroyOrdInd(ord);
    return 0;
}
