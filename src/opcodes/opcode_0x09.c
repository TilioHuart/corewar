/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** Instructions for opcode zjump
*/

#include "my.h"
#include "op.h"
#include "virtualmachine/initialize_vm.h"
#include "champions/champions.h"

int execute_opcode_zjmp(cpu_t *cpu, champions_t *champion)
{
    size_t first_parameter = 0;

    if (cpu == NULL || champion == NULL)
        return display_error("Unable to retrieve structs for zjump\n");
    if (champion->carry == TRUE) {
        champion->program_counter += 5;
        champion->program_counter %= MEM_SIZE;
        return SUCCESS;
    }
    first_parameter = cpu->memory[(champion->program_counter + 1) % MEM_SIZE];
    first_parameter <<= 2;
    first_parameter += cpu->memory[(champion->program_counter + 2) % MEM_SIZE];
    first_parameter <<= 2;
    first_parameter += cpu->memory[(champion->program_counter + 3) % MEM_SIZE];
    first_parameter <<= 2;
    first_parameter += cpu->memory[(champion->program_counter + 4) % MEM_SIZE];
    champion->program_counter += (first_parameter % IDX_MOD);
    champion->program_counter %= MEM_SIZE;
    return SUCCESS;
}