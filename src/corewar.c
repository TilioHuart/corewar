/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** Principal function of the corewar
*/

#include <stdlib.h>
#include <stdio.h>
#include "champions/champions.h"
#include "my.h"
#include "corewar.h"
#include "my_macros.h"
#include "op.h"
#include "virtualmachine/set_load_address.h"
#include "virtualmachine/initialize_vm.h"

static
void destroy_file_stream(cpu_t *cpu)
{
    if (cpu->champions == NULL)
        return;
    for (size_t i = 0; cpu->champions[i] != NULL &&
        i < cpu->init_champ; i += 1) {
        if (cpu->champions[i]->file_stream != NULL)
            fclose(cpu->champions[i]->file_stream);
    }
}

static
void destroy_champions(cpu_t *cpu)
{
    if (cpu == NULL)
        return;
    if (cpu->champions == NULL)
        return;
    destroy_file_stream(cpu);
    for (size_t i = 0; cpu->champions[i] != NULL;
        i += 1) {
        if (cpu->champions[i]->header != NULL)
            free(cpu->champions[i]->header);
        if (cpu->champions[i] != NULL)
            free(cpu->champions[i]);
    }
    if (cpu->champions != NULL)
        free(cpu->champions);
}

static
void display_winner(cpu_t *cpu)
{
    if (cpu == NULL || cpu->winner == -1 || cpu->winner_name == NULL)
        return;
    my_putstr("The player ");
    my_put_nbr(cpu->winner);
    my_putstr("(");
    my_putstr(cpu->winner_name);
    my_putstr(") has won.\n");
}

static
void initialize_memory(cpu_t *cpu)
{
    for (size_t i = 0; i < MEM_SIZE; i += 1)
        cpu->memory[i] = 0;
}

int execute_corewar(char const *const *argv)
{
    cpu_t cpu = { { 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    if (initialize_vm(&cpu, argv) == FAILURE) {
        destroy_champions(&cpu);
        return display_error("Unable to initialize the cpu\n");
    }
    initialize_memory(&cpu);
    if (retrieve_champions_instructions(&cpu) == FAILURE)
        return FAILURE;
    if (execute_arena(&cpu) == FAILURE)
        return FAILURE;
    display_winner(&cpu);
    destroy_champions(&cpu);
    return SUCCESS;
}
