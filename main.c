#include <stdio.h>
#include <stdlib.h>

#define INPUTFILE "casy.txt"
#define OUTPUTFILE "odpoledne.txt"

int pulnoc(int hodiny, int minuty, int sekundy) {
    return hodiny * 3600 + minuty * 60 + sekundy;
}

int prevod(int hodiny) {
    if (hodiny > 12) {
        hodiny -= 12;
    } else if (hodiny == 0) {
        hodiny = 12;
    } else {
        hodiny = hodiny;
    }
    return hodiny;
}


void hlavicka(const char *text, FILE *file) {
    fprintf(file, "%8s\n", text);
    fprintf(file, "----------------------------------------------------------\n");
    fprintf(file, "poradi casu|evropsky cas|anglicky cas|sekundy od pulnoci");
    fprintf(file, "----------------------------------------------------------\n");
};

void radek(int poradi, int hodiny, int minuty, int sekundy, FILE *file) {
    const char *text = (hodiny > 12) ? "PM" : "AM";
    fprintf(file, "%02d|%02d:%02d:%02d|%02d:%02d:%02d %s|%d|\n", poradi, hodiny, minuty, sekundy, prevod(hodiny), minuty, sekundy,
            text, pulnoc(hodiny, minuty, sekundy));
}

int main() {
    FILE *fr;
    FILE *fw;
    int hodiny;
    int minuty;
    int sekundy;
    int poradi = 0;
    int souborPoradi =0;
    if ((fr = fopen(INPUTFILE, "r")) == NULL) {
            printf("Nepodarilo se otevrit soubor %s. Program bude ukoncen.\n", INPUTFILE);
            return EXIT_FAILURE;
        }
    if ((fw = fopen(OUTPUTFILE, "w")) == NULL) {
        printf("Nepodarilo se otevrit soubor %s.\n", OUTPUTFILE);
    }
    hlavicka("U D A J E  Z E  S O U B O R U", stdout);
    hlavicka("O D P O L E D N E", fw);
    while (fscanf(fr, "%d %d %d", &hodiny, &minuty, &sekundy) == 3) {
        poradi++;
        radek(poradi, hodiny, minuty, sekundy, stdout);
        if (hodiny > 12) {
            souborPoradi++;
            radek(souborPoradi, hodiny, minuty, sekundy, fw);
        }
    }
    if (fclose(fr) == EOF) {
        printf("Nepodarilo se zavrit soubor %s.\n", INPUTFILE);
    }
    if (fclose(fw) == EOF) {
        printf("Nepodarilo se zavrit soubor %s.\n", OUTPUTFILE);
    }

    return 0;
}

