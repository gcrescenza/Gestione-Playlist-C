
#include "fileHandler.h"

int contaRigheCSV(const char* filename)
{    FILE* file=fopen(filename,"r");
    char line[1000];

    int i=0;
    if(file==NULL)
    {
        return -1;
    }
    else
    {
        while(!feof(file))
        {if(fgets(line,sizeof(line),file)!=NULL)
                i++;
        }

    }
    fclose(file);
    return i;
}
