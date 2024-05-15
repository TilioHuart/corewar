/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** Instructions for opcode ldi
*/

#include "op.h"
#include "opcodes/opcodes.h"
#include "virtualmachine/initialize_vm.h"
#include "champions/champions.h"
#include "my.h"
#include <stddef.h>

static
int retrieve_sum(cpu_t *cpu, champions_t *champion, int *bytes, size_t sum)
{
    size_t first_param = 0;
    size_t second_param = 0;
    bool first_register = false;

    *bytes = retrieve_first_parameter(cpu, champion, &first_param, *bytes);
    if (*bytes == 2) {
        first_register = true;
        sum = cpu->memory[(champion->program_counter + (champion->registers[first_param] % IDX_MOD)) % MEM_SIZE];
        sum <<= 8;
        sum += cpu->memory[(champion->program_counter + (champion->registers[first_param] % IDX_MOD) + 1) % MEM_SIZE];
    } else {
        sum = cpu->memory[(champion->program_counter + (first_param % IDX_MOD)) % MEM_SIZE];
        sum <<= 8;
        sum += cpu->memory[(champion->program_counter + (first_param % IDX_MOD) + 1) % MEM_SIZE];
    }
    *bytes = retrieve_second_parameter(cpu, champion, &second_param, *bytes);
    if ((first_register == true && *bytes == 3) ||
        (first_register == false && *bytes == 4))
        sum += champion->registers[second_param];
    else
        sum += second_param;
    return sum;
}

int execute_opcode_ldi(cpu_t *cpu, champions_t *champion)
{
    size_t third_param = 0;
    size_t sum = 0;
    int bytes = 1;

    if (cpu == NULL || champion == NULL || champion->name == NULL)
        return display_error("Unable to retrieve structs in opcode ldi\n");
    champion->index = true;
    sum = retrieve_sum(cpu, champion, &bytes, sum);
    bytes = retrieve_third_parameter(cpu, champion, &third_param, bytes);
    champion->registers[third_param] = cpu->memory[(champion->program_counter + (sum % IDX_MOD)) % MEM_SIZE];
    champion->registers[third_param] <<= 8;
    champion->registers[third_param] += cpu->memory[(champion->program_counter + (sum % IDX_MOD)) % MEM_SIZE];
    champion->registers[third_param] <<= 8;
    champion->registers[third_param] += cpu->memory[(champion->program_counter + (sum % IDX_MOD)) % MEM_SIZE];
    champion->registers[third_param] <<= 8;
    champion->registers[third_param] += cpu->memory[(champion->program_counter + (sum % IDX_MOD)) % MEM_SIZE];
    champion->registers[third_param] <<= 8;
    champion->program_counter = (champion->program_counter + bytes + 1) % MEM_SIZE;
    return SUCCESS;
}
