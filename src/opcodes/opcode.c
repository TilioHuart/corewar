/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** Table to contain every opcode instructions
*/

#include "champions/champions.h"
#include "opcodes/opcodes.h"
#include "virtualmachine/initialize_vm.h"

int (*instruction_table[])(cpu_t *cpu, champions_t *champion) = {
    &execute_opcode_live,
    &execute_opcode_ld,
    &execute_opcode_st,
    &execute_opcode_add,
    &execute_opcode_sub,
    &execute_opcode_and,
    &execute_opcode_or,
    &execute_opcode_xor,
    &execute_opcode_zjmp,
    &execute_opcode_ldi,
    &execute_opcode_sti,
    &execute_opcode_fork,
    &execute_opcode_lld,
    &execute_opcode_lldi,
    &execute_opcode_lfork,
    &execute_opcode_aff
};

static
int check_direct(cpu_t *cpu, champions_t *champion,
    size_t *parameter, int byte_read)
{
        *parameter = cpu->memory[(champion->program_counter + byte_read + 1)
            % MEM_SIZE];
        *parameter <<= 8;
        *parameter += cpu->memory[(champion->program_counter + byte_read + 2)
            % MEM_SIZE];
        *parameter <<= 8;
        *parameter += cpu->memory[(champion->program_counter + byte_read + 3)
            % MEM_SIZE];
        *parameter <<= 8;
        *parameter += cpu->memory[(champion->program_counter + byte_read + 4)
            % MEM_SIZE];
        return 4;
}

static
void check_indirect(cpu_t *cpu, champions_t *champion, size_t *parameter,
    int *byte_read)
{
    *parameter = cpu->memory[(champion->program_counter + *byte_read + 1)
        % MEM_SIZE];
    *parameter <<= 8;
    *parameter += cpu->memory[(champion->program_counter + *byte_read + 2)
        % MEM_SIZE];
    *byte_read += 2;
}

int retrieve_first_parameter(cpu_t *cpu, champions_t *champion,
    size_t *first_parameter, int byte_read)
{
    size_t parameter = 0;
    uint8_t coding_byte = cpu->memory[(champion->program_counter + 1)
        % MEM_SIZE];

    if (coding_byte >> 6 == 0x01) {
        parameter = cpu->memory[(champion->program_counter + 2) % MEM_SIZE];
        byte_read += 1;
    }
    if (coding_byte >> 6 == 0x02 && champion->index == false)
        byte_read += check_direct(cpu, champion, &parameter, byte_read);
    if (coding_byte >> 6 == 0x03 ||
        ((coding_byte >> 6 == 0x02) && champion->index == true)) {
        check_indirect(cpu, champion, &parameter, &byte_read);
    }
    *first_parameter = parameter;
    return byte_read;
}

int retrieve_second_parameter(cpu_t *cpu, champions_t *champion,
    size_t *first_parameter, int byte_read)
{
    size_t parameter = 0;
    uint8_t coding_byte = cpu->memory[(champion->program_counter + 1)
        % MEM_SIZE];

    coding_byte = coding_byte << 2;
    if (coding_byte >> 6 == 0x01) {
        parameter = cpu->memory[(champion->program_counter + byte_read + 1)
            % MEM_SIZE];
        byte_read += 1;
    }
    if (coding_byte >> 6 == 0x02 && champion->index == false)
        byte_read += check_direct(cpu, champion, &parameter, byte_read);
    if (coding_byte >> 6 == 0x03 ||
        ((coding_byte >> 6 == 0x02) && champion->index == true)) {
        check_indirect(cpu, champion, &parameter, &byte_read);
    }
    *first_parameter = parameter;
    return byte_read;
}

int retrieve_third_parameter(cpu_t *cpu, champions_t *champion,
    size_t *first_parameter, int byte_read)
{
    size_t parameter = 0;
    uint8_t coding_byte = cpu->memory[(champion->program_counter + 1)
        % MEM_SIZE];

    coding_byte = coding_byte << 4;
    if (coding_byte >> 6 == 0x01) {
        parameter = cpu->memory[(champion->program_counter + byte_read + 1)
            % MEM_SIZE];
        byte_read += 1;
    }
    if (coding_byte >> 6 == 0x02 && champion->index == false)
        byte_read += check_direct(cpu, champion, &parameter, byte_read);
    if (coding_byte >> 6 == 0x03 ||
        ((coding_byte >> 6 == 0x02) && champion->index == true)) {
        check_indirect(cpu, champion, &parameter, &byte_read);
    }
    *first_parameter = parameter;
    return byte_read;
}
