/*
* Alunos:
* - Fabricio Guite Pereira
* - Luiz Guilherme Durau Rodrigues
* Curso:
* - Ciência da Computação
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "FreeRTOS.h"
#include "basic_io.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"
/* Tamanho máximo do buffer utilizado para impressão na tela */
#define BUFSIZE 384
volatile char sentido[12] = "horario"; /* sentido */
volatile char direcao[12] = "frente"; /* frente e trás */
volatile char orientacao[12] = "esquerda"; /* esquerda e direita */
SemaphoreHandle_t xBinary;
int motor0 = 100;
int motor1 = 100;
int motor2 = 100;
int motor3 = 100;

void radio_frequencia(void* pvParameters) {
    int x, y, z;
    for (;;) {
        vPrintString("Radio\n");
        x = rand() % 100;
        y = rand() % 100;
        z = rand() % 100;
        if (x % 2 == 0) {
            snprintf(sentido, 12, "horario");
        } else {
            snprintf(sentido, 12, "antihorario");
        }
        if (y % 2 == 0) {
            snprintf(direcao, 12, "frente");
        } else {
            snprintf(direcao, 12, "tras");
        }
        if (z % 2 == 0) {
            snprintf(orientacao, 12, "esquerda");
        } else {
            snprintf(orientacao, 12, "direita");
        }
        vTaskDelay(100 * portTICK_RATE_MS);
    }
    vTaskDelete(NULL);
}

void guinada(void* pvParameters) {
    char* mensagem = (char*)pvParameters;
    char buffer[BUFSIZE];
    for (;;) {
        if (strcmp(sentido, "horario") == 0) {
            /* girar sentido horário incrementando 1 vez a cada 10ms por 100 vezes (período 1s) */
            xSemaphoreTake(xBinary, portMAX_DELAY);
            motor0 = motor0 + 100;
            motor1 = motor1 - 100;
            motor2 = motor2 + 100;
            motor3 = motor3 - 100;
            /* Passar para o buffer as informações dos motores antes da impressão */
            snprintf(buffer, BUFSIZE, "%s virando sentido horário:\nmotor 0: %d motor 1: %d motor 2: %d motor 3: %d\n", mensagem, motor0, motor1, motor2, motor3);
            vPrintString(buffer);
            xSemaphoreGive(xBinary);
            vTaskDelay(1000 * portTICK_RATE_MS);
        }
        if (strcmp(sentido, "antihorario") == 0) {
            /* girar sentido anti-horário incrementando 1 vez a cada 10ms por 100 vezes (período 1s) */
            xSemaphoreTake(xBinary, portMAX_DELAY);
            motor0 = motor0 - 100;
            motor1 = motor1 + 100;
            motor2 = motor2 - 100;
            motor3 = motor3 + 100;
            snprintf(buffer, BUFSIZE, "%s virando sentido anti-horário:\nmotor 0: %d motor 1: %d motor 2: %d motor 3: %d\n", mensagem, motor0, motor1, motor2, motor3);
            vPrintString(buffer);
            xSemaphoreGive(xBinary);
            vTaskDelay(1000 * portTICK_RATE_MS);
        }
    }
    vTaskDelete(NULL);
}

void arfagem(void* pvParameters) {
    char* mensagem = (char*)pvParameters;
    char buffer[BUFSIZE];
    for (;;) {
        if (strcmp(direcao, "frente") == 0) {
            /* ir para frente incrementando 1 vez a cada 40ms por 25 vezes (período 1s) */
            xSemaphoreTake(xBinary, portMAX_DELAY);
            motor0 = motor0 - 25;
            motor1 = motor1 - 25;
            motor2 = motor2 + 25;
            motor3 = motor3 + 25;
            snprintf(buffer, BUFSIZE, "%s indo para frente:\nmotor 0: %d motor 1: %d motor 2: %d motor 3: %d\n", mensagem, motor0, motor1, motor2, motor3);
            vPrintString(buffer);
            xSemaphoreGive(xBinary);
            vTaskDelay(1000 * portTICK_RATE_MS);
        }
        if (strcmp(direcao, "tras") == 0) {
            /* ir para trás incrementando 1 vez a cada 40ms por 25 vezes (período 1s) */
            xSemaphoreTake(xBinary, portMAX_DELAY);
            motor0 = motor0 + 25;
            motor1 = motor1 + 25;
            motor2 = motor2 - 25;
            motor3 = motor3 - 25;
            snprintf(buffer, BUFSIZE, "%s indo para trás:\nmotor 0: %d motor 1: %d motor 2: %d motor 3: %d\n", mensagem, motor0, motor1, motor2, motor3);
            vPrintString(buffer);
            xSemaphoreGive(xBinary);
            vTaskDelay(1000 * portTICK_RATE_MS);
        }
    }
    vTaskDelete(NULL);
}

void rolagem(void* pvParameters) {
    char* mensagem = (char*)pvParameters;
    char buffer[BUFSIZE];
    for (;;) {
        if (strcmp(orientacao, "direita") == 0) {
            /* ir para direita incrementando 1 vez a cada 20ms por 50 vezes (período 1s) */
            xSemaphoreTake(xBinary, portMAX_DELAY);
            motor0 = motor0 + 50;
            motor1 = motor1 - 50;
            motor2 = motor2 - 50;
            motor3 = motor3 + 50;
            snprintf(buffer, BUFSIZE, "%s indo para direita:\nmotor 0: %d motor 1: %d motor 2: %d motor 3: %d\n", mensagem, motor0, motor1, motor2, motor3);
            vPrintString(buffer);
            xSemaphoreGive(xBinary);
            vTaskDelay(1000 * portTICK_RATE_MS);
        }
        if (strcmp(orientacao, "esquerda") == 0) {
            /* ir para esquerda incrementando 1 vez a cada 20ms por 50 vezes (período 1s) */
            xSemaphoreTake(xBinary, portMAX_DELAY);
            motor0 = motor0 - 50;
            motor1 = motor1 + 50;
            motor2 = motor2 + 50;
            motor3 = motor3 - 50;
            snprintf(buffer, BUFSIZE, "%s indo para esquerda:\nmotor 0: %d motor 1: %d motor 2: %d motor 3: %d\n", mensagem, motor0, motor1, motor2, motor3);
            vPrintString(buffer);
            xSemaphoreGive(xBinary);
            vTaskDelay(1000 * portTICK_RATE_MS);
        }
    }
    vTaskDelete(NULL);
}

int main_(void) {
    srand(time(NULL));
    vSemaphoreCreateBinary(xBinary);
    /* Cria as tarefas */
    xTaskCreate(guinada, "Guinada", configMINIMAL_STACK_SIZE, (void*)"Guinada:", 1, NULL);
    xTaskCreate(arfagem, "Arfagem", configMINIMAL_STACK_SIZE, (void*)"Arfagem:", 1, NULL);
    xTaskCreate(rolagem, "Rolagem", configMINIMAL_STACK_SIZE, (void*)"Rolagem:", 1, NULL);
    xTaskCreate(radio_frequencia, "Radio frequencia", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
    vTaskStartScheduler();
    for (;;);
    return 0;
}
