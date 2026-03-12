#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DISEASES 200
#define MAX_SYMPTOMS 10
#define MAX_LENGTH 100

/* Structure to store disease data */
struct Disease {
    char name[MAX_LENGTH];
    char symptoms[MAX_SYMPTOMS][MAX_LENGTH];
    int symptom_count;
};

/* Function to remove newline characters from strings */
void trim_newline(char *str)
{
    str[strcspn(str, "\n")] = 0;
}

/* Function to load diseases and symptoms from file */
int load_data(struct Disease diseases[])
{
    FILE *fp = fopen("human_health.txt", "r");

    if (fp == NULL)
    {
        printf("Error opening disease dataset file.\n");
        return 0;
    }

    char line[200];
    int disease_index = -1;

    while (fgets(line, sizeof(line), fp))
    {
        trim_newline(line);

        if (strlen(line) == 0)
            continue;

        /* If line contains ':' it is a disease name */
        if (strchr(line, ':'))
        {
            disease_index++;

            strtok(line, ":");
            strcpy(diseases[disease_index].name, line);
            diseases[disease_index].symptom_count = 0;
        }
        else
        {
            char *symptom = strchr(line, '.');

            if (symptom != NULL)
            {
                symptom += 2;

                strcpy(
                    diseases[disease_index]
                        .symptoms[diseases[disease_index].symptom_count],
                    symptom);

                diseases[disease_index].symptom_count++;
            }
        }
    }

    fclose(fp);

    return disease_index + 1;
}

/* Function to predict disease based on symptoms */
void predict_disease(struct Disease diseases[], int total_diseases)
{
    int n;
    char user_symptoms[10][MAX_LENGTH];

    printf("\nEnter number of symptoms you have: ");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++)
    {
        printf("Enter symptom %d: ", i + 1);
        fgets(user_symptoms[i], MAX_LENGTH, stdin);
        trim_newline(user_symptoms[i]);
    }

    int best_match = -1;
    int max_score = 0;

    for (int i = 0; i < total_diseases; i++)
    {
        int score = 0;

        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < diseases[i].symptom_count; k++)
            {
                if (strcasecmp(user_symptoms[j], diseases[i].symptoms[k]) == 0)
                {
                    score++;
                }
            }
        }

        if (score > max_score)
        {
            max_score = score;
            best_match = i;
        }
    }

    if (best_match != -1)
    {
        printf("\nPossible Disease Prediction: %s\n", diseases[best_match].name);
        printf("Matching Symptoms: %d\n", max_score);
    }
    else
    {
        printf("\nNo disease matched your symptoms.\n");
    }
}

/* Function to display diseases stored in file */
void display_diseases(struct Disease diseases[], int total)
{
    printf("\nAvailable Diseases in Dataset:\n\n");

    for (int i = 0; i < total; i++)
    {
        printf("%d. %s\n", i + 1, diseases[i].name);
    }
}

/* Main menu */
int main()
{
    struct Disease diseases[MAX_DISEASES];

    int total_diseases = load_data(diseases);

    if (total_diseases == 0)
        return 0;

    int choice;

    while (1)
    {
        printf("\n===== DISEASE PREDICTOR SYSTEM =====\n");
        printf("1. Display Diseases in Dataset\n");
        printf("2. Predict Disease\n");
        printf("3. Exit\n");
        printf("====================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        getchar();

        switch (choice)
        {
        case 1:
            display_diseases(diseases, total_diseases);
            break;

        case 2:
            predict_disease(diseases, total_diseases);
            break;

        case 3:
            printf("Exiting program.\n");
            exit(0);

        default:
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
