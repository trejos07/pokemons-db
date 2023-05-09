#include <stdlib.h>

#ifndef ICOMMAND_RECORDER_C
#define ICOMMAND_RECORDER_C

#include "CommandRecorder.h"
#include "CommandStack.c"
#include "ICommand.h"

struct CommandRecorder {
    int history_size;
    CommandStack* doHistory;
    CommandStack* undoHistory;
};

CommandRecorder* CommandRecorder_new(int history_size)
{
    CommandRecorder* recorder = malloc(sizeof(CommandRecorder));

    if (recorder == NULL) {
        printf("Error: Failed to allocate memory for CommandRecorder.\n");
        return NULL;
    }

    recorder->history_size = history_size;
    recorder->doHistory = CommandStack_new(history_size);
    recorder->undoHistory = CommandStack_new(history_size);
    return recorder;
}

void CommandRecorder_destroy(CommandRecorder* self)
{
    CommandStack_destroy(self->doHistory);
    CommandStack_destroy(self->undoHistory);
    free(self);
}

void CommandRecorder_record(CommandRecorder* self, ICommand* command)
{
    if (self->undoHistory->count > 0) {
        CommandStack_clear(self->undoHistory);
    }

    CommandStack_push(self->doHistory, command);
}

void CommandRecorder_swap_stacks(CommandStack* from, CommandStack* to, int to_move_count, void (*command_move_callback)(ICommand*))
{
    for (int i = 0; i < to_move_count; i++) {
        if (from->count == 0) {
            break;
        }

        ICommand* command = CommandStack_peak(from);
        command_move_callback(command);
        CommandStack_push(to, command);
        CommandStack_pop(from);
    }
    
}

void CommandRecorder_redo(CommandRecorder* self, int redo_count)
{
    CommandRecorder_swap_stacks(self->undoHistory, self->doHistory, redo_count, ICommand_execute);
}

void CommandRecorder_undo(CommandRecorder* self, int undo_count)
{
    CommandRecorder_swap_stacks(self->doHistory, self->undoHistory, undo_count, ICommand_un_execute);
}

#endif